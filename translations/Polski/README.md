# SA-MP Rich Presence

**SA-MP Rich Presence** to **ASI** dla **SA-MP (San Andreas Multiplayer)**, które automatycznie aktualizuje Twój status na Discordzie, wyświetlając szczegółowe informacje o serwerze. **ASI** jest wstrzykiwane do gry po połączeniu z serwerem SA-MP, pokazując informacje o serwerze.

## Języki

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Spis treści

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Języki](#języki)
  - [Spis treści](#spis-treści)
  - [Funkcjonalności](#funkcjonalności)
    - [Discord Rich Presence](#discord-rich-presence)
    - [System automatycznej aktualizacji](#system-automatycznej-aktualizacji)
  - [Wymagania](#wymagania)
  - [Instalacja](#instalacja)
  - [Integracja z AlderGrounds Integration API](#integracja-z-aldergrounds-integration-api)
    - [Jak informacje są pobierane i wykorzystywane:](#jak-informacje-są-pobierane-i-wykorzystywane)
  - [Dla twórców serwerów](#dla-twórców-serwerów)
    - [Jak zaimplementować AlderGrounds Integration na swoim serwerze:](#jak-zaimplementować-aldergrounds-integration-na-swoim-serwerze)
  - [Szczegółowa architektura techniczna](#szczegółowa-architektura-techniczna)
      - [System główny (`main.cpp`)](#system-główny-maincpp)
      - [System aktualizacji (`asi_update.hpp`)](#system-aktualizacji-asi_updatehpp)
      - [Menedżer Discorda (`discord_manager.cpp`)](#menedżer-discorda-discord_managercpp)
      - [Menedżer serwera (`server_manager.cpp`)](#menedżer-serwera-server_managercpp)
      - [System sieciowy (`samp_network.cpp`)](#system-sieciowy-samp_networkcpp)
      - [Zapytanie do serwera (`server_query.cpp`)](#zapytanie-do-serwera-server_querycpp)
      - [Menedżer URL (`url_manager.cpp`)](#menedżer-url-url_managercpp)
    - [Struktura kodu](#struktura-kodu)
      - [Stałe globalne (`constants.hpp`)](#stałe-globalne-constantshpp)
      - [Struktury danych (`server_types.hpp`)](#struktury-danych-server_typeshpp)
      - [Zabezpieczanie tajemnic (`secrets.hpp`)](#zabezpieczanie-tajemnic-secretshpp)
      - [Narzędzia ogólne (`utils.hpp`)](#narzędzia-ogólne-utilshpp)
    - [Obsługa błędów i odporność](#obsługa-błędów-i-odporność)
    - [System przetwarzania linii poleceń](#system-przetwarzania-linii-poleceń)
      - [Parser linii poleceń (`command_line_parser.cpp`)](#parser-linii-poleceń-command_line_parsercpp)
    - [Protokół komunikacji SA-MP](#protokół-komunikacji-sa-mp)
      - [Implementacja protokołu](#implementacja-protokołu)
    - [Korzyści płynące z SA-MP Rich Presence](#korzyści-płynące-z-sa-mp-rich-presence)
  - [Licencja](#licencja)
    - [Warunki:](#warunki)

## Funkcjonalności

### Discord Rich Presence

**Discord Rich Presence** to funkcja, która umożliwia aplikacjom wyświetlanie szczegółowych informacji o tym, co użytkownik robi, bezpośrednio na jego profilu na Discordzie. W przypadku **SA-MP Rich Presence** wyświetlane są następujące informacje:

- **Nazwa serwera (Hostname):** Główna nazwa serwera.
- **Nazwa gracza:** Twój aktualny pseudonim w grze.
- **Liczba graczy:** Aktualna liczba graczy online oraz maksymalna dozwolona liczba.
- **Adres serwera:** IP i port serwera dla łatwej identyfikacji.
- **Spersonalizowany obraz serwera:** Unikalne logo serwera, jeśli dostępne.
- **Rotująca ikona społecznościowa:** Małe ikony reprezentujące linki do mediów społecznościowych serwera (strona internetowa, Discord, YouTube, Instagram, Facebook, TikTok), zmieniające się automatycznie.
- **Czas gry:** Jak długo jesteś połączony z aktualnym serwerem.
- **Status połączenia:** Wskazuje, czy jesteś online na serwerze, czy w stanie "Idle" (bezczynnym).
- **Przycisk "Join" (Dołącz):** Pozwala Twoim znajomym dołączyć bezpośrednio do tego samego serwera, na którym grasz.

### System automatycznej aktualizacji

**ASI** zawiera system sprawdzania aktualizacji. Po uruchomieniu gry sprawdza, czy dostępne są nowe wersje w oficjalnym repozytorium GitHub projektu. Jeśli aktualizacja zostanie wykryta, wyświetlane jest przyjazne powiadomienie, oferujące opcje:

1. Otwarcie przeglądarki bezpośrednio na stronie wydań w celu pobrania.
2. Kontynuowanie bez aktualizacji, z opcją wyłączenia **ASI** na czas bieżącej sesji.

Ta funkcja zapewnia użytkownikom dostęp do najnowszych ulepszeń, poprawek błędów i nowych funkcji, promując aktualne i nieprzerwane doświadczenie.

## Wymagania

- Klient SA-MP (jeśli go nie posiadasz: [clients-samp](https://github.com/aldergrounds/clients-samp)).
- Aplikacja Discord Desktop.
- System operacyjny Windows.
- Visual C++ Runtime.
- Zainstalowany [ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) w Twoim Grand Theft Auto: San Andreas.

## Instalacja

1. Pobierz najnowszą wersję skompilowanego **ASI** bezpośrednio z sekcji [releases](https://github.com/ocalasans/samp-rich-presence/releases) na GitHubie.
2. Po pobraniu znajdź plik `.asi`.
3. Skopiuj pobrany plik `.asi` do głównego folderu Twojego GTA San Andreas (tam, gdzie znajduje się plik `gta_sa.exe`).
4. Uruchom grę przez klienta SA-MP.
5. **ASI** zostanie automatycznie załadowane i zainicjalizowane po połączeniu z serwerem, aktualizując Twój status na Discordzie.

## Integracja z AlderGrounds Integration API

**SA-MP Rich Presence** znacząco poprawia wyświetlanie informacji na Discordzie dzięki integracji z **AlderGrounds Integration API**. Zamiast polegać tylko na podstawowych danych z zapytań, **ASI** teraz bezpośrednio komunikuje się z tą API, aby uzyskać wizualne i społecznościowe informacje o serwerze. Aby dowiedzieć się więcej o **AlderGrounds Integration**, odwiedź oficjalne repozytorium: [aldergrounds/integration](https://github.com/aldergrounds/integration).

### Jak informacje są pobierane i wykorzystywane:

1. **Formatowanie adresu:** Gdy gracz łączy się z serwerem (IP i Port), **ASI** formatuje ten adres (`IP:PORT`) na przyjazny wzorzec (`IP-PORT`), przygotowując go do żądania API.
2. **Żądanie do API:** **ASI** wysyła żądanie `GET` do endpointu **AlderGrounds Integration API**, zawierające sformatowane IP i port. Przykład, jak wewnętrznie tworzony jest adres URL żądania:
   ```cpp
   // Trecho adaptado de url_manager.cpp
   auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
   std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
   path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   const std::string json_data = Request_API_Data(path);
   ```
3. **Przetwarzanie odpowiedzi JSON:** API zwraca odpowiedź w formacie JSON. **ASI** używa biblioteki [nlohmann/json](https://github.com/nlohmann/json) do parsowania tej odpowiedzi i wyodrębnienia istotnych danych.
   ```json
   // Przykład struktury odpowiedzi AlderGrounds Integration API
   {
       "success": true,
       "data": {
           "public": {
               "logo": "https://url.do.seu.logo/server_logo.png",
               "website": "https://seu-site.com",
               "discord": "https://discord.gg/seuservidor",
               "youtube": "https://youtube.com/seucanal"
               // ...inne media społecznościowe
           }
       }
   }
   ```
4. **Ekstrakcja danych:**
   - **Logo serwera:** URL obrazu serwera (pole `logo` w sekcji `public`) jest wyodrębniany i używany jako główny obraz (large image) w **Discord Rich Presence**. Gwarantuje to autentyczną i konfigurowalną tożsamość wizualną dla każdego serwera.
   - **Linki społecznościowe:** Predefiniowana lista mediów społecznościowych (strona internetowa, Discord, YouTube, Instagram, Facebook, TikTok) jest sprawdzana w odpowiedzi JSON. Dla każdego znalezionego i ważnego medium społecznościowego nazwa medium i odpowiadający mu link są zapisywane.
5. **Wyświetlanie na Discordzie:** `Server_Manager` używa listy wyodrębnionych linków społecznościowych do wdrożenia dynamicznej rotacji. Co 30 sekund inny ikonka jednego z mediów społecznościowych serwera jest wyświetlana jako "small image" (mały obraz) w obecności na Discordzie, wraz z linkiem lub nazwą platformy, zachęcając do eksploracji społeczności serwera.

## Dla twórców serwerów

Integracja Twojego serwera z [AlderGrounds Integration](https://github.com/aldergrounds/integration) przynosi szereg bezpośrednich i pośrednich korzyści, które zwiększają widoczność i zaangażowanie Twojej społeczności SA-MP. Jeśli jesteś twórcą serwera, rozważ strategiczne zalety:

1. **Wzmocnienie marki:**
   - **Premium widoczność:** Spersonalizowane logo Twojego serwera to nie tylko tekst, ale żywy i przyciągający uwagę obraz, wyświetlany w widocznym miejscu na profilu Discord każdego gracza korzystającego z tego **ASI**. To organiczna i ciągła forma brandingu.
   - **Profesjonalna obecność:** Poprzez wyraźne przedstawienie logo i mediów społecznościowych, Twój serwer zyskuje bardziej ugruntowany i wiarygodny wizerunek, przyciągając większe zainteresowanie i potencjalnych nowych graczy.
2. **Rozwój społeczności:**
   - **Zwiększenie kanałów dostępu:** Dzięki rotacji ikon społecznościowych możesz promować różne platformy swojej społeczności – od oficjalnej strony internetowej i Discorda serwera po strony na YouTube, Instagramie, Facebooku czy TikToku. Każda ikona i link w **Discord Rich Presence** kieruje zainteresowanych bezpośrednio do miejsc, gdzie Twoja społeczność jest aktywna.
   - **Natychmiastowa łączność:** Funkcjonalność "Join" przez Discord pozwala znajomym Twoich graczy dołączyć do Twojego serwera SA-MP jednym kliknięciem, zmniejszając bariery wejścia i zachęcając nowych członków.
3. **Uproszczona aktualizacja treści:**
   - Korzystając z [AlderGrounds Integration](https://github.com/aldergrounds/integration), każda aktualizacja logo Twojego serwera lub listy mediów społecznościowych skonfigurowanych w wtyczce [AlderGrounds Integration](https://github.com/aldergrounds/integration) **(po stronie serwera)** zostanie automatycznie odzwierciedlona dla graczy korzystających z **ASI**, bez konieczności aktualizacji **ASI** przez nich. Gwarantuje to, że informacje są zawsze poprawne i aktualne.

### Jak zaimplementować AlderGrounds Integration na swoim serwerze:

1. **Wtyczka AlderGrounds Integration:** Twój serwer musi mieć zainstalowaną i poprawnie skonfigurowaną wtyczkę [AlderGrounds Integration](https://github.com/aldergrounds/integration). Ta wtyczka jest mostem, który przesyła informacje o Twoim serwerze do listy danych **AlderGrounds**, które następnie są wykorzystywane przez **AlderGrounds Integration API** do udostępniania informacji publicznych.
2. **Konfiguracja:** Postępuj zgodnie z instrukcjami w repozytorium wtyczki [AlderGrounds Integration](https://github.com/aldergrounds/integration), aby skonfigurować:
   - Parametr `logo` z adresem URL logo Twojego serwera.
   - Parametry mediów społecznościowych (`discord`, `website`, `youtube` itp.) z ważnymi linkami do Twoich platform.
3. **Automatyczna aktualizacja:** Po skonfigurowaniu informacji w wtyczce serwera, **SA-MP Rich Presence** automatycznie je wykryje i wyświetli. Nie jest wymagane żadne działanie ze strony gracza poza początkową instalacją **ASI**.

Integrując swój serwer z [AlderGrounds Integration](https://github.com/aldergrounds/integration), nie tylko poprawiasz doświadczenie swoich graczy, ale także otwierasz drzwi do znaczącego wzrostu i zaangażowania Twojej społeczności.

## Szczegółowa architektura techniczna

**SA-MP Rich Presence** posiada dobrze zdefiniowaną modułową architekturę, z komponentami skupionymi na konkretnych zadaniach. Baza kodu jest zgodna z nowoczesnymi standardami C++ (C++17 i C++20), wykorzystując `std::string_view`, `std::span` oraz semantykę przenoszenia dla zapewnienia wysokiej wydajności, bezpieczeństwa i efektywności.

#### System główny (`main.cpp`)

Serce **ASI** znajduje się w `main.cpp`, który zarządza cyklem życia aplikacji, od inicjalizacji jako DLL, przez ciągły cykl aktualizacji, aż po łagodne zamknięcie.

- **`DllMain`**: Punkt wejścia **ASI**, gdy jest ładowane przez system operacyjny.
   ```cpp
   // DllMain (uproszczone dla skupienia na strukturze)
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
   W tej funkcji, po dołączeniu do procesu gry (`DLL_PROCESS_ATTACH`), blokuje niepotrzebne wywołania bibliotek (`DisableThreadLibraryCalls`) i **tworzy nowy wątek (`Main_Update_Thread`)** do asynchronicznego wykonywania logiki **ASI**, zapewniając, że gra nie zostanie zablokowana. Podczas zamykania (`DLL_PROCESS_DETACH`), `Shutdown_Managers()` jest wywoływane w celu zwolnienia zasobów.
- **`Main_Update_Thread`**: Dusza **ASI**, działająca we własnym wątku.
   ```cpp
   // Main_Update_Thread (kluczowy fragment)
   DWORD WINAPI Main_Update_Thread(LPVOID) {
       // 1. Sprawdzanie aktualizacji
       if (Asi_Update::Check_For_Update())
           return 0; // Jeśli użytkownik wybrał wyłączenie, kończy.
   
       // 2. Inicjalizacja sieci (Winsock)
       WSAData wsa_data;

       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
   
       // 3. Inicjalizacja menedżerów serwera i Discorda
       Initialize_Managers();
   
       // 4. Główna pętla aktualizacji
       while (is_running && v_server_manager && v_discord_manager) {
           v_server_manager->Update(); // Zapytania do serwera, API AlderGrounds, itp.
           v_discord_manager->Update_Presence( // Aktualizuje status na Discordzie
               v_server_manager->Get_Server_Info(),
               v_server_manager->Get_Display_Social_Link(),
               v_server_manager->Get_Player_Name(),
               v_server_manager->Get_Current_Image_URL(),
               v_server_manager->Is_Connected());
   
           Discord_RunCallbacks(); // Przetwarza zdarzenia RPC Discorda
           std::this_thread::sleep_for(Constants::MAIN_LOOP_INTERVAL);
       }
   
       // 5. Zamknięcie (jeśli menedżery istnieją)
       if (v_discord_manager)
           v_discord_manager->Shutdown();

       WSACleanup(); // Zwalnia Winsock

       return 0;
   }
   ```
   Ta funkcja priorytetowo sprawdza aktualizacje. Następnie inicjalizuje stos sieciowy Winsock oraz instancje menedżerów serwera i Discorda. Trwała pętla `while` (kontrolowana przez `std::atomic<bool> is_running` dla bezpiecznego zamykania) koordynuje wywołania `Server_Manager::Update()` (zbieranie danych) i `Discord_Manager::Update_Presence()` (wysyłanie do Discorda). `Discord_RunCallbacks()` zapewnia, że Discord przetwarza zdarzenia Rich Presence. Pętla jest okresowo pauzowana za pomocą `std::this_thread::sleep_for` dla optymalizacji zasobów.

#### System aktualizacji (`asi_update.hpp`)

Ten kluczowy moduł dodaje inteligencję do **ASI**, zapewniając użytkownikom aktualność.

- **`Check_For_Update()`**: Główna funkcja sprawdzania aktualizacji.
   ```cpp
   // asi_update.hpp (kluczowy fragment Check_For_Update)
   inline bool Check_For_Update() {
       HINTERNET h_session = nullptr, h_connect = nullptr, h_request = nullptr;
       bool update_found_and_handled = false;
   
       try {
           h_session = WinHttpOpen(L"SA-MP Rich Presence Update/1.0", ...);
           // ... (żądanie GET do Constants::UPDATE_API_PATH w API GitHub) ...
           std::string response_body;
           // ... (odczyt odpowiedzi HTTP) ...
           nlohmann::json release_info = nlohmann::json::parse(response_body);
   
           std::string latest_tag = release_info["tag_name"].get<std::string>();
           // ... (normalizacja i porównanie wersji za pomocą sscanf_s/sscanf) ...
   
           if (latest_major > current_major || (latest_major == current_major && latest_minor > current_minor)) {
               update_found_and_handled = true;
               std::wstringstream message_stream;
               // ... (przygotowanie wiadomości dla MessageBox) ...
               int msgbox_result = MessageBoxW(NULL, message_stream.str().c_str(), L"SA-MP Rich Presence - Update Available", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
               
               if (msgbox_result == IDYES)
                   ShellExecuteW(NULL, L"open", Constants::UPDATE_RELEASES_URL, NULL, NULL, SW_SHOWNORMAL);
           }
       }
       catch (const std::exception&) { /* Obsługa błędów */ }
   
       // ... (zamykanie uchwytów WinHttp) ...
       return update_found_and_handled;
   }
   ```
   Korzystając z **API WinHTTP** dla żądań sieciowych, `Check_For_Update` wykonuje żądanie `GET` do endpointu `/releases/latest` API GitHub dla repozytorium projektu. Odpowiedź w formacie JSON jest parsowana za pomocą biblioteki `nlohmann/json`. Najnowsza wersja (`tag_name`) jest porównywana numerycznie z wersją skompilowaną **ASI**. Jeśli wykryta zostanie nowa wersja, wyświetlane jest okno dialogowe (`MessageBoxW`), pytające użytkownika, czy chce przejść do strony pobrań za pomocą `ShellExecuteW`. Cały proces jest otoczony blokiem `try-catch`, aby zapewnić, że niepowodzenia sieciowe lub parsowania nie zakłócą uruchamiania gry.

#### Menedżer Discorda (`discord_manager.cpp`)

Klasa `Discord_Manager` abstrahuje interakcje z biblioteką **Discord RPC**, zarządzając inicjalizacją połączenia i wysyłaniem danych do statusu obecności użytkownika.

- **`Initialize()`**: Konfiguruje komunikację z Discordem.
   ```cpp
   // discord_manager.cpp (kluczowy fragment Initialize)
   void Discord_Manager::Initialize() noexcept {
       DiscordEventHandlers handlers;
       memset(&handlers, 0, sizeof(handlers)); // Zapewnia inicjalizację
       
       // App ID jest deszyfrowane tutaj
       auto app_id_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_Discord_App_ID());
       Discord_Initialize(app_id_accessor.Get(), &handlers, 1, nullptr);
   
       start_timestamp_ = time(nullptr); // Rejestruje początek sesji
   }
   ```
   Wywołanie `Discord_Initialize` jest kluczowe, wykorzystując `DISCORD_APP_ID`, który jest uzyskiwany w bezpieczny sposób przez deszyfrowanie ciągu w `secrets.hpp`. `start_timestamp_` jest ustawiany tutaj, aby obliczyć czas gry w obecności na Discordzie.
- **`Update_Presence()`**: Kluczowa funkcja aktualizująca Rich Presence na Discordzie.
   ```cpp
   // discord_manager.cpp (kluczowy fragment Update_Presence)
   void Discord_Manager::Update_Presence(const Server_Information& server_info, const server_types::Social_Link& social_link, const std::string_view player_name, const std::string_view current_image, const bool is_connected) noexcept {
       DiscordRichPresence discord_presence;
       memset(&discord_presence, 0, sizeof(discord_presence));
   
       discord_presence.startTimestamp = start_timestamp_;
       discord_presence.largeImageKey = current_image.data(); // Logo serwera
   
       if (is_connected) {
           discord_presence.details = server_info.Hostname.c_str();
           discord_presence.state = player_name.data();
           discord_presence.largeImageText = server_info.Server_Address.c_str(); // IP:Port
           discord_presence.partySize = server_info.Players;
           discord_presence.partyMax = server_info.Max_Players;
           discord_presence.joinSecret = server_info.Server_Address.c_str(); // Włącza przycisk "Join"
   
           // Zarządza rotującą ikoną społecznościową
           if (!social_link.first.empty()) {
               current_small_image_key_ = Constants::SOCIAL_ICON_BASE_URL;
               current_small_image_key_ += social_link.first; // Np.: "discord.png"
               current_small_image_key_ += ".png";
               discord_presence.smallImageKey = current_small_image_key_.c_str();
               discord_presence.smallImageText = social_link.second.c_str(); // Tekst po najechaniu myszą (link/nazwa)
           }
       }
       else {
           discord_presence.details = "SA-MP"; // Stan "Idle"
           discord_presence.state = "Idle";
           discord_presence.largeImageText = "San Andreas Multiplayer";
           // smallImageKey i smallImageText pozostają puste dla stanu bezczynności
       }
   
       Discord_UpdatePresence(&discord_presence);
   }
   ```
   Wypełnia strukturę `DiscordRichPresence` na podstawie stanu połączenia. Jeśli `is_connected` jest prawdziwe, wyświetlane są hostname, liczba graczy, IP serwera i nazwa gracza. `largeImageKey` określa główny obraz serwera. Warto zauważyć, że `joinSecret` jest ustawiany, aby umożliwić znajomym bezpośrednie łączenie, a `smallImageKey` (dynamicznie budowany na podstawie dostarczonego `social_link`) wyświetla rotujące ikony społecznościowe. W stanie "Idle" obecność jest uproszczona, aby odzwierciedlić brak aktywności. Na koniec `Discord_UpdatePresence` wysyła dane do Discorda.

#### Menedżer serwera (`server_manager.cpp`)

`Server_Manager` jest orkiestratorem danych, zarządzając stanem połączenia, wysyłając zapytania do serwera i **AlderGrounds Integration API**, oraz decydując, które informacje powinny być wyświetlane i kiedy.

- **`Update()`**: Główny cykl życia dla zbierania danych.
   ```cpp
   // server_manager.cpp (kluczowy fragment Update)
   void Server_Manager::Update() {
       const auto now = std::chrono::steady_clock::now();
   
       if (server_query.Query(live_server_data)) { // Próbuje uzyskać dane przez zapytanie SAMP
           if (!connection_status) { // Jeśli właśnie się połączył/ponownie połączył
               connection_status = true;
               Fetch_API_Data(); // Pobiera logo i media społecznościowe z API
           }
           
           last_successful_query = now;
   
           // Aktualizuje dane do wyświetlenia na Discordzie
           display_server_data.Hostname = live_server_data.Hostname;
           display_server_data.Players = live_server_data.Players;
           display_server_data.Max_Players = live_server_data.Max_Players;
           display_server_data.Server_Address = server_ip + ":" + std::to_string(server_port);
   
           if (now - last_api_update > Constants::IMAGE_UPDATE_INTERVAL)
               Fetch_API_Data(); // Ponownie konsultuje API po określonym czasie
   
           if (now - last_social_rotation > Constants::SOCIAL_UPDATE_INTERVAL)
               Rotate_Social_Link(); // Rotuje ikonę społecznościową
       }
       else { // Jeśli zapytanie nie powiodło się
           if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
               connection_status = false; // Rozłączony po przekroczeniu limitu czasu
               display_image_url = Constants::DEFAULT_IMAGE;
               display_server_data = {}; // Czyści dane
               current_display_social = {}; // Czyści media społecznościowe
           }
       }
   }
   ```
   Funkcja `Update` próbuje wykonać zapytanie do serwera. W przypadku powodzenia aktualizuje dane w `live_server_data` i `display_server_data`. Warunkowo wywołuje `Fetch_API_Data()` w celu aktualizacji obrazu i linków społecznościowych (jeśli jest to nowe połączenie lub minął `IMAGE_UPDATE_INTERVAL`) oraz `Rotate_Social_Link()` w celu przełączania ikon społecznościowych (`SOCIAL_UPDATE_INTERVAL`). Jeśli zapytania do serwera nie powiodą się przez ponad 15 sekund, status połączenia jest uznawany za utracony, resetując wyświetlane informacje.
- **`Fetch_API_Data()`**: Odpowiedzialne za pobieranie danych wizualnych i społecznościowych.
   ```cpp
   // server_manager.cpp (kluczowy fragment Fetch_API_Data)
   void Server_Manager::Fetch_API_Data() {
       display_image_url = url_manager.Get_Image_URL_And_Populate_Socials(server_ip, server_port, live_server_data);
       last_api_update = std::chrono::steady_clock::now();
       current_social_index_ = 0; // Resetuje indeks po nowym pobraniu API
       Rotate_Social_Link(); // Zapewnia, że ikona społecznościowa jest wyświetlana natychmiast
   }
   ```
   Ta funkcja koordynuje z `URL_Manager`, aby pobrać logo i linki społecznościowe z API, aktualizując `display_image_url` i wypełniając `Social_Links` w `live_server_data`. Resetuje indeks rotacji społecznościowej i wywołuje `Rotate_Social_Link()`, aby zapewnić, że pierwsza ikona jest gotowa do wyświetlenia.
- **`Rotate_Social_Link()`**: Logika przełączania ikon społecznościowych.
   ```cpp
   // server_manager.cpp (kluczowy fragment Rotate_Social_Link)
   void Server_Manager::Rotate_Social_Link() {
       if (!live_server_data.Social_Links.empty()) {
           if (current_social_index_ >= live_server_data.Social_Links.size())
               current_social_index_ = 0; // Restartuje cykl
   
           current_display_social = live_server_data.Social_Links[current_social_index_];
           current_social_index_ = (current_social_index_ + 1) % live_server_data.Social_Links.size();
       }
       else
           current_display_social = {}; // Czyści, jeśli nie ma mediów społecznościowych
       
       last_social_rotation = std::chrono::steady_clock::now();
   }
   ```
   Ta prosta funkcja wybiera kolejny `Social_Link` z listy `live_server_data.Social_Links` w sposób cykliczny i zapisuje go w `current_display_social`, aby `Discord_Manager` mógł go wykorzystać.

#### System sieciowy (`samp_network.cpp`)

Klasa `Samp_Network` to implementacja niskopoziomowej komunikacji **UDP**, odpowiedzialna za otwieranie i zarządzanie gniazdem dla zapytań SA-MP. Teraz oferuje konstruktory i operatory przenoszenia dla lepszego zarządzania zasobami.

- **`Initialize()`**: Konfiguruje gniazdo dla komunikacji **UDP**.
   ```cpp
   // samp_network.cpp (kluczowy fragment Initialize)
   bool Samp_Network::Initialize(const std::string_view ip, const int port) noexcept {
       if (network_socket != INVALID_SOCKET)
           closesocket(network_socket); // Zamyka istniejące gniazdo
   
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       if (network_socket == INVALID_SOCKET)
           return false;
   
       const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
       setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
   
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(static_cast<u_short>(port));
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr); // Wsparcie dla IPv4
       return true;
   }
   ```
   Inicjalizuje gniazdo, ustawia limity czasu dla operacji wysyłania i odbierania oraz konfiguruje strukturę adresu (`sockaddr_in`) z IP i portem serwera docelowego, używając `inet_pton` do konwersji IP.
- **`Send_Query()`**: Wysyła pakiet zapytania i odbiera odpowiedź.
   ```cpp
   // samp_network.cpp (kluczowy fragment Send_Query)
   bool Samp_Network::Send_Query(const std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept {
       // Wysłanie pakietu UDP
       if (sendto(network_socket, query_packet.data(), static_cast<int>(query_packet.size()), 0, reinterpret_cast<const sockaddr*>(&server_address), sizeof(server_address)) < 0)
           return false;
   
       sockaddr_in from_address;
       int address_length = sizeof(from_address);
       // Odebranie odpowiedzi
       received_bytes = recvfrom(network_socket, response_buffer.data(), static_cast<int>(response_buffer.size()), 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);
   
       return received_bytes > Constants::QUERY_PACKET_SIZE;
   }
   ```
   Ta metoda wysyła `query_packet` (przekazany jako `std::span` dla bezpieczeństwa bufora) do serwera. Następnie próbuje odebrać odpowiedź w `response_buffer`. Zwracana wartość wskazuje, czy operacja zakończyła się sukcesem i czy odebrano więcej bajtów niż rozmiar pakietu zapytania.

#### Zapytanie do serwera (`server_query.cpp`)

Klasa `Server_Query` jest dedykowana implementacji protokołu zapytań SA-MP (`'i'`), wyodrębniając podstawowe informacje o serwerze (gracze, hostname) z odpowiedzi **UDP**.

- **`Query()`**: Zarządza próbami zapytań.
   ```cpp
   // server_query.cpp (kluczowy fragment Query)
   bool Server_Query::Query(Server_Information& server_data) noexcept {
       for (int attempt = 0; attempt < Constants::MAX_RETRY_ATTEMPTS; ++attempt) {
           if (Try_Query(server_data))
               return true; // Sukces zapytania
   
           if (attempt < Constants::MAX_RETRY_ATTEMPTS - 1)
               // Krótka przerwa przed ponowną próbą, aby uniknąć przeciążenia
               std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)));
       }

       return false; // Wszystkie próby nie powiodły się
   }
   ```
   Implementuje strategię ponownych prób z `MAX_RETRY_ATTEMPTS` i rosnącym czasem oczekiwania, aby zapewnić, że zapytania są odporne i unikają przeciążenia sieci. Wywołuje `Try_Query` przy każdej próbie.
- **`Assemble_Query_Packet()`**: Składa pakiet zapytania SA-MP.
   ```cpp
   // server_query.cpp (kluczowy fragment Assemble_Query_Packet)
   void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
       memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
       packet = 'i'; // Kod zapytania informacji
   }
   ```
   Standardowy pakiet dla zapytania informacji (`'i'`) SA-MP jest budowany, zawierając podpis "SAMP" i bajt identyfikatora 'i'.
- **`Parse_Response()`**: Rozpakowuje binarną odpowiedź serwera.
   ```cpp
   // server_query.cpp (kluczowy fragment Parse_Response)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       if (response.size() <= Constants::QUERY_PACKET_SIZE) 
           return false;
   
       auto data_span = response.subspan(Constants::QUERY_PACKET_SIZE); // Pomija nagłówek
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Ignorowane, ale odczytywane
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false;

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false;

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false;
   
       // Uwaga: Gamemode i Language są automatycznie pomijane przez Read_String_From_Span, jeśli pakiet zawiera więcej danych.
       // Jeśli potrzebujesz innych pól, wystarczy stworzyć string i wywołać: Read_String_From_Span(data_span, string_variable);
       return true;
   }
   ```
   Ta metoda bezpiecznie odczytuje dane z `response_buffer` (używając `std::span` oraz funkcji pomocniczych `Read_From_Span` i `Read_String_From_Span`). Wyodrębnia liczbę graczy, maksymalną liczbę graczy oraz hostname serwera, wypełniając strukturę `Server_Information`. Nieużywane pola (np. czy serwer jest chroniony hasłem) są odczytywane, ale ignorowane, a inne, takie jak "gamemode" i "language", są pomijane, jeśli odpowiedź zawiera więcej danych, niż potrzebuje **ASI**.
- **Funkcje odczytu pomocnicze:**
   ```cpp
   // server_query.hpp (fragmenty funkcji pomocniczych)
   template<typename T>
   static bool Read_From_Span(std::span<const char>& s, T& value) noexcept;
   
   static bool Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept;
   ```
   `Read_From_Span` obsługuje odczyt typów stałych (całkowite, logiczne) z `std::span` i przesuwa `span`. `Read_String_From_Span` odczytuje długość ciągu (jako `uint32_t`), a następnie sam ciąg, również przesuwając `span`. Zapewnia to bezpieczeństwo podczas parsowania bajtów i zapobiega odczytom poza granicami bufora.

#### Menedżer URL (`url_manager.cpp`)

Klasa `URL_Manager` zarządza komunikacją HTTPS z **AlderGrounds Integration API**, kluczowym elementem dla nowych funkcji wizualnych i społecznościowych **Discord Rich Presence**.

- **`Get_Image_URL_And_Populate_Socials()`**: Metoda wysokiego poziomu do pobierania informacji z API.
   ```cpp
   // url_manager.cpp (kluczowy fragment Get_Image_URL_And_Populate_Socials)
   std::string URL_Manager::Get_Image_URL_And_Populate_Socials(const std::string& ip, const int port, Server_Information& server_info) {
       if (!session_handle)
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);
   
       auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
       std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
       path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   
       const std::string json_data = Request_API_Data(path); // Żądanie HTTP do API
   
       if (json_data.empty())
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE); // Błąd żądania
   
       return Parse_API_Response(json_data, server_info); // Parsuje i wypełnia server_info
   }
   ```
   Przyjmuje IP i port, buduje URL API, dołączając je jako parametry. Wywołuje `Request_API_Data`, aby pobrać dane JSON. W przypadku powodzenia `Parse_API_Response` jest wywoływane, aby wyodrębnić URL obrazu (logo) i wypełnić listę linków społecznościowych w `server_info`.
- **`Request_API_Data()`**: Wykonuje żądanie HTTPS do API.
   ```cpp
   // url_manager.cpp (kluczowy fragment Request_API_Data)
   std::string URL_Manager::Request_API_Data(const std::wstring& path) {
       auto api_host_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Host());
       const std::wstring wide_host = Utils::Convert_Utf8_To_Wide_String(api_host_accessor.Get());
       HINTERNET connect_handle = WinHttpConnect(session_handle, wide_host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
   
       if (!connect_handle) return "";
   
       HINTERNET request_handle = WinHttpOpenRequest(connect_handle, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
   
       if (!request_handle) return (WinHttpCloseHandle(connect_handle), "");
   
       // Wysłanie żądania, odebranie odpowiedzi, sprawdzenie statusu 200, odczyt danych w pętli
       // ... (szczegóły wywołania WinHttpSendRequest, WinHttpReceiveResponse, WinHttpQueryHeaders, WinHttpReadData) ...
       
       WinHttpCloseHandle(request_handle); WinHttpCloseHandle(connect_handle);
       return response_body; // Zwraca JSON jako ciąg
   }
   ```
   Łączy się z hostem API (uzyskanym w sposób zaszyfrowany), otwiera i wysyła żądanie `GET` z podaną ścieżką (`path`). Obsługuje odpowiedź HTTP, sprawdza kod statusu (200 OK dla sukcesu) i odczytuje pełne ciało odpowiedzi (które powinno być JSON). Wszystkie uchwyty WinHTTP są zwalniane w przypadku powodzenia lub niepowodzenia.
- **`Parse_API_Response()`**: Przetwarza ciąg JSON w celu wyodrębnienia danych.
   ```cpp
   // url_manager.cpp (kluczowy fragment Parse_API_Response)
   std::string URL_Manager::Parse_API_Response(const std::string& json_content, Server_Information& server_info) {
       server_info.Social_Links.clear(); // Czyści istniejące linki społecznościowe
       try {
           const auto json = nlohmann::json::parse(json_content);
   
           if (json.value("success", false) && json.contains("data") && json["data"].contains("public")) {
               const auto& public_data = json["data"]["public"];
               const std::vector<std::string> social_keys = { "website", "discord", "youtube", "instagram", "facebook", "tiktok" };
               
               // Wyodrębnia i wypełnia linki społecznościowe
               for (const auto& key : social_keys) {
                   if (public_data.contains(key)) {
                       std::string value = public_data.value(key, "not-defined");

                       if (!value.empty() && value != "not-defined")
                           server_info.Social_Links.push_back({ key, value });
                   }
               }

               return public_data.value("logo", ""); // Zwraca URL logo
           }
       }
       catch (const nlohmann::json::exception&) { /* Obsługuje błąd parsowania */ }

       return ""; // Niepowodzenie parsowania
   }
   ```
   Używa `nlohmann::json::parse` do konwersji ciągu JSON na obiekt JSON, który można manipulować. Nawiguje po strukturze (`success`, `data`, `public`) i wyodrębnia `logo` (które staje się `display_image_url`) oraz iteruje po predefiniowanych kluczach, aby znaleźć i wypełnić `Social_Links` w `server_info`.

### Struktura kodu

Projekt **SA-MP Rich Presence** jest starannie zorganizowany w przejrzystej strukturze katalogów, z kodem źródłowym (`src/`) i podkatalogiem dla bibliotek zewnętrznych (`libraries/`). Nazewnictwo plików stosuje konwencję `_manager` lub `_network` dla jasności co do celu każdej klasy. Większość plików nagłówkowych używa rozszerzenia `.hpp`, wskazując, że są to nagłówki C++.

```
src/
├── libraries/               # Zawiera podstawowe biblioteki zewnętrzne
│   ├── Dralyxor/            # Biblioteka do szyfrowania ciągów
│   ├── Discord/             # Oficjalna biblioteka Discord RPC
│   └── nlohmann/            # Biblioteka do manipulacji JSON
├── asi_update.hpp           # Definicja systemu automatycznej aktualizacji
├── command_line_parser.hpp  # Definicja parsera linii poleceń
├── constants.hpp            # Definicje globalnych stałych projektu
├── discord_manager.hpp      # Definicja menedżera komunikacji z Discordem
├── main.cpp                 # Punkt wejścia ASI i główny orkiestrator
├── samp_network.hpp         # Definicja menedżera sieci dla zapytań SA-MP
├── secrets.hpp              # Definicje do szyfrowania tajemnic
├── server_manager.hpp       # Definicja menedżera informacji o serwerze
├── server_query.hpp         # Definicja logiki zapytań do serwera SA-MP
├── server_types.hpp         # Definicje struktur danych serwera
├── url_manager.hpp          # Definicja menedżera URL dla AlderGrounds Integration API
└── utils.hpp                # Ogólne funkcje narzędziowe (konwersja ciągów)
```

#### Stałe globalne (`constants.hpp`)

Ten plik koncentruje wszystkie konfiguracje i niezmienne wartości projektu, dostępne globalnie. Używa `inline constexpr`, aby zapewnić, że stałe są bezpośrednio dostępne dla kompilatora, optymalizując wydajność.

```cpp
// constants.hpp (fragment)
namespace Constants {
    inline constexpr char ASI_VERSION[] = "1.1"; // Wersja dla systemu aktualizacji
    inline constexpr wchar_t UPDATE_API_HOST[] = L"api.github.com"; // Host API aktualizacji
    inline constexpr char DEFAULT_IMAGE[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/default_logo.png"; // Domyślny obraz
    inline constexpr int QUERY_TIMEOUT_MS = 800; // Limit czasu zapytania w ms
    inline constexpr std::chrono::seconds MAIN_LOOP_INTERVAL = std::chrono::seconds(1); // Interwał głównej pętli
}
```
Ważne szczegóły, takie jak adresy URL API, domyślne ścieżki obrazów, limity czasu sieci oraz interwały aktualizacji **Discord Rich Presence**, są scentralizowane tutaj. Użycie `std::chrono::seconds` dla interwałów poprawia czytelność i zapobiega błędom jednostek.

#### Struktury danych (`server_types.hpp`)

Ten plik definiuje ważne `structs` i `using` do organizacji zebranych i wyświetlanych danych.

```cpp
// server_types.hpp (fragment)
namespace server_types {
    using Social_Link = std::pair<std::string, std::string>; // Krotka (nazwa medium, URL/wartość)
}

struct Server_Information {
    uint16_t Players{0};           // Liczba aktualnych graczy
    uint16_t Max_Players{0};       // Maksymalna pojemność graczy
    std::string Hostname{};        // Nazwa serwera
    std::string Server_Address{};  // Np.: "192.168.1.1:7777"

    std::vector<server_types::Social_Link> Social_Links{}; // Lista linków społecznościowych serwera
};
```
`Server_Information` to główna struktura przechowująca dane serwera. Dodanie `std::vector<server_types::Social_Link> Social_Links` odzwierciedla nową zdolność do pobierania wielu linków mediów społecznościowych z API, zorganizowanych jako pary `(nazwa_medium, link)`.

#### Zabezpieczanie tajemnic (`secrets.hpp`)

Ten plik jest dedykowany ochronie wrażliwych informacji, takich jak **Discord Application ID** i adresy **AlderGrounds Integration API (na razie)**, przed łatwą inżynierią wsteczną.

```cpp
// secrets.hpp (fragment)
#include "libraries/Dralyxor/dralyxor.hpp"

namespace Secrets {
    namespace {
        inline auto& Get_Obfuscated_Discord_App_ID() {
            static auto& dc_app_id_obfuscated = DRALYXOR_KEY("DISCORD_APP_ID", "YOUR_SECRET_KEY_HERE");

            return dc_app_id_obfuscated;
        }
        // ... (inne zaszyfrowane tajemnice) ...
    }
    namespace Detail {
        inline auto& Get_Discord_App_ID() {
            return Get_Obfuscated_Discord_App_ID();
        }
        // ... (publiczne gettery do dostępu do odszyfrowanych tajemnic) ...
    }
}
```
Biblioteka [Dralyxor](https://github.com/ocalasans/dralyxor) jest używana z makrem `DRALYXOR_KEY` do szyfrowania literałów ciągów w skompilowanym binarnym pliku. `DRALYXOR_SECURE` jest następnie używane w czasie rzeczywistym do odszyfrowania tych wartości, gdy są potrzebne, dodając solidną warstwę bezpieczeństwa przeciwko statycznemu wydobywaniu kluczy.

#### Narzędzia ogólne (`utils.hpp`)

Plik dla ogólnych funkcji pomocniczych, które mogą być użyteczne w różnych modułach, zapobiegając duplikacji kodu.

```cpp
// utils.hpp (fragment)
namespace Utils {
    inline std::string Convert_Wide_To_Utf8_String(const std::wstring_view wide_string) {
        // ... (implementacja konwersji za pomocą WideCharToMultiByte) ...
    }

    inline std::wstring Convert_Utf8_To_Wide_String(const std::string_view narrow_string) {
        // ... (implementacja konwersji za pomocą MultiByteToWideChar) ...
    }
}
```
Zawiera funkcje `Convert_Wide_To_Utf8_String` i `Convert_Utf8_To_Wide_String`, kluczowe dla interoperacji z API Windows (które używają UTF-16) oraz standardowymi operacjami C++ (które generalnie korzystają z UTF-8). Te funkcje używają API Windows dla bezpiecznej i wydajnej konwersji.

### Obsługa błędów i odporność

**SA-MP Rich Presence** został zaprojektowany z myślą o odporności, włączając wiele mechanizmów do radzenia sobie z błędami sieciowymi, niepoprawnymi danymi wejściowymi i niedostępnością usług.

- **Limity czasu i ponowne próby sieciowe:**
   - **Jawne limity czasu:** Gniazda sieciowe w `samp_network.cpp` konfigurują limity czasu (`Constants::QUERY_TIMEOUT_MS`) zarówno dla wysyłania, jak i odbierania danych, zapobiegając "zawieszeniu" programu podczas oczekiwania na odpowiedź z nieaktywnego serwera.
      ```cpp
      // samp_network.cpp (konfiguracja limitu czasu)
      const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
      setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      ```
   - **Wiele prób zapytań:** `Server_Query` wykonuje `Constants::MAX_RETRY_ATTEMPTS` zapytań w przypadku niepowodzenia. Wdrożono wykładniczy czas oczekiwania (`std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)))`), aby czekać przed kolejnymi próbami, zmniejszając obciążenie i zwiększając szanse powodzenia w niestabilnych warunkach sieciowych.
- **Solidne obsługiwanie rozłączenia:**
   - **Płynne przejście stanu:** W `server_manager.cpp` status połączenia (`connection_status`) nie jest zmieniany natychmiast po pojedynczym niepowodzeniu zapytania. Tylko jeśli przez 15 sekund nie ma odpowiedzi (`now - last_successful_query > std::chrono::seconds(15)`), status jest aktualizowany na `false`. Zapobiega to "miganiu" obecności na Discordzie z powodu drobnych strat pakietów.
      ```cpp
      // server_manager.cpp (logika rozłączenia)
      else { // Jeśli zapytanie nie powiodło się
          if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
              connection_status = false;
              display_image_url = Constants::DEFAULT_IMAGE;
              display_server_data = {};
              current_display_social = {};
          }
      }
      ```
   - **Zapasowy obraz wizualny:** Po wykryciu rozłączenia obraz obecności na Discordzie wraca do `Constants::DEFAULT_IMAGE`, a dane serwera/społecznościowe są czyszczone, zapewniając wyraźny feedback dla użytkownika, że nie jest już połączony.
- **Obsługa niepoprawnych danych wejściowych:**
   - **`command_line_parser.cpp`:** Podczas konwersji argumentu portu z ciągu na liczbę całkowitą (`std::stoi`), używany jest blok `try-catch` do obsługi `std::invalid_argument` (nie jest liczbą) lub `std::out_of_range` (liczba za duża/mała). W przypadku błędu utrzymywany jest domyślny port lub parsowanie kończy się w kontrolowany sposób, zapobiegając awariom.
- **Odporność na pobieranie danych z API:**
   - **Niepowodzenia WinHTTP:** Wszystkie operacje API WinHTTP w `url_manager.cpp` są sprawdzane pod kątem `null` uchwytów i zwracania `false` na każdym etapie (otwarcie sesji, połączenie, otwarcie żądania, wysyłanie/odbieranie, odczyt danych), zapewniając wychwytywanie częściowych niepowodzeń.
   - **Kody statusu HTTP:** Po żądaniu HTTP `url_manager.cpp` sprawdza `HTTP Status Code`. Tylko kod `200 OK` jest akceptowany jako sukces, odrzucając odpowiedzi błędów serwera lub bramy.
   - **Bezpieczne parsowanie JSON:** `url_manager.cpp` otacza parsowanie JSON (`nlohmann::json::parse`) blokiem `try-catch(const nlohmann::json::exception&)`. Zapobiega to awariom z powodu zdeformowanych lub niekompletnych JSON-ów z API, zwracając puste ciągi lub domyślny obraz.
- **Bezpieczne mechanizmy aktualizacji:**
   - **`asi_update.hpp`:** Proces sprawdzania aktualizacji w `Check_For_Update` jest otoczony blokiem `try-catch(const std::exception&)`. Gwarantuje to, że nawet jeśli GitHub jest offline, sieć jest niestabilna, lub odpowiedź JSON jest nieprawidłowa, **ASI** nie ulegnie awarii, a gra będzie mogła się ładować, bezpiecznie ignorując sprawdzanie aktualizacji.
   - **Zarządzanie uchwytami WinHTTP:** Zwolnienie uchwytów `HINTERNET` w `asi_update.hpp` i `url_manager.cpp` jest starannie zaplanowane, aby wykonać się we wszystkich ścieżkach kodu (sukces i niepowodzenie), zapobiegając wyciekom zasobów.

### System przetwarzania linii poleceń

**SA-MP Rich Presence** wyciąga kluczowe informacje dla swojej operacji (IP serwera, port i nazwa gracza) bezpośrednio z linii poleceń gry Grand Theft Auto: San Andreas. Ta metoda zapewnia, że **ASI** uzyskuje najdokładniejsze i najbardziej odpowiednie dane zaraz po uruchomieniu gry lub połączeniu z serwerem.

#### Parser linii poleceń (`command_line_parser.cpp`)

Klasa `Command_Line_Parser` jest odpowiedzialna za analizę pełnego ciągu poleceń procesu, identyfikację i wyodrębnienie specyficznych parametrów używanych przez SA-MP.

- **`Parse()`**: Punkt wejścia dla analizy linii poleceń.
   ```cpp
   // command_line_parser.cpp (kluczowy fragment Parse)
   bool Command_Line_Parser::Parse(const std::wstring_view command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       server_ip = Constants::DEFAULT_SERVER_IP; // Domyślne wartości
       server_port = Constants::DEFAULT_SERVER_PORT;
   
       if (const auto ip_param = Parse_Parameter(command_line, L"-h"); !ip_param.empty())
           server_ip = Utils::Convert_Wide_To_Utf8_String(ip_param); // Wyodrębnia i konwertuje IP
   
       if (const auto port_param = Parse_Parameter(command_line, L"-p"); !port_param.empty()) {
           try {
               server_port = std::stoi(std::wstring(port_param)); // Wyodrębnia i konwertuje port (z obsługą błędów)
           }
           catch (const std::invalid_argument&) {}
           catch (const std::out_of_range&) {}
       }
   
       if (const auto name_param = Parse_Parameter(command_line, L"-n"); !name_param.empty())
           player_name = Utils::Convert_Wide_To_Utf8_String(name_param); // Wyodrębnia i konwertuje nazwę
   
       return !server_ip.empty() && server_port > 0 && !player_name.empty(); // Weryfikuje, czy podstawowe dane są obecne
   }
   ```
   Przyjmuje linię poleceń (`command_line`) jako `std::wstring_view` dla efektywności. Używa `Parse_Parameter`, aby znaleźć i wyodrębnić wartości powiązane z `-h` (host/IP), `-p` (port) i `-n` (nazwa gracza). Wyodrębnione wartości (w `std::wstring_view`) są konwertowane na `std::string` (UTF-8) za pomocą `Utils::Convert_Wide_To_Utf8_String`. Dla portu blok `try-catch` otacza `std::stoi`, aby zarządzać możliwymi błędami konwersji w bezpieczny sposób. Funkcja zwraca `true`, jeśli wszystkie kluczowe parametry (IP, prawidłowy port i nazwa gracza) zostały uzyskane.
- **`Parse_Parameter()`**: Funkcja pomocnicza do wyodrębniania pojedynczego parametru.
   ```cpp
   // command_line_parser.cpp (kluczowy fragment Parse_Parameter)
   std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring_view command_string, const std::wstring_view parameter) {
       if (const size_t position = command_string.find(parameter); position != std::wstring_view::npos) {
           size_t value_start = position + parameter.length();
           value_start = command_string.find_first_not_of(L" \t", value_start); // Pomija spacje po parametrze

           if (value_start == std::wstring_view::npos)
               return L""; // Parametr znaleziony, ale bez wartości
   
           const size_t value_end = command_string.find(L' ', value_start); // Znajduje następną spację (koniec wartości)
           
           return std::wstring(command_string.substr(value_start, value_end - value_start)); // Zwraca podciąg wartości
       }

       return L""; // Parametr nie znaleziony
   }
   ```
   Lokalizuje podciąg `parameter` (`-h`, `-p`, `-n`) w `command_string`. Oblicza początkową pozycję wartości, ignorując spacje/tabulatory. Określa końcową pozycję wartości (następna spacja) i zwraca podciąg odpowiadający wartości parametru.

### Protokół komunikacji SA-MP

**ASI** bezpośrednio komunikuje się z serwerami SA-MP, używając protokołu zapytań **UDP** do wyodrębnienia istotnych informacji w czasie rzeczywistym. Ta komunikacja jest zaimplementowana, aby być wydajną i odporną na niepowodzenia sieciowe.

#### Implementacja protokołu

Klasa `Server_Query` jest podstawą tej implementacji, zarządzając wysyłaniem pakietów i interpretacją odpowiedzi.

- **Struktura pakietu zapytania SA-MP (`'i'`)**: **ASI** buduje pakiet **UDP** o długości 11 bajtów dla zapytania informacji:
   - `BYTE 0-3`: Podpis "SAMP" (S A M P).
   - `BYTE 4-9`: Sekwencja 6 bajtów dowolnych (zazwyczaj adres IP źródła żądania, aby serwer rozpoznał klienta).
   - `BYTE 10`: Identyfikator zapytania 'i' (ASCII 105), wskazujący, że **ASI** chce ogólnych informacji o serwerze (hostname, gracze itp.).
      ```cpp
      // server_query.cpp (składanie pakietu)
      void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
          memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
          packet = 'i'; // Zapytanie informacji (Information)
      }
      ```
- **Struktura odpowiedzi serwera**: Gdy serwer SA-MP odpowiada na zapytanie 'i', wysyła pakiet **UDP** zawierający sekwencję uporządkowanych danych, które **ASI** musi sparsować:
   - **Nagłówek odpowiedzi:** Powtórzenie podpisu "SAMP" i sekwencji 6 bajtów z pakietu żądania. **ASI** po prostu pomija te `Constants::QUERY_PACKET_SIZE` bajtów początkowych.
   - **Passworded (`bool`):** Jeden bajt wskazujący, czy serwer jest chroniony hasłem. Odczytany, ale nieużywany.
   - **Players (`uint16_t`):** Liczba graczy aktualnie podłączonych do serwera.
   - **Max_Players (`uint16_t`):** Maksymalna liczba slotów graczy, które serwer obsługuje.
   - **Hostname (ciąg z prefiksem `uint32_t`):** Przyjazna nazwa serwera. Pakiet zawiera `uint32_t` wskazujący długość ciągu hostname, po którym następują bajty rzeczywistego ciągu.
   - **Inne pola:** Protokół SAMP kontynuuje z "gamemode" i "language", również z prefiksami długości. **ASI** odczytuje i pomija te pola, aby skupić się na istotnych danych `Players`, `Max_Players` i `Hostname`.

   Odczyt tych pól jest wykonywany za pomocą funkcji pomocniczych `Read_From_Span` i `Read_String_From_Span`, które zapewniają, że **ASI** nie odczytuje bajtów poza granicami bufora i poprawnie obsługuje odczyt typów danych o stałej i zmiennej długości (ciągi).
   ```cpp
   // server_query.cpp (parsowanie odpowiedzi)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       // ... (sprawdzenie rozmiaru i subspan dla danych) ...
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Odczytuje bool 'passworded'
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false; // Odczytuje 'Players'

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false; // Odczytuje 'Max_Players'

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false; // Odczytuje 'Hostname'
   
       // Pola 'Gamemode' i 'Language' są implicite pomijane
       // przez kolejne wywołanie Read_String_From_Span
       // aby przesunąć span poza ich dane w buforze.
       uint32_t length_placeholder; // Tymczasowa zmienna na długość.

       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Odczytuje długość gamemode

       if (data_span.size() < length_placeholder)
           return false; // Sprawdza granice

       data_span = data_span.subspan(length_placeholder); // Pomija dane gamemode
   
       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Odczytuje długość language

       if (data_span.size() < length_placeholder)
           return false; // Sprawdza granice

       data_span = data_span.subspan(length_placeholder); // Pomija dane language
   
       return true;
   }
   ```
   W powyższym przykładzie logika `data_span = data_span.subspan(length_placeholder);` to efektywny sposób na "pominięcie" liczby bajtów odczytanych przez ciąg, którego zawartość nie jest potrzebna do Rich Presence.

### Korzyści płynące z SA-MP Rich Presence

**SA-MP Rich Presence** znacząco poprawia doświadczenie zarówno dla graczy, jak i administratorów serwerów, oferując zauważalne korzyści:

1. **Dla graczy:**
   - **Bezproblemowa widoczność:** Automatycznie dziel się swoim statusem gry na Discordzie z przyjaciółmi, pokazując dokładnie, gdzie grasz.
   - **Bogate informacje:** Uzyskaj natychmiastowy dostęp do szczegółów serwera (nazwa, liczba graczy, IP, spersonalizowane logo) bezpośrednio na Discordzie, eliminując potrzebę sprawdzania tych informacji gdzie indziej.
   - **Bezpośredni dostęp do społeczności:** Szybko odkrywaj i uzyskuj dostęp do mediów społecznościowych serwera poprzez rotujące ikony w obecności na Discordzie, ułatwiając dołączenie do aktywnych społeczności.
   - **Szybkie połączenie z przyjaciółmi:** Zaproś lub dołącz do tego samego serwera, co Twoi znajomi, jednym kliknięciem, dzięki funkcji przycisku "Join".
   - **Zawsze aktualne doświadczenie:** System automatycznych aktualizacji zapewnia, że zawsze używasz najbardziej zoptymalizowanej i funkcjonalnej wersji **ASI**.
2. **Dla serwerów:**
   - **Naturalny marketing wirusowy:** Obecność na Discordzie Twoich graczy działa jak cyfrowy billboard, reklamując Twój serwer organicznej publiczności (przyjaciołom graczy) 24 godziny na dobę.
   - **Silna tożsamość wizualna:** Spersonalizowane logo i rotacja linków społecznościowych pozwalają Twojemu serwerowi wyróżnić się i prezentować profesjonalny, nowoczesny wizerunek w środowisku Discorda.
   - **Zwiększone zaangażowanie:** Ułatwiaj drogę nowym i obecnym graczom do łączenia się z Twoimi platformami społecznościowymi, wzmacniając społeczność i zaangażowanie poza grą.
   - **Ułatwiona rekrutacja:** Funkcja "Join" przyspiesza proces dla nowych graczy, eliminując bariery i zachęcając do eksperymentowania.
   - **Spójne dane:** Dzięki integracji z **AlderGrounds Integration API**, wyświetlanie informacji jest ujednolicone i aktualizowane centralnie, zapewniając, że marka i kontakty Twojego serwera są zawsze poprawne.

## Licencja

Ten ASI jest chroniony Licencją Apache 2.0, która zezwala na:

- ✔️ Użytek komercyjny i prywatny
- ✔️ Modyfikację kodu źródłowego
- ✔️ Dystrybucję kodu
- ✔️ Udzielanie patentów

### Warunki:

- Zachowanie informacji o prawach autorskich
- Dokumentowanie znaczących zmian
- Dołączenie kopii licencji Apache 2.0

Więcej szczegółów o licencji: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Wszelkie prawa zastrzeżone**