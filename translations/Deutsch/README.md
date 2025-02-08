# SA-MP Rich Presence

SA-MP Rich Presence ist ein ASI für SA-MP (San Andreas Multiplayer), das automatisch Ihren Discord-Status mit detaillierten Serverinformationen aktualisiert. Das ASI wird in das Spiel injiziert, wenn Sie sich mit einem SA-MP-Server verbinden und zeigt Serverinformationen an.

## Sprachen

- Português: [README](../../)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Inhaltsverzeichnis

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Sprachen](#sprachen)
  - [Inhaltsverzeichnis](#inhaltsverzeichnis)
  - [Was ist ein ASI?](#was-ist-ein-asi)
  - [Funktionen](#funktionen)
    - [Discord Rich Presence](#discord-rich-presence)
  - [Anforderungen](#anforderungen)
  - [Installation](#installation)
  - [Detaillierte Technische Architektur](#detaillierte-technische-architektur)
    - [Hauptsystem (main.cpp)](#hauptsystem-maincpp)
    - [Discord-Manager (discord\_manager.cpp)](#discord-manager-discord_managercpp)
    - [Server-Manager (server\_manager.cpp)](#server-manager-server_managercpp)
    - [Netzwerksystem (network\_manager.cpp)](#netzwerksystem-network_managercpp)
    - [Server-Abfrage (server\_query.cpp)](#server-abfrage-server_querycpp)
  - [SPC-Integration](#spc-integration)
    - [Was ist SPC Integration?](#was-ist-spc-integration)
    - [Wie es funktioniert](#wie-es-funktioniert)
    - [URL-Manager (url\_manager.cpp)](#url-manager-url_managercpp)
  - [Für Server-Entwickler](#für-server-entwickler)
  - [Code-Struktur](#code-struktur)
    - [Globale Konstanten (constants.h)](#globale-konstanten-constantsh)
    - [Datenstrukturen (server\_types.h)](#datenstrukturen-server_typesh)
  - [Fehlerbehandlung](#fehlerbehandlung)
  - [Befehlszeilenverarbeitungssystem](#befehlszeilenverarbeitungssystem)
    - [Befehlszeilenparser (command\_line\_parser.cpp)](#befehlszeilenparser-command_line_parsercpp)
  - [SA-MP-Kommunikationsprotokoll](#sa-mp-kommunikationsprotokoll)
    - [Protokollimplementierung](#protokollimplementierung)
  - [Vorteile von SA-MP Rich Presence](#vorteile-von-sa-mp-rich-presence)
  - [Zusätzliche Technische Hinweise](#zusätzliche-technische-hinweise)

## Was ist ein ASI?

ASI ist eine dynamische Bibliothek (.dll), die mit der Erweiterung .asi umbenannt wurde und automatisch von einem ASI-Loader geladen wird, wenn GTA San Andreas gestartet wird. ASI-Plugins ermöglichen es, Spielfunktionen zu modifizieren oder hinzuzufügen, ohne die originalen Dateien zu ändern. Es ist eine der beliebtesten Modding-Methoden für GTA San Andreas und andere GTA-Spiele. Mit einem installierten ASI-Loader können Sie einfach Modifikationen installieren oder entfernen, indem Sie .asi-Dateien zum Spielordner hinzufügen oder daraus entfernen.

## Funktionen

### Discord Rich Presence

Discord Rich Presence ist eine Funktion, die es Anwendungen ermöglicht, detaillierte Informationen über die Aktivitäten des Benutzers direkt im Discord-Profil anzuzeigen. Im Fall von SA-MP Rich Presence werden folgende Informationen angezeigt:
- Servername (Hostname)
- Spielername
- Aktuelle Spieleranzahl und maximale Spieleranzahl
- Server-IP und Port
- Benutzerdefiniertes Serverbild (erfordert das [SPC Integration](https://github.com/spc-samp/spc-integration) Plugin)
- Spielzeit
- Verbindungsstatus

## Anforderungen

- SA-MP Client (falls nicht vorhanden: [clients-samp](https://github.com/spc-samp/clients-samp))
- Discord Desktop Anwendung
- Windows Betriebssystem
- Visual C++ Runtime
- ASI Loader im GTA San Andreas installiert

## Installation

1. Laden Sie die neueste Version des kompilierten ASI von [releases](https://github.com/ocalasans/samp-rich-presence/releases) herunter
2. Stellen Sie sicher, dass ein ASI Loader in Ihrem GTA San Andreas installiert ist
3. Kopieren Sie die heruntergeladene .asi-Datei in Ihren GTA San Andreas Ordner
4. Starten Sie das Spiel mit SA-MP
5. Das ASI wird automatisch initialisiert, wenn Sie einem Server beitreten

## Detaillierte Technische Architektur

### Hauptsystem (main.cpp)

Die main.cpp-Datei ist der Einstiegspunkt des ASI und verantwortlich für:
1. Systeminitialisierung:
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

2. Update-Thread-Verwaltung:
   ```cpp
   DWORD WINAPI Update_Thread(LPVOID) {
       // Initialisiert WSA für Netzwerkoperationen
       WSAData wsa_data;
       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
       
       // Verarbeitet Befehlszeilenparameter
       std::string server_ip, player_name;
       int server_port;
       
       // Initialisiert Manager
       Global_Server_Manager = std::make_unique<Server_Manager>(server_ip, server_port, player_name);
       Global_Discord_Manager = std::make_unique<Discord_Manager>();
       
       // Haupt-Update-Schleife
       while (true) {
           Global_Server_Manager->Update();
           Global_Discord_Manager->Update_Presence(...);
           Sleep(Constants::PRESENCE_UPDATE_INTERVAL);
       }
   }
   ```

### Discord-Manager (discord_manager.cpp)

Der Discord_Manager ist verantwortlich für die gesamte Discord Rich Presence Integration:
1. Discord RPC Initialisierung:
   ```cpp
   void Discord_Manager::Initialize() noexcept {
       Sleep(5000);  // Wartet auf Discord-Initialisierung
       
       DiscordEventHandlers discord_handlers{};
       Discord_Initialize("DISCORD_APP_ID", &discord_handlers, 1, NULL); // "DISCORD_APP_ID > Application ID"
       
       start_timestamp = time(nullptr);  // Markiert den Sitzungsbeginn
   }
   ```

2. Presence-Aktualisierung:
   ```cpp
   void Discord_Manager::Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept {
       DiscordRichPresence discord_presence{};
       
       // Konfiguriert Basisinformationen
       discord_presence.state = player_name.data();
       discord_presence.details = server_info.Hostname.c_str();
       discord_presence.largeImageKey = current_image.data();
       
       // Fügt Serverinformationen hinzu
       discord_presence.largeImageText = server_info.Server_Address.c_str();
       discord_presence.startTimestamp = start_timestamp;
       discord_presence.partySize = server_info.Players;
       discord_presence.partyMax = server_info.Max_Players;
       
       Discord_UpdatePresence(&discord_presence);
   }
   ```

### Server-Manager (server_manager.cpp)

Der Server_Manager koordiniert alle serverbezogenen Operationen:
1. Zustandsverwaltung:
   ```cpp
   Server_Manager::Server_Manager(const std::string& ip, int port, const std::string& name)
       : connection_status(false)
       , server_ip(ip)
       , server_port(port)
       , player_name(name)
       , current_image_url(Constants::DEFAULT_IMAGE)
   {}
   ```

2. Informationsaktualisierung:
   ```cpp
   bool Server_Manager::Update() {
       bool query_success = server_query.Query(server_data);
       
       if (query_success) {
           connection_status = true;
           server_data.Server_Address = Get_Server_Address();
           
           // Versucht, benutzerdefiniertes Serverbild zu erhalten
           std::string new_image_url = url_manager.Get_Image_URL(server_data.Server_Address);

           if (!new_image_url.empty())
               current_image_url = new_image_url;
       }
       // ...
   }
   ```

### Netzwerksystem (network_manager.cpp)

Der Network_Manager implementiert die gesamte Netzwerkkommunikation:
1. Socket-Initialisierung:
   ```cpp
   bool Network_Manager::Initialize(std::string_view ip, int port) noexcept {
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       
       // Konfiguriert Timeout
       timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
       
       // Konfiguriert Serveradresse
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(port);
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr);
       
       return true;
   }
   ```

### Server-Abfrage (server_query.cpp)

Die Server_Query implementiert das SA-MP-Abfrageprotokoll:
1. Abfragepaket-Zusammenbau:
   ```cpp
   bool Server_Query::Assemble_Query_Packet(char* packet) noexcept {
       memcpy(packet, QUERY_SIGNATURE, 4);  // "SAMP"
       packet[10] = 'i';  // Informationsabfrage

       return true;
   }
   ```

2. Antwortverarbeitung:
   ```cpp
   bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
       // Extrahiert Informationen wie:
       // - Spieleranzahl
       // - Maximale Spieleranzahl
       // - Hostname
   }
   ```

## SPC-Integration

### Was ist SPC Integration?

[SPC Integration](https://github.com/spc-samp/spc-integration) ist ein Plugin, das für **SA-MP** (San Andreas Multiplayer) und **open.mp** (Open Multiplayer) entwickelt wurde und als Brücke zwischen Servern und dem **SPC**-Ökosystem fungiert. Das Plugin sammelt wichtige Serverinformationen, einschließlich:
- IP und Port
- Server-Website-URL
- Benutzerdefinierte Bild-URL
- Konfigurationsinformationen

Diese Informationen werden sicher im **SPC (SA-MP Programming Community)** Datenspeicher gespeichert und ermöglichen eine Integration mit verschiedenen **SPC**-Anwendungen, einschließlich Rich Presence.

### Wie es funktioniert

1. Der Server verwendet das [SPC Integration](https://github.com/spc-samp/spc-integration) Plugin, um sein benutzerdefiniertes Bild zu registrieren
2. Das Bild wird im **SPC**-Datenspeicher in der Server-JSON-Datei gespeichert
3. Wenn sich ein Spieler mit dem Server verbindet:
    - Der URL_Manager des ASI versucht, die Server-JSON-Datei abzurufen (Format: `ip-port.json`)
    - Wenn gefunden, wird die Bild-URL aus dem Parameter `spc_integration_image` extrahiert
    - Das Bild wird dann im Discord Rich Presence des Spielers angezeigt

### URL-Manager (url_manager.cpp)

Der URL_Manager ist verantwortlich für die gesamte Kommunikation mit dem **SPC**-Datenspeicher:
1. Server-Bildabfrage:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       std::string formatted_address = server_address;
       // Konvertiert ":" zu "-" in der Adresse
       size_t colon_pos = formatted_address.find(':');

       if (colon_pos != std::string::npos)
           formatted_address.replace(colon_pos, 1, "-");
       
       // Ruft Server-JSON ab
       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;
       
       return image_url;
   }
   ```

2. JSON-Verarbeitung:
   ```cpp
   std::string URL_Manager::Parse_JSON(const std::string& json_content) {
       const std::string key = "\"spc_integration_image\":";
       size_t key_pos = json_content.find(key);
       
       // Extrahiert Bild-URL aus JSON
       // ...
       
       return image_url;
   }
   ```

## Für Server-Entwickler

Wenn Sie ein SA-MP-Server-Entwickler sind, empfehlen wir dringend die Installation des [SPC Integration](https://github.com/spc-samp/spc-integration) Plugins aus folgenden Gründen:
1. Sichtbarkeit:
    - Das benutzerdefinierte Bild Ihres Servers wird im Discord aller Spieler angezeigt, die dieses ASI verwenden
    - Erhöht die Markenbekanntheit Ihres Servers
    - Bietet eine professionellere Präsentation

2. Vorteile:
    - Erhöhtes Spielerengagement
    - Visuelle Differenzierung in Discord
    - Automatische Integration mit Rich Presence

3. Implementierung:
   - Lesen Sie das [SPC Integration](https://github.com/spc-samp/spc-integration) Plugin-Repository für Implementierungsdetails

## Code-Struktur

Das Projekt ist in verschiedene Komponenten gegliedert:
```
src/
├── discord/               # Discord RPC Bibliothek
├── command_line_parser.*  # Befehlszeilenverarbeitung
├── constants.h            # Globale Konstanten
├── discord_manager.*      # Discord-Integration
├── main.cpp               # Einstiegspunkt
├── network_manager.*      # Netzwerkoperationen
├── server_manager.*       # Serververwaltung
├── server_query.*         # SA-MP-Protokoll
├── server_types.h         # Datenstrukturen
└── url_manager.*          # SPC-Integration
```

### Globale Konstanten (constants.h)

Die Datei definiert wichtige Konstanten:
```cpp
namespace Constants {
    // Standardwerte
    inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
    inline constexpr int DEFAULT_SERVER_PORT = 7777;
    
    // Netzwerkeinstellungen
    inline constexpr int QUERY_TIMEOUT = 1000;
    inline constexpr int QUERY_PACKET_SIZE = 11;
    inline constexpr int QUERY_BUFFER_SIZE = 512;
    
    // Wiederholungseinstellungen
    inline constexpr int MAX_RETRY_ATTEMPTS = 3;
    
    // Intervalle
    inline constexpr int PRESENCE_UPDATE_INTERVAL = 5000;
}
```

### Datenstrukturen (server_types.h)

Definiert die Hauptstrukturen:
```cpp
struct Server_Information {
    uint16_t Players{ 0 };           // Online-Spieler
    uint16_t Max_Players{ 0 };       // Maximale Spieleranzahl
    std::string Hostname;            // Servername
    std::string Server_Image;        // Bild-URL
    std::string Server_Address;      // Serveradresse
};
```

## Fehlerbehandlung

Das System implementiert ein robustes Fehlerbehandlungssystem:
1. Netzwerk-Timeout:
   ```cpp
   timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
   setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
   ```

2. Wiederholungssystem:
   ```cpp
   bool Server_Query::Try_Query(Server_Information& server_data, int retry_count) noexcept {
       for (int attempt = 0; attempt <= retry_count; attempt++) {
           if (network_manager.Send_Query(...))
               return true;
           
           // Wartet vor dem nächsten Versuch
           std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
       }

       return false;
   }
   ```

3. Fallback auf Standardbild:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       // Bei Fehlern wird das Standardbild zurückgegeben
       if (!session_handle)
           return Constants::DEFAULT_IMAGE;

       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;

       return image_url;
   }
   ```

4. Verbindungsstatusüberwachung:
   ```cpp
   bool Server_Manager::Update() {
       auto current_time = std::chrono::steady_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_successful_query);
       
       // Nach 15 Sekunden ohne Antwort als getrennt betrachten
       if (duration.count() > 15) {
           connection_status = false;
           current_image_url = Constants::DEFAULT_IMAGE;
       }
   }
   ```

## Befehlszeilenverarbeitungssystem

Das ASI implementiert ein flexibles System zur Verarbeitung von Befehlszeilenargumenten:

### Befehlszeilenparser (command_line_parser.cpp)

1. Hauptverarbeitung:
   ```cpp
   bool Command_Line_Parser::Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       // Setzt Standardwerte
       server_ip = Constants::DEFAULT_SERVER_IP;
       server_port = Constants::DEFAULT_SERVER_PORT;

       // Verarbeitet jeden Parameter
       std::wstring ip_parameter = Parse_Parameter(command_string, L"-h");
       std::wstring port_parameter = Parse_Parameter(command_string, L"-p");
       std::wstring name_parameter = Parse_Parameter(command_string, L"-n");

       // Konvertiert und validiert die Werte
       if (!ip_parameter.empty())
           server_ip = Convert_To_String(ip_parameter);

       if (!port_parameter.empty())
           server_port = std::stoi(port_parameter);

       if (!name_parameter.empty())
           player_name = Convert_To_String(name_parameter);

       // Überprüft, ob alle erforderlichen Parameter vorhanden sind
       return !server_ip.empty() && server_port > 0 && !player_name.empty();
   }
   ```

2. Parameterextraktion:
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

## SA-MP-Kommunikationsprotokoll

Das ASI implementiert das SA-MP-Abfrageprotokoll für Serverinformationen:
1. Abfragepaketstruktur:
    - 4 Bytes: Signatur "SAMP"
    - 7 Bytes: Zusätzliche Daten
    - Letztes Byte: 'i' (zeigt Informationsabfrage an)

2. Antwortstruktur:
    - Paketkopf
    - Players (uint16_t)
    - Max_Players (uint16_t)
    - Hostname (string)

### Protokollimplementierung

```cpp
bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
    char* current_pos = response_buffer + Constants::QUERY_PACKET_SIZE;
    const char* buffer_end = response_buffer + received_bytes;

    // "password" überspringen
    current_pos += sizeof(bool);
    
    // Feste Daten lesen
    memcpy(&server_data.Players, current_pos, sizeof(server_data.Players));
    current_pos += sizeof(server_data.Players);
    
    memcpy(&server_data.Max_Players, current_pos, sizeof(server_data.Max_Players));
    current_pos += sizeof(server_data.Max_Players);

    // Hostname lesen und "gamemode" und "language" überspringen
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
    
    // "gamemode" und "language" überspringen
    // ...

    return true;
}
```

## Vorteile von SA-MP Rich Presence

1. Für Spieler:
    - Schnelle Übersicht über den aktuellen Server
    - Detaillierte Serverinformationen
    - Nahtlose Discord-Integration
    - Sozialeres Spielerlebnis

2. Für Server:
    - Erhöhte Sichtbarkeit durch Discord
    - Organisches Marketing durch Spieler
    - Angepasste visuelle Identität (mit dem [SPC Integration](https://github.com/spc-samp/spc-integration) Plugin)
    - Echtzeit-Statistiken

## Zusätzliche Technische Hinweise

1. Thread-Sicherheit:
    - Das ASI verwendet einen einzelnen Thread für Updates
    - Manager sind von Natur aus thread-sicher
    - Ressourcen sind ordnungsgemäß synchronisiert

2. Speichernutzung:
    - Minimale Speicherzuweisung
    - Vorab zugewiesene Abfrage-Puffer
    - Automatische Ressourcenverwaltung (RAII)

3. Leistung:
    - Optimierte Abfragen mit Timeout
    - Intelligentes Wiederholungssystem
    - Konfigurierbares Update-Intervall

4. Kompatibilität:
    - Unicode-Unterstützung
    - Kompatibel mit modernem Windows
    - IPv4-Unterstützung