# SA-MP Rich Presence

Le **SA-MP Rich Presence** est un **ASI** pour **SA-MP (San Andreas Multiplayer)** qui met à jour automatiquement votre statut Discord avec des informations détaillées sur le serveur. L'**ASI** est injecté dans le jeu lorsque vous vous connectez à un serveur SA-MP, affichant des informations sur le serveur.

## Idiomas

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Índice

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Fonctionnalités](#fonctionnalités)
    - [Discord Rich Presence](#discord-rich-presence)
    - [Système de Mise à Jour Automatique](#système-de-mise-à-jour-automatique)
  - [Exigences](#exigences)
  - [Installation](#installation)
  - [Intégration avec l'API SPC Integration](#intégration-avec-lapi-spc-integration)
    - [Comment l'information est obtenue et utilisée:](#comment-linformation-est-obtenue-et-utilisée)
  - [Pour les Développeurs de Serveurs](#pour-les-développeurs-de-serveurs)
    - [Comment implémenter SPC Integration sur votre serveur:](#comment-implémenter-spc-integration-sur-votre-serveur)
  - [Architecture Technique Détaillée](#architecture-technique-détaillée)
      - [Système Principal (`main.cpp`)](#système-principal-maincpp)
      - [Système de Mise à Jour (`asi_update.hpp`)](#système-de-mise-à-jour-asi_updatehpp)
      - [Gestionnaire Discord (`discord_manager.cpp`)](#gestionnaire-discord-discord_managercpp)
      - [Gestionnaire de Serveur (`server_manager.cpp`)](#gestionnaire-de-serveur-server_managercpp)
      - [Système de Réseau (`samp_network.cpp`)](#système-de-réseau-samp_networkcpp)
      - [Consultation du Serveur (`server_query.cpp`)](#consultation-du-serveur-server_querycpp)
      - [Gestionnaire d'URL (`url_manager.cpp`)](#gestionnaire-durl-url_managercpp)
    - [Structure du Code](#structure-du-code)
      - [Constantes Globales (`constants.hpp`)](#constantes-globales-constantshpp)
      - [Structures de Données (`server_types.hpp`)](#structures-de-données-server_typeshpp)
      - [Obfuscation des Secrets (`secrets.hpp`)](#obfuscation-des-secrets-secretshpp)
      - [Utilitaires Généraux (`utils.hpp`)](#utilitaires-généraux-utilshpp)
    - [Traitement des Erreurs et Résilience](#traitement-des-erreurs-et-résilience)
    - [Système de Traitement de la Ligne de Commande](#système-de-traitement-de-la-ligne-de-commande)
      - [Parseur de Ligne de Commande (`command_line_parser.cpp`)](#parseur-de-ligne-de-commande-command_line_parsercpp)
    - [Protocole de Communication SA-MP](#protocole-de-communication-sa-mp)
      - [Implémentation du Protocole](#implémentation-du-protocole)
    - [Avantages du SA-MP Rich Presence](#avantages-du-sa-mp-rich-presence)
  - [Licence](#licence)
    - [Conditions](#conditions)

## Fonctionnalités

### Discord Rich Presence

Le **Discord Rich Presence** est une fonctionnalité qui permet aux applications d'afficher des informations détaillées sur ce que l'utilisateur fait directement sur son profil Discord. Dans le cas du **SA-MP Rich Presence**, les informations suivantes sont affichées:

- **Nom du serveur (Hostname):** Le nom principal du serveur.
- **Nom du joueur:** Votre pseudonyme actuel dans le jeu.
- **Contagem de jogadores:** Nombre actuel de joueurs en ligne et le maximum autorisé.
- **Endereço do servidor:** Adresse IP et port du serveur pour une identification facile.
- **Imagem personalizada do servidor:** Un logo unique du serveur, si disponible.
- **Ícone social rotativo:** Petits icônes représentant les liens vers les réseaux sociaux du serveur (site web, Discord, YouTube, Instagram, Facebook, TikTok), alternant automatiquement.
- **Tempo de jogo:** Temps pendant lequel vous êtes connecté au serveur actuel.
- **Status da conexão:** Indique si vous êtes en ligne sur un serveur ou dans l'état "Idle" (inactif).
- **Botão "Join" (Entrer):** Permet à vos amis de rejoindre directement le même serveur que vous jouez.

### Système de Mise à Jour Automatique

L'**ASI** intègre un système de vérification de mise à jour. Au démarrage du jeu, il vérifie s'il existe de nouvelles versions disponibles dans le dépôt GitHub officiel du projet. Si une mise à jour est détectée, une notification conviviale est affichée à l'utilisateur, offrant les options suivantes:

1. Ouvrir le navigateur directement sur la page des releases pour le téléchargement.
2. Continuer sans mettre à jour, avec l'option de désactiver l'**ASI** pour la session actuelle.

Cette fonctionnalité garantit que les utilisateurs ont toujours accès aux dernières améliorations, corrections de bugs et nouvelles fonctionnalités, offrant une expérience actualisée et sans interruptions.

## Exigences

- Client SA-MP (si vous n'en avez pas: [clients-samp](https://github.com/spc-samp/clients-samp)).
- Application Discord Desktop.
- Système d'exploitation Windows.
- Visual C++ Runtime.
- Un [ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) installé dans votre Grand Theft Auto: San Andreas.

## Installation

1. Téléchargez la version la plus récente de l'**ASI** compilée directement depuis la section des [releases](https://github.com/ocalasans/samp-rich-presence/releases) sur GitHub.
2. Après le téléchargement, localisez le fichier `.asi`.
3. Copiez le fichier `.asi` téléchargé dans le dossier racine de votre GTA San Andreas (où se trouve le fichier `gta_sa.exe`).
4. Lancez le jeu via le client SA-MP.
5. L'**ASI** sera chargé et initialisé automatiquement lorsque vous vous connecterez à un serveur, mettant à jour votre statut sur Discord.

## Intégration avec l'API SPC Integration

Le **SA-MP Rich Presence** améliore significativement l'affichage des informations sur Discord grâce à son intégration avec l'**SPC Integration API**. Au lieu de dépendre uniquement des données de requête de base, l'**ASI** interagit désormais directement avec cette API pour obtenir des informations visuelles et sociales du serveur. Pour en savoir plus sur **SPC Integration**, visitez le dépôt officiel: [spc-samp/spc-integration](https://github.com/spc-samp/spc-integration).

### Comment l'information est obtenue et utilisée:

1. **Formatage de l'adresse:** Lorsque le joueur se connecte à un serveur (IP et Port), l'**ASI** formate cette adresse (`IP:PORT`) en un format convivial (`IP-PORT`), la préparant pour la requête API.
2. **Requête à l'API:** L'**ASI** envoie une requête `GET` à l'endpoint de l'**SPC Integration API**, incluant l'IP et le port formatés. Exemple de comment l'URL de requête est construite en interne:
   ```cpp
   // Trecho adaptado de url_manager.cpp
   auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
   std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
   path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   const std::string json_data = Request_API_Data(path);
   ```
3. **Traitement de la réponse JSON:** L'API renvoie une réponse au format JSON. L'**ASI** utilise la bibliothèque [nlohmann/json](https://github.com/nlohmann/json) pour analyser cette réponse et extraire les données pertinentes.
   ```json
   // Exemple de structure de réponse de l'API SPC Integration
   {
       "success": true,
       "data": {
           "public": {
               "logo": "https://url.de.votre.logo/server_logo.png",
               "website": "https://votre-site.com",
               "discord": "https://discord.gg/votreserveur",
               "youtube": "https://youtube.com/votrechaîne"
               // ...autres réseaux sociaux
           }
       }
   }
   ```
4. **Extraction des données:**
   - **Logo du serveur:** L'URL de l'image du serveur (le `logo` dans la section `public`) est extraite et utilisée comme image principale (large image) dans le **Discord Rich Presence**. Cela garantit une identité visuelle authentique et personnalisable pour chaque serveur.
   - **Liens sociaux:** Une liste prédéfinie de réseaux sociaux (site web, Discord, YouTube, Instagram, Facebook, TikTok) est vérifiée dans la réponse JSON. Pour chaque réseau social trouvé avec une valeur valide, le nom du réseau et son lien respectif sont stockés.
5. **Affichage sur Discord:** Le `Server_Manager` utilise la liste des liens sociaux extraits pour implémenter une rotation dynamique. Toutes les 30 secondes, une icône différente d'un des réseaux sociaux du serveur est affichée comme la "small image" (petite image) dans la présence Discord, accompagnée du lien ou du nom de la plateforme, encourageant l'exploration des communautés du serveur.

## Pour les Développeurs de Serveurs

L'intégration de votre serveur avec [SPC Integration](https://github.com/spc-samp/spc-integration) apporte une série d'avantages directs et indirects qui stimulent la visibilité et l'engagement de votre communauté SA-MP. Si vous êtes un développeur de serveur, considérez les avantages stratégiques:

1. **Renforcez votre marque:**
   - **Visibilité premium:** Le logo personnalisé de votre serveur ne sera pas seulement un texte, mais une image vibrante et attrayante, affichée en évidence sur le profil Discord de tous les joueurs utilisant cet **ASI**. C'est une forme organique et constante de branding.
   - **Présence professionnelle:** En ayant votre logo et vos réseaux sociaux bien représentés, votre serveur projette une image plus établie et fiable, attirant plus d'intérêt et de potentiels nouveaux joueurs.
2. **Expansion de la communauté:**
   - **Multipliez les canaux d'accès:** Avec la rotation des icônes sociales, vous pouvez promouvoir différentes plateformes de votre communauté – du site web officiel et du Discord du serveur à vos pages YouTube, Instagram, Facebook ou TikTok. Chaque icône et lien dans le **Discord Rich Presence** dirige directement les intéressés vers les lieux où votre communauté est active.
   - **Connectivité instantanée:** La fonctionnalité "Join" via Discord permet aux amis de vos joueurs de rejoindre votre serveur SA-MP en un seul clic, réduisant les barrières à l'entrée et encourageant de nouveaux membres.
3. **Mise à jour simplifiée du contenu:**
   - En utilisant [SPC Integration](https://github.com/spc-samp/spc-integration), toute mise à jour du logo de votre serveur ou de la liste des réseaux sociaux configurés dans le plugin [SPC Integration](https://github.com/spc-samp/spc-integration) **(côté serveur)** sera automatiquement reflétée pour les joueurs utilisant l'**ASI**, sans qu'ils aient besoin de mettre à jour l'**ASI**. Cela garantit que les informations sont toujours correctes et à jour.

### Comment implémenter SPC Integration sur votre serveur:

1. **Plugin SPC Integration:** Votre serveur devra avoir le plugin [SPC Integration](https://github.com/spc-samp/spc-integration) installé et configuré correctement. Ce plugin est le pont qui envoie les informations de votre serveur à une liste de données **SPC**, qui est ensuite utilisée par l'**SPC Integration API** pour fournir des informations publiques.
2. **Configuration:** Suivez les instructions dans le dépôt du plugin [SPC Integration](https://github.com/spc-samp/spc-integration) pour configurer:
   - Le paramètre `logo` avec l'URL du logo de votre serveur.
   - Les paramètres des réseaux sociaux (`discord`, `website`, `youtube`, etc.) avec les liens valides vers vos plateformes.
3. **Mise à jour automatique:** Une fois les informations configurées dans le plugin du serveur, le **SA-MP Rich Presence** les détectera et les affichera automatiquement. Aucune action n'est requise de la part du joueur au-delà de l'installation initiale de l'**ASI**.

En intégrant votre serveur avec [SPC Integration](https://github.com/spc-samp/spc-integration), vous améliorez non seulement l'expérience de vos joueurs, mais vous ouvrez également la voie à une croissance et un engagement significatifs pour votre communauté.

## Architecture Technique Détaillée

Le **SA-MP Rich Presence** possède une architecture modulaire bien définie, avec des composants axés sur des tâches spécifiques. La base de code est alignée sur les normes modernes de C++ (C++17 et C++20), utilisant `std::string_view`, `std::span` et la sémantique de déplacement pour garantir des performances élevées, la sécurité et l'efficacité.

#### Système Principal (`main.cpp`)

Le cœur de l'**ASI** réside dans `main.cpp`, qui gère le cycle de vie de l'application, depuis son initialisation en tant que DLL jusqu'à la boucle de mise à jour continue et son arrêt gracieux.

- **`DllMain`**: La porte d'entrée de l'**ASI** lorsqu'il est chargé par le système d'exploitation.
   ```cpp
   // DllMain (simplifié pour se concentrer sur la structure)
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
   Dans cette fonction, lorsqu'il est attaché au processus du jeu (`DLL_PROCESS_ATTACH`), il empêche les appels de bibliothèque inutiles (`DisableThreadLibraryCalls`) et **crée un nouveau thread (`Main_Update_Thread`)** pour exécuter la logique de l'**ASI** de manière asynchrone, garantissant que le jeu ne soit pas bloqué. Lors de l'arrêt (`DLL_PROCESS_DETACH`), `Shutdown_Managers()` est invoqué pour libérer les ressources.
- **`Main_Update_Thread`**: L'âme de l'**ASI**, opérant dans son propre thread.
   ```cpp
   // Main_Update_Thread (extrait clé)
   DWORD WINAPI Main_Update_Thread(LPVOID) {
       // 1. Vérification de mise à jour
       if (Asi_Update::Check_For_Update())
           return 0; // Si l'utilisateur choisit de désactiver, termine.
   
       // 2. Initialisation du réseau (Winsock)
       WSAData wsa_data;

       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
   
       // 3. Initialisation des gestionnaires de serveur et Discord
       Initialize_Managers();
   
       // 4. Boucle principale de mise à jour
       while (is_running && v_server_manager && v_discord_manager) {
           v_server_manager->Update(); // Requête serveur, API SPC, etc.
           v_discord_manager->Update_Presence( // Met à jour le statut Discord
               v_server_manager->Get_Server_Info(),
               v_server_manager->Get_Display_Social_Link(),
               v_server_manager->Get_Player_Name(),
               v_server_manager->Get_Current_Image_URL(),
               v_server_manager->Is_Connected());
   
           Discord_RunCallbacks(); // Traite les événements RPC de Discord
           std::this_thread::sleep_for(Constants::MAIN_LOOP_INTERVAL);
       }
   
       // 5. Arrêt (si les gestionnaires existent)
       if (v_discord_manager)
           v_discord_manager->Shutdown();

       WSACleanup(); // Libère Winsock

       return 0;
   }
   ```
   Cette fonction donne la priorité à la vérification des mises à jour. Ensuite, elle initialise la pile réseau Winsock et les instances des gestionnaires de serveur et Discord. Une boucle `while` persistante (contrôlée par `std::atomic<bool> is_running` pour un arrêt sécurisé) coordonne les appels à `Server_Manager::Update()` (collecte de données) et `Discord_Manager::Update_Presence()` (envoi à Discord). `Discord_RunCallbacks()` garantit que Discord traite les événements de Rich Presence. La boucle est mise en pause périodiquement à l'aide de `std::this_thread::sleep_for` pour optimiser les ressources.

#### Système de Mise à Jour (`asi_update.hpp`)

Ce module vital ajoute de l'intelligence à l'**ASI**, garantissant que les utilisateurs restent à jour.

- **`Check_For_Update()`**: La fonction principale de vérification.
   ```cpp
   // asi_update.hpp (extrait clé de Check_For_Update)
   inline bool Check_For_Update() {
       HINTERNET h_session = nullptr, h_connect = nullptr, h_request = nullptr;
       bool update_found_and_handled = false;
   
       try {
           h_session = WinHttpOpen(L"SA-MP Rich Presence Update/1.0", ...);
           // ... (requête GET pour Constants::UPDATE_API_PATH dans l'API GitHub) ...
           std::string response_body;
           // ... (lecture de la réponse HTTP) ...
           nlohmann::json release_info = nlohmann::json::parse(response_body);
   
           std::string latest_tag = release_info["tag_name"].get<std::string>();
           // ... (normalise et compare les versions avec sscanf_s/sscanf) ...
   
           if (latest_major > current_major || (latest_major == current_major && latest_minor > current_minor)) {
               update_found_and_handled = true;
               std::wstringstream message_stream;
               // ... (prépare le message de la MessageBox) ...
               int msgbox_result = MessageBoxW(NULL, message_stream.str().c_str(), L"SA-MP Rich Presence - Update Available", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
               
               if (msgbox_result == IDYES)
                   ShellExecuteW(NULL, L"open", Constants::UPDATE_RELEASES_URL, NULL, NULL, SW_SHOWNORMAL);
           }
       }
       catch (const std::exception&) { /* Traitement des erreurs */ }
   
       // ... (fermer les handles WinHttp) ...
       return update_found_and_handled;
   }
   ```
   Utilisant l'**API WinHTTP** pour les requêtes réseau, `Check_For_Update` effectue une requête `GET` à l'endpoint `/releases/latest` de l'API GitHub pour le dépôt du projet. La réponse, au format JSON, est analysée avec la bibliothèque `nlohmann/json`. La version la plus récente (`tag_name`) est comparée numériquement à la version compilée de l'**ASI**. Si une nouvelle version est détectée, une boîte de dialogue (`MessageBoxW`) est affichée, demandant à l'utilisateur s'il souhaite se rendre sur la page des téléchargements via `ShellExecuteW`. L'ensemble du processus est encapsulé dans un `try-catch` pour garantir que les échecs réseau ou d'analyse n'empêchent pas le démarrage du jeu.

#### Gestionnaire Discord (`discord_manager.cpp`)

La classe `Discord_Manager` abstrait les interactions avec la bibliothèque **Discord RPC**, gérant l'initialisation de la connexion et l'envoi des données pour le statut de présence de l'utilisateur.

- **`Initialize()`**: Configure la communication avec Discord.
   ```cpp
   // discord_manager.cpp (extrait clé de Initialize)
   void Discord_Manager::Initialize() noexcept {
       DiscordEventHandlers handlers;
       memset(&handlers, 0, sizeof(handlers)); // Garantit l'initialisation
       
       // App ID est désobfusqué ici
       auto app_id_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_Discord_App_ID());
       Discord_Initialize(app_id_accessor.Get(), &handlers, 1, nullptr);
   
       start_timestamp_ = time(nullptr); // Enregistre le début de la session
   }
   ```
   L'appel à `Discord_Initialize` est crucial, utilisant le `DISCORD_APP_ID` obtenu de manière sécurisée via l'obfuscation de chaîne dans `secrets.hpp`. Le `start_timestamp_` est défini ici pour calculer le temps de jeu dans la présence Discord.
- **`Update_Presence()`**: La fonction vitale qui met à jour la Rich Presence de Discord.
   ```cpp
   // discord_manager.cpp (extrait clé de Update_Presence)
   void Discord_Manager::Update_Presence(const Server_Information& server_info, const server_types::Social_Link& social_link, const std::string_view player_name, const std::string_view current_image, const bool is_connected) noexcept {
       DiscordRichPresence discord_presence;
       memset(&discord_presence, 0, sizeof(discord_presence));
   
       discord_presence.startTimestamp = start_timestamp_;
       discord_presence.largeImageKey = current_image.data(); // Logo du serveur
   
       if (is_connected) {
           discord_presence.details = server_info.Hostname.c_str();
           discord_presence.state = player_name.data();
           discord_presence.largeImageText = server_info.Server_Address.c_str(); // IP:Port
           discord_presence.partySize = server_info.Players;
           discord_presence.partyMax = server_info.Max_Players;
           discord_presence.joinSecret = server_info.Server_Address.c_str(); // Active le bouton "Join"
   
           // Gère l'icône sociale rotative
           if (!social_link.first.empty()) {
               current_small_image_key_ = Constants::SOCIAL_ICON_BASE_URL;
               current_small_image_key_ += social_link.first; // Ex: "discord.png"
               current_small_image_key_ += ".png";
               discord_presence.smallImageKey = current_small_image_key_.c_str();
               discord_presence.smallImageText = social_link.second.c_str(); // Texte au survol (lien/nom)
           }
       }
       else {
           discord_presence.details = "SA-MP"; // État "Idle"
           discord_presence.state = "Idle";
           discord_presence.largeImageText = "San Andreas Multiplayer";
           // smallImageKey et smallImageText restent vides pour l'état idle
       }
   
       Discord_UpdatePresence(&discord_presence);
   }
   ```
   Remplit la structure `DiscordRichPresence` en fonction de l'état de la connexion. Si `is_connected` est vrai, le hostname, le nombre de joueurs, l'IP du serveur et le nom du joueur sont affichés. Le `largeImageKey` définit l'image principale du serveur. Notamment, `joinSecret` est défini pour permettre aux amis de se connecter directement, et le `smallImageKey` (construit dynamiquement à partir du `social_link` fourni) affiche les icônes sociales rotatives. En état "Idle", la présence est simplifiée pour refléter l'inactivité. Enfin, `Discord_UpdatePresence` envoie les données à Discord.

#### Gestionnaire de Serveur (`server_manager.cpp`)

Le `Server_Manager` est l'orchestrateur des données, gérant l'état de la connexion, consultant le serveur et l'**SPC Integration API**, et décidant quelles informations doivent être affichées et quand.

- **`Update()`**: Le cycle de vie principal pour la collecte de données.
   ```cpp
   // server_manager.cpp (extrait clé de Update)
   void Server_Manager::Update() {
       const auto now = std::chrono::steady_clock::now();
   
       if (server_query.Query(live_server_data)) { // Tente d'obtenir des données via une requête SA-MP
           if (!connection_status) { // Si juste connecté/reconnecté
               connection_status = true;
               Fetch_API_Data(); // Récupère le logo et les sociaux de l'API
           }
           
           last_successful_query = now;
   
           // Met à jour les données à afficher sur Discord
           display_server_data.Hostname = live_server_data.Hostname;
           display_server_data.Players = live_server_data.Players;
           display_server_data.Max_Players = live_server_data.Max_Players;
           display_server_data.Server_Address = server_ip + ":" + std::to_string(server_port);
   
           if (now - last_api_update > Constants::IMAGE_UPDATE_INTERVAL)
               Fetch_API_Data(); // Reconsulte l'API après un temps défini
   
           if (now - last_social_rotation > Constants::SOCIAL_UPDATE_INTERVAL)
               Rotate_Social_Link(); // Fait pivoter l'icône sociale
       }
       else { // Si la requête a échoué
           if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
               connection_status = false; // Déconnecté après un timeout
               display_image_url = Constants::DEFAULT_IMAGE;
               display_server_data = {}; // Efface les données
               current_display_social = {}; // Efface les sociaux
           }
       }
   }
   ```
   La fonction `Update` tente d'effectuer une requête au serveur. En cas de succès, elle met à jour les données dans `live_server_data` et `display_server_data`. Conditionnellement, elle appelle `Fetch_API_Data()` pour mettre à jour l'image et les liens sociaux (si c'est une nouvelle connexion ou si `IMAGE_UPDATE_INTERVAL` est écoulé) et `Rotate_Social_Link()` pour alterner les icônes sociales (`SOCIAL_UPDATE_INTERVAL`). Si les requêtes au serveur échouent de manière constante pendant plus de 15 secondes, l'état de la connexion est considéré comme perdu, réinitialisant les informations affichées.
- **`Fetch_API_Data()`**: Responsable de l'obtention des données visuelles et sociales.
   ```cpp
   // server_manager.cpp (extrait clé de Fetch_API_Data)
   void Server_Manager::Fetch_API_Data() {
       display_image_url = url_manager.Get_Image_URL_And_Populate_Socials(server_ip, server_port, live_server_data);
       last_api_update = std::chrono::steady_clock::now();
       current_social_index_ = 0; // Réinitialise l'index après une nouvelle récupération API
       Rotate_Social_Link(); // Garantit qu'une icône sociale est affichée immédiatement
   }
   ```
   Cette fonction coordonne avec `URL_Manager` pour récupérer le logo et les liens sociaux de l'API, mettant à jour `display_image_url` et remplissant les `Social_Links` dans `live_server_data`. Elle réinitialise l'index de rotation des sociaux et appelle `Rotate_Social_Link()` pour garantir que la première icône est prête à être affichée.
- **`Rotate_Social_Link()`**: Logique pour alterner les icônes sociales.
   ```cpp
   // server_manager.cpp (extrait clé de Rotate_Social_Link)
   void Server_Manager::Rotate_Social_Link() {
       if (!live_server_data.Social_Links.empty()) {
           if (current_social_index_ >= live_server_data.Social_Links.size())
               current_social_index_ = 0; // Redémarre le cycle
   
           current_display_social = live_server_data.Social_Links[current_social_index_];
           current_social_index_ = (current_social_index_ + 1) % live_server_data.Social_Links.size();
       }
       else
           current_display_social = {}; // Efface si aucun social
       
       last_social_rotation = std::chrono::steady_clock::now();
   }
   ```
   Cette fonction simple sélectionne le prochain `Social_Link` dans la liste de `live_server_data.Social_Links` de manière cyclique et le stocke dans `current_display_social` pour que le `Discord_Manager` puisse l'utiliser.

#### Système de Réseau (`samp_network.cpp`)

La classe `Samp_Network` est l'implémentation de bas niveau de la communication **UDP**, responsable de l'ouverture et de la gestion du socket pour les requêtes SA-MP. Elle offre désormais des constructeurs et des opérateurs de déplacement pour une meilleure gestion des ressources.

- **`Initialize()`**: Configure le socket pour la communication **UDP**.
   ```cpp
   // samp_network.cpp (extrait clé de Initialize)
   bool Samp_Network::Initialize(const std::string_view ip, const int port) noexcept {
       if (network_socket != INVALID_SOCKET)
           closesocket(network_socket); // Ferme le socket existant
   
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       if (network_socket == INVALID_SOCKET)
           return false;
   
       const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
       setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
   
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(static_cast<u_short>(port));
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr); // Support IPv4
       return true;
   }
   ```
   Initialise le socket, définit les délais pour les opérations d'envoi et de réception, et configure la structure d'adresse (`sockaddr_in`) avec l'IP et le port du serveur de destination, en utilisant `inet_pton` pour gérer la conversion de l'IP.
- **`Send_Query()`**: Envoie un paquet de requête et reçoit la réponse.
   ```cpp
   // samp_network.cpp (extrait clé de Send_Query)
   bool Samp_Network::Send_Query(const std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept {
       // Envoie le paquet UDP
       if (sendto(network_socket, query_packet.data(), static_cast<int>(query_packet.size()), 0, reinterpret_cast<const sockaddr*>(&server_address), sizeof(server_address)) < 0)
           return false;
   
       sockaddr_in from_address;
       int address_length = sizeof(from_address);
       // Reçoit la réponse
       received_bytes = recvfrom(network_socket, response_buffer.data(), static_cast<int>(response_buffer.size()), 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);
   
       return received_bytes > Constants::QUERY_PACKET_SIZE;
   }
   ```
   Cette méthode envoie le `query_packet` (passé en tant que `std::span` pour la sécurité du buffer) au serveur. Ensuite, elle tente de recevoir une réponse dans `response_buffer`. Le retour indique si l'opération a réussi et si un nombre d'octets supérieur à la taille du paquet de requête a été reçu.

#### Consultation du Serveur (`server_query.cpp`)

La classe `Server_Query` est dédiée à l'implémentation du protocole de requête SA-MP (`'i'`), extrayant les informations de base du serveur (joueurs, hostname) à partir des réponses **UDP**.

- **`Query()`**: Gère les tentatives de requête.
   ```cpp
   // server_query.cpp (extrait clé de Query)
   bool Server_Query::Query(Server_Information& server_data) noexcept {
       for (int attempt = 0; attempt < Constants::MAX_RETRY_ATTEMPTS; ++attempt) {
           if (Try_Query(server_data))
               return true; // Succès de la requête
   
           if (attempt < Constants::MAX_RETRY_ATTEMPTS - 1)
               // Petite pause avant de réessayer, pour éviter le flooding
               std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)));
       }

       return false; // Toutes les tentatives ont échoué
   }
   ```
   Implémente la stratégie de *retry* avec `MAX_RETRY_ATTEMPTS` et un *back-off* de temps croissant, pour garantir que les requêtes soient robustes et évitent de saturer le réseau. Appelle `Try_Query` à chaque tentative.
- **`Assemble_Query_Packet()`**: Construit le paquet de requête SA-MP.
   ```cpp
   // server_query.cpp (extrait clé de Assemble_Query_Packet)
   void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
       memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
       packet = 'i'; // Code de requête d'information
   }
   ```
   Le paquet standard pour la requête d'information (`'i'`) de SA-MP est construit, incluant la signature "SAMP" et le byte identifiant 'i'.
- **`Parse_Response()`**: Décompacte la réponse binaire du serveur.
   ```cpp
   // server_query.cpp (extrait clé de Parse_Response)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       if (response.size() <= Constants::QUERY_PACKET_SIZE) 
           return false;
   
       auto data_span = response.subspan(Constants::QUERY_PACKET_SIZE); // Saute l'en-tête
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Ignoré, mais lu
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false;

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false;

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false;
   
       // Note: Gamemode et Language sont automatiquement sautés par Read_String_From_Span si le paquet contient plus de données.
       // Si vous avez besoin des autres champs, il suffit de créer une chaîne et d'appeler: Read_String_From_Span(data_span, string_variable);
       return true;
   }
   ```
   Cette méthode lit de manière sécurisée les données du `response_buffer` (en utilisant `std::span` et les fonctions auxiliaires `Read_From_Span` et `Read_String_From_Span`). Elle extrait le nombre de joueurs, le maximum de joueurs et le hostname du serveur, remplissant la structure `Server_Information`. Les champs non utilisés (comme si le serveur est protégé par mot de passe) sont lus mais ignorés, et d'autres comme "gamemode" et "language" sont "sautés" si la réponse contient plus de données que l'**ASI** n'a besoin pour le moment.
- **Fonctions de lecture auxiliaires:**
   ```cpp
   // server_query.hpp (extraits des auxiliaires de lecture)
   template<typename T>
   static bool Read_From_Span(std::span<const char>& s, T& value) noexcept;
   
   static bool Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept;
   ```
   `Read_From_Span` gère la lecture de types fixes (entiers, booléens) à partir du `std::span` et avance le `span`. `Read_String_From_Span` lit la longueur d'une chaîne (comme `uint32_t`) puis la chaîne elle-même, en avançant également le `span`. Cela garantit la sécurité lors de l'analyse des octets et empêche les lectures hors limites du buffer.

#### Gestionnaire d'URL (`url_manager.cpp`)

La classe `URL_Manager` gère les communications HTTPS avec l'**SPC Integration API**, un élément central pour les nouvelles fonctionnalités visuelles et sociales du **Discord Rich Presence**.

- **`Get_Image_URL_And_Populate_Socials()`**: La méthode de haut niveau pour récupérer les informations de l'API.
   ```cpp
   // url_manager.cpp (extrait clé de Get_Image_URL_And_Populate_Socials)
   std::string URL_Manager::Get_Image_URL_And_Populate_Socials(const std::string& ip, const int port, Server_Information& server_info) {
       if (!session_handle)
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);
   
       auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
       std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
       path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   
       const std::string json_data = Request_API_Data(path); // Requête HTTP pour l'API
   
       if (json_data.empty())
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE); // Erreur dans la requête
   
       return Parse_API_Response(json_data, server_info); // Analyse et remplit server_info
   }
   ```
   Reçoit l'IP et le port, construit l'URL de l'API en les incluant comme paramètres. Appelle `Request_API_Data` pour récupérer les données JSON. En cas de succès, `Parse_API_Response` est appelée pour extraire l'URL de l'image (logo) et remplir la liste des liens sociaux dans `server_info`.
- **`Request_API_Data()`**: Effectue la requête HTTPS pour l'API.
   ```cpp
   // url_manager.cpp (extrait clé de Request_API_Data)
   std::string URL_Manager::Request_API_Data(const std::wstring& path) {
       auto api_host_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Host());
       const std::wstring wide_host = Utils::Convert_Utf8_To_Wide_String(api_host_accessor.Get());
       HINTERNET connect_handle = WinHttpConnect(session_handle, wide_host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
   
       if (!connect_handle) return "";
   
       HINTERNET request_handle = WinHttpOpenRequest(connect_handle, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
   
       if (!request_handle) return (WinHttpCloseHandle(connect_handle), "");
   
       // Envoyer la requête, recevoir la réponse, vérifier le statut 200, lire les données en boucle
       // ... (détails de l'appel WinHttpSendRequest, WinHttpReceiveResponse, WinHttpQueryHeaders, WinHttpReadData) ...
       
       WinHttpCloseHandle(request_handle); WinHttpCloseHandle(connect_handle);
       return response_body; // Retourne le JSON sous forme de chaîne
   }
   ```
   Se connecte à l'hôte de l'API (obtenu de manière obfusquée), ouvre et envoie une requête `GET` avec le chemin (`path`). Gère la réponse HTTP, vérifie le code de statut (200 OK pour le succès), et lit le corps complet de la réponse (qui doit être JSON). Tous les handles WinHTTP sont libérés en cas de succès ou d'échec.
- **`Parse_API_Response()`**: Traite la chaîne JSON pour extraire les données.
   ```cpp
   // url_manager.cpp (extrait clé de Parse_API_Response)
   std::string URL_Manager::Parse_API_Response(const std::string& json_content, Server_Information& server_info) {
       server_info.Social_Links.clear(); // Efface les liens sociaux existants
       try {
           const auto json = nlohmann::json::parse(json_content);
   
           if (json.value("success", false) && json.contains("data") && json["data"].contains("public")) {
               const auto& public_data = json["data"]["public"];
               const std::vector<std::string> social_keys = { "website", "discord", "youtube", "instagram", "facebook", "tiktok" };
               
               // Extrait et remplit les liens sociaux
               for (const auto& key : social_keys) {
                   if (public_data.contains(key)) {
                       std::string value = public_data.value(key, "not-defined");

                       if (!value.empty() && value != "not-defined")
                           server_info.Social_Links.push_back({ key, value });
                   }
               }

               return public_data.value("logo", ""); // Retourne l'URL du logo
           }
       }
       catch (const nlohmann::json::exception&) { /* Traite l'erreur de parse */ }

       return ""; // Échec du parse
   }
   ```
   Utilise `nlohmann::json::parse` pour convertir la chaîne JSON en un objet JSON manipulable. Navigue dans la structure (`success`, `data`, `public`) et extrait le `logo` (qui devient `display_image_url`) et itère sur les clés prédéfinies pour trouver et remplir les `Social_Links` de `server_info`.

### Structure du Code

Le projet **SA-MP Rich Presence** est soigneusement organisé dans un layout de répertoires clair, avec le code source (`src/`) et un sous-répertoire pour les bibliothèques externes (`libraries/`). La nomenclature des fichiers suit la convention `_manager` ou `_network` pour plus de clarté sur le but de chaque classe. La majorité des fichiers d'en-tête utilisent l'extension `.hpp`, indiquant qu'il s'agit de fichiers d'en-tête C++.

```
src/
├── libraries/               # Contient les bibliothèques tierces essentielles
│   ├── Dralyxor/            # Bibliothèque d'obfuscation de chaînes
│   ├── Discord/             # Bibliothèque officielle de Discord RPC
│   └── nlohmann/            # Bibliothèque pour la manipulation de JSON
├── asi_update.hpp           # Définition du système de mise à jour automatique
├── command_line_parser.hpp  # Définition du parseur de ligne de commande
├── constants.hpp            # Définitions des constantes globales du projet
├── discord_manager.hpp      # Définition du gestionnaire de communication avec Discord
├── main.cpp                 # Point d'entrée de l'ASI et orchestrateur principal
├── samp_network.hpp         # Définition du gestionnaire de réseau pour les requêtes SA-MP
├── secrets.hpp              # Définitions pour l'obfuscation des secrets
├── server_manager.hpp       # Définition du gestionnaire d'informations du serveur
├── server_query.hpp         # Définition de la logique de requête au serveur SA-MP
├── server_types.hpp         # Définitions des structures de données du serveur
├── url_manager.hpp          # Définition du gestionnaire d'URL pour l'API SPC Integration
└── utils.hpp                # Fonctions utilitaires générales (conversion de chaînes)
```

#### Constantes Globales (`constants.hpp`)

Ce fichier concentre toutes les configurations et valeurs immuables du projet, accessibles globalement. Il utilise `inline constexpr` pour garantir que les constantes soient directement disponibles pour le compilateur, optimisant les performances.

```cpp
// constants.hpp (extrait)
namespace Constants {
    inline constexpr char ASI_VERSION[] = "1.1"; // Version pour le système de mise à jour
    inline constexpr wchar_t UPDATE_API_HOST[] = L"api.github.com"; // Hôte de l'API de mise à jour
    inline constexpr char DEFAULT_IMAGE[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/default_logo.png"; // Image par défaut
    inline constexpr int QUERY_TIMEOUT_MS = 800; // Timeout de la requête en ms
    inline constexpr std::chrono::seconds MAIN_LOOP_INTERVAL = std::chrono::seconds(1); // Intervalle de la boucle principale
}
```
Des détails importants comme les URLs de l'API, les chemins des images par défaut, les délais de réseau et les intervalles de mise à jour du **Discord Rich Presence** sont centralisés ici. L'utilisation de `std::chrono::seconds` pour les intervalles améliore la lisibilité et prévient les erreurs d'unités.

#### Structures de Données (`server_types.hpp`)

Ce fichier définit les `structs` et `using` importants pour organiser les données collectées et affichées.

```cpp
// server_types.hpp (extrait)
namespace server_types {
    using Social_Link = std::pair<std::string, std::string>; // Tuple (nom du réseau, URL/valeur)
}

struct Server_Information {
    uint16_t Players{0};           // Nombre de joueurs actuels
    uint16_t Max_Players{0};       // Capacité maximale de joueurs
    std::string Hostname{};        // Nom du serveur
    std::string Server_Address{};  // Ex: "192.168.1.1:7777"

    std::vector<server_types::Social_Link> Social_Links{}; // Liste des liens sociaux du serveur
};
```
La structure `Server_Information` est la structure principale qui stocke les données du serveur. L'ajout de `std::vector<server_types::Social_Link> Social_Links` reflète la nouvelle capacité à récupérer plusieurs liens de réseaux sociaux via l'API, organisés sous forme de paires `(nom_réseau, lien)`.

#### Obfuscation des Secrets (`secrets.hpp`)

Ce fichier est dédié à la protection des informations sensibles, comme l'**ID d'application Discord** et les adresses de l'**SPC Integration API (pour l'instant)**, contre une ingénierie inverse facile.

```cpp
// secrets.hpp (extrait)
#include "libraries/Dralyxor/dralyxor.hpp"

namespace Secrets {
    namespace {
        inline auto& Get_Obfuscated_Discord_App_ID() {
            static auto& dc_app_id_obfuscated = DRALYXOR_KEY("DISCORD_APP_ID", "YOUR_SECRET_KEY_HERE");

            return dc_app_id_obfuscated;
        }
        // ... (autres secrets obfusqués) ...
    }
    namespace Detail {
        inline auto& Get_Discord_App_ID() {
            return Get_Obfuscated_Discord_App_ID();
        }
        // ... (getters publics pour accéder aux secrets désobfusqués) ...
    }
}
```
La bibliothèque [Dralyxor](https://github.com/ocalasans/dralyxor) est utilisée avec la macro `DRALYXOR_KEY` pour crypter les chaînes littérales dans le binaire compilé. `DRALYXOR_SECURE` est ensuite utilisée au moment de l'exécution pour désobfusquer ces valeurs lorsqu'elles sont nécessaires, ajoutant une couche de sécurité robuste contre l'extraction statique des clés.

#### Utilitaires Généraux (`utils.hpp`)

Un fichier pour les fonctions auxiliaires génériques qui peuvent être utiles dans plusieurs modules, évitant la duplication de code.

```cpp
// utils.hpp (extrait)
namespace Utils {
    inline std::string Convert_Wide_To_Utf8_String(const std::wstring_view wide_string) {
        // ... (implémentation de la conversion utilisant WideCharToMultiByte) ...
    }

    inline std::wstring Convert_Utf8_To_Wide_String(const std::string_view narrow_string) {
        // ... (implémentation de la conversion utilisant MultiByteToWideChar) ...
    }
}
```
Contient les fonctions `Convert_Wide_To_Utf8_String` et `Convert_Utf8_To_Wide_String`, essentielles pour les interopérations avec les API Windows (qui utilisent UTF-16) et les opérations standard C++ (qui bénéficient généralement de l'UTF-8). Ces fonctions utilisent les API Windows pour une conversion sécurisée et efficace.

### Traitement des Erreurs et Résilience

Le **SA-MP Rich Presence** a été conçu avec la résilience à l'esprit, incorporant de multiples mécanismes pour gérer les erreurs réseau, les entrées invalides et l'indisponibilité des services.

- **Délais et tentatives réseau:**
   - **Délais explicites:** Les sockets réseau dans `samp_network.cpp` configurent des délais (`Constants::QUERY_TIMEOUT_MS`) pour les opérations d'envoi et de réception, empêchant le programme de rester "bloqué" en attendant une réponse d'un serveur inactif.
      ```cpp
      // samp_network.cpp (configuration du délai)
      const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
      setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      ```
   - **Multiples tentatives de requête:** Le `Server_Query` exécute `Constants::MAX_RETRY_ATTEMPTS` requêtes en cas d'échec. Un *back-off* exponentiel est implémenté (`std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)))`) pour attendre avant de nouvelles tentatives, réduisant la charge et augmentant les chances de succès dans des conditions de réseau instables.
- **Traitement robuste de la déconnexion:**
   - **Transition d'état gracieuse:** Dans `server_manager.cpp`, l'état de connexion (`connection_status`) n'est pas modifié immédiatement après un seul échec de requête. Ce n'est que si aucune réponse n'est reçue pendant 15 secondes consécutives (`now - last_successful_query > std::chrono::seconds(15)`) que l'état est mis à jour à `false`. Cela évite le "clignotement" de la présence sur Discord en raison de petites pertes de paquets.
      ```cpp
      // server_manager.cpp (logique de déconnexion)
      else { // Si la requête a échoué
          if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
              connection_status = false;
              display_image_url = Constants::DEFAULT_IMAGE;
              display_server_data = {};
              current_display_social = {};
          }
      }
      ```
   - **Repli visuel:** Lors de la détection d'une déconnexion, l'image de la présence sur Discord revient à `Constants::DEFAULT_IMAGE`, et les données du serveur/sociaux sont effacées, fournissant un retour clair à l'utilisateur qu'il n'est plus connecté.
- **Traitement des entrées invalides:**
   - **`command_line_parser.cpp`:** Lors de la conversion de l'argument de port de chaîne à entier (`std::stoi`), un bloc `try-catch` est utilisé pour gérer `std::invalid_argument` (pas un nombre) ou `std::out_of_range` (nombre trop grand/petit). En cas d'erreur, le port par défaut est conservé ou l'analyse échoue de manière contrôlée, empêchant les plantages.
- **Résilience dans l'obtention des données de l'API:**
   - **Échecs WinHTTP:** Toutes les opérations de l'API WinHTTP dans `url_manager.cpp` sont vérifiées pour les handles `null` et les retours de `false` à chaque étape (ouvrir la session, connecter, ouvrir la requête, envoyer/recevoir, lire les données), garantissant que les échecs partiels sont capturés.
   - **Codes de statut HTTP:** Après une requête HTTP, `url_manager.cpp` vérifie le `HTTP Status Code`. Seul un code `200 OK` est accepté comme succès, rejetant les réponses d'erreur du serveur ou de la passerelle.
   - **Analyse JSON sécurisée:** `url_manager.cpp` encapsule l'analyse JSON (`nlohmann::json::parse`) dans un bloc `try-catch(const nlohmann::json::exception&)`. Cela empêche les JSON malformés ou incomplets provenant de l'API de provoquer un plantage, renvoyant des chaînes vides ou l'image par défaut.
- **Mécanismes de mise à jour sécurisés:**
   - **`asi_update.hpp`:** Le processus de vérification de mise à jour dans `Check_For_Update` est encapsulé dans un bloc `try-catch(const std::exception&)`. Cela garantit que, même si GitHub est hors ligne, le réseau est instable, ou la réponse JSON est invalide, l'**ASI** ne plante pas et le jeu peut continuer à être chargé, ignorant la vérification de mise à jour de manière sécurisée.
   - **Gestion des handles WinHTTP:** La libération des handles `HINTERNET` dans `asi_update.hpp` et `url_manager.cpp` est soigneusement planifiée pour être exécutée dans tous les chemins de code (succès et échec), empêchant les fuites de ressources.

### Système de Traitement de la Ligne de Commande

Le **SA-MP Rich Presence** extrait les informations cruciales pour son fonctionnement (IP du serveur, port et nom du joueur) directement depuis la ligne de commande du jeu Grand Theft Auto: San Andreas. Cette méthode garantit que l'**ASI** obtienne les données les plus précises et pertinentes dès que le jeu est initialisé ou qu'un serveur est connecté.

#### Parseur de Ligne de Commande (`command_line_parser.cpp`)

La classe `Command_Line_Parser` est responsable de l'analyse de la chaîne de commande complète du processus, identifiant et extrayant les paramètres spécifiques utilisés par SA-MP.

- **`Parse()`**: Le point d'entrée pour l'analyse de la ligne de commande.
   ```cpp
   // command_line_parser.cpp (extrait clé de Parse)
   bool Command_Line_Parser::Parse(const std::wstring_view command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       server_ip = Constants::DEFAULT_SERVER_IP; // Valeurs par défaut
       server_port = Constants::DEFAULT_SERVER_PORT;
   
       if (const auto ip_param = Parse_Parameter(command_line, L"-h"); !ip_param.empty())
           server_ip = Utils::Convert_Wide_To_Utf8_String(ip_param); // Extrait et convertit l'IP
   
       if (const auto port_param = Parse_Parameter(command_line, L"-p"); !port_param.empty()) {
           try {
               server_port = std::stoi(std::wstring(port_param)); // Extrait et convertit le port (avec gestion des erreurs)
           }
           catch (const std::invalid_argument&) {}
           catch (const std::out_of_range&) {}
       }
   
       if (const auto name_param = Parse_Parameter(command_line, L"-n"); !name_param.empty())
           player_name = Utils::Convert_Wide_To_Utf8_String(name_param); // Extrait et convertit le nom
   
       return !server_ip.empty() && server_port > 0 && !player_name.empty(); // Valide si les données essentielles sont présentes
   }
   ```
   Reçoit la ligne de commande (`command_line`) sous forme de `std::wstring_view` pour plus d'efficacité. Utilise `Parse_Parameter` pour trouver et extraire les valeurs associées à `-h` (hôte/IP), `-p` (port) et `-n` (nom du joueur). Les valeurs extraites (en `std::wstring_view`) sont converties en `std::string` (UTF-8) à l'aide de `Utils::Convert_Wide_To_Utf8_String`. Pour le port, un bloc `try-catch` encapsule `std::stoi` pour gérer les erreurs de conversion de manière sécurisée. La fonction retourne `true` si tous les paramètres cruciaux (IP, port valide et nom du joueur) sont obtenus.
- **`Parse_Parameter()`**: La fonction auxiliaire pour l'extraction d'un seul paramètre.
   ```cpp
   // command_line_parser.cpp (extrait clé de Parse_Parameter)
   std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring_view command_string, const std::wstring_view parameter) {
       if (const size_t position = command_string.find(parameter); position != std::wstring_view::npos) {
           size_t value_start = position + parameter.length();
           value_start = command_string.find_first_not_of(L" \t", value_start); // Saute les espaces après le paramètre

           if (value_start == std::wstring_view::npos)
               return L""; // Paramètre trouvé mais sans valeur
   
           const size_t value_end = command_string.find(L' ', value_start); // Trouve le prochain espace (fin de la valeur)
           
           return std::wstring(command_string.substr(value_start, value_end - value_start)); // Retourne la sous-chaîne de la valeur
       }

       return L""; // Paramètre non trouvé
   }
   ```
   Localise la sous-chaîne du `parameter` (`-h`, `-p`, `-n`) dans `command_string`. Calcule la position initiale de la valeur, en ignorant les espaces/tabulations. Identifie la position finale de la valeur (prochain espace) et retourne la sous-chaîne correspondant à la valeur du paramètre.

### Protocole de Communication SA-MP

L'**ASI** interagit directement avec les serveurs SA-MP en utilisant le protocole de requête **UDP** pour extraire des informations vitales en temps réel. Cette communication est implémentée pour être efficace et résiliente aux échecs réseau.

#### Implémentation du Protocole

La classe `Server_Query` est la colonne vertébrale de cette implémentation, gérant l'envoi des paquets et l'interprétation des réponses.

- **Structure du paquet de requête SA-MP (`'i'`)**: L'**ASI** construit un paquet **UDP** de 11 octets pour la requête d'informations:
   - `BYTE 0-3`: Signature "SAMP" (S A M P).
   - `BYTE 4-9`: Séquence de 6 octets arbitraires (généralement l'adresse IP de l'origine de la requête pour que le serveur reconnaisse le client).
   - `BYTE 10`: Identifiant de la requête 'i' (ASCII 105), indiquant que l'**ASI** souhaite des informations générales sur le serveur (hostname, joueurs, etc.).
      ```cpp
      // server_query.cpp (construction du paquet)
      void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
          memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
          packet = 'i'; // Requête d'information (Information)
      }
      ```
- **Structure de la réponse du serveur**: Lorsqu'un serveur SA-MP répond à une requête 'i', il envoie un paquet **UDP** contenant une séquence de données structurées, que l'**ASI** doit analyser:
   - **En-tête de la réponse:** Répétition de la signature "SAMP" et de la séquence de 6 octets du paquet de requête. L'**ASI** saute simplement ces `Constants::QUERY_PACKET_SIZE` octets initiaux.
   - **Passworded (`bool`):** Un octet indiquant si le serveur est protégé par un mot de passe. Lu, mais non utilisé.
   - **Players (`uint16_t`):** Le nombre de joueurs actuellement connectés au serveur.
   - **Max_Players (`uint16_t`):** Le nombre maximum de slots de joueurs que le serveur prend en charge.
   - **Hostname (chaîne préfixée par `uint32_t`):** Le nom convivial du serveur. Le paquet inclut un `uint32_t` pour indiquer la longueur de la chaîne de hostname, suivi des octets de la chaîne réelle.
   - **Autres champs:** Le protocole SA-MP continue avec "gamemode" et "language", également préfixés par la taille. L'**ASI** lit et saute ces champs pour se concentrer sur les données essentielles de `Players`, `Max_Players` et `Hostname`.

   La lecture de ces champs est effectuée avec les fonctions auxiliaires `Read_From_Span` et `Read_String_From_Span`, qui garantissent que l'**ASI** ne lit pas d'octets hors limites du buffer et gère correctement la lecture des types de données de longueur fixe et variable (chaînes).
   ```cpp
   // server_query.cpp (analyse de la réponse)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       // ... (Vérification de la taille et sous-span pour les données) ...
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Lit le booléen 'passworded'
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false; // Lit 'Players'

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false; // Lit 'Max_Players'

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false; // Lit 'Hostname'
   
       // Les champs 'Gamemode' et 'Language' sont implicitement "sautés"
       // par l'appel suivant de Read_String_From_Span
       // pour déplacer le span au-delà de leurs données dans le buffer.
       uint32_t length_placeholder; // Variable temporaire pour stocker la taille.

       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Lit la taille du gamemode

       if (data_span.size() < length_placeholder)
           return false; // Vérifie les limites

       data_span = data_span.subspan(length_placeholder); // Saute les données du gamemode
   
       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Lit la taille du language

       if (data_span.size() < length_placeholder)
           return false; // Vérifie les limites

       data_span = data_span.subspan(length_placeholder); // Saute les données du language
   
       return true;
   }
   ```
   Dans l'exemple ci-dessus, la logique `data_span = data_span.subspan(length_placeholder);` est une manière efficace de "sauter" le nombre d'octets lus par une chaîne dont le contenu n'est pas nécessaire pour le Rich Presence.

### Avantages du SA-MP Rich Presence

Le **SA-MP Rich Presence** améliore considérablement l'expérience tant pour les joueurs que pour les administrateurs de serveurs, offrant des avantages remarquables:

1. **Pour les joueurs:**
   - **Visibilité sans effort:** Partagez automatiquement votre statut de jeu sur Discord avec vos amis, montrant exactement où vous jouez.
   - **Informations riches:** Accédez immédiatement aux détails du serveur (nom, nombre de joueurs, IP, logo personnalisé) directement sur Discord, éliminant le besoin de vérifier ces informations ailleurs.
   - **Accès direct à la communauté:** Découvrez et accédez rapidement aux réseaux sociaux du serveur via les icônes rotatives dans la présence Discord, facilitant l'intégration dans des communautés vibrantes.
   - **Connexion rapide avec les amis:** Invitez ou rejoignez le même serveur que vos amis en un seul clic, grâce à la fonctionnalité de bouton "Join".
   - **Expérience toujours active:** Le système de mise à jour automatique garantit que vous utilisez toujours la version la plus optimisée et fonctionnelle de l'**ASI**.
2. **Pour les serveurs:**
   - **Marketing viral naturel:** La présence sur Discord de vos joueurs agit comme un panneau d'affichage numérique, faisant la promotion de votre serveur auprès d'une audience organique (les amis des joueurs) 24 heures sur 24.
   - **Identité visuelle forte:** Un logo personnalisé et la rotation des liens sociaux permettent à votre serveur de se démarquer et de projeter une image professionnelle et moderne dans l'environnement Discord.
   - **Engagement accru:** Facilitez le chemin pour que les nouveaux et anciens joueurs se connectent avec vos plateformes sociales, renforçant votre communauté et l'engagement hors jeu.
   - **Recrutement facilité:** La fonctionnalité "Join" simplifie le processus pour les nouveaux joueurs, éliminant les barrières et encourageant l'expérimentation.
   - **Données cohérentes:** Grâce à l'intégration avec l'**SPC Integration API**, l'affichage des informations est unifié et mis à jour de manière centralisée, garantissant que la marque et les contacts de votre serveur sont toujours corrects.

## Licence

Cet ASI est protégé sous la Licence Apache 2.0, qui permet:

- ✔️ Utilisation commerciale et privée
- ✔️ Modification du code source
- ✔️ Distribution du code
- ✔️ Concession de brevets

### Conditions

- Conserver la notice de droits d'auteur
- Documenter les modifications significatives
- Inclure une copie de la licence Apache 2.0

Pour plus de détails sur la licence: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Tous droits réservés**