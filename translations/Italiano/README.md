# SA-MP Rich Presence

SA-MP Rich Presence è un ASI per SA-MP (San Andreas Multiplayer) che aggiorna automaticamente il tuo stato Discord con informazioni dettagliate del server. L'ASI viene iniettato nel gioco quando ti connetti a un server SA-MP, mostrando le informazioni del server.

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
  - [Cos'è un ASI?](#cosè-un-asi)
  - [Funzionalità](#funzionalità)
    - [Discord Rich Presence](#discord-rich-presence)
  - [Requisiti](#requisiti)
  - [Installazione](#installazione)
  - [Architettura Tecnica Dettagliata](#architettura-tecnica-dettagliata)
    - [Sistema Principale (main.cpp)](#sistema-principale-maincpp)
    - [Gestore Discord (discord\_manager.cpp)](#gestore-discord-discord_managercpp)
    - [Gestore Server (server\_manager.cpp)](#gestore-server-server_managercpp)
    - [Sistema di Rete (network\_manager.cpp)](#sistema-di-rete-network_managercpp)
    - [Query Server (server\_query.cpp)](#query-server-server_querycpp)
  - [Integrazione con SPC](#integrazione-con-spc)
    - [Cos'è SPC Integration?](#cosè-spc-integration)
    - [Come Funziona](#come-funziona)
    - [Gestore URL (url\_manager.cpp)](#gestore-url-url_managercpp)
  - [Per gli Sviluppatori di Server](#per-gli-sviluppatori-di-server)
  - [Struttura del Codice](#struttura-del-codice)
    - [Costanti Globali (constants.h)](#costanti-globali-constantsh)
    - [Strutture Dati (server\_types.h)](#strutture-dati-server_typesh)
  - [Gestione degli Errori](#gestione-degli-errori)
  - [Sistema di Elaborazione della Riga di Comando](#sistema-di-elaborazione-della-riga-di-comando)
    - [Parser della Riga di Comando (command\_line\_parser.cpp)](#parser-della-riga-di-comando-command_line_parsercpp)
  - [Protocollo di Comunicazione SA-MP](#protocollo-di-comunicazione-sa-mp)
    - [Implementazione del Protocollo](#implementazione-del-protocollo)
  - [Vantaggi di SA-MP Rich Presence](#vantaggi-di-sa-mp-rich-presence)
  - [Note Tecniche Aggiuntive](#note-tecniche-aggiuntive)

## Cos'è un ASI?

ASI è una libreria dinamica (.dll) rinominata con estensione .asi che viene caricata automaticamente da un loader ASI quando GTA San Andreas viene avviato. I plugin ASI permettono di modificare o aggiungere funzionalità al gioco senza alterare i file originali, essendo una delle forme più popolari di modding per GTA San Andreas e altri giochi della serie GTA. Con un ASI loader installato, puoi facilmente installare o rimuovere modifiche semplicemente aggiungendo o rimuovendo file .asi dalla cartella del gioco.

## Funzionalità

### Discord Rich Presence

Discord Rich Presence è una funzionalità che permette alle applicazioni di mostrare informazioni dettagliate su ciò che l'utente sta facendo direttamente nel profilo Discord. Nel caso di SA-MP Rich Presence, vengono mostrate le seguenti informazioni:
- Nome del server (Hostname)
- Nome del giocatore
- Numero attuale di giocatori e numero massimo di giocatori
- IP e porta del server
- Immagine personalizzata del server (richiede che il server abbia il plugin [SPC Integration](https://github.com/spc-samp/spc-integration))
- Tempo di gioco
- Stato della connessione

## Requisiti

- Client SA-MP (se non ce l'hai: [clients-samp](https://github.com/spc-samp/clients-samp))
- Applicazione Discord Desktop
- Sistema Operativo Windows
- Visual C++ Runtime
- ASI Loader installato in GTA San Andreas

## Installazione

1. Scarica la versione più recente dell'ASI compilato da [releases](https://github.com/ocalasans/samp-rich-presence/releases)
2. Assicurati di avere un ASI Loader installato nel tuo GTA San Andreas
3. Copia il file .asi scaricato nella cartella del tuo GTA San Andreas
4. Avvia il gioco con SA-MP
5. L'ASI verrà automaticamente inizializzato quando entri in un server

## Architettura Tecnica Dettagliata

### Sistema Principale (main.cpp)

Il file main.cpp è il punto di ingresso dell'ASI ed è responsabile di:
1. Inizializzazione del sistema:
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

2. Gestione del thread di aggiornamento:
   ```cpp
   DWORD WINAPI Update_Thread(LPVOID) {
       // Inizializza WSA per operazioni di rete
       WSAData wsa_data;
       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
       
       // Elabora parametri della riga di comando
       std::string server_ip, player_name;
       int server_port;
       
       // Inizializza gestori
       Global_Server_Manager = std::make_unique<Server_Manager>(server_ip, server_port, player_name);
       Global_Discord_Manager = std::make_unique<Discord_Manager>();
       
       // Loop principale di aggiornamento
       while (true) {
           Global_Server_Manager->Update();
           Global_Discord_Manager->Update_Presence(...);
           Sleep(Constants::PRESENCE_UPDATE_INTERVAL);
       }
   }
   ```

### Gestore Discord (discord_manager.cpp)

Il Discord_Manager è responsabile di tutta l'integrazione con Discord Rich Presence:
1. Inizializzazione di Discord RPC:
   ```cpp
   void Discord_Manager::Initialize() noexcept {
       Sleep(5000);  // Attende l'inizializzazione di Discord
       
       DiscordEventHandlers discord_handlers{};
       Discord_Initialize("DISCORD_APP_ID", &discord_handlers, 1, NULL); // "DISCORD_APP_ID > Application ID"
       
       start_timestamp = time(nullptr);  // Marca l'inizio della sessione
   }
   ```

2. Aggiornamento della presenza:
   ```cpp
   void Discord_Manager::Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept {
       DiscordRichPresence discord_presence{};
       
       // Configura informazioni di base
       discord_presence.state = player_name.data();
       discord_presence.details = server_info.Hostname.c_str();
       discord_presence.largeImageKey = current_image.data();
       
       // Aggiunge informazioni del server
       discord_presence.largeImageText = server_info.Server_Address.c_str();
       discord_presence.startTimestamp = start_timestamp;
       discord_presence.partySize = server_info.Players;
       discord_presence.partyMax = server_info.Max_Players;
       
       Discord_UpdatePresence(&discord_presence);
   }
   ```

### Gestore Server (server_manager.cpp)

Il Server_Manager coordina tutte le operazioni relative al server:
1. Gestione dello stato:
   ```cpp
   Server_Manager::Server_Manager(const std::string& ip, int port, const std::string& name)
       : connection_status(false)
       , server_ip(ip)
       , server_port(port)
       , player_name(name)
       , current_image_url(Constants::DEFAULT_IMAGE)
   {}
   ```

2. Aggiornamento delle informazioni:
   ```cpp
   bool Server_Manager::Update() {
       bool query_success = server_query.Query(server_data);
       
       if (query_success) {
           connection_status = true;
           server_data.Server_Address = Get_Server_Address();
           
           // Tenta di ottenere l'immagine personalizzata del server
           std::string new_image_url = url_manager.Get_Image_URL(server_data.Server_Address);

           if (!new_image_url.empty())
               current_image_url = new_image_url;
       }
       // ...
   }
   ```

### Sistema di Rete (network_manager.cpp)

Il Network_Manager implementa tutta la comunicazione di rete:
1. Inizializzazione del socket:
   ```cpp
   bool Network_Manager::Initialize(std::string_view ip, int port) noexcept {
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       
       // Configura timeout
       timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
       
       // Configura indirizzo del server
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(port);
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr);
       
       return true;
   }
   ```

### Query Server (server_query.cpp)

Il Server_Query implementa il protocollo di query di SA-MP:
1. Assemblaggio del pacchetto di query:
   ```cpp
   bool Server_Query::Assemble_Query_Packet(char* packet) noexcept {
       memcpy(packet, QUERY_SIGNATURE, 4);  // "SAMP"
       packet[10] = 'i';  // Query informazioni

       return true;
   }
   ```

2. Elaborazione della risposta:
   ```cpp
   bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
       // Estrae informazioni come:
       // - Numero di giocatori
       // - Massimo di giocatori
       // - Hostname
   }
   ```

## Integrazione con SPC

### Cos'è SPC Integration?

[SPC Integration](https://github.com/spc-samp/spc-integration) è un plugin sviluppato per **SA-MP** (San Andreas Multiplayer) e **open.mp** (Open Multiplayer) che funge da ponte tra i server e l'ecosistema **SPC**. Il plugin raccoglie informazioni cruciali del server, tra cui:
- IP e porta
- URL del sito del server
- URL dell'immagine personalizzata
- Informazioni di configurazione

Queste informazioni vengono inviate e memorizzate in modo sicuro nell'archivio dati di **SPC (SA-MP Programming Community)**, permettendo un'integrazione con varie applicazioni SPC, incluso il Rich Presence.

### Come Funziona

1. Il server utilizza il plugin [SPC Integration](https://github.com/spc-samp/spc-integration) per registrare la sua immagine personalizzata
2. L'immagine viene memorizzata nell'archivio dati SPC all'interno del file JSON del server
3. Quando un giocatore si connette al server:
    - L'URL_Manager dell'ASI tenta di recuperare il file JSON del server (formato: `ip-port.json`)
    - Se trovato, estrae l'URL dell'immagine dal parametro `spc_integration_image`
    - L'immagine viene quindi mostrata nel Discord Rich Presence del giocatore

### Gestore URL (url_manager.cpp)

L'URL_Manager è responsabile di tutta la comunicazione con l'archivio dati SPC:
1. Ricerca dell'immagine del server:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       std::string formatted_address = server_address;
       // Converte ":" in "-" nell'indirizzo
       size_t colon_pos = formatted_address.find(':');

       if (colon_pos != std::string::npos)
           formatted_address.replace(colon_pos, 1, "-");
       
       // Recupera JSON del server
       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;
       
       return image_url;
   }
   ```

2. Elaborazione del JSON:
   ```cpp
   std::string URL_Manager::Parse_JSON(const std::string& json_content) {
       const std::string key = "\"spc_integration_image\":";
       size_t key_pos = json_content.find(key);
       
       // Estrae URL dell'immagine dal JSON
       // ...
       
       return image_url;
   }
   ```

## Per gli Sviluppatori di Server

Se sei uno sviluppatore di server SA-MP, raccomandiamo fortemente l'installazione del plugin [SPC Integration](https://github.com/spc-samp/spc-integration) per i seguenti motivi:
1. Visibilità:
    - L'immagine personalizzata del tuo server sarà mostrata su Discord a tutti i giocatori che usano questo ASI
    - Aumenta il riconoscimento del brand del tuo server
    - Fornisce una presentazione più professionale

2. Benefici:
    - Maggiore coinvolgimento dei giocatori
    - Differenziazione visiva su Discord
    - Integrazione automatica con Rich Presence

3. Come implementare:
   - Leggi il repository del plugin [SPC Integration](https://github.com/spc-samp/spc-integration) per sapere come implementarlo

## Struttura del Codice

Il progetto è organizzato in vari componenti:
```
src/
├── discord/               # Libreria Discord RPC
├── command_line_parser.*  # Elaborazione argomenti
├── constants.h            # Costanti globali
├── discord_manager.*      # Integrazione con Discord
├── main.cpp               # Punto di ingresso
├── network_manager.*      # Operazioni di rete
├── server_manager.*       # Gestione del server
├── server_query.*         # Protocollo SA-MP
├── server_types.h         # Strutture dati
└── url_manager.*          # Integrazione con SPC
```

### Costanti Globali (constants.h)

Il file definisce diverse costanti importanti:
```cpp
namespace Constants {
    // Valori predefiniti
    inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
    inline constexpr int DEFAULT_SERVER_PORT = 7777;
    
    // Configurazioni di rete
    inline constexpr int QUERY_TIMEOUT = 1000;
    inline constexpr int QUERY_PACKET_SIZE = 11;
    inline constexpr int QUERY_BUFFER_SIZE = 512;
    
    // Configurazioni di retry
    inline constexpr int MAX_RETRY_ATTEMPTS = 3;
    
    // Intervalli
    inline constexpr int PRESENCE_UPDATE_INTERVAL = 5000;
}
```

### Strutture Dati (server_types.h)

Definisce le strutture principali:
```cpp
struct Server_Information {
    uint16_t Players{ 0 };           // Giocatori online
    uint16_t Max_Players{ 0 };       // Massimo di giocatori
    std::string Hostname;            // Nome del server
    std::string Server_Image;        // URL dell'immagine
    std::string Server_Address;      // Indirizzo del server
};
```

## Gestione degli Errori

Il sistema implementa un robusto sistema di gestione degli errori:
1. Timeout di rete:
   ```cpp
   timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
   setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
   ```

2. Sistema di retry:
   ```cpp
   bool Server_Query::Try_Query(Server_Information& server_data, int retry_count) noexcept {
       for (int attempt = 0; attempt <= retry_count; attempt++) {
           if (network_manager.Send_Query(...))
               return true;
           
           // Attende prima di riprovare
           std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
       }

       return false;
   }
   ```

3. Fallback per immagine predefinita:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       // Se qualcosa va storto, ritorna l'immagine predefinita
       if (!session_handle)
           return Constants::DEFAULT_IMAGE;

       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;

       return image_url;
   }
   ```

4. Monitoraggio dello stato di connessione:
   ```cpp
   bool Server_Manager::Update() {
       auto current_time = std::chrono::steady_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_successful_query);
       
       // Se rimane più di 15 secondi senza risposta, considera disconnesso
       if (duration.count() > 15) {
           connection_status = false;
           current_image_url = Constants::DEFAULT_IMAGE;
       }
   }
   ```

## Sistema di Elaborazione della Riga di Comando

L'ASI implementa un sistema flessibile per elaborare gli argomenti della riga di comando:

### Parser della Riga di Comando (command_line_parser.cpp)

1. Elaborazione principale:
   ```cpp
   bool Command_Line_Parser::Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       // Definisce valori predefiniti
       server_ip = Constants::DEFAULT_SERVER_IP;
       server_port = Constants::DEFAULT_SERVER_PORT;

       // Elabora ogni parametro
       std::wstring ip_parameter = Parse_Parameter(command_string, L"-h");
       std::wstring port_parameter = Parse_Parameter(command_string, L"-p");
       std::wstring name_parameter = Parse_Parameter(command_string, L"-n");

       // Converte e valida i valori
       if (!ip_parameter.empty())
           server_ip = Convert_To_String(ip_parameter);

       if (!port_parameter.empty())
           server_port = std::stoi(port_parameter);

       if (!name_parameter.empty())
           player_name = Convert_To_String(name_parameter);

       // Verifica se tutti i parametri necessari sono presenti
       return !server_ip.empty() && server_port > 0 && !player_name.empty();
   }
   ```

2. Estrazione dei parametri:
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

## Protocollo di Comunicazione SA-MP

L'ASI implementa il protocollo di query di SA-MP per ottenere informazioni dal server:
1. Struttura del pacchetto di query:
    - 4 byte: Firma "SAMP"
    - 7 byte: Dati aggiuntivi
    - Ultimo byte: 'i' (indica query di informazioni)

2. Struttura della risposta:
    - Header del pacchetto
    - Players (uint16_t)
    - Max_Players (uint16_t)
    - Hostname (string)

### Implementazione del Protocollo

```cpp
bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
    char* current_pos = response_buffer + Constants::QUERY_PACKET_SIZE;
    const char* buffer_end = response_buffer + received_bytes;

    // Salta "password"
    current_pos += sizeof(bool);
    
    // Legge dati fissi
    memcpy(&server_data.Players, current_pos, sizeof(server_data.Players));
    current_pos += sizeof(server_data.Players);
    
    memcpy(&server_data.Max_Players, current_pos, sizeof(server_data.Max_Players));
    current_pos += sizeof(server_data.Max_Players);

    // Legge Hostname e salta "gamemode" e "language"
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
    
    // Salta "gamemode" e "language"
    // ...

    return true;
}
```

## Vantaggi di SA-MP Rich Presence

1. Per i Giocatori:
    - Visualizzazione rapida del server attuale
    - Informazioni dettagliate sul server
    - Integrazione perfetta con Discord
    - Esperienza di gioco più sociale

2. Per i Server:
    - Maggiore visibilità attraverso Discord
    - Marketing organico attraverso i giocatori
    - Identità visiva personalizzata (con il plugin [SPC Integration](https://github.com/spc-samp/spc-integration))
    - Statistiche in tempo reale

## Note Tecniche Aggiuntive

1. Thread Safety:
    - L'ASI utilizza un singolo thread per gli aggiornamenti
    - I gestori sono thread-safe per design
    - Le risorse sono propriamente sincronizzate

2. Uso della Memoria:
    - Allocazione minima della memoria
    - Buffer pre-allocati per le query
    - Gestione automatica delle risorse (RAII)

3. Performance:
    - Query ottimizzate con timeout
    - Sistema di retry intelligente
    - Intervallo di aggiornamento configurabile

4. Compatibilità:
    - Supporto Unicode
    - Compatibile con Windows moderno
    - Supporto IPv4