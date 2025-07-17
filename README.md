# SA-MP Rich Presence

O **SA-MP Rich Presence** é um **ASI** para **SA-MP (San Andreas Multiplayer)** que atualiza automaticamente seu status do Discord com informações detalhadas do servidor. O **ASI** é injetado no jogo quando você se conecta a um servidor SA-MP, exibindo informações do servidor.

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
  - [Funcionalidades](#funcionalidades)
    - [Discord Rich Presence](#discord-rich-presence)
    - [Sistema de Atualização Automática](#sistema-de-atualização-automática)
  - [Requisitos](#requisitos)
  - [Instalação](#instalação)
  - [Integração com o SPC Integration API](#integração-com-o-spc-integration-api)
    - [Como a Informação é Obtida e Utilizada:](#como-a-informação-é-obtida-e-utilizada)
  - [Para Desenvolvedores de Servidor](#para-desenvolvedores-de-servidor)
    - [Como Implementar o SPC Integration no Seu Servidor:](#como-implementar-o-spc-integration-no-seu-servidor)
  - [Arquitetura Técnica Detalhada](#arquitetura-técnica-detalhada)
      - [Sistema Principal (`main.cpp`)](#sistema-principal-maincpp)
      - [Sistema de Atualização (`asi_update.hpp`)](#sistema-de-atualização-asi_updatehpp)
      - [Gerenciador do Discord (`discord_manager.cpp`)](#gerenciador-do-discord-discord_managercpp)
      - [Gerenciador de Servidor (`server_manager.cpp`)](#gerenciador-de-servidor-server_managercpp)
      - [Sistema de Rede (`samp_network.cpp`)](#sistema-de-rede-samp_networkcpp)
      - [Consulta ao Servidor (`server_query.cpp`)](#consulta-ao-servidor-server_querycpp)
      - [Gerenciador de URL (`url_manager.cpp`)](#gerenciador-de-url-url_managercpp)
    - [Estrutura do Código](#estrutura-do-código)
      - [Constantes Globais (`constants.hpp`)](#constantes-globais-constantshpp)
      - [Estruturas de Dados (`server_types.hpp`)](#estruturas-de-dados-server_typeshpp)
      - [Ofuscação de Segredos (`secrets.hpp`)](#ofuscação-de-segredos-secretshpp)
      - [Utilitários Gerais (`utils.hpp`)](#utilitários-gerais-utilshpp)
    - [Tratamento de Erros e Resiliência](#tratamento-de-erros-e-resiliência)
    - [Sistema de Processamento de Linha de Comando](#sistema-de-processamento-de-linha-de-comando)
      - [Parser de Linha de Comando (`command_line_parser.cpp`)](#parser-de-linha-de-comando-command_line_parsercpp)
    - [Protocolo de Comunicação SA-MP](#protocolo-de-comunicação-sa-mp)
      - [Implementação do Protocolo](#implementação-do-protocolo)
    - [Benefícios do SA-MP Rich Presence](#benefícios-do-sa-mp-rich-presence)
  - [Licença](#licença)
    - [Condições:](#condições)

## Funcionalidades

### Discord Rich Presence

O **Discord Rich Presence** é uma funcionalidade que permite que aplicativos mostrem informações detalhadas sobre o que o usuário está fazendo diretamente no perfil do Discord. No caso do **SA-MP Rich Presence**, as seguintes informações são exibidas:

- **Nome do servidor (Hostname):** O nome principal do servidor.
- **Nome do jogador:** Seu nickname atual no jogo.
- **Contagem de jogadores:** Número atual de jogadores online e o máximo permitido.
- **Endereço do servidor:** IP e porta do servidor para fácil identificação.
- **Imagem personalizada do servidor:** Um logo único do servidor, se disponível.
- **Ícone social rotativo:** Pequenos ícones que representam links para redes sociais do servidor (website, Discord, YouTube, Instagram, Facebook, TikTok), alternando automaticamente.
- **Tempo de jogo:** Quanto tempo você está conectado ao servidor atual.
- **Status da conexão:** Indica se você está online em um servidor ou no estado "Idle" (ocioso).
- **Botão "Join" (Entrar):** Permite que seus amigos entrem diretamente no mesmo servidor que você está jogando.

### Sistema de Atualização Automática

O **ASI** integra um sistema de verificação de atualização. Ao iniciar o jogo, ele verifica se há novas versões disponíveis no repositório GitHub oficial do projeto. Se uma atualização for detectada, uma notificação amigável é exibida ao usuário, oferecendo opções para:

1. Abrir o navegador diretamente na página de releases para download.
2. Continuar sem atualizar, com a opção de desabilitar o **ASI** para a sessão atual.

Essa funcionalidade garante que os usuários sempre tenham acesso às últimas melhorias, correções de bugs e novas funcionalidades, promovendo uma experiência atualizada e sem interrupções.

## Requisitos

- Cliente SA-MP (caso não possua: [clients-samp](https://github.com/spc-samp/clients-samp)).
- Aplicativo Discord Desktop.
- Sistema Operacional Windows.
- Visual C++ Runtime.
- Um [ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) instalado no seu Grand Theft Auto: San Andreas.

## Instalação

1. Baixe a versão mais recente do **ASI** compilada diretamente da seção de [releases](https://github.com/ocalasans/samp-rich-presence/releases) no GitHub.
2. Após o download, localize o arquivo `.asi`.
3. Copie o arquivo `.asi` baixado para a pasta raiz do seu GTA San Andreas (onde se encontra o arquivo `gta_sa.exe`).
4. Inicie o jogo através do cliente SA-MP.
5. O **ASI** será carregado e inicializado automaticamente quando você se conectar a um servidor, atualizando seu status no Discord.

## Integração com o SPC Integration API

O **SA-MP Rich Presence** aprimora significativamente a exibição de informações no Discord através de sua integração com o **SPC Integration API**. Em vez de depender apenas de dados básicos de query, o **ASI** agora interage diretamente com essa API para obter informações visuais e sociais do servidor. Para entender mais sobre o **SPC Integration** em si, visite o repositório oficial: [spc-samp/spc-integration](https://github.com/spc-samp/spc-integration).

### Como a Informação é Obtida e Utilizada:

1. **Formatação do Endereço:** Quando o jogador se conecta a um servidor (IP e Porta), o **ASI** formata esse endereço (`IP:PORTA`) para um padrão amigável (`IP-PORTA`), preparando-o para a requisição da API.
2. **Requisição à API:** O **ASI** envia uma requisição `GET` para o endpoint do **SPC Integration API**, incluindo o IP e a porta formatados. Exemplo de como a URL de requisição é construída internamente:
   ```cpp
   // Trecho adaptado de url_manager.cpp
   auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
   std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
   path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   const std::string json_data = Request_API_Data(path);
   ```
3. **Processamento da Resposta JSON:** A API retorna uma resposta em formato JSON. O **ASI** utiliza a biblioteca [nlohmann/json](https://github.com/nlohmann/json) para parsear essa resposta e extrair os dados relevantes.
   ```json
   // Exemplo de Estrutura de Resposta do SPC Integration API
   {
       "success": true,
       "data": {
           "public": {
               "logo": "https://url.do.seu.logo/server_logo.png",
               "website": "https://seu-site.com",
               "discord": "https://discord.gg/seuservidor",
               "youtube": "https://youtube.com/seucanal"
               // ...outras redes sociais
           }
       }
   }
   ```
4. **Extração de Dados:**
   - **Logo do Servidor:** A URL da imagem do servidor (o `logo` dentro da seção `public`) é extraída e utilizada como a imagem principal (large image) no **Discord Rich Presence**. Isso garante uma identidade visual autêntica e personalizável para cada servidor.
   - **Links Sociais:** Uma lista predefinida de redes sociais (website, Discord, YouTube, Instagram, Facebook, TikTok) é verificada na resposta JSON. Para cada rede social encontrada e com um valor válido, o nome da rede e seu respectivo link são armazenados.
5. **Exibição no Discord:** O `Server_Manager` utiliza a lista de links sociais extraídos para implementar uma rotação dinâmica. A cada 30 segundos, um ícone diferente de uma das redes sociais do servidor é exibido como a "small image" (pequena imagem) na presença do Discord, juntamente com o link ou nome da plataforma, incentivando a exploração das comunidades do servidor.

## Para Desenvolvedores de Servidor

A integração do seu servidor com o [SPC Integration](https://github.com/spc-samp/spc-integration) traz uma série de benefícios diretos e indiretos que impulsionam a visibilidade e o engajamento da sua comunidade SA-MP. Se você é um desenvolvedor de servidor, considere as vantagens estratégicas:

1. **Potencialize Sua Marca:**
   - **Visibilidade Premium:** O logo personalizado do seu servidor não será apenas um texto, mas uma imagem vibrante e chamativa, exibida em destaque no perfil do Discord de todos os jogadores que utilizam este **ASI**. Esta é uma forma orgânica e constante de branding.
   - **Presença Profissional:** Ao ter seu logo e redes sociais bem representadas, seu servidor projeta uma imagem mais estabelecida e confiável, atraindo mais interesse e potenciais novos jogadores.
2. **Expansão da Comunidade:**
   - **Multiplique os Canais de Acesso:** Com a rotação de ícones sociais, você pode divulgar diversas plataformas de sua comunidade – desde o website oficial e o Discord do servidor até suas páginas no YouTube, Instagram, Facebook ou TikTok. Cada ícone e link no **Discord Rich Presence** direciona diretamente os interessados para onde sua comunidade está ativa.
   - **Conectividade Instantânea:** A funcionalidade de "Join" via Discord permite que amigos de seus jogadores entrem no seu servidor SA-MP com apenas um clique, reduzindo barreiras de entrada e incentivando novos membros.
3. **Atualização Simplificada de Conteúdo:**
   - Ao utilizar o [SPC Integration](https://github.com/spc-samp/spc-integration), qualquer atualização no logo do seu servidor ou na lista de redes sociais configuradas no plugin [SPC Integration](https://github.com/spc-samp/spc-integration) **(no lado do servidor)** será refletida automaticamente para os jogadores que utilizam o **ASI**, sem que eles precisem atualizar o **ASI**. Isso garante que a informação esteja sempre correta e atualizada.

### Como Implementar o SPC Integration no Seu Servidor:

1. **Plugin SPC Integration:** Seu servidor precisará ter o plugin [SPC Integration](https://github.com/spc-samp/spc-integration) instalado e configurado corretamente. Este plugin é a ponte que envia as informações do seu servidor para uma lista de dados da **SPC**, que, consequentemente, é utilizada pelo **SPC Integration API** para disponibilizar informações públicas.
2. **Configuração:** Siga as instruções no repositório do plugin [SPC Integration](https://github.com/spc-samp/spc-integration) para configurar:
   - O parâmetro `logo` com a URL do logo do seu servidor.
   - Os parâmetros de redes sociais (`discord`, `website`, `youtube`, etc.) com os links válidos para suas plataformas.
3. **Atualização Automática:** Uma vez que as informações estejam configuradas no plugin do servidor, o **SA-MP Rich Presence** irá detectá-las e exibi-las automaticamente. Não é necessária nenhuma ação por parte do jogador além da instalação inicial do **ASI**.

Ao integrar seu servidor com o [SPC Integration](https://github.com/spc-samp/spc-integration), você não apenas melhora a experiência dos seus jogadores, mas também abre portas para um crescimento e engajamento significativos para sua comunidade.

## Arquitetura Técnica Detalhada

O **SA-MP Rich Presence** possui uma arquitetura modular bem definida, com componentes focados em tarefas específicas. A base de código está alinhada com padrões modernos do C++ (C++17 e C++20), utilizando `std::string_view`, `std::span` e semântica de movimentação para garantir alta performance, segurança e eficiência.

#### Sistema Principal (`main.cpp`)

O coração do **ASI** reside em `main.cpp`, que gerencia o ciclo de vida da aplicação, desde sua inicialização como uma DLL até o loop contínuo de atualização e seu desligamento gracioso.

- **`DllMain`**: A porta de entrada do **ASI** quando carregado pelo sistema operacional.
   ```cpp
   // DllMain (simplificado para foco na estrutura)
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
   Nesta função, ao ser anexada ao processo do jogo (`DLL_PROCESS_ATTACH`), ela impede chamadas de biblioteca desnecessárias (`DisableThreadLibraryCalls`) e **cria uma nova thread (`Main_Update_Thread`)** para executar a lógica do **ASI** de forma assíncrona, garantindo que o jogo não seja bloqueado. Durante o desligamento (`DLL_PROCESS_DETACH`), `Shutdown_Managers()` é invocado para liberar recursos.
- **`Main_Update_Thread`**: A alma do **ASI**, operando em sua própria thread.
   ```cpp
   // Main_Update_Thread (trecho chave)
   DWORD WINAPI Main_Update_Thread(LPVOID) {
       // 1. Verificação de Atualização
       if (Asi_Update::Check_For_Update())
           return 0; // Se usuário optou por desativar, finaliza.
   
       // 2. Inicialização da Rede (Winsock)
       WSAData wsa_data;

       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
   
       // 3. Inicializa Gerenciadores de Servidor e Discord
       Initialize_Managers();
   
       // 4. Loop Principal de Atualização
       while (is_running && v_server_manager && v_discord_manager) {
           v_server_manager->Update(); // Consulta servidor, API SPC etc.
           v_discord_manager->Update_Presence( // Atualiza o status do Discord
               v_server_manager->Get_Server_Info(),
               v_server_manager->Get_Display_Social_Link(),
               v_server_manager->Get_Player_Name(),
               v_server_manager->Get_Current_Image_URL(),
               v_server_manager->Is_Connected());
   
           Discord_RunCallbacks(); // Processa eventos RPC do Discord
           std::this_thread::sleep_for(Constants::MAIN_LOOP_INTERVAL);
       }
   
       // 5. Desligamento (se os managers existirem)
       if (v_discord_manager)
           v_discord_manager->Shutdown();

       WSACleanup(); // Libera Winsock

       return 0;
   }
   ```
   Esta função prioritiza a verificação de atualizações. Em seguida, inicializa a pilha de rede Winsock e instâncias dos gerenciadores de servidor e Discord. Um loop `while` persistente (controlado pela `std::atomic<bool> is_running` para desligamento seguro) coordena as chamadas para `Server_Manager::Update()` (coleta de dados) e `Discord_Manager::Update_Presence()` (envio para o Discord). `Discord_RunCallbacks()` garante que o Discord processe os eventos da Rich Presence. O loop é pausado periodicamente usando `std::this_thread::sleep_for` para otimização de recursos.

#### Sistema de Atualização (`asi_update.hpp`)

Este módulo vital adiciona inteligência ao **ASI**, garantindo que os usuários permaneçam atualizados.

- **`Check_For_Update()`**: A função principal de verificação.
   ```cpp
   // asi_update.hpp (trecho chave de Check_For_Update)
   inline bool Check_For_Update() {
       HINTERNET h_session = nullptr, h_connect = nullptr, h_request = nullptr;
       bool update_found_and_handled = false;
   
       try {
           h_session = WinHttpOpen(L"SA-MP Rich Presence Update/1.0", ...);
           // ... (requisição GET para Constants::UPDATE_API_PATH na API do GitHub) ...
           std::string response_body;
           // ... (leitura da resposta HTTP) ...
           nlohmann::json release_info = nlohmann::json::parse(response_body);
   
           std::string latest_tag = release_info["tag_name"].get<std::string>();
           // ... (normaliza e compara as versões usando sscanf_s/sscanf) ...
   
           if (latest_major > current_major || (latest_major == current_major && latest_minor > current_minor)) {
               update_found_and_handled = true;
               std::wstringstream message_stream;
               // ... (prepara a mensagem da MessageBox) ...
               int msgbox_result = MessageBoxW(NULL, message_stream.str().c_str(), L"SA-MP Rich Presence - Update Available", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
               
               if (msgbox_result == IDYES)
                   ShellExecuteW(NULL, L"open", Constants::UPDATE_RELEASES_URL, NULL, NULL, SW_SHOWNORMAL);
           }
       }
       catch (const std::exception&) { /* Tratamento de erro */ }
   
       // ... (fechar handles WinHttp) ...
       return update_found_and_handled;
   }
   ```
   Utilizando a **API WinHTTP** para requisições de rede, `Check_For_Update` realiza uma requisição `GET` ao endpoint `/releases/latest` da API do GitHub para o repositório do projeto. A resposta, em formato JSON, é parseada com a biblioteca `nlohmann/json`. A versão mais recente (`tag_name`) é comparada numericamente com a versão compilada do **ASI**. Se uma nova versão for detectada, uma caixa de diálogo (`MessageBoxW`) é exibida, perguntando ao usuário se ele deseja ir à página de downloads via `ShellExecuteW`. Todo o processo é encapsulado em um `try-catch` para garantir que falhas de rede ou parseamento não comprometam o início do jogo.

#### Gerenciador do Discord (`discord_manager.cpp`)

A classe `Discord_Manager` abstrai as interações com a biblioteca **Discord RPC**, gerenciando a inicialização da conexão e o envio de dados para o status de presença do usuário.

- **`Initialize()`**: Configura a comunicação com o Discord.
   ```cpp
   // discord_manager.cpp (trecho chave de Initialize)
   void Discord_Manager::Initialize() noexcept {
       DiscordEventHandlers handlers;
       memset(&handlers, 0, sizeof(handlers)); // Garante inicialização
       
       // App ID é desofuscado aqui
       auto app_id_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_Discord_App_ID());
       Discord_Initialize(app_id_accessor.Get(), &handlers, 1, nullptr);
   
       start_timestamp_ = time(nullptr); // Registra início da sessão
   }
   ```
   A chamada a `Discord_Initialize` é crucial, utilizando o `DISCORD_APP_ID` que é obtido de forma segura através da ofuscação de string em `secrets.hpp`. O `start_timestamp_` é definido aqui para calcular o tempo de jogo na presença do Discord.
- **`Update_Presence()`**: A função vital que atualiza a Rich Presence do Discord.
   ```cpp
   // discord_manager.cpp (trecho chave de Update_Presence)
   void Discord_Manager::Update_Presence(const Server_Information& server_info, const server_types::Social_Link& social_link, const std::string_view player_name, const std::string_view current_image, const bool is_connected) noexcept {
       DiscordRichPresence discord_presence;
       memset(&discord_presence, 0, sizeof(discord_presence));
   
       discord_presence.startTimestamp = start_timestamp_;
       discord_presence.largeImageKey = current_image.data(); // Logo do servidor
   
       if (is_connected) {
           discord_presence.details = server_info.Hostname.c_str();
           discord_presence.state = player_name.data();
           discord_presence.largeImageText = server_info.Server_Address.c_str(); // IP:Porta
           discord_presence.partySize = server_info.Players;
           discord_presence.partyMax = server_info.Max_Players;
           discord_presence.joinSecret = server_info.Server_Address.c_str(); // Habilita o botão "Join"
   
           // Gerencia o ícone social rotativo
           if (!social_link.first.empty()) {
               current_small_image_key_ = Constants::SOCIAL_ICON_BASE_URL;
               current_small_image_key_ += social_link.first; // Ex: "discord.png"
               current_small_image_key_ += ".png";
               discord_presence.smallImageKey = current_small_image_key_.c_str();
               discord_presence.smallImageText = social_link.second.c_str(); // Texto ao passar mouse (link/nome)
           }
       }
       else {
           discord_presence.details = "SA-MP"; // Estado "Idle"
           discord_presence.state = "Idle";
           discord_presence.largeImageText = "San Andreas Multiplayer";
           // smallImageKey e smallImageText permanecem vazios para estado idle
       }
   
       Discord_UpdatePresence(&discord_presence);
   }
   ```
   Preenche a estrutura `DiscordRichPresence` com base no estado da conexão. Se `is_connected` for verdadeiro, o hostname, contagem de jogadores, IP do servidor e o nome do jogador são exibidos. O `largeImageKey` define a imagem principal do servidor. Notavelmente, `joinSecret` é definido para permitir que amigos se conectem diretamente, e o `smallImageKey` (construído dinamicamente com base no `social_link` fornecido) exibe os ícones sociais rotativos. Em estado "Idle", a presença é simplificada para refletir a inatividade. Finalmente, `Discord_UpdatePresence` envia os dados ao Discord.

#### Gerenciador de Servidor (`server_manager.cpp`)

O `Server_Manager` é o orquestrador dos dados, gerenciando o estado de conexão, consultando o servidor e o **SPC Integration API**, e decidindo quais informações devem ser exibidas e quando.

- **`Update()`**: O ciclo de vida principal para a coleta de dados.
   ```cpp
   // server_manager.cpp (trecho chave de Update)
   void Server_Manager::Update() {
       const auto now = std::chrono::steady_clock::now();
   
       if (server_query.Query(live_server_data)) { // Tenta obter dados via query SAMP
           if (!connection_status) { // Se acabou de conectar/reconectar
               connection_status = true;
               Fetch_API_Data(); // Puxa logo e sociais da API
           }
           
           last_successful_query = now;
   
           // Atualiza dados a serem exibidos no Discord
           display_server_data.Hostname = live_server_data.Hostname;
           display_server_data.Players = live_server_data.Players;
           display_server_data.Max_Players = live_server_data.Max_Players;
           display_server_data.Server_Address = server_ip + ":" + std::to_string(server_port);
   
           if (now - last_api_update > Constants::IMAGE_UPDATE_INTERVAL)
               Fetch_API_Data(); // Reconsulta API após tempo definido
   
           if (now - last_social_rotation > Constants::SOCIAL_UPDATE_INTERVAL)
               Rotate_Social_Link(); // Rotaciona o ícone social
       }
       else { // Se a query falhou
           if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
               connection_status = false; // Desconectado após timeout
               display_image_url = Constants::DEFAULT_IMAGE;
               display_server_data = {}; // Limpa dados
               current_display_social = {}; // Limpa social
           }
       }
   }
   ```
   A função `Update` tenta realizar uma query ao servidor. Se bem-sucedida, atualiza os dados em `live_server_data` e `display_server_data`. Condicionalmente, ela chama `Fetch_API_Data()` para atualizar a imagem e os links sociais (se é uma nova conexão ou se o `IMAGE_UPDATE_INTERVAL` passou) e `Rotate_Social_Link()` para alternar os ícones sociais (`SOCIAL_UPDATE_INTERVAL`). Se as queries ao servidor falharem consistentemente por mais de 15 segundos, o status da conexão é considerado perdido, redefinindo as informações exibidas.
- **`Fetch_API_Data()`**: Responsável por obter os dados visuais e sociais.
   ```cpp
   // server_manager.cpp (trecho chave de Fetch_API_Data)
   void Server_Manager::Fetch_API_Data() {
       display_image_url = url_manager.Get_Image_URL_And_Populate_Socials(server_ip, server_port, live_server_data);
       last_api_update = std::chrono::steady_clock::now();
       current_social_index_ = 0; // Reseta índice após nova API fetch
       Rotate_Social_Link(); // Garante que um ícone social é exibido imediatamente
   }
   ```
   Essa função coordena com `URL_Manager` para puxar o logo e os links sociais da API, atualizando o `display_image_url` e populando os `Social_Links` dentro de `live_server_data`. Reseta o índice de rotação de sociais e chama `Rotate_Social_Link()` para garantir que o primeiro ícone esteja pronto para exibição.
- **`Rotate_Social_Link()`**: Lógica para alternar os ícones sociais.
   ```cpp
   // server_manager.cpp (trecho chave de Rotate_Social_Link)
   void Server_Manager::Rotate_Social_Link() {
       if (!live_server_data.Social_Links.empty()) {
           if (current_social_index_ >= live_server_data.Social_Links.size())
               current_social_index_ = 0; // Reinicia o ciclo
   
           current_display_social = live_server_data.Social_Links[current_social_index_];
           current_social_index_ = (current_social_index_ + 1) % live_server_data.Social_Links.size();
       }
       else
           current_display_social = {}; // Limpa se não houver sociais
       
       last_social_rotation = std::chrono::steady_clock::now();
   }
   ```
   Esta função simples seleciona o próximo `Social_Link` na lista de `live_server_data.Social_Links` de forma cíclica e armazena-o em `current_display_social` para que o `Discord_Manager` possa utilizá-lo.

#### Sistema de Rede (`samp_network.cpp`)

A classe `Samp_Network` é a implementação de baixo nível da comunicação **UDP**, responsável por abrir e gerenciar o socket para queries do SA-MP. Ela agora oferece construtores e operadores de movimentação para uma melhor gestão de recursos.

- **`Initialize()`**: Configura o socket para comunicação **UDP**.
   ```cpp
   // samp_network.cpp (trecho chave de Initialize)
   bool Samp_Network::Initialize(const std::string_view ip, const int port) noexcept {
       if (network_socket != INVALID_SOCKET)
           closesocket(network_socket); // Fecha socket existente
   
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       if (network_socket == INVALID_SOCKET)
           return false;
   
       const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
       setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
   
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(static_cast<u_short>(port));
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr); // IP V4 support
       return true;
   }
   ```
   Inicializa o socket, define timeouts para operações de envio e recebimento, e configura a estrutura de endereço (`sockaddr_in`) com o IP e porta do servidor de destino, usando `inet_pton` para lidar com a conversão do IP.
- **`Send_Query()`**: Envia um pacote de query e recebe a resposta.
   ```cpp
   // samp_network.cpp (trecho chave de Send_Query)
   bool Samp_Network::Send_Query(const std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept {
       // Envia o pacote UDP
       if (sendto(network_socket, query_packet.data(), static_cast<int>(query_packet.size()), 0, reinterpret_cast<const sockaddr*>(&server_address), sizeof(server_address)) < 0)
           return false;
   
       sockaddr_in from_address;
       int address_length = sizeof(from_address);
       // Recebe a resposta
       received_bytes = recvfrom(network_socket, response_buffer.data(), static_cast<int>(response_buffer.size()), 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);
   
       return received_bytes > Constants::QUERY_PACKET_SIZE;
   }
   ```
   Este método envia o `query_packet` (passado como `std::span` para segurança de buffer) ao servidor. Em seguida, tenta receber uma resposta no `response_buffer`. O retorno indica se a operação foi bem-sucedida e se um número de bytes maior que o tamanho do pacote de query foi recebido.

#### Consulta ao Servidor (`server_query.cpp`)

A classe `Server_Query` é dedicada à implementação do protocolo de consulta SA-MP (`'i'`), extraindo as informações básicas do servidor (jogadores, hostname) a partir das respostas **UDP**.

- **`Query()`**: Gerencia as tentativas de consulta.
   ```cpp
   // server_query.cpp (trecho chave de Query)
   bool Server_Query::Query(Server_Information& server_data) noexcept {
       for (int attempt = 0; attempt < Constants::MAX_RETRY_ATTEMPTS; ++attempt) {
           if (Try_Query(server_data))
               return true; // Sucesso na query
   
           if (attempt < Constants::MAX_RETRY_ATTEMPTS - 1)
               // Pequena pausa antes de tentar novamente, para evitar flooding
               std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)));
       }

       return false; // Todas as tentativas falharam
   }
   ```
   Implementa a estratégia de *retry* com `MAX_RETRY_ATTEMPTS` e um *back-off* de tempo crescente, para garantir que as consultas sejam robustas e evitem saturar a rede. Chama `Try_Query` em cada tentativa.
- **`Assemble_Query_Packet()`**: Monta o pacote de query SA-MP.
   ```cpp
   // server_query.cpp (trecho chave de Assemble_Query_Packet)
   void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
       memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
       packet = 'i'; // Código da query de informações
   }
   ```
   O pacote padrão para a consulta de informações (`'i'`) do SA-MP é construído, incluindo a assinatura "SAMP" e o byte identificador 'i'.
- **`Parse_Response()`**: Descompacta a resposta binária do servidor.
   ```cpp
   // server_query.cpp (trecho chave de Parse_Response)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       if (response.size() <= Constants::QUERY_PACKET_SIZE) 
           return false;
   
       auto data_span = response.subspan(Constants::QUERY_PACKET_SIZE); // Pula o cabeçalho
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Ignorado, mas lido
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false;

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false;

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false;
   
       // Note: Gamemode e Language são automaticamente pulados por Read_String_From_Span se o    pacote contiver mais dados.
       // Se precisar dos outros campos basta criar um string e chamar: Read_String_From_Span   (data_span, string_variable);
       return true;
   }
   ```
   Este método lê de forma segura os dados do `response_buffer` (utilizando `std::span` e as funções auxiliares `Read_From_Span` e `Read_String_From_Span`). Ele extrai o número de jogadores, o máximo de jogadores e o hostname do servidor, populando a estrutura `Server_Information`. Os campos não utilizados (como se o servidor é protegido por senha) são lidos mas ignorados, e outros como "gamemode" e "language" são "pulados" se a resposta contiver mais dados que o **ASI** precisa no momento.
- **Funções de Leitura Auxiliares:**
   ```cpp
   // server_query.hpp (snippets das auxiliares de leitura)
   template<typename T>
   static bool Read_From_Span(std::span<const char>& s, T& value) noexcept;
   
   static bool Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept;
   ```
   `Read_From_Span` lida com a leitura de tipos fixos (inteiros, booleans) do `std::span` e avança o `span`. `Read_String_From_Span` lê o comprimento de uma string (como `uint32_t`) e depois a própria string, também avançando o `span`. Isso garante segurança ao parsear bytes e impede leituras fora dos limites do buffer.

#### Gerenciador de URL (`url_manager.cpp`)

A classe `URL_Manager` gerencia as comunicações HTTPS com o **SPC Integration API**, um elemento central para as novas funcionalidades visuais e sociais do **Discord Rich Presence**.

- **`Get_Image_URL_And_Populate_Socials()`**: O método de alto nível para buscar informações da API.
   ```cpp
   // url_manager.cpp (trecho chave de Get_Image_URL_And_Populate_Socials)
   std::string URL_Manager::Get_Image_URL_And_Populate_Socials(const std::string& ip, const int    port, Server_Information& server_info) {
       if (!session_handle)
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);
   
       auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
       std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
       path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   
       const std::string json_data = Request_API_Data(path); // Requisição HTTP para a API
   
       if (json_data.empty())
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE); // Erro na requisição
   
       return Parse_API_Response(json_data, server_info); // Parseia e preenche a server_info
   }
   ```
   Recebe IP e porta, constrói a URL da API incluindo-os como parâmetros. Chama `Request_API_Data` para buscar os dados JSON. Em caso de sucesso, `Parse_API_Response` é chamada para extrair a URL da imagem (logo) e preencher a lista de links sociais no `server_info`.
- **`Request_API_Data()`**: Realiza a requisição HTTPS para a API.
   ```cpp
   // url_manager.cpp (trecho chave de Request_API_Data)
   std::string URL_Manager::Request_API_Data(const std::wstring& path) {
       auto api_host_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Host());
       const std::wstring wide_host = Utils::Convert_Utf8_To_Wide_String(api_host_accessor.Get());
       HINTERNET connect_handle = WinHttpConnect(session_handle, wide_host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
   
       if (!connect_handle) return "";
   
       HINTERNET request_handle = WinHttpOpenRequest(connect_handle, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
   
       if (!request_handle) return (WinHttpCloseHandle(connect_handle), "");
   
       // Enviar requisição, receber resposta, verificar status 200, ler dados em loop
       // ... (detalhes da chamada WinHttpSendRequest, WinHttpReceiveResponse, WinHttpQueryHeaders, WinHttpReadData) ...
       
       WinHttpCloseHandle(request_handle); WinHttpCloseHandle(connect_handle);
       return response_body; // Retorna o JSON como string
   }
   ```
   Conecta ao host da API (obtido de forma ofuscada), abre e envia uma requisição `GET` com o caminho (`path`). Lida com a resposta HTTP, verifica o código de status (200 OK para sucesso), e lê o corpo completo da resposta (que deve ser JSON). Todos os handles WinHTTP são liberados em caso de sucesso ou falha.
- **`Parse_API_Response()`**: Processa a string JSON para extrair dados.
   ```cpp
   // url_manager.cpp (trecho chave de Parse_API_Response)
   std::string URL_Manager::Parse_API_Response(const std::string& json_content,    Server_Information& server_info) {
       server_info.Social_Links.clear(); // Limpa links sociais existentes
       try {
           const auto json = nlohmann::json::parse(json_content);
   
           if (json.value("success", false) && json.contains("data") && json["data"].contains("public")) {
               const auto& public_data = json["data"]["public"];
               const std::vector<std::string> social_keys = { "website", "discord", "youtube", "instagram", "facebook", "tiktok" };
               
               // Extrai e popula links sociais
               for (const auto& key : social_keys) {
                   if (public_data.contains(key)) {
                       std::string value = public_data.value(key, "not-defined");

                       if (!value.empty() && value != "not-defined")
                           server_info.Social_Links.push_back({ key, value });
                   }
               }

               return public_data.value("logo", ""); // Retorna a URL do logo
           }
       }
       catch (const nlohmann::json::exception&) { /* Trata erro de parseamento */ }

       return ""; // Falha no parseamento
   }
   ```
   Utiliza `nlohmann::json::parse` para converter a string JSON em um objeto JSON manipulável. Navega pela estrutura (`success`, `data`, `public`) e extrai a `logo` (que se torna o `display_image_url`) e itera sobre chaves predefinidas para encontrar e popular os `Social_Links` do `server_info`.

### Estrutura do Código

O projeto **SA-MP Rich Presence** é cuidadosamente organizado em um layout de diretórios claro, com o código-fonte (`src/`) e um subdiretório para bibliotecas externas (`libraries/`). A nomeclatura dos arquivos segue a convenção `_manager` ou `_network` para clareza sobre o propósito de cada classe. A maioria dos arquivos de cabeçalho usa a extensão `.hpp`, indicando que são arquivos de cabeçalho C++.

```
src/
├── libraries/               # Contém bibliotecas de terceiros essenciais
│   ├── Dralyxor/            # Biblioteca de ofuscação de strings
│   ├── Discord/             # Biblioteca oficial do Discord RPC
│   └── nlohmann/            # Biblioteca para manipulação de JSON
├── asi_update.hpp           # Definição do sistema de atualização automática
├── command_line_parser.hpp  # Definição do parser de linha de comando
├── constants.hpp            # Definições de constantes globais do projeto
├── discord_manager.hpp      # Definição do gerenciador de comunicação com o Discord
├── main.cpp                 # Ponto de entrada do ASI e orquestrador principal
├── samp_network.hpp         # Definição do gerenciador de rede para consultas SA-MP
├── secrets.hpp              # Definições para ofuscação de segredos
├── server_manager.hpp       # Definição do gerenciador de informações do servidor
├── server_query.hpp         # Definição da lógica de consulta ao servidor SA-MP
├── server_types.hpp         # Definições de estruturas de dados do servidor
├── url_manager.hpp          # Definição do gerenciador de URL para SPC Integration API
└── utils.hpp                # Funções utilitárias gerais (conversão de strings)
```

#### Constantes Globais (`constants.hpp`)

Este arquivo concentra todas as configurações e valores imutáveis do projeto, acessíveis globalmente. Ele usa `inline constexpr` para garantir que as constantes estejam diretamente disponíveis para o compilador, otimizando o desempenho.

```cpp
// constants.hpp (trecho)
namespace Constants {
    inline constexpr char ASI_VERSION[] = "1.1"; // Versão para o sistema de atualização
    inline constexpr wchar_t UPDATE_API_HOST[] = L"api.github.com"; // Host da API de update
    inline constexpr char DEFAULT_IMAGE[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/default_logo.png"; // Imagem padrão
    inline constexpr int QUERY_TIMEOUT_MS = 800; // Timeout da query em ms
    inline constexpr std::chrono::seconds MAIN_LOOP_INTERVAL = std::chrono::seconds(1); // Intervalo do loop principal
}
```
Detalhes importantes como URLs de API, caminhos de imagens padrão, tempos limite de rede e intervalos de atualização do **Discord Rich Presence** são centralizados aqui. O uso de `std::chrono::seconds` para intervalos melhora a legibilidade e previne erros de unidades.

#### Estruturas de Dados (`server_types.hpp`)

Este arquivo define os `structs` e `using` importantes para organizar os dados coletados e exibidos.

```cpp
// server_types.hpp (trecho)
namespace server_types {
    using Social_Link = std::pair<std::string, std::string>; // Tupla (nome da rede, URL/valor)
}

struct Server_Information {
    uint16_t Players{0};           // Número de jogadores atuais
    uint16_t Max_Players{0};       // Capacidade máxima de jogadores
    std::string Hostname{};        // Nome do servidor
    std::string Server_Address{};  // Ex: "192.168.1.1:7777"

    std::vector<server_types::Social_Link> Social_Links{}; // Lista de links sociais do servidor
};
```
O `Server_Information` é a estrutura primária que armazena os dados do servidor. A adição de `std::vector<server_types::Social_Link> Social_Links` reflete a nova capacidade de puxar múltiplos links de redes sociais da API, organizados como pares `(nome_rede, link)`.

#### Ofuscação de Segredos (`secrets.hpp`)

Este arquivo é dedicado a proteger informações sensíveis, como o **Discord Application ID** e os endereços do **SPC Integration API (por enquanto)**, de engenharia reversa fácil.

```cpp
// secrets.hpp (trecho)
#include "libraries/Dralyxor/dralyxor.hpp"

namespace Secrets {
    namespace {
        inline auto& Get_Obfuscated_Discord_App_ID() {
            static auto& dc_app_id_obfuscated = DRALYXOR_KEY("DISCORD_APP_ID", "YOUR_SECRET_KEY_HERE");

            return dc_app_id_obfuscated;
        }
        // ... (outros segredos ofuscados) ...
    }
    namespace Detail {
        inline auto& Get_Discord_App_ID() {
            return Get_Obfuscated_Discord_App_ID();
        }
        // ... (getters públicos para acessar os segredos desofuscados) ...
    }
}
```
A biblioteca [Dralyxor](https://github.com/ocalasans/dralyxor) é usada com a macro `DRALYXOR_KEY` para criptografar strings literais no binário compilado. `DRALYXOR_SECURE` é então usada no tempo de execução para desofuscar esses valores quando eles são necessários, adicionando uma camada de segurança robusta contra a extração estática de chaves.

#### Utilitários Gerais (`utils.hpp`)

Um arquivo para funções auxiliares genéricas que podem ser úteis em vários módulos, evitando duplicação de código.

```cpp
// utils.hpp (trecho)
namespace Utils {
    inline std::string Convert_Wide_To_Utf8_String(const std::wstring_view wide_string) {
        // ... (implementação de conversão usando WideCharToMultiByte) ...
    }

    inline std::wstring Convert_Utf8_To_Wide_String(const std::string_view narrow_string) {
        // ... (implementação de conversão usando MultiByteToWideChar) ...
    }
}
```
Contém funções `Convert_Wide_To_Utf8_String` e `Convert_Utf8_To_Wide_String`, essenciais para interoperações com APIs do Windows (que usam UTF-16) e operações padrão C++ (que geralmente se beneficiam do UTF-8). Estas funções usam as APIs do Windows para conversão segura e eficiente.

### Tratamento de Erros e Resiliência

O **SA-MP Rich Presence** foi projetado com resiliência em mente, incorporando múltiplos mecanismos para lidar com erros de rede, entradas inválidas e indisponibilidade de serviços.

- **Timeouts e Retries de Rede:**
   - **Timeouts Explícitos:** Sockets de rede em `samp_network.cpp` configuram timeouts (`Constants::QUERY_TIMEOUT_MS`) tanto para envio quanto para recebimento de dados, prevenindo que o programa fique "travado" aguardando por uma resposta de um servidor inativo.
      ```cpp
      // samp_network.cpp (configuração de timeout)
      const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
      setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      ```
   - **Múltiplas Tentativas de Query:** O `Server_Query` executa `Constants::MAX_RETRY_ATTEMPTS` consultas em caso de falha. Um *back-off* exponencial é implementado (`std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)))`) para aguardar antes de novas tentativas, reduzindo a carga e aumentando a chance de sucesso em condições de rede instáveis.
- **Tratamento de Desconexão Robusto:**
   - **Transição de Estado Graceful:** Em `server_manager.cpp`, o status de conexão (`connection_status`) não é alterado imediatamente após uma única falha de query. Somente se nenhuma resposta for recebida por 15 segundos consecutivos (`now - last_successful_query > std::chrono::seconds(15)`), o status é atualizado para `false`. Isso evita o "piscar" da presença no Discord devido a pequenas perdas de pacotes.
      ```cpp
      // server_manager.cpp (lógica de desconexão)
      else { // Se a query falhou
          if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
              connection_status = false;
              display_image_url = Constants::DEFAULT_IMAGE;
              display_server_data = {};
              current_display_social = {};
          }
      }
      ```
   - **Fallback Visual:** Ao detectar uma desconexão, a imagem da presença no Discord retorna à `Constants::DEFAULT_IMAGE`, e os dados do servidor/sociais são limpos, fornecendo um feedback claro ao usuário de que não está mais conectado.
- **Tratamento de Entradas Inválidas:**
   - **`command_line_parser.cpp`:** Ao converter o argumento de porta de string para inteiro (`std::stoi`), um bloco `try-catch` é utilizado para lidar com `std::invalid_argument` (não é um número) ou `std::out_of_range` (número muito grande/pequeno). Se ocorrer um erro, a porta padrão é mantida ou o parseamento falha de forma controlada, prevenindo travamentos.
- **Resiliência na Obtenção de Dados da API:**
   - **WinHTTP Falhas:** Todas as operações da API WinHTTP em `url_manager.cpp` são verificadas para `null` handles e retornos de `false` em cada etapa (abrir sessão, conectar, abrir requisição, enviar/receber, ler dados), garantindo que falhas parciais sejam capturadas.
   - **HTTP Status Codes:** Após uma requisição HTTP, o `url_manager.cpp` verifica o `HTTP Status Code`. Apenas um código `200 OK` é aceito como sucesso, descartando respostas de erro do servidor ou do gateway.
   - **Parseamento JSON Seguro:** `url_manager.cpp` envolve o parseamento JSON (`nlohmann::json::parse`) em um bloco `try-catch(const nlohmann::json::exception&)`. Isso impede que JSONs malformados ou incompletos vindos da API causem um crash, retornando strings vazias ou a imagem padrão.
- **Mecanismos de Atualização Seguros:**
   - **`asi_update.hpp`:** O processo de verificação de atualização no `Check_For_Update` é encapsulado em um bloco `try-catch(const std::exception&)`. Isso garante que, mesmo que o GitHub esteja offline, a rede esteja instável, ou a resposta JSON seja inválida, o **ASI** não crashe e o jogo possa continuar a ser carregado, ignorando a verificação de atualização de forma segura.
   - **Gerenciamento de Handles WinHTTP:** A liberação de `HINTERNET` handles no `asi_update.hpp` e `url_manager.cpp` é cuidadosamente planejada para ser executada em todos os caminhos de código (sucesso e falha), prevenindo vazamentos de recursos.

### Sistema de Processamento de Linha de Comando

O **SA-MP Rich Presence** extrai informações cruciais para sua operação (IP do servidor, porta e nome do jogador) diretamente da linha de comando do jogo Grand Theft Auto: San Andreas. Este método garante que o **ASI** obtenha os dados mais precisos e relevantes assim que o jogo é inicializado ou um servidor é conectado.

#### Parser de Linha de Comando (`command_line_parser.cpp`)

A classe `Command_Line_Parser` é responsável por analisar a string de comando completa do processo, identificar e extrair os parâmetros específicos usados pelo SA-MP.

- **`Parse()`**: O ponto de entrada para a análise da linha de comando.
   ```cpp
   // command_line_parser.cpp (trecho chave de Parse)
   bool Command_Line_Parser::Parse(const std::wstring_view command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       server_ip = Constants::DEFAULT_SERVER_IP; // Valores padrão
       server_port = Constants::DEFAULT_SERVER_PORT;
   
       if (const auto ip_param = Parse_Parameter(command_line, L"-h"); !ip_param.empty())
           server_ip = Utils::Convert_Wide_To_Utf8_String(ip_param); // Extrai e converte IP
   
       if (const auto port_param = Parse_Parameter(command_line, L"-p"); !port_param.empty()) {
           try {
               server_port = std::stoi(std::wstring(port_param)); // Extrai e converte Porta (com tratamento de erro)
           }
           catch (const std::invalid_argument&) {}
           catch (const std::out_of_range&) {}
       }
   
       if (const auto name_param = Parse_Parameter(command_line, L"-n"); !name_param.empty())
           player_name = Utils::Convert_Wide_To_Utf8_String(name_param); // Extrai e converte Nome
   
       return !server_ip.empty() && server_port > 0 && !player_name.empty(); // Valida se os dados essenciais estão presentes
   }
   ```
   Recebe a linha de comando (`command_line`) como `std::wstring_view` para eficiência. Utiliza `Parse_Parameter` para encontrar e extrair os valores associados a `-h` (host/IP), `-p` (port) e `-n` (player name). Os valores extraídos (em `std::wstring_view`) são convertidos para `std::string` (UTF-8) usando o `Utils::Convert_Wide_To_Utf8_String`. Para a porta, um bloco `try-catch` envolve `std::stoi` para gerenciar possíveis erros de conversão de forma segura. A função retorna `true` se todos os parâmetros cruciais (IP, porta válida e nome do jogador) forem obtidos.
- **`Parse_Parameter()`**: A função auxiliar para a extração de um único parâmetro.
   ```cpp
   // command_line_parser.cpp (trecho chave de Parse_Parameter)
   std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring_view command_string, const std::wstring_view parameter) {
       if (const size_t position = command_string.find(parameter); position != std::wstring_view::npos) {
           size_t value_start = position + parameter.length();
           value_start = command_string.find_first_not_of(L" \t", value_start); // Pula espaços após o parâmetro

           if (value_start == std::wstring_view::npos)
               return L""; // Parâmetro encontrado mas sem valor
   
           const size_t value_end = command_string.find(L' ', value_start); // Encontra o próximo espaço (fim do valor)
           
           return std::wstring(command_string.substr(value_start, value_end - value_start)); // Retorna a substring do valor
       }

       return L""; // Parâmetro não encontrado
   }
   ```
   Localiza a substring do `parameter` (`-h`, `-p`, `-n`) na `command_string`. Calcula a posição inicial do valor, ignorando espaços/tabulações. Identifica a posição final do valor (próximo espaço) e retorna a substring que corresponde ao valor do parâmetro.

### Protocolo de Comunicação SA-MP

O **ASI** interage diretamente com servidores SA-MP usando o protocolo de consulta **UDP** para extrair informações vitais de tempo real. Essa comunicação é implementada para ser eficiente e resiliente a falhas de rede.

#### Implementação do Protocolo

A classe `Server_Query` é a espinha dorsal dessa implementação, gerenciando o envio de pacotes e a interpretação das respostas.

- **Estrutura do Pacote de Consulta SA-MP (`'i'`)**: O **ASI** constrói um pacote **UDP** de 11 bytes para a query de informações:
   - `BYTE 0-3`: Assinatura "SAMP" (S A M P).
   - `BYTE 4-9`: Sequência de 6 bytes arbitrários (geralmente endereço de IP de origem da requisição para o servidor reconhecer o cliente).
   - `BYTE 10`: Identificador da query 'i' (ASCII 105), indicando que o **ASI** deseja informações gerais do servidor (hostname, jogadores, etc.).
      ```cpp
      // server_query.cpp (montagem do pacote)
      void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
          memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
          packet = 'i'; // Informação (Information) query
      }
      ```
- **Estrutura da Resposta do Servidor**: Quando um servidor SA-MP responde a uma query 'i', ele envia um pacote **UDP** contendo uma sequência de dados estruturados, que o **ASI** precisa parsear:
   - **Cabeçalho da Resposta:** Repetição da assinatura "SAMP" e da sequência de 6 bytes do pacote de requisição. O **ASI** simplesmente pula esses `Constants::QUERY_PACKET_SIZE` bytes iniciais.
   - **Passworded (`bool`):** Um byte indicando se o servidor está protegido por senha. Lido, mas não usado.
   - **Players (`uint16_t`):** O número de jogadores atualmente conectados ao servidor.
   - **Max_Players (`uint16_t`):** O número máximo de slots de jogadores que o servidor suporta.
   - **Hostname (string prefixada por `uint32_t`):** O nome amigável do servidor. O pacote inclui um `uint32_t` para indicar o comprimento da string de hostname, seguido pelos bytes da string real.
   - **Outros Campos:** O protocolo SAMP continua com "gamemode" e "language", também prefixados por tamanho. O **ASI** lê e pula esses campos para se focar nos dados essenciais de `Players`, `Max_Players`, e `Hostname`.

   A leitura desses campos é feita com as funções auxiliares `Read_From_Span` e `Read_String_From_Span`, que garantem que o **ASI** não leia bytes fora do limite do buffer e lide corretamente com a leitura de tipos de dados de comprimento fixo e variáveis (strings).
   ```cpp
   // server_query.cpp (parseamento da resposta)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       // ... (Verificação de tamanho e subspan para os dados) ...
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Lê o booleano 'passworded'
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false; // Lê 'Players'

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false; // Lê 'Max_Players'

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false; // Lê 'Hostname'
   
       // Campos 'Gamemode' e 'Language' são implicitamente "pulados"
       // pela subsequente chamada de Read_String_From_Span
       // para mover o span para além de seus dados no buffer.
       uint32_t length_placeholder; // Variável temporária para segurar o tamanho.

       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Lê tamanho do gamemode

       if (data_span.size() < length_placeholder)
           return false; // Verifica bounds

       data_span = data_span.subspan(length_placeholder); // Pula dados do gamemode
   
       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Lê tamanho do language

       if (data_span.size() < length_placeholder)
           return false; // Verifica bounds

       data_span = data_span.subspan(length_placeholder); // Pula dados do language
   
       return true;
   }
   ```
   No exemplo acima, a lógica `data_span = data_span.subspan(length_placeholder);` é uma forma eficiente de "pular" o número de bytes lidos por uma string cujo conteúdo não é necessário para o Rich Presence.

### Benefícios do SA-MP Rich Presence

O SA-MP Rich Presence aprimora significativamente a experiência tanto para jogadores quanto para administradores de servidores, oferecendo vantagens notáveis:

1. **Para Jogadores:**
   - **Visibilidade Sem Esforço:** Compartilhe automaticamente seu status de jogo no Discord com amigos, mostrando exatamente onde você está jogando.
   - **Informações Rica:** Tenha acesso imediato aos detalhes do servidor (nome, contagem de jogadores, IP, logo personalizado) diretamente no Discord, eliminando a necessidade de verificar essas informações em outros lugares.
   - **Acesso Direto à Comunidade:** Descubra e acesse rapidamente as redes sociais do servidor através dos ícones rotativos na presença do Discord, facilitando a entrada em comunidades vibrantes.
   - **Conexão Rápida com Amigos:** Convide ou entre no mesmo servidor que seus amigos com um clique, graças à funcionalidade de botão "Join".
   - **Experiência Always-On:** O sistema de atualização automática garante que você sempre utilize a versão mais otimizada e funcional do **ASI**.
2. **Para Servidores:**
   - **Marketing Virar Natural:** A presença no Discord dos seus jogadores atua como um outdoor digital, divulgando seu servidor para uma audiência orgânica (os amigos dos jogadores) 24 horas por dia.
   - **Identidade Visual Forte:** Um logo personalizado e a rotação de links sociais permitem que seu servidor se destaque e projete uma imagem profissional e moderna no ambiente Discord.
   - **Engajamento Aumentado:** Facilite o caminho para que novos e antigos jogadores se conectem com suas plataformas sociais, fortalecendo sua comunidade e engajamento fora do jogo.
   - **Recrutamento Facilitado:** O recurso "Join" agiliza o processo para novos jogadores, eliminando barreiras e incentivando a experimentação.
   - **Dados Consistentes:** Através da integração com o **SPC Integration API**, a exibição de informações é unificada e atualizada centralmente, garantindo que a marca e os contatos do seu servidor estejam sempre corretos.

## Licença

Este ASI está protegido sob a Licença Apache 2.0, que permite:

- ✔️ Uso comercial e privado
- ✔️ Modificação do código fonte
- ✔️ Distribuição do código
- ✔️ Concessão de patentes

### Condições:

- Manter o aviso de direitos autorais
- Documentar alterações significativas
- Incluir cópia da licença Apache 2.0

Para mais detalhes sobre a licença: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Todos os direitos reservados**