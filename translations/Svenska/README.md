# SA-MP Rich Presence

**SA-MP Rich Presence** är ett **ASI** för **SA-MP (San Andreas Multiplayer)** som automatiskt uppdaterar din Discord-status med detaljerad information om servern. **ASI** injiceras i spelet när du ansluter till en SA-MP-server och visar serverinformation.

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
  - [Funktioner](#funktioner)
    - [Discord Rich Presence](#discord-rich-presence)
    - [System för automatisk uppdatering](#system-för-automatisk-uppdatering)
  - [Krav](#krav)
  - [Installation](#installation)
  - [Integration med SPC Integration API](#integration-med-spc-integration-api)
    - [Hur informationen hämtas och används:](#hur-informationen-hämtas-och-används)
  - [För serverutvecklare](#för-serverutvecklare)
    - [Hur man implementerar SPC Integration på din server:](#hur-man-implementerar-spc-integration-på-din-server)
  - [Detaljerad teknisk arkitektur](#detaljerad-teknisk-arkitektur)
      - [Huvudsystem (`main.cpp`)](#huvudsystem-maincpp)
      - [Uppdateringssystem (`asi_update.hpp`)](#uppdateringssystem-asi_updatehpp)
      - [Discord-hanterare (`discord_manager.cpp`)](#discord-hanterare-discord_managercpp)
      - [Serverhanterare (`server_manager.cpp`)](#serverhanterare-server_managercpp)
      - [Nätverkssystem (`samp_network.cpp`)](#nätverkssystem-samp_networkcpp)
      - [Serverförfrågan (`server_query.cpp`)](#serverförfrågan-server_querycpp)
      - [URL-hanterare (`url_manager.cpp`)](#url-hanterare-url_managercpp)
    - [Kodstruktur](#kodstruktur)
      - [Globala konstanter (`constants.hpp`)](#globala-konstanter-constantshpp)
      - [Datastrukturer (`server_types.hpp`)](#datastrukturer-server_typeshpp)
      - [Obfuskering av hemligheter (`secrets.hpp`)](#obfuskering-av-hemligheter-secretshpp)
      - [Allmänna verktyg (`utils.hpp`)](#allmänna-verktyg-utilshpp)
    - [Felhantering och motståndskraft](#felhantering-och-motståndskraft)
    - [System för kommandoargsbehandling](#system-för-kommandoargsbehandling)
      - [Kommandoargs-parser (`command_line_parser.cpp`)](#kommandoargs-parser-command_line_parsercpp)
    - [SA-MP-kommunikationsprotokoll](#sa-mp-kommunikationsprotokoll)
      - [Protokollimplementering](#protokollimplementering)
    - [Fördelar med SA-MP Rich Presence](#fördelar-med-sa-mp-rich-presence)
  - [Licens](#licens)
    - [Villkor:](#villkor)

## Funktioner

### Discord Rich Presence

**Discord Rich Presence** är en funktion som gör det möjligt för applikationer att visa detaljerad information om vad användaren gör direkt i Discord-profilen. För **SA-MP Rich Presence** visas följande information:

- **Servernamn (Hostname):** Serverns primära namn.
- **Spelarnamn:** Ditt nuvarande smeknamn i spelet.
- **Antal spelare:** Aktuellt antal spelare online och max tillåtet.
- **Serveradress:** IP och port för enkel identifiering.
- **Anpassad serverbild:** En unik serverlogotyp, om tillgänglig.
- **Roterande sociala ikoner:** Små ikoner som representerar länkar till serverns sociala medier (webbplats, Discord, YouTube, Instagram, Facebook, TikTok), som växlar automatiskt.
- **Speltid:** Hur länge du varit ansluten till den aktuella servern.
- **Anslutningsstatus:** Indikerar om du är online på en server eller i tillståndet "Idle" (inaktiv).
- **Knapp för "Join" (Gå med):** Gör det möjligt för dina vänner att gå med direkt på samma server som du spelar på.

### System för automatisk uppdatering

**ASI** integrerar ett system för uppdateringskontroll. När spelet startar kontrollerar det om det finns nya versioner tillgängliga i projektets officiella GitHub-repositorium. Om en uppdatering hittas visas en vänlig notifikation för användaren med alternativ för:

1. Öppna webbläsaren direkt på releases-sidan för nedladdning.
2. Fortsätta utan att uppdatera, med möjlighet att inaktivera **ASI** för den aktuella sessionen.

Denna funktion säkerställer att användare alltid har tillgång till de senaste förbättringarna, buggfixarna och nya funktionerna, vilket främjar en uppdaterad och oavbruten upplevelse.

## Krav

- SA-MP-klient (om du inte har en: [clients-samp](https://github.com/spc-samp/clients-samp)).
- Discord Desktop-applikation.
- Windows-operativsystem.
- Visual C++ Runtime.
- En [ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) installerad i din Grand Theft Auto: San Andreas.

## Installation

1. Ladda ner den senaste kompilerade versionen av **ASI** direkt från sektionen [releases](https://github.com/ocalasans/samp-rich-presence/releases) på GitHub.
2. Efter nedladdning, hitta `.asi`-filen.
3. Kopiera den nedladdade `.asi`-filen till rotmappen för ditt GTA San Andreas (där `gta_sa.exe` finns).
4. Starta spelet via SA-MP-klienten.
5. **ASI** laddas och initieras automatiskt när du ansluter till en server, vilket uppdaterar din status på Discord.

## Integration med SPC Integration API

**SA-MP Rich Presence** förbättrar avsevärt visningen av information på Discord genom sin integration med **SPC Integration API**. Istället för att enbart förlita sig på grundläggande query-data interagerar **ASI** nu direkt med denna API för att hämta visuell och social information om servern. För att lära dig mer om **SPC Integration** i sig, besök det officiella repositoriet: [spc-samp/spc-integration](https://github.com/spc-samp/spc-integration).

### Hur informationen hämtas och används:

1. **Formatering av adress:** När spelaren ansluter till en server (IP och port) formaterar **ASI** denna adress (`IP:PORT`) till ett användarvänligt format (`IP-PORT`), och förbereder den för API-förfrågan.
2. **Förfrågan till API:** **ASI** skickar en `GET`-förfrågan till endpointen för **SPC Integration API**, inklusive den formaterade IP-adressen och porten. Exempel på hur förfrågans URL byggs internt:
   ```cpp
   // Trecho adaptado de url_manager.cpp
   auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
   std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
   path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   const std::string json_data = Request_API_Data(path);
   ```
3. **Bearbetning av JSON-svar:** API:et returnerar ett svar i JSON-format. **ASI** använder biblioteket [nlohmann/json](https://github.com/nlohmann/json) för att tolka detta svar och extrahera relevanta data.
   ```json
   // Exempel på struktur för svar från SPC Integration API
   {
       "success": true,
       "data": {
           "public": {
               "logo": "https://url.till.din.logo/server_logo.png",
               "website": "https://din-webbplats.com",
               "discord": "https://discord.gg/dinserver",
               "youtube": "https://youtube.com/dinkanal"
               // ...andra sociala medier
           }
       }
   }
   ```
4. **Extrahering av data:**
   - **Serverlogotyp:** URL:en till serverns bild (fältet `logo` i sektionen `public`) extraheras och används som den primära bilden (large image) i **Discord Rich Presence**. Detta säkerställer en autentisk och anpassningsbar visuell identitet för varje server.
   - **Sociala länkar:** En fördefinierad lista med sociala medier (webbplats, Discord, YouTube, Instagram, Facebook, TikTok) kontrolleras i JSON-svaret. För varje hittad och giltig social media-plattform lagras namnet på plattformen och dess respektive länk.
5. **Visning på Discord:** `Server_Manager` använder listan över extraherade sociala länkar för att implementera en dynamisk rotation. Var 30:e sekund visas en annan ikon för en av serverns sociala medier som "small image" (liten bild) i Discord-presensen, tillsammans med plattformens länk eller namn, vilket uppmuntrar till utforskning av serverns communities.

## För serverutvecklare

Att integrera din server med [SPC Integration](https://github.com/spc-samp/spc-integration) ger en rad direkta och indirekta fördelar som ökar synligheten och engagemanget i din SA-MP-community. Om du är en serverutvecklare, överväg de strategiska fördelarna:

1. **Stärk ditt varumärke:**
   - **Premiumsynlighet:** Din servers anpassade logotyp blir inte bara text utan en levande och iögonfallande bild som visas framträdande i Discord-profilen för alla spelare som använder detta **ASI**. Detta är ett organiskt och konstant sätt att stärka varumärket.
   - **Professionell närvaro:** Genom att ha din logotyp och sociala medier väl representerade projicerar din server en mer etablerad och pålitlig image, vilket lockar mer intresse och potentiella nya spelare.
2. **Utvidgning av communityn:**
   - **Fler åtkomstkanaler:** Med rotationen av sociala ikoner kan du marknadsföra flera plattformar för din community – från den officiella webbplatsen och serverns Discord till sidor på YouTube, Instagram, Facebook eller TikTok. Varje ikon och länk i **Discord Rich Presence** leder direkt intresserade till där din community är aktiv.
   - **Omedelbar anslutning:** Funktionen "Join" via Discord gör det möjligt för vänner till dina spelare att gå med i din server med ett enda klick, vilket minskar inträdesbarriärer och uppmuntrar nya medlemmar.
3. **Förenklad uppdatering av innehåll:**
   - Genom att använda [SPC Integration](https://github.com/spc-samp/spc-integration) kommer alla uppdateringar av din servers logotyp eller lista över sociala medier som konfigurerats i plugin [SPC Integration](https://github.com/spc-samp/spc-integration) **(på serversidan)** att automatiskt reflekteras för spelare som använder **ASI**, utan att de behöver uppdatera **ASI**. Detta säkerställer att informationen alltid är korrekt och uppdaterad.

### Hur man implementerar SPC Integration på din server:

1. **Plugin SPC Integration:** Din server måste ha plugin [SPC Integration](https://github.com/spc-samp/spc-integration) installerat och korrekt konfigurerat. Denna plugin är bron som skickar information om din server till en lista med data i **SPC**, som sedan används av **SPC Integration API** för att tillhandahålla offentlig information.
2. **Konfiguration:** Följ instruktionerna i repositoriet för plugin [SPC Integration](https://github.com/spc-samp/spc-integration) för att konfigurera:
   - Parametern `logo` med URL:en till din servers logotyp.
   - Parametrarna för sociala medier (`discord`, `website`, `youtube`, etc.) med giltiga länkar till dina plattformar.
3. **Automatisk uppdatering:** När informationen är konfigurerad i serverns plugin kommer **SA-MP Rich Presence** att automatiskt upptäcka och visa den. Ingen ytterligare åtgärd krävs från spelarens sida utöver den initiala installationen av **ASI**.

Genom att integrera din server med [SPC Integration](https://github.com/spc-samp/spc-integration) förbättrar du inte bara spelarupplevelsen utan öppnar också dörrar för betydande tillväxt och engagemang i din community.

## Detaljerad teknisk arkitektur

**SA-MP Rich Presence** har en väldefinierad modulär arkitektur, med komponenter fokuserade på specifika uppgifter. Kodbasen är i linje med moderna C++-standarder (C++17 och C++20), och använder `std::string_view`, `std::span` och flyttsemantik för att säkerställa hög prestanda, säkerhet och effektivitet.

#### Huvudsystem (`main.cpp`)

Hjärtat i **ASI** finns i `main.cpp`, som hanterar applikationens livscykel, från dess initialisering som en DLL till dess kontinuerliga uppdateringsloop och graciösa avslut.

- **`DllMain`**: Ingångspunkten för **ASI** när den laddas av operativsystemet.
   ```cpp
   // DllMain (förenklad för strukturens skull)
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
   I denna funktion, vid anslutning till spelets process (`DLL_PROCESS_ATTACH`), förhindras onödiga bibliotekssamtal (`DisableThreadLibraryCalls`) och **en ny tråd (`Main_Update_Thread`)** skapas för att köra **ASI**:s logik asynkront, vilket säkerställer att spelet inte blockeras. Vid avslut (`DLL_PROCESS_DETACH`) anropas `Shutdown_Managers()` för att frigöra resurser.
- **`Main_Update_Thread`**: Själva själen i **ASI**, som körs i sin egen tråd.
   ```cpp
   // Main_Update_Thread (viktigt utdrag)
   DWORD WINAPI Main_Update_Thread(LPVOID) {
       // 1. Uppdateringskontroll
       if (Asi_Update::Check_For_Update())
           return 0; // Om användaren väljer att inaktivera, avslutas.
   
       // 2. Nätverksinitialisering (Winsock)
       WSAData wsa_data;

       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
   
       // 3. Initialiserar server- och Discord-hanterare
       Initialize_Managers();
   
       // 4. Huvudsaklig uppdateringsloop
       while (is_running && v_server_manager && v_discord_manager) {
           v_server_manager->Update(); // Frågar server, SPC API etc.
           v_discord_manager->Update_Presence( // Uppdaterar Discord-status
               v_server_manager->Get_Server_Info(),
               v_server_manager->Get_Display_Social_Link(),
               v_server_manager->Get_Player_Name(),
               v_server_manager->Get_Current_Image_URL(),
               v_server_manager->Is_Connected());
   
           Discord_RunCallbacks(); // Bearbetar Discord RPC-händelser
           std::this_thread::sleep_for(Constants::MAIN_LOOP_INTERVAL);
       }
   
       // 5. Avslut (om hanterare finns)
       if (v_discord_manager)
           v_discord_manager->Shutdown();

       WSACleanup(); // Frigör Winsock

       return 0;
   }
   ```
   Denna funktion prioriterar uppdateringskontroll. Därefter initialiseras Winsock-nätverksstacken och instanser av server- och Discord-hanterare. En persistent `while`-loop (kontrollerad av `std::atomic<bool> is_running` för säkert avslut) koordinerar anrop till `Server_Manager::Update()` (datainsamling) och `Discord_Manager::Update_Presence()` (sändning till Discord). `Discord_RunCallbacks()` säkerställer att Discord bearbetar Rich Presence-händelser. Loopen pausas periodvis med `std::this_thread::sleep_for` för resursoptimering.

#### Uppdateringssystem (`asi_update.hpp`)

Denna viktiga modul lägger till intelligens till **ASI**, och säkerställer att användarna håller sig uppdaterade.

- **`Check_For_Update()`**: Huvudfunktionen för uppdateringskontroll.
   ```cpp
   // asi_update.hpp (viktigt utdrag av Check_For_Update)
   inline bool Check_For_Update() {
       HINTERNET h_session = nullptr, h_connect = nullptr, h_request = nullptr;
       bool update_found_and_handled = false;
   
       try {
           h_session = WinHttpOpen(L"SA-MP Rich Presence Update/1.0", ...);
           // ... (GET-förfrågan till Constants::UPDATE_API_PATH på GitHub API) ...
           std::string response_body;
           // ... (läser HTTP-svaret) ...
           nlohmann::json release_info = nlohmann::json::parse(response_body);
   
           std::string latest_tag = release_info["tag_name"].get<std::string>();
           // ... (normaliserar och jämför versioner med sscanf_s/sscanf) ...
   
           if (latest_major > current_major || (latest_major == current_major && latest_minor > current_minor)) {
               update_found_and_handled = true;
               std::wstringstream message_stream;
               // ... (förbereder meddelandet för MessageBox) ...
               int msgbox_result = MessageBoxW(NULL, message_stream.str().c_str(), L"SA-MP Rich Presence - Update Available", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
               
               if (msgbox_result == IDYES)
                   ShellExecuteW(NULL, L"open", Constants::UPDATE_RELEASES_URL, NULL, NULL, SW_SHOWNORMAL);
           }
       }
       catch (const std::exception&) { /* Felhantering */ }
   
       // ... (stänger WinHttp-handles) ...
       return update_found_and_handled;
   }
   ```
   Genom att använda **WinHTTP API** för nätverksförfrågningar gör `Check_For_Update` en `GET`-förfrågan till `/releases/latest`-endpointen på GitHubs API för projektets repositorium. Svaret, i JSON-format, tolkas med biblioteket `nlohmann/json`. Den senaste versionen (`tag_name`) jämförs numeriskt med den kompilerade versionen av **ASI**. Om en ny version hittas visas en dialogruta (`MessageBoxW`) som frågar användaren om de vill gå till nedladdningssidan via `ShellExecuteW`. Hela processen är inkapslad i en `try-catch` för att säkerställa att nätverksfel eller tolkningsfel inte hindrar spelet från att starta.

#### Discord-hanterare (`discord_manager.cpp`)

Klassen `Discord_Manager` abstraherar interaktionerna med **Discord RPC**-biblioteket, och hanterar initialisering av anslutningen och sändning av data till användarens närvarostatus.

- **`Initialize()`**: Konfigurerar kommunikationen med Discord.
   ```cpp
   // discord_manager.cpp (viktigt utdrag av Initialize)
   void Discord_Manager::Initialize() noexcept {
       DiscordEventHandlers handlers;
       memset(&handlers, 0, sizeof(handlers)); // Säkerställer initialisering
       
       // App ID avobfuskeras här
       auto app_id_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_Discord_App_ID());
       Discord_Initialize(app_id_accessor.Get(), &handlers, 1, nullptr);
   
       start_timestamp_ = time(nullptr); // Registrerar sessionens start
   }
   ```
   Anropet till `Discord_Initialize` är avgörande och använder `DISCORD_APP_ID` som erhålls säkert genom strängobfuskering i `secrets.hpp`. `start_timestamp_` sätts här för att beräkna speltiden i Discord-närvaron.
- **`Update_Presence()`**: Den vitala funktionen som uppdaterar Discord Rich Presence.
   ```cpp
   // discord_manager.cpp (viktigt utdrag av Update_Presence)
   void Discord_Manager::Update_Presence(const Server_Information& server_info, const server_types::Social_Link& social_link, const std::string_view player_name, const std::string_view current_image, const bool is_connected) noexcept {
       DiscordRichPresence discord_presence;
       memset(&discord_presence, 0, sizeof(discord_presence));
   
       discord_presence.startTimestamp = start_timestamp_;
       discord_presence.largeImageKey = current_image.data(); // Serverlogotyp
   
       if (is_connected) {
           discord_presence.details = server_info.Hostname.c_str();
           discord_presence.state = player_name.data();
           discord_presence.largeImageText = server_info.Server_Address.c_str(); // IP:Port
           discord_presence.partySize = server_info.Players;
           discord_presence.partyMax = server_info.Max_Players;
           discord_presence.joinSecret = server_info.Server_Address.c_str(); // Aktiverar knappen "Join"
   
           // Hanterar roterande sociala ikoner
           if (!social_link.first.empty()) {
               current_small_image_key_ = Constants::SOCIAL_ICON_BASE_URL;
               current_small_image_key_ += social_link.first; // Ex: "discord.png"
               current_small_image_key_ += ".png";
               discord_presence.smallImageKey = current_small_image_key_.c_str();
               discord_presence.smallImageText = social_link.second.c_str(); // Text vid hovring (länk/namn)
           }
       }
       else {
           discord_presence.details = "SA-MP"; // Tillstånd "Idle"
           discord_presence.state = "Idle";
           discord_presence.largeImageText = "San Andreas Multiplayer";
           // smallImageKey och smallImageText förblir tomma för idle-tillstånd
       }
   
       Discord_UpdatePresence(&discord_presence);
   }
   ```
   Fyller i strukturen `DiscordRichPresence` baserat på anslutningsstatus. Om `is_connected` är sant visas hostname, antal spelare, serverns IP och spelarens namn. `largeImageKey` definierar serverns primära bild. Noterbart är att `joinSecret` sätts för att möjliggöra direkt anslutning för vänner, och `smallImageKey` (byggd dynamiskt baserat på `social_link`) visar roterande sociala ikoner. I tillståndet "Idle" förenklas närvaron för att reflektera inaktivitet. Slutligen skickar `Discord_UpdatePresence` datan till Discord.

#### Serverhanterare (`server_manager.cpp`)

`Server_Manager` är orkestratorn för data, och hanterar anslutningsstatus, förfrågningar till servern och **SPC Integration API**, samt beslutar vilka uppgifter som ska visas och när.

- **`Update()`**: Huvudlivscykeln för datainsamling.
   ```cpp
   // server_manager.cpp (viktigt utdrag av Update)
   void Server_Manager::Update() {
       const auto now = std::chrono::steady_clock::now();
   
       if (server_query.Query(live_server_data)) { // Försöker hämta data via SAMP-query
           if (!connection_status) { // Om precis ansluten/återansluten
               connection_status = true;
               Fetch_API_Data(); // Hämtar logotyp och sociala medier från API
           }
           
           last_successful_query = now;
   
           // Uppdaterar data som ska visas på Discord
           display_server_data.Hostname = live_server_data.Hostname;
           display_server_data.Players = live_server_data.Players;
           display_server_data.Max_Players = live_server_data.Max_Players;
           display_server_data.Server_Address = server_ip + ":" + std::to_string(server_port);
   
           if (now - last_api_update > Constants::IMAGE_UPDATE_INTERVAL)
               Fetch_API_Data(); // Återförfrågar API efter angivet intervall
   
           if (now - last_social_rotation > Constants::SOCIAL_UPDATE_INTERVAL)
               Rotate_Social_Link(); // Roterar den sociala ikonen
       }
       else { // Om förfrågan misslyckas
           if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
               connection_status = false; // Frånkopplad efter timeout
               display_image_url = Constants::DEFAULT_IMAGE;
               display_server_data = {}; // Rensar data
               current_display_social = {}; // Rensar sociala medier
           }
       }
   }
   ```
   Funktionen `Update` försöker utföra en förfrågan till servern. Vid framgång uppdateras data i `live_server_data` och `display_server_data`. Villkorligt anropas `Fetch_API_Data()` för att uppdatera bilden och sociala länkar (vid ny anslutning eller om `IMAGE_UPDATE_INTERVAL` har passerat) och `Rotate_Social_Link()` för att växla sociala ikoner (`SOCIAL_UPDATE_INTERVAL`). Om förfrågningar till servern konsekvent misslyckas i över 15 sekunder anses anslutningsstatus förlorad, och de visade uppgifterna återställs.
- **`Fetch_API_Data()`**: Ansvarar för att hämta visuella och sociala data.
   ```cpp
   // server_manager.cpp (viktigt utdrag av Fetch_API_Data)
   void Server_Manager::Fetch_API_Data() {
       display_image_url = url_manager.Get_Image_URL_And_Populate_Socials(server_ip, server_port, live_server_data);
       last_api_update = std::chrono::steady_clock::now();
       current_social_index_ = 0; // Återställer index efter ny API-hämtning
       Rotate_Social_Link(); // Säkerställer att en social ikon visas omedelbart
   }
   ```
   Denna funktion koordinerar med `URL_Manager` för att hämta logotyp och sociala länkar från API, uppdaterar `display_image_url` och fyller i `Social_Links` i `live_server_data`. Återställer rotationsindex för sociala medier och anropar `Rotate_Social_Link()` för att säkerställa att den första ikonen är redo för visning.
- **`Rotate_Social_Link()`**: Logik för att växla sociala ikoner.
   ```cpp
   // server_manager.cpp (viktigt utdrag av Rotate_Social_Link)
   void Server_Manager::Rotate_Social_Link() {
       if (!live_server_data.Social_Links.empty()) {
           if (current_social_index_ >= live_server_data.Social_Links.size())
               current_social_index_ = 0; // Startar om cykeln
   
           current_display_social = live_server_data.Social_Links[current_social_index_];
           current_social_index_ = (current_social_index_ + 1) % live_server_data.Social_Links.size();
       }
       else
           current_display_social = {}; // Rensar om inga sociala medier finns
       
       last_social_rotation = std::chrono::steady_clock::now();
   }
   ```
   Denna enkla funktion väljer nästa `Social_Link` i listan från `live_server_data.Social_Links` cykliskt och lagrar den i `current_display_social` för att användas av `Discord_Manager`.

#### Nätverkssystem (`samp_network.cpp`)

Klassen `Samp_Network` är den lågnivåimplementering av **UDP**-kommunikation, ansvarig för att öppna och hantera socketen för SA-MP-förfrågningar. Den erbjuder nu konstruktörer och flyttoperatorer för bättre resurshantering.

- **`Initialize()`**: Konfigurerar socketen för **UDP**-kommunikation.
   ```cpp
   // samp_network.cpp (viktigt utdrag av Initialize)
   bool Samp_Network::Initialize(const std::string_view ip, const int port) noexcept {
       if (network_socket != INVALID_SOCKET)
           closesocket(network_socket); // Stänger befintlig socket
   
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       if (network_socket == INVALID_SOCKET)
           return false;
   
       const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
       setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
   
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(static_cast<u_short>(port));
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr); // Stöd för IPv4
       return true;
   }
   ```
   Initialiserar socketen, sätter timeouts för sändning och mottagning, och konfigurerar adressstrukturen (`sockaddr_in`) med serverns IP och port, med `inet_pton` för IP-konvertering.
- **`Send_Query()`**: Skickar ett förfrågningspaket och tar emot svaret.
   ```cpp
   // samp_network.cpp (viktigt utdrag av Send_Query)
   bool Samp_Network::Send_Query(const std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept {
       // Skickar UDP-paketet
       if (sendto(network_socket, query_packet.data(), static_cast<int>(query_packet.size()), 0, reinterpret_cast<const sockaddr*>(&server_address), sizeof(server_address)) < 0)
           return false;
   
       sockaddr_in from_address;
       int address_length = sizeof(from_address);
       // Tar emot svaret
       received_bytes = recvfrom(network_socket, response_buffer.data(), static_cast<int>(response_buffer.size()), 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);
   
       return received_bytes > Constants::QUERY_PACKET_SIZE;
   }
   ```
   Denna metod skickar `query_packet` (passerat som `std::span` för buffertsäkerhet) till servern. Därefter försöker den ta emot ett svar i `response_buffer`. Returen indikerar om operationen lyckades och om ett antal byte större än förfrågningspaketets storlek togs emot.

#### Serverförfrågan (`server_query.cpp`)

Klassen `Server_Query` är dedikerad till implementeringen av SA-MP:s förfrågansprotokoll (`'i'`), och extraherar grundläggande serverinformation (spelare, hostname) från **UDP**-svar.

- **`Query()`**: Hanterar förfrågansförsök.
   ```cpp
   // server_query.cpp (viktigt utdrag av Query)
   bool Server_Query::Query(Server_Information& server_data) noexcept {
       for (int attempt = 0; attempt < Constants::MAX_RETRY_ATTEMPTS; ++attempt) {
           if (Try_Query(server_data))
               return true; // Lyckad förfrågan
   
           if (attempt < Constants::MAX_RETRY_ATTEMPTS - 1)
               // Kort paus innan nytt försök för att undvika flooding
               std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)));
       }

       return false; // Alla försök misslyckades
   }
   ```
   Implementerar en *retry*-strategi med `MAX_RETRY_ATTEMPTS` och en exponentiell *back-off*-tid för att säkerställa robusta förfrågningar och undvika nätverksöverbelastning. Anropar `Try_Query` vid varje försök.
- **`Assemble_Query_Packet()`**: Bygger förfrågningspaketet för SA-MP.
   ```cpp
   // server_query.cpp (viktigt utdrag av Assemble_Query_Packet)
   void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
       memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
       packet = 'i'; // Kod för informationsförfrågan
   }
   ```
   Det standardiserade paketet för informationsförfrågan (`'i'`) byggs, inklusive signaturen "SAMP" och byten 'i'.
- **`Parse_Response()`**: Packar upp serverns binära svar.
   ```cpp
   // server_query.cpp (viktigt utdrag av Parse_Response)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       if (response.size() <= Constants::QUERY_PACKET_SIZE) 
           return false;
   
       auto data_span = response.subspan(Constants::QUERY_PACKET_SIZE); // Hoppar över rubriken
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Ignorerat men läst
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false;

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false;

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false;
   
       // Notera: Gamemode och Language hoppas över automatiskt av Read_String_From_Span om paketet innehåller ytterligare data.
       // Om du behöver andra fält, skapa en sträng och anropa: Read_String_From_Span(data_span, string_variable);
       return true;
   }
   ```
   Denna metod läser säkert data från `response_buffer` (med `std::span` och hjälpfunktionerna `Read_From_Span` och `Read_String_From_Span`). Den extraherar antal spelare, max spelare och hostname, och fyller i strukturen `Server_Information`. Oanvända fält (som om servern är lösenordsskyddad) läses men ignoreras, och andra som "gamemode" och "language" hoppas över om svaret innehåller mer data än vad **ASI** behöver för tillfället.
- **Hjälpfunktioner för läsning:**
   ```cpp
   // server_query.hpp (utdrag av hjälpfunktioner för läsning)
   template<typename T>
   static bool Read_From_Span(std::span<const char>& s, T& value) noexcept;
   
   static bool Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept;
   ```
   `Read_From_Span` hanterar läsning av fasta typer (heltal, booleska värden) från `std::span` och flyttar fram `span`. `Read_String_From_Span` läser längden på en sträng (som `uint32_t`) och sedan själva strängen, och flyttar också fram `span`. Detta säkerställer säkerhet vid tolkning av byte och förhindrar läsningar utanför buffertens gränser.

#### URL-hanterare (`url_manager.cpp`)

Klassen `URL_Manager` hanterar HTTPS-kommunikation med **SPC Integration API**, en central komponent för de nya visuella och sociala funktionerna i **Discord Rich Presence**.

- **`Get_Image_URL_And_Populate_Socials()`**: Högnivåmetoden för att hämta information från API.
   ```cpp
   // url_manager.cpp (viktigt utdrag av Get_Image_URL_And_Populate_Socials)
   std::string URL_Manager::Get_Image_URL_And_Populate_Socials(const std::string& ip, const int port, Server_Information& server_info) {
       if (!session_handle)
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);
   
       auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
       std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
       path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   
       const std::string json_data = Request_API_Data(path); // HTTP-förfrågan till API
   
       if (json_data.empty())
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE); // Fel vid förfrågan
   
       return Parse_API_Response(json_data, server_info); // Tolkar och fyller i server_info
   }
   ```
   Tar emot IP och port, bygger API:ets URL med dessa som parametrar. Anropar `Request_API_Data` för att hämta JSON-data. Vid framgång anropas `Parse_API_Response` för att extrahera bildens URL (logotyp) och fylla i sociala länkar i `server_info`.
- **`Request_API_Data()`**: Utför HTTPS-förfrågan till API.
   ```cpp
   // url_manager.cpp (viktigt utdrag av Request_API_Data)
   std::string URL_Manager::Request_API_Data(const std::wstring& path) {
       auto api_host_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Host());
       const std::wstring wide_host = Utils::Convert_Utf8_To_Wide_String(api_host_accessor.Get());
       HINTERNET connect_handle = WinHttpConnect(session_handle, wide_host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
   
       if (!connect_handle) return "";
   
       HINTERNET request_handle = WinHttpOpenRequest(connect_handle, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
   
       if (!request_handle) return (WinHttpCloseHandle(connect_handle), "");
   
       // Skicka förfrågan, ta emot svar, verifiera status 200, läs data i loop
       // ... (detaljer för WinHttpSendRequest, WinHttpReceiveResponse, WinHttpQueryHeaders, WinHttpReadData) ...
       
       WinHttpCloseHandle(request_handle); WinHttpCloseHandle(connect_handle);
       return response_body; // Returnerar JSON som sträng
   }
   ```
   Ansluter till API:ets värd (hämtad obfuskerat), öppnar och skickar en `GET`-förfrågan med sökvägen (`path`). Hanterar HTTP-svaret, verifierar statuskoden (200 OK för framgång), och läser hela svarsinnehållet (som ska vara JSON). Alla WinHTTP-handles frigörs vid framgång eller misslyckande.
- **`Parse_API_Response()`**: Bearbetar JSON-strängen för att extrahera data.
   ```cpp
   // url_manager.cpp (viktigt utdrag av Parse_API_Response)
   std::string URL_Manager::Parse_API_Response(const std::string& json_content, Server_Information& server_info) {
       server_info.Social_Links.clear(); // Rensar befintliga sociala länkar
       try {
           const auto json = nlohmann::json::parse(json_content);
   
           if (json.value("success", false) && json.contains("data") && json["data"].contains("public")) {
               const auto& public_data = json["data"]["public"];
               const std::vector<std::string> social_keys = { "website", "discord", "youtube", "instagram", "facebook", "tiktok" };
               
               // Extraherar och fyller i sociala länkar
               for (const auto& key : social_keys) {
                   if (public_data.contains(key)) {
                       std::string value = public_data.value(key, "not-defined");

                       if (!value.empty() && value != "not-defined")
                           server_info.Social_Links.push_back({ key, value });
                   }
               }

               return public_data.value("logo", ""); // Returnerar logotypens URL
           }
       }
       catch (const nlohmann::json::exception&) { /* Hanterar tolkningsfel */ }

       return ""; // Misslyckat tolkning
   }
   ```
   Använder `nlohmann::json::parse` för att konvertera JSON-strängen till ett hanterbart JSON-objekt. Navigerar genom strukturen (`success`, `data`, `public`) och extraherar `logo` (som blir `display_image_url`) och itererar över fördefinierade nycklar för att hitta och fylla i `Social_Links` i `server_info`.

### Kodstruktur

Projektet **SA-MP Rich Presence** är noggrant organiserat i en tydlig katalogstruktur, med källkoden (`src/`) och en underkatalog för externa bibliotek (`libraries/`). Filnamnen följer konventionen `_manager` eller `_network` för tydlighet om varje klass syfte. De flesta header-filer använder tillägget `.hpp`, vilket indikerar att de är C++-header-filer.

```
src/
├── libraries/               # Innehåller viktiga tredjepartsbibliotek
│   ├── Dralyxor/            # Bibliotek för strängobfuskering
│   ├── Discord/             # Officiellt Discord RPC-bibliotek
│   └── nlohmann/            # Bibliotek för JSON-hantering
├── asi_update.hpp           # Definition av systemet för automatisk uppdatering
├── command_line_parser.hpp  # Definition av kommandoargs-parser
├── constants.hpp            # Definitioner av globala konstanter för projektet
├── discord_manager.hpp      # Definition av hanteraren för Discord-kommunikation
├── main.cpp                 # Ingångspunkt för ASI och huvudsaklig orkestrator
├── samp_network.hpp         # Definition av nätverkshanteraren för SA-MP-förfrågningar
├── secrets.hpp              # Definitioner för obfuskering av hemligheter
├── server_manager.hpp       # Definition av hanteraren för serverinformation
├── server_query.hpp         # Definition av logiken för serverförfrågningar
├── server_types.hpp         # Definitioner av datastrukturer för servern
├── url_manager.hpp          # Definition av URL-hanteraren för SPC Integration API
└── utils.hpp                # Allmänna hjälpfunktioner (strängkonvertering)
```

#### Globala konstanter (`constants.hpp`)

Denna fil samlar alla projektets konfigurationer och oföränderliga värden, tillgängliga globalt. Den använder `inline constexpr` för att säkerställa att konstanterna är direkt tillgängliga för kompilatorn, vilket optimerar prestandan.

```cpp
// constants.hpp (utdrag)
namespace Constants {
    inline constexpr char ASI_VERSION[] = "1.1"; // Version för uppdateringssystemet
    inline constexpr wchar_t UPDATE_API_HOST[] = L"api.github.com"; // Värd för uppdaterings-API
    inline constexpr char DEFAULT_IMAGE[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/default_logo.png"; // Standardbild
    inline constexpr int QUERY_TIMEOUT_MS = 800; // Timeout för förfrågningar i ms
    inline constexpr std::chrono::seconds MAIN_LOOP_INTERVAL = std::chrono::seconds(1); // Intervall för huvudsaklig loop
}
```
Viktiga detaljer som API-URL:er, standardbildvägar, nätverkstimeouts och uppdateringsintervall för **Discord Rich Presence** är centraliserade här. Användningen av `std::chrono::seconds` för intervall förbättrar läsbarheten och förhindrar enhetsfel.

#### Datastrukturer (`server_types.hpp`)

Denna fil definierar `structs` och `using` som är viktiga för att organisera insamlade och visade data.

```cpp
// server_types.hpp (utdrag)
namespace server_types {
    using Social_Link = std::pair<std::string, std::string>; // Tupel (nätverksnamn, URL/värde)
}

struct Server_Information {
    uint16_t Players{0};           // Antal aktuella spelare
    uint16_t Max_Players{0};       // Maximal kapacitet för spelare
    std::string Hostname{};        // Serverns namn
    std::string Server_Address{};  // Ex: "192.168.1.1:7777"

    std::vector<server_types::Social_Link> Social_Links{}; // Lista över serverns sociala länkar
};
```
`Server_Information` är den primära strukturen som lagrar serverdata. Tillägget av `std::vector<server_types::Social_Link> Social_Links` återspeglar den nya förmågan att hämta flera sociala medielänkar från API, organiserade som par `(nätverksnamn, länk)`.

#### Obfuskering av hemligheter (`secrets.hpp`)

Denna fil är dedikerad till att skydda känslig information, såsom **Discord Application ID** och adresserna till **SPC Integration API (för närvarande)**, från enkel reverse engineering.

```cpp
// secrets.hpp (utdrag)
#include "libraries/Dralyxor/dralyxor.hpp"

namespace Secrets {
    namespace {
        inline auto& Get_Obfuscated_Discord_App_ID() {
            static auto& dc_app_id_obfuscated = DRALYXOR_KEY("DISCORD_APP_ID", "YOUR_SECRET_KEY_HERE");

            return dc_app_id_obfuscated;
        }
        // ... (andra obfuskerade hemligheter) ...
    }
    namespace Detail {
        inline auto& Get_Discord_App_ID() {
            return Get_Obfuscated_Discord_App_ID();
        }
        // ... (offentliga getters för att få tillgång till avobfuskerade hemligheter) ...
    }
}
```
Biblioteket [Dralyxor](https://github.com/ocalasans/dralyxor) används med makrot `DRALYXOR_KEY` för att kryptera stränglitteraler i den kompilerade binären. `DRALYXOR_SECURE` används sedan vid körning för att avobfuskera dessa värden när de behövs, vilket lägger till ett robust säkerhetslager mot statisk nyckelextraktion.

#### Allmänna verktyg (`utils.hpp`)

En fil för generiska hjälpfunktioner som kan vara användbara i flera moduler, vilket undviker kodduplicering.

```cpp
// utils.hpp (utdrag)
namespace Utils {
    inline std::string Convert_Wide_To_Utf8_String(const std::wstring_view wide_string) {
        // ... (implementering av konvertering med WideCharToMultiByte) ...
    }

    inline std::wstring Convert_Utf8_To_Wide_String(const std::string_view narrow_string) {
        // ... (implementering av konvertering med MultiByteToWideChar) ...
    }
}
```
Innehåller funktionerna `Convert_Wide_To_Utf8_String` och `Convert_Utf8_To_Wide_String`, som är essentiella för interoperationer med Windows API:er (som använder UTF-16) och standard C++-operationer (som generellt drar nytta av UTF-8). Dessa funktioner använder Windows API:er för säker och effektiv konvertering.

### Felhantering och motståndskraft

**SA-MP Rich Presence** är designat med motståndskraft i åtanke och innehåller flera mekanismer för att hantera nätverksfel, ogiltiga inmatningar och otillgängliga tjänster.

- **Timeouts och retries för nätverk:**
   - **Explicita timeouts:** Nätverkssocketar i `samp_network.cpp` konfigurerar timeouts (`Constants::QUERY_TIMEOUT_MS`) för både sändning och mottagning av data, vilket förhindrar att programmet "hänger" i väntan på svar från en inaktiv server.
      ```cpp
      // samp_network.cpp (timeout-konfiguration)
      const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
      setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      ```
   - **Flera förfrågansförsök:** `Server_Query` utför `Constants::MAX_RETRY_ATTEMPTS` förfrågningar vid misslyckande. En exponentiell *back-off*-tid implementeras (`std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)))`) för att vänta innan nya försök, vilket minskar belastningen och ökar chansen för framgång i instabila nätverksförhållanden.
- **Robust hantering av frånkoppling:**
   - **Graciös statusövergång:** I `server_manager.cpp` ändras inte anslutningsstatus (`connection_status`) omedelbart efter en enskild misslyckad förfrågan. Endast om inget svar mottas under 15 sekunder i rad (`now - last_successful_query > std::chrono::seconds(15)`) uppdateras status till `false`. Detta undviker "blinkande" i Discord-närvaron på grund av mindre paketförluster.
      ```cpp
      // server_manager.cpp (logik för frånkoppling)
      else { // Om förfrågan misslyckas
          if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
              connection_status = false;
              display_image_url = Constants::DEFAULT_IMAGE;
              display_server_data = {};
              current_display_social = {};
          }
      }
      ```
   - **Visuell reserv:** Vid upptäckt av frånkoppling återgår bilden i Discord-närvaron till `Constants::DEFAULT_IMAGE`, och serverdata/sociala medier rensas, vilket ger tydlig feedback till användaren om att de inte longer är anslutna.
- **Hantering av ogiltiga inmatningar:**
   - **`command_line_parser.cpp`:** Vid konvertering av portargumentet från sträng till heltal (`std::stoi`) används ett `try-catch`-block för att hantera `std::invalid_argument` (inte ett nummer) eller `std::out_of_range` (nummer för stort/litet). Vid fel behålls standardporten eller tolkningen misslyckas kontrollerat, vilket förhindrar krascher.
- **Motståndskraft vid API-datahämtning:**
   - **WinHTTP-fel:** Alla API-operationer i `url_manager.cpp` kontrolleras för `null`-handles och returer av `false` i varje steg (öppna session, ansluta, öppna förfrågan, skicka/ta emot, läsa data), vilket säkerställer att partiella fel fångas upp.
   - **HTTP-statuskoder:** Efter en HTTP-förfrågan verifierar `url_manager.cpp` HTTP-statuskoden. Endast en kod `200 OK` accepteras som framgång, och felaktiga svar från servern eller gatewayen kastas.
   - **Säker JSON-tolkning:** `url_manager.cpp` omsluter JSON-tolkningen (`nlohmann::json::parse`) i ett `try-catch(const nlohmann::json::exception&)`-block. Detta förhindrar att felformaterade eller ofullständiga JSON-svar från API:et orsakar en krasch, och returnerar tomma strängar eller standardbilden.
- **Säkra uppdateringsmekanismer:**
   - **`asi_update.hpp`:** Uppdateringskontrollprocessen i `Check_For_Update` är inkapslad i ett `try-catch(const std::exception&)`-block. Detta säkerställer att även om GitHub är offline, nätverket är instabilt eller JSON-svaret är ogiltigt, kraschar inte **ASI** och spelet kan fortsätta laddas, genom att ignorera uppdateringskontrollen på ett säkert sätt.
   - **Hantering av WinHTTP-handles:** Frigöringen av `HINTERNET`-handles i `asi_update.hpp` och `url_manager.cpp` är noggrant planerad för att utföras i alla kodvägar (framgång och misslyckande), vilket förhindrar resursläckor.

### System för kommandoargsbehandling

**SA-MP Rich Presence** extraherar viktig information för sin drift (serverns IP, port och spelarens namn) direkt från spelets kommandorad i Grand Theft Auto: San Andreas. Denna metod säkerställer att **ASI** får de mest exakta och relevanta uppgifterna så snart spelet startas eller en server ansluts till.

#### Kommandoargs-parser (`command_line_parser.cpp`)

Klassen `Command_Line_Parser` ansvarar för att analysera hela kommandoradssträngen för processen, identifiera och extrahera de specifika parametrar som används av SA-MP.

- **`Parse()`**: Ingångspunkten för kommandoradsanalys.
   ```cpp
   // command_line_parser.cpp (viktigt utdrag av Parse)
   bool Command_Line_Parser::Parse(const std::wstring_view command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       server_ip = Constants::DEFAULT_SERVER_IP; // Standardvärden
       server_port = Constants::DEFAULT_SERVER_PORT;
   
       if (const auto ip_param = Parse_Parameter(command_line, L"-h"); !ip_param.empty())
           server_ip = Utils::Convert_Wide_To_Utf8_String(ip_param); // Extraherar och konverterar IP
   
       if (const auto port_param = Parse_Parameter(command_line, L"-p"); !port_param.empty()) {
           try {
               server_port = std::stoi(std::wstring(port_param)); // Extraherar och konverterar port (med felhantering)
           }
           catch (const std::invalid_argument&) {}
           catch (const std::out_of_range&) {}
       }
   
       if (const auto name_param = Parse_Parameter(command_line, L"-n"); !name_param.empty())
           player_name = Utils::Convert_Wide_To_Utf8_String(name_param); // Extraherar och konverterar namn
   
       return !server_ip.empty() && server_port > 0 && !player_name.empty(); // Validerar om väsentliga data finns
   }
   ```
   Tar emot kommandoraden (`command_line`) som `std::wstring_view` för effektivitet. Använder `Parse_Parameter` för att hitta och extrahera värden associerade med `-h` (host/IP), `-p` (port) och `-n` (spelarens namn). Extraherade värden (i `std::wstring_view`) konverteras till `std::string` (UTF-8) med `Utils::Convert_Wide_To_Utf8_String`. För porten omsluts `std::stoi` i ett `try-catch`-block för att hantera eventuella konverteringsfel på ett säkert sätt. Funktionen returnerar `true` om alla viktiga parametrar (IP, giltig port och spelarens namn) erhålls.
- **`Parse_Parameter()`**: Hjälpfunktionen för att extrahera en enskild parameter.
   ```cpp
   // command_line_parser.cpp (viktigt utdrag av Parse_Parameter)
   std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring_view command_string, const std::wstring_view parameter) {
       if (const size_t position = command_string.find(parameter); position != std::wstring_view::npos) {
           size_t value_start = position + parameter.length();
           value_start = command_string.find_first_not_of(L" \t", value_start); // Hoppar över mellanslag efter parametern

           if (value_start == std::wstring_view::npos)
               return L""; // Parameter hittad men utan värde
   
           const size_t value_end = command_string.find(L' ', value_start); // Hittar nästa mellanslag (värdets slut)
           
           return std::wstring(command_string.substr(value_start, value_end - value_start)); // Returnerar värdets substring
       }

       return L""; // Parameter ej hittad
   }
   ```
   Lokaliserar substrängen för `parameter` (`-h`, `-p`, `-n`) i `command_string`. Beräknar startpositionen för värdet, ignorerar mellanslag/tabbar. Identifierar värdets slutposition (nästa mellanslag) och returnerar substrängen som motsvarar parameterns värde.

### SA-MP-kommunikationsprotokoll

**ASI** interagerar direkt med SA-MP-servrar med hjälp av **UDP**-förfrågansprotokollet för att extrahera viktig realtidsinformation. Denna kommunikation är implementerad för att vara effektiv och motståndskraftig mot nätverksfel.

#### Protokollimplementering

Klassen `Server_Query` är ryggraden i denna implementering, och hanterar sändning av paket och tolkning av svar.

- **Struktur för SA-MP-förfrågningspaket (`'i'`)**: **ASI** bygger ett **UDP**-paket på 11 byte för informationsförfrågan:
   - `BYTE 0-3`: Signaturen "SAMP" (S A M P).
   - `BYTE 4-9`: Sekvens av 6 godtyckliga byte (vanligtvis käll-IP-adressen för förfrågan så att servern kan identifiera klienten).
   - `BYTE 10`: Identifieraren 'i' (ASCII 105), som indikerar att **ASI** vill ha generell serverinformation (hostname, spelare, etc.).
      ```cpp
      // server_query.cpp (paketmontering)
      void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
          memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
          packet = 'i'; // Informationsförfrågan
      }
      ```
- **Struktur för serversvaret**: När en SA-MP-server svarar på en 'i'-förfrågan skickar den ett **UDP**-paket med en sekvens av strukturerade data, som **ASI** behöver tolka:
   - **Svarshuvud:** Upprepning av signaturen "SAMP" och de 6 byte från förfrågningspaketet. **ASI** hoppar helt enkelt över dessa `Constants::QUERY_PACKET_SIZE` byte.
   - **Passworded (`bool`):** En byte som indikerar om servern är lösenordsskyddad. Läses men används inte.
   - **Players (`uint16_t`):** Antalet spelare som för närvarande är anslutna till servern.
   - **Max_Players (`uint16_t`):** Det maximala antalet spelarplatser som servern stödjer.
   - **Hostname (sträng prefixad med `uint32_t`):** Serverns vänliga namn. Paketet inkluderar en `uint32_t` för att ange strängens längd, följt av strängens faktiska byte.
   - **Andra fält:** SA-MP-protokollet fortsätter med "gamemode" och "language", också prefixade med längd. **ASI** läser och hoppar över dessa fält för att fokusera på de väsentliga data för `Players`, `Max_Players` och `Hostname`.

   Läsningen av dessa fält görs med hjälpfunktionerna `Read_From_Span` och `Read_String_From_Span`, som säkerställer att **ASI** inte läser byte utanför buffertens gränser och hanterar läsning av fasta och variabla datatyper (strängar) korrekt.
   ```cpp
   // server_query.cpp (tolkning av svaret)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       // ... (storleksverifiering och subspan för data) ...
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Läser booleska 'passworded'
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false; // Läser 'Players'

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false; // Läser 'Max_Players'

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false; // Läser 'Hostname'
   
       // Notera: 'Gamemode' och 'Language' hoppas över implicit av Read_String_From_Span
       // genom efterföljande anrop för att flytta span förbi deras data i bufferten.
       uint32_t length_placeholder; // Tillfällig variabel för att hålla längden.

       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Läser gamemode-längd

       if (data_span.size() < length_placeholder)
           return false; // Kontrollerar gränser

       data_span = data_span.subspan(length_placeholder); // Hoppar över gamemode-data
   
       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Läser language-längd

       if (data_span.size() < length_placeholder)
           return false; // Kontrollerar gränser

       data_span = data_span.subspan(length_placeholder); // Hoppar över language-data
   
       return true;
   }
   ```
   I exemplet ovan är logiken `data_span = data_span.subspan(length_placeholder);` ett effektivt sätt att "hoppa över" antalet lästa byte för en sträng vars innehåll inte behövs för Rich Presence.

### Fördelar med SA-MP Rich Presence

**SA-MP Rich Presence** förbättrar avsevärt upplevelsen för både spelare och serveradministratörer, och erbjuder betydande fördelar:

1. **För spelare:**
   - **Sömlös synlighet:** Dela automatiskt din spelstatus på Discord med vänner, och visa exakt var du spelar.
   - **Rik information:** Få omedelbar tillgång till serverdetaljer (namn, antal spelare, IP, anpassad logotyp) direkt i Discord, vilket eliminerar behovet av att kontrollera denna information på andra ställen.
   - **Direkt tillgång till communityn:** Upptäck och få snabb tillgång till serverns sociala medier genom de roterande ikonerna i Discord-närvaron, vilket underlättar anslutning till livliga communities.
   - **Snabb anslutning med vänner:** Bjud in eller gå med i samma server som dina vänner med ett klick, tack vare knappen "Join".
   - **Alltid på-upplevelse:** Systemet för automatisk uppdatering säkerställer att du alltid använder den mest optimerade och funktionella versionen av **ASI**.
2. **För servrar:**
   - **Naturlig viral marknadsföring:** Spelarnas Discord-närvaro fungerar som en digital reklamskylt, som marknadsför din server till en organisk publik (spelares vänner) dygnet runt.
   - **Stark visuell identitet:** En anpassad logotyp och rotation av sociala länkar gör att din server sticker ut och projicerar en professionell och modern image i Discord-miljön.
   - **Ökat engagemang:** Underlätta för nya och befintliga spelare att ansluta till dina sociala plattformar, vilket stärker din community och engagemang utanför spelet.
   - **Förenklad rekrytering:** Funktionen "Join" förenklar processen för nya spelare, minskar inträdesbarriärer och uppmuntrar till att prova servern.
   - **Konsistenta data:** Genom integrationen med **SPC Integration API** är informationsvisningen enhetlig och centralt uppdaterad, vilket säkerställer att din servers varumärke och kontaktuppgifter alltid är korrekta.

## Licens

Denna ASI är licensierad under Apache License 2.0, som tillåter:

- ✔️ Kommersiell och privat användning
- ✔️ Modifiering av källkoden
- ✔️ Distribution av koden
- ✔️ Patentbeviljning

### Villkor:

- Behåll upphovsrättsmeddelandet
- Dokumentera betydande ändringar
- Inkludera en kopia av Apache 2.0-licensen

För mer information om licensen: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Alla rättigheter förbehållna**