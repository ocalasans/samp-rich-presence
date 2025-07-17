# SA-MP Rich Presence

Il **SA-MP Rich Presence** è un **ASI** per **SA-MP (San Andreas Multiplayer)** che aggiorna automaticamente il tuo stato su Discord con informazioni dettagliate del server. L'**ASI** viene iniettato nel gioco quando ti connetti a un server SA-MP, mostrando informazioni del server.

## Lingue

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Indice

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Lingue](#lingue)
  - [Indice](#indice)
  - [Funzionalità](#funzionalità)
    - [Discord Rich Presence](#discord-rich-presence)
    - [Sistema di Aggiornamento Automatico](#sistema-di-aggiornamento-automatico)
  - [Requisiti](#requisiti)
  - [Installazione](#installazione)
  - [Integrazione con l'SPC Integration API](#integrazione-con-lspc-integration-api)
    - [Come vengono ottenute e utilizzate le informazioni:](#come-vengono-ottenute-e-utilizzate-le-informazioni)
  - [Per gli Sviluppatori di Server](#per-gli-sviluppatori-di-server)
    - [Come implementare l'SPC Integration nel tuo server:](#come-implementare-lspc-integration-nel-tuo-server)
  - [Architettura Tecnica Dettagliata](#architettura-tecnica-dettagliata)
      - [Sistema Principale (`main.cpp`)](#sistema-principale-maincpp)
      - [Sistema di Aggiornamento (`asi_update.hpp`)](#sistema-di-aggiornamento-asi_updatehpp)
      - [Gestore Discord (`discord_manager.cpp`)](#gestore-discord-discord_managercpp)
      - [Gestore Server (`server_manager.cpp`)](#gestore-server-server_managercpp)
      - [Sistema di Rete (`samp_network.cpp`)](#sistema-di-rete-samp_networkcpp)
      - [Query al Server (`server_query.cpp`)](#query-al-server-server_querycpp)
      - [Gestore URL (`url_manager.cpp`)](#gestore-url-url_managercpp)
    - [Struttura del Codice](#struttura-del-codice)
      - [Costanti Globali (`constants.hpp`)](#costanti-globali-constantshpp)
      - [Strutture di Dati (`server_types.hpp`)](#strutture-di-dati-server_typeshpp)
      - [Offuscamento dei Segreti (`secrets.hpp`)](#offuscamento-dei-segreti-secretshpp)
      - [Utilità Generali (`utils.hpp`)](#utilità-generali-utilshpp)
    - [Gestione degli Errori e Resilienza](#gestione-degli-errori-e-resilienza)
    - [Sistema di Elaborazione della Riga di Comando](#sistema-di-elaborazione-della-riga-di-comando)
      - [Parser della Riga di Comando (`command_line_parser.cpp`)](#parser-della-riga-di-comando-command_line_parsercpp)
    - [Protocollo di Comunicazione SA-MP](#protocollo-di-comunicazione-sa-mp)
      - [Implementazione del Protocollo](#implementazione-del-protocollo)
    - [Benefici del SA-MP Rich Presence](#benefici-del-sa-mp-rich-presence)
  - [Licenza](#licenza)
    - [Condizioni:](#condizioni)

## Funzionalità

### Discord Rich Presence

Il **Discord Rich Presence** è una funzionalità che consente alle applicazioni di mostrare informazioni dettagliate su ciò che l'utente sta facendo direttamente sul profilo Discord. Nel caso del **SA-MP Rich Presence**, vengono visualizzate le seguenti informazioni:

- **Nome del server (Hostname):** Il nome principale del server.
- **Nome del giocatore:** Il tuo nickname attuale nel gioco.
- **Conteggio dei giocatori:** Numero attuale di giocatori online e il massimo consentito.
- **Indirizzo del server:** IP e porta del server per una facile identificazione.
- **Immagine personalizzata del server:** Un logo unico del server, se disponibile.
- **Icona sociale rotante:** Piccole icone che rappresentano i link ai social media del server (website, Discord, YouTube, Instagram, Facebook, TikTok), che si alternano automaticamente.
- **Tempo di gioco:** Quanto tempo sei connesso al server attuale.
- **Stato della connessione:** Indica se sei online su un server o nello stato "Idle" (inattivo).
- **Pulsante "Join" (Unisciti):** Permette ai tuoi amici di entrare direttamente nello stesso server in cui stai giocando.

### Sistema di Aggiornamento Automatico

L'**ASI** integra un sistema di verifica degli aggiornamenti. All'avvio del gioco, verifica se sono disponibili nuove versioni nel repository GitHub ufficiale del progetto. Se viene rilevato un aggiornamento, viene visualizzata una notifica amichevole all'utente, offrendo opzioni per:

1. Aprire il browser direttamente sulla pagina dei rilasci per il download.
2. Continuare senza aggiornare, con l'opzione di disabilitare l'**ASI** per la sessione attuale.

Questa funzionalità garantisce che gli utenti abbiano sempre accesso alle ultime migliorie, correzioni di bug e nuove funzionalità, promuovendo un'esperienza aggiornata e senza interruzioni.

## Requisiti

- Cliente SA-MP (se non lo possiedi: [clients-samp](https://github.com/spc-samp/clients-samp)).
- Applicazione Discord Desktop.
- Sistema Operativo Windows.
- Visual C++ Runtime.
- Un [ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) installato nel tuo Grand Theft Auto: San Andreas.

## Installazione

1. Scarica l'ultima versione dell'**ASI** compilata direttamente dalla sezione dei [releases](https://github.com/ocalasans/samp-rich-presence/releases) su GitHub.
2. Dopo il download, individua il file `.asi`.
3. Copia il file `.asi` scaricato nella cartella principale del tuo GTA San Andreas (dove si trova il file `gta_sa.exe`).
4. Avvia il gioco tramite il cliente SA-MP.
5. L'**ASI** verrà caricato e inizializzato automaticamente quando ti connetti a un server, aggiornando il tuo stato su Discord.

## Integrazione con l'SPC Integration API

Il **SA-MP Rich Presence** migliora significativamente la visualizzazione delle informazioni su Discord attraverso la sua integrazione con l'**SPC Integration API**. Invece di dipendere solo dai dati di query di base, l'**ASI** ora interagisce direttamente con questa API per ottenere informazioni visive e sociali del server. Per saperne di più sull'**SPC Integration**, visita il repository ufficiale: [spc-samp/spc-integration](https://github.com/spc-samp/spc-integration).

### Come vengono ottenute e utilizzate le informazioni:

1. **Formattazione dell'indirizzo:** Quando il giocatore si connette a un server (IP e Porta), l'**ASI** formatta questo indirizzo (`IP:PORTA`) in un formato amichevole (`IP-PORTA`), preparandolo per la richiesta dell'API.
2. **Richiesta all'API:** L'**ASI** invia una richiesta `GET` all'endpoint dell'**SPC Integration API**, includendo l'IP e la porta formattati. Esempio di come l'URL della richiesta viene costruito internamente:
   ```cpp
   // Trecho adaptado de url_manager.cpp
   auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
   std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
   path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   const std::string json_data = Request_API_Data(path);
   ```
3. **Elaborazione della risposta JSON:** L'API restituisce una risposta in formato JSON. L'**ASI** utilizza la libreria [nlohmann/json](https://github.com/nlohmann/json) per analizzare questa risposta ed estrarre i dati rilevanti.
   ```json
   // Esempio di struttura della risposta dell'SPC Integration API
   {
       "success": true,
       "data": {
           "public": {
               "logo": "https://url.del.tuo.logo/server_logo.png",
               "website": "https://tuo-sito.com",
               "discord": "https://discord.gg/tuoserver",
               "youtube": "https://youtube.com/tuocanale"
               // ...altri social media
           }
       }
   }
   ```
4. **Estrazione dei dati:**
   - **Logo del server:** L'URL dell'immagine del server (il `logo` nella sezione `public`) viene estratto e utilizzato come immagine principale (large image) nel **Discord Rich Presence**. Ciò garantisce un'identità visiva autentica e personalizzabile per ogni server.
   - **Link sociali:** Una lista predefinita di social media (website, Discord, YouTube, Instagram, Facebook, TikTok) viene verificata nella risposta JSON. Per ogni social media trovato con un valore valido, il nome del social e il rispettivo link vengono memorizzati.
5. **Visualizzazione su Discord:** Il `Server_Manager` utilizza la lista di link sociali estratti per implementare una rotazione dinamica. Ogni 30 secondi, un'icona diversa di uno dei social media del server viene visualizzata come "small image" (immagine piccola) nella presenza di Discord, insieme al link o al nome della piattaforma, incoraggiando l'esplorazione delle comunità del server.

## Per gli Sviluppatori di Server

L'integrazione del tuo server con l'[SPC Integration](https://github.com/spc-samp/spc-integration) porta una serie di benefici diretti e indiretti che aumentano la visibilità e l'engagement della tua comunità SA-MP. Se sei uno sviluppatore di server, considera i vantaggi strategici:

1. **Potenzia il tuo brand:**
   - **Visibilità Premium:** Il logo personalizzato del tuo server non sarà solo un testo, ma un'immagine vibrante e accattivante, mostrata in evidenza nel profilo Discord di tutti i giocatori che utilizzano questo **ASI**. Questa è una forma organica e costante di branding.
   - **Presenza professionale:** Avendo il tuo logo e i social media ben rappresentati, il tuo server proietta un'immagine più consolidata e affidabile, attirando maggiore interesse e potenziali nuovi giocatori.
2. **Espansione della comunità:**
   - **Moltiplica i canali di accesso:** Con la rotazione delle icone sociali, puoi promuovere diverse piattaforme della tua comunità – dal sito web ufficiale e il Discord del server fino alle tue pagine su YouTube, Instagram, Facebook o TikTok. Ogni icona e link nel **Discord Rich Presence** dirige direttamente gli interessati verso i luoghi in cui la tua comunità è attiva.
   - **Connettività istantanea:** La funzionalità di "Join" tramite Discord consente agli amici dei tuoi giocatori di entrare nel tuo server SA-MP con un solo clic, riducendo le barriere di ingresso e incoraggiando nuovi membri.
3. **Aggiornamento semplificato dei contenuti:**
   - Utilizzando l'[SPC Integration](https://github.com/spc-samp/spc-integration), qualsiasi aggiornamento al logo del tuo server o alla lista di social media configurati nel plugin [SPC Integration](https://github.com/spc-samp/spc-integration) **(lato server)** verrà riflesso automaticamente per i giocatori che utilizzano l'**ASI**, senza che debbano aggiornare l'**ASI**. Ciò garantisce che le informazioni siano sempre corrette e aggiornate.

### Come implementare l'SPC Integration nel tuo server:

1. **Plugin SPC Integration:** Il tuo server dovrà avere il plugin [SPC Integration](https://github.com/spc-samp/spc-integration) installato e configurato correttamente. Questo plugin è il ponte che invia le informazioni del tuo server a una lista di dati dell'**SPC**, che, di conseguenza, viene utilizzata dall'**SPC Integration API** per fornire informazioni pubbliche.
2. **Configurazione:** Segui le istruzioni nel repository del plugin [SPC Integration](https://github.com/spc-samp/spc-integration) per configurare:
   - Il parametro `logo` con l'URL del logo del tuo server.
   - I parametri dei social media (`discord`, `website`, `youtube`, ecc.) con i link validi per le tue piattaforme.
3. **Aggiornamento automatico:** Una volta che le informazioni sono configurate nel plugin del server, il **SA-MP Rich Presence** le rileverà e le mostrerà automaticamente. Non è necessaria alcuna azione da parte del giocatore oltre all'installazione iniziale dell'**ASI**.

Integrando il tuo server con l'[SPC Integration](https://github.com/spc-samp/spc-integration), non solo migliori l'esperienza dei tuoi giocatori, ma apri anche le porte a una crescita e un engagement significativi per la tua comunità.

## Architettura Tecnica Dettagliata

Il **SA-MP Rich Presence** ha un'architettura modulare ben definita, con componenti focalizzati su compiti specifici. La base di codice è allineata con gli standard moderni del C++ (C++17 e C++20), utilizzando `std::string_view`, `std::span` e semantica di movimento per garantire alte prestazioni, sicurezza ed efficienza.

#### Sistema Principale (`main.cpp`)

Il cuore dell'**ASI** risiede in `main.cpp`, che gestisce il ciclo di vita dell'applicazione, dalla sua inizializzazione come DLL fino al loop continuo di aggiornamento e al suo spegnimento graduale.

- **`DllMain`**: Il punto di ingresso dell'**ASI** quando viene caricato dal sistema operativo.
   ```cpp
   // DllMain (semplificato per concentrarsi sulla struttura)
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
   In questa funzione, quando viene collegata al processo del gioco (`DLL_PROCESS_ATTACH`), impedisce chiamate di libreria non necessarie (`DisableThreadLibraryCalls`) e **crea un nuovo thread (`Main_Update_Thread`)** per eseguire la logica dell'**ASI** in modo asincrono, garantendo che il gioco non venga bloccato. Durante lo spegnimento (`DLL_PROCESS_DETACH`), viene invocato `Shutdown_Managers()` per liberare le risorse.
- **`Main_Update_Thread`**: L'anima dell'**ASI**, operante nel proprio thread.
   ```cpp
   // Main_Update_Thread (tratto chiave)
   DWORD WINAPI Main_Update_Thread(LPVOID) {
       // 1. Verifica degli aggiornamenti
       if (Asi_Update::Check_For_Update())
           return 0; // Se l'utente ha scelto di disattivare, termina.
   
       // 2. Inizializzazione della rete (Winsock)
       WSAData wsa_data;

       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
   
       // 3. Inizializza i gestori di server e Discord
       Initialize_Managers();
   
       // 4. Loop principale di aggiornamento
       while (is_running && v_server_manager && v_discord_manager) {
           v_server_manager->Update(); // Consulta il server, l'API SPC, ecc.
           v_discord_manager->Update_Presence( // Aggiorna lo stato di Discord
               v_server_manager->Get_Server_Info(),
               v_server_manager->Get_Display_Social_Link(),
               v_server_manager->Get_Player_Name(),
               v_server_manager->Get_Current_Image_URL(),
               v_server_manager->Is_Connected());
   
           Discord_RunCallbacks(); // Elabora gli eventi RPC di Discord
           std::this_thread::sleep_for(Constants::MAIN_LOOP_INTERVAL);
       }
   
       // 5. Spegnimento (se i gestori esistono)
       if (v_discord_manager)
           v_discord_manager->Shutdown();

       WSACleanup(); // Libera Winsock

       return 0;
   }
   ```
   Questa funzione dà priorità alla verifica degli aggiornamenti. Successivamente, inizializza lo stack di rete Winsock e le istanze dei gestori di server e Discord. Un loop `while` persistente (controllato da `std::atomic<bool> is_running` per uno spegnimento sicuro) coordina le chiamate a `Server_Manager::Update()` (raccolta dati) e `Discord_Manager::Update_Presence()` (invio a Discord). `Discord_RunCallbacks()` garantisce che Discord elabori gli eventi della Rich Presence. Il loop viene messo in pausa periodicamente utilizzando `std::this_thread::sleep_for` per l'ottimizzazione delle risorse.

#### Sistema di Aggiornamento (`asi_update.hpp`)

Questo modulo vitale aggiunge intelligenza all'**ASI**, garantendo che gli utenti rimangano aggiornati.

- **`Check_For_Update()`**: La funzione principale di verifica.
   ```cpp
   // asi_update.hpp (tratto chiave di Check_For_Update)
   inline bool Check_For_Update() {
       HINTERNET h_session = nullptr, h_connect = nullptr, h_request = nullptr;
       bool update_found_and_handled = false;
   
       try {
           h_session = WinHttpOpen(L"SA-MP Rich Presence Update/1.0", ...);
           // ... (richiesta GET per Constants::UPDATE_API_PATH nell'API di GitHub) ...
           std::string response_body;
           // ... (lettura della risposta HTTP) ...
           nlohmann::json release_info = nlohmann::json::parse(response_body);
   
           std::string latest_tag = release_info["tag_name"].get<std::string>();
           // ... (normalizza e confronta le versioni usando sscanf_s/sscanf) ...
   
           if (latest_major > current_major || (latest_major == current_major && latest_minor > current_minor)) {
               update_found_and_handled = true;
               std::wstringstream message_stream;
               // ... (prepara il messaggio della MessageBox) ...
               int msgbox_result = MessageBoxW(NULL, message_stream.str().c_str(), L"SA-MP Rich Presence - Update Available", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
               
               if (msgbox_result == IDYES)
                   ShellExecuteW(NULL, L"open", Constants::UPDATE_RELEASES_URL, NULL, NULL, SW_SHOWNORMAL);
           }
       }
       catch (const std::exception&) { /* Gestione degli errori */ }
   
       // ... (chiudi handle WinHttp) ...
       return update_found_and_handled;
   }
   ```
   Utilizzando l'**API WinHTTP** per le richieste di rete, `Check_For_Update` effettua una richiesta `GET` all'endpoint `/releases/latest` dell'API di GitHub per il repository del progetto. La risposta, in formato JSON, viene analizzata con la libreria `nlohmann/json`. La versione più recente (`tag_name`) viene confrontata numericamente con la versione compilata dell'**ASI**. Se viene rilevata una nuova versione, viene visualizzata una finestra di dialogo (`MessageBoxW`), chiedendo all'utente se desidera accedere alla pagina dei download tramite `ShellExecuteW`. L'intero processo è incapsulato in un `try-catch` per garantire che eventuali errori di rete o di analisi non compromettano l'avvio del gioco.

#### Gestore Discord (`discord_manager.cpp`)

La classe `Discord_Manager` astrae le interazioni con la libreria **Discord RPC**, gestendo l'inizializzazione della connessione e l'invio dei dati per lo stato di presenza dell'utente.

- **`Initialize()`**: Configura la comunicazione con Discord.
   ```cpp
   // discord_manager.cpp (tratto chiave di Initialize)
   void Discord_Manager::Initialize() noexcept {
       DiscordEventHandlers handlers;
       memset(&handlers, 0, sizeof(handlers)); // Garantisce l'inizializzazione
       
       // App ID viene desoffuscato qui
       auto app_id_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_Discord_App_ID());
       Discord_Initialize(app_id_accessor.Get(), &handlers, 1, nullptr);
   
       start_timestamp_ = time(nullptr); // Registra l'inizio della sessione
   }
   ```
   La chiamata a `Discord_Initialize` è cruciale, utilizzando il `DISCORD_APP_ID` che viene ottenuto in modo sicuro tramite l'offuscamento delle stringhe in `secrets.hpp`. Il `start_timestamp_` viene definito qui per calcolare il tempo di gioco nella presenza di Discord.
- **`Update_Presence()`**: La funzione vitale che aggiorna la Rich Presence di Discord.
   ```cpp
   // discord_manager.cpp (tratto chiave di Update_Presence)
   void Discord_Manager::Update_Presence(const Server_Information& server_info, const server_types::Social_Link& social_link, const std::string_view player_name, const std::string_view current_image, const bool is_connected) noexcept {
       DiscordRichPresence discord_presence;
       memset(&discord_presence, 0, sizeof(discord_presence));
   
       discord_presence.startTimestamp = start_timestamp_;
       discord_presence.largeImageKey = current_image.data(); // Logo del server
   
       if (is_connected) {
           discord_presence.details = server_info.Hostname.c_str();
           discord_presence.state = player_name.data();
           discord_presence.largeImageText = server_info.Server_Address.c_str(); // IP:Porta
           discord_presence.partySize = server_info.Players;
           discord_presence.partyMax = server_info.Max_Players;
           discord_presence.joinSecret = server_info.Server_Address.c_str(); // Abilita il pulsante "Join"
   
           // Gestisce l'icona sociale rotante
           if (!social_link.first.empty()) {
               current_small_image_key_ = Constants::SOCIAL_ICON_BASE_URL;
               current_small_image_key_ += social_link.first; // Es: "discord.png"
               current_small_image_key_ += ".png";
               discord_presence.smallImageKey = current_small_image_key_.c_str();
               discord_presence.smallImageText = social_link.second.c_str(); // Testo al passaggio del mouse (link/nome)
           }
       }
       else {
           discord_presence.details = "SA-MP"; // Stato "Idle"
           discord_presence.state = "Idle";
           discord_presence.largeImageText = "San Andreas Multiplayer";
           // smallImageKey e smallImageText rimangono vuoti per lo stato idle
       }
   
       Discord_UpdatePresence(&discord_presence);
   }
   ```
   Compila la struttura `DiscordRichPresence` in base allo stato della connessione. Se `is_connected` è vero, vengono visualizzati l'hostname, il conteggio dei giocatori, l'IP del server e il nome del giocatore. Il `largeImageKey` definisce l'immagine principale del server. In particolare, `joinSecret` è impostato per consentire agli amici di connettersi direttamente, e il `smallImageKey` (costruito dinamicamente in base al `social_link` fornito) mostra le icone sociali rotanti. In stato "Idle", la presenza è semplificata per riflettere l'inattività. Infine, `Discord_UpdatePresence` invia i dati a Discord.

#### Gestore Server (`server_manager.cpp`)

Il `Server_Manager` è l'orchestratore dei dati, gestendo lo stato della connessione, consultando il server e l'**SPC Integration API**, e decidendo quali informazioni devono essere visualizzate e quando.

- **`Update()`**: Il ciclo di vita principale per la raccolta dei dati.
   ```cpp
   // server_manager.cpp (tratto chiave di Update)
   void Server_Manager::Update() {
       const auto now = std::chrono::steady_clock::now();
   
       if (server_query.Query(live_server_data)) { // Tenta di ottenere dati tramite query SAMP
           if (!connection_status) { // Se si è appena connesso/riconnesso
               connection_status = true;
               Fetch_API_Data(); // Recupera logo e social dall'API
           }
           
           last_successful_query = now;
   
           // Aggiorna i dati da visualizzare su Discord
           display_server_data.Hostname = live_server_data.Hostname;
           display_server_data.Players = live_server_data.Players;
           display_server_data.Max_Players = live_server_data.Max_Players;
           display_server_data.Server_Address = server_ip + ":" + std::to_string(server_port);
   
           if (now - last_api_update > Constants::IMAGE_UPDATE_INTERVAL)
               Fetch_API_Data(); // Ricontrolla l'API dopo il tempo definito
   
           if (now - last_social_rotation > Constants::SOCIAL_UPDATE_INTERVAL)
               Rotate_Social_Link(); // Ruota l'icona sociale
       }
       else { // Se la query è fallita
           if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
               connection_status = false; // Disconnesso dopo timeout
               display_image_url = Constants::DEFAULT_IMAGE;
               display_server_data = {}; // Pulisce i dati
               current_display_social = {}; // Pulisce il social
           }
       }
   }
   ```
   La funzione `Update` tenta di eseguire una query al server. Se ha successo, aggiorna i dati in `live_server_data` e `display_server_data`. Condizionalmente, chiama `Fetch_API_Data()` per aggiornare l'immagine e i link sociali (se è una nuova connessione o se è passato il `IMAGE_UPDATE_INTERVAL`) e `Rotate_Social_Link()` per alternare le icone sociali (`SOCIAL_UPDATE_INTERVAL`). Se le query al server falliscono costantemente per più di 15 secondi, lo stato della connessione viene considerato perso, reimpostando le informazioni visualizzate.
- **`Fetch_API_Data()`**: Responsabile per ottenere i dati visivi e sociali.
   ```cpp
   // server_manager.cpp (tratto chiave di Fetch_API_Data)
   void Server_Manager::Fetch_API_Data() {
       display_image_url = url_manager.Get_Image_URL_And_Populate_Socials(server_ip, server_port, live_server_data);
       last_api_update = std::chrono::steady_clock::now();
       current_social_index_ = 0; // Resetta l'indice dopo un nuovo fetch API
       Rotate_Social_Link(); // Garantisce che un'icona sociale sia visualizzata immediatamente
   }
   ```
   Questa funzione coordina con `URL_Manager` per recuperare il logo e i link sociali dall'API, aggiornando il `display_image_url` e popolando i `Social_Links` all'interno di `live_server_data`. Resetta l'indice di rotazione dei social e chiama `Rotate_Social_Link()` per garantire che la prima icona sia pronta per la visualizzazione.
- **`Rotate_Social_Link()`**: Logica per alternare le icone sociali.
   ```cpp
   // server_manager.cpp (tratto chiave di Rotate_Social_Link)
   void Server_Manager::Rotate_Social_Link() {
       if (!live_server_data.Social_Links.empty()) {
           if (current_social_index_ >= live_server_data.Social_Links.size())
               current_social_index_ = 0; // Riavvia il ciclo
   
           current_display_social = live_server_data.Social_Links[current_social_index_];
           current_social_index_ = (current_social_index_ + 1) % live_server_data.Social_Links.size();
       }
       else
           current_display_social = {}; // Pulisce se non ci sono social
       
       last_social_rotation = std::chrono::steady_clock::now();
   }
   ```
   Questa funzione semplice seleziona il prossimo `Social_Link` nella lista di `live_server_data.Social_Links` in modo ciclico e lo memorizza in `current_display_social` affinché il `Discord_Manager` possa utilizzarlo.

#### Sistema di Rete (`samp_network.cpp`)

La classe `Samp_Network` è l'implementazione di basso livello della comunicazione **UDP**, responsabile dell'apertura e della gestione del socket per le query SA-MP. Ora offre costruttori e operatori di movimento per una migliore gestione delle risorse.

- **`Initialize()`**: Configura il socket per la comunicazione **UDP**.
   ```cpp
   // samp_network.cpp (tratto chiave di Initialize)
   bool Samp_Network::Initialize(const std::string_view ip, const int port) noexcept {
       if (network_socket != INVALID_SOCKET)
           closesocket(network_socket); // Chiude il socket esistente
   
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       if (network_socket == INVALID_SOCKET)
           return false;
   
       const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
       setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
   
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(static_cast<u_short>(port));
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr); // Supporto per IP V4
       return true;
   }
   ```
   Inizializza il socket, definisce i timeout per le operazioni di invio e ricezione e configura la struttura dell'indirizzo (`sockaddr_in`) con l'IP e la porta del server di destinazione, utilizzando `inet_pton` per gestire la conversione dell'IP.
- **`Send_Query()`**: Invia un pacchetto di query e riceve la risposta.
   ```cpp
   // samp_network.cpp (tratto chiave di Send_Query)
   bool Samp_Network::Send_Query(const std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept {
       // Invia il pacchetto UDP
       if (sendto(network_socket, query_packet.data(), static_cast<int>(query_packet.size()), 0, reinterpret_cast<const sockaddr*>(&server_address), sizeof(server_address)) < 0)
           return false;
   
       sockaddr_in from_address;
       int address_length = sizeof(from_address);
       // Riceve la risposta
       received_bytes = recvfrom(network_socket, response_buffer.data(), static_cast<int>(response_buffer.size()), 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);
   
       return received_bytes > Constants::QUERY_PACKET_SIZE;
   }
   ```
   Questo metodo invia il `query_packet` (passato come `std::span` per la sicurezza del buffer) al server. Successivamente, tenta di ricevere una risposta nel `response_buffer`. Il ritorno indica se l'operazione è riuscita e se è stato ricevuto un numero di byte maggiore della dimensione del pacchetto di query.

#### Query al Server (`server_query.cpp`)

La classe `Server_Query` è dedicata all'implementazione del protocollo di query SA-MP (`'i'`), estraendo le informazioni di base del server (giocatori, hostname) dalle risposte **UDP**.

- **`Query()`**: Gestisce i tentativi di query.
   ```cpp
   // server_query.cpp (tratto chiave di Query)
   bool Server_Query::Query(Server_Information& server_data) noexcept {
       for (int attempt = 0; attempt < Constants::MAX_RETRY_ATTEMPTS; ++attempt) {
           if (Try_Query(server_data))
               return true; // Successo nella query
   
           if (attempt < Constants::MAX_RETRY_ATTEMPTS - 1)
               // Breve pausa prima di riprovare, per evitare il flooding
               std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)));
       }

       return false; // Tutti i tentativi sono falliti
   }
   ```
   Implementa la strategia di *retry* con `MAX_RETRY_ATTEMPTS` e un *back-off* di tempo crescente, per garantire che le query siano robuste e evitino di saturare la rete. Chiama `Try_Query` a ogni tentativo.
- **`Assemble_Query_Packet()`**: Costruisce il pacchetto di query SA-MP.
   ```cpp
   // server_query.cpp (tratto chiave di Assemble_Query_Packet)
   void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
       memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
       packet = 'i'; // Codice della query di informazioni
   }
   ```
   Il pacchetto standard per la query di informazioni (`'i'`) di SA-MP viene costruito, includendo la firma "SAMP" e il byte identificatore 'i'.
- **`Parse_Response()`**: Decodifica la risposta binaria del server.
   ```cpp
   // server_query.cpp (tratto chiave di Parse_Response)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       if (response.size() <= Constants::QUERY_PACKET_SIZE) 
           return false;
   
       auto data_span = response.subspan(Constants::QUERY_PACKET_SIZE); // Salta l'intestazione
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Ignorato, ma letto
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false;

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false;

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false;
   
       // Nota: Gamemode e Language vengono automaticamente saltati da Read_String_From_Span se il pacchetto contiene più dati.
       // Se hai bisogno degli altri campi, basta creare una stringa e chiamare: Read_String_From_Span(data_span, string_variable);
       return true;
   }
   ```
   Questo metodo legge in modo sicuro i dati dal `response_buffer` (utilizzando `std::span` e le funzioni ausiliarie `Read_From_Span` e `Read_String_From_Span`). Estrae il numero di giocatori, il massimo di giocatori e l'hostname del server, popolando la struttura `Server_Information`. I campi non utilizzati (come se il server è protetto da password) vengono letti ma ignorati, e altri come "gamemode" e "language" vengono "saltati" se la risposta contiene più dati di quelli necessari all'**ASI** in quel momento.
- **Funzioni di lettura ausiliarie:**
   ```cpp
   // server_query.hpp (frammenti delle funzioni ausiliarie di lettura)
   template<typename T>
   static bool Read_From_Span(std::span<const char>& s, T& value) noexcept;
   
   static bool Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept;
   ```
   `Read_From_Span` gestisce la lettura di tipi fissi (interi, booleani) dal `std::span` e avanza il `span`. `Read_String_From_Span` legge la lunghezza di una stringa (come `uint32_t`) e poi la stringa stessa, avanzando anche il `span`. Ciò garantisce la sicurezza nel parsing dei byte e impedisce letture oltre i limiti del buffer.

#### Gestore URL (`url_manager.cpp`)

La classe `URL_Manager` gestisce le comunicazioni HTTPS con l'**SPC Integration API**, un elemento centrale per le nuove funzionalità visive e sociali del **Discord Rich Presence**.

- **`Get_Image_URL_And_Populate_Socials()`**: Il metodo di alto livello per recuperare le informazioni dall'API.
   ```cpp
   // url_manager.cpp (tratto chiave di Get_Image_URL_And_Populate_Socials)
   std::string URL_Manager::Get_Image_URL_And_Populate_Socials(const std::string& ip, const int port, Server_Information& server_info) {
       if (!session_handle)
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);
   
       auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
       std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
       path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   
       const std::string json_data = Request_API_Data(path); // Richiesta HTTP per l'API
   
       if (json_data.empty())
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE); // Errore nella richiesta
   
       return Parse_API_Response(json_data, server_info); // Analizza e popola server_info
   }
   ```
   Riceve IP e porta, costruisce l'URL dell'API includendoli come parametri. Chiama `Request_API_Data` per recuperare i dati JSON. In caso di successo, `Parse_API_Response` viene chiamata per estrarre l'URL dell'immagine (logo) e popolare la lista di link sociali in `server_info`.
- **`Request_API_Data()`**: Esegue la richiesta HTTPS per l'API.
   ```cpp
   // url_manager.cpp (tratto chiave di Request_API_Data)
   std::string URL_Manager::Request_API_Data(const std::wstring& path) {
       auto api_host_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Host());
       const std::wstring wide_host = Utils::Convert_Utf8_To_Wide_String(api_host_accessor.Get());
       HINTERNET connect_handle = WinHttpConnect(session_handle, wide_host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
   
       if (!connect_handle) return "";
   
       HINTERNET request_handle = WinHttpOpenRequest(connect_handle, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
   
       if (!request_handle) return (WinHttpCloseHandle(connect_handle), "");
   
       // Invia richiesta, riceve risposta, verifica stato 200, legge dati in loop
       // ... (dettagli della chiamata WinHttpSendRequest, WinHttpReceiveResponse, WinHttpQueryHeaders, WinHttpReadData) ...
       
       WinHttpCloseHandle(request_handle); WinHttpCloseHandle(connect_handle);
       return response_body; // Restituisce il JSON come stringa
   }
   ```
   Si connette all'host dell'API (ottenuto in modo offuscato), apre e invia una richiesta `GET` con il percorso (`path`). Gestisce la risposta HTTP, verifica il codice di stato (200 OK per il successo) e legge il corpo completo della risposta (che deve essere JSON). Tutti gli handle WinHTTP vengono liberati in caso di successo o fallimento.
- **`Parse_API_Response()`**: Elabora la stringa JSON per estrarre i dati.
   ```cpp
   // url_manager.cpp (tratto chiave di Parse_API_Response)
   std::string URL_Manager::Parse_API_Response(const std::string& json_content, Server_Information& server_info) {
       server_info.Social_Links.clear(); // Pulisce i link sociali esistenti
       try {
           const auto json = nlohmann::json::parse(json_content);
   
           if (json.value("success", false) && json.contains("data") && json["data"].contains("public")) {
               const auto& public_data = json["data"]["public"];
               const std::vector<std::string> social_keys = { "website", "discord", "youtube", "instagram", "facebook", "tiktok" };
               
               // Estrae e popola i link sociali
               for (const auto& key : social_keys) {
                   if (public_data.contains(key)) {
                       std::string value = public_data.value(key, "not-defined");

                       if (!value.empty() && value != "not-defined")
                           server_info.Social_Links.push_back({ key, value });
                   }
               }

               return public_data.value("logo", ""); // Restituisce l'URL del logo
           }
       }
       catch (const nlohmann::json::exception&) { /* Gestisce l'errore di parsing */ }

       return ""; // Fallimento nel parsing
   }
   ```
   Utilizza `nlohmann::json::parse` per convertire la stringa JSON in un oggetto JSON manipolabile. Naviga nella struttura (`success`, `data`, `public`) ed estrae il `logo` (che diventa il `display_image_url`) e itera sulle chiavi predefinite per trovare e popolare i `Social_Links` di `server_info`.

### Struttura del Codice

Il progetto **SA-MP Rich Presence** è organizzato con cura in una struttura di directory chiara, con il codice sorgente (`src/`) e una sottodirectory per le librerie esterne (`libraries/`). La nomenclatura dei file segue la convenzione `_manager` o `_network` per chiarezza sullo scopo di ogni classe. La maggior parte dei file di intestazione utilizza l'estensione `.hpp`, indicando che sono file di intestazione C++.

```
src/
├── libraries/               # Contiene librerie di terze parti essenziali
│   ├── Dralyxor/            # Libreria di offuscamento delle stringhe
│   ├── Discord/             # Libreria ufficiale di Discord RPC
│   └── nlohmann/            # Libreria per la manipolazione di JSON
├── asi_update.hpp           # Definizione del sistema di aggiornamento automatico
├── command_line_parser.hpp  # Definizione del parser della riga di comando
├── constants.hpp            # Definizioni delle costanti globali del progetto
├── discord_manager.hpp      # Definizione del gestore della comunicazione con Discord
├── main.cpp                 # Punto di ingresso dell'ASI e orchestratore principale
├── samp_network.hpp         # Definizione del gestore di rete per le query SA-MP
├── secrets.hpp              # Definizioni per l'offuscamento dei segreti
├── server_manager.hpp       # Definizione del gestore delle informazioni del server
├── server_query.hpp         # Definizione della logica di query al server SA-MP
├── server_types.hpp         # Definizioni delle strutture di dati del server
├── url_manager.hpp          # Definizione del gestore URL per l'SPC Integration API
└── utils.hpp                # Funzioni di utilità generali (conversione di stringhe)
```

#### Costanti Globali (`constants.hpp`)

Questo file concentra tutte le configurazioni e i valori immutabili del progetto, accessibili globalmente. Utilizza `inline constexpr` per garantire che le costanti siano direttamente disponibili per il compilatore, ottimizzando le prestazioni.

```cpp
// constants.hpp (tratto)
namespace Constants {
    inline constexpr char ASI_VERSION[] = "1.1"; // Versione per il sistema di aggiornamento
    inline constexpr wchar_t UPDATE_API_HOST[] = L"api.github.com"; // Host dell'API di aggiornamento
    inline constexpr char DEFAULT_IMAGE[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/default_logo.png"; // Immagine predefinita
    inline constexpr int QUERY_TIMEOUT_MS = 800; // Timeout della query in ms
    inline constexpr std::chrono::seconds MAIN_LOOP_INTERVAL = std::chrono::seconds(1); // Intervallo del loop principale
}
```
Dettagli importanti come gli URL dell'API, i percorsi delle immagini predefinite, i tempi limite di rete e gli intervalli di aggiornamento del **Discord Rich Presence** sono centralizzati qui. L'uso di `std::chrono::seconds` per gli intervalli migliora la leggibilità e previene errori di unità.

#### Strutture di Dati (`server_types.hpp`)

Questo file definisce gli `struct` e gli `using` importanti per organizzare i dati raccolti e visualizzati.

```cpp
// server_types.hpp (tratto)
namespace server_types {
    using Social_Link = std::pair<std::string, std::string>; // Tupla (nome del social, URL/valore)
}

struct Server_Information {
    uint16_t Players{0};           // Numero di giocatori attuali
    uint16_t Max_Players{0};       // Capacità massima di giocatori
    std::string Hostname{};        // Nome del server
    std::string Server_Address{};  // Es: "192.168.1.1:7777"

    std::vector<server_types::Social_Link> Social_Links{}; // Lista di link sociali del server
};
```
La struttura `Server_Information` è la struttura primaria che memorizza i dati del server. L'aggiunta di `std::vector<server_types::Social_Link> Social_Links` riflette la nuova capacità di recuperare più link di social media dall'API, organizzati come coppie `(nome_rete, link)`.

#### Offuscamento dei Segreti (`secrets.hpp`)

Questo file è dedicato alla protezione di informazioni sensibili, come il **Discord Application ID** e gli indirizzi dell'**SPC Integration API (per ora)**, da un reverse engineering facile.

```cpp
// secrets.hpp (tratto)
#include "libraries/Dralyxor/dralyxor.hpp"

namespace Secrets {
    namespace {
        inline auto& Get_Obfuscated_Discord_App_ID() {
            static auto& dc_app_id_obfuscated = DRALYXOR_KEY("DISCORD_APP_ID", "YOUR_SECRET_KEY_HERE");

            return dc_app_id_obfuscated;
        }
        // ... (altri segreti offuscati) ...
    }
    namespace Detail {
        inline auto& Get_Discord_App_ID() {
            return Get_Obfuscated_Discord_App_ID();
        }
        // ... (getter pubblici per accedere ai segreti desoffuscati) ...
    }
}
```
La libreria [Dralyxor](https://github.com/ocalasans/dralyxor) viene utilizzata con la macro `DRALYXOR_KEY` per criptare le stringhe letterali nel binario compilato. `DRALYXOR_SECURE` viene poi utilizzata in runtime per desoffuscare questi valori quando sono necessari, aggiungendo un robusto livello di sicurezza contro l'estrazione statica delle chiavi.

#### Utilità Generali (`utils.hpp`)

Un file per le funzioni ausiliarie generiche che possono essere utili in vari moduli, evitando la duplicazione del codice.

```cpp
// utils.hpp (tratto)
namespace Utils {
    inline std::string Convert_Wide_To_Utf8_String(const std::wstring_view wide_string) {
        // ... (implementazione della conversione usando WideCharToMultiByte) ...
    }

    inline std::wstring Convert_Utf8_To_Wide_String(const std::string_view narrow_string) {
        // ... (implementazione della conversione usando MultiByteToWideChar) ...
    }
}
```
Contiene le funzioni `Convert_Wide_To_Utf8_String` e `Convert_Utf8_To_Wide_String`, essenziali per le interazioni con le API di Windows (che usano UTF-16) e le operazioni standard di C++ (che generalmente beneficiano dell'UTF-8). Queste funzioni utilizzano le API di Windows per una conversione sicura ed efficiente.

### Gestione degli Errori e Resilienza

Il **SA-MP Rich Presence** è stato progettato con la resilienza in mente, incorporando molteplici meccanismi per gestire errori di rete, input non validi e indisponibilità dei servizi.

- **Timeout e Riprove di Rete:**
   - **Timeout Espliciti:** I socket di rete in `samp_network.cpp` configurano i timeout (`Constants::QUERY_TIMEOUT_MS`) sia per l'invio che per la ricezione dei dati, prevenendo che il programma rimanga "bloccato" in attesa di una risposta da un server inattivo.
      ```cpp
      // samp_network.cpp (configurazione del timeout)
      const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
      setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      ```
   - **Riprove Multiple di Query:** Il `Server_Query` esegue `Constants::MAX_RETRY_ATTEMPTS` query in caso di fallimento. Un *back-off* esponenziale viene implementato (`std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)))`) per attendere prima di nuovi tentativi, riducendo il carico e aumentando le possibilità di successo in condizioni di rete instabili.
- **Gestione Robusta della Disconnessione:**
   - **Transizione di Stato Graduale:** In `server_manager.cpp`, lo stato di connessione (`connection_status`) non viene modificato immediatamente dopo un singolo fallimento di query. Solo se non viene ricevuta alcuna risposta per 15 secondi consecutivi (`now - last_successful_query > std::chrono::seconds(15)`), lo stato viene aggiornato a `false`. Ciò evita il "lampeggio" della presenza su Discord a causa di piccole perdite di pacchetti.
      ```cpp
      // server_manager.cpp (logica di disconnessione)
      else { // Se la query è fallita
          if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
              connection_status = false;
              display_image_url = Constants::DEFAULT_IMAGE;
              display_server_data = {};
              current_display_social = {};
          }
      }
      ```
   - **Fallback Visivo:** Quando viene rilevata una disconnessione, l'immagine della presenza su Discord torna a `Constants::DEFAULT_IMAGE`, e i dati del server/social vengono puliti, fornendo un feedback chiaro all'utente che non è più connesso.
- **Gestione degli Input Non Validi:**
   - **`command_line_parser.cpp`:** Durante la conversione dell'argomento della porta da stringa a intero (`std::stoi`), viene utilizzato un blocco `try-catch` per gestire `std::invalid_argument` (non è un numero) o `std::out_of_range` (numero troppo grande/piccolo). In caso di errore, viene mantenuta la porta predefinita o il parsing fallisce in modo controllato, prevenendo crash.
- **Resilienza nell'Ottenimento dei Dati dall'API:**
   - **Fallimenti di WinHTTP:** Tutte le operazioni dell'API WinHTTP in `url_manager.cpp` vengono verificate per handle `null` e ritorni `false` in ogni fase (apertura della sessione, connessione, apertura della richiesta, invio/ricezione, lettura dei dati), garantendo che i fallimenti parziali vengano catturati.
   - **Codici di Stato HTTP:** Dopo una richiesta HTTP, `url_manager.cpp` verifica il `HTTP Status Code`. Solo un codice `200 OK` viene accettato come successo, scartando le risposte di errore del server o del gateway.
   - **Parsing JSON Sicuro:** `url_manager.cpp` avvolge il parsing JSON (`nlohmann::json::parse`) in un blocco `try-catch(const nlohmann::json::exception&)`. Ciò impedisce che JSON malformati o incompleti provenienti dall'API causino un crash, restituendo stringhe vuote o l'immagine predefinita.
- **Meccanismi di Aggiornamento Sicuri:**
   - **`asi_update.hpp`:** Il processo di verifica degli aggiornamenti in `Check_For_Update` è incapsulato in un blocco `try-catch(const std::exception&)`. Ciò garantisce che, anche se GitHub è offline, la rete è instabile o la risposta JSON è non valida, l'**ASI** non crashi e il gioco possa continuare a essere caricato, ignorando la verifica degli aggiornamenti in modo sicuro.
   - **Gestione degli Handle WinHTTP:** La liberazione degli handle `HINTERNET` in `asi_update.hpp` e `url_manager.cpp` è pianificata con cura per essere eseguita in tutti i percorsi di codice (successo e fallimento), prevenendo perdite di risorse.

### Sistema di Elaborazione della Riga di Comando

Il **SA-MP Rich Presence** estrae informazioni cruciali per il suo funzionamento (IP del server, porta e nome del giocatore) direttamente dalla riga di comando del gioco Grand Theft Auto: San Andreas. Questo metodo garantisce che l'**ASI** ottenga i dati più precisi e rilevanti non appena il gioco viene avviato o viene connesso un server.

#### Parser della Riga di Comando (`command_line_parser.cpp`)

La classe `Command_Line_Parser` è responsabile dell'analisi della stringa di comando completa del processo, identificando ed estraendo i parametri specifici utilizzati da SA-MP.

- **`Parse()`**: Il punto di ingresso per l'analisi della riga di comando.
   ```cpp
   // command_line_parser.cpp (tratto chiave di Parse)
   bool Command_Line_Parser::Parse(const std::wstring_view command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       server_ip = Constants::DEFAULT_SERVER_IP; // Valori predefiniti
       server_port = Constants::DEFAULT_SERVER_PORT;
   
       if (const auto ip_param = Parse_Parameter(command_line, L"-h"); !ip_param.empty())
           server_ip = Utils::Convert_Wide_To_Utf8_String(ip_param); // Estrae e converte l'IP
   
       if (const auto port_param = Parse_Parameter(command_line, L"-p"); !port_param.empty()) {
           try {
               server_port = std::stoi(std::wstring(port_param)); // Estrae e converte la porta (con gestione degli errori)
           }
           catch (const std::invalid_argument&) {}
           catch (const std::out_of_range&) {}
       }
   
       if (const auto name_param = Parse_Parameter(command_line, L"-n"); !name_param.empty())
           player_name = Utils::Convert_Wide_To_Utf8_String(name_param); // Estrae e converte il nome
   
       return !server_ip.empty() && server_port > 0 && !player_name.empty(); // Valida se i dati essenziali sono presenti
   }
   ```
   Riceve la riga di comando (`command_line`) come `std::wstring_view` per efficienza. Utilizza `Parse_Parameter` per trovare ed estrarre i valori associati a `-h` (host/IP), `-p` (porta) e `-n` (nome del giocatore). I valori estratti (in `std::wstring_view`) vengono convertiti in `std::string` (UTF-8) utilizzando `Utils::Convert_Wide_To_Utf8_String`. Per la porta, un blocco `try-catch` avvolge `std::stoi` per gestire eventuali errori di conversione in modo sicuro. La funzione restituisce `true` se tutti i parametri cruciali (IP, porta valida e nome del giocatore) vengono ottenuti.
- **`Parse_Parameter()`**: La funzione ausiliaria per l'estrazione di un singolo parametro.
   ```cpp
   // command_line_parser.cpp (tratto chiave di Parse_Parameter)
   std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring_view command_string, const std::wstring_view parameter) {
       if (const size_t position = command_string.find(parameter); position != std::wstring_view::npos) {
           size_t value_start = position + parameter.length();
           value_start = command_string.find_first_not_of(L" \t", value_start); // Salta gli spazi dopo il parametro

           if (value_start == std::wstring_view::npos)
               return L""; // Parametro trovato ma senza valore
   
           const size_t value_end = command_string.find(L' ', value_start); // Trova il prossimo spazio (fine del valore)
           
           return std::wstring(command_string.substr(value_start, value_end - value_start)); // Restituisce la sottostringa del valore
       }

       return L""; // Parametro non trovato
   }
   ```
   Localizza la sottostringa del `parameter` (`-h`, `-p`, `-n`) nella `command_string`. Calcola la posizione iniziale del valore, ignorando spazi/tab. Identifica la posizione finale del valore (prossimo spazio) e restituisce la sottostringa corrispondente al valore del parametro.

### Protocollo di Comunicazione SA-MP

L'**ASI** interagisce direttamente con i server SA-MP utilizzando il protocollo di query **UDP** per estrarre informazioni vitali in tempo reale. Questa comunicazione è implementata per essere efficiente e resiliente agli errori di rete.

#### Implementazione del Protocollo

La classe `Server_Query` è la spina dorsale di questa implementazione, gestendo l'invio dei pacchetti e l'interpretazione delle risposte.

- **Struttura del Pacchetto di Query SA-MP (`'i'`)**: L'**ASI** costruisce un pacchetto **UDP** di 11 byte per la query di informazioni:
   - `BYTE 0-3`: Firma "SAMP" (S A M P).
   - `BYTE 4-9`: Sequenza di 6 byte arbitrari (generalmente l'indirizzo IP di origine della richiesta per il riconoscimento del cliente da parte del server).
   - `BYTE 10`: Identificatore della query 'i' (ASCII 105), che indica che l'**ASI** desidera informazioni generali del server (hostname, giocatori, ecc.).
      ```cpp
      // server_query.cpp (montaggio del pacchetto)
      void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
          memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
          packet = 'i'; // Query di informazioni (Information)
      }
      ```
- **Struttura della Risposta del Server**: Quando un server SA-MP risponde a una query 'i', invia un pacchetto **UDP** contenente una sequenza di dati strutturati, che l'**ASI** deve analizzare:
   - **Intestazione della Risposta:** Ripetizione della firma "SAMP" e della sequenza di 6 byte del pacchetto di richiesta. L'**ASI** semplicemente salta questi `Constants::QUERY_PACKET_SIZE` byte iniziali.
   - **Passworded (`bool`):** Un byte che indica se il server è protetto da password. Letto, ma non usato.
   - **Players (`uint16_t`):** Il numero di giocatori attualmente connessi al server.
   - **Max_Players (`uint16_t`):** Il numero massimo di slot di giocatori che il server supporta.
   - **Hostname (stringa prefissata da `uint32_t`):** Il nome amichevole del server. Il pacchetto include un `uint32_t` per indicare la lunghezza della stringa di hostname, seguito dai byte della stringa reale.
   - **Altri Campi:** Il protocollo SAMP continua con "gamemode" e "language", anch'essi prefissati dalla lunghezza. L'**ASI** legge e salta questi campi per concentrarsi sui dati essenziali di `Players`, `Max_Players` e `Hostname`.

   La lettura di questi campi viene effettuata con le funzioni ausiliarie `Read_From_Span` e `Read_String_From_Span`, che garantiscono che l'**ASI** non legga byte oltre il limite del buffer e gestisca correttamente la lettura di tipi di dati a lunghezza fissa e variabile (stringhe).
   ```cpp
   // server_query.cpp (parsing della risposta)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       // ... (Verifica della dimensione e subspan per i dati) ...
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Legge il booleano 'passworded'
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false; // Legge 'Players'

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false; // Legge 'Max_Players'

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false; // Legge 'Hostname'
   
       // Campi 'Gamemode' e 'Language' vengono implicitamente "saltati"
       // dalla successiva chiamata di Read_String_From_Span
       // per spostare lo span oltre i loro dati nel buffer.
       uint32_t length_placeholder; // Variabile temporanea per contenere la lunghezza.

       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Legge la lunghezza del gamemode

       if (data_span.size() < length_placeholder)
           return false; // Verifica i limiti

       data_span = data_span.subspan(length_placeholder); // Salta i dati del gamemode
   
       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Legge la lunghezza del language

       if (data_span.size() < length_placeholder)
           return false; // Verifica i limiti

       data_span = data_span.subspan(length_placeholder); // Salta i dati del language
   
       return true;
   }
   ```
   Nel esempio sopra, la logica `data_span = data_span.subspan(length_placeholder);` è un modo efficiente per "saltare" il numero di byte letti da una stringa il cui contenuto non è necessario per il Rich Presence.

### Benefici del SA-MP Rich Presence

Il SA-MP Rich Presence migliora significativamente l'esperienza sia per i giocatori che per gli amministratori dei server, offrendo vantaggi notevoli:

1. **Per i Giocatori:**
   - **Visibilità Senza Sforzo:** Condividi automaticamente il tuo stato di gioco su Discord con gli amici, mostrando esattamente dove stai giocando.
   - **Informazioni Ricche:** Accedi immediatamente ai dettagli del server (nome, conteggio dei giocatori, IP, logo personalizzato) direttamente su Discord, eliminando la necessità di verificare queste informazioni altrove.
   - **Accesso Diretto alla Comunità:** Scopri e accedi rapidamente ai social media del server attraverso le icone rotanti nella presenza di Discord, facilitando l'ingresso in comunità vivaci.
   - **Connessione Rapida con gli Amici:** Invita o unisciti allo stesso server dei tuoi amici con un clic, grazie alla funzionalità del pulsante "Join".
   - **Esperienza Sempre Attiva:** Il sistema di aggiornamento automatico garantisce che utilizzi sempre la versione più ottimizzata e funzionale dell'**ASI**.
2. **Per i Server:**
   - **Marketing Virale Naturale:** La presenza su Discord dei tuoi giocatori funge da cartellone digitale, promuovendo il tuo server a un pubblico organico (gli amici dei giocatori) 24 ore al giorno.
   - **Identità Visiva Forte:** Un logo personalizzato e la rotazione dei link sociali consentono al tuo server di distinguersi e proiettare un'immagine professionale e moderna nell'ambiente Discord.
   - **Engagement Aumentato:** Facilita il percorso affinché nuovi e vecchi giocatori si connettano con le tue piattaforme sociali, rafforzando la tua comunità e l'engagement fuori dal gioco.
   - **Reclutamento Facilitato:** La funzione "Join" semplifica il processo per i nuovi giocatori, eliminando le barriere e incoraggiando la sperimentazione.
   - **Dati Coerenti:** Attraverso l'integrazione con l'**SPC Integration API**, la visualizzazione delle informazioni è unificata e aggiornata centralmente, garantendo che il marchio e i contatti del tuo server siano sempre corretti.

## Licenza

Questo ASI è protetto sotto la Licenza Apache 2.0, che permette:

- ✔️ Uso commerciale e privato
- ✔️ Modifica del codice sorgente
- ✔️ Distribuzione del codice
- ✔️ Concessione di brevetti

### Condizioni:

- Mantenere l'avviso di copyright
- Documentare le modifiche significative
- Includere una copia della licenza Apache 2.0

Per maggiori dettagli sulla licenza: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Tutti i diritti riservati**