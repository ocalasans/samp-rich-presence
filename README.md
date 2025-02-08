# SA-MP Rich Presence

O SA-MP Rich Presence é um ASI para SA-MP (San Andreas Multiplayer) que atualiza automaticamente seu status do Discord com informações detalhadas do servidor. O ASI é injetado no jogo quando você se conecta a um servidor SA-MP, exibindo informações do servidor.

## Idiomas

- Deutsch: [README](translations/Deutsch/README.md)
- English: [README](translations/English/README.md)
- Español: [README](translations/Espanol/README.md)
- Français: [README](translations/Francais/README.md)
- Italiano: [README](translations/Italiano/README.md)
- Polski: [README](translations/Polski/README.md)
- Русский: [README](translations/Русский/README.md)
- Svenska: [README](translations/Svenska/README.md)
- Türkçe: [README](translations/Turkce/README.md)

## Índice

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [O que é um ASI?](#o-que-é-um-asi)
  - [Funcionalidades](#funcionalidades)
    - [Discord Rich Presence](#discord-rich-presence)
  - [Requisitos](#requisitos)
  - [Instalação](#instalação)
  - [Arquitetura Técnica Detalhada](#arquitetura-técnica-detalhada)
    - [Sistema Principal (main.cpp)](#sistema-principal-maincpp)
    - [Gerenciador do Discord (discord\_manager.cpp)](#gerenciador-do-discord-discord_managercpp)
    - [Gerenciador de Servidor (server\_manager.cpp)](#gerenciador-de-servidor-server_managercpp)
    - [Sistema de Rede (network\_manager.cpp)](#sistema-de-rede-network_managercpp)
    - [Consulta ao Servidor (server\_query.cpp)](#consulta-ao-servidor-server_querycpp)
  - [Integração com a SPC](#integração-com-a-spc)
    - [O que é o SPC Integration?](#o-que-é-o-spc-integration)
    - [Como Funciona](#como-funciona)
    - [Gerenciador de URL (url\_manager.cpp)](#gerenciador-de-url-url_managercpp)
  - [Para Desenvolvedores de Servidor](#para-desenvolvedores-de-servidor)
  - [Estrutura do Código](#estrutura-do-código)
    - [Constantes Globais (constants.h)](#constantes-globais-constantsh)
    - [Estruturas de Dados (server\_types.h)](#estruturas-de-dados-server_typesh)
  - [Tratamento de Erros](#tratamento-de-erros)
  - [Sistema de Processamento de Linha de Comando](#sistema-de-processamento-de-linha-de-comando)
    - [Parser de Linha de Comando (command\_line\_parser.cpp)](#parser-de-linha-de-comando-command_line_parsercpp)
  - [Protocolo de Comunicação SA-MP](#protocolo-de-comunicação-sa-mp)
    - [Implementação do Protocolo](#implementação-do-protocolo)
  - [Benefícios do SA-MP Rich Presence](#benefícios-do-sa-mp-rich-presence)
  - [Notas Técnicas Adicionais](#notas-técnicas-adicionais)

## O que é um ASI?

ASI é uma biblioteca dinâmica (.dll) renomeada com a extensão .asi que é automaticamente carregada por um loader ASI quando o GTA San Andreas é iniciado. Os plugins ASI permitem modificar ou adicionar funcionalidades ao jogo sem alterar os arquivos originais, sendo uma das formas mais populares de modding para o GTA San Andreas e outros jogos da série GTA. Com um ASI loader instalado, você pode facilmente instalar ou remover modificações simplesmente adicionando ou removendo arquivos .asi da pasta do jogo.

## Funcionalidades

### Discord Rich Presence

O Discord Rich Presence é uma funcionalidade que permite que aplicativos mostrem informações detalhadas sobre o que o usuário está fazendo diretamente no perfil do Discord. No caso do SA-MP Rich Presence, as seguintes informações são exibidas:
- Nome do servidor (Hostname).
- Nome do jogador.
- Número atual de jogadores e máximo de jogadores.
- IP e porta do servidor.
- Imagem personalizada do servidor (requer que o servidor tenha o plugin [SPC Integration](https://github.com/spc-samp/spc-integration)).
- Tempo de jogo.
- Status da conexão.

## Requisitos

- Cliente SA-MP (se não tiver: [clients-samp](https://github.com/spc-samp/clients-samp)).
- Aplicativo Discord Desktop.
- Sistema Operacional Windows.
- Visual C++ Runtime.
- ASI Loader instalado no GTA San Andreas.

## Instalação

1. Baixe a versão mais recente do ASI compilado em [releases](https://github.com/ocalasans/samp-rich-presence/releases).
2. Certifique-se de ter um ASI Loader instalado no seu GTA San Andreas.
3. Copie o arquivo .asi baixado para a pasta do seu GTA San Andreas.
4. Inicie o jogo com o SA-MP.
5. O ASI será automaticamente inicializado quando você entrar em um servidor.

## Arquitetura Técnica Detalhada

### Sistema Principal (main.cpp)

O arquivo main.cpp é o ponto de entrada do ASI e responsável por:
1. Inicialização do sistema:
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

2. Gerenciamento da thread de atualização:
   ```cpp
   DWORD WINAPI Update_Thread(LPVOID) {
       // Inicializa WSA para operações de rede
       WSAData wsa_data;
       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
       
       // Processa parâmetros de linha de comando
       std::string server_ip, player_name;
       int server_port;
       
       // Inicializa gerenciadores
       Global_Server_Manager = std::make_unique<Server_Manager>(server_ip, server_port, player_name);
       Global_Discord_Manager = std::make_unique<Discord_Manager>();
       
       // Loop principal de atualização
       while (true) {
           Global_Server_Manager->Update();
           Global_Discord_Manager->Update_Presence(...);
           Sleep(Constants::PRESENCE_UPDATE_INTERVAL);
       }
   }
   ```

### Gerenciador do Discord (discord_manager.cpp)

O Discord_Manager é responsável por toda a integração com o Discord Rich Presence:
1. Inicialização do Discord RPC:
   ```cpp
   void Discord_Manager::Initialize() noexcept {
       Sleep(5000);  // Aguarda inicialização do Discord
       
       DiscordEventHandlers discord_handlers{};
       Discord_Initialize("DISCORD_APP_ID", &discord_handlers, 1, NULL); // "DISCORD_APP_ID > Application ID"
       
       start_timestamp = time(nullptr);  // Marca o início da sessão
   }
   ```

2. Atualização da presença:
   ```cpp
   void Discord_Manager::Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept {
       DiscordRichPresence discord_presence{};
       
       // Configura informações básicas
       discord_presence.state = player_name.data();
       discord_presence.details = server_info.Hostname.c_str();
       discord_presence.largeImageKey = current_image.data();
       
       // Adiciona informações do servidor
       discord_presence.largeImageText = server_info.Server_Address.c_str();
       discord_presence.startTimestamp = start_timestamp;
       discord_presence.partySize = server_info.Players;
       discord_presence.partyMax = server_info.Max_Players;
       
       Discord_UpdatePresence(&discord_presence);
   }
   ```

### Gerenciador de Servidor (server_manager.cpp)

O Server_Manager coordena todas as operações relacionadas ao servidor:
1. Gerenciamento de estado:
   ```cpp
   Server_Manager::Server_Manager(const std::string& ip, int port, const std::string& name)
       : connection_status(false)
       , server_ip(ip)
       , server_port(port)
       , player_name(name)
       , current_image_url(Constants::DEFAULT_IMAGE)
   {}
   ```

2. Atualização de informações:
   ```cpp
   bool Server_Manager::Update() {
       bool query_success = server_query.Query(server_data);
       
       if (query_success) {
           connection_status = true;
           server_data.Server_Address = Get_Server_Address();
           
           // Tenta obter imagem personalizada do servidor
           std::string new_image_url = url_manager.Get_Image_URL(server_data.Server_Address);

           if (!new_image_url.empty())
               current_image_url = new_image_url;
       }
       // ...
   }
   ```

### Sistema de Rede (network_manager.cpp)

O Network_Manager implementa toda a comunicação de rede:
1. Inicialização do socket:
   ```cpp
   bool Network_Manager::Initialize(std::string_view ip, int port) noexcept {
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       
       // Configura timeout
       timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
       
       // Configura endereço do servidor
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(port);
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr);
       
       return true;
   }
   ```

### Consulta ao Servidor (server_query.cpp)

O Server_Query implementa o protocolo de consulta do SA-MP:
1. Montagem do pacote de consulta:
   ```cpp
   bool Server_Query::Assemble_Query_Packet(char* packet) noexcept {
       memcpy(packet, QUERY_SIGNATURE, 4);  // "SAMP"
       packet[10] = 'i';  // Information query

       return true;
   }
   ```

2. Processamento da resposta:
   ```cpp
   bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
       // Extrai informações como:
       // - Número de jogadores
       // - Máximo de jogadores
       // - Hostname
   }
   ```

## Integração com a SPC

### O que é o SPC Integration?

[SPC Integration](https://github.com/spc-samp/spc-integration) é um plugin desenvolvido para **SA-MP** (San Andreas Multiplayer) e **open.mp** (Open Multiplayer) que atua como uma ponte entre servidores e o ecossistema da **SPC**. O plugin coleta informações cruciais do servidor, incluindo:
- IP e porta.
- URL do site do servidor.
- URL da imagem personalizada.
- Informações de configuração.

Essas informações são enviadas e armazenadas de forma segura no armazenador de dados da **SPC (SA-MP Programming Community)**, permitindo uma integração com várias aplicações da **SPC**, incluindo o Rich Presence.

### Como Funciona

1. O servidor utiliza o plugin [SPC Integration](https://github.com/spc-samp/spc-integration) para registrar sua imagem personalizada.
2. A imagem é armazenada no armazenamento de dados da **SPC** dentro do arquivo JSON do servidor.
3. Quando um jogador conecta no servidor:
    - O URL_Manager do ASI tenta buscar o arquivo JSON do servidor (formato: `ip-port.json`).
    - Se encontrado, extrai a URL da imagem do parâmetro `spc_integration_image`.
    - A imagem é então exibida no Discord Rich Presence do jogador.

### Gerenciador de URL (url_manager.cpp)

O URL_Manager é responsável por toda a comunicação com o armazenamento de dados da **SPC**:
1. Busca da imagem do servidor:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       std::string formatted_address = server_address;
       // Converte ":" para "-" no endereço
       size_t colon_pos = formatted_address.find(':');

       if (colon_pos != std::string::npos)
           formatted_address.replace(colon_pos, 1, "-");
       
       // Busca JSON do servidor
       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;
       
       return image_url;
   }
   ```

2. Processamento do JSON:
   ```cpp
   std::string URL_Manager::Parse_JSON(const std::string& json_content) {
       const std::string key = "\"spc_integration_image\":";
       size_t key_pos = json_content.find(key);
       
       // Extrai URL da imagem do JSON
       // ...
       
       return image_url;
   }
   ```

## Para Desenvolvedores de Servidor

Se você é um desenvolvedor de servidor SA-MP, recomendamos fortemente a instalação do plugin [SPC Integration](https://github.com/spc-samp/spc-integration) pelos seguintes motivos:
1. Visibilidade:
    - A imagem personalizada do seu servidor será exibida no Discord de todos os jogadores que usam este ASI.
    - Aumenta o reconhecimento da marca do seu servidor.
    - Proporciona uma apresentação mais profissional.

2. Benefícios:
    - Maior engajamento dos jogadores.
    - Diferenciação visual no Discord.
    - Integração automática com o Rich Presence.

3. Como implementar:
   - Leia o repositório do plugin [SPC Integration](https://github.com/spc-samp/spc-integration) para saber como implementar.

## Estrutura do Código

O projeto é organizado em vários componentes:
```
src/
├── discord/               # Biblioteca Discord RPC
├── command_line_parser.*  # Processamento de argumentos
├── constants.h            # Constantes globais
├── discord_manager.*      # Integração com Discord
├── main.cpp               # Ponto de entrada
├── network_manager.*      # Operações de rede
├── server_manager.*       # Gerenciamento do servidor
├── server_query.*         # Protocolo SA-MP
├── server_types.h         # Estruturas de dados
└── url_manager.*          # Integração com SPC
```

### Constantes Globais (constants.h)

O arquivo define várias constantes importantes:
```cpp
namespace Constants {
    // Valores padrão
    inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
    inline constexpr int DEFAULT_SERVER_PORT = 7777;
    
    // Configurações de rede
    inline constexpr int QUERY_TIMEOUT = 1000;
    inline constexpr int QUERY_PACKET_SIZE = 11;
    inline constexpr int QUERY_BUFFER_SIZE = 512;
    
    // Configurações de retry
    inline constexpr int MAX_RETRY_ATTEMPTS = 3;
    
    // Intervalos
    inline constexpr int PRESENCE_UPDATE_INTERVAL = 5000;
}
```

### Estruturas de Dados (server_types.h)

Define as estruturas principais:
```cpp
struct Server_Information {
    uint16_t Players{ 0 };           // Jogadores online
    uint16_t Max_Players{ 0 };       // Máximo de jogadores
    std::string Hostname;            // Nome do servidor
    std::string Server_Image;        // URL da imagem
    std::string Server_Address;      // Endereço do servidor
};
```

## Tratamento de Erros

O sistema implementa um robusto sistema de tratamento de erros:
1. Timeout de rede:
   ```cpp
   timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
   setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
   ```

2. Sistema de retry:
   ```cpp
   bool Server_Query::Try_Query(Server_Information& server_data, int retry_count) noexcept {
       for (int attempt = 0; attempt <= retry_count; attempt++) {
           if (network_manager.Send_Query(...))
               return true;
           
           // Aguarda antes de tentar novamente
           std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
       }

       return false;
   }
   ```

3. Fallback para imagem padrão:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       // Se algo der errado, retorna a imagem padrão
       if (!session_handle)
           return Constants::DEFAULT_IMAGE;

       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;

       return image_url;
   }
   ```

4. Monitoramento de estado de conexão:
   ```cpp
   bool Server_Manager::Update() {
       auto current_time = std::chrono::steady_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_successful_query);
       
       // Se ficar mais de 15 segundos sem resposta, considera desconectado
       if (duration.count() > 15) {
           connection_status = false;
           current_image_url = Constants::DEFAULT_IMAGE;
       }
   }
   ```

## Sistema de Processamento de Linha de Comando

O ASI implementa um sistema flexível para processar argumentos de linha de comando:

### Parser de Linha de Comando (command_line_parser.cpp)

1. Processamento principal:
   ```cpp
   bool Command_Line_Parser::Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       // Define valores padrão
       server_ip = Constants::DEFAULT_SERVER_IP;
       server_port = Constants::DEFAULT_SERVER_PORT;

       // Processa cada parâmetro
       std::wstring ip_parameter = Parse_Parameter(command_string, L"-h");
       std::wstring port_parameter = Parse_Parameter(command_string, L"-p");
       std::wstring name_parameter = Parse_Parameter(command_string, L"-n");

       // Converte e valida os valores
       if (!ip_parameter.empty())
           server_ip = Convert_To_String(ip_parameter);

       if (!port_parameter.empty())
           server_port = std::stoi(port_parameter);

       if (!name_parameter.empty())
           player_name = Convert_To_String(name_parameter);

       // Verifica se todos os parâmetros necessários estão presentes
       return !server_ip.empty() && server_port > 0 && !player_name.empty();
   }
   ```

2. Extração de parâmetros:
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

## Protocolo de Comunicação SA-MP

O ASI implementa o protocolo de consulta do SA-MP para obter informações do servidor:
1. Estrutura do pacote de consulta:
    - 4 bytes: Assinatura "SAMP"
    - 7 bytes: Dados adicionais
    - Último byte: 'i' (indica consulta de informações)

2. Estrutura da resposta:
    - Cabeçalho do pacote
    - Players (uint16_t)
    - Max_Players (uint16_t)
    - Hostname (string)

### Implementação do Protocolo

```cpp
bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
    char* current_pos = response_buffer + Constants::QUERY_PACKET_SIZE;
    const char* buffer_end = response_buffer + received_bytes;

    // Pular "password"
    current_pos += sizeof(bool);
    
    // Lê dados fixos
    memcpy(&server_data.Players, current_pos, sizeof(server_data.Players));
    current_pos += sizeof(server_data.Players);
    
    memcpy(&server_data.Max_Players, current_pos, sizeof(server_data.Max_Players));
    current_pos += sizeof(server_data.Max_Players);

    // Lê Hostname e pula "gamemode" e "language"
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
    
    // Pular "gamemode" e "language"
    // ...

    return true;
}
```

## Benefícios do SA-MP Rich Presence

1. Para Jogadores:
    - Visualização rápida do servidor atual.
    - Informações detalhadas sobre o servidor.
    - Integração perfeita com o Discord.
    - Experiência de jogo mais social.

2. Para Servidores:
    - Maior visibilidade através do Discord.
    - Marketing orgânico através dos jogadores.
    - Identidade visual personalizada (com o plugin [SPC Integration](https://github.com/spc-samp/spc-integration)).
    - Estatísticas em tempo real.

## Notas Técnicas Adicionais

1. Thread Safety:
    - O ASI utiliza um único thread para atualizações.
    - Gerenciadores são thread-safe por design.
    - Recursos são propriamente sincronizados.

2. Uso de Memória:
    - Alocação mínima de memória.
    - Buffers pré-alocados para queries.
    - Gerenciamento automático de recursos (RAII).

3. Performance:
    - Queries otimizadas com timeout.
    - Sistema de retry inteligente.
    - Intervalo de atualização configurável.

4. Compatibilidade:
    - Suporte a Unicode.
    - Compatível com Windows moderno.
    - Suporte a IPv4.
