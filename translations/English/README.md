# SA-MP Rich Presence

The **SA-MP Rich Presence** is an **ASI** for **SA-MP (San Andreas Multiplayer)** that automatically updates your Discord status with detailed server information. The **ASI** is injected into the game when you connect to an SA-MP server, displaying server information.

## Languages

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Table of Contents

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Languages](#languages)
  - [Table of Contents](#table-of-contents)
  - [Features](#features)
    - [Discord Rich Presence](#discord-rich-presence)
    - [Automatic Update System](#automatic-update-system)
  - [Requirements](#requirements)
  - [Installation](#installation)
  - [Integration with the SPC Integration API](#integration-with-the-spc-integration-api)
    - [How Information is Obtained and Used:](#how-information-is-obtained-and-used)
  - [For Server Developers](#for-server-developers)
    - [How to Implement SPC Integration on Your Server:](#how-to-implement-spc-integration-on-your-server)
  - [Detailed Technical Architecture](#detailed-technical-architecture)
      - [Main System (`main.cpp`)](#main-system-maincpp)
      - [Update System (`asi_update.hpp`)](#update-system-asi_updatehpp)
      - [Discord Manager (`discord_manager.cpp`)](#discord-manager-discord_managercpp)
      - [Server Manager (`server_manager.cpp`)](#server-manager-server_managercpp)
      - [Network System (`samp_network.cpp`)](#network-system-samp_networkcpp)
      - [Server Query (`server_query.cpp`)](#server-query-server_querycpp)
      - [URL Manager (`url_manager.cpp`)](#url-manager-url_managercpp)
    - [Code Structure](#code-structure)
      - [Global Constants (`constants.hpp`)](#global-constants-constantshpp)
      - [Data Structures (`server_types.hpp`)](#data-structures-server_typeshpp)
      - [Secrets Obfuscation (`secrets.hpp`)](#secrets-obfuscation-secretshpp)
      - [General Utilities (`utils.hpp`)](#general-utilities-utilshpp)
    - [Error Handling and Resilience](#error-handling-and-resilience)
    - [Command Line Processing System](#command-line-processing-system)
      - [Command Line Parser (`command_line_parser.cpp`)](#command-line-parser-command_line_parsercpp)
    - [SA-MP Communication Protocol](#sa-mp-communication-protocol)
      - [Protocol Implementation](#protocol-implementation)
    - [Benefits of SA-MP Rich Presence](#benefits-of-sa-mp-rich-presence)
  - [License](#license)
    - [Conditions:](#conditions)

## Features

### Discord Rich Presence

The **Discord Rich Presence** is a feature that allows applications to display detailed information about what the user is doing directly on their Discord profile. In the case of **SA-MP Rich Presence**, the following information is displayed:

- **Server Name (Hostname):** The main name of the server.
- **Player Name:** Your current in-game nickname.
- **Player Count:** Current number of online players and the maximum allowed.
- **Server Address:** Server IP and port for easy identification.
- **Custom Server Image:** A unique server logo, if available.
- **Rotating Social Icon:** Small icons representing links to the server’s social media (website, Discord, YouTube, Instagram, Facebook, TikTok), rotating automatically.
- **Play Time:** How long you have been connected to the current server.
- **Connection Status:** Indicates whether you are online on a server or in an "Idle" state.
- **"Join" Button:** Allows your friends to join the same server you are playing on directly.

### Automatic Update System

The **ASI** integrates an update verification system. Upon starting the game, it checks for new versions available in the project’s official GitHub repository. If an update is detected, a friendly notification is displayed to the user, offering options to:

1. Open the browser directly on the releases page for download.
2. Continue without updating, with the option to disable the **ASI** for the current session.

This feature ensures that users always have access to the latest improvements, bug fixes, and new functionalities, promoting an updated and seamless experience.

## Requirements

- SA-MP Client (if you don’t have it: [clients-samp](https://github.com/spc-samp/clients-samp)).
- Discord Desktop Application.
- Windows Operating System.
- Visual C++ Runtime.
- An [ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) installed in your Grand Theft Auto: San Andreas.

## Installation

1. Download the latest compiled version of the **ASI** directly from the [releases](https://github.com/ocalasans/samp-rich-presence/releases) section on GitHub.
2. After downloading, locate the `.asi` file.
3. Copy the downloaded `.asi` file to the root folder of your GTA San Andreas (where the `gta_sa.exe` file is located).
4. Start the game through the SA-MP client.
5. The **ASI** will be loaded and initialized automatically when you connect to a server, updating your Discord status.

## Integration with the SPC Integration API

The **SA-MP Rich Presence** significantly enhances the display of information on Discord through its integration with the **SPC Integration API**. Instead of relying solely on basic query data, the **ASI** now interacts directly with this API to obtain visual and social information about the server. To learn more about **SPC Integration** itself, visit the official repository: [spc-samp/spc-integration](https://github.com/spc-samp/spc-integration).

### How Information is Obtained and Used:

1. **Address Formatting:** When the player connects to a server (IP and Port), the **ASI** formats this address (`IP:PORT`) into a user-friendly pattern (`IP-PORT`), preparing it for the API request.
2. **API Request:** The **ASI** sends a `GET` request to the **SPC Integration API** endpoint, including the formatted IP and port. Example of how the request URL is built internally:
   ```cpp
   // Trecho adaptado de url_manager.cpp
   auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
   std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
   path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   const std::string json_data = Request_API_Data(path);
   ```
3. **JSON Response Processing:** The API returns a response in JSON format. The **ASI** uses the [nlohmann/json](https://github.com/nlohmann/json) library to parse this response and extract relevant data.
   ```json
   // Example of SPC Integration API Response Structure
   {
       "success": true,
       "data": {
           "public": {
               "logo": "https://url.of.your.logo/server_logo.png",
               "website": "https://your-site.com",
               "discord": "https://discord.gg/yourserver",
               "youtube": "https://youtube.com/yourchannel"
               // ...other social networks
           }
       }
   }
   ```
4. **Data Extraction:**
   - **Server Logo:** The server image URL (the `logo` within the `public` section) is extracted and used as the main image (large image) in the **Discord Rich Presence**. This ensures an authentic and customizable visual identity for each server.
   - **Social Links:** A predefined list of social networks (website, Discord, YouTube, Instagram, Facebook, TikTok) is checked in the JSON response. For each found and valid social network, the network name and its respective link are stored.
5. **Display on Discord:** The `Server_Manager` uses the extracted list of social links to implement dynamic rotation. Every 30 seconds, a different icon from one of the server’s social networks is displayed as the "small image" in the Discord presence, along with the platform’s link or name, encouraging exploration of the server’s communities.

## For Server Developers

Integrating your server with [SPC Integration](https://github.com/spc-samp/spc-integration) brings a range of direct and indirect benefits that boost your SA-MP community’s visibility and engagement. If you are a server developer, consider the strategic advantages:

1. **Enhance Your Brand:**
   - **Premium Visibility:** Your server’s custom logo will not just be text but a vibrant and eye-catching image displayed prominently on the Discord profiles of all players using this **ASI**. This is an organic and constant form of branding.
   - **Professional Presence:** By having your logo and social media well-represented, your server projects a more established and trustworthy image, attracting more interest and potential new players.
2. **Community Expansion:**
   - **Multiply Access Channels:** With the rotation of social icons, you can promote various platforms of your community—from the official website and server Discord to your YouTube, Instagram, Facebook, or TikTok pages. Each icon and link in the **Discord Rich Presence** directs interested users straight to where your community is active.
   - **Instant Connectivity:** The "Join" functionality via Discord allows friends of your players to join your SA-MP server with just one click, reducing barriers to entry and encouraging new members.
3. **Simplified Content Updates:**
   - By using [SPC Integration](https://github.com/spc-samp/spc-integration), any updates to your server’s logo or configured social media links in the [SPC Integration](https://github.com/spc-samp/spc-integration) plugin **(on the server side)** will automatically reflect for players using the **ASI**, without requiring them to update the **ASI**. This ensures that the information is always accurate and up-to-date.

### How to Implement SPC Integration on Your Server:

1. **SPC Integration Plugin:** Your server will need to have the [SPC Integration](https://github.com/spc-samp/spc-integration) plugin installed and properly configured. This plugin is the bridge that sends your server’s information to an **SPC** data list, which is subsequently used by the **SPC Integration API** to provide public information.
2. **Configuration:** Follow the instructions in the [SPC Integration](https://github.com/spc-samp/spc-integration) plugin repository to configure:
   - The `logo` parameter with the URL of your server’s logo.
   - The social media parameters (`discord`, `website`, `youtube`, etc.) with valid links to your platforms.
3. **Automatic Updates:** Once the information is configured in the server plugin, the **SA-MP Rich Presence** will detect and display it automatically. No action is required from the player beyond the initial installation of the **ASI**.

By integrating your server with [SPC Integration](https://github.com/spc-samp/spc-integration), you not only enhance your players’ experience but also open doors to significant growth and engagement for your community.

## Detailed Technical Architecture

The **SA-MP Rich Presence** has a well-defined modular architecture, with components focused on specific tasks. The codebase aligns with modern C++ standards (C++17 and C++20), using `std::string_view`, `std::span`, and move semantics to ensure high performance, safety, and efficiency.

#### Main System (`main.cpp`)

The heart of the **ASI** lies in `main.cpp`, which manages the application’s lifecycle, from its initialization as a DLL to the continuous update loop and graceful shutdown.

- **`DllMain`**: The entry point of the **ASI** when loaded by the operating system.
   ```cpp
   // DllMain (simplified for structure focus)
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
   In this function, when attached to the game process (`DLL_PROCESS_ATTACH`), it disables unnecessary library calls (`DisableThreadLibraryCalls`) and **creates a new thread (`Main_Update_Thread`)** to run the **ASI** logic asynchronously, ensuring the game is not blocked. During shutdown (`DLL_PROCESS_DETACH`), `Shutdown_Managers()` is invoked to release resources.
- **`Main_Update_Thread`**: The soul of the **ASI**, running in its own thread.
   ```cpp
   // Main_Update_Thread (key excerpt)
   DWORD WINAPI Main_Update_Thread(LPVOID) {
       // 1. Update Check
       if (Asi_Update::Check_For_Update())
           return 0; // If user chose to disable, terminate.
   
       // 2. Network Initialization (Winsock)
       WSAData wsa_data;

       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
   
       // 3. Initialize Server and Discord Managers
       Initialize_Managers();
   
       // 4. Main Update Loop
       while (is_running && v_server_manager && v_discord_manager) {
           v_server_manager->Update(); // Queries server, SPC API, etc.
           v_discord_manager->Update_Presence( // Updates Discord status
               v_server_manager->Get_Server_Info(),
               v_server_manager->Get_Display_Social_Link(),
               v_server_manager->Get_Player_Name(),
               v_server_manager->Get_Current_Image_URL(),
               v_server_manager->Is_Connected());
   
           Discord_RunCallbacks(); // Processes Discord RPC events
           std::this_thread::sleep_for(Constants::MAIN_LOOP_INTERVAL);
       }
   
       // 5. Shutdown (if managers exist)
       if (v_discord_manager)
           v_discord_manager->Shutdown();

       WSACleanup(); // Frees Winsock

       return 0;
   }
   ```
   This function prioritizes checking for updates. Next, it initializes the Winsock network stack and instances of the server and Discord managers. A persistent `while` loop (controlled by `std::atomic<bool> is_running` for safe shutdown) coordinates calls to `Server_Manager::Update()` (data collection) and `Discord_Manager::Update_Presence()` (sending to Discord). `Discord_RunCallbacks()` ensures Discord processes Rich Presence events. The loop is paused periodically using `std::this_thread::sleep_for` to optimize resource usage.

#### Update System (`asi_update.hpp`)

This vital module adds intelligence to the **ASI**, ensuring users stay up-to-date.

- **`Check_For_Update()`**: The main update-checking function.
   ```cpp
   // asi_update.hpp (key excerpt of Check_For_Update)
   inline bool Check_For_Update() {
       HINTERNET h_session = nullptr, h_connect = nullptr, h_request = nullptr;
       bool update_found_and_handled = false;
   
       try {
           h_session = WinHttpOpen(L"SA-MP Rich Presence Update/1.0", ...);
           // ... (GET request to Constants::UPDATE_API_PATH on GitHub API) ...
           std::string response_body;
           // ... (reading HTTP response) ...
           nlohmann::json release_info = nlohmann::json::parse(response_body);
   
           std::string latest_tag = release_info["tag_name"].get<std::string>();
           // ... (normalize and compare versions using sscanf_s/sscanf) ...
   
           if (latest_major > current_major || (latest_major == current_major && latest_minor > current_minor)) {
               update_found_and_handled = true;
               std::wstringstream message_stream;
               // ... (prepare MessageBox message) ...
               int msgbox_result = MessageBoxW(NULL, message_stream.str().c_str(), L"SA-MP Rich Presence - Update Available", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
               
               if (msgbox_result == IDYES)
                   ShellExecuteW(NULL, L"open", Constants::UPDATE_RELEASES_URL, NULL, NULL, SW_SHOWNORMAL);
           }
       }
       catch (const std::exception&) { /* Error handling */ }
   
       // ... (close WinHttp handles) ...
       return update_found_and_handled;
   }
   ```
   Using the **WinHTTP API** for network requests, `Check_For_Update` performs a `GET` request to the `/releases/latest` endpoint of the project’s GitHub API. The JSON response is parsed with the `nlohmann/json` library. The latest version (`tag_name`) is compared numerically with the compiled **ASI** version. If a new version is detected, a dialog box (`MessageBoxW`) is displayed, asking the user if they wish to visit the downloads page via `ShellExecuteW`. The entire process is encapsulated in a `try-catch` to ensure network or parsing failures do not compromise game startup.

#### Discord Manager (`discord_manager.cpp`)

The `Discord_Manager` class abstracts interactions with the **Discord RPC** library, managing connection initialization and sending data to the user’s presence status.

- **`Initialize()`**: Sets up communication with Discord.
   ```cpp
   // discord_manager.cpp (key excerpt of Initialize)
   void Discord_Manager::Initialize() noexcept {
       DiscordEventHandlers handlers;
       memset(&handlers, 0, sizeof(handlers)); // Ensures initialization
       
       // App ID is deobfuscated here
       auto app_id_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_Discord_App_ID());
       Discord_Initialize(app_id_accessor.Get(), &handlers, 1, nullptr);
   
       start_timestamp_ = time(nullptr); // Records session start
   }
   ```
   The call to `Discord_Initialize` is crucial, using the `DISCORD_APP_ID` obtained securely via string obfuscation in `secrets.hpp`. The `start_timestamp_` is set here to calculate playtime in the Discord presence.
- **`Update_Presence()`**: The vital function that updates the Discord Rich Presence.
   ```cpp
   // discord_manager.cpp (key excerpt of Update_Presence)
   void Discord_Manager::Update_Presence(const Server_Information& server_info, const server_types::Social_Link& social_link, const std::string_view player_name, const std::string_view current_image, const bool is_connected) noexcept {
       DiscordRichPresence discord_presence;
       memset(&discord_presence, 0, sizeof(discord_presence));
   
       discord_presence.startTimestamp = start_timestamp_;
       discord_presence.largeImageKey = current_image.data(); // Server logo
   
       if (is_connected) {
           discord_presence.details = server_info.Hostname.c_str();
           discord_presence.state = player_name.data();
           discord_presence.largeImageText = server_info.Server_Address.c_str(); // IP:Port
           discord_presence.partySize = server_info.Players;
           discord_presence.partyMax = server_info.Max_Players;
           discord_presence.joinSecret = server_info.Server_Address.c_str(); // Enables "Join" button
   
           // Manages rotating social icon
           if (!social_link.first.empty()) {
               current_small_image_key_ = Constants::SOCIAL_ICON_BASE_URL;
               current_small_image_key_ += social_link.first; // Ex: "discord.png"
               current_small_image_key_ += ".png";
               discord_presence.smallImageKey = current_small_image_key_.c_str();
               discord_presence.smallImageText = social_link.second.c_str(); // Hover text (link/name)
           }
       }
       else {
           discord_presence.details = "SA-MP"; // "Idle" state
           discord_presence.state = "Idle";
           discord_presence.largeImageText = "San Andreas Multiplayer";
           // smallImageKey and smallImageText remain empty for idle state
       }
   
       Discord_UpdatePresence(&discord_presence);
   }
   ```
   Fills the `DiscordRichPresence` structure based on the connection state. If `is_connected` is true, the hostname, player count, server IP, and player name are displayed. The `largeImageKey` sets the main server image. Notably, `joinSecret` is set to allow friends to connect directly, and the `smallImageKey` (dynamically built based on the provided `social_link`) displays the rotating social icons. In the "Idle" state, the presence is simplified to reflect inactivity. Finally, `Discord_UpdatePresence` sends the data to Discord.

#### Server Manager (`server_manager.cpp`)

The `Server_Manager` is the orchestrator of data, managing connection state, querying the server and the **SPC Integration API**, and deciding which information to display and when.

- **`Update()`**: The main lifecycle for data collection.
   ```cpp
   // server_manager.cpp (key excerpt of Update)
   void Server_Manager::Update() {
       const auto now = std::chrono::steady_clock::now();
   
       if (server_query.Query(live_server_data)) { // Attempts to query SA-MP server
           if (!connection_status) { // If just connected/reconnected
               connection_status = true;
               Fetch_API_Data(); // Pulls logo and socials from API
           }
           
           last_successful_query = now;
   
           // Updates data to be displayed on Discord
           display_server_data.Hostname = live_server_data.Hostname;
           display_server_data.Players = live_server_data.Players;
           display_server_data.Max_Players = live_server_data.Max_Players;
           display_server_data.Server_Address = server_ip + ":" + std::to_string(server_port);
   
           if (now - last_api_update > Constants::IMAGE_UPDATE_INTERVAL)
               Fetch_API_Data(); // Re-queries API after set time
   
           if (now - last_social_rotation > Constants::SOCIAL_UPDATE_INTERVAL)
               Rotate_Social_Link(); // Rotates social icon
       }
       else { // If query failed
           if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
               connection_status = false; // Disconnected after timeout
               display_image_url = Constants::DEFAULT_IMAGE;
               display_server_data = {}; // Clears data
               current_display_social = {}; // Clears social
           }
       }
   }
   ```
   The `Update` function attempts to query the server. If successful, it updates `live_server_data` and `display_server_data`. Conditionally, it calls `Fetch_API_Data()` to update the image and social links (if it’s a new connection or `IMAGE_UPDATE_INTERVAL` has passed) and `Rotate_Social_Link()` to cycle social icons (`SOCIAL_UPDATE_INTERVAL`). If server queries consistently fail for more than 15 seconds, the connection status is considered lost, resetting displayed information.
- **`Fetch_API_Data()`**: Responsible for obtaining visual and social data.
   ```cpp
   // server_manager.cpp (key excerpt of Fetch_API_Data)
   void Server_Manager::Fetch_API_Data() {
       display_image_url = url_manager.Get_Image_URL_And_Populate_Socials(server_ip, server_port, live_server_data);
       last_api_update = std::chrono::steady_clock::now();
       current_social_index_ = 0; // Resets index after new API fetch
       Rotate_Social_Link(); // Ensures a social icon is displayed immediately
   }
   ```
   This function coordinates with `URL_Manager` to pull the logo and social links from the API, updating `display_image_url` and populating `Social_Links` within `live_server_data`. It resets the social rotation index and calls `Rotate_Social_Link()` to ensure the first icon is ready for display.
- **`Rotate_Social_Link()`**: Logic for cycling social icons.
   ```cpp
   // server_manager.cpp (key excerpt of Rotate_Social_Link)
   void Server_Manager::Rotate_Social_Link() {
       if (!live_server_data.Social_Links.empty()) {
           if (current_social_index_ >= live_server_data.Social_Links.size())
               current_social_index_ = 0; // Restarts cycle
   
           current_display_social = live_server_data.Social_Links[current_social_index_];
           current_social_index_ = (current_social_index_ + 1) % live_server_data.Social_Links.size();
       }
       else
           current_display_social = {}; // Clears if no socials
       
       last_social_rotation = std::chrono::steady_clock::now();
   }
   ```
   This simple function selects the next `Social_Link` in the `live_server_data.Social_Links` list cyclically and stores it in `current_display_social` for the `Discord_Manager` to use.

#### Network System (`samp_network.cpp`)

The `Samp_Network` class is the low-level implementation of **UDP** communication, responsible for opening and managing the socket for SA-MP queries. It now offers constructors and move operators for better resource management.

- **`Initialize()`**: Sets up the socket for **UDP** communication.
   ```cpp
   // samp_network.cpp (key excerpt of Initialize)
   bool Samp_Network::Initialize(const std::string_view ip, const int port) noexcept {
       if (network_socket != INVALID_SOCKET)
           closesocket(network_socket); // Closes existing socket
   
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
   Initializes the socket, sets timeouts for send and receive operations, and configures the address structure (`sockaddr_in`) with the target server’s IP and port, using `inet_pton` for IP conversion.
- **`Send_Query()`**: Sends a query packet and receives the response.
   ```cpp
   // samp_network.cpp (key excerpt of Send_Query)
   bool Samp_Network::Send_Query(const std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept {
       // Sends UDP packet
       if (sendto(network_socket, query_packet.data(), static_cast<int>(query_packet.size()), 0, reinterpret_cast<const sockaddr*>(&server_address), sizeof(server_address)) < 0)
           return false;
   
       sockaddr_in from_address;
       int address_length = sizeof(from_address);
       // Receives response
       received_bytes = recvfrom(network_socket, response_buffer.data(), static_cast<int>(response_buffer.size()), 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);
   
       return received_bytes > Constants::QUERY_PACKET_SIZE;
   }
   ```
   This method sends the `query_packet` (passed as `std::span` for buffer safety) to the server. It then attempts to receive a response into `response_buffer`. The return indicates whether the operation was successful and if a number of bytes greater than the query packet size was received.

#### Server Query (`server_query.cpp`)

The `Server_Query` class is dedicated to implementing the SA-MP query protocol (`'i'`), extracting basic server information (players, hostname) from **UDP** responses.

- **`Query()`**: Manages query attempts.
   ```cpp
   // server_query.cpp (key excerpt of Query)
   bool Server_Query::Query(Server_Information& server_data) noexcept {
       for (int attempt = 0; attempt < Constants::MAX_RETRY_ATTEMPTS; ++attempt) {
           if (Try_Query(server_data))
               return true; // Query successful
   
           if (attempt < Constants::MAX_RETRY_ATTEMPTS - 1)
               // Small pause before retrying to avoid flooding
               std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)));
       }

       return false; // All attempts failed
   }
   ```
   Implements a retry strategy with `MAX_RETRY_ATTEMPTS` and an increasing time *back-off* to ensure robust queries and avoid network saturation. Calls `Try_Query` on each attempt.
- **`Assemble_Query_Packet()`**: Builds the SA-MP query packet.
   ```cpp
   // server_query.cpp (key excerpt of Assemble_Query_Packet)
   void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
       memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
       packet = 'i'; // Code for information query
   }
   ```
   The standard packet for the SA-MP information query (`'i'`) is constructed, including the "SAMP" signature and the 'i' identifier byte.
- **`Parse_Response()`**: Unpacks the server’s binary response.
   ```cpp
   // server_query.cpp (key excerpt of Parse_Response)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       if (response.size() <= Constants::QUERY_PACKET_SIZE) 
           return false;
   
       auto data_span = response.subspan(Constants::QUERY_PACKET_SIZE); // Skips header
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Ignored but read
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false;

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false;

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false;
   
       // Note: Gamemode and Language are automatically skipped by Read_String_From_Span if the packet contains more data.
       // If other fields are needed, create a string and call: Read_String_From_Span(data_span, string_variable);
       return true;
   }
   ```
   This method safely reads data from the `response_buffer` (using `std::span` and helper functions `Read_From_Span` and `Read_String_From_Span`). It extracts the player count, maximum players, and server hostname, populating the `Server_Information` structure. Unused fields (like whether the server is password-protected) are read but ignored, and others like "gamemode" and "language" are skipped if the response contains more data than the **ASI** needs at the moment.
- **Helper Read Functions:**
   ```cpp
   // server_query.hpp (snippets of helper read functions)
   template<typename T>
   static bool Read_From_Span(std::span<const char>& s, T& value) noexcept;
   
   static bool Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept;
   ```
   `Read_From_Span` handles reading fixed-size types (integers, booleans) from the `std::span` and advances the span. `Read_String_From_Span` reads the length of a string (as `uint32_t`) and then the string itself, also advancing the span. This ensures safe parsing of bytes and prevents out-of-bounds reads.

#### URL Manager (`url_manager.cpp`)

The `URL_Manager` class manages HTTPS communications with the **SPC Integration API**, a central element for the new visual and social functionalities of the **Discord Rich Presence**.

- **`Get_Image_URL_And_Populate_Socials()`**: The high-level method for fetching API information.
   ```cpp
   // url_manager.cpp (key excerpt of Get_Image_URL_And_Populate_Socials)
   std::string URL_Manager::Get_Image_URL_And_Populate_Socials(const std::string& ip, const int port, Server_Information& server_info) {
       if (!session_handle)
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);
   
       auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
       std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
       path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   
       const std::string json_data = Request_API_Data(path); // HTTP request to API
   
       if (json_data.empty())
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE); // Request error
   
       return Parse_API_Response(json_data, server_info); // Parses and fills server_info
   }
   ```
   Receives IP and port, builds the API URL including them as parameters. Calls `Request_API_Data` to fetch JSON data. On success, `Parse_API_Response` is called to extract the image URL (logo) and populate the social links in `server_info`.
- **`Request_API_Data()`**: Performs the HTTPS request to the API.
   ```cpp
   // url_manager.cpp (key excerpt of Request_API_Data)
   std::string URL_Manager::Request_API_Data(const std::wstring& path) {
       auto api_host_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Host());
       const std::wstring wide_host = Utils::Convert_Utf8_To_Wide_String(api_host_accessor.Get());
       HINTERNET connect_handle = WinHttpConnect(session_handle, wide_host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
   
       if (!connect_handle) return "";
   
       HINTERNET request_handle = WinHttpOpenRequest(connect_handle, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
   
       if (!request_handle) return (WinHttpCloseHandle(connect_handle), "");
   
       // Send request, receive response, verify status 200, read data in loop
       // ... (details of WinHttpSendRequest, WinHttpReceiveResponse, WinHttpQueryHeaders, WinHttpReadData calls) ...
       
       WinHttpCloseHandle(request_handle); WinHttpCloseHandle(connect_handle);
       return response_body; // Returns JSON as string
   }
   ```
   Connects to the API host (obtained obfuscated), opens and sends a `GET` request with the path (`path`). Handles the HTTP response, verifies the status code (200 OK for success), and reads the full response body (expected to be JSON). All WinHTTP handles are freed on success or failure.
- **`Parse_API_Response()`**: Processes the JSON string to extract data.
   ```cpp
   // url_manager.cpp (key excerpt of Parse_API_Response)
   std::string URL_Manager::Parse_API_Response(const std::string& json_content, Server_Information& server_info) {
       server_info.Social_Links.clear(); // Clears existing social links
       try {
           const auto json = nlohmann::json::parse(json_content);
   
           if (json.value("success", false) && json.contains("data") && json["data"].contains("public")) {
               const auto& public_data = json["data"]["public"];
               const std::vector<std::string> social_keys = { "website", "discord", "youtube", "instagram", "facebook", "tiktok" };
               
               // Extracts and populates social links
               for (const auto& key : social_keys) {
                   if (public_data.contains(key)) {
                       std::string value = public_data.value(key, "not-defined");

                       if (!value.empty() && value != "not-defined")
                           server_info.Social_Links.push_back({ key, value });
                   }
               }

               return public_data.value("logo", ""); // Returns logo URL
           }
       }
       catch (const nlohmann::json::exception&) { /* Handles parsing error */ }

       return ""; // Parsing failure
   }
   ```
   Uses `nlohmann::json::parse` to convert the JSON string into a manipulable JSON object. Navigates the structure (`success`, `data`, `public`) and extracts the `logo` (becoming `display_image_url`) and iterates over predefined keys to find and populate `Social_Links` in `server_info`.

### Code Structure

The **SA-MP Rich Presence** project is carefully organized in a clear directory layout, with source code (`src/`) and a subdirectory for external libraries (`libraries/`). File naming follows the `_manager` or `_network` convention for clarity on each class’s purpose. Most header files use the `.hpp` extension, indicating C++ header files.

```
src/
├── libraries/               # Contains essential third-party libraries
│   ├── Dralyxor/            # String obfuscation library
│   ├── Discord/             # Official Discord RPC library
│   └── nlohmann/            # JSON manipulation library
├── asi_update.hpp           # Definition of the automatic update system
├── command_line_parser.hpp  # Definition of the command line parser
├── constants.hpp            # Global project constant definitions
├── discord_manager.hpp      # Definition of the Discord communication manager
├── main.cpp                 # ASI entry point and main orchestrator
├── samp_network.hpp         # Definition of the network manager for SA-MP queries
├── secrets.hpp              # Definitions for secrets obfuscation
├── server_manager.hpp       # Definition of the server information manager
├── server_query.hpp         # Definition of the SA-MP server query logic
├── server_types.hpp         # Definitions of server data structures
├── url_manager.hpp          # Definition of the URL manager for SPC Integration API
└── utils.hpp                # General utility functions (string conversion)
```

#### Global Constants (`constants.hpp`)

This file centralizes all project configurations and immutable values, accessible globally. It uses `inline constexpr` to ensure constants are directly available to the compiler, optimizing performance.

```cpp
// constants.hpp (excerpt)
namespace Constants {
    inline constexpr char ASI_VERSION[] = "1.1"; // Version for update system
    inline constexpr wchar_t UPDATE_API_HOST[] = L"api.github.com"; // Update API host
    inline constexpr char DEFAULT_IMAGE[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/default_logo.png"; // Default image
    inline constexpr int QUERY_TIMEOUT_MS = 800; // Query timeout in ms
    inline constexpr std::chrono::seconds MAIN_LOOP_INTERVAL = std::chrono::seconds(1); // Main loop interval
}
```
Critical details like API URLs, default image paths, network timeouts, and Discord Rich Presence update intervals are centralized here. Using `std::chrono::seconds` for intervals improves readability and prevents unit errors.

#### Data Structures (`server_types.hpp`)

This file defines the `structs` and `using` important for organizing collected and displayed data.

```cpp
// server_types.hpp (excerpt)
namespace server_types {
    using Social_Link = std::pair<std::string, std::string>; // Tuple (network name, URL/value)
}

struct Server_Information {
    uint16_t Players{0};           // Current player count
    uint16_t Max_Players{0};       // Maximum player capacity
    std::string Hostname{};        // Server name
    std::string Server_Address{};  // Ex: "192.168.1.1:7777"

    std::vector<server_types::Social_Link> Social_Links{}; // List of server social links
};
```
The `Server_Information` is the primary structure storing server data. The addition of `std::vector<server_types::Social_Link> Social_Links` reflects the new capability to pull multiple social media links from the API, organized as `(network_name, link)` pairs.

#### Secrets Obfuscation (`secrets.hpp`)

This file is dedicated to protecting sensitive information, such as the **Discord Application ID** and **SPC Integration API** addresses (for now), from easy reverse engineering.

```cpp
// secrets.hpp (excerpt)
#include "libraries/Dralyxor/dralyxor.hpp"

namespace Secrets {
    namespace {
        inline auto& Get_Obfuscated_Discord_App_ID() {
            static auto& dc_app_id_obfuscated = DRALYXOR_KEY("DISCORD_APP_ID", "YOUR_SECRET_KEY_HERE");

            return dc_app_id_obfuscated;
        }
        // ... (other obfuscated secrets) ...
    }
    namespace Detail {
        inline auto& Get_Discord_App_ID() {
            return Get_Obfuscated_Discord_App_ID();
        }
        // ... (public getters to access deobfuscated secrets) ...
    }
}
```
The [Dralyxor](https://github.com/ocalasans/dralyxor) library is used with the `DRALYXOR_KEY` macro to encrypt string literals in the compiled binary. `DRALYXOR_SECURE` is then used at runtime to deobfuscate these values when needed, adding a robust security layer against static key extraction.

#### General Utilities (`utils.hpp`)

A file for generic helper functions useful across modules, avoiding code duplication.

```cpp
// utils.hpp (excerpt)
namespace Utils {
    inline std::string Convert_Wide_To_Utf8_String(const std::wstring_view wide_string) {
        // ... (implementation of conversion using WideCharToMultiByte) ...
    }

    inline std::wstring Convert_Utf8_To_Wide_String(const std::string_view narrow_string) {
        // ... (implementation of conversion using MultiByteToWideChar) ...
    }
}
```
Contains `Convert_Wide_To_Utf8_String` and `Convert_Utf8_To_Wide_String`, essential for interoperability with Windows APIs (using UTF-16) and standard C++ operations (which generally benefit from UTF-8). These functions use Windows APIs for safe and efficient conversion.

### Error Handling and Resilience

The **SA-MP Rich Presence** was designed with resilience in mind, incorporating multiple mechanisms to handle network errors, invalid inputs, and service unavailability.

- **Network Timeouts and Retries:**
   - **Explicit Timeouts:** Network sockets in `samp_network.cpp` set timeouts (`Constants::QUERY_TIMEOUT_MS`) for both send and receive operations, preventing the program from "hanging" while waiting for a response from an inactive server.
      ```cpp
      // samp_network.cpp (timeout configuration)
      const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
      setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      ```
   - **Multiple Query Attempts:** The `Server_Query` performs `Constants::MAX_RETRY_ATTEMPTS` queries on failure. An exponential *back-off* is implemented (`std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)))`) to wait before retrying, reducing load and increasing success chances in unstable network conditions.
- **Robust Disconnection Handling:**
   - **Graceful State Transition:** In `server_manager.cpp`, the connection status (`connection_status`) is not changed immediately after a single query failure. Only if no response is received for 15 consecutive seconds (`now - last_successful_query > std::chrono::seconds(15)`), the status is updated to `false`. This prevents the Discord presence from "flickering" due to minor packet losses.
      ```cpp
      // server_manager.cpp (disconnection logic)
      else { // If query failed
          if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
              connection_status = false;
              display_image_url = Constants::DEFAULT_IMAGE;
              display_server_data = {};
              current_display_social = {};
          }
      }
      ```
   - **Visual Fallback:** Upon detecting a disconnection, the Discord presence image reverts to `Constants::DEFAULT_IMAGE`, and server/social data is cleared, providing clear feedback to the user that they are no longer connected.
- **Invalid Input Handling:**
   - **`command_line_parser.cpp`:** When converting the port argument from string to integer (`std::stoi`), a `try-catch` block is used to handle `std::invalid_argument` (not a number) or `std::out_of_range` (number too large/small). If an error occurs, the default port is kept or parsing fails gracefully, preventing crashes.
- **API Data Retrieval Resilience:**
   - **WinHTTP Failures:** All WinHTTP operations in `url_manager.cpp` are checked for `null` handles and `false` returns at each step (open session, connect, open request, send/receive, read data), ensuring partial failures are caught.
   - **HTTP Status Codes:** After an HTTP request, `url_manager.cpp` verifies the HTTP status code. Only a `200 OK` code is accepted as success, discarding server or gateway error responses.
   - **Safe JSON Parsing:** `url_manager.cpp` wraps JSON parsing (`nlohmann::json::parse`) in a `try-catch(const nlohmann::json::exception&)` block. This prevents malformed or incomplete JSONs from the API from causing a crash, returning empty strings or the default image.
- **Safe Update Mechanisms:**
   - **`asi_update.hpp`:** The update check process in `Check_For_Update` is wrapped in a `try-catch(const std::exception&)` block. This ensures that, even if GitHub is offline, the network is unstable, or the JSON response is invalid, the **ASI** does not crash, and the game can continue loading, safely ignoring the update check.
   - **WinHTTP Handle Management:** The release of `HINTERNET` handles in `asi_update.hpp` and `url_manager.cpp` is carefully planned to execute in all code paths (success and failure), preventing resource leaks.

### Command Line Processing System

The **SA-MP Rich Presence** extracts crucial operational information (server IP, port, and player name) directly from the Grand Theft Auto: San Andreas command line. This method ensures the **ASI** obtains the most accurate and relevant data as soon as the game is launched or a server is connected.

#### Command Line Parser (`command_line_parser.cpp`)

The `Command_Line_Parser` class is responsible for analyzing the full command line string of the process, identifying and extracting specific parameters used by SA-MP.

- **`Parse()`**: The entry point for command line analysis.
   ```cpp
   // command_line_parser.cpp (key excerpt of Parse)
   bool Command_Line_Parser::Parse(const std::wstring_view command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       server_ip = Constants::DEFAULT_SERVER_IP; // Default values
       server_port = Constants::DEFAULT_SERVER_PORT;
   
       if (const auto ip_param = Parse_Parameter(command_line, L"-h"); !ip_param.empty())
           server_ip = Utils::Convert_Wide_To_Utf8_String(ip_param); // Extracts and converts IP
   
       if (const auto port_param = Parse_Parameter(command_line, L"-p"); !port_param.empty()) {
           try {
               server_port = std::stoi(std::wstring(port_param)); // Extracts and converts Port (with error handling)
           }
           catch (const std::invalid_argument&) {}
           catch (const std::out_of_range&) {}
       }
   
       if (const auto name_param = Parse_Parameter(command_line, L"-n"); !name_param.empty())
           player_name = Utils::Convert_Wide_To_Utf8_String(name_param); // Extracts and converts Name
   
       return !server_ip.empty() && server_port > 0 && !player_name.empty(); // Validates essential data presence
   }
   ```
   Receives the command line (`command_line`) as `std::wstring_view` for efficiency. Uses `Parse_Parameter` to find and extract values associated with `-h` (host/IP), `-p` (port), and `-n` (player name). Extracted values (in `std::wstring_view`) are converted to `std::string` (UTF-8) using `Utils::Convert_Wide_To_Utf8_String`. For the port, a `try-catch` block wraps `std::stoi` to safely manage conversion errors. The function returns `true` if all critical parameters (IP, valid port, and player name) are obtained.
- **`Parse_Parameter()`**: The helper function for extracting a single parameter.
   ```cpp
   // command_line_parser.cpp (key excerpt of Parse_Parameter)
   std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring_view command_string, const std::wstring_view parameter) {
       if (const size_t position = command_string.find(parameter); position != std::wstring_view::npos) {
           size_t value_start = position + parameter.length();
           value_start = command_string.find_first_not_of(L" \t", value_start); // Skips spaces after parameter

           if (value_start == std::wstring_view::npos)
               return L""; // Parameter found but no value
   
           const size_t value_end = command_string.find(L' ', value_start); // Finds next space (end of value)
           
           return std::wstring(command_string.substr(value_start, value_end - value_start)); // Returns value substring
       }

       return L""; // Parameter not found
   }
   ```
   Locates the `parameter` substring (`-h`, `-p`, `-n`) in `command_string`. Calculates the value’s start position, skipping spaces/tabs. Identifies the value’s end position (next space) and returns the substring corresponding to the parameter’s value.

### SA-MP Communication Protocol

The **ASI** interacts directly with SA-MP servers using the **UDP** query protocol to extract vital real-time information. This communication is implemented to be efficient and resilient to network failures.

#### Protocol Implementation

The `Server_Query` class is the backbone of this implementation, managing packet sending and response interpretation.

- **SA-MP Query Packet Structure (`'i'`)**: The **ASI** constructs an 11-byte **UDP** packet for the information query:
   - `BYTE 0-3`: Signature "SAMP" (S A M P).
   - `BYTE 4-9`: 6-byte arbitrary sequence (typically the source IP address for server recognition).
   - `BYTE 10`: Query identifier 'i' (ASCII 105), indicating the **ASI** wants general server information (hostname, players, etc.).
      ```cpp
      // server_query.cpp (packet assembly)
      void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
          memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
          packet = 'i'; // Information query
      }
      ```
- **Server Response Structure**: When an SA-MP server responds to an 'i' query, it sends a **UDP** packet containing a structured data sequence that the **ASI** must parse:
   - **Response Header:** Repetition of the "SAMP" signature and the 6-byte sequence from the query packet. The **ASI** simply skips these `Constants::QUERY_PACKET_SIZE` bytes.
   - **Passworded (`bool`):** One byte indicating whether the server is password-protected. Read but not used.
   - **Players (`uint16_t`):** The number of players currently connected to the server.
   - **Max_Players (`uint16_t`):** The maximum player slots the server supports.
   - **Hostname (string prefixed by `uint32_t`):** The server’s friendly name. The packet includes a `uint32_t` for the hostname string length, followed by the string bytes.
   - **Other Fields:** The SA-MP protocol continues with "gamemode" and "language," also length-prefixed. The **ASI** reads and skips these fields to focus on the essential `Players`, `Max_Players`, and `Hostname` data.

   Reading these fields is done with helper functions `Read_From_Span` and `Read_String_From_Span`, ensuring the **ASI** does not read beyond the buffer’s bounds and correctly handles fixed and variable-length (string) data reads.
   ```cpp
   // server_query.cpp (response parsing)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       // ... (size check and subspan for data) ...
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Reads 'passworded' boolean
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false; // Reads 'Players'

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false; // Reads 'Max_Players'

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false; // Reads 'Hostname'
   
       // Fields 'Gamemode' and 'Language' are implicitly "skipped"
       // by subsequent Read_String_From_Span calls
       // to move the span past their data in the buffer.
       uint32_t length_placeholder; // Temporary variable to hold size.

       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Reads gamemode size

       if (data_span.size() < length_placeholder)
           return false; // Checks bounds

       data_span = data_span.subspan(length_placeholder); // Skips gamemode data
   
       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Reads language size

       if (data_span.size() < length_placeholder)
           return false; // Checks bounds

       data_span = data_span.subspan(length_placeholder); // Skips language data
   
       return true;
   }
   ```
   In the example above, the `data_span = data_span.subspan(length_placeholder);` logic is an efficient way to "skip" the number of bytes read for a string whose content is not needed for the Rich Presence.

### Benefits of SA-MP Rich Presence

The SA-MP Rich Presence significantly enhances the experience for both players and server administrators, offering notable advantages:

1. **For Players:**
   - **Effortless Visibility:** Automatically share your gaming status on Discord with friends, showing exactly where you are playing.
   - **Rich Information:** Gain immediate access to server details (name, player count, IP, custom logo) directly on Discord, eliminating the need to check this information elsewhere.
   - **Direct Community Access:** Quickly discover and access the server’s social media through rotating icons in the Discord presence, facilitating entry into vibrant communities.
   - **Fast Friend Connection:** Invite or join the same server as your friends with one click, thanks to the "Join" button functionality.
   - **Always-On Experience:** The automatic update system ensures you always use the most optimized and functional version of the **ASI**.
2. **For Servers:**
   - **Natural Viral Marketing:** Your players’ Discord presence acts as a digital billboard, promoting your server to an organic audience (players’ friends) 24/7.
   - **Strong Visual Identity:** A custom logo and rotating social links allow your server to stand out and project a professional, modern image in the Discord environment.
   - **Increased Engagement:** Facilitate the path for new and returning players to connect with your social platforms, strengthening your community and engagement outside the game.
   - **Easier Recruitment:** The "Join" feature streamlines the process for new players, removing barriers and encouraging experimentation.
   - **Consistent Data:** Through integration with the **SPC Integration API**, information display is unified and centrally updated, ensuring your server’s branding and contacts are always accurate.

## License

This ASI is protected under the Apache License 2.0, which allows:

- ✔️ Commercial and private use
- ✔️ Source code modification
- ✔️ Code distribution
- ✔️ Patent grant

### Conditions:

- Maintain copyright notice
- Document significant changes
- Include Apache License 2.0 copy

For more details about the license: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - All rights reserved**