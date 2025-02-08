# SA-MP Rich Presence

SA-MP Rich Presence est un ASI pour SA-MP (San Andreas Multiplayer) qui met automatiquement à jour votre statut Discord avec des informations détaillées sur le serveur. L'ASI est injecté dans le jeu lorsque vous vous connectez à un serveur SA-MP, affichant les informations du serveur.

## Langues

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Indice

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Langues](#langues)
  - [Indice](#indice)
  - [Qu'est-ce qu'un ASI ?](#quest-ce-quun-asi-)
  - [Fonctionnalités](#fonctionnalités)
    - [Discord Rich Presence](#discord-rich-presence)
  - [Prérequis](#prérequis)
  - [Installation](#installation)
  - [Architecture Technique Détaillée](#architecture-technique-détaillée)
    - [Système Principal (main.cpp)](#système-principal-maincpp)
    - [Gestionnaire Discord (discord\_manager.cpp)](#gestionnaire-discord-discord_managercpp)
    - [Gestionnaire de Serveur (server\_manager.cpp)](#gestionnaire-de-serveur-server_managercpp)
    - [Système Réseau (network\_manager.cpp)](#système-réseau-network_managercpp)
    - [Requête Serveur (server\_query.cpp)](#requête-serveur-server_querycpp)
  - [Intégration avec SPC](#intégration-avec-spc)
    - [Qu'est-ce que SPC Integration ?](#quest-ce-que-spc-integration-)
    - [Comment ça fonctionne](#comment-ça-fonctionne)
    - [Gestionnaire d'URL (url\_manager.cpp)](#gestionnaire-durl-url_managercpp)
  - [Pour les Développeurs de Serveur](#pour-les-développeurs-de-serveur)
  - [Structure du Code](#structure-du-code)
    - [Constantes Globales (constants.h)](#constantes-globales-constantsh)
    - [Structures de Données (server\_types.h)](#structures-de-données-server_typesh)
  - [Gestion des Erreurs](#gestion-des-erreurs)
  - [Système de Traitement de la Ligne de Commande](#système-de-traitement-de-la-ligne-de-commande)
    - [Parser de Ligne de Commande (command\_line\_parser.cpp)](#parser-de-ligne-de-commande-command_line_parsercpp)
  - [Protocole de Communication SA-MP](#protocole-de-communication-sa-mp)
    - [Implémentation du Protocole](#implémentation-du-protocole)
  - [Avantages de SA-MP Rich Presence](#avantages-de-sa-mp-rich-presence)
  - [Notes Techniques Supplémentaires](#notes-techniques-supplémentaires)
  - [Licence](#licence)
    - [Conditions](#conditions)

## Qu'est-ce qu'un ASI ?

Un ASI est une bibliothèque dynamique (.dll) renommée avec l'extension .asi qui est automatiquement chargée par un chargeur ASI lorsque GTA San Andreas démarre. Les plugins ASI permettent de modifier ou d'ajouter des fonctionnalités au jeu sans altérer les fichiers originaux, étant l'une des formes les plus populaires de modding pour GTA San Andreas et d'autres jeux de la série GTA. Avec un chargeur ASI installé, vous pouvez facilement installer ou supprimer des modifications simplement en ajoutant ou en supprimant des fichiers .asi du dossier du jeu.

## Fonctionnalités

### Discord Rich Presence

Discord Rich Presence est une fonctionnalité qui permet aux applications d'afficher des informations détaillées sur ce que l'utilisateur fait directement sur son profil Discord. Dans le cas de SA-MP Rich Presence, les informations suivantes sont affichées :
- Nom du serveur (Hostname)
- Nom du joueur
- Nombre actuel de joueurs et maximum de joueurs
- IP et port du serveur
- Image personnalisée du serveur (nécessite que le serveur ait le plugin [SPC Integration](https://github.com/spc-samp/spc-integration))
- Temps de jeu
- Statut de la connexion

## Prérequis

- Client SA-MP (si vous ne l'avez pas : [clients-samp](https://github.com/spc-samp/clients-samp))
- Application Discord Desktop
- Système d'exploitation Windows
- Visual C++ Runtime
- ASI Loader installé dans GTA San Andreas

## Installation

1. Téléchargez la version la plus récente de l'ASI compilé dans les [releases](https://github.com/ocalasans/samp-rich-presence/releases)
2. Assurez-vous d'avoir un ASI Loader installé dans votre GTA San Andreas
3. Copiez le fichier .asi téléchargé dans le dossier de votre GTA San Andreas
4. Lancez le jeu avec SA-MP
5. L'ASI sera automatiquement initialisé lorsque vous entrerez sur un serveur

## Architecture Technique Détaillée

### Système Principal (main.cpp)

Le fichier main.cpp est le point d'entrée de l'ASI et responsable de :
1. Initialisation du système :
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

2. Gestion du thread de mise à jour :
   ```cpp
   DWORD WINAPI Update_Thread(LPVOID) {
       // Initialise WSA pour les opérations réseau
       WSAData wsa_data;
       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
       
       // Traite les paramètres de ligne de commande
       std::string server_ip, player_name;
       int server_port;
       
       // Initialise les gestionnaires
       Global_Server_Manager = std::make_unique<Server_Manager>(server_ip, server_port, player_name);
       Global_Discord_Manager = std::make_unique<Discord_Manager>();
       
       // Boucle principale de mise à jour
       while (true) {
           Global_Server_Manager->Update();
           Global_Discord_Manager->Update_Presence(...);
           Sleep(Constants::PRESENCE_UPDATE_INTERVAL);
       }
   }
   ```

### Gestionnaire Discord (discord_manager.cpp)

Le Discord_Manager est responsable de toute l'intégration avec Discord Rich Presence :
1. Initialisation du Discord RPC :
   ```cpp
   void Discord_Manager::Initialize() noexcept {
       Sleep(5000);  // Attend l'initialisation de Discord
       
       DiscordEventHandlers discord_handlers{};
       Discord_Initialize("DISCORD_APP_ID", &discord_handlers, 1, NULL); // "DISCORD_APP_ID > Application ID"
       
       start_timestamp = time(nullptr);  // Marque le début de la session
   }
   ```

2. Mise à jour de la présence :
   ```cpp
   void Discord_Manager::Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept {
       DiscordRichPresence discord_presence{};
       
       // Configure les informations de base
       discord_presence.state = player_name.data();
       discord_presence.details = server_info.Hostname.c_str();
       discord_presence.largeImageKey = current_image.data();
       
       // Ajoute les informations du serveur
       discord_presence.largeImageText = server_info.Server_Address.c_str();
       discord_presence.startTimestamp = start_timestamp;
       discord_presence.partySize = server_info.Players;
       discord_presence.partyMax = server_info.Max_Players;
       
       Discord_UpdatePresence(&discord_presence);
   }
   ```

### Gestionnaire de Serveur (server_manager.cpp)

Le Server_Manager coordonne toutes les opérations liées au serveur :
1. Gestion de l'état :
   ```cpp
   Server_Manager::Server_Manager(const std::string& ip, int port, const std::string& name)
       : connection_status(false)
       , server_ip(ip)
       , server_port(port)
       , player_name(name)
       , current_image_url(Constants::DEFAULT_IMAGE)
   {}
   ```

2. Mise à jour des informations :
   ```cpp
   bool Server_Manager::Update() {
       bool query_success = server_query.Query(server_data);
       
       if (query_success) {
           connection_status = true;
           server_data.Server_Address = Get_Server_Address();
           
           // Tente d'obtenir l'image personnalisée du serveur
           std::string new_image_url = url_manager.Get_Image_URL(server_data.Server_Address);

           if (!new_image_url.empty())
               current_image_url = new_image_url;
       }
       // ...
   }
   ```

### Système Réseau (network_manager.cpp)

Le Network_Manager implémente toute la communication réseau :
1. Initialisation du socket :
   ```cpp
   bool Network_Manager::Initialize(std::string_view ip, int port) noexcept {
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       
       // Configure le timeout
       timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
       
       // Configure l'adresse du serveur
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(port);
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr);
       
       return true;
   }
   ```

### Requête Serveur (server_query.cpp)

Le Server_Query implémente le protocole de requête SA-MP :
1. Assemblage du paquet de requête :
   ```cpp
   bool Server_Query::Assemble_Query_Packet(char* packet) noexcept {
       memcpy(packet, QUERY_SIGNATURE, 4);  // "SAMP"
       packet[10] = 'i';  // Information query

       return true;
   }
   ```

2. Traitement de la réponse :
   ```cpp
   bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
       // Extrait les informations comme :
       // - Nombre de joueurs
       // - Maximum de joueurs
       // - Hostname
   }
   ```

## Intégration avec SPC

### Qu'est-ce que SPC Integration ?

[SPC Integration](https://github.com/spc-samp/spc-integration) est un plugin développé pour **SA-MP** (San Andreas Multiplayer) et **open.mp** (Open Multiplayer) qui agit comme un pont entre les serveurs et l'écosystème **SPC**. Le plugin collecte des informations cruciales du serveur, notamment :
- IP et port
- URL du site du serveur
- URL de l'image personnalisée
- Informations de configuration

Ces informations sont envoyées et stockées de manière sécurisée dans le stockage de données **SPC (SA-MP Programming Community)**, permettant une intégration avec diverses applications SPC, y compris le Rich Presence.

### Comment ça fonctionne

1. Le serveur utilise le plugin [SPC Integration](https://github.com/spc-samp/spc-integration) pour enregistrer son image personnalisée
2. L'image est stockée dans le stockage de données SPC dans le fichier JSON du serveur
3. Quand un joueur se connecte au serveur :
    - L'URL_Manager de l'ASI tente de récupérer le fichier JSON du serveur (format : `ip-port.json`)
    - Si trouvé, extrait l'URL de l'image du paramètre `spc_integration_image`
    - L'image est alors affichée dans le Discord Rich Presence du joueur

### Gestionnaire d'URL (url_manager.cpp)

L'URL_Manager est responsable de toute la communication avec le stockage de données SPC :
1. Recherche de l'image du serveur :
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       std::string formatted_address = server_address;
       // Convertit ":" en "-" dans l'adresse
       size_t colon_pos = formatted_address.find(':');

       if (colon_pos != std::string::npos)
           formatted_address.replace(colon_pos, 1, "-");
       
       // Recherche le JSON du serveur
       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;
       
       return image_url;
   }
   ```

2. Traitement du JSON :
   ```cpp
   std::string URL_Manager::Parse_JSON(const std::string& json_content) {
       const std::string key = "\"spc_integration_image\":";
       size_t key_pos = json_content.find(key);
       
       // Extrait l'URL de l'image du JSON
       // ...
       
       return image_url;
   }
   ```

## Pour les Développeurs de Serveur

Si vous êtes un développeur de serveur SA-MP, nous recommandons fortement l'installation du plugin [SPC Integration](https://github.com/spc-samp/spc-integration) pour les raisons suivantes :
1. Visibilité :
    - L'image personnalisée de votre serveur sera affichée sur Discord pour tous les joueurs qui utilisent cet ASI
    - Augmente la reconnaissance de la marque de votre serveur
    - Fournit une présentation plus professionnelle

2. Avantages :
    - Plus grand engagement des joueurs
    - Différenciation visuelle sur Discord
    - Intégration automatique avec Rich Presence

3. Comment implémenter :
   - Lisez le dépôt du plugin [SPC Integration](https://github.com/spc-samp/spc-integration) pour savoir comment l'implémenter

## Structure du Code

Le projet est organisé en plusieurs composants :
```
src/
├── discord/               # Bibliothèque Discord RPC
├── command_line_parser.*  # Traitement des arguments
├── constants.h            # Constantes globales
├── discord_manager.*      # Intégration avec Discord
├── main.cpp               # Point d'entrée
├── network_manager.*      # Opérations réseau
├── server_manager.*       # Gestion du serveur
├── server_query.*         # Protocole SA-MP
├── server_types.h         # Structures de données
└── url_manager.*          # Intégration avec SPC
```

### Constantes Globales (constants.h)

Le fichier définit plusieurs constantes importantes :
```cpp
namespace Constants {
    // Valeurs par défaut
    inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
    inline constexpr int DEFAULT_SERVER_PORT = 7777;
    
    // Paramètres réseau
    inline constexpr int QUERY_TIMEOUT = 1000;
    inline constexpr int QUERY_PACKET_SIZE = 11;
    inline constexpr int QUERY_BUFFER_SIZE = 512;
    
    // Paramètres de retry
    inline constexpr int MAX_RETRY_ATTEMPTS = 3;
    
    // Intervalles
    inline constexpr int PRESENCE_UPDATE_INTERVAL = 5000;
}
```

### Structures de Données (server_types.h)

Définit les structures principales :
```cpp
struct Server_Information {
    uint16_t Players{ 0 };           // Joueurs en ligne
    uint16_t Max_Players{ 0 };       // Maximum de joueurs
    std::string Hostname;            // Nom du serveur
    std::string Server_Image;        // URL de l'image
    std::string Server_Address;      // Adresse du serveur
};
```

## Gestion des Erreurs

Le système implémente un système robuste de gestion des erreurs :
1. Timeout réseau :
   ```cpp
   timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
   setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
   ```

2. Système de retry :
   ```cpp
   bool Server_Query::Try_Query(Server_Information& server_data, int retry_count) noexcept {
       for (int attempt = 0; attempt <= retry_count; attempt++) {
           if (network_manager.Send_Query(...))
               return true;
           
           // Attend avant de réessayer
           std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
       }

       return false;
   }
   ```

3. Repli vers l'image par défaut :
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       // Si quelque chose ne va pas, retourne l'image par défaut
       if (!session_handle)
           return Constants::DEFAULT_IMAGE;

       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;

       return image_url;
   }
   ```

4. Surveillance de l'état de connexion :
   ```cpp
   bool Server_Manager::Update() {
       auto current_time = std::chrono::steady_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_successful_query);
       
       // Si plus de 15 secondes sans réponse, considère comme déconnecté
       if (duration.count() > 15) {
           connection_status = false;
           current_image_url = Constants::DEFAULT_IMAGE;
       }
   }
   ```

## Système de Traitement de la Ligne de Commande

L'ASI implémente un système flexible pour traiter les arguments de ligne de commande :

### Parser de Ligne de Commande (command_line_parser.cpp)

1. Traitement principal :
   ```cpp
   bool Command_Line_Parser::Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       // Définit les valeurs par défaut
       server_ip = Constants::DEFAULT_SERVER_IP;
       server_port = Constants::DEFAULT_SERVER_PORT;

       // Traite chaque paramètre
       std::wstring ip_parameter = Parse_Parameter(command_string, L"-h");
       std::wstring port_parameter = Parse_Parameter(command_string, L"-p");
       std::wstring name_parameter = Parse_Parameter(command_string, L"-n");

       // Convertit et valide les valeurs
       if (!ip_parameter.empty())
           server_ip = Convert_To_String(ip_parameter);

       if (!port_parameter.empty())
           server_port = std::stoi(port_parameter);

       if (!name_parameter.empty())
           player_name = Convert_To_String(name_parameter);

       // Vérifie si tous les paramètres nécessaires sont présents
       return !server_ip.empty() && server_port > 0 && !player_name.empty();
   }
   ```

2. Extraction des paramètres :
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

## Protocole de Communication SA-MP

L'ASI implémente le protocole de requête SA-MP pour obtenir des informations du serveur :
1. Structure du paquet de requête :
    - 4 octets : Signature "SAMP"
    - 7 octets : Données additionnelles
    - Dernier octet : 'i' (indique une requête d'informations)

2. Structure de la réponse :
    - En-tête du paquet
    - Players (uint16_t)
    - Max_Players (uint16_t)
    - Hostname (string)

### Implémentation du Protocole

```cpp
bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
    char* current_pos = response_buffer + Constants::QUERY_PACKET_SIZE;
    const char* buffer_end = response_buffer + received_bytes;

    // Sauter "password"
    current_pos += sizeof(bool);
    
    // Lit les données fixes
    memcpy(&server_data.Players, current_pos, sizeof(server_data.Players));
    current_pos += sizeof(server_data.Players);
    
    memcpy(&server_data.Max_Players, current_pos, sizeof(server_data.Max_Players));
    current_pos += sizeof(server_data.Max_Players);

    // Lit Hostname et saute "gamemode" et "language"
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
    
    // Saute "gamemode" et "language"
    // ...

    return true;
}
```

## Avantages de SA-MP Rich Presence

1. Pour les Joueurs :
    - Visualisation rapide du serveur actuel
    - Informations détaillées sur le serveur
    - Intégration parfaite avec Discord
    - Expérience de jeu plus sociale

2. Pour les Serveurs :
    - Plus grande visibilité via Discord
    - Marketing organique via les joueurs
    - Identité visuelle personnalisée (avec le plugin [SPC Integration](https://github.com/spc-samp/spc-integration))
    - Statistiques en temps réel

## Notes Techniques Supplémentaires

1. Thread Safety :
    - L'ASI utilise un seul thread pour les mises à jour
    - Les gestionnaires sont thread-safe par conception
    - Les ressources sont correctement synchronisées

2. Utilisation de la Mémoire :
    - Allocation minimale de mémoire
    - Buffers pré-alloués pour les requêtes
    - Gestion automatique des ressources (RAII)

3. Performance :
    - Requêtes optimisées avec timeout
    - Système de retry intelligent
    - Intervalle de mise à jour configurable

4. Compatibilité :
    - Support de l'Unicode
    - Compatible avec Windows moderne
    - Support IPv4

## Licence

Cet ASI est protégé sous la Licence Apache 2.0, qui permet :

- ✔️ Utilisation commerciale et privée
- ✔️ Modification du code source
- ✔️ Distribution du code
- ✔️ Concession de brevets

### Conditions

- Conserver la notice de droits d'auteur
- Documenter les modifications significatives
- Inclure une copie de la licence Apache 2.0

Pour plus de détails sur la licence : http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Tous droits réservés**