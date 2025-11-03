# SA-MP Rich Presence

El **SA-MP Rich Presence** es un **ASI** para **SA-MP (San Andreas Multiplayer)** que actualiza automáticamente tu estado en Discord con información detallada del servidor. El **ASI** se inyecta en el juego cuando te conectas a un servidor SA-MP, mostrando información del servidor.

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
  - [Funcionalidades](#funcionalidades)
    - [Discord Rich Presence](#discord-rich-presence)
    - [Sistema de Actualización Automática](#sistema-de-actualización-automática)
  - [Requisitos](#requisitos)
  - [Instalación](#instalación)
  - [Integración con la AlderGrounds Integration API](#integración-con-la-aldergrounds-integration-api)
    - [Cómo se Obtiene y Utiliza la Información:](#cómo-se-obtiene-y-utiliza-la-información)
  - [Para Desarrolladores de Servidores](#para-desarrolladores-de-servidores)
    - [Cómo Implementar la AlderGrounds Integration en Tu Servidor:](#cómo-implementar-la-aldergrounds-integration-en-tu-servidor)
  - [Arquitectura Técnica Detallada](#arquitectura-técnica-detallada)
      - [Sistema Principal (`main.cpp`)](#sistema-principal-maincpp)
      - [Sistema de Actualización (`asi_update.hpp`)](#sistema-de-actualización-asi_updatehpp)
      - [Gestor de Discord (`discord_manager.cpp`)](#gestor-de-discord-discord_managercpp)
      - [Gestor de Servidor (`server_manager.cpp`)](#gestor-de-servidor-server_managercpp)
      - [Sistema de Red (`samp_network.cpp`)](#sistema-de-red-samp_networkcpp)
      - [Consulta al Servidor (`server_query.cpp`)](#consulta-al-servidor-server_querycpp)
      - [Gestor de URL (`url_manager.cpp`)](#gestor-de-url-url_managercpp)
    - [Estructura del Código](#estructura-del-código)
      - [Constantes Globales (`constants.hpp`)](#constantes-globales-constantshpp)
      - [Estructuras de Datos (`server_types.hpp`)](#estructuras-de-datos-server_typeshpp)
      - [Ofuscación de Secretos (`secrets.hpp`)](#ofuscación-de-secretos-secretshpp)
      - [Utilitarios Generales (`utils.hpp`)](#utilitarios-generales-utilshpp)
    - [Tratamiento de Errores y Resiliencia](#tratamiento-de-errores-y-resiliencia)
    - [Sistema de Procesamiento de Línea de Comando](#sistema-de-procesamiento-de-línea-de-comando)
      - [Parser de Línea de Comando (`command_line_parser.cpp`)](#parser-de-línea-de-comando-command_line_parsercpp)
    - [Protocolo de Comunicación SA-MP](#protocolo-de-comunicación-sa-mp)
      - [Implementación del Protocolo](#implementación-del-protocolo)
    - [Beneficios del SA-MP Rich Presence](#beneficios-del-sa-mp-rich-presence)
  - [Licencia](#licencia)
    - [Condiciones:](#condiciones)

## Funcionalidades

### Discord Rich Presence

El **Discord Rich Presence** es una funcionalidad que permite que las aplicaciones muestren información detallada sobre lo que el usuario está haciendo directamente en el perfil de Discord. En el caso del **SA-MP Rich Presence**, se muestran las siguientes informaciones:

- **Nombre del servidor (Hostname):** El nombre principal del servidor.
- **Nombre del jugador:** Tu apodo actual en el juego.
- **Conteo de jugadores:** Número actual de jugadores en línea y el máximo permitido.
- **Dirección del servidor:** IP y puerto del servidor para fácil identificación.
- **Imagen personalizada del servidor:** Un logo único del servidor, si está disponible.
- **Ícono social rotativo:** Pequeños íconos que representan enlaces a redes sociales del servidor (website, Discord, YouTube, Instagram, Facebook, TikTok), alternando automáticamente.
- **Tiempo de juego:** Cuánto tiempo estás conectado al servidor actual.
- **Estado de la conexión:** Indica si estás en línea en un servidor o en el estado "Idle" (inactivo).
- **Botón "Join" (Unirse):** Permite que tus amigos se unan directamente al mismo servidor en el que estás jugando.

### Sistema de Actualización Automática

El **ASI** integra un sistema de verificación de actualización. Al iniciar el juego, verifica si hay nuevas versiones disponibles en el repositorio oficial de GitHub del proyecto. Si se detecta una actualización, se muestra una notificación amigable al usuario, ofreciendo opciones para:

1. Abrir el navegador directamente en la página de releases para la descarga.
2. Continuar sin actualizar, con la opción de deshabilitar el **ASI** para la sesión actual.

Esta funcionalidad garantiza que los usuarios siempre tengan acceso a las últimas mejoras, correcciones de errores y nuevas funcionalidades, promoviendo una experiencia actualizada y sin interrupciones.

## Requisitos

- Cliente SA-MP (en caso de no poseerlo: [clients-samp](https://github.com/aldergrounds/clients-samp)).
- Aplicación Discord Desktop.
- Sistema Operativo Windows.
- Visual C++ Runtime.
- Un [ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) instalado en tu Grand Theft Auto: San Andreas.

## Instalación

1. Descarga la versión más reciente del **ASI** compilada directamente desde la sección de [releases](https://github.com/ocalasans/samp-rich-presence/releases) en GitHub.
2. Después de la descarga, localiza el archivo `.asi`.
3. Copia el archivo `.asi` descargado a la carpeta raíz de tu GTA San Andreas (donde se encuentra el archivo `gta_sa.exe`).
4. Inicia el juego a través del cliente SA-MP.
5. El **ASI** se cargará e inicializará automáticamente cuando te conectes a un servidor, actualizando tu estado en Discord.

## Integración con la AlderGrounds Integration API

El **SA-MP Rich Presence** mejora significativamente la visualización de información en Discord a través de su integración con la **AlderGrounds Integration API**. En lugar de depender solo de datos básicos de consulta, el **ASI** ahora interactúa directamente con esta API para obtener información visual y social del servidor. Para entender más sobre el **AlderGrounds Integration** en sí, visita el repositorio oficial: [aldergrounds/integration](https://github.com/aldergrounds/integration).

### Cómo se Obtiene y Utiliza la Información:

1. **Formateo de la Dirección:** Cuando el jugador se conecta a un servidor (IP y Puerto), el **ASI** formatea esa dirección (`IP:PUERTO`) a un estándar amigable (`IP-PUERTO`), preparándola para la solicitud de la API.
2. **Solicitud a la API:** El **ASI** envía una solicitud `GET` al endpoint de la **AlderGrounds Integration API**, incluyendo el IP y el puerto formateados. Ejemplo de cómo se construye internamente la URL de la solicitud:
   ```cpp
   // Trecho adaptado de url_manager.cpp
   auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
   std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
   path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   const std::string json_data = Request_API_Data(path);
   ```
3. **Procesamiento de la Respuesta JSON:** La API retorna una respuesta en formato JSON. El **ASI** utiliza la biblioteca [nlohmann/json](https://github.com/nlohmann/json) para parsear esta respuesta y extraer los datos relevantes.
   ```json
   // Ejemplo de Estructura de Respuesta de la AlderGrounds Integration API
   {
       "success": true,
       "data": {
           "public": {
               "logo": "https://url.de.tu.logo/server_logo.png",
               "website": "https://tu-sitio.com",
               "discord": "https://discord.gg/tuservidor",
               "youtube": "https://youtube.com/tucanal"
               // ...otras redes sociales
           }
       }
   }
   ```
4. **Extracción de Datos:**
   - **Logo del Servidor:** La URL de la imagen del servidor (el `logo` dentro de la sección `public`) se extrae y se utiliza como la imagen principal (large image) en el **Discord Rich Presence**. Esto garantiza una identidad visual auténtica y personalizable para cada servidor.
   - **Enlaces Sociales:** Una lista predefinida de redes sociales (website, Discord, YouTube, Instagram, Facebook, TikTok) se verifica en la respuesta JSON. Para cada red social encontrada y con un valor válido, el nombre de la red y su respectivo enlace se almacenan.
5. **Visualización en Discord:** El `Server_Manager` utiliza la lista de enlaces sociales extraídos para implementar una rotación dinámica. Cada 30 segundos, se muestra un ícono diferente de una de las redes sociales del servidor como la "small image" (imagen pequeña) en la presencia de Discord, junto con el enlace o nombre de la plataforma, incentivando la exploración de las comunidades del servidor.

## Para Desarrolladores de Servidores

La integración de tu servidor con la [AlderGrounds Integration](https://github.com/aldergrounds/integration) trae una serie de beneficios directos e indirectos que impulsan la visibilidad y el compromiso de tu comunidad SA-MP. Si eres un desarrollador de servidores, considera las ventajas estratégicas:

1. **Potencia Tu Marca:**
   - **Visibilidad Premium:** El logo personalizado de tu servidor no será solo un texto, sino una imagen vibrante y llamativa, mostrada prominentemente en el perfil de Discord de todos los jugadores que usan este **ASI**. Esta es una forma orgánica y constante de branding.
   - **Presencia Profesional:** Al tener tu logo y redes sociales bien representadas, tu servidor proyecta una imagen más establecida y confiable, atrayendo más interés y potenciales nuevos jugadores.
2. **Expansión de la Comunidad:**
   - **Multiplica los Canales de Acceso:** Con la rotación de íconos sociales, puedes divulgar varias plataformas de tu comunidad – desde el sitio web oficial y el Discord del servidor hasta tus páginas en YouTube, Instagram, Facebook o TikTok. Cada ícono y enlace en el **Discord Rich Presence** dirige directamente a los interesados a donde tu comunidad está activa.
   - **Conectividad Instantánea:** La funcionalidad de "Join" a través de Discord permite que los amigos de tus jugadores se unan a tu servidor SA-MP con solo un clic, reduciendo barreras de entrada e incentivando nuevos miembros.
3. **Actualización Simplificada de Contenido:**
   - Al utilizar la [AlderGrounds Integration](https://github.com/aldergrounds/integration), cualquier actualización en el logo de tu servidor o en la lista de redes sociales configuradas en el plugin [AlderGrounds Integration](https://github.com/aldergrounds/integration) **(en el lado del servidor)** se reflejará automáticamente para los jugadores que usan el **ASI**, sin que ellos necesiten actualizar el **ASI**. Esto garantiza que la información esté siempre correcta y actualizada.

### Cómo Implementar la AlderGrounds Integration en Tu Servidor:

1. **Plugin AlderGrounds Integration:** Tu servidor necesitará tener el plugin [AlderGrounds Integration](https://github.com/aldergrounds/integration) instalado y configurado correctamente. Este plugin es el puente que envía la información de tu servidor a una lista de datos de **AlderGrounds**, que, a su vez, es utilizada por la **AlderGrounds Integration API** para disponibilizar información pública.
2. **Configuración:** Sigue las instrucciones en el repositorio del plugin [AlderGrounds Integration](https://github.com/aldergrounds/integration) para configurar:
   - El parámetro `logo` con la URL del logo de tu servidor.
   - Los parámetros de redes sociales (`discord`, `website`, `youtube`, etc.) con los enlaces válidos para tus plataformas.
3. **Actualización Automática:** Una vez que la información esté configurada en el plugin del servidor, el **SA-MP Rich Presence** la detectará y mostrará automáticamente. No es necesaria ninguna acción por parte del jugador más allá de la instalación inicial del **ASI**.

Al integrar tu servidor con la [AlderGrounds Integration](https://github.com/aldergrounds/integration), no solo mejoras la experiencia de tus jugadores, sino que también abres puertas para un crecimiento y compromiso significativos para tu comunidad.

## Arquitectura Técnica Detallada

El **SA-MP Rich Presence** tiene una arquitectura modular bien definida, con componentes enfocados en tareas específicas. La base de código está alineada con estándares modernos de C++ (C++17 y C++20), utilizando `std::string_view`, `std::span` y semántica de movimiento para garantizar un alto rendimiento, seguridad y eficiencia.

#### Sistema Principal (`main.cpp`)

El corazón del **ASI** reside en `main.cpp`, que gestiona el ciclo de vida de la aplicación, desde su inicialización como una DLL hasta el bucle continuo de actualización y su apagado elegante.

- **`DllMain`**: La puerta de entrada del **ASI** cuando es cargado por el sistema operativo.
   ```cpp
   // DllMain (simplificado para enfoque en la estructura)
   BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
       switch (dwReason) {
           case DLL_PROCESS_ATTACH:
               DisableThreadLibraryCalls(hModule);

               if (HANDLE thread = CreateThread(nullptr, 0, Main_Update_Thread, nullptr, 0, nullptr))
                   CloseHandle(thread);

               break;
           case DLL_PROCESS_DETACH:
               Shutdown_Managers();

               break;
       }

       return TRUE;
   }
   ```
   En esta función, al ser anexada al proceso del juego (`DLL_PROCESS_ATTACH`), impide llamadas de biblioteca innecesarias (`DisableThreadLibraryCalls`) y **crea un nuevo hilo (`Main_Update_Thread`)** para ejecutar la lógica del **ASI** de forma asíncrona, garantizando que el juego no se bloquee. Durante el apagado (`DLL_PROCESS_DETACH`), se invoca `Shutdown_Managers()` para liberar recursos.
- **`Main_Update_Thread`**: El alma del **ASI**, operando en su propio hilo.
   ```cpp
   // Main_Update_Thread (trecho clave)
   DWORD WINAPI Main_Update_Thread(LPVOID) {
       // 1. Verificación de Actualización
       if (Asi_Update::Check_For_Update())
           return 0; // Si el usuario optó por desactivar, finaliza.
   
       // 2. Inicialización de la Red (Winsock)
       WSAData wsa_data;

       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
   
       // 3. Inicializa Gestores de Servidor y Discord
       Initialize_Managers();
   
       // 4. Bucle Principal de Actualización
       while (is_running && v_server_manager && v_discord_manager) {
           v_server_manager->Update(); // Consulta servidor, API AlderGrounds, etc.
           v_discord_manager->Update_Presence( // Actualiza el estado de Discord
               v_server_manager->Get_Server_Info(),
               v_server_manager->Get_Display_Social_Link(),
               v_server_manager->Get_Player_Name(),
               v_server_manager->Get_Current_Image_URL(),
               v_server_manager->Is_Connected());
   
           Discord_RunCallbacks(); // Procesa eventos RPC de Discord
           std::this_thread::sleep_for(Constants::MAIN_LOOP_INTERVAL);
       }
   
       // 5. Apagado (si los gestores existen)
       if (v_discord_manager)
           v_discord_manager->Shutdown();

       WSACleanup(); // Libera Winsock

       return 0;
   }
   ```
   Esta función prioriza la verificación de actualizaciones. Luego, inicializa la pila de red Winsock e instancias de los gestores de servidor y Discord. Un bucle `while` persistente (controlado por la `std::atomic<bool> is_running` para un apagado seguro) coordina las llamadas a `Server_Manager::Update()` (recopilación de datos) y `Discord_Manager::Update_Presence()` (envío a Discord). `Discord_RunCallbacks()` asegura que Discord procese los eventos de la Rich Presence. El bucle se pausa periódicamente usando `std::this_thread::sleep_for` para optimización de recursos.

#### Sistema de Actualización (`asi_update.hpp`)

Este módulo vital añade inteligencia al **ASI**, garantizando que los usuarios permanezcan actualizados.

- **`Check_For_Update()`**: La función principal de verificación.
   ```cpp
   // asi_update.hpp (trecho clave de Check_For_Update)
   inline bool Check_For_Update() {
       HINTERNET h_session = nullptr, h_connect = nullptr, h_request = nullptr;
       bool update_found_and_handled = false;
   
       try {
           h_session = WinHttpOpen(L"SA-MP Rich Presence Update/1.0", ...);
           // ... (solicitud GET para Constants::UPDATE_API_PATH en la API de GitHub) ...
           std::string response_body;
           // ... (lectura de la respuesta HTTP) ...
           nlohmann::json release_info = nlohmann::json::parse(response_body);
   
           std::string latest_tag = release_info["tag_name"].get<std::string>();
           // ... (normaliza y compara las versiones usando sscanf_s/sscanf) ...
   
           if (latest_major > current_major || (latest_major == current_major && latest_minor > current_minor)) {
               update_found_and_handled = true;
               std::wstringstream message_stream;
               // ... (prepara el mensaje de la MessageBox) ...
               int msgbox_result = MessageBoxW(NULL, message_stream.str().c_str(), L"SA-MP Rich Presence - Update Available", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
               
               if (msgbox_result == IDYES)
                   ShellExecuteW(NULL, L"open", Constants::UPDATE_RELEASES_URL, NULL, NULL, SW_SHOWNORMAL);
           }
       }
       catch (const std::exception&) { /* Tratamiento de error */ }
   
       // ... (cerrar handles WinHttp) ...
       return update_found_and_handled;
   }
   ```
   Utilizando la **API WinHTTP** para solicitudes de red, `Check_For_Update` realiza una solicitud `GET` al endpoint `/releases/latest` de la API de GitHub para el repositorio del proyecto. La respuesta, en formato JSON, se parsea con la biblioteca `nlohmann/json`. La versión más reciente (`tag_name`) se compara numéricamente con la versión compilada del **ASI**. Si se detecta una nueva versión, se muestra una caja de diálogo (`MessageBoxW`), preguntando al usuario si desea ir a la página de descargas vía `ShellExecuteW`. Todo el proceso está encapsulado en un `try-catch` para garantizar que fallos de red o parseo no comprometan el inicio del juego.

#### Gestor de Discord (`discord_manager.cpp`)

La clase `Discord_Manager` abstrae las interacciones con la biblioteca **Discord RPC**, gestionando la inicialización de la conexión y el envío de datos para el estado de presencia del usuario.

- **`Initialize()`**: Configura la comunicación con Discord.
   ```cpp
   // discord_manager.cpp (trecho clave de Initialize)
   void Discord_Manager::Initialize() noexcept {
       DiscordEventHandlers handlers;
       memset(&handlers, 0, sizeof(handlers)); // Garantiza inicialización
       
       // App ID se desofusca aquí
       auto app_id_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_Discord_App_ID());
       Discord_Initialize(app_id_accessor.Get(), &handlers, 1, nullptr);
   
       start_timestamp_ = time(nullptr); // Registra inicio de la sesión
   }
   ```
   La llamada a `Discord_Initialize` es crucial, utilizando el `DISCORD_APP_ID` que se obtiene de forma segura a través de la ofuscación de string en `secrets.hpp`. El `start_timestamp_` se define aquí para calcular el tiempo de juego en la presencia de Discord.
- **`Update_Presence()`**: La función vital que actualiza la Rich Presence de Discord.
   ```cpp
   // discord_manager.cpp (trecho clave de Update_Presence)
   void Discord_Manager::Update_Presence(const Server_Information& server_info, const server_types::Social_Link& social_link, const std::string_view player_name, const std::string_view current_image, const bool is_connected) noexcept {
       DiscordRichPresence discord_presence;
       memset(&discord_presence, 0, sizeof(discord_presence));
   
       discord_presence.startTimestamp = start_timestamp_;
       discord_presence.largeImageKey = current_image.data(); // Logo del servidor
   
       if (is_connected) {
           discord_presence.details = server_info.Hostname.c_str();
           discord_presence.state = player_name.data();
           discord_presence.largeImageText = server_info.Server_Address.c_str(); // IP:Puerto
           discord_presence.partySize = server_info.Players;
           discord_presence.partyMax = server_info.Max_Players;
           discord_presence.joinSecret = server_info.Server_Address.c_str(); // Habilita el botón "Join"
   
           // Gestiona el ícono social rotativo
           if (!social_link.first.empty()) {
               current_small_image_key_ = Constants::SOCIAL_ICON_BASE_URL;
               current_small_image_key_ += social_link.first; // Ej: "discord.png"
               current_small_image_key_ += ".png";
               discord_presence.smallImageKey = current_small_image_key_.c_str();
               discord_presence.smallImageText = social_link.second.c_str(); // Texto al pasar el mouse (enlace/nombre)
           }
       }
       else {
           discord_presence.details = "SA-MP"; // Estado "Idle"
           discord_presence.state = "Idle";
           discord_presence.largeImageText = "San Andreas Multiplayer";
           // smallImageKey y smallImageText permanecen vacíos para el estado idle
       }
   
       Discord_UpdatePresence(&discord_presence);
   }
   ```
   Rellena la estructura `DiscordRichPresence` basándose en el estado de la conexión. Si `is_connected` es verdadero, el hostname, conteo de jugadores, IP del servidor y el nombre del jugador se muestran. El `largeImageKey` define la imagen principal del servidor. Notablemente, `joinSecret` se define para permitir que los amigos se conecten directamente, y el `smallImageKey` (construido dinámicamente basándose en el `social_link` proporcionado) muestra los íconos sociales rotativos. En estado "Idle", la presencia se simplifica para reflejar la inactividad. Finalmente, `Discord_UpdatePresence` envía los datos a Discord.

#### Gestor de Servidor (`server_manager.cpp`)

El `Server_Manager` es el orquestador de los datos, gestionando el estado de conexión, consultando el servidor y la **AlderGrounds Integration API**, y decidiendo qué información debe mostrarse y cuándo.

- **`Update()`**: El ciclo de vida principal para la recolección de datos.
   ```cpp
   // server_manager.cpp (trecho clave de Update)
   void Server_Manager::Update() {
       const auto now = std::chrono::steady_clock::now();
   
       if (server_query.Query(live_server_data)) { // Intenta obtener datos vía consulta SAMP
           if (!connection_status) { // Si acaba de conectar/reconectar
               connection_status = true;
               Fetch_API_Data(); // Obtiene logo y sociales de la API
           }
           
           last_successful_query = now;
   
           // Actualiza datos a mostrarse en Discord
           display_server_data.Hostname = live_server_data.Hostname;
           display_server_data.Players = live_server_data.Players;
           display_server_data.Max_Players = live_server_data.Max_Players;
           display_server_data.Server_Address = server_ip + ":" + std::to_string(server_port);
   
           if (now - last_api_update > Constants::IMAGE_UPDATE_INTERVAL)
               Fetch_API_Data(); // Reconsulta la API tras el tiempo definido
   
           if (now - last_social_rotation > Constants::SOCIAL_UPDATE_INTERVAL)
               Rotate_Social_Link(); // Rota el ícono social
       }
       else { // Si la consulta falló
           if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
               connection_status = false; // Desconectado tras timeout
               display_image_url = Constants::DEFAULT_IMAGE;
               display_server_data = {}; // Limpia datos
               current_display_social = {}; // Limpia social
           }
       }
   }
   ```
   La función `Update` intenta realizar una consulta al servidor. Si tiene éxito, actualiza los datos en `live_server_data` y `display_server_data`. Condicionalmente, llama a `Fetch_API_Data()` para actualizar la imagen y los enlaces sociales (si es una nueva conexión o si ha pasado el `IMAGE_UPDATE_INTERVAL`) y `Rotate_Social_Link()` para alternar los íconos sociales (`SOCIAL_UPDATE_INTERVAL`). Si las consultas al servidor fallan consistentemente por más de 15 segundos, el estado de la conexión se considera perdido, redefiniendo las informaciones mostradas.
- **`Fetch_API_Data()`**: Responsable de obtener los datos visuales y sociales.
   ```cpp
   // server_manager.cpp (trecho clave de Fetch_API_Data)
   void Server_Manager::Fetch_API_Data() {
       display_image_url = url_manager.Get_Image_URL_And_Populate_Socials(server_ip, server_port, live_server_data);
       last_api_update = std::chrono::steady_clock::now();
       current_social_index_ = 0; // Resetea índice tras nueva obtención de la API
       Rotate_Social_Link(); // Asegura que un ícono social se muestre inmediatamente
   }
   ```
   Esta función coordina con `URL_Manager` para obtener el logo y los enlaces sociales de la API, actualizando el `display_image_url` y poblando los `Social_Links` dentro de `live_server_data`. Resetea el índice de rotación de sociales y llama a `Rotate_Social_Link()` para garantizar que el primer ícono esté listo para mostrarse.
- **`Rotate_Social_Link()`**: Lógica para alternar los íconos sociales.
   ```cpp
   // server_manager.cpp (trecho clave de Rotate_Social_Link)
   void Server_Manager::Rotate_Social_Link() {
       if (!live_server_data.Social_Links.empty()) {
           if (current_social_index_ >= live_server_data.Social_Links.size())
               current_social_index_ = 0; // Reinicia el ciclo
   
           current_display_social = live_server_data.Social_Links[current_social_index_];
           current_social_index_ = (current_social_index_ + 1) % live_server_data.Social_Links.size();
       }
       else
           current_display_social = {}; // Limpia si no hay sociales
       
       last_social_rotation = std::chrono::steady_clock::now();
   }
   ```
   Esta función simple selecciona el próximo `Social_Link` en la lista de `live_server_data.Social_Links` de forma cíclica y lo almacena en `current_display_social` para que el `Discord_Manager` pueda utilizarlo.

#### Sistema de Red (`samp_network.cpp`)

La clase `Samp_Network` es la implementación de bajo nivel de la comunicación **UDP**, responsable de abrir y gestionar el socket para consultas de SA-MP. Ahora ofrece constructores y operadores de movimiento para una mejor gestión de recursos.

- **`Initialize()`**: Configura el socket para comunicación **UDP**.
   ```cpp
   // samp_network.cpp (trecho clave de Initialize)
   bool Samp_Network::Initialize(const std::string_view ip, const int port) noexcept {
       if (network_socket != INVALID_SOCKET)
           closesocket(network_socket); // Cierra socket existente
   
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       if (network_socket == INVALID_SOCKET)
           return false;
   
       const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
       setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
   
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(static_cast<u_short>(port));
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr); // Soporte para IP V4
       return true;
   }
   ```
   Inicializa el socket, define timeouts para operaciones de envío y recepción, y configura la estructura de dirección (`sockaddr_in`) con el IP y puerto del servidor de destino, usando `inet_pton` para manejar la conversión del IP.
- **`Send_Query()`**: Envía un paquete de consulta y recibe la respuesta.
   ```cpp
   // samp_network.cpp (trecho clave de Send_Query)
   bool Samp_Network::Send_Query(const std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept {
       // Envía el paquete UDP
       if (sendto(network_socket, query_packet.data(), static_cast<int>(query_packet.size()), 0, reinterpret_cast<const sockaddr*>(&server_address), sizeof(server_address)) < 0)
           return false;
   
       sockaddr_in from_address;
       int address_length = sizeof(from_address);
       // Recibe la respuesta
       received_bytes = recvfrom(network_socket, response_buffer.data(), static_cast<int>(response_buffer.size()), 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);
   
       return received_bytes > Constants::QUERY_PACKET_SIZE;
   }
   ```
   Este método envía el `query_packet` (pasado como `std::span` para seguridad de buffer) al servidor. Luego, intenta recibir una respuesta en el `response_buffer`. El retorno indica si la operación fue exitosa y si se recibió un número de bytes mayor que el tamaño del paquete de consulta.

#### Consulta al Servidor (`server_query.cpp`)

La clase `Server_Query` está dedicada a la implementación del protocolo de consulta SA-MP (`'i'`), extrayendo las informaciones básicas del servidor (jugadores, hostname) a partir de las respuestas **UDP**.

- **`Query()`**: Gestiona los intentos de consulta.
   ```cpp
   // server_query.cpp (trecho clave de Query)
   bool Server_Query::Query(Server_Information& server_data) noexcept {
       for (int attempt = 0; attempt < Constants::MAX_RETRY_ATTEMPTS; ++attempt) {
           if (Try_Query(server_data))
               return true; // Éxito en la consulta
   
           if (attempt < Constants::MAX_RETRY_ATTEMPTS - 1)
               // Pequeña pausa antes de intentar de nuevo, para evitar flooding
               std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)));
       }

       return false; // Todos los intentos fallaron
   }
   ```
   Implementa la estrategia de *retry* con `MAX_RETRY_ATTEMPTS` y un *back-off* de tiempo creciente, para garantizar que las consultas sean robustas y eviten saturar la red. Llama a `Try_Query` en cada intento.
- **`Assemble_Query_Packet()`**: Monta el paquete de consulta SA-MP.
   ```cpp
   // server_query.cpp (trecho clave de Assemble_Query_Packet)
   void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
       memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
       packet = 'i'; // Código de consulta de información
   }
   ```
   El paquete estándar para la consulta de información (`'i'`) de SA-MP se construye, incluyendo la firma "SAMP" y el byte identificador 'i'.
- **`Parse_Response()`**: Desempaqueta la respuesta binaria del servidor.
   ```cpp
   // server_query.cpp (trecho clave de Parse_Response)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       if (response.size() <= Constants::QUERY_PACKET_SIZE) 
           return false;
   
       auto data_span = response.subspan(Constants::QUERY_PACKET_SIZE); // Salta el encabezado
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Ignorado, pero leído
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false;

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false;

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false;
   
       // Nota: Gamemode y Language se saltan automáticamente por Read_String_From_Span si el paquete contiene más datos.
       // Si necesitas los otros campos, basta con crear una string y llamar: Read_String_From_Span(data_span, string_variable);
       return true;
   }
   ```
   Este método lee de forma segura los datos del `response_buffer` (utilizando `std::span` y las funciones auxiliares `Read_From_Span` y `Read_String_From_Span`). Extrae el número de jugadores, el máximo de jugadores y el hostname del servidor, poblando la estructura `Server_Information`. Los campos no utilizados (como si el servidor está protegido por contraseña) se leen pero se ignoran, y otros como "gamemode" y "language" se "saltan" si la respuesta contiene más datos que el **ASI** necesita en el momento.
- **Funciones de Lectura Auxiliares:**
   ```cpp
   // server_query.hpp (snippets de las auxiliares de lectura)
   template<typename T>
   static bool Read_From_Span(std::span<const char>& s, T& value) noexcept;
   
   static bool Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept;
   ```
   `Read_From_Span` maneja la lectura de tipos fijos (enteros, booleanos) del `std::span` y avanza el `span`. `Read_String_From_Span` lee el longitud de una string (como `uint32_t`) y luego la propia string, también avanzando el `span`. Esto garantiza seguridad al parsear bytes e impide lecturas fuera de los límites del buffer.

#### Gestor de URL (`url_manager.cpp`)

La clase `URL_Manager` gestiona las comunicaciones HTTPS con la **AlderGrounds Integration API**, un elemento central para las nuevas funcionalidades visuales y sociales del **Discord Rich Presence**.

- **`Get_Image_URL_And_Populate_Socials()`**: El método de alto nivel para buscar información de la API.
   ```cpp
   // url_manager.cpp (trecho clave de Get_Image_URL_And_Populate_Socials)
   std::string URL_Manager::Get_Image_URL_And_Populate_Socials(const std::string& ip, const int port, Server_Information& server_info) {
       if (!session_handle)
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);
   
       auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
       std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
       path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   
       const std::string json_data = Request_API_Data(path); // Solicitud HTTP para la API
   
       if (json_data.empty())
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE); // Error en la solicitud
   
       return Parse_API_Response(json_data, server_info); // Parsea y llena la server_info
   }
   ```
   Recibe IP y puerto, construye la URL de la API incluyéndolos como parámetros. Llama a `Request_API_Data` para obtener los datos JSON. En caso de éxito, `Parse_API_Response` se llama para extraer la URL de la imagen (logo) y llenar la lista de enlaces sociales en el `server_info`.
- **`Request_API_Data()`**: Realiza la solicitud HTTPS para la API.
   ```cpp
   // url_manager.cpp (trecho clave de Request_API_Data)
   std::string URL_Manager::Request_API_Data(const std::wstring& path) {
       auto api_host_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Host());
       const std::wstring wide_host = Utils::Convert_Utf8_To_Wide_String(api_host_accessor.Get());
       HINTERNET connect_handle = WinHttpConnect(session_handle, wide_host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
   
       if (!connect_handle) return "";
   
       HINTERNET request_handle = WinHttpOpenRequest(connect_handle, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
   
       if (!request_handle) return (WinHttpCloseHandle(connect_handle), "");
   
       // Enviar solicitud, recibir respuesta, verificar estado 200, leer datos en bucle
       // ... (detalles de la llamada WinHttpSendRequest, WinHttpReceiveResponse, WinHttpQueryHeaders, WinHttpReadData) ...
       
       WinHttpCloseHandle(request_handle); WinHttpCloseHandle(connect_handle);
       return response_body; // Retorna el JSON como string
   }
   ```
   Conecta al host de la API (obtenido de forma ofuscada), abre y envía una solicitud `GET` con el camino (`path`). Maneja la respuesta HTTP, verifica el código de estado (200 OK para éxito), y lee el cuerpo completo de la respuesta (que debe ser JSON). Todos los handles WinHTTP se liberan en caso de éxito o fallo.
- **`Parse_API_Response()`**: Procesa la string JSON para extraer datos.
   ```cpp
   // url_manager.cpp (trecho clave de Parse_API_Response)
   std::string URL_Manager::Parse_API_Response(const std::string& json_content, Server_Information& server_info) {
       server_info.Social_Links.clear(); // Limpia enlaces sociales existentes
       try {
           const auto json = nlohmann::json::parse(json_content);
   
           if (json.value("success", false) && json.contains("data") && json["data"].contains("public")) {
               const auto& public_data = json["data"]["public"];
               const std::vector<std::string> social_keys = { "website", "discord", "youtube", "instagram", "facebook", "tiktok" };
               
               // Extrae y llena enlaces sociales
               for (const auto& key : social_keys) {
                   if (public_data.contains(key)) {
                       std::string value = public_data.value(key, "not-defined");

                       if (!value.empty() && value != "not-defined")
                           server_info.Social_Links.push_back({ key, value });
                   }
               }

               return public_data.value("logo", ""); // Retorna la URL del logo
           }
       }
       catch (const nlohmann::json::exception&) { /* Maneja error de parseo */ }

       return ""; // Fallo en el parseo
   }
   ```
   Utiliza `nlohmann::json::parse` para convertir la string JSON en un objeto JSON manipulable. Navega por la estructura (`success`, `data`, `public`) y extrae el `logo` (que se convierte en el `display_image_url`) e itera sobre claves predefinidas para encontrar y poblar los `Social_Links` del `server_info`.

### Estructura del Código

El proyecto **SA-MP Rich Presence** está cuidadosamente organizado en un diseño de directorios claro, con el código fuente (`src/`) y un subdirectorio para bibliotecas externas (`libraries/`). La nomenclatura de los archivos sigue la convención `_manager` o `_network` para claridad sobre el propósito de cada clase. La mayoría de los archivos de encabezado usan la extensión `.hpp`, indicando que son archivos de encabezado C++.

```
src/
├── libraries/               # Contiene bibliotecas de terceros esenciales
│   ├── Dralyxor/            # Biblioteca de ofuscación de strings
│   ├── Discord/             # Biblioteca oficial de Discord RPC
│   └── nlohmann/            # Biblioteca para manipulación de JSON
├── asi_update.hpp           # Definición del sistema de actualización automática
├── command_line_parser.hpp  # Definición del parser de línea de comando
├── constants.hpp            # Definiciones de constantes globales del proyecto
├── discord_manager.hpp      # Definición del gestor de comunicación con Discord
├── main.cpp                 # Punto de entrada del ASI y orquestador principal
├── samp_network.hpp         # Definición del gestor de red para consultas SA-MP
├── secrets.hpp              # Definiciones para ofuscación de secretos
├── server_manager.hpp       # Definición del gestor de información del servidor
├── server_query.hpp         # Definición de la lógica de consulta al servidor SA-MP
├── server_types.hpp         # Definiciones de estructuras de datos del servidor
├── url_manager.hpp          # Definición del gestor de URL para AlderGrounds Integration API
└── utils.hpp                # Funciones utilitarias generales (conversión de strings)
```

#### Constantes Globales (`constants.hpp`)

Este archivo concentra todas las configuraciones y valores inmutables del proyecto, accesibles globalmente. Usa `inline constexpr` para garantizar que las constantes estén directamente disponibles para el compilador, optimizando el rendimiento.

```cpp
// constants.hpp (trecho)
namespace Constants {
    inline constexpr char ASI_VERSION[] = "1.1"; // Versión para el sistema de actualización
    inline constexpr wchar_t UPDATE_API_HOST[] = L"api.github.com"; // Host de la API de actualización
    inline constexpr char DEFAULT_IMAGE[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/default_logo.png"; // Imagen predeterminada
    inline constexpr int QUERY_TIMEOUT_MS = 800; // Timeout de la consulta en ms
    inline constexpr std::chrono::seconds MAIN_LOOP_INTERVAL = std::chrono::seconds(1); // Intervalo del bucle principal
}
```
Detalles importantes como URLs de API, caminos de imágenes predeterminadas, tiempos límite de red e intervalos de actualización del **Discord Rich Presence** están centralizados aquí. El uso de `std::chrono::seconds` para intervalos mejora la legibilidad y previene errores de unidades.

#### Estructuras de Datos (`server_types.hpp`)

Este archivo define los `structs` y `using` importantes para organizar los datos recopilados y mostrados.

```cpp
// server_types.hpp (trecho)
namespace server_types {
    using Social_Link = std::pair<std::string, std::string>; // Tupla (nombre de la red, URL/valor)
}

struct Server_Information {
    uint16_t Players{0};           // Número de jugadores actuales
    uint16_t Max_Players{0};       // Capacidad máxima de jugadores
    std::string Hostname{};        // Nombre del servidor
    std::string Server_Address{};  // Ej: "192.168.1.1:7777"

    std::vector<server_types::Social_Link> Social_Links{}; // Lista de enlaces sociales del servidor
};
```
La `Server_Information` es la estructura primaria que almacena los datos del servidor. La adición de `std::vector<server_types::Social_Link> Social_Links` refleja la nueva capacidad de obtener múltiples enlaces de redes sociales de la API, organizados como pares `(nombre_red, enlace)`.

#### Ofuscación de Secretos (`secrets.hpp`)

Este archivo está dedicado a proteger información sensible, como el **Discord Application ID** y las direcciones de la **AlderGrounds Integration API (por ahora)**, de ingeniería inversa fácil.

```cpp
// secrets.hpp (trecho)
#include "libraries/Dralyxor/dralyxor.hpp"

namespace Secrets {
    namespace {
        inline auto& Get_Obfuscated_Discord_App_ID() {
            static auto& dc_app_id_obfuscated = DRALYXOR_KEY("DISCORD_APP_ID", "YOUR_SECRET_KEY_HERE");

            return dc_app_id_obfuscated;
        }
        // ... (otros secretos ofuscados) ...
    }
    namespace Detail {
        inline auto& Get_Discord_App_ID() {
            return Get_Obfuscated_Discord_App_ID();
        }
        // ... (getters públicos para acceder a los secretos desofuscados) ...
    }
}
```
La biblioteca [Dralyxor](https://github.com/ocalasans/dralyxor) se usa con la macro `DRALYXOR_KEY` para encriptar strings literales en el binario compilado. `DRALYXOR_SECURE` se usa luego en tiempo de ejecución para desofuscar esos valores cuando son necesarios, añadiendo una capa de seguridad robusta contra la extracción estática de claves.

#### Utilitarios Generales (`utils.hpp`)

Un archivo para funciones auxiliares genéricas que pueden ser útiles en varios módulos, evitando duplicación de código.

```cpp
// utils.hpp (trecho)
namespace Utils {
    inline std::string Convert_Wide_To_Utf8_String(const std::wstring_view wide_string) {
        // ... (implementación de conversión usando WideCharToMultiByte) ...
    }

    inline std::wstring Convert_Utf8_To_Wide_String(const std::string_view narrow_string) {
        // ... (implementación de conversión usando MultiByteToWideChar) ...
    }
}
```
Contiene funciones `Convert_Wide_To_Utf8_String` y `Convert_Utf8_To_Wide_String`, esenciales para interoperaciones con APIs de Windows (que usan UTF-16) y operaciones estándar de C++ (que generalmente se benefician del UTF-8). Estas funciones usan las APIs de Windows para conversión segura y eficiente.

### Tratamiento de Errores y Resiliencia

El **SA-MP Rich Presence** fue diseñado con resiliencia en mente, incorporando múltiples mecanismos para lidiar con errores de red, entradas inválidas lidiar con errores de red, entradas inválidas e indisponibilidad de servicios.

- **Timeouts y Retries de Red:**
   - **Timeouts Explícitos:** Los sockets de red en `samp_network.cpp` configuran timeouts (`Constants::QUERY_TIMEOUT_MS`) tanto para envío como para recepción de datos, previniendo que el programa se quede "congelado" esperando una respuesta de un servidor inactivo.
      ```cpp
      // samp_network.cpp (configuración de timeout)
      const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
      setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      ```
   - **Múltiples Intentos de Consulta:** El `Server_Query` ejecuta `Constants::MAX_RETRY_ATTEMPTS` consultas en caso de fallo. Un *back-off* exponencial se implementa (`std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)))`) para esperar antes de nuevos intentos, reduciendo la carga y aumentando la probabilidad de éxito en condiciones de red inestables.
- **Tratamiento de Desconexión Robusto:**
   - **Transición de Estado Elegante:** En `server_manager.cpp`, el estado de conexión (`connection_status`) no se cambia inmediatamente tras un único fallo de consulta. Solo si no se recibe respuesta durante 15 segundos consecutivos (`now - last_successful_query > std::chrono::seconds(15)`), el estado se actualiza a `false`. Esto evita el "parpadeo" de la presencia en Discord debido a pequeñas pérdidas de paquetes.
      ```cpp
      // server_manager.cpp (lógica de desconexión)
      else { // Si la consulta falló
          if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
              connection_status = false;
              display_image_url = Constants::DEFAULT_IMAGE;
              display_server_data = {};
              current_display_social = {};
          }
      }
      ```
   - **Fallback Visual:** Al detectar una desconexión, la imagen de la presencia en Discord regresa a `Constants::DEFAULT_IMAGE`, y los datos del servidor/sociales se limpian, proporcionando un feedback claro al usuario de que no está más conectado.
- **Tratamiento de Entradas Inválidas:**
   - **`command_line_parser.cpp`:** Al convertir el argumento de puerto de string a entero (`std::stoi`), se utiliza un bloque `try-catch` para manejar `std::invalid_argument` (no es un número) o `std::out_of_range` (número demasiado grande/pequeño). Si ocurre un error, el puerto predeterminado se mantiene o el parseo falla de forma controlada, previniendo cuelgues.
- **Resiliencia en la Obtención de Datos de la API:**
   - **Fallos WinHTTP:** Todas las operaciones de la API WinHTTP en `url_manager.cpp` se verifican para handles `null` y retornos de `false` en cada etapa (abrir sesión, conectar, abrir solicitud, enviar/recibir, leer datos), garantizando que fallos parciales sean capturados.
   - **Códigos de Estado HTTP:** Tras una solicitud HTTP, el `url_manager.cpp` verifica el `HTTP Status Code`. Solo un código `200 OK` se acepta como éxito, descartando respuestas de error del servidor o del gateway.
   - **Parseo JSON Seguro:** `url_manager.cpp` envuelve el parseo JSON (`nlohmann::json::parse`) en un bloque `try-catch(const nlohmann::json::exception&)`. Esto impide que JSONs malformados o incompletos provenientes de la API causen un crash, retornando strings vacías o la imagen predeterminada.
- **Mecanismos de Actualización Seguros:**
   - **`asi_update.hpp`:** El proceso de verificación de actualización en `Check_For_Update` está encapsulado en un bloque `try-catch(const std::exception&)`. Esto garantiza que, incluso si GitHub está offline, la red está inestable, o la respuesta JSON es inválida, el **ASI** no se cuelgue y el juego pueda continuar cargándose, ignorando la verificación de actualización de forma segura.
   - **Gestión de Handles WinHTTP:** La liberación de handles `HINTERNET` en `asi_update.hpp` y `url_manager.cpp` está cuidadosamente planeada para ejecutarse en todos los caminos de código (éxito y fallo), previniendo fugas de recursos.

### Sistema de Procesamiento de Línea de Comando

El **SA-MP Rich Presence** extrae información crucial para su operación (IP del servidor, puerto y nombre del jugador) directamente de la línea de comando del juego Grand Theft Auto: San Andreas. Este método garantiza que el **ASI** obtenga los datos más precisos y relevantes tan pronto como el juego se inicializa o se conecta a un servidor.

#### Parser de Línea de Comando (`command_line_parser.cpp`)

La clase `Command_Line_Parser` es responsable de analizar la string de comando completa del proceso, identificar y extraer los parámetros específicos usados por SA-MP.

- **`Parse()`**: El punto de entrada para el análisis de la línea de comando.
   ```cpp
   // command_line_parser.cpp (trecho clave de Parse)
   bool Command_Line_Parser::Parse(const std::wstring_view command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       server_ip = Constants::DEFAULT_SERVER_IP; // Valores predeterminados
       server_port = Constants::DEFAULT_SERVER_PORT;
   
       if (const auto ip_param = Parse_Parameter(command_line, L"-h"); !ip_param.empty())
           server_ip = Utils::Convert_Wide_To_Utf8_String(ip_param); // Extrae y convierte IP
   
       if (const auto port_param = Parse_Parameter(command_line, L"-p"); !port_param.empty()) {
           try {
               server_port = std::stoi(std::wstring(port_param)); // Extrae y convierte Puerto (con manejo de errores)
           }
           catch (const std::invalid_argument&) {}
           catch (const std::out_of_range&) {}
       }
   
       if (const auto name_param = Parse_Parameter(command_line, L"-n"); !name_param.empty())
           player_name = Utils::Convert_Wide_To_Utf8_String(name_param); // Extrae y convierte Nombre
   
       return !server_ip.empty() && server_port > 0 && !player_name.empty(); // Valida si los datos esenciales están presentes
   }
   ```
   Recibe la línea de comando (`command_line`) como `std::wstring_view` para eficiencia. Utiliza `Parse_Parameter` para encontrar y extraer los valores asociados a `-h` (host/IP), `-p` (puerto) y `-n` (nombre del jugador). Los valores extraídos (en `std::wstring_view`) se convierten a `std::string` (UTF-8) usando `Utils::Convert_Wide_To_Utf8_String`. Para el puerto, un bloque `try-catch` envuelve `std::stoi` para gestionar posibles errores de conversión de forma segura. La función retorna `true` si todos los parámetros cruciales (IP, puerto válido y nombre del jugador) se obtienen.
- **`Parse_Parameter()`**: La función auxiliar para la extracción de un único parámetro.
   ```cpp
   // command_line_parser.cpp (trecho clave de Parse_Parameter)
   std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring_view command_string, const std::wstring_view parameter) {
       if (const size_t position = command_string.find(parameter); position != std::wstring_view::npos) {
           size_t value_start = position + parameter.length();
           value_start = command_string.find_first_not_of(L" \t", value_start); // Salta espacios tras el parámetro

           if (value_start == std::wstring_view::npos)
               return L""; // Parámetro encontrado pero sin valor
   
           const size_t value_end = command_string.find(L' ', value_start); // Encuentra el próximo espacio (fin del valor)
           
           return std::wstring(command_string.substr(value_start, value_end - value_start)); // Retorna la substring del valor
       }

       return L""; // Parámetro no encontrado
   }
   ```
   Localiza la substring del `parameter` (`-h`, `-p`, `-n`) en la `command_string`. Calcula la posición inicial del valor, ignorando espacios/tabularizaciones. Identifica la posición final del valor (próximo espacio) y retorna la substring que corresponde al valor del parámetro.

### Protocolo de Comunicación SA-MP

El **ASI** interactúa directamente con servidores SA-MP usando el protocolo de consulta **UDP** para extraer información vital en tiempo real. Esta comunicación está implementada para ser eficiente y resistente a fallos de red.

#### Implementación del Protocolo

La clase `Server_Query` es la columna vertebral de esta implementación, gestionando el envío de paquetes y la interpretación de las respuestas.

- **Estructura del Paquete de Consulta SA-MP (`'i'`)**: El **ASI** construye un paquete **UDP** de 11 bytes para la consulta de información:
   - `BYTE 0-3`: Firma "SAMP" (S A M P).
   - `BYTE 4-9`: Secuencia de 6 bytes arbitrarios (generalmente dirección de IP de origen de la solicitud para que el servidor reconozca al cliente).
   - `BYTE 10`: Identificador de la consulta 'i' (ASCII 105), indicando que el **ASI** desea información general del servidor (hostname, jugadores, etc.).
      ```cpp
      // server_query.cpp (montaje del paquete)
      void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
          memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
          packet = 'i'; // Consulta de información (Information)
      }
      ```
- **Estructura de la Respuesta del Servidor**: Cuando un servidor SA-MP responde a una consulta 'i', envía un paquete **UDP** que contiene una secuencia de datos estructurados, que el **ASI** necesita parsear:
   - **Encabezado de la Respuesta:** Repetición de la firma "SAMP" y de la secuencia de 6 bytes del paquete de solicitud. El **ASI** simplemente salta estos `Constants::QUERY_PACKET_SIZE` bytes iniciales.
   - **Passworded (`bool`):** Un byte que indica si el servidor está protegido por contraseña. Leído, pero no usado.
   - **Players (`uint16_t`):** El número de jugadores actualmente conectados al servidor.
   - **Max_Players (`uint16_t`):** El número máximo de slots de jugadores que el servidor soporta.
   - **Hostname (string prefijada por `uint32_t`):** El nombre amigable del servidor. El paquete incluye un `uint32_t` para indicar la longitud de la string de hostname, seguido por los bytes de la string real.
   - **Otros Campos:** El protocolo SAMP continúa con "gamemode" y "language", también prefijados por tamaño. El **ASI** lee y salta estos campos para enfocarse en los datos esenciales de `Players`, `Max_Players`, y `Hostname`.

   La lectura de estos campos se hace con las funciones auxiliares `Read_From_Span` y `Read_String_From_Span`, que garantizan que el **ASI** no lea bytes fuera del límite del buffer y maneje correctamente la lectura de tipos de datos de longitud fija y variable (strings).
   ```cpp
   // server_query.cpp (parseo de la respuesta)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       // ... (Verificación de tamaño y subspan para los datos) ...
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Lee el booleano 'passworded'
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false; // Lee 'Players'

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false; // Lee 'Max_Players'

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false; // Lee 'Hostname'
   
       // Campos 'Gamemode' y 'Language' se saltan implícitamente
       // por la subsiguiente llamada de Read_String_From_Span
       // para mover el span más allá de sus datos en el buffer.
       uint32_t length_placeholder; // Variable temporal para contener el tamaño.

       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Lee tamaño del gamemode

       if (data_span.size() < length_placeholder)
           return false; // Verifica límites

       data_span = data_span.subspan(length_placeholder); // Salta datos del gamemode
   
       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Lee tamaño del language

       if (data_span.size() < length_placeholder)
           return false; // Verifica límites

       data_span = data_span.subspan(length_placeholder); // Salta datos del language
   
       return true;
   }
   ```
   En el ejemplo anterior, la lógica `data_span = data_span.subspan(length_placeholder);` es una forma eficiente de "saltar" el número de bytes leídos por una string cuyo contenido no es necesario para el Rich Presence.

### Beneficios del SA-MP Rich Presence

El **SA-MP Rich Presence** mejora significativamente la experiencia tanto para jugadores como para administradores de servidores, ofreciendo ventajas notables:

1. **Para Jugadores:**
   - **Visibilidad Sin Esfuerzo:** Comparte automáticamente tu estado de juego en Discord con amigos, mostrando exactamente dónde estás jugando.
   - **Información Rica:** Ten acceso inmediato a los detalles del servidor (nombre, conteo de jugadores, IP, logo personalizado) directamente en Discord, eliminando la necesidad de verificar esta información en otros lugares.
   - **Acceso Directo a la Comunidad:** Descubre y accede rápidamente a las redes sociales del servidor a través de los íconos rotativos en la presencia de Discord, facilitando la entrada a comunidades vibrantes.
   - **Conexión Rápida con Amigos:** Invita o únete al mismo servidor que tus amigos con un clic, gracias a la funcionalidad del botón "Join".
   - **Experiencia Siempre Activa:** El sistema de actualización automática garantiza que siempre utilices la versión más optimizada y funcional del **ASI**.
2. **Para Servidores:**
   - **Marketing Viral Natural:** La presencia en Discord de tus jugadores actúa como un cartel digital, promocionando tu servidor para una audiencia orgánica (los amigos de los jugadores) 24 horas al día.
   - **Identidad Visual Fuerte:** Un logo personalizado y la rotación de enlaces sociales permiten que tu servidor se destaque y proyecte una imagen profesional y moderna en el entorno de Discord.
   - **Compromiso Aumentado:** Facilita el camino para que nuevos y antiguos jugadores se conecten con tus plataformas sociales, fortaleciendo tu comunidad y compromiso fuera del juego.
   - **Reclutamiento Facilitado:** El recurso "Join" agiliza el proceso para nuevos jugadores, eliminando barreras e incentivando la experimentación.
   - **Datos Consistentes:** A través de la integración con la **AlderGrounds Integration API**, la visualización de información es unificada y actualizada centralmente, garantizando que la marca y los contactos de tu servidor estén siempre correctos.

## Licencia

Este ASI está protegido bajo la Licencia Apache 2.0, que permite:

- ✔️ Uso comercial y privado
- ✔️ Modificación del código fuente
- ✔️ Distribución del código
- ✔️ Concesión de patentes

### Condiciones:

- Mantener el aviso de derechos de autor
- Documentar cambios significativos
- Incluir copia de la licencia Apache 2.0

Para más detalles sobre la licencia: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Todos los derechos reservados**