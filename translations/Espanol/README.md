# SA-MP Rich Presence

El SA-MP Rich Presence es un ASI para SA-MP (San Andreas Multiplayer) que actualiza automáticamente tu estado de Discord con información detallada del servidor. El ASI se inyecta en el juego cuando te conectas a un servidor SA-MP, mostrando información del servidor.

## Idiomas

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Índice

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [¿Qué es un ASI?](#qué-es-un-asi)
  - [Funcionalidades](#funcionalidades)
    - [Discord Rich Presence](#discord-rich-presence)
  - [Requisitos](#requisitos)
  - [Instalación](#instalación)
  - [Arquitectura Técnica Detallada](#arquitectura-técnica-detallada)
    - [Sistema Principal (main.cpp)](#sistema-principal-maincpp)
    - [Gestor de Discord (discord\_manager.cpp)](#gestor-de-discord-discord_managercpp)
    - [Gestor de Servidor (server\_manager.cpp)](#gestor-de-servidor-server_managercpp)
    - [Sistema de Red (network\_manager.cpp)](#sistema-de-red-network_managercpp)
    - [Consulta al Servidor (server\_query.cpp)](#consulta-al-servidor-server_querycpp)
  - [Integración con SPC](#integración-con-spc)
    - [¿Qué es SPC Integration?](#qué-es-spc-integration)
    - [Cómo Funciona](#cómo-funciona)
    - [Gestor de URL (url\_manager.cpp)](#gestor-de-url-url_managercpp)
  - [Para Desarrolladores de Servidor](#para-desarrolladores-de-servidor)
  - [Estructura del Código](#estructura-del-código)
    - [Constantes Globales (constants.h)](#constantes-globales-constantsh)
    - [Estructuras de Datos (server\_types.h)](#estructuras-de-datos-server_typesh)
  - [Manejo de Errores](#manejo-de-errores)
  - [Sistema de Procesamiento de Línea de Comandos](#sistema-de-procesamiento-de-línea-de-comandos)
    - [Parser de Línea de Comandos (command\_line\_parser.cpp)](#parser-de-línea-de-comandos-command_line_parsercpp)
  - [Protocolo de Comunicación SA-MP](#protocolo-de-comunicación-sa-mp)
    - [Implementación del Protocolo](#implementación-del-protocolo)
  - [Beneficios del SA-MP Rich Presence](#beneficios-del-sa-mp-rich-presence)
  - [Notas Técnicas Adicionales](#notas-técnicas-adicionales)

## ¿Qué es un ASI?

ASI es una biblioteca dinámica (.dll) renombrada con la extensión .asi que es automáticamente cargada por un loader ASI cuando se inicia GTA San Andreas. Los plugins ASI permiten modificar o agregar funcionalidades al juego sin alterar los archivos originales, siendo una de las formas más populares de modding para GTA San Andreas y otros juegos de la serie GTA. Con un ASI loader instalado, puedes fácilmente instalar o remover modificaciones simplemente agregando o removiendo archivos .asi de la carpeta del juego.

## Funcionalidades

### Discord Rich Presence

El Discord Rich Presence es una funcionalidad que permite que las aplicaciones muestren información detallada sobre lo que el usuario está haciendo directamente en el perfil de Discord. En el caso del SA-MP Rich Presence, se muestra la siguiente información:
- Nombre del servidor (Hostname).
- Nombre del jugador.
- Número actual de jugadores y máximo de jugadores.
- IP y puerto del servidor.
- Imagen personalizada del servidor (requiere que el servidor tenga el plugin [SPC Integration](https://github.com/spc-samp/spc-integration)).
- Tiempo de juego.
- Estado de la conexión.

## Requisitos

- Cliente SA-MP (si no lo tienes: [clients-samp](https://github.com/spc-samp/clients-samp)).
- Aplicación Discord Desktop.
- Sistema Operativo Windows.
- Visual C++ Runtime.
- ASI Loader instalado en GTA San Andreas.

## Instalación

1. Descarga la versión más reciente del ASI compilado en [releases](https://github.com/ocalasans/samp-rich-presence/releases).
2. Asegúrate de tener un ASI Loader instalado en tu GTA San Andreas.
3. Copia el archivo .asi descargado en la carpeta de tu GTA San Andreas.
4. Inicia el juego con SA-MP.
5. El ASI se iniciará automáticamente cuando entres a un servidor.

## Arquitectura Técnica Detallada

### Sistema Principal (main.cpp)

El archivo main.cpp es el punto de entrada del ASI y responsable de:
1. Inicialización del sistema:
   ```cpp
   BOOL APIENTRY DllMain(HMODULE module_handle, DWORD reason, LPVOID) {
       switch (reason) {
           case DLL_PROCESS_ATTACH:
               DisableThreadLibraryCalls(module_handle);
               CreateThread(nullptr, 0, Update_Thread, nullptr, 0, nullptr);
               break;
           // ...
       }

       return TRUE;
   }
   ```

2. Gestión del hilo de actualización:
   ```cpp
   DWORD WINAPI Update_Thread(LPVOID) {
       // Inicializa WSA para operaciones de red
       WSAData wsa_data;
       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
       
       // Procesa parámetros de línea de comandos
       std::string server_ip, player_name;
       int server_port;
       
       // Inicializa gestores
       Global_Server_Manager = std::make_unique<Server_Manager>(server_ip, server_port, player_name);
       Global_Discord_Manager = std::make_unique<Discord_Manager>();
       
       // Bucle principal de actualización
       while (true) {
           Global_Server_Manager->Update();
           Global_Discord_Manager->Update_Presence(...);
           Sleep(Constants::PRESENCE_UPDATE_INTERVAL);
       }
   }
   ```

### Gestor de Discord (discord_manager.cpp)

El Discord_Manager es responsable de toda la integración con Discord Rich Presence:
1. Inicialización del Discord RPC:
   ```cpp
   void Discord_Manager::Initialize() noexcept {
       Sleep(5000);  // Espera inicialización de Discord
       
       DiscordEventHandlers discord_handlers{};
       Discord_Initialize("DISCORD_APP_ID", &discord_handlers, 1, NULL); // "DISCORD_APP_ID > Application ID"
       
       start_timestamp = time(nullptr);  // Marca el inicio de la sesión
   }
   ```

2. Actualización de la presencia:
   ```cpp
   void Discord_Manager::Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept {
       DiscordRichPresence discord_presence{};
       
       // Configura información básica
       discord_presence.state = player_name.data();
       discord_presence.details = server_info.Hostname.c_str();
       discord_presence.largeImageKey = current_image.data();
       
       // Agrega información del servidor
       discord_presence.largeImageText = server_info.Server_Address.c_str();
       discord_presence.startTimestamp = start_timestamp;
       discord_presence.partySize = server_info.Players;
       discord_presence.partyMax = server_info.Max_Players;
       
       Discord_UpdatePresence(&discord_presence);
   }
   ```

### Gestor de Servidor (server_manager.cpp)

El Server_Manager coordina todas las operaciones relacionadas con el servidor:
1. Gestión de estado:
   ```cpp
   Server_Manager::Server_Manager(const std::string& ip, int port, const std::string& name)
       : connection_status(false)
       , server_ip(ip)
       , server_port(port)
       , player_name(name)
       , current_image_url(Constants::DEFAULT_IMAGE)
   {}
   ```

2. Actualización de información:
   ```cpp
   bool Server_Manager::Update() {
       bool query_success = server_query.Query(server_data);
       
       if (query_success) {
           connection_status = true;
           server_data.Server_Address = Get_Server_Address();
           
           // Intenta obtener imagen personalizada del servidor
           std::string new_image_url = url_manager.Get_Image_URL(server_data.Server_Address);

           if (!new_image_url.empty())
               current_image_url = new_image_url;
       }
       // ...
   }
   ```

### Sistema de Red (network_manager.cpp)

El Network_Manager implementa toda la comunicación de red:
1. Inicialización del socket:
   ```cpp
   bool Network_Manager::Initialize(std::string_view ip, int port) noexcept {
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       
       // Configura timeout
       timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
       
       // Configura dirección del servidor
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(port);
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr);
       
       return true;
   }
   ```

### Consulta al Servidor (server_query.cpp)

El Server_Query implementa el protocolo de consulta de SA-MP:
1. Montaje del paquete de consulta:
   ```cpp
   bool Server_Query::Assemble_Query_Packet(char* packet) noexcept {
       memcpy(packet, QUERY_SIGNATURE, 4);  // "SAMP"
       packet[10] = 'i';  // Information query

       return true;
   }
   ```

2. Procesamiento de la respuesta:
   ```cpp
   bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
       // Extrae información como:
       // - Número de jugadores
       // - Máximo de jugadores
       // - Hostname
   }
   ```

## Integración con SPC

### ¿Qué es SPC Integration?

[SPC Integration](https://github.com/spc-samp/spc-integration) es un plugin desarrollado para **SA-MP** (San Andreas Multiplayer) y **open.mp** (Open Multiplayer) que actúa como un puente entre servidores y el ecosistema de **SPC**. El plugin recolecta información crucial del servidor, incluyendo:
- IP y puerto.
- URL del sitio web del servidor.
- URL de la imagen personalizada.
- Información de configuración.

Esta información se envía y almacena de forma segura en el almacenador de datos de **SPC (SA-MP Programming Community)**, permitiendo una integración con varias aplicaciones de **SPC**, incluyendo el Rich Presence.

### Cómo Funciona

1. El servidor utiliza el plugin [SPC Integration](https://github.com/spc-samp/spc-integration) para registrar su imagen personalizada.
2. La imagen se almacena en el almacenamiento de datos de **SPC** dentro del archivo JSON del servidor.
3. Cuando un jugador se conecta al servidor:
    - El URL_Manager del ASI intenta buscar el archivo JSON del servidor (formato: `ip-port.json`).
    - Si se encuentra, extrae la URL de la imagen del parámetro `spc_integration_image`.
    - La imagen se muestra entonces en el Discord Rich Presence del jugador.

### Gestor de URL (url_manager.cpp)

El URL_Manager es responsable de toda la comunicación con el almacenamiento de datos de **SPC**:
1. Búsqueda de la imagen del servidor:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       std::string formatted_address = server_address;
       // Convierte ":" a "-" en la dirección
       size_t colon_pos = formatted_address.find(':');

       if (colon_pos != std::string::npos)
           formatted_address.replace(colon_pos, 1, "-");
       
       // Busca JSON del servidor
       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;
       
       return image_url;
   }
   ```

2. Procesamiento del JSON:
   ```cpp
   std::string URL_Manager::Parse_JSON(const std::string& json_content) {
       const std::string key = "\"spc_integration_image\":";
       size_t key_pos = json_content.find(key);
       
       // Extrae URL de la imagen del JSON
       // ...
       
       return image_url;
   }
   ```

## Para Desarrolladores de Servidor

Si eres un desarrollador de servidor SA-MP, recomendamos encarecidamente la instalación del plugin [SPC Integration](https://github.com/spc-samp/spc-integration) por las siguientes razones:
1. Visibilidad:
    - La imagen personalizada de tu servidor se mostrará en el Discord de todos los jugadores que usen este ASI.
    - Aumenta el reconocimiento de la marca de tu servidor.
    - Proporciona una presentación más profesional.

2. Beneficios:
    - Mayor participación de los jugadores.
    - Diferenciación visual en Discord.
    - Integración automática con Rich Presence.

3. Cómo implementar:
   - Lee el repositorio del plugin [SPC Integration](https://github.com/spc-samp/spc-integration) para saber cómo implementarlo.

## Estructura del Código

El proyecto está organizado en varios componentes:
```
src/
├── discord/               # Biblioteca Discord RPC
├── command_line_parser.*  # Procesamiento de argumentos
├── constants.h            # Constantes globales
├── discord_manager.*      # Integración con Discord
├── main.cpp               # Punto de entrada
├── network_manager.*      # Operaciones de red
├── server_manager.*       # Gestión del servidor
├── server_query.*         # Protocolo SA-MP
├── server_types.h         # Estructuras de datos
└── url_manager.*          # Integración con SPC
```

### Constantes Globales (constants.h)

El archivo define varias constantes importantes:
```cpp
namespace Constants {
    // Valores predeterminados
    inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
    inline constexpr int DEFAULT_SERVER_PORT = 7777;
    
    // Configuraciones de red
    inline constexpr int QUERY_TIMEOUT = 1000;
    inline constexpr int QUERY_PACKET_SIZE = 11;
    inline constexpr int QUERY_BUFFER_SIZE = 512;
    
    // Configuraciones de reintento
    inline constexpr int MAX_RETRY_ATTEMPTS = 3;
    
    // Intervalos
    inline constexpr int PRESENCE_UPDATE_INTERVAL = 5000;
}
```

### Estructuras de Datos (server_types.h)

Define las estructuras principales:
```cpp
struct Server_Information {
    uint16_t Players{ 0 };           // Jugadores en línea
    uint16_t Max_Players{ 0 };       // Máximo de jugadores
    std::string Hostname;            // Nombre del servidor
    std::string Server_Image;        // URL de la imagen
    std::string Server_Address;      // Dirección del servidor
};
```

## Manejo de Errores

El sistema implementa un robusto sistema de manejo de errores:
1. Timeout de red:
   ```cpp
   timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
   setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
   ```

2. Sistema de reintento:
   ```cpp
   bool Server_Query::Try_Query(Server_Information& server_data, int retry_count) noexcept {
       for (int attempt = 0; attempt <= retry_count; attempt++) {
           if (network_manager.Send_Query(...))
               return true;
           
           // Espera antes de intentar nuevamente
           std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
       }

       return false;
   }
   ```

3. Retorno a imagen predeterminada:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       // Si algo sale mal, retorna la imagen predeterminada
       if (!session_handle)
           return Constants::DEFAULT_IMAGE;

       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;

       return image_url;
   }
   ```

4. Monitoreo del estado de conexión:
   ```cpp
   bool Server_Manager::Update() {
       auto current_time = std::chrono::steady_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_successful_query);
       
       // Si pasan más de 15 segundos sin respuesta, se considera desconectado
       if (duration.count() > 15) {
           connection_status = false;
           current_image_url = Constants::DEFAULT_IMAGE;
       }
   }
   ```

## Sistema de Procesamiento de Línea de Comandos

El ASI implementa un sistema flexible para procesar argumentos de línea de comandos:

### Parser de Línea de Comandos (command_line_parser.cpp)

1. Procesamiento principal:
   ```cpp
   bool Command_Line_Parser::Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       // Define valores predeterminados
       server_ip = Constants::DEFAULT_SERVER_IP;
       server_port = Constants::DEFAULT_SERVER_PORT;

       // Procesa cada parámetro
       std::wstring ip_parameter = Parse_Parameter(command_string, L"-h");
       std::wstring port_parameter = Parse_Parameter(command_string, L"-p");
       std::wstring name_parameter = Parse_Parameter(command_string, L"-n");

       // Convierte y valida los valores
       if (!ip_parameter.empty())
           server_ip = Convert_To_String(ip_parameter);

       if (!port_parameter.empty())
           server_port = std::stoi(port_parameter);

       if (!name_parameter.empty())
           player_name = Convert_To_String(name_parameter);

       // Verifica si todos los parámetros necesarios están presentes
       return !server_ip.empty() && server_port > 0 && !player_name.empty();
   }
   ```

2. Extracción de parámetros:
   ```cpp
   std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring& command_string, const wchar_t* parameter) {
       size_t position = command_string.find(parameter);
       
       if (position != std::wstring::npos) {
           position += wcslen(parameter) + 1;
           size_t end_position = command_string.find(L" ", position);
           
           if (end_position == std::wstring::npos)
               end_position = command_string.length();
           
           return command_string.substr(position, end_position - position);
       }
       
       return L"";
   }
   ```

## Protocolo de Comunicación SA-MP

El ASI implementa el protocolo de consulta de SA-MP para obtener información del servidor:
1. Estructura del paquete de consulta:
    - 4 bytes: Firma "SAMP"
    - 7 bytes: Datos adicionales
    - Último byte: 'i' (indica consulta de información)

2. Estructura de la respuesta:
    - Cabecera del paquete
    - Players (uint16_t)
    - Max_Players (uint16_t)
    - Hostname (string)

### Implementación del Protocolo

```cpp
bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
    char* current_pos = response_buffer + Constants::QUERY_PACKET_SIZE;
    const char* buffer_end = response_buffer + received_bytes;

    // Saltar "password"
    current_pos += sizeof(bool);
    
    // Lee datos fijos
    memcpy(&server_data.Players, current_pos, sizeof(server_data.Players));
    current_pos += sizeof(server_data.Players);
    
    memcpy(&server_data.Max_Players, current_pos, sizeof(server_data.Max_Players));
    current_pos += sizeof(server_data.Max_Players);

    // Lee Hostname y salta "gamemode" y "language"
    auto read_string = [](char*& pos, const char* end, std::string& str) noexcept -> bool {
        uint32_t length;
        memcpy(&length, pos, sizeof(length));
        pos += sizeof(length);
        
        str.assign(pos, length);
        pos += length;
        
        return true;
    };

    if (!read_string(current_pos, buffer_end, server_data.Hostname))
        return false;
    
    // Saltar "gamemode" y "language"
    // ...

    return true;
}
```

## Beneficios del SA-MP Rich Presence

1. Para Jugadores:
    - Visualización rápida del servidor actual.
    - Información detallada sobre el servidor.
    - Integración perfecta con Discord.
    - Experiencia de juego más social.

2. Para Servidores:
    - Mayor visibilidad a través de Discord.
    - Marketing orgánico a través de los jugadores.
    - Identidad visual personalizada (con el plugin [SPC Integration](https://github.com/spc-samp/spc-integration)).
    - Estadísticas en tiempo real.

## Notas Técnicas Adicionales

1. Seguridad de Hilos:
    - El ASI utiliza un único hilo para actualizaciones.
    - Los gestores son thread-safe por diseño.
    - Los recursos están correctamente sincronizados.

2. Uso de Memoria:
    - Asignación mínima de memoria.
    - Buffers preasignados para consultas.
    - Gestión automática de recursos (RAII).

3. Rendimiento:
    - Consultas optimizadas con timeout.
    - Sistema de reintento inteligente.
    - Intervalo de actualización configurable.

4. Compatibilidad:
    - Soporte para Unicode.
    - Compatible con Windows moderno.
    - Soporte para IPv4.