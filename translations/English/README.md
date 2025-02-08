# SA-MP Rich Presence

SA-MP Rich Presence is an ASI for SA-MP (San Andreas Multiplayer) that automatically updates your Discord status with detailed server information. The ASI is injected into the game when you connect to a SA-MP server, displaying server information.

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

## Index

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Languages](#languages)
  - [Index](#index)
  - [What is an ASI?](#what-is-an-asi)
  - [Features](#features)
    - [Discord Rich Presence](#discord-rich-presence)
  - [Requirements](#requirements)
  - [Installation](#installation)
  - [Detailed Technical Architecture](#detailed-technical-architecture)
    - [Main System (main.cpp)](#main-system-maincpp)
    - [Discord Manager (discord\_manager.cpp)](#discord-manager-discord_managercpp)
    - [Server Manager (server\_manager.cpp)](#server-manager-server_managercpp)
    - [Network System (network\_manager.cpp)](#network-system-network_managercpp)
    - [Server Query (server\_query.cpp)](#server-query-server_querycpp)
  - [SPC Integration](#spc-integration)
    - [What is SPC Integration?](#what-is-spc-integration)
    - [How It Works](#how-it-works)
    - [URL Manager (url\_manager.cpp)](#url-manager-url_managercpp)
  - [For Server Developers](#for-server-developers)
  - [Code Structure](#code-structure)
    - [Global Constants (constants.h)](#global-constants-constantsh)
    - [Data Structures (server\_types.h)](#data-structures-server_typesh)
  - [Error Handling](#error-handling)
  - [Command Line Processing System](#command-line-processing-system)
    - [Command Line Parser (command\_line\_parser.cpp)](#command-line-parser-command_line_parsercpp)
  - [SA-MP Communication Protocol](#sa-mp-communication-protocol)
    - [Protocol Implementation](#protocol-implementation)
  - [Benefits of SA-MP Rich Presence](#benefits-of-sa-mp-rich-presence)
  - [Additional Technical Notes](#additional-technical-notes)

## What is an ASI?

ASI is a dynamic library (.dll) renamed with the .asi extension that is automatically loaded by an ASI loader when GTA San Andreas is started. ASI plugins allow modifying or adding functionality to the game without altering the original files, being one of the most popular forms of modding for GTA San Andreas and other GTA series games. With an ASI loader installed, you can easily install or remove modifications by simply adding or removing .asi files from the game folder.

## Features

### Discord Rich Presence

Discord Rich Presence is a feature that allows applications to show detailed information about what the user is doing directly in their Discord profile. In the case of SA-MP Rich Presence, the following information is displayed:
- Server name (Hostname)
- Player name
- Current number of players and maximum players
- Server IP and port
- Custom server image (requires the server to have the [SPC Integration](https://github.com/spc-samp/spc-integration) plugin)
- Play time
- Connection status

## Requirements

- SA-MP Client (if you don't have it: [clients-samp](https://github.com/spc-samp/clients-samp))
- Discord Desktop Application
- Windows Operating System
- Visual C++ Runtime
- ASI Loader installed in GTA San Andreas

## Installation

1. Download the latest compiled version of the ASI from [releases](https://github.com/ocalasans/samp-rich-presence/releases)
2. Make sure you have an ASI Loader installed in your GTA San Andreas
3. Copy the downloaded .asi file to your GTA San Andreas folder
4. Start the game with SA-MP
5. The ASI will automatically initialize when you join a server

## Detailed Technical Architecture

### Main System (main.cpp)

The main.cpp file is the entry point of the ASI and responsible for:
1. System initialization:
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

2. Update thread management:
   ```cpp
   DWORD WINAPI Update_Thread(LPVOID) {
       // Initialize WSA for network operations
       WSAData wsa_data;
       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
       
       // Process command line parameters
       std::string server_ip, player_name;
       int server_port;
       
       // Initialize managers
       Global_Server_Manager = std::make_unique<Server_Manager>(server_ip, server_port, player_name);
       Global_Discord_Manager = std::make_unique<Discord_Manager>();
       
       // Main update loop
       while (true) {
           Global_Server_Manager->Update();
           Global_Discord_Manager->Update_Presence(...);
           Sleep(Constants::PRESENCE_UPDATE_INTERVAL);
       }
   }
   ```

### Discord Manager (discord_manager.cpp)

The Discord_Manager is responsible for all Discord Rich Presence integration:
1. Discord RPC initialization:
   ```cpp
   void Discord_Manager::Initialize() noexcept {
       Sleep(5000);  // Wait for Discord initialization
       
       DiscordEventHandlers discord_handlers{};
       Discord_Initialize("DISCORD_APP_ID", &discord_handlers, 1, NULL); // "DISCORD_APP_ID > Application ID"
       
       start_timestamp = time(nullptr);  // Mark session start
   }
   ```

2. Presence update:
   ```cpp
   void Discord_Manager::Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept {
       DiscordRichPresence discord_presence{};
       
       // Configure basic information
       discord_presence.state = player_name.data();
       discord_presence.details = server_info.Hostname.c_str();
       discord_presence.largeImageKey = current_image.data();
       
       // Add server information
       discord_presence.largeImageText = server_info.Server_Address.c_str();
       discord_presence.startTimestamp = start_timestamp;
       discord_presence.partySize = server_info.Players;
       discord_presence.partyMax = server_info.Max_Players;
       
       Discord_UpdatePresence(&discord_presence);
   }
   ```

### Server Manager (server_manager.cpp)

The Server_Manager coordinates all server-related operations:
1. State management:
   ```cpp
   Server_Manager::Server_Manager(const std::string& ip, int port, const std::string& name)
       : connection_status(false)
       , server_ip(ip)
       , server_port(port)
       , player_name(name)
       , current_image_url(Constants::DEFAULT_IMAGE)
   {}
   ```

2. Information update:
   ```cpp
   bool Server_Manager::Update() {
       bool query_success = server_query.Query(server_data);
       
       if (query_success) {
           connection_status = true;
           server_data.Server_Address = Get_Server_Address();
           
           // Try to get custom server image
           std::string new_image_url = url_manager.Get_Image_URL(server_data.Server_Address);

           if (!new_image_url.empty())
               current_image_url = new_image_url;
       }
       // ...
   }
   ```

### Network System (network_manager.cpp)

The Network_Manager implements all network communication:
1. Socket initialization:
   ```cpp
   bool Network_Manager::Initialize(std::string_view ip, int port) noexcept {
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       
       // Configure timeout
       timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
       
       // Configure server address
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(port);
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr);
       
       return true;
   }
   ```

### Server Query (server_query.cpp)

The Server_Query implements the SA-MP query protocol:
1. Query packet assembly:
   ```cpp
   bool Server_Query::Assemble_Query_Packet(char* packet) noexcept {
       memcpy(packet, QUERY_SIGNATURE, 4);  // "SAMP"
       packet[10] = 'i';  // Information query

       return true;
   }
   ```

2. Response processing:
   ```cpp
   bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
       // Extract information such as:
       // - Number of players
       // - Maximum players
       // - Hostname
   }
   ```

## SPC Integration

### What is SPC Integration?

[SPC Integration](https://github.com/spc-samp/spc-integration) is a plugin developed for **SA-MP** (San Andreas Multiplayer) and **open.mp** (Open Multiplayer) that acts as a bridge between servers and the **SPC** ecosystem. The plugin collects crucial server information, including:
- IP and port
- Server website URL
- Custom image URL
- Configuration information

This information is sent and securely stored in the **SPC (SA-MP Programming Community)** data storage, allowing integration with various **SPC** applications, including Rich Presence.

### How It Works

1. The server uses the [SPC Integration](https://github.com/spc-samp/spc-integration) plugin to register its custom image
2. The image is stored in **SPC**'s data storage within the server's JSON file
3. When a player connects to the server:
    - The ASI's URL_Manager tries to fetch the server's JSON file (format: `ip-port.json`)
    - If found, extracts the image URL from the `spc_integration_image` parameter
    - The image is then displayed in the player's Discord Rich Presence

### URL Manager (url_manager.cpp)

The URL_Manager is responsible for all communication with **SPC**'s data storage:
1. Server image fetch:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       std::string formatted_address = server_address;
       // Convert ":" to "-" in address
       size_t colon_pos = formatted_address.find(':');

       if (colon_pos != std::string::npos)
           formatted_address.replace(colon_pos, 1, "-");
       
       // Fetch server JSON
       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;
       
       return image_url;
   }
   ```

2. JSON processing:
   ```cpp
   std::string URL_Manager::Parse_JSON(const std::string& json_content) {
       const std::string key = "\"spc_integration_image\":";
       size_t key_pos = json_content.find(key);
       
       // Extract image URL from JSON
       // ...
       
       return image_url;
   }
   ```

## For Server Developers

If you are a SA-MP server developer, we strongly recommend installing the [SPC Integration](https://github.com/spc-samp/spc-integration) plugin for the following reasons:
1. Visibility:
    - Your server's custom image will be displayed in the Discord of all players using this ASI
    - Increases your server's brand recognition
    - Provides a more professional presentation

2. Benefits:
    - Greater player engagement
    - Visual differentiation on Discord
    - Automatic Rich Presence integration

3. How to implement:
   - Read the [SPC Integration](https://github.com/spc-samp/spc-integration) plugin repository to learn how to implement

## Code Structure

The project is organized into several components:
```
src/
├── discord/               # Discord RPC Library
├── command_line_parser.*  # Argument processing
├── constants.h            # Global constants
├── discord_manager.*      # Discord integration
├── main.cpp               # Entry point
├── network_manager.*      # Network operations
├── server_manager.*       # Server management
├── server_query.*         # SA-MP protocol
├── server_types.h         # Data structures
└── url_manager.*          # SPC integration
```

### Global Constants (constants.h)

The file defines several important constants:
```cpp
namespace Constants {
    // Default values
    inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
    inline constexpr int DEFAULT_SERVER_PORT = 7777;
    
    // Network settings
    inline constexpr int QUERY_TIMEOUT = 1000;
    inline constexpr int QUERY_PACKET_SIZE = 11;
    inline constexpr int QUERY_BUFFER_SIZE = 512;
    
    // Retry settings
    inline constexpr int MAX_RETRY_ATTEMPTS = 3;
    
    // Intervals
    inline constexpr int PRESENCE_UPDATE_INTERVAL = 5000;
}
```

### Data Structures (server_types.h)

Defines the main structures:
```cpp
struct Server_Information {
    uint16_t Players{ 0 };           // Online players
    uint16_t Max_Players{ 0 };       // Maximum players
    std::string Hostname;            // Server name
    std::string Server_Image;        // Image URL
    std::string Server_Address;      // Server address
};
```

## Error Handling

The system implements a robust error handling system:
1. Network timeout:
   ```cpp
   timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
   setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
   ```

2. Retry system:
   ```cpp
   bool Server_Query::Try_Query(Server_Information& server_data, int retry_count) noexcept {
       for (int attempt = 0; attempt <= retry_count; attempt++) {
           if (network_manager.Send_Query(...))
               return true;
           
           // Wait before trying again
           std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
       }

       return false;
   }
   ```

3. Default image fallback:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       // If something goes wrong, return default image
       if (!session_handle)
           return Constants::DEFAULT_IMAGE;

       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;

       return image_url;
   }
   ```

4. Connection state monitoring:
   ```cpp
   bool Server_Manager::Update() {
       auto current_time = std::chrono::steady_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_successful_query);
       
       // If no response for more than 15 seconds, consider disconnected
       if (duration.count() > 15) {
           connection_status = false;
           current_image_url = Constants::DEFAULT_IMAGE;
       }
   }
   ```

## Command Line Processing System

The ASI implements a flexible system for processing command line arguments:

### Command Line Parser (command_line_parser.cpp)

1. Main processing:
   ```cpp
   bool Command_Line_Parser::Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       // Set default values
       server_ip = Constants::DEFAULT_SERVER_IP;
       server_port = Constants::DEFAULT_SERVER_PORT;

       // Process each parameter
       std::wstring ip_parameter = Parse_Parameter(command_string, L"-h");
       std::wstring port_parameter = Parse_Parameter(command_string, L"-p");
       std::wstring name_parameter = Parse_Parameter(command_string, L"-n");

       // Convert and validate values
       if (!ip_parameter.empty())
           server_ip = Convert_To_String(ip_parameter);

       if (!port_parameter.empty())
           server_port = std::stoi(port_parameter);

       if (!name_parameter.empty())
           player_name = Convert_To_String(name_parameter);

       // Check if all necessary parameters are present
       return !server_ip.empty() && server_port > 0 && !player_name.empty();
   }
   ```

2. Parameter extraction:
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

## SA-MP Communication Protocol

The ASI implements the SA-MP query protocol to obtain server information:
1. Query packet structure:
    - 4 bytes: "SAMP" signature
    - 7 bytes: Additional data
    - Last byte: 'i' (indicates information query)

2. Response structure:
    - Packet header
    - Players (uint16_t)
    - Max_Players (uint16_t)
    - Hostname (string)

### Protocol Implementation

```cpp
bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
    char* current_pos = response_buffer + Constants::QUERY_PACKET_SIZE;
    const char* buffer_end = response_buffer + received_bytes;

    // Skip "password"
    current_pos += sizeof(bool);
    
    // Read fixed data
    memcpy(&server_data.Players, current_pos, sizeof(server_data.Players));
    current_pos += sizeof(server_data.Players);
    
    memcpy(&server_data.Max_Players, current_pos, sizeof(server_data.Max_Players));
    current_pos += sizeof(server_data.Max_Players);

    // Read Hostname and skip "gamemode" and "language"
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
    
    // Skip "gamemode" and "language"
    // ...

    return true;
}
```

## Benefits of SA-MP Rich Presence

1. For Players:
    - Quick visualization of current server
    - Detailed server information
    - Seamless Discord integration
    - More social gaming experience

2. For Servers:
    - Greater visibility through Discord
    - Organic marketing through players
    - Custom visual identity (with [SPC Integration](https://github.com/spc-samp/spc-integration) plugin)
    - Real-time statistics

## Additional Technical Notes

1. Thread Safety:
    - ASI uses a single thread for updates
    - Managers are thread-safe by design
    - Resources are properly synchronized

2. Memory Usage:
    - Minimal memory allocation
    - Pre-allocated buffers for queries
    - Automatic resource management (RAII)

3. Performance:
    - Optimized queries with timeout
    - Smart retry system
    - Configurable update interval

4. Compatibility:
    - Unicode support
    - Compatible with modern Windows
    - IPv4 support