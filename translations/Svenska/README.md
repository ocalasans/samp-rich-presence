# SA-MP Rich Presence

SA-MP Rich Presence är en ASI för SA-MP (San Andreas Multiplayer) som automatiskt uppdaterar din Discord-status med detaljerad serverinformation. ASI injiceras i spelet när du ansluter till en SA-MP-server och visar serverinformation.

## Språk

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Türkçe: [README](../Turkce/README.md)

## Innehållsförteckning

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Språk](#språk)
  - [Innehållsförteckning](#innehållsförteckning)
  - [Vad är en ASI?](#vad-är-en-asi)
  - [Funktioner](#funktioner)
    - [Discord Rich Presence](#discord-rich-presence)
  - [Krav](#krav)
  - [Installation](#installation)
  - [Detaljerad Teknisk Arkitektur](#detaljerad-teknisk-arkitektur)
    - [Huvudsystem (main.cpp)](#huvudsystem-maincpp)
    - [Discord Manager (discord\_manager.cpp)](#discord-manager-discord_managercpp)
    - [Server Manager (server\_manager.cpp)](#server-manager-server_managercpp)
    - [Nätverkssystem (network\_manager.cpp)](#nätverkssystem-network_managercpp)
    - [Serverförfrågan (server\_query.cpp)](#serverförfrågan-server_querycpp)
  - [SPC Integration](#spc-integration)
    - [Vad är SPC Integration?](#vad-är-spc-integration)
    - [Hur det fungerar](#hur-det-fungerar)
    - [URL Manager (url\_manager.cpp)](#url-manager-url_managercpp)
  - [För Serverutvecklare](#för-serverutvecklare)
  - [Kodstruktur](#kodstruktur)
    - [Globala Konstanter (constants.h)](#globala-konstanter-constantsh)
    - [Datastrukturer (server\_types.h)](#datastrukturer-server_typesh)
  - [Felhantering](#felhantering)
  - [Kommandoradshanteringssystem](#kommandoradshanteringssystem)
    - [Kommandoradsparser (command\_line\_parser.cpp)](#kommandoradsparser-command_line_parsercpp)
  - [SA-MP Kommunikationsprotokoll](#sa-mp-kommunikationsprotokoll)
    - [Protokollimplementering](#protokollimplementering)
  - [Fördelar med SA-MP Rich Presence](#fördelar-med-sa-mp-rich-presence)
  - [Ytterligare Tekniska Anteckningar](#ytterligare-tekniska-anteckningar)

## Vad är en ASI?

ASI är ett dynamiskt bibliotek (.dll) som döpts om med tillägget .asi och laddas automatiskt av en ASI-laddare när GTA San Andreas startas. ASI-plugins gör det möjligt att modifiera eller lägga till funktioner i spelet utan att ändra originalfilerna, och är ett av de mest populära sätten att modda GTA San Andreas och andra GTA-spel. Med en ASI-laddare installerad kan du enkelt installera eller ta bort modifieringar genom att bara lägga till eller ta bort .asi-filer från spelmappen.

## Funktioner

### Discord Rich Presence

Discord Rich Presence är en funktion som låter applikationer visa detaljerad information om vad användaren gör direkt i deras Discord-profil. För SA-MP Rich Presence visas följande information:
- Servernamn (Hostname)
- Spelarnamn
- Nuvarande antal spelare och maximalt antal spelare
- Server-IP och port
- Anpassad serverbild (kräver att servern har pluginen [SPC Integration](https://github.com/spc-samp/spc-integration))
- Speltid
- Anslutningsstatus

## Krav

- SA-MP-klient (om du inte har en: [clients-samp](https://github.com/spc-samp/clients-samp))
- Discord Desktop-applikation
- Windows operativsystem
- Visual C++ Runtime
- ASI Loader installerad i GTA San Andreas

## Installation

1. Ladda ner den senaste kompilerade versionen av ASI från [releases](https://github.com/ocalasans/samp-rich-presence/releases)
2. Se till att du har en ASI Loader installerad i din GTA San Andreas
3. Kopiera den nedladdade .asi-filen till din GTA San Andreas-mapp
4. Starta spelet med SA-MP
5. ASI initieras automatiskt när du går in på en server

## Detaljerad Teknisk Arkitektur

### Huvudsystem (main.cpp)

Main.cpp är ASI:ns ingångspunkt och ansvarar för:
1. Systeminitiering:
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

2. Hantering av uppdateringstråd:
   ```cpp
   DWORD WINAPI Update_Thread(LPVOID) {
       // Initierar WSA för nätverksoperationer
       WSAData wsa_data;
       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
       
       // Behandlar kommandoradsparametrar
       std::string server_ip, player_name;
       int server_port;
       
       // Initierar hanterare
       Global_Server_Manager = std::make_unique<Server_Manager>(server_ip, server_port, player_name);
       Global_Discord_Manager = std::make_unique<Discord_Manager>();
       
       // Huvuduppdateringsloop
       while (true) {
           Global_Server_Manager->Update();
           Global_Discord_Manager->Update_Presence(...);
           Sleep(Constants::PRESENCE_UPDATE_INTERVAL);
       }
   }
   ```

### Discord Manager (discord_manager.cpp)

Discord_Manager ansvarar för all integration med Discord Rich Presence:
1. Initiering av Discord RPC:
   ```cpp
   void Discord_Manager::Initialize() noexcept {
       Sleep(5000);  // Väntar på Discord-initiering
       
       DiscordEventHandlers discord_handlers{};
       Discord_Initialize("DISCORD_APP_ID", &discord_handlers, 1, NULL); // "DISCORD_APP_ID > Application ID"
       
       start_timestamp = time(nullptr);  // Markerar sessionens start
   }
   ```

2. Uppdatering av presence:
   ```cpp
   void Discord_Manager::Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept {
       DiscordRichPresence discord_presence{};
       
       // Konfigurerar grundläggande information
       discord_presence.state = player_name.data();
       discord_presence.details = server_info.Hostname.c_str();
       discord_presence.largeImageKey = current_image.data();
       
       // Lägger till serverinformation
       discord_presence.largeImageText = server_info.Server_Address.c_str();
       discord_presence.startTimestamp = start_timestamp;
       discord_presence.partySize = server_info.Players;
       discord_presence.partyMax = server_info.Max_Players;
       
       Discord_UpdatePresence(&discord_presence);
   }
   ```

### Server Manager (server_manager.cpp)

Server_Manager koordinerar alla serverrelaterade operationer:
1. Tillståndshantering:
   ```cpp
   Server_Manager::Server_Manager(const std::string& ip, int port, const std::string& name)
       : connection_status(false)
       , server_ip(ip)
       , server_port(port)
       , player_name(name)
       , current_image_url(Constants::DEFAULT_IMAGE)
   {}
   ```

2. Informationsuppdatering:
   ```cpp
   bool Server_Manager::Update() {
       bool query_success = server_query.Query(server_data);
       
       if (query_success) {
           connection_status = true;
           server_data.Server_Address = Get_Server_Address();
           
           // Försöker hämta anpassad serverbild
           std::string new_image_url = url_manager.Get_Image_URL(server_data.Server_Address);

           if (!new_image_url.empty())
               current_image_url = new_image_url;
       }
       // ...
   }
   ```

### Nätverkssystem (network_manager.cpp)

Network_Manager implementerar all nätverkskommunikation:
1. Socket-initiering:
   ```cpp
   bool Network_Manager::Initialize(std::string_view ip, int port) noexcept {
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       
       // Konfigurerar timeout
       timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
       
       // Konfigurerar serveradress
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(port);
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr);
       
       return true;
   }
   ```

### Serverförfrågan (server_query.cpp)

Server_Query implementerar SA-MP:s frågeprotokoll:
1. Sammanställning av frågepaket:
   ```cpp
   bool Server_Query::Assemble_Query_Packet(char* packet) noexcept {
       memcpy(packet, QUERY_SIGNATURE, 4);  // "SAMP"
       packet[10] = 'i';  // Informationsförfrågan

       return true;
   }
   ```

2. Svarsbehandling:
   ```cpp
   bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
       // Extraherar information som:
       // - Antal spelare
       // - Max antal spelare
       // - Hostname
   }
   ```

## SPC Integration

### Vad är SPC Integration?

[SPC Integration](https://github.com/spc-samp/spc-integration) är en plugin utvecklad för **SA-MP** (San Andreas Multiplayer) och **open.mp** (Open Multiplayer) som fungerar som en brygga mellan servrar och **SPC**-ekosystemet. Pluginen samlar viktig serverinformation, inklusive:
- IP och port
- Serverns webbadress
- Anpassad bildadress
- Konfigurationsinformation

Denna information skickas och lagras säkert i **SPC:s (SA-MP Programming Community)** datalager, vilket möjliggör integration med olika SPC-applikationer, inklusive Rich Presence.

### Hur det fungerar

1. Servern använder [SPC Integration](https://github.com/spc-samp/spc-integration)-pluginen för att registrera sin anpassade bild
2. Bilden lagras i SPC:s datalager i serverns JSON-fil
3. När en spelare ansluter till servern:
    - ASI:ns URL_Manager försöker hämta serverns JSON-fil (format: `ip-port.json`)
    - Om den hittas, extraheras bildadressen från parametern `spc_integration_image`
    - Bilden visas sedan i spelarens Discord Rich Presence

### URL Manager (url_manager.cpp)

URL_Manager ansvarar för all kommunikation med SPC:s datalager:
1. Hämtning av serverbild:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       std::string formatted_address = server_address;
       // Konverterar ":" till "-" i adressen
       size_t colon_pos = formatted_address.find(':');

       if (colon_pos != std::string::npos)
           formatted_address.replace(colon_pos, 1, "-");
       
       // Hämtar serverns JSON
       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;
       
       return image_url;
   }
   ```

2. JSON-behandling:
   ```cpp
   std::string URL_Manager::Parse_JSON(const std::string& json_content) {
       const std::string key = "\"spc_integration_image\":";
       size_t key_pos = json_content.find(key);
       
       // Extraherar bildadress från JSON
       // ...
       
       return image_url;
   }
   ```

## För Serverutvecklare

Om du är en SA-MP-serverutvecklare rekommenderar vi starkt att du installerar [SPC Integration](https://github.com/spc-samp/spc-integration)-pluginen av följande skäl:
1. Synlighet:
    - Din servers anpassade bild kommer att visas i Discord för alla spelare som använder denna ASI
    - Ökar igenkänningen av din servers varumärke
    - Ger en mer professionell presentation

2. Fördelar:
    - Ökat spelarengagemang
    - Visuell differentiering i Discord
    - Automatisk integration med Rich Presence

3. Hur man implementerar:
   - Läs pluginens [SPC Integration](https://github.com/spc-samp/spc-integration)-repository för att lära dig hur man implementerar

## Kodstruktur

Projektet är organiserat i flera komponenter:
```
src/
├── discord/               # Discord RPC-bibliotek
├── command_line_parser.*  # Kommandoradsbehandling
├── constants.h            # Globala konstanter
├── discord_manager.*      # Discord-integration
├── main.cpp               # Ingångspunkt
├── network_manager.*      # Nätverksoperationer
├── server_manager.*       # Serverhantering
├── server_query.*         # SA-MP-protokoll
├── server_types.h         # Datastrukturer
└── url_manager.*          # SPC-integration
```

### Globala Konstanter (constants.h)

Filen definierar flera viktiga konstanter:
```cpp
namespace Constants {
    // Standardvärden
    inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
    inline constexpr int DEFAULT_SERVER_PORT = 7777;
    
    // Nätverksinställningar
    inline constexpr int QUERY_TIMEOUT = 1000;
    inline constexpr int QUERY_PACKET_SIZE = 11;
    inline constexpr int QUERY_BUFFER_SIZE = 512;
    
    // Återförsöksinställningar
    inline constexpr int MAX_RETRY_ATTEMPTS = 3;
    
    // Intervaller
    inline constexpr int PRESENCE_UPDATE_INTERVAL = 5000;
}
```

### Datastrukturer (server_types.h)

Definierar huvudstrukturerna:
```cpp
struct Server_Information {
    uint16_t Players{ 0 };           // Spelare online
    uint16_t Max_Players{ 0 };       // Max antal spelare
    std::string Hostname;            // Servernamn
    std::string Server_Image;        // Bildadress
    std::string Server_Address;      // Serveradress
};
```

## Felhantering

Systemet implementerar ett robust felhanteringssystem:
1. Nätverkstimeout:
   ```cpp
   timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
   setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
   ```

2. Återförsökssystem:
   ```cpp
   bool Server_Query::Try_Query(Server_Information& server_data, int retry_count) noexcept {
       for (int attempt = 0; attempt <= retry_count; attempt++) {
           if (network_manager.Send_Query(...))
               return true;
           
           // Väntar innan nytt försök
           std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
       }

       return false;
   }
   ```

3. Fallback till standardbild:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       // Om något går fel, returnera standardbilden
       if (!session_handle)
           return Constants::DEFAULT_IMAGE;

       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;

       return image_url;
   }
   ```

4. Övervakning av anslutningsstatus:
   ```cpp
   bool Server_Manager::Update() {
       auto current_time = std::chrono::steady_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_successful_query);
       
       // Om det gått mer än 15 sekunder utan svar, anses frånkopplad
       if (duration.count() > 15) {
           connection_status = false;
           current_image_url = Constants::DEFAULT_IMAGE;
       }
   }
   ```

## Kommandoradshanteringssystem

ASI:n implementerar ett flexibelt system för att bearbeta kommandoradsargument:

### Kommandoradsparser (command_line_parser.cpp)

1. Huvudbearbetning:
   ```cpp
   bool Command_Line_Parser::Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       // Ställer in standardvärden
       server_ip = Constants::DEFAULT_SERVER_IP;
       server_port = Constants::DEFAULT_SERVER_PORT;

       // Bearbetar varje parameter
       std::wstring ip_parameter = Parse_Parameter(command_string, L"-h");
       std::wstring port_parameter = Parse_Parameter(command_string, L"-p");
       std::wstring name_parameter = Parse_Parameter(command_string, L"-n");

       // Konverterar och validerar värden
       if (!ip_parameter.empty())
           server_ip = Convert_To_String(ip_parameter);

       if (!port_parameter.empty())
           server_port = std::stoi(port_parameter);

       if (!name_parameter.empty())
           player_name = Convert_To_String(name_parameter);

       // Kontrollerar om alla nödvändiga parametrar finns
       return !server_ip.empty() && server_port > 0 && !player_name.empty();
   }
   ```

2. Parameterextrahering:
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

## SA-MP Kommunikationsprotokoll

ASI:n implementerar SA-MP:s frågeprotokoll för att hämta serverinformation:
1. Frågepaketets struktur:
    - 4 bytes: Signatur "SAMP"
    - 7 bytes: Ytterligare data
    - Sista byte: 'i' (indikerar informationsförfrågan)

2. Svarsstruktur:
    - Pakethuvud
    - Players (uint16_t)
    - Max_Players (uint16_t)
    - Hostname (string)

### Protokollimplementering

```cpp
bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
    char* current_pos = response_buffer + Constants::QUERY_PACKET_SIZE;
    const char* buffer_end = response_buffer + received_bytes;

    // Hoppa över "password"
    current_pos += sizeof(bool);
    
    // Läser fast data
    memcpy(&server_data.Players, current_pos, sizeof(server_data.Players));
    current_pos += sizeof(server_data.Players);
    
    memcpy(&server_data.Max_Players, current_pos, sizeof(server_data.Max_Players));
    current_pos += sizeof(server_data.Max_Players);

    // Läser Hostname och hoppar över "gamemode" och "language"
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
    
    // Hoppar över "gamemode" och "language"
    // ...

    return true;
}
```

## Fördelar med SA-MP Rich Presence

1. För Spelare:
    - Snabb överblick av aktuell server
    - Detaljerad serverinformation
    - Sömlös Discord-integration
    - Mer social spelupplevelse

2. För Servrar:
    - Ökad synlighet genom Discord
    - Organisk marknadsföring genom spelare
    - Anpassad visuell identitet (med [SPC Integration](https://github.com/spc-samp/spc-integration)-pluginen)
    - Realtidsstatistik

## Ytterligare Tekniska Anteckningar

1. Trådsäkerhet:
    - ASI:n använder en enda tråd för uppdateringar
    - Hanterare är trådsäkra genom design
    - Resurser är korrekt synkroniserade

2. Minnesanvändning:
    - Minimal minnesallokering
    - Förallokererade buffertar för förfrågningar
    - Automatisk resurshantering (RAII)

3. Prestanda:
    - Optimerade förfrågningar med timeout
    - Intelligent återförsökssystem
    - Konfigurerbart uppdateringsintervall

4. Kompatibilitet:
    - Unicode-stöd
    - Kompatibel med modern Windows
    - IPv4-stöd