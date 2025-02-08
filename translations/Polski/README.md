# SA-MP Rich Presence

SA-MP Rich Presence to ASI dla SA-MP (San Andreas Multiplayer), które automatycznie aktualizuje Twój status Discord ze szczegółowymi informacjami o serwerze. ASI jest wstrzykiwane do gry, gdy łączysz się z serwerem SA-MP, wyświetlając informacje o serwerze.

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

## Indeks

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Języki](#języki)
  - [Indeks](#indeks)
  - [Czym jest ASI?](#czym-jest-asi)
  - [Funkcje](#funkcje)
    - [Discord Rich Presence](#discord-rich-presence)
  - [Wymagania](#wymagania)
  - [Instalacja](#instalacja)
  - [Szczegółowa architektura techniczna](#szczegółowa-architektura-techniczna)
    - [System główny (main.cpp)](#system-główny-maincpp)
    - [Menedżer Discord (discord\_manager.cpp)](#menedżer-discord-discord_managercpp)
    - [Menedżer serwera (server\_manager.cpp)](#menedżer-serwera-server_managercpp)
    - [System sieciowy (network\_manager.cpp)](#system-sieciowy-network_managercpp)
    - [Zapytanie do serwera (server\_query.cpp)](#zapytanie-do-serwera-server_querycpp)
  - [Integracja z SPC](#integracja-z-spc)
    - [Czym jest SPC Integration?](#czym-jest-spc-integration)
    - [Jak to działa](#jak-to-działa)
    - [Menedżer URL (url\_manager.cpp)](#menedżer-url-url_managercpp)
  - [Dla deweloperów serwerów](#dla-deweloperów-serwerów)
  - [Struktura kodu](#struktura-kodu)
    - [Stałe globalne (constants.h)](#stałe-globalne-constantsh)
    - [Struktury danych (server\_types.h)](#struktury-danych-server_typesh)
  - [Obsługa błędów](#obsługa-błędów)
  - [System przetwarzania wiersza poleceń](#system-przetwarzania-wiersza-poleceń)
    - [Parser wiersza poleceń (command\_line\_parser.cpp)](#parser-wiersza-poleceń-command_line_parsercpp)
  - [Protokół komunikacji SA-MP](#protokół-komunikacji-sa-mp)
    - [Implementacja protokołu](#implementacja-protokołu)
  - [Korzyści z SA-MP Rich Presence](#korzyści-z-sa-mp-rich-presence)
  - [Dodatkowe informacje techniczne](#dodatkowe-informacje-techniczne)

## Czym jest ASI?

ASI to biblioteka dynamiczna (.dll) przemianowana z rozszerzeniem .asi, która jest automatycznie ładowana przez loader ASI podczas uruchamiania GTA San Andreas. Wtyczki ASI pozwalają modyfikować lub dodawać funkcje do gry bez zmiany oryginalnych plików, będąc jedną z najpopularniejszych form moddingu dla GTA San Andreas i innych gier z serii GTA. Mając zainstalowany loader ASI, możesz łatwo instalować lub usuwać modyfikacje, po prostu dodając lub usuwając pliki .asi z folderu gry.

## Funkcje

### Discord Rich Presence

Discord Rich Presence to funkcja, która pozwala aplikacjom wyświetlać szczegółowe informacje o tym, co użytkownik robi, bezpośrednio w profilu Discord. W przypadku SA-MP Rich Presence wyświetlane są następujące informacje:
- Nazwa serwera (Hostname)
- Nazwa gracza
- Aktualna liczba graczy i maksymalna liczba graczy
- IP i port serwera
- Niestandardowy obraz serwera (wymaga, aby serwer miał wtyczkę [SPC Integration](https://github.com/spc-samp/spc-integration))
- Czas gry
- Status połączenia

## Wymagania

- Klient SA-MP (jeśli nie masz: [clients-samp](https://github.com/spc-samp/clients-samp))
- Aplikacja Discord Desktop
- System operacyjny Windows
- Visual C++ Runtime
- ASI Loader zainstalowany w GTA San Andreas

## Instalacja

1. Pobierz najnowszą skompilowaną wersję ASI z [releases](https://github.com/ocalasans/samp-rich-presence/releases)
2. Upewnij się, że masz zainstalowany ASI Loader w swoim GTA San Andreas
3. Skopiuj pobrany plik .asi do folderu GTA San Andreas
4. Uruchom grę z SA-MP
5. ASI zostanie automatycznie zainicjowane po wejściu na serwer

## Szczegółowa architektura techniczna

### System główny (main.cpp)

Plik main.cpp jest punktem wejścia ASI i odpowiada za:
1. Inicjalizację systemu:
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

2. Zarządzanie wątkiem aktualizacji:
   ```cpp
   DWORD WINAPI Update_Thread(LPVOID) {
       // Inicjalizuje WSA dla operacji sieciowych
       WSAData wsa_data;
       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
       
       // Przetwarza parametry wiersza poleceń
       std::string server_ip, player_name;
       int server_port;
       
       // Inicjalizuje menedżerów
       Global_Server_Manager = std::make_unique<Server_Manager>(server_ip, server_port, player_name);
       Global_Discord_Manager = std::make_unique<Discord_Manager>();
       
       // Główna pętla aktualizacji
       while (true) {
           Global_Server_Manager->Update();
           Global_Discord_Manager->Update_Presence(...);
           Sleep(Constants::PRESENCE_UPDATE_INTERVAL);
       }
   }
   ```

### Menedżer Discord (discord_manager.cpp)

Discord_Manager jest odpowiedzialny za całą integrację z Discord Rich Presence:
1. Inicjalizacja Discord RPC:
   ```cpp
   void Discord_Manager::Initialize() noexcept {
       Sleep(5000);  // Czeka na inicjalizację Discord
       
       DiscordEventHandlers discord_handlers{};
       Discord_Initialize("DISCORD_APP_ID", &discord_handlers, 1, NULL); // "DISCORD_APP_ID > Application ID"
       
       start_timestamp = time(nullptr);  // Oznacza początek sesji
   }
   ```

2. Aktualizacja obecności:
   ```cpp
   void Discord_Manager::Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept {
       DiscordRichPresence discord_presence{};
       
       // Konfiguruje podstawowe informacje
       discord_presence.state = player_name.data();
       discord_presence.details = server_info.Hostname.c_str();
       discord_presence.largeImageKey = current_image.data();
       
       // Dodaje informacje o serwerze
       discord_presence.largeImageText = server_info.Server_Address.c_str();
       discord_presence.startTimestamp = start_timestamp;
       discord_presence.partySize = server_info.Players;
       discord_presence.partyMax = server_info.Max_Players;
       
       Discord_UpdatePresence(&discord_presence);
   }
   ```

### Menedżer serwera (server_manager.cpp)

Server_Manager koordynuje wszystkie operacje związane z serwerem:
1. Zarządzanie stanem:
   ```cpp
   Server_Manager::Server_Manager(const std::string& ip, int port, const std::string& name)
       : connection_status(false)
       , server_ip(ip)
       , server_port(port)
       , player_name(name)
       , current_image_url(Constants::DEFAULT_IMAGE)
   {}
   ```

2. Aktualizacja informacji:
   ```cpp
   bool Server_Manager::Update() {
       bool query_success = server_query.Query(server_data);
       
       if (query_success) {
           connection_status = true;
           server_data.Server_Address = Get_Server_Address();
           
           // Próbuje pobrać niestandardowy obraz serwera
           std::string new_image_url = url_manager.Get_Image_URL(server_data.Server_Address);

           if (!new_image_url.empty())
               current_image_url = new_image_url;
       }
       // ...
   }
   ```

### System sieciowy (network_manager.cpp)

Network_Manager implementuje całą komunikację sieciową:
1. Inicjalizacja gniazda:
   ```cpp
   bool Network_Manager::Initialize(std::string_view ip, int port) noexcept {
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       
       // Konfiguruje timeout
       timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
       
       // Konfiguruje adres serwera
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(port);
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr);
       
       return true;
   }
   ```

### Zapytanie do serwera (server_query.cpp)

Server_Query implementuje protokół zapytań SA-MP:
1. Montaż pakietu zapytania:
   ```cpp
   bool Server_Query::Assemble_Query_Packet(char* packet) noexcept {
       memcpy(packet, QUERY_SIGNATURE, 4);  // "SAMP"
       packet[10] = 'i';  // Zapytanie o informacje

       return true;
   }
   ```

2. Przetwarzanie odpowiedzi:
   ```cpp
   bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
       // Wyodrębnia informacje takie jak:
       // - Liczba graczy
       // - Maksymalna liczba graczy
       // - Nazwa hosta
   }
   ```

## Integracja z SPC

### Czym jest SPC Integration?

[SPC Integration](https://github.com/spc-samp/spc-integration) to wtyczka opracowana dla **SA-MP** (San Andreas Multiplayer) i **open.mp** (Open Multiplayer), która działa jako most między serwerami a ekosystemem **SPC**. Wtyczka zbiera kluczowe informacje o serwerze, w tym:
- IP i port
- URL strony serwera
- URL niestandardowego obrazu
- Informacje o konfiguracji

Te informacje są wysyłane i bezpiecznie przechowywane w magazynie danych **SPC (SA-MP Programming Community)**, umożliwiając integrację z różnymi aplikacjami **SPC**, w tym Rich Presence.

### Jak to działa

1. Serwer używa wtyczki [SPC Integration](https://github.com/spc-samp/spc-integration) do zarejestrowania swojego niestandardowego obrazu
2. Obraz jest przechowywany w magazynie danych SPC w pliku JSON serwera
3. Gdy gracz łączy się z serwerem:
    - URL_Manager ASI próbuje pobrać plik JSON serwera (format: `ip-port.json`)
    - Jeśli zostanie znaleziony, wyodrębnia URL obrazu z parametru `spc_integration_image`
    - Obraz jest następnie wyświetlany w Discord Rich Presence gracza

### Menedżer URL (url_manager.cpp)

URL_Manager jest odpowiedzialny za całą komunikację z magazynem danych SPC:
1. Pobieranie obrazu serwera:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       std::string formatted_address = server_address;
       // Konwertuje ":" na "-" w adresie
       size_t colon_pos = formatted_address.find(':');

       if (colon_pos != std::string::npos)
           formatted_address.replace(colon_pos, 1, "-");
       
       // Pobiera JSON serwera
       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;
       
       return image_url;
   }
   ```

2. Przetwarzanie JSON:
   ```cpp
   std::string URL_Manager::Parse_JSON(const std::string& json_content) {
       const std::string key = "\"spc_integration_image\":";
       size_t key_pos = json_content.find(key);
       
       // Wyodrębnia URL obrazu z JSON
       // ...
       
       return image_url;
   }
   ```

## Dla deweloperów serwerów

Jeśli jesteś deweloperem serwera SA-MP, zdecydowanie zalecamy zainstalowanie wtyczki [SPC Integration](https://github.com/spc-samp/spc-integration) z następujących powodów:
1. Widoczność:
    - Niestandardowy obraz twojego serwera będzie wyświetlany w Discord wszystkich graczy korzystających z tego ASI
    - Zwiększa rozpoznawalność marki twojego serwera
    - Zapewnia bardziej profesjonalną prezentację

2. Korzyści:
    - Większe zaangażowanie graczy
    - Wizualne wyróżnienie w Discord
    - Automatyczna integracja z Rich Presence

3. Jak wdrożyć:
   - Przeczytaj repozytorium wtyczki [SPC Integration](https://github.com/spc-samp/spc-integration), aby dowiedzieć się, jak wdrożyć

## Struktura kodu

Projekt jest zorganizowany w kilka komponentów:
```
src/
├── discord/               # Biblioteka Discord RPC
├── command_line_parser.*  # Przetwarzanie argumentów
├── constants.h            # Stałe globalne
├── discord_manager.*      # Integracja z Discord
├── main.cpp               # Punkt wejścia
├── network_manager.*      # Operacje sieciowe
├── server_manager.*       # Zarządzanie serwerem
├── server_query.*         # Protokół SA-MP
├── server_types.h         # Struktury danych
└── url_manager.*          # Integracja z SPC
```

### Stałe globalne (constants.h)

Plik definiuje kilka ważnych stałych:
```cpp
namespace Constants {
    // Wartości domyślne
    inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
    inline constexpr int DEFAULT_SERVER_PORT = 7777;
    
    // Ustawienia sieciowe
    inline constexpr int QUERY_TIMEOUT = 1000;
    inline constexpr int QUERY_PACKET_SIZE = 11;
    inline constexpr int QUERY_BUFFER_SIZE = 512;
    
    // Ustawienia ponownych prób
    inline constexpr int MAX_RETRY_ATTEMPTS = 3;
    
    // Interwały
    inline constexpr int PRESENCE_UPDATE_INTERVAL = 5000;
}
```

### Struktury danych (server_types.h)

Definiuje główne struktury:
```cpp
struct Server_Information {
    uint16_t Players{ 0 };           // Gracze online
    uint16_t Max_Players{ 0 };       // Maksymalna liczba graczy
    std::string Hostname;            // Nazwa serwera
    std::string Server_Image;        // URL obrazu
    std::string Server_Address;      // Adres serwera
};
```

## Obsługa błędów

System implementuje solidny system obsługi błędów:
1. Timeout sieci:
   ```cpp
   timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
   setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
   ```

2. System ponownych prób:
   ```cpp
   bool Server_Query::Try_Query(Server_Information& server_data, int retry_count) noexcept {
       for (int attempt = 0; attempt <= retry_count; attempt++) {
           if (network_manager.Send_Query(...))
               return true;
           
           // Czeka przed ponowną próbą
           std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
       }

       return false;
   }
   ```

3. Fallback do domyślnego obrazu:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       // Jeśli coś pójdzie nie tak, zwraca domyślny obraz
       if (!session_handle)
           return Constants::DEFAULT_IMAGE;

       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;

       return image_url;
   }
   ```

4. Monitorowanie stanu połączenia:
   ```cpp
   bool Server_Manager::Update() {
       auto current_time = std::chrono::steady_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_successful_query);
       
       // Jeśli nie ma odpowiedzi przez ponad 15 sekund, uznaje się za rozłączone
       if (duration.count() > 15) {
           connection_status = false;
           current_image_url = Constants::DEFAULT_IMAGE;
       }
   }
   ```

## System przetwarzania wiersza poleceń

ASI implementuje elastyczny system do przetwarzania argumentów wiersza poleceń:

### Parser wiersza poleceń (command_line_parser.cpp)

1. Główne przetwarzanie:
   ```cpp
   bool Command_Line_Parser::Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       // Ustawia wartości domyślne
       server_ip = Constants::DEFAULT_SERVER_IP;
       server_port = Constants::DEFAULT_SERVER_PORT;

       // Przetwarza każdy parametr
       std::wstring ip_parameter = Parse_Parameter(command_string, L"-h");
       std::wstring port_parameter = Parse_Parameter(command_string, L"-p");
       std::wstring name_parameter = Parse_Parameter(command_string, L"-n");

       // Konwertuje i waliduje wartości
       if (!ip_parameter.empty())
           server_ip = Convert_To_String(ip_parameter);

       if (!port_parameter.empty())
           server_port = std::stoi(port_parameter);

       if (!name_parameter.empty())
           player_name = Convert_To_String(name_parameter);

       // Sprawdza, czy wszystkie wymagane parametry są obecne
       return !server_ip.empty() && server_port > 0 && !player_name.empty();
   }
   ```

2. Ekstrakcja parametrów:
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

## Protokół komunikacji SA-MP

ASI implementuje protokół zapytań SA-MP do uzyskiwania informacji o serwerze:
1. Struktura pakietu zapytania:
    - 4 bajty: Sygnatura "SAMP"
    - 7 bajtów: Dodatkowe dane
    - Ostatni bajt: 'i' (wskazuje zapytanie o informacje)

2. Struktura odpowiedzi:
    - Nagłówek pakietu
    - Players (uint16_t)
    - Max_Players (uint16_t)
    - Hostname (string)

### Implementacja protokołu

```cpp
bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
    char* current_pos = response_buffer + Constants::QUERY_PACKET_SIZE;
    const char* buffer_end = response_buffer + received_bytes;

    // Pomija "password"
    current_pos += sizeof(bool);
    
    // Odczytuje stałe dane
    memcpy(&server_data.Players, current_pos, sizeof(server_data.Players));
    current_pos += sizeof(server_data.Players);
    
    memcpy(&server_data.Max_Players, current_pos, sizeof(server_data.Max_Players));
    current_pos += sizeof(server_data.Max_Players);

    // Odczytuje Hostname i pomija "gamemode" i "language"
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
    
    // Pomija "gamemode" i "language"
    // ...

    return true;
}
```

## Korzyści z SA-MP Rich Presence

1. Dla graczy:
    - Szybki podgląd aktualnego serwera
    - Szczegółowe informacje o serwerze
    - Doskonała integracja z Discord
    - Bardziej społeczne doświadczenie z gry

2. Dla serwerów:
    - Większa widoczność przez Discord
    - Marketing organiczny przez graczy
    - Spersonalizowana tożsamość wizualna (z wtyczką [SPC Integration](https://github.com/spc-samp/spc-integration))
    - Statystyki w czasie rzeczywistym

## Dodatkowe informacje techniczne

1. Bezpieczeństwo wątków:
    - ASI używa pojedynczego wątku do aktualizacji
    - Menedżerowie są z założenia bezpieczni dla wątków
    - Zasoby są odpowiednio zsynchronizowane

2. Wykorzystanie pamięci:
    - Minimalna alokacja pamięci
    - Wstępnie zaalokowane bufory dla zapytań
    - Automatyczne zarządzanie zasobami (RAII)

3. Wydajność:
    - Zoptymalizowane zapytania z timeoutem
    - Inteligentny system ponownych prób
    - Konfigurowalny interwał aktualizacji

4. Kompatybilność:
    - Wsparcie dla Unicode
    - Kompatybilny z nowoczesnymi systemami Windows
    - Wsparcie dla IPv4