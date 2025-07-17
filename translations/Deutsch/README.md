# SA-MP Rich Presence

Das **SA-MP Rich Presence** ist ein **ASI** für **SA-MP (San Andreas Multiplayer)**, das automatisch deinen Discord-Status mit detaillierten Informationen über den Server aktualisiert. Das **ASI** wird in das Spiel injiziert, wenn du dich mit einem SA-MP-Server verbindest, und zeigt Serverinformationen an.

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
  - [Funktionen](#funktionen)
    - [Discord Rich Presence](#discord-rich-presence)
    - [Automatisches Updatesystem](#automatisches-updatesystem)
  - [Voraussetzungen](#voraussetzungen)
  - [Installation](#installation)
  - [Integration mit der SPC Integration API](#integration-mit-der-spc-integration-api)
    - [Wie die Informationen abgerufen und verwendet werden:](#wie-die-informationen-abgerufen-und-verwendet-werden)
  - [Für Serverentwickler](#für-serverentwickler)
    - [Wie man die SPC Integration auf deinem Server implementiert:](#wie-man-die-spc-integration-auf-deinem-server-implementiert)
  - [Detaillierte technische Architektur](#detaillierte-technische-architektur)
      - [Hauptsystem (`main.cpp`)](#hauptsystem-maincpp)
      - [Updatesystem (`asi_update.hpp`)](#updatesystem-asi_updatehpp)
      - [Discord-Manager (`discord_manager.cpp`)](#discord-manager-discord_managercpp)
      - [Server-Manager (`server_manager.cpp`)](#server-manager-server_managercpp)
      - [Netzwerksystem (`samp_network.cpp`)](#netzwerksystem-samp_networkcpp)
      - [Serverabfrage (`server_query.cpp`)](#serverabfrage-server_querycpp)
      - [URL-Manager (`url_manager.cpp`)](#url-manager-url_managercpp)
    - [Code-Struktur](#code-struktur)
      - [Globale Konstanten (`constants.hpp`)](#globale-konstanten-constantshpp)
      - [Datenstrukturen (`server_types.hpp`)](#datenstrukturen-server_typeshpp)
      - [Verschleierung von Geheimnissen (`secrets.hpp`)](#verschleierung-von-geheimnissen-secretshpp)
      - [Allgemeine Hilfsfunktionen (`utils.hpp`)](#allgemeine-hilfsfunktionen-utilshpp)
    - [Fehlerbehandlung und Robustheit](#fehlerbehandlung-und-robustheit)
    - [Kommandozeilenverarbeitungssystem](#kommandozeilenverarbeitungssystem)
      - [Kommandozeilen-Parser (`command_line_parser.cpp`)](#kommandozeilen-parser-command_line_parsercpp)
    - [SA-MP Kommunikationsprotokoll](#sa-mp-kommunikationsprotokoll)
      - [Protokollimplementierung](#protokollimplementierung)
    - [Vorteile von SA-MP Rich Presence](#vorteile-von-sa-mp-rich-presence)
  - [Lizenz](#lizenz)
    - [Bedingungen:](#bedingungen)

## Funktionen

### Discord Rich Presence

Die **Discord Rich Presence** ist eine Funktion, die es Anwendungen ermöglicht, detaillierte Informationen darüber anzuzeigen, was der Benutzer gerade tut, direkt im Discord-Profil. Im Falle von **SA-MP Rich Presence** werden folgende Informationen angezeigt:

- **Servername (Hostname):** Der Hauptname des Servers.
- **Spielername:** Dein aktueller Nickname im Spiel.
- **Spieleranzahl:** Aktuelle Anzahl der online befindlichen Spieler und die maximal zulässige Anzahl.
- **Serveradresse:** IP und Port des Servers zur einfachen Identifikation.
- **Individuelles Serverbild:** Ein einzigartiges Serverlogo, falls verfügbar.
- **Rotierendes soziales Symbol:** Kleine Symbole, die Links zu sozialen Medien des Servers darstellen (Website, Discord, YouTube, Instagram, Facebook, TikTok), die automatisch wechseln.
- **Spielzeit:** Wie lange du mit dem aktuellen Server verbunden bist.
- **Verbindungsstatus:** Zeigt an, ob du online auf einem Server bist oder im Zustand "Idle" (inaktiv).
- **"Join"-Button:** Ermöglicht deinen Freunden, direkt dem gleichen Server beizutreten, auf dem du spielst.

### Automatisches Updatesystem

Das **ASI** integriert ein System zur Überprüfung von Updates. Beim Start des Spiels wird geprüft, ob neue Versionen im offiziellen GitHub-Repository des Projekts verfügbar sind. Wird ein Update erkannt, erscheint eine benutzerfreundliche Benachrichtigung mit folgenden Optionen:

1. Öffnen des Browsers direkt auf der Release-Seite zum Herunterladen.
2. Fortfahren ohne Update, mit der Möglichkeit, das **ASI** für die aktuelle Sitzung zu deaktivieren.

Diese Funktion stellt sicher, dass Benutzer immer Zugriff auf die neuesten Verbesserungen, Fehlerkorrekturen und neuen Funktionen haben, was eine aktuelle und unterbrechungsfreie Erfahrung fördert.

## Voraussetzungen

- SA-MP-Client (falls nicht vorhanden: [clients-samp](https://github.com/spc-samp/clients-samp)).
- Discord Desktop-Anwendung.
- Windows-Betriebssystem.
- Visual C++ Runtime.
- Ein installierter [ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) in deinem Grand Theft Auto: San Andreas.

## Installation

1. Lade die neueste kompilierte Version des **ASI** direkt aus dem [Releases](https://github.com/ocalasans/samp-rich-presence/releases)-Bereich auf GitHub herunter.
2. Nach dem Download finde die `.asi`-Datei.
3. Kopiere die heruntergeladene `.asi`-Datei in den Hauptordner deines GTA San Andreas (wo sich die Datei `gta_sa.exe` befindet).
4. Starte das Spiel über den SA-MP-Client.
5. Das **ASI** wird automatisch geladen und initialisiert, sobald du dich mit einem Server verbindest, und aktualisiert deinen Discord-Status.

## Integration mit der SPC Integration API

Das **SA-MP Rich Presence** verbessert die Anzeige von Informationen in Discord erheblich durch seine Integration mit der **SPC Integration API**. Anstatt sich nur auf grundlegende Abfragedaten zu verlassen, interagiert das **ASI** nun direkt mit dieser API, um visuelle und soziale Informationen des Servers zu erhalten. Für weitere Informationen über die **SPC Integration** selbst, besuche das offizielle Repository: [spc-samp/spc-integration](https://github.com/spc-samp/spc-integration).

### Wie die Informationen abgerufen und verwendet werden:

1. **Adressformatierung:** Wenn sich der Spieler mit einem Server verbindet (IP und Port), formatiert das **ASI** diese Adresse (`IP:PORT`) in ein benutzerfreundliches Format (`IP-PORT`), um sie für die API-Anfrage vorzubereiten.
2. **API-Anfrage:** Das **ASI** sendet eine `GET`-Anfrage an den Endpunkt der **SPC Integration API**, die die formatierte IP und den Port enthält. Beispiel, wie die Anfrage-URL intern erstellt wird:
   ```cpp
   // Auszug aus url_manager.cpp
   auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
   std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
   path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   const std::string json_data = Request_API_Data(path);
   ```
3. **Verarbeitung der JSON-Antwort:** Die API gibt eine Antwort im JSON-Format zurück. Das **ASI** verwendet die Bibliothek [nlohmann/json](https://github.com/nlohmann/json), um diese Antwort zu parsen und relevante Daten zu extrahieren.
   ```json
   // Beispiel für die Struktur der Antwort der SPC Integration API
   {
       "success": true,
       "data": {
           "public": {
               "logo": "https://url.deines.logos/server_logo.png",
               "website": "https://deine-seite.com",
               "discord": "https://discord.gg/deinserver",
               "youtube": "https://youtube.com/deinkanal"
               // ...weitere soziale Medien
           }
       }
   }
   ```
4. **Datenextraktion:**
   - **Serverlogo:** Die URL des Serverbildes (das `logo` innerhalb des `public`-Abschnitts) wird extrahiert und als Hauptbild (large image) im **Discord Rich Presence** verwendet. Dies garantiert eine authentische und anpassbare visuelle Identität für jeden Server.
   - **Soziale Links:** Eine vordefinierte Liste sozialer Medien (Website, Discord, YouTube, Instagram, Facebook, TikTok) wird in der JSON-Antwort überprüft. Für jedes gefundene soziale Medium mit einem gültigen Wert werden der Name des Mediums und der entsprechende Link gespeichert.
5. **Anzeige in Discord:** Der `Server_Manager` verwendet die Liste der extrahierten sozialen Links, um eine dynamische Rotation zu implementieren. Alle 30 Sekunden wird ein anderes Symbol eines sozialen Mediums des Servers als "small image" (kleines Bild) in der Discord-Präsenz angezeigt, zusammen mit dem Link oder Namen der Plattform, um die Erkundung der Server-Communitys zu fördern.

## Für Serverentwickler

Die Integration deines Servers mit der [SPC Integration](https://github.com/spc-samp/spc-integration) bringt eine Reihe direkter und indirekter Vorteile, die die Sichtbarkeit und das Engagement deiner SA-MP-Community steigern. Wenn du ein Serverentwickler bist, beachte die strategischen Vorteile:

1. **Stärke deine Marke:**
   - **Premium-Sichtbarkeit:** Das personalisierte Logo deines Servers ist nicht nur ein Text, sondern ein lebendiges, auffälliges Bild, das im Discord-Profil aller Spieler angezeigt wird, die dieses **ASI** verwenden. Dies ist eine organische und konstante Form der Markenbildung.
   - **Professionelle Präsenz:** Mit einem gut dargestellten Logo und sozialen Medien vermittelt dein Server ein etabliertes und vertrauenswürdiges Image, das mehr Interesse und potenzielle neue Spieler anzieht.
2. **Erweiterung der Community:**
   - **Vervielfache die Zugangskanäle:** Mit der Rotation der sozialen Symbole kannst du verschiedene Plattformen deiner Community bewerben – von der offiziellen Website und dem Discord des Servers bis hin zu deinen Seiten auf YouTube, Instagram, Facebook oder TikTok. Jedes Symbol und jeder Link im **Discord Rich Presence** führt Interessierte direkt zu den aktiven Plattformen deiner Community.
   - **Sofortige Konnektivität:** Die "Join"-Funktion über Discord ermöglicht es Freunden deiner Spieler, mit nur einem Klick deinem Server beizutreten, wodurch Zugangsbarrieren reduziert und neue Mitglieder angezogen werden.
3. **Vereinfachte Inhaltsaktualisierung:**
   - Durch die Nutzung der [SPC Integration](https://github.com/spc-samp/spc-integration) werden Änderungen am Logo deines Servers oder der Liste sozialer Medien, die im Plugin [SPC Integration](https://github.com/spc-samp/spc-integration) **(auf Serverseite)** konfiguriert sind, automatisch für Spieler, die das **ASI** verwenden, übernommen, ohne dass diese das **ASI** aktualisieren müssen. Dies stellt sicher, dass die Informationen stets korrekt und aktuell sind.

### Wie man die SPC Integration auf deinem Server implementiert:

1. **SPC Integration Plugin:** Dein Server muss das Plugin [SPC Integration](https://github.com/spc-samp/spc-integration) installiert und korrekt konfiguriert haben. Dieses Plugin ist die Brücke, die die Informationen deines Servers an eine Datenliste der **SPC** sendet, die anschließend von der **SPC Integration API** verwendet wird, um öffentliche Informationen bereitzustellen.
2. **Konfiguration:** Folge den Anweisungen im Repository des Plugins [SPC Integration](https://github.com/spc-samp/spc-integration), um Folgendes zu konfigurieren:
   - Den Parameter `logo` mit der URL des Logos deines Servers.
   - Die Parameter für soziale Medien (`discord`, `website`, `youtube`, etc.) mit den gültigen Links zu deinen Plattformen.
3. **Automatische Aktualisierung:** Sobald die Informationen im Server-Plugin konfiguriert sind, erkennt das **SA-MP Rich Presence** diese automatisch und zeigt sie an. Es sind keine weiteren Aktionen seitens des Spielers erforderlich, außer der initialen Installation des **ASI**.

Durch die Integration deines Servers mit der [SPC Integration](https://github.com/spc-samp/spc-integration) verbesserst du nicht nur die Erfahrung deiner Spieler, sondern öffnest auch Türen für signifikantes Wachstum und Engagement deiner Community.

## Detaillierte technische Architektur

Das **SA-MP Rich Presence** verfügt über eine klar definierte modulare Architektur mit Komponenten, die auf spezifische Aufgaben fokussiert sind. Die Codebasis ist mit modernen C++-Standards (C++17 und C++20) ausgerichtet und verwendet `std::string_view`, `std::span` sowie Move-Semantik, um hohe Leistung, Sicherheit und Effizienz zu gewährleisten.

#### Hauptsystem (`main.cpp`)

Das Herz des **ASI** liegt in `main.cpp`, das den Lebenszyklus der Anwendung verwaltet, von der Initialisierung als DLL bis zum kontinuierlichen Update-Loop und einem sauberen Herunterfahren.

- **`DllMain`**: Der Einstiegspunkt des **ASI**, wenn es vom Betriebssystem geladen wird.
   ```cpp
   // DllMain (vereinfacht zur Darstellung der Struktur)
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
   In dieser Funktion wird bei der Prozessanbindung (`DLL_PROCESS_ATTACH`) unnötige Bibliotheksaufrufe verhindert (`DisableThreadLibraryCalls`) und ein neuer Thread (`Main_Update_Thread`) erstellt, um die Logik des **ASI** asynchron auszuführen, sodass das Spiel nicht blockiert wird. Beim Herunterfahren (`DLL_PROCESS_DETACH`) wird `Shutdown_Managers()` aufgerufen, um Ressourcen freizugeben.
- **`Main_Update_Thread`**: Die Seele des **ASI**, die in einem eigenen Thread läuft.
   ```cpp
   // Main_Update_Thread (Schlüsselabschnitt)
   DWORD WINAPI Main_Update_Thread(LPVOID) {
       // 1. Update-Überprüfung
       if (Asi_Update::Check_For_Update())
           return 0; // Wenn der Benutzer deaktiviert hat, beenden.
   
       // 2. Netzwerk-Initialisierung (Winsock)
       WSAData wsa_data;

       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
   
       // 3. Initialisierung der Server- und Discord-Manager
       Initialize_Managers();
   
       // 4. Hauptschleife für Updates
       while (is_running && v_server_manager && v_discord_manager) {
           v_server_manager->Update(); // Serverabfrage, SPC-API etc.
           v_discord_manager->Update_Presence( // Aktualisiert Discord-Status
               v_server_manager->Get_Server_Info(),
               v_server_manager->Get_Display_Social_Link(),
               v_server_manager->Get_Player_Name(),
               v_server_manager->Get_Current_Image_URL(),
               v_server_manager->Is_Connected());
   
           Discord_RunCallbacks(); // Verarbeitet Discord-RPC-Ereignisse
           std::this_thread::sleep_for(Constants::MAIN_LOOP_INTERVAL);
       }
   
       // 5. Herunterfahren (falls Manager vorhanden)
       if (v_discord_manager)
           v_discord_manager->Shutdown();

       WSACleanup(); // Freigabe von Winsock

       return 0;
   }
   ```
   Diese Funktion priorisiert die Update-Überprüfung. Anschließend initialisiert sie den Winsock-Netzwerkstack und die Instanzen der Server- und Discord-Manager. Eine persistente `while`-Schleife (gesteuert durch `std::atomic<bool> is_running` für sicheres Herunterfahren) koordiniert die Aufrufe von `Server_Manager::Update()` (Datenabfrage) und `Discord_Manager::Update_Presence()` (Senden an Discord). `Discord_RunCallbacks()` stellt sicher, dass Discord die Rich Presence-Ereignisse verarbeitet. Die Schleife wird periodisch mit `std::this_thread::sleep_for` pausiert, um Ressourcen zu schonen.

#### Updatesystem (`asi_update.hpp`)

Dieses lebenswichtige Modul fügt dem **ASI** Intelligenz hinzu, um sicherzustellen, dass Benutzer stets aktualisiert bleiben.

- **`Check_For_Update()`**: Die Hauptfunktion zur Update-Überprüfung.
   ```cpp
   // asi_update.hpp (Schlüsselabschnitt von Check_For_Update)
   inline bool Check_For_Update() {
       HINTERNET h_session = nullptr, h_connect = nullptr, h_request = nullptr;
       bool update_found_and_handled = false;
   
       try {
           h_session = WinHttpOpen(L"SA-MP Rich Presence Update/1.0", ...);
           // ... (GET-Anfrage an Constants::UPDATE_API_PATH in der GitHub-API) ...
           std::string response_body;
           // ... (Lesen der HTTP-Antwort) ...
           nlohmann::json release_info = nlohmann::json::parse(response_body);
   
           std::string latest_tag = release_info["tag_name"].get<std::string>();
           // ... (Vergleich der Versionen mit sscanf_s/sscanf) ...
   
           if (latest_major > current_major || (latest_major == current_major && latest_minor > current_minor)) {
               update_found_and_handled = true;
               std::wstringstream message_stream;
               // ... (Vorbereitung der MessageBox-Nachricht) ...
               int msgbox_result = MessageBoxW(NULL, message_stream.str().c_str(), L"SA-MP Rich Presence - Update Available", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
               
               if (msgbox_result == IDYES)
                   ShellExecuteW(NULL, L"open", Constants::UPDATE_RELEASES_URL, NULL, NULL, SW_SHOWNORMAL);
           }
       }
       catch (const std::exception&) { /* Fehlerbehandlung */ }
   
       // ... (Schließen der WinHttp-Handles) ...
       return update_found_and_handled;
   }
   ```
   Unter Verwendung der **WinHTTP API** für Netzwerkanfragen führt `Check_For_Update` eine `GET`-Anfrage an den Endpunkt `/releases/latest` der GitHub-API für das Projekt-Repository durch. Die JSON-Antwort wird mit der Bibliothek `nlohmann/json` geparst. Die neueste Version (`tag_name`) wird numerisch mit der kompilierten Version des **ASI** verglichen. Wird eine neue Version erkannt, wird ein Dialogfeld (`MessageBoxW`) angezeigt, das den Benutzer fragt, ob er zur Download-Seite über `ShellExecuteW` navigieren möchte. Der gesamte Prozess ist in einem `try-catch` eingebettet, um sicherzustellen, dass Netzwerk- oder Parsingfehler den Spielstart nicht beeinträchtigen.

#### Discord-Manager (`discord_manager.cpp`)

Die Klasse `Discord_Manager` abstrahiert die Interaktionen mit der **Discord RPC**-Bibliothek und verwaltet die Initialisierung der Verbindung sowie das Senden von Daten an den Präsenzstatus des Benutzers.

- **`Initialize()`**: Richtet die Kommunikation mit Discord ein.
   ```cpp
   // discord_manager.cpp (Schlüsselabschnitt von Initialize)
   void Discord_Manager::Initialize() noexcept {
       DiscordEventHandlers handlers;
       memset(&handlers, 0, sizeof(handlers)); // Sicherstellung der Initialisierung
       
       // App ID wird hier entschlüsselt
       auto app_id_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_Discord_App_ID());
       Discord_Initialize(app_id_accessor.Get(), &handlers, 1, nullptr);
   
       start_timestamp_ = time(nullptr); // Registriert den Sitzungsstart
   }
   ```
   Der Aufruf von `Discord_Initialize` ist entscheidend und verwendet die `DISCORD_APP_ID`, die sicher durch die String-Verschleierung in `secrets.hpp` bezogen wird. Der `start_timestamp_` wird hier festgelegt, um die Spielzeit in der Discord-Präsenz zu berechnen.
- **`Update_Presence()`**: Die zentrale Funktion, die die Rich Presence in Discord aktualisiert.
   ```cpp
   // discord_manager.cpp (Schlüsselabschnitt von Update_Presence)
   void Discord_Manager::Update_Presence(const Server_Information& server_info, const server_types::Social_Link& social_link, const std::string_view player_name, const std::string_view current_image, const bool is_connected) noexcept {
       DiscordRichPresence discord_presence;
       memset(&discord_presence, 0, sizeof(discord_presence));
   
       discord_presence.startTimestamp = start_timestamp_;
       discord_presence.largeImageKey = current_image.data(); // Serverlogo
   
       if (is_connected) {
           discord_presence.details = server_info.Hostname.c_str();
           discord_presence.state = player_name.data();
           discord_presence.largeImageText = server_info.Server_Address.c_str(); // IP:Port
           discord_presence.partySize = server_info.Players;
           discord_presence.partyMax = server_info.Max_Players;
           discord_presence.joinSecret = server_info.Server_Address.c_str(); // Aktiviert den "Join"-Button
   
           // Verwaltet das rotierende soziale Symbol
           if (!social_link.first.empty()) {
               current_small_image_key_ = Constants::SOCIAL_ICON_BASE_URL;
               current_small_image_key_ += social_link.first; // z.B. "discord.png"
               current_small_image_key_ += ".png";
               discord_presence.smallImageKey = current_small_image_key_.c_str();
               discord_presence.smallImageText = social_link.second.c_str(); // Text bei Mauszeiger (Link/Name)
           }
       }
       else {
           discord_presence.details = "SA-MP"; // Zustand "Idle"
           discord_presence.state = "Idle";
           discord_presence.largeImageText = "San Andreas Multiplayer";
           // smallImageKey und smallImageText bleiben leer für den Idle-Zustand
       }
   
       Discord_UpdatePresence(&discord_presence);
   }
   ```
   Füllt die Struktur `DiscordRichPresence` basierend auf dem Verbindungsstatus. Wenn `is_connected` wahr ist, werden Hostname, Spieleranzahl, Server-IP und Spielername angezeigt. Der `largeImageKey` definiert das Hauptbild des Servers. Insbesondere wird `joinSecret` gesetzt, um Freunden das direkte Verbinden zu ermöglichen, und der `smallImageKey` (dynamisch basierend auf dem bereitgestellten `social_link` erstellt) zeigt die rotierenden sozialen Symbole an. Im "Idle"-Zustand wird die Präsenz vereinfacht, um die Inaktivität widerzuspiegeln. Schließlich sendet `Discord_UpdatePresence` die Daten an Discord.

#### Server-Manager (`server_manager.cpp`)

Der `Server_Manager` ist der Orchestrator der Daten, verwaltet den Verbindungsstatus, fragt den Server und die **SPC Integration API** ab und entscheidet, welche Informationen wann angezeigt werden sollen.

- **`Update()`**: Der Hauptlebenszyklus für die Datensammlung.
   ```cpp
   // server_manager.cpp (Schlüsselabschnitt von Update)
   void Server_Manager::Update() {
       const auto now = std::chrono::steady_clock::now();
   
       if (server_query.Query(live_server_data)) { // Versucht, Daten über SAMP-Abfrage zu erhalten
           if (!connection_status) { // Wenn gerade verbunden/reverbunden
               connection_status = true;
               Fetch_API_Data(); // Ruft Logo und soziale Medien von der API ab
           }
           
           last_successful_query = now;
   
           // Aktualisiert die anzuzeigenden Daten für Discord
           display_server_data.Hostname = live_server_data.Hostname;
           display_server_data.Players = live_server_data.Players;
           display_server_data.Max_Players = live_server_data.Max_Players;
           display_server_data.Server_Address = server_ip + ":" + std::to_string(server_port);
   
           if (now - last_api_update > Constants::IMAGE_UPDATE_INTERVAL)
               Fetch_API_Data(); // Erneute API-Abfrage nach definiertem Zeitintervall
   
           if (now - last_social_rotation > Constants::SOCIAL_UPDATE_INTERVAL)
               Rotate_Social_Link(); // Rotiert das soziale Symbol
       }
       else { // Wenn die Abfrage fehlschlägt
           if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
               connection_status = false; // Nach Timeout als getrennt betrachtet
               display_image_url = Constants::DEFAULT_IMAGE;
               display_server_data = {}; // Löscht Daten
               current_display_social = {}; // Löscht soziale Daten
           }
       }
   }
   ```
   Die Funktion `Update` versucht, eine Serverabfrage durchzuführen. Bei Erfolg aktualisiert sie die Daten in `live_server_data` und `display_server_data`. Bedingt ruft sie `Fetch_API_Data()` auf, um Bild und soziale Links zu aktualisieren (bei neuer Verbindung oder wenn `IMAGE_UPDATE_INTERVAL` verstrichen ist) und `Rotate_Social_Link()`, um die sozialen Symbole zu wechseln (`SOCIAL_UPDATE_INTERVAL`). Wenn Serverabfragen kontinuierlich für mehr als 15 Sekunden fehlschlagen, wird der Verbindungsstatus als verloren betrachtet, und die angezeigten Informationen werden zurückgesetzt.
- **`Fetch_API_Data()`**: Verantwortlich für das Abrufen der visuellen und sozialen Daten.
   ```cpp
   // server_manager.cpp (Schlüsselabschnitt von Fetch_API_Data)
   void Server_Manager::Fetch_API_Data() {
       display_image_url = url_manager.Get_Image_URL_And_Populate_Socials(server_ip, server_port, live_server_data);
       last_api_update = std::chrono::steady_clock::now();
       current_social_index_ = 0; // Setzt Index nach neuem API-Abruf zurück
       Rotate_Social_Link(); // Stellt sicher, dass sofort ein soziales Symbol angezeigt wird
   }
   ```
   Diese Funktion koordiniert mit `URL_Manager`, um das Logo und die sozialen Links von der API abzurufen, aktualisiert den `display_image_url` und füllt die `Social_Links` in `live_server_data`. Setzt den Rotationsindex zurück und ruft `Rotate_Social_Link()` auf, um sicherzustellen, dass das erste Symbol sofort bereit zur Anzeige ist.
- **`Rotate_Social_Link()`**: Logik zum Wechseln der sozialen Symbole.
   ```cpp
   // server_manager.cpp (Schlüsselabschnitt von Rotate_Social_Link)
   void Server_Manager::Rotate_Social_Link() {
       if (!live_server_data.Social_Links.empty()) {
           if (current_social_index_ >= live_server_data.Social_Links.size())
               current_social_index_ = 0; // Startet den Zyklus neu
   
           current_display_social = live_server_data.Social_Links[current_social_index_];
           current_social_index_ = (current_social_index_ + 1) % live_server_data.Social_Links.size();
       }
       else
           current_display_social = {}; // Löscht, wenn keine sozialen Links vorhanden
       
       last_social_rotation = std::chrono::steady_clock::now();
   }
   ```
   Diese einfache Funktion wählt den nächsten `Social_Link` in der Liste von `live_server_data.Social_Links` zyklisch aus und speichert ihn in `current_display_social`, damit der `Discord_Manager` ihn verwenden kann.

#### Netzwerksystem (`samp_network.cpp`)

Die Klasse `Samp_Network` ist die Low-Level-Implementierung der **UDP**-Kommunikation, verantwortlich für das Öffnen und Verwalten des Sockets für SA-MP-Abfragen. Sie bietet nun Konstruktoren und Move-Operatoren für eine bessere Ressourcenverwaltung.

- **`Initialize()`**: Richtet den Socket für die **UDP**-Kommunikation ein.
   ```cpp
   // samp_network.cpp (Schlüsselabschnitt von Initialize)
   bool Samp_Network::Initialize(const std::string_view ip, const int port) noexcept {
       if (network_socket != INVALID_SOCKET)
           closesocket(network_socket); // Schließt vorhandenen Socket
   
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       if (network_socket == INVALID_SOCKET)
           return false;
   
       const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
       setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
   
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(static_cast<u_short>(port));
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr); // Unterstützung für IPv4
       return true;
   }
   ```
   Initialisiert den Socket, setzt Timeouts für Sende- und Empfangsvorgänge und konfiguriert die Adressstruktur (`sockaddr_in`) mit der IP und dem Port des Zielservers unter Verwendung von `inet_pton` für die IP-Konvertierung.
- **`Send_Query()`**: Sendet ein Abfragepaket und empfängt die Antwort.
   ```cpp
   // samp_network.cpp (Schlüsselabschnitt von Send_Query)
   bool Samp_Network::Send_Query(const std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept {
       // Sendet das UDP-Paket
       if (sendto(network_socket, query_packet.data(), static_cast<int>(query_packet.size()), 0, reinterpret_cast<const sockaddr*>(&server_address), sizeof(server_address)) < 0)
           return false;
   
       sockaddr_in from_address;
       int address_length = sizeof(from_address);
       // Empfängt die Antwort
       received_bytes = recvfrom(network_socket, response_buffer.data(), static_cast<int>(response_buffer.size()), 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);
   
       return received_bytes > Constants::QUERY_PACKET_SIZE;
   }
   ```
   Diese Methode sendet das `query_packet` (als `std::span` übergeben für Puffesicherheit) an den Server. Anschließend versucht sie, eine Antwort in den `response_buffer` zu empfangen. Der Rückgabewert zeigt an, ob die Operation erfolgreich war und ob mehr Bytes als die Größe des Abfragepakets empfangen wurden.

#### Serverabfrage (`server_query.cpp`)

Die Klasse `Server_Query` ist speziell für die Implementierung des SA-MP-Abfrageprotokolls (`'i'`) zuständig und extrahiert grundlegende Serverinformationen (Spieler, Hostname) aus den **UDP**-Antworten.

- **`Query()`**: Verwaltet die Abfrageversuche.
   ```cpp
   // server_query.cpp (Schlüsselabschnitt von Query)
   bool Server_Query::Query(Server_Information& server_data) noexcept {
       for (int attempt = 0; attempt < Constants::MAX_RETRY_ATTEMPTS; ++attempt) {
           if (Try_Query(server_data))
               return true; // Erfolgreiche Abfrage
   
           if (attempt < Constants::MAX_RETRY_ATTEMPTS - 1)
               // Kurze Pause vor erneutem Versuch, um Flooding zu vermeiden
               std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)));
       }

       return false; // Alle Versuche fehlgeschlagen
   }
   ```
   Implementiert eine Wiederholungsstrategie mit `MAX_RETRY_ATTEMPTS` und einem exponentiellen Back-off (`std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)))`), um robuste Abfragen zu gewährleisten und Netzwerksättigung zu vermeiden. Ruft bei jedem Versuch `Try_Query` auf.
- **`Assemble_Query_Packet()`**: Baut das SA-MP-Abfragepaket zusammen.
   ```cpp
   // server_query.cpp (Schlüsselabschnitt von Assemble_Query_Packet)
   void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
       memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
       packet = 'i'; // Code für Informationsabfrage
   }
   ```
   Das Standardpaket für die Informationsabfrage (`'i'`) von SA-MP wird erstellt, einschließlich der Signatur "SAMP" und des Identifikationsbytes 'i'.
- **`Parse_Response()`**: Entpackt die binäre Serverantwort.
   ```cpp
   // server_query.cpp (Schlüsselabschnitt von Parse_Response)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       if (response.size() <= Constants::QUERY_PACKET_SIZE) 
           return false;
   
       auto data_span = response.subspan(Constants::QUERY_PACKET_SIZE); // Überspringt den Header
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Ignoriert, aber gelesen
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false;

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false;

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false;
   
       // Hinweis: Gamemode und Language werden automatisch von Read_String_From_Span übersprungen, wenn das Paket weitere Daten enthält.
       // Wenn andere Felder benötigt werden, einfach einen String erstellen und Read_String_From_Span(data_span, string_variable) aufrufen;
       return true;
   }
   ```
   Diese Methode liest sicher die Daten aus dem `response_buffer` (unter Verwendung von `std::span` und den Hilfsfunktionen `Read_From_Span` und `Read_String_From_Span`). Sie extrahiert die Anzahl der Spieler, die maximale Anzahl der Spieler und den Hostnamen des Servers und füllt die Struktur `Server_Information`. Nicht verwendete Felder (wie ob der Server passwortgeschützt ist) werden gelesen, aber ignoriert, und andere wie "Gamemode" und "Language" werden übersprungen, wenn die Antwort mehr Daten enthält, als das **ASI** benötigt.
- **Hilfsfunktionen für das Lesen:**
   ```cpp
   // server_query.hpp (Auszüge der Lesehilfsfunktionen)
   template<typename T>
   static bool Read_From_Span(std::span<const char>& s, T& value) noexcept;
   
   static bool Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept;
   ```
   `Read_From_Span` behandelt das Lesen von festen Typen (Integer, Booleans) aus dem `std::span` und bewegt den `span` vorwärts. `Read_String_From_Span` liest die Länge einer Zeichenkette (als `uint32_t`) und dann die eigentliche Zeichenkette und bewegt den `span` ebenfalls vorwärts. Dies gewährleistet Sicherheit beim Parsen von Bytes und verhindert Lesevorgänge außerhalb der Puffergrenzen.

#### URL-Manager (`url_manager.cpp`)

Die Klasse `URL_Manager` verwaltet die HTTPS-Kommunikation mit der **SPC Integration API**, ein zentrales Element für die neuen visuellen und sozialen Funktionen der **Discord Rich Presence**.

- **`Get_Image_URL_And_Populate_Socials()`**: Die High-Level-Methode zum Abrufen von API-Informationen.
   ```cpp
   // url_manager.cpp (Schlüsselabschnitt von Get_Image_URL_And_Populate_Socials)
   std::string URL_Manager::Get_Image_URL_And_Populate_Socials(const std::string& ip, const int port, Server_Information& server_info) {
       if (!session_handle)
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);
   
       auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
       std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
       path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   
       const std::string json_data = Request_API_Data(path); // HTTP-Anfrage an die API
   
       if (json_data.empty())
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE); // Fehler bei der Anfrage
   
       return Parse_API_Response(json_data, server_info); // Parst und füllt server_info
   }
   ```
   Erhält IP und Port, erstellt die API-URL mit diesen als Parameter. Ruft `Request_API_Data` auf, um die JSON-Daten abzurufen. Bei Erfolg wird `Parse_API_Response` aufgerufen, um die Bild-URL (Logo) zu extrahieren und die Liste der sozialen Links in `server_info` zu füllen.
- **`Request_API_Data()`**: Führt die HTTPS-Anfrage an die API durch.
   ```cpp
   // url_manager.cpp (Schlüsselabschnitt von Request_API_Data)
   std::string URL_Manager::Request_API_Data(const std::wstring& path) {
       auto api_host_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Host());
       const std::wstring wide_host = Utils::Convert_Utf8_To_Wide_String(api_host_accessor.Get());
       HINTERNET connect_handle = WinHttpConnect(session_handle, wide_host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
   
       if (!connect_handle) return "";
   
       HINTERNET request_handle = WinHttpOpenRequest(connect_handle, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
   
       if (!request_handle) return (WinHttpCloseHandle(connect_handle), "");
   
       // Anfrage senden, Antwort empfangen, Status 200 prüfen, Daten in Schleife lesen
       // ... (Details zu WinHttpSendRequest, WinHttpReceiveResponse, WinHttpQueryHeaders, WinHttpReadData) ...
       
       WinHttpCloseHandle(request_handle); WinHttpCloseHandle(connect_handle);
       return response_body; // Gibt JSON als String zurück
   }
   ```
   Verbindet sich mit dem API-Host (sicher bezogen), öffnet und sendet eine `GET`-Anfrage mit dem Pfad (`path`). Behandelt die HTTP-Antwort, prüft den Statuscode (200 OK für Erfolg) und liest den vollständigen Antwortkörper (der JSON sein sollte). Alle WinHTTP-Handles werden bei Erfolg oder Fehler freigegeben.
- **`Parse_API_Response()`**: Verarbeitet die JSON-Zeichenkette, um Daten zu extrahieren.
   ```cpp
   // url_manager.cpp (Schlüsselabschnitt von Parse_API_Response)
   std::string URL_Manager::Parse_API_Response(const std::string& json_content, Server_Information& server_info) {
       server_info.Social_Links.clear(); // Löscht vorhandene soziale Links
       try {
           const auto json = nlohmann::json::parse(json_content);
   
           if (json.value("success", false) && json.contains("data") && json["data"].contains("public")) {
               const auto& public_data = json["data"]["public"];
               const std::vector<std::string> social_keys = { "website", "discord", "youtube", "instagram", "facebook", "tiktok" };
               
               // Extrahiert und füllt soziale Links
               for (const auto& key : social_keys) {
                   if (public_data.contains(key)) {
                       std::string value = public_data.value(key, "not-defined");

                       if (!value.empty() && value != "not-defined")
                           server_info.Social_Links.push_back({ key, value });
                   }
               }

               return public_data.value("logo", ""); // Gibt die Logo-URL zurück
           }
       }
       catch (const nlohmann::json::exception&) { /* Behandelt Parsingfehler */ }

       return ""; // Parsingfehler
   }
   ```
   Verwendet `nlohmann::json::parse`, um die JSON-Zeichenkette in ein manipulierbares JSON-Objekt umzuwandeln. Navigiert durch die Struktur (`success`, `data`, `public`) und extrahiert das `logo` (wird zu `display_image_url`) und iteriert über vordefinierte Schlüssel, um die `Social_Links` von `server_info` zu füllen.

### Code-Struktur

Das Projekt **SA-MP Rich Presence** ist sorgfältig in einem klaren Verzeichnislayout organisiert, mit dem Quellcode (`src/`) und einem Unterverzeichnis für externe Bibliotheken (`libraries/`). Die Dateinamen folgen der Konvention `_manager` oder `_network` für Klarheit über den Zweck jeder Klasse. Die meisten Header-Dateien verwenden die Erweiterung `.hpp`, was anzeigt, dass es sich um C++-Header handelt.

```
src/
├── libraries/               # Enthält essentielle Drittanbieter-Bibliotheken
│   ├── Dralyxor/            # Bibliothek zur String-Verschleierung
│   ├── Discord/             # Offizielle Discord-RPC-Bibliothek
│   └── nlohmann/            # Bibliothek zur JSON-Manipulation
├── asi_update.hpp           # Definition des automatischen Updatesystems
├── command_line_parser.hpp  # Definition des Kommandozeilen-Parsers
├── constants.hpp            # Definitionen globaler Konstanten des Projekts
├── discord_manager.hpp      # Definition des Managers für die Kommunikation mit Discord
├── main.cpp                 # Einstiegspunkt des ASI und Hauptorchestrator
├── samp_network.hpp         # Definition des Netzwerkmanagers für SA-MP-Abfragen
├── secrets.hpp              # Definitionen für die Verschleierung von Geheimnissen
├── server_manager.hpp       # Definition des Managers für Serverinformationen
├── server_query.hpp         # Definition der Logik für Serverabfragen
├── server_types.hpp         # Definitionen von Datenstrukturen des Servers
├── url_manager.hpp          # Definition des URL-Managers für die SPC Integration API
└── utils.hpp                # Allgemeine Hilfsfunktionen (String-Konvertierung)
```

#### Globale Konstanten (`constants.hpp`)

Diese Datei zentralisiert alle Konfigurationen und unveränderlichen Werte des Projekts, die global zugänglich sind. Sie verwendet `inline constexpr`, um sicherzustellen, dass die Konstanten direkt für den Compiler verfügbar sind, was die Leistung optimiert.

```cpp
// constants.hpp (Auszug)
namespace Constants {
    inline constexpr char ASI_VERSION[] = "1.1"; // Version für das Updatesystem
    inline constexpr wchar_t UPDATE_API_HOST[] = L"api.github.com"; // Host der Update-API
    inline constexpr char DEFAULT_IMAGE[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/default_logo.png"; // Standardbild
    inline constexpr int QUERY_TIMEOUT_MS = 800; // Timeout der Abfrage in ms
    inline constexpr std::chrono::seconds MAIN_LOOP_INTERVAL = std::chrono::seconds(1); // Intervall der Hauptschleife
}
```
Wichtige Details wie API-URLs, Standardbildpfade, Netzwerk-Timeouts und Update-Intervalle für die **Discord Rich Presence** sind hier zentralisiert. Die Verwendung von `std::chrono::seconds` für Intervalle verbessert die Lesbarkeit und verhindert Einheitenfehler.

#### Datenstrukturen (`server_types.hpp`)

Diese Datei definiert die `structs` und `using`, die wichtig sind, um die gesammelten und angezeigten Daten zu organisieren.

```cpp
// server_types.hpp (Auszug)
namespace server_types {
    using Social_Link = std::pair<std::string, std::string>; // Tupel (Name des Mediums, URL/Wert)
}

struct Server_Information {
    uint16_t Players{0};           // Anzahl aktueller Spieler
    uint16_t Max_Players{0};       // Maximale Spielerkapazität
    std::string Hostname{};        // Name des Servers
    std::string Server_Address{};  // z.B. "192.168.1.1:7777"

    std::vector<server_types::Social_Link> Social_Links{}; // Liste der sozialen Links des Servers
};
```
Die `Server_Information` ist die primäre Struktur, die die Serverdaten speichert. Die Hinzufügung von `std::vector<server_types::Social_Link> Social_Links` spiegelt die neue Fähigkeit wider, mehrere soziale Medien-Links von der API zu ziehen, organisiert als Paare `(Name_des_Mediums, Link)`.

#### Verschleierung von Geheimnissen (`secrets.hpp`)

Diese Datei ist darauf ausgelegt, sensible Informationen wie die **Discord Application ID** und die Adressen der **SPC Integration API (vorläufig)** vor einfachem Reverse Engineering zu schützen.

```cpp
// secrets.hpp (Auszug)
#include "libraries/Dralyxor/dralyxor.hpp"

namespace Secrets {
    namespace {
        inline auto& Get_Obfuscated_Discord_App_ID() {
            static auto& dc_app_id_obfuscated = DRALYXOR_KEY("DISCORD_APP_ID", "YOUR_SECRET_KEY_HERE");

            return dc_app_id_obfuscated;
        }
        // ... (weitere verschlüsselte Geheimnisse) ...
    }
    namespace Detail {
        inline auto& Get_Discord_App_ID() {
            return Get_Obfuscated_Discord_App_ID();
        }
        // ... (öffentliche Getter für den Zugriff auf entschlüsselte Geheimnisse) ...
    }
}
```
Die Bibliothek [Dralyxor](https://github.com/ocalasans/dralyxor) wird mit dem Makro `DRALYXOR_KEY` verwendet, um String-Literale im kompilierten Binärcode zu verschlüsseln. `DRALYXOR_SECURE` wird dann zur Laufzeit verwendet, um diese Werte bei Bedarf zu entschlüsseln, was eine robuste Sicherheitsschicht gegen statische Schlüsselauslese hinzufügt.

#### Allgemeine Hilfsfunktionen (`utils.hpp`)

Eine Datei für generische Hilfsfunktionen, die in verschiedenen Modulen nützlich sein können, um Code-Duplikation zu vermeiden.

```cpp
// utils.hpp (Auszug)
namespace Utils {
    inline std::string Convert_Wide_To_Utf8_String(const std::wstring_view wide_string) {
        // ... (Implementierung der Konvertierung mit WideCharToMultiByte) ...
    }

    inline std::wstring Convert_Utf8_To_Wide_String(const std::string_view narrow_string) {
        // ... (Implementierung der Konvertierung mit MultiByteToWideChar) ...
    }
}
```
Enthält die Funktionen `Convert_Wide_To_Utf8_String` und `Convert_Utf8_To_Wide_String`, die für Interoperationen mit Windows-APIs (die UTF-16 verwenden) und Standard-C++-Operationen (die normalerweise von UTF-8 profitieren) unerlässlich sind. Diese Funktionen verwenden Windows-APIs für eine sichere und effiziente Konvertierung.

### Fehlerbehandlung und Robustheit

Das **SA-MP Rich Presence** wurde mit Blick auf Robustheit entwickelt und integriert mehrere Mechanismen zur Behandlung von Netzwerkfehlern, ungültigen Eingaben und Dienstunverfügbarkeit.

- **Netzwerk-Timeouts und Wiederholungen:**
   - **Explizite Timeouts:** Netzwerksockets in `samp_network.cpp` setzen Timeouts (`Constants::QUERY_TIMEOUT_MS`) für Sende- und Empfangsvorgänge, um zu verhindern, dass das Programm bei einem inaktiven Server "hängen bleibt".
      ```cpp
      // samp_network.cpp (Timeout-Konfiguration)
      const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
      setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      ```
   - **Mehrfache Abfrageversuche:** Der `Server_Query` führt `Constants::MAX_RETRY_ATTEMPTS` Abfragen bei Fehlschlägen aus. Ein exponentieller Back-off (`std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)))`) wird implementiert, um vor erneuten Versuchen zu warten, was die Belastung reduziert und die Erfolgschancen bei instabilen Netzwerkbedingungen erhöht.
- **Robuste Behandlung von Verbindungsabbrüchen:**
   - **Sanfter Zustandsübergang:** In `server_manager.cpp` wird der Verbindungsstatus (`connection_status`) nicht sofort nach einem einzelnen Abfragefehler geändert. Nur wenn 15 Sekunden lang keine Antwort empfangen wird (`now - last_successful_query > std::chrono::seconds(15)`), wird der Status auf `false` aktualisiert. Dies verhindert ein "Flackern" der Discord-Präsenz aufgrund kleiner Paketverluste.
      ```cpp
      // server_manager.cpp (Logik für Verbindungsabbruch)
      else { // Wenn die Abfrage fehlschlägt
          if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
              connection_status = false;
              display_image_url = Constants::DEFAULT_IMAGE;
              display_server_data = {};
              current_display_social = {};
          }
      }
      ```
   - **Visuelles Fallback:** Bei erkannter Trennung wird das Bild der Discord-Präsenz auf `Constants::DEFAULT_IMAGE` zurückgesetzt, und die Server-/Sozialdaten werden gelöscht, um dem Benutzer ein klares Feedback zu geben, dass er nicht mehr verbunden ist.
- **Behandlung ungültiger Eingaben:**
   - **`command_line_parser.cpp`:** Beim Konvertieren des Port-Arguments von einer Zeichenkette in einen Integer (`std::stoi`) wird ein `try-catch`-Block verwendet, um `std::invalid_argument` (keine Zahl) oder `std::out_of_range` (Zahl zu groß/klein) zu behandeln. Bei einem Fehler wird der Standardport beibehalten oder das Parsen schlägt kontrolliert fehl, um Abstürze zu verhindern.
- **Robustheit beim Abrufen von API-Daten:**
   - **WinHTTP-Fehler:** Alle WinHTTP-Operationen in `url_manager.cpp` werden auf `null`-Handles und `false`-Rückgabewerte in jedem Schritt (Öffnen der Sitzung, Verbinden, Öffnen der Anfrage, Senden/Empfangen, Lesen von Daten) überprüft, um partielle Fehler abzufangen.
   - **HTTP-Statuscodes:** Nach einer HTTP-Anfrage überprüft `url_manager.cpp` den `HTTP Status Code`. Nur ein Code `200 OK` wird als Erfolg akzeptiert, wobei Fehlerantworten vom Server oder Gateway verworfen werden.
   - **Sicheres JSON-Parsing:** `url_manager.cpp` schließt das JSON-Parsing (`nlohmann::json::parse`) in einen `try-catch(const nlohmann::json::exception&)`-Block ein. Dies verhindert, dass fehlerhafte oder unvollständige JSONs von der API einen Absturz verursachen, indem leere Strings oder das Standardbild zurückgegeben werden.
- **Sichere Update-Mechanismen:**
   - **`asi_update.hpp`:** Der Update-Überprüfungsprozess in `Check_For_Update` ist in einen `try-catch(const std::exception&)`-Block eingebettet. Dies stellt sicher, dass selbst wenn GitHub offline ist, das Netzwerk instabil ist oder die JSON-Antwort ungültig ist, das **ASI** nicht abstürzt und das Spiel ohne Unterbrechung geladen werden kann, indem die Update-Überprüfung sicher ignoriert wird.
   - **Verwaltung von WinHTTP-Handles:** Die Freigabe von `HINTERNET`-Handles in `asi_update.hpp` und `url_manager.cpp` ist sorgfältig geplant, um in allen Codepfaden (Erfolg und Fehler) ausgeführt zu werden, um Ressourcenlecks zu verhindern.

### Kommandozeilenverarbeitungssystem

Das **SA-MP Rich Presence** extrahiert entscheidende Informationen für seinen Betrieb (Server-IP, Port und Spielername) direkt aus der Kommandozeile von Grand Theft Auto: San Andreas. Diese Methode stellt sicher, dass das **ASI** die genauesten und relevantesten Daten erhält, sobald das Spiel initialisiert oder ein Server verbunden wird.

#### Kommandozeilen-Parser (`command_line_parser.cpp`)

Die Klasse `Command_Line_Parser` ist dafür verantwortlich, die gesamte Kommandozeilen-Zeichenkette des Prozesses zu analysieren, spezifische Parameter zu identifizieren und zu extrahieren, die von SA-MP verwendet werden.

- **`Parse()`**: Der Einstiegspunkt für die Kommandozeilenanalyse.
   ```cpp
   // command_line_parser.cpp (Schlüsselabschnitt von Parse)
   bool Command_Line_Parser::Parse(const std::wstring_view command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       server_ip = Constants::DEFAULT_SERVER_IP; // Standardwerte
       server_port = Constants::DEFAULT_SERVER_PORT;
   
       if (const auto ip_param = Parse_Parameter(command_line, L"-h"); !ip_param.empty())
           server_ip = Utils::Convert_Wide_To_Utf8_String(ip_param); // Extrahiert und konvertiert IP
   
       if (const auto port_param = Parse_Parameter(command_line, L"-p"); !port_param.empty()) {
           try {
               server_port = std::stoi(std::wstring(port_param)); // Extrahiert und konvertiert Port (mit Fehlerbehandlung)
           }
           catch (const std::invalid_argument&) {}
           catch (const std::out_of_range&) {}
       }
   
       if (const auto name_param = Parse_Parameter(command_line, L"-n"); !name_param.empty())
           player_name = Utils::Convert_Wide_To_Utf8_String(name_param); // Extrahiert und konvertiert Name
   
       return !server_ip.empty() && server_port > 0 && !player_name.empty(); // Validiert, ob wesentliche Daten vorhanden sind
   }
   ```
   Erhält die Kommandozeile (`command_line`) als `std::wstring_view` für Effizienz. Verwendet `Parse_Parameter`, um die Werte für `-h` (Host/IP), `-p` (Port) und `-n` (Spielername) zu finden und zu extrahieren. Die extrahierten Werte (in `std::wstring_view`) werden mit `Utils::Convert_Wide_To_Utf8_String` in `std::string` (UTF-8) konvertiert. Für den Port wird ein `try-catch`-Block um `std::stoi` verwendet, um Konvertierungsfehler sicher zu handhaben. Die Funktion gibt `true` zurück, wenn alle entscheidenden Parameter (IP, gültiger Port und Spielername) erhalten wurden.
- **`Parse_Parameter()`**: Die Hilfsfunktion zur Extraktion eines einzelnen Parameters.
   ```cpp
   // command_line_parser.cpp (Schlüsselabschnitt von Parse_Parameter)
   std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring_view command_string, const std::wstring_view parameter) {
       if (const size_t position = command_string.find(parameter); position != std::wstring_view::npos) {
           size_t value_start = position + parameter.length();
           value_start = command_string.find_first_not_of(L" \t", value_start); // Überspringt Leerzeichen nach dem Parameter

           if (value_start == std::wstring_view::npos)
               return L""; // Parameter gefunden, aber kein Wert
   
           const size_t value_end = command_string.find(L' ', value_start); // Findet das nächste Leerzeichen (Ende des Werts)
           
           return std::wstring(command_string.substr(value_start, value_end - value_start)); // Gibt die Wert-Substring zurück
       }

       return L""; // Parameter nicht gefunden
   }
   ```
   Lokalisiert die Substring des `parameter` (`-h`, `-p`, `-n`) in der `command_string`. Berechnet die Startposition des Werts, ignoriert Leerzeichen/Tabulatoren. Ermittelt die Endposition des Werts (nächstes Leerzeichen) und gibt die Substring zurück, die dem Wert des Parameters entspricht.

### SA-MP Kommunikationsprotokoll

Das **ASI** interagiert direkt mit SA-MP-Servern unter Verwendung des **UDP**-Abfrageprotokolls, um wichtige Echtzeitinformationen zu extrahieren. Diese Kommunikation ist so implementiert, dass sie effizient und widerstandsfähig gegen Netzwerkfehler ist.

#### Protokollimplementierung

Die Klasse `Server_Query` ist das Rückgrat dieser Implementierung und verwaltet das Senden von Paketen und die Interpretation der Antworten.

- **Struktur des SA-MP-Abfragepakets (`'i'`)**: Das **ASI** erstellt ein **UDP**-Paket von 11 Bytes für die Informationsabfrage:
   - `BYTE 0-3`: Signatur "SAMP" (S A M P).
   - `BYTE 4-9`: Sequenz von 6 Bytes (in der Regel die Quell-IP-Adresse der Anfrage, damit der Server den Client erkennt).
   - `BYTE 10`: Identifikator der Abfrage 'i' (ASCII 105), der anzeigt, dass das **ASI** allgemeine Serverinformationen (Hostname, Spieler, etc.) wünscht.
      ```cpp
      // server_query.cpp (Paketzusammenstellung)
      void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
          memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
          packet = 'i'; // Informationsabfrage (Information)
      }
      ```
- **Struktur der Serverantwort**: Wenn ein SA-MP-Server auf eine Abfrage 'i' antwortet, sendet er ein **UDP**-Paket mit einer strukturierten Datenfolge, die das **ASI** parsen muss:
   - **Antwort-Header:** Wiederholung der Signatur "SAMP" und der 6-Byte-Sequenz des Anfragepakets. Das **ASI** überspringt einfach diese `Constants::QUERY_PACKET_SIZE` Bytes.
   - **Passworded (`bool`):** Ein Byte, das angibt, ob der Server passwortgeschützt ist. Wird gelesen, aber nicht verwendet.
   - **Players (`uint16_t`):** Die Anzahl der aktuell mit dem Server verbundenen Spieler.
   - **Max_Players (`uint16_t`):** Die maximale Anzahl an Spielerslots, die der Server unterstützt.
   - **Hostname (string mit `uint32_t` Präfix):** Der benutzerfreundliche Name des Servers. Das Paket enthält einen `uint32_t`, der die Länge der Hostname-Zeichenkette angibt, gefolgt von den eigentlichen String-Bytes.
   - **Weitere Felder:** Das SA-MP-Protokoll fährt mit "Gamemode" und "Language" fort, die ebenfalls mit Größenpräfix versehen sind. Das **ASI** liest und überspringt diese Felder, um sich auf die wesentlichen Daten `Players`, `Max_Players` und `Hostname` zu konzentrieren.

   Das Lesen dieser Felder erfolgt mit den Hilfsfunktionen `Read_From_Span` und `Read_String_From_Span`, die sicherstellen, dass das **ASI** keine Bytes außerhalb der Puffergrenzen liest und die Lesevorgänge für feste und variable Datentypen (Strings) korrekt handhabt.
   ```cpp
   // server_query.cpp (Antwort-Parsing)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       // ... (Größenprüfung und Subspan für Daten) ...
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Liest den Boolean 'passworded'
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false; // Liest 'Players'

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false; // Liest 'Max_Players'

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false; // Liest 'Hostname'
   
       // Felder 'Gamemode' und 'Language' werden implizit durch Read_String_From_Span übersprungen
       // durch den nachfolgenden Aufruf von Read_String_From_Span, um den Span über ihre Daten hinaus zu bewegen.
       uint32_t length_placeholder; // Temporäre Variable für die Größe.

       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Liest Gamemode-Größe

       if (data_span.size() < length_placeholder)
           return false; // Prüft Grenzen

       data_span = data_span.subspan(length_placeholder); // Überspringt Gamemode-Daten
   
       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Liest Language-Größe

       if (data_span.size() < length_placeholder)
           return false; // Prüft Grenzen

       data_span = data_span.subspan(length_placeholder); // Überspringt Language-Daten
   
       return true;
   }
   ```
   Im obigen Beispiel ist die Logik `data_span = data_span.subspan(length_placeholder);` eine effiziente Methode, um die Anzahl der gelesenen Bytes einer Zeichenkette, deren Inhalt für die Rich Presence nicht benötigt wird, zu überspringen.

### Vorteile von SA-MP Rich Presence

Das **SA-MP Rich Presence** verbessert die Erfahrung sowohl für Spieler als auch für Serveradministratoren erheblich und bietet bemerkenswerte Vorteile:

1. **Für Spieler:**
   - **Mühelose Sichtbarkeit:** Teile deinen Spielstatus automatisch mit Freunden auf Discord und zeige genau, wo du spielst.
   - **Reichhaltige Informationen:** Erhalte sofortigen Zugriff auf Serverdetails (Name, Spieleranzahl, IP, personalisiertes Logo) direkt in Discord, ohne diese Informationen anderswo überprüfen zu müssen.
   - **Direkter Community-Zugang:** Entdecke und greife schnell auf die sozialen Medien des Servers über die rotierenden Symbole in der Discord-Präsenz zu, was den Einstieg in lebendige Communitys erleichtert.
   - **Schnelle Verbindung mit Freunden:** Lade Freunde ein oder trete mit einem Klick dem gleichen Server bei, dank der "Join"-Button-Funktionalität.
   - **Immer aktuelle Erfahrung:** Das automatische Updatesystem stellt sicher, dass du immer die optimierteste und funktionalste Version des **ASI** verwendest.
2. **Für Server:**
   - **Natürliches virales Marketing:** Die Discord-Präsenz deiner Spieler fungiert als digitales Werbeplakat und bewirbt deinen Server rund um die Uhr für eine organische Zielgruppe (die Freunde der Spieler).
   - **Starke visuelle Identität:** Ein personalisiertes Logo und die Rotation sozialer Links ermöglichen es deinem Server, sich abzuheben und ein professionelles, modernes Image im Discord-Umfeld zu projizieren.
   - **Erhöhtes Engagement:** Erleichtert den Weg für neue und bestehende Spieler, sich mit deinen sozialen Plattformen zu verbinden, und stärkt so deine Community und das Engagement außerhalb des Spiels.
   - **Vereinfachtes Recruiting:** Die "Join"-Funktion vereinfacht den Prozess für neue Spieler, indem sie Barrieren abbaut und die Erprobung fördert.
   - **Konsistente Daten:** Durch die Integration mit der **SPC Integration API** ist die Anzeige von Informationen einheitlich und zentral aktualisiert, sodass die Marke und die Kontakte deines Servers immer korrekt sind.

## Lizenz

Dieses ASI steht unter der Apache 2.0 Lizenz, die Folgendes erlaubt:

- ✔️ Kommerzielle und private Nutzung
- ✔️ Modifikation des Quellcodes
- ✔️ Verteilung des Codes
- ✔️ Patenterteilung

### Bedingungen:

- Urheberrechtshinweis beibehalten
- Wesentliche Änderungen dokumentieren
- Kopie der Apache 2.0 Lizenz beifügen

Weitere Details zur Lizenz: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Alle Rechte vorbehalten**