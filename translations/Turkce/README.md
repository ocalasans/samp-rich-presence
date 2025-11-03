# SA-MP Rich Presence

**SA-MP Rich Presence**, **SA-MP (San Andreas Multiplayer)** için bir **ASI**'dir ve Discord durumunuzu sunucu bilgileriyle otomatik olarak günceller. **ASI**, bir SA-MP sunucusuna bağlandığınızda oyuna enjekte edilir ve sunucu bilgilerini gösterir.

## Diller

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)

## İçindekiler

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Diller](#diller)
  - [İçindekiler](#i̇çindekiler)
  - [Özellikler](#özellikler)
    - [Discord Rich Presence](#discord-rich-presence)
    - [Otomatik Güncelleme Sistemi](#otomatik-güncelleme-sistemi)
  - [Gereksinimler](#gereksinimler)
  - [Kurulum](#kurulum)
  - [AlderGrounds Integration API ile Entegrasyon](#aldergrounds-integration-api-ile-entegrasyon)
    - [Bilgi Nasıl Elde Edilir ve Kullanılır:](#bilgi-nasıl-elde-edilir-ve-kullanılır)
  - [Sunucu Geliştiricileri İçin](#sunucu-geliştiricileri-i̇çin)
    - [Sunucunuza AlderGrounds Integration’ı Nasıl Uygularsınız:](#sunucunuza-aldergrounds-integrationı-nasıl-uygularsınız)
  - [Detaylı Teknik Mimari](#detaylı-teknik-mimari)
      - [Ana Sistem (`main.cpp`)](#ana-sistem-maincpp)
      - [Güncelleme Sistemi (`asi_update.hpp`)](#güncelleme-sistemi-asi_updatehpp)
      - [Discord Yöneticisi (`discord_manager.cpp`)](#discord-yöneticisi-discord_managercpp)
      - [Sunucu Yöneticisi (`server_manager.cpp`)](#sunucu-yöneticisi-server_managercpp)
      - [Ağ Sistemi (`samp_network.cpp`)](#ağ-sistemi-samp_networkcpp)
      - [Sunucu Sorgulama (`server_query.cpp`)](#sunucu-sorgulama-server_querycpp)
      - [URL Yöneticisi (`url_manager.cpp`)](#url-yöneticisi-url_managercpp)
    - [Kod Yapısı](#kod-yapısı)
      - [Genel Sabitler (`constants.hpp`)](#genel-sabitler-constantshpp)
      - [Veri Yapıları (`server_types.hpp`)](#veri-yapıları-server_typeshpp)
      - [Gizli Bilgilerin Şifrelenmesi (`secrets.hpp`)](#gizli-bilgilerin-şifrelenmesi-secretshpp)
      - [Genel Yardımcı Fonksiyonlar (`utils.hpp`)](#genel-yardımcı-fonksiyonlar-utilshpp)
    - [Hata Yönetimi ve Dayanıklılık](#hata-yönetimi-ve-dayanıklılık)
    - [Komut Satırı İşleme Sistemi](#komut-satırı-i̇şleme-sistemi)
      - [Komut Satırı Ayrıştırıcısı (`command_line_parser.cpp`)](#komut-satırı-ayrıştırıcısı-command_line_parsercpp)
    - [SA-MP İletişim Protokolü](#sa-mp-i̇letişim-protokolü)
      - [Protokol Uygulaması](#protokol-uygulaması)
    - [SA-MP Rich Presence’ın Avantajları](#sa-mp-rich-presenceın-avantajları)
  - [Lisans](#lisans)
    - [Koşullar:](#koşullar)

## Özellikler

### Discord Rich Presence

**Discord Rich Presence**, uygulamaların kullanıcının ne yaptığını Discord profilinde detaylı bir şekilde göstermesini sağlayan bir özelliktir. **SA-MP Rich Presence** durumunda, aşağıdaki bilgiler gösterilir:

- **Sunucu Adı (Hostname):** Sunucunun ana adı.
- **Oyuncu Adı:** Oyundaki mevcut takma adınız.
- **Oyuncu Sayısı:** Çevrimiçi oyuncu sayısı ve izin verilen maksimum sayı.
- **Sunucu Adresi:** Sunucunun IP’si ve portu, kolay tanımlama için.
- **Özel Sunucu Resmi:** Varsa, sunucuya özgü bir logo.
- **Dönen Sosyal İkon:** Sunucunun sosyal medya bağlantılarını temsil eden küçük ikonlar (web sitesi, Discord, YouTube, Instagram, Facebook, TikTok), otomatik olarak değişir.
- **Oyun Süresi:** Mevcut sunucuya bağlı olduğunuz süre.
- **Bağlantı Durumu:** Çevrimiçi bir sunucuda mısınız yoksa "Idle" (boşta) durumunda mısınız, bunu belirtir.
- **"Join" (Katıl) Düğmesi:** Arkadaşlarınızın oynadığınız sunucuya doğrudan katılmasını sağlar.

### Otomatik Güncelleme Sistemi

**ASI**, bir güncelleme kontrol sistemi içerir. Oyun başlatıldığında, projenin resmi GitHub deposunda yeni sürümler olup olmadığını kontrol eder. Bir güncelleme tespit edilirse, kullanıcıya dostça bir bildirim gösterilir ve şu seçenekler sunulur:

1. Doğrudan tarayıcıyı açarak indirme için releases sayfasına gitme.
2. Güncelleme yapmadan devam etme, mevcut oturum için **ASI**’yi devre dışı bırakma seçeneğiyle.

Bu özellik, kullanıcıların her zaman en son iyileştirmelere, hata düzeltmelerine ve yeni özelliklere erişmesini sağlayarak güncel ve kesintisiz bir deneyim sunar.

## Gereksinimler

- SA-MP istemcisi (eğer yoksa: [clients-samp](https://github.com/aldergrounds /

clients-samp)).
- Discord Masaüstü uygulaması.
- Windows İşletim Sistemi.
- Visual C++ Runtime.
- Grand Theft Auto: San Andreas’ınıza kurulmuş bir [ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader).

## Kurulum

1. GitHub’daki [releases](https://github.com/ocalasans/samp-rich-presence/releases) bölümünden en son derlenmiş **ASI** sürümünü indirin.
2. İndirdikten sonra `.asi` dosyasını bulun.
3. İndirilen `.asi` dosyasını GTA San Andreas’ın kök klasörüne kopyalayın (`gta_sa.exe` dosyasının bulunduğu yer).
4. Oyunu SA-MP istemcisi üzerinden başlatın.
5. Bir sunucuya bağlandığınızda **ASI** otomatik olarak yüklenecek ve başlatılacak, Discord durumunuzu güncelleyecektir.

## AlderGrounds Integration API ile Entegrasyon

**SA-MP Rich Presence**, **AlderGrounds Integration API** ile entegrasyonu sayesinde Discord’daki bilgi gösterimini önemli ölçüde geliştirir. Sadece temel sorgu verilerine dayanmak yerine, **ASI** artık bu API ile doğrudan etkileşime girerek sunucunun görsel ve sosyal bilgilerini alır. **AlderGrounds Integration** hakkında daha fazla bilgi için resmi depoyu ziyaret edin: [aldergrounds/integration](https://github.com/aldergrounds/integration).

### Bilgi Nasıl Elde Edilir ve Kullanılır:

1. **Adres Formatlama:** Oyuncu bir sunucuya bağlandığında (IP ve Port), **ASI** bu adresi (`IP:PORT`) kullanıcı dostu bir formata (`IP-PORT`) dönüştürerek API isteğine hazırlar.
2. **API’ye İstek:** **ASI**, formatlanmış IP ve portu içeren bir `GET` isteğini **AlderGrounds Integration API**’nin endpoint’ine gönderir. İstek URL’sinin dahili olarak nasıl oluşturulduğuna bir örnek:
   ```cpp
   // url_manager.cpp’den uyarlanmış bölüm
   auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
   std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
   path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   const std::string json_data = Request_API_Data(path);
   ```
3. **JSON Yanıtının İşlenmesi:** API, JSON formatında bir yanıt döndürür. **ASI**, bu yanıtı ayrıştırmak ve ilgili verileri çıkarmak için [nlohmann/json](https://github.com/nlohmann/json) kütüphanesini kullanır.
   ```json
   // AlderGrounds Integration API’den Yanıt Yapısı Örneği
   {
       "success": true,
       "data": {
           "public": {
               "logo": "https://url.do.seu.logo/server_logo.png",
               "website": "https://seu-site.com",
               "discord": "https://discord.gg/seuservidor",
               "youtube": "https://youtube.com/seucanal"
               // ...diğer sosyal medya bağlantıları
           }
       }
   }
   ```
4. **Veri Çıkarımı:**
   - **Sunucu Logosu:** Sunucunun logosunun URL’si (`public` bölümündeki `logo`), **Discord Rich Presence**’ta ana görsel (large image) olarak kullanılır. Bu, her sunucu için özgün ve özelleştirilebilir bir görsel kimlik sağlar.
   - **Sosyal Bağlantılar:** Önceden tanımlanmış sosyal medya listesi (web sitesi, Discord, YouTube, Instagram, Facebook, TikTok) JSON yanıtında kontrol edilir. Geçerli bir değere sahip her sosyal medya için, ağın adı ve ilgili bağlantısı saklanır.
5. **Discord’da Gösterim:** `Server_Manager`, çıkarılan sosyal bağlantılar listesini kullanarak dinamik bir rotasyon uygular. Her 30 saniyede bir, sunucunun sosyal medya ağlarından birine ait farklı bir ikon, Discord durumunda "small image" (küçük görsel) olarak gösterilir ve bağlantı veya platform adı ile birlikte, sunucu topluluklarının keşfedilmesini teşvik eder.

## Sunucu Geliştiricileri İçin

Sunucunuzu [AlderGrounds Integration](https://github.com/aldergrounds/integration) ile entegre etmek, SA-MP topluluğunuzun görünürlüğünü ve katılımını artıran bir dizi doğrudan ve dolaylı avantaj sağlar. Sunucu geliştiricisiyseniz, stratejik avantajları düşünün:

1. **Markanızı Güçlendirin:**
   - **Öncelikli Görünürlük:** Sunucunuzun özelleştirilmiş logosu, yalnızca bir metin değil, tüm oyuncuların Discord profillerinde öne çıkan canlı ve dikkat çekici bir görsel olarak gösterilir. Bu, organik ve sürekli bir markalaşma yöntemidir.
   - **Profesyonel Görünüm:** Logo ve sosyal medya bağlantılarının iyi temsil edilmesi, sunucunuzun daha köklü ve güvenilir bir imaj yansıtmasını sağlar, daha fazla ilgi çeker ve potansiyel yeni oyuncuları cezbeder.
2. **Topluluğunuzu Genişletin:**
   - **Erişim Kanallarını Çoğaltın:** Sosyal ikon rotasyonu ile sunucunuzun resmi web sitesi, Discord, YouTube, Instagram, Facebook veya TikTok sayfalarını tanıtabilirsiniz. **Discord Rich Presence**’taki her ikon ve bağlantı, ilgilenenleri doğrudan topluluğunuzun aktif olduğu platformlara yönlendirir.
   - **Anında Bağlantı:** Discord üzerinden "Join" özelliği, oyuncularınızın arkadaşlarının tek bir tıkla sunucunuza katılmasını sağlar, giriş engellerini azaltır ve yeni üyeleri teşvik eder.
3. **Kolaylaştırılmış İçerik Güncelleme:**
   - [AlderGrounds Integration](https://github.com/aldergrounds/integration) kullanıldığında, sunucu logosu veya sosyal medya bağlantılarında yapılan herhangi bir güncelleme, **ASI** kullanan oyuncular için otomatik olarak yansıtılır, **ASI**’nin güncellenmesine gerek kalmadan. Bu, bilgilerin her zaman doğru ve güncel olmasını sağlar.

### Sunucunuza AlderGrounds Integration’ı Nasıl Uygularsınız:

1. **AlderGrounds Integration Eklentisi:** Sunucunuzda [AlderGrounds Integration](https://github.com/aldergrounds/integration) eklentisinin kurulu ve doğru şekilde yapılandırılmış olması gerekir. Bu eklenti, sunucunuzun bilgilerini **AlderGrounds** veri listesine gönderen bir köprüdür ve bu bilgiler **AlderGrounds Integration API** tarafından genel kullanıma sunulur.
2. **Yapılandırma:** [AlderGrounds Integration](https://github.com/aldergrounds/integration) deposundaki talimatları takip ederek:
   - Sunucunuzun logosunun URL’sini `logo` parametresiyle ayarlayın.
   - Sosyal medya parametrelerini (`discord`, `website`, `youtube`, vb.) platformlarınızın geçerli bağlantılarıyla yapılandırın.
3. **Otomatik Güncelleme:** Bilgiler eklentide yapılandırıldığında, **SA-MP Rich Presence** bunları otomatik olarak algılar ve gösterir. Oyuncunun yalnızca ilk **ASI** kurulumunu yapması gerekir.

Sunucunuzu [AlderGrounds Integration](https://github.com/aldergrounds/integration) ile entegre ederek, oyuncularınızın deneyimini geliştirmenin yanı sıra topluluğunuz için önemli bir büyüme ve katılım fırsatı yaratırsınız.

## Detaylı Teknik Mimari

**SA-MP Rich Presence**, belirli görevlere odaklanmış modüler bir mimariye sahiptir. Kod tabanı, yüksek performans, güvenlik ve verimlilik sağlamak için modern C++ standartlarıyla (C++17 ve C++20) hizalanmıştır ve `std::string_view`, `std::span` ve hareket semantiği kullanır.

#### Ana Sistem (`main.cpp`)

**ASI**’nin kalbi `main.cpp`’dedir ve uygulamanın yaşam döngüsünü, DLL olarak başlatılmasından sürekli güncelleme döngüsüne ve zarif kapanışına kadar yönetir.

- **`DllMain`**: **ASI**’nin işletim sistemi tarafından yüklendiğinde giriş noktası.
   ```cpp
   // DllMain (yapıyı vurgulamak için sadeleştirilmiş)
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
   Bu fonksiyon, oyunun işlemine bağlandığında (`DLL_PROCESS_ATTACH`), gereksiz kütüphane çağrılarını engeller (`DisableThreadLibraryCalls`) ve **ASI** mantığını asenkron olarak çalıştıran yeni bir iş parçacığı (`Main_Update_Thread`) oluşturur, böylece oyunun engellenmesini önler. Kapanış sırasında (`DLL_PROCESS_DETACH`), kaynakları serbest bırakmak için `Shutdown_Managers()` çağrılır.
- **`Main_Update_Thread`**: **ASI**’nin ruhu, kendi iş parçacığında çalışır.
   ```cpp
   // Main_Update_Thread (anahtar bölüm)
   DWORD WINAPI Main_Update_Thread(LPVOID) {
       // 1. Güncelleme Kontrolü
       if (Asi_Update::Check_For_Update())
           return 0; // Kullanıcı devre dışı bırakmayı seçerse, sonlandırılır.
   
       // 2. Ağ Başlatma (Winsock)
       WSAData wsa_data;

       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
   
       // 3. Sunucu ve Discord Yöneticilerini Başlatma
       Initialize_Managers();
   
       // 4. Ana Güncelleme Döngüsü
       while (is_running && v_server_manager && v_discord_manager) {
           v_server_manager->Update(); // Sunucu sorgulama, AlderGrounds API, vb.
           v_discord_manager->Update_Presence( // Discord durumunu günceller
               v_server_manager->Get_Server_Info(),
               v_server_manager->Get_Display_Social_Link(),
               v_server_manager->Get_Player_Name(),
               v_server_manager->Get_Current_Image_URL(),
               v_server_manager->Is_Connected());
   
           Discord_RunCallbacks(); // Discord RPC olaylarını işler
           std::this_thread::sleep_for(Constants::MAIN_LOOP_INTERVAL);
       }
   
       // 5. Kapanış (eğer yöneticiler varsa)
       if (v_discord_manager)
           v_discord_manager->Shutdown();

       WSACleanup(); // Winsock’u serbest bırakır

       return 0;
   }
   ```
   Bu fonksiyon önce güncellemeleri kontrol eder. Ardından Winsock ağ yığınını başlatır ve sunucu ile Discord yöneticilerinin örneklerini oluşturur. Kalıcı bir `while` döngüsü (`std::atomic<bool> is_running` ile güvenli kapanış için kontrol edilir), `Server_Manager::Update()` (veri toplama) ve `Discord_Manager::Update_Presence()` (Discord’a veri gönderme) çağrılarını koordine eder. `Discord_RunCallbacks()`, Discord’un Rich Presence olaylarını işlemesini sağlar. Döngü, kaynak optimizasyonu için `std::this_thread::sleep_for` ile periyodik olarak duraklatılır.

#### Güncelleme Sistemi (`asi_update.hpp`)

Bu hayati modül, kullanıcıların güncel kalmasını sağlamak için **ASI**’ye zeka katar.

- **`Check_For_Update()`**: Ana kontrol fonksiyonu.
   ```cpp
   // asi_update.hpp (Check_For_Update’den anahtar bölüm)
   inline bool Check_For_Update() {
       HINTERNET h_session = nullptr, h_connect = nullptr, h_request = nullptr;
       bool update_found_and_handled = false;
   
       try {
           h_session = WinHttpOpen(L"SA-MP Rich Presence Update/1.0", ...);
           // ... (GitHub API’sine Constants::UPDATE_API_PATH için GET isteği) ...
           std::string response_body;
           // ... (HTTP yanıtını okuma) ...
           nlohmann::json release_info = nlohmann::json::parse(response_body);
   
           std::string latest_tag = release_info["tag_name"].get<std::string>();
           // ... (versiyonları normalleştirme ve karşılaştırma için sscanf_s/sscanf kullanımı) ...
   
           if (latest_major > current_major || (latest_major == current_major && latest_minor > current_minor)) {
               update_found_and_handled = true;
               std::wstringstream message_stream;
               // ... (MessageBox mesajını hazırlar) ...
               int msgbox_result = MessageBoxW(NULL, message_stream.str().c_str(), L"SA-MP Rich Presence - Update Available", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
               
               if (msgbox_result == IDYES)
                   ShellExecuteW(NULL, L"open", Constants::UPDATE_RELEASES_URL, NULL, NULL, SW_SHOWNORMAL);
           }
       }
       catch (const std::exception&) { /* Hata yönetimi */ }
   
       // ... (WinHttp tutamaçlarını kapatma) ...
       return update_found_and_handled;
   }
   ```
   Ağ istekleri için **WinHTTP API**’sini kullanarak, `Check_For_Update`, projenin GitHub deposundaki `/releases/latest` uç noktasına bir `GET` isteği yapar. Yanıt, JSON formatında `nlohmann/json` kütüphanesiyle ayrıştırılır. En son sürüm (`tag_name`), **ASI**’nin derlenmiş sürümüyle sayısal olarak karşılaştırılır. Yeni bir sürüm tespit edilirse, bir iletişim kutusu (`MessageBoxW`), kullanıcıya `ShellExecuteW` aracılığıyla indirme sayfasına gitme seçeneği sunar. Sürecin tamamı, ağ veya ayrıştırma hatalarının oyunun başlamasını engellememesi için bir `try-catch` bloğunda kapsüllenir.

#### Discord Yöneticisi (`discord_manager.cpp`)

`Discord_Manager` sınıfı, **Discord RPC** kütüphanesiyle etkileşimleri soyutlar, bağlantı başlatma ve kullanıcı durumunu güncelleme işlemlerini yönetir.

- **`Initialize()`**: Discord ile iletişimi kurar.
   ```cpp
   // discord_manager.cpp (Initialize’den anahtar bölüm)
   void Discord_Manager::Initialize() noexcept {
       DiscordEventHandlers handlers;
       memset(&handlers, 0, sizeof(handlers)); // Başlatmayı garanti eder
       
       // Uygulama kimliği burada desofuske edilir
       auto app_id_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_Discord_App_ID());
       Discord_Initialize(app_id_accessor.Get(), &handlers, 1, nullptr);
   
       start_timestamp_ = time(nullptr); // Oturum başlangıcını kaydeder
   }
   ```
   `Discord_Initialize` çağrısı, `secrets.hpp`’den güvenli bir şekilde alınan `DISCORD_APP_ID` ile kritik öneme sahiptir. `start_timestamp_`, Discord durumunda oyun süresini hesaplamak için burada tanımlanır.
- **`Update_Presence()`**: Discord Rich Presence’ı güncelleyen hayati fonksiyon.
   ```cpp
   // discord_manager.cpp (Update_Presence’den anahtar bölüm)
   void Discord_Manager::Update_Presence(const Server_Information& server_info, const server_types::Social_Link& social_link, const std::string_view player_name, const std::string_view current_image, const bool is_connected) noexcept {
       DiscordRichPresence discord_presence;
       memset(&discord_presence, 0, sizeof(discord_presence));
   
       discord_presence.startTimestamp = start_timestamp_;
       discord_presence.largeImageKey = current_image.data(); // Sunucu logosu
   
       if (is_connected) {
           discord_presence.details = server_info.Hostname.c_str();
           discord_presence.state = player_name.data();
           discord_presence.largeImageText = server_info.Server_Address.c_str(); // IP:Port
           discord_presence.partySize = server_info.Players;
           discord_presence.partyMax = server_info.Max_Players;
           discord_presence.joinSecret = server_info.Server_Address.c_str(); // "Join" düğmesini etkinleştirir
   
           // Dönen sosyal ikonu yönetir
           if (!social_link.first.empty()) {
               current_small_image_key_ = Constants::SOCIAL_ICON_BASE_URL;
               current_small_image_key_ += social_link.first; // Ör: "discord.png"
               current_small_image_key_ += ".png";
               discord_presence.smallImageKey = current_small_image_key_.c_str();
               discord_presence.smallImageText = social_link.second.c_str(); // Fareyle üzerine gelindiğinde görünen metin (bağlantı/ad)
           }
       }
       else {
           discord_presence.details = "SA-MP"; // "Idle" durumu
           discord_presence.state = "Idle";
           discord_presence.largeImageText = "San Andreas Multiplayer";
           // smallImageKey ve smallImageText boş kalır
       }
   
       Discord_UpdatePresence(&discord_presence);
   }
   ```
   Bağlantı durumuna bağlı olarak `DiscordRichPresence` yapısını doldurur. `is_connected` doğruysa, sunucu adı, oyuncu sayısı, IP ve oyuncu adı gösterilir. `largeImageKey`, sunucunun ana görselini tanımlar. Özellikle, `joinSecret`, arkadaşların doğrudan bağlanmasını sağlar ve `smallImageKey` (sağlanan `social_link`’e göre dinamik olarak oluşturulur), dönen sosyal ikonları gösterir. "Idle" durumunda, durum basitleştirilir. Son olarak, `Discord_UpdatePresence`, verileri Discord’a gönderir.

#### Sunucu Yöneticisi (`server_manager.cpp`)

`Server_Manager`, bağlantı durumunu, sunucu ve **AlderGrounds Integration API** sorgularını yönetir ve hangi bilgilerin ne zaman gösterileceğine karar verir.

- **`Update()`**: Veri toplama için ana yaşam döngüsü.
   ```cpp
   // server_manager.cpp (Update’den anahtar bölüm)
   void Server_Manager::Update() {
       const auto now = std::chrono::steady_clock::now();
   
       if (server_query.Query(live_server_data)) { // SA-MP sorgusuyla veri almayı dener
           if (!connection_status) { // Yeni bağlantı/yeniden bağlantı durumunda
               connection_status = true;
               Fetch_API_Data(); // API’den logo ve sosyal bağlantıları çeker
           }
           
           last_successful_query = now;
   
           // Discord’da gösterilecek verileri günceller
           display_server_data.Hostname = live_server_data.Hostname;
           display_server_data.Players = live_server_data.Players;
           display_server_data.Max_Players = live_server_data.Max_Players;
           display_server_data.Server_Address = server_ip + ":" + std::to_string(server_port);
   
           if (now - last_api_update > Constants::IMAGE_UPDATE_INTERVAL)
               Fetch_API_Data(); // Belirtilen süre geçtikten sonra API’yi tekrar sorgular
   
           if (now - last_social_rotation > Constants::SOCIAL_UPDATE_INTERVAL)
               Rotate_Social_Link(); // Sosyal ikonu döndürür
       }
       else { // Sorgu başarısız olursa
           if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
               connection_status = false; // Zaman aşımından sonra bağlantı kesilir
               display_image_url = Constants::DEFAULT_IMAGE;
               display_server_data = {}; // Verileri temizler
               current_display_social = {}; // Sosyal bağlantıları temizler
           }
       }
   }
   ```
   `Update` fonksiyonu, sunucuya sorgu yapmayı dener. Başarılı olursa, `live_server_data` ve `display_server_data`’yı günceller. Koşullu olarak, `Fetch_API_Data()`’yı (yeni bağlantı veya `IMAGE_UPDATE_INTERVAL` geçtiğinde) ve `Rotate_Social_Link()`’ü (`SOCIAL_UPDATE_INTERVAL`) çağırır. Sorgular 15 saniyeden fazla başarısız olursa, bağlantı durumu kaybolur ve gösterilen bilgiler sıfırlanır.
- **`Fetch_API_Data()`**: Görsel ve sosyal verileri almakla sorumludur.
   ```cpp
   // server_manager.cpp (Fetch_API_Data’dan anahtar bölüm)
   void Server_Manager::Fetch_API_Data() {
       display_image_url = url_manager.Get_Image_URL_And_Populate_Socials(server_ip, server_port, live_server_data);
       last_api_update = std::chrono::steady_clock::now();
       current_social_index_ = 0; // Yeni API çekiminden sonra indeksi sıfırlar
       Rotate_Social_Link(); // Hemen bir sosyal ikonun gösterilmesini sağlar
   }
   ```
   Bu fonksiyon, `URL_Manager` ile koordineli çalışarak logo ve sosyal bağlantıları API’den çeker, `display_image_url`’yi günceller ve `live_server_data` içindeki `Social_Links`’i doldurur. Sosyal rotasyon indeksini sıfılar ve ilk ikonun gösterilmesi için `Rotate_Social_Link()`’ü çağırır.
- **`Rotate_Social_Link()`**: Sosyal ikonları döndürme mantığı.
   ```cpp
   // server_manager.cpp (Rotate_Social_Link’ten anahtar bölüm)
   void Server_Manager::Rotate_Social_Link() {
       if (!live_server_data.Social_Links.empty()) {
           if (current_social_index_ >= live_server_data.Social_Links.size())
               current_social_index_ = 0; // Döngüyü yeniden başlatır
   
           current_display_social = live_server_data.Social_Links[current_social_index_];
           current_social_index_ = (current_social_index_ + 1) % live_server_data.Social_Links.size();
       }
       else
           current_display_social = {}; // Sosyal bağlantı yoksa temizler
       
       last_social_rotation = std::chrono::steady_clock::now();
   }
   ```
   Bu basit fonksiyon, `live_server_data.Social_Links` listesinden bir sonraki `Social_Link`’i döngüsel olarak seçer ve `current_display_social`’a kaydeder, böylece `Discord_Manager` bunu kullanabilir.

#### Ağ Sistemi (`samp_network.cpp`)

`Samp_Network` sınıfı, SA-MP sorguları için soket açma ve yönetme işlemlerini gerçekleştiren düşük seviyeli **UDP** iletişimini uygular. Artık daha iyi kaynak yönetimi için yapıcılar ve hareket operatörleri sunar.

- **`Initialize()`**: **UDP** iletişimi için soketi kurar.
   ```cpp
   // samp_network.cpp (Initialize’den anahtar bölüm)
   bool Samp_Network::Initialize(const std::string_view ip, const int port) noexcept {
       if (network_socket != INVALID_SOCKET)
           closesocket(network_socket); // Mevcut soketi kapatır
   
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       if (network_socket == INVALID_SOCKET)
           return false;
   
       const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
       setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
   
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(static_cast<u_short>(port));
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr); // IPv4 desteği
       return true;
   }
   ```
   Soketi başlatır, gönderme ve alma işlemleri için zaman aşımlarını ayarlar ve hedef sunucunun IP ve portuyla `sockaddr_in` yapısını yapılandırır, IP dönüşümü için `inet_pton` kullanır.
- **`Send_Query()`**: Sorgu paketini gönderir ve yanıtı alır.
   ```cpp
   // samp_network.cpp (Send_Query’den anahtar bölüm)
   bool Samp_Network::Send_Query(const std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept {
       // UDP paketini gönderir
       if (sendto(network_socket, query_packet.data(), static_cast<int>(query_packet.size()), 0, reinterpret_cast<const sockaddr*>(&server_address), sizeof(server_address)) < 0)
           return false;
   
       sockaddr_in from_address;
       int address_length = sizeof(from_address);
       // Yanıtı alır
       received_bytes = recvfrom(network_socket, response_buffer.data(), static_cast<int>(response_buffer.size()), 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);
   
       return received_bytes > Constants::QUERY_PACKET_SIZE;
   }
   ```
   Bu yöntem, `query_packet`’i (tampon güvenliği için `std::span` olarak geçirilir) sunucuya gönderir. Ardından `response_buffer`’da yanıt almayı dener. İşlemin başarılı olup olmadığını ve sorgu paketinden daha fazla bayt alınıp alınmadığını belirtir.

#### Sunucu Sorgulama (`server_query.cpp`)

`Server_Query` sınıfı, SA-MP’nin bilgi sorgu protokolü (`'i'`) için özelleşmiştir ve **UDP** yanıtlarından temel sunucu bilgilerini (oyuncular, sunucu adı) çıkarır.

- **`Query()`**: Sorgu denemelerini yönetir.
   ```cpp
   // server_query.cpp (Query’den anahtar bölüm)
   bool Server_Query::Query(Server_Information& server_data) noexcept {
       for (int attempt = 0; attempt < Constants::MAX_RETRY_ATTEMPTS; ++attempt) {
           if (Try_Query(server_data))
               return true; // Sorgu başarılı
   
           if (attempt < Constants::MAX_RETRY_ATTEMPTS - 1)
               // Yeniden denemeden önce kısa bir duraklama, ağ taşmasını önler
               std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)));
       }

       return false; // Tüm denemeler başarısız
   }
   ```
   `MAX_RETRY_ATTEMPTS` ile yeniden deneme stratejisi ve ağ yükünü azaltmak için artan zamanlı bir *back-off* uygular. Her denemede `Try_Query`’i çağırır.
- **`Assemble_Query_Packet()`**: SA-MP sorgu paketini oluşturur.
   ```cpp
   // server_query.cpp (Assemble_Query_Packet’ten anahtar bölüm)
   void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
       memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
       packet = 'i'; // Bilgi sorgusu
   }
   ```
   SA-MP’nin bilgi sorgusu (`'i'`) için standart paket oluşturulur, "SAMP" imzasını ve 'i' baytını içerir.
- **`Parse_Response()`**: Sunucudan gelen ikili yanıtı ayrıştırır.
   ```cpp
   // server_query.cpp (Parse_Response’tan anahtar bölüm)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       if (response.size() <= Constants::QUERY_PACKET_SIZE) 
           return false;
   
       auto data_span = response.subspan(Constants::QUERY_PACKET_SIZE); // Başlığı atlar
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Kullanılmasa da okunur
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false;

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false;

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false;
   
       // Not: Gamemode ve Language, Read_String_From_Span tarafından otomatik olarak atlanır
       // eğer paket daha fazla veri içeriyorsa.
       // Diğer alanlar gerekiyorsa: Read_String_From_Span(data_span, string_variable);
       return true;
   }
   ```
   Bu yöntem, `response_buffer`’dan verileri güvenli bir şekilde okur (`std::span` ve `Read_From_Span` ile `Read_String_From_Span` yardımcı fonksiyonlarını kullanarak). Oyuncu sayısı, maksimum oyuncu sayısı ve sunucu adını çıkararak `Server_Information` yapısını doldurur. Kullanılmayan alanlar (şifre koruması gibi) okunur ama yoksayılır, "gamemode" ve "language" gibi diğer alanlar gerektiğinde atlanır.
- **Yardımcı Okuma Fonksiyonları:**
   ```cpp
   // server_query.hpp (okuma yardımcılarından parçalar)
   template<typename T>
   static bool Read_From_Span(std::span<const char>& s, T& value) noexcept;
   
   static bool Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept;
   ```
   `Read_From_Span`, sabit türleri (tamsayılar, boolean’lar) `std::span`’dan okur ve `span`’i ilerletir. `Read_String_From_Span`, bir stringin uzunluğunu (`uint32_t` olarak) ve ardından stringin kendisini okur, `span`’i de ilerletir. Bu, bayt ayrıştırmada güvenliği sağlar ve tampon sınırlarının dışına çıkmayı önler.

#### URL Yöneticisi (`url_manager.cpp`)

`URL_Manager` sınıfı, **AlderGrounds Integration API** ile HTTPS iletişimlerini yönetir ve **Discord Rich Presence**’ın yeni görsel ve sosyal özelliklerinin temel bir bileşenidir.

- **`Get_Image_URL_And_Populate_Socials()`**: API’den bilgi almak için üst düzey yöntem.
   ```cpp
   // url_manager.cpp (Get_Image_URL_And_Populate_Socials’ten anahtar bölüm)
   std::string URL_Manager::Get_Image_URL_And_Populate_Socials(const std::string& ip, const int port, Server_Information& server_info) {
       if (!session_handle)
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);
   
       auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
       std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
       path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   
       const std::string json_data = Request_API_Data(path); // HTTP isteği
   
       if (json_data.empty())
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE); // İstek hatası
   
       return Parse_API_Response(json_data, server_info); // Yanıtı ayrıştırır ve server_info’yu doldurur
   }
   ```
   IP ve portu alır, bunları parametre olarak içeren API URL’sini oluşturur. `Request_API_Data`’yı çağırarak JSON verilerini alır. Başarılı olursa, `Parse_API_Response`, logo URL’sini çıkarır ve `server_info`’daki sosyal bağlantıları doldurur.
- **`Request_API_Data()`**: API’ye HTTPS isteği yapar.
   ```cpp
   // url_manager.cpp (Request_API_Data’dan anahtar bölüm)
   std::string URL_Manager::Request_API_Data(const std::wstring& path) {
       auto api_host_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Host());
       const std::wstring wide_host = Utils::Convert_Utf8_To_Wide_String(api_host_accessor.Get());
       HINTERNET connect_handle = WinHttpConnect(session_handle, wide_host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
   
       if (!connect_handle) return "";
   
       HINTERNET request_handle = WinHttpOpenRequest(connect_handle, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
   
       if (!request_handle) return (WinHttpCloseHandle(connect_handle), "");
   
       // İsteği gönder, yanıtı al, 200 durumunu kontrol et, verileri döngüde oku
       // ... (WinHttpSendRequest, WinHttpReceiveResponse, WinHttpQueryHeaders, WinHttpReadData detayları) ...
       
       WinHttpCloseHandle(request_handle); WinHttpCloseHandle(connect_handle);
       return response_body; // JSON’u string olarak döndürür
   }
   ```
   Şifrelenmiş host’a bağlanır, `path` ile bir `GET` isteği açar ve gönderir. HTTP yanıtını işler, 200 OK durum kodunu kontrol eder ve tam yanıt gövdesini (JSON olması gerekir) okur. Başarı veya başarısızlık durumunda tüm WinHTTP tutamaçları serbest bırakılır.
- **`Parse_API_Response()`**: JSON stringini işleyerek verileri çıkarır.
   ```cpp
   // url_manager.cpp (Parse_API_Response’tan anahtar bölüm)
   std::string URL_Manager::Parse_API_Response(const std::string& json_content, Server_Information& server_info) {
       server_info.Social_Links.clear(); // Mevcut sosyal bağlantıları temizler
       try {
           const auto json = nlohmann::json::parse(json_content);
   
           if (json.value("success", false) && json.contains("data") && json["data"].contains("public")) {
               const auto& public_data = json["data"]["public"];
               const std::vector<std::string> social_keys = { "website", "discord", "youtube", "instagram", "facebook", "tiktok" };
               
               // Sosyal bağlantıları çıkarır ve doldurur
               for (const auto& key : social_keys) {
                   if (public_data.contains(key)) {
                       std::string value = public_data.value(key, "not-defined");

                       if (!value.empty() && value != "not-defined")
                           server_info.Social_Links.push_back({ key, value });
                   }
               }

               return public_data.value("logo", ""); // Logo URL’sini döndürür
           }
       }
       catch (const nlohmann::json::exception&) { /* Ayrıştırma hatasını işler */ }

       return ""; // Ayrıştırma başarısız
   }
   ```
   `nlohmann::json::parse` ile JSON stringini işlenebilir bir JSON nesnesine dönüştürür. `success`, `data`, `public` yapısında gezinir ve `logo`’yu (`display_image_url` olarak) çıkarır, ardından `server_info`’daki `Social_Links`’i önceden tanımlanmış anahtarlar üzerinden doldurur.

### Kod Yapısı

**SA-MP Rich Presence** projesi, açık bir dizin düzeniyle dikkatle organize edilmiştir; kaynak kodu (`src/`) ve harici kütüphaneler için bir alt dizin (`libraries/`) içerir. Dosya adlandırması, her sınıfın amacını netleştirmek için `_manager` veya `_network` kuralını takip eder. Çoğu başlık dosyası, C++ başlık dosyalarını belirtmek için `.hpp` uzantısını kullanır.

```
src/
├── libraries/               # Gerekli üçüncü taraf kütüphaneleri içerir
│   ├── Dralyxor/            # String şifreleme kütüphanesi
│   ├── Discord/             # Resmi Discord RPC kütüphanesi
│   └── nlohmann/            # JSON işleme kütüphanesi
├── asi_update.hpp           # Otomatik güncelleme sisteminin tanımı
├── command_line_parser.hpp  # Komut satırı ayrıştırıcısının tanımı
├── constants.hpp            # Projenin genel sabit tanımları
├── discord_manager.hpp      # Discord iletişim yöneticisinin tanımı
├── main.cpp                 # ASI’nin giriş noktası ve ana orkestratör
├── samp_network.hpp         # SA-MP sorguları için ağ yöneticisinin tanımı
├── secrets.hpp              # Gizli bilgilerin şifrelenmesi için tanımlar
├── server_manager.hpp       # Sunucu bilgisi yöneticisinin tanımı
├── server_query.hpp         # SA-MP sunucu sorgulama mantığının tanımı
├── server_types.hpp         # Sunucu veri yapılarının tanımları
├── url_manager.hpp          # AlderGrounds Integration API için URL yöneticisinin tanımı
└── utils.hpp                # Genel yardımcı fonksiyonlar (string dönüşümleri)
```

#### Genel Sabitler (`constants.hpp`)

Bu dosya, projenin tüm yapılandırmalarını ve değişmez değerlerini toplar ve global olarak erişilebilir hale getirir. `inline constexpr` kullanarak sabitlerin doğrudan derleyiciye sunulmasını sağlar, performansı optimize eder.

```cpp
// constants.hpp (bölüm)
namespace Constants {
    inline constexpr char ASI_VERSION[] = "1.1"; // Güncelleme sistemi için sürüm
    inline constexpr wchar_t UPDATE_API_HOST[] = L"api.github.com"; // Güncelleme API’si host’u
    inline constexpr char DEFAULT_IMAGE[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/default_logo.png"; // Varsayılan resim
    inline constexpr int QUERY_TIMEOUT_MS = 800; // Sorgu zaman aşımı (ms)
    inline constexpr std::chrono::seconds MAIN_LOOP_INTERVAL = std::chrono::seconds(1); // Ana döngü aralığı
}
```
API URL’leri, varsayılan resim yolları, ağ zaman aşımları ve **Discord Rich Presence** güncelleme aralıkları gibi önemli detaylar burada merkezileştirilmiştir. Aralıklar için `std::chrono::seconds` kullanımı, okunabilirliği artırır ve birim hatalarını önler.

#### Veri Yapıları (`server_types.hpp`)

Bu dosya, toplanan ve gösterilen verileri organize etmek için gerekli `struct`’ları ve `using`’leri tanımlar.

```cpp
// server_types.hpp (bölüm)
namespace server_types {
    using Social_Link = std::pair<std::string, std::string>; // (ağ adı, URL/değer) çifti
}

struct Server_Information {
    uint16_t Players{0};           // Mevcut oyuncu sayısı
    uint16_t Max_Players{0};       // Maksimum oyuncu kapasitesi
    std::string Hostname{};        // Sunucu adı
    std::string Server_Address{};  // Ör: "192.168.1.1:7777"

    std::vector<server_types::Social_Link> Social_Links{}; // Sunucunun sosyal bağlantıları
};
```
`Server_Information`, sunucu verilerini saklayan ana yapıdır. `std::vector<server_types::Social_Link> Social_Links`’in eklenmesi, API’den birden fazla sosyal medya bağlantısını çekme yeteneğini yansıtır ve `(ağ_adı, bağlantı)` çiftleri olarak organize edilir.

#### Gizli Bilgilerin Şifrelenmesi (`secrets.hpp`)

Bu dosya, **Discord Application ID** ve **AlderGrounds Integration API** adresleri gibi hassas bilgilerin tersine mühendislikten korunmasını sağlar.

```cpp
// secrets.hpp (bölüm)
#include "libraries/Dralyxor/dralyxor.hpp"

namespace Secrets {
    namespace {
        inline auto& Get_Obfuscated_Discord_App_ID() {
            static auto& dc_app_id_obfuscated = DRALYXOR_KEY("DISCORD_APP_ID", "YOUR_SECRET_KEY_HERE");

            return dc_app_id_obfuscated;
        }
        // ... (diğer şifrelenmiş sırlar) ...
    }
    namespace Detail {
        inline auto& Get_Discord_App_ID() {
            return Get_Obfuscated_Discord_App_ID();
        }
        // ... (şifresi çözülmüş sırları almak için genel erişimciler) ...
    }
}
```
[Dralyxor](https://github.com/ocalasans/dralyxor) kütüphanesi, derlenmiş ikili dosyada string literallerini şifrelemek için `DRALYXOR_KEY` makrosunu kullanır. `DRALYXOR_SECURE`, çalışma zamanında bu değerlerin şifresini çözmek için kullanılır ve statik anahtar çıkarımına karşı sağlam bir güvenlik katmanı ekler.

#### Genel Yardımcı Fonksiyonlar (`utils.hpp`)

Kod tekrarını önlemek için çeşitli modüllerde kullanılabilecek genel yardımcı fonksiyonları içerir.

```cpp
// utils.hpp (bölüm)
namespace Utils {
    inline std::string Convert_Wide_To_Utf8_String(const std::wstring_view wide_string) {
        // ... (WideCharToMultiByte kullanarak dönüşüm uygulaması) ...
    }

    inline std::wstring Convert_Utf8_To_Wide_String(const std::string_view narrow_string) {
        // ... (MultiByteToWideChar kullanarak dönüşüm uygulaması) ...
    }
}
```
`Convert_Wide_To_Utf8_String` ve `Convert_Utf8_To_Wide_String` fonksiyonları, Windows API’leriyle (UTF-16 kullanan) ve standart C++ işlemleriyle (genellikle UTF-8’den faydalanan) etkileşim için gereklidir. Bu fonksiyonlar, güvenli ve verimli dönüşüm için Windows API’lerini kullanır.

### Hata Yönetimi ve Dayanıklılık

**SA-MP Rich Presence**, ağ hataları, geçersiz girişler ve hizmet kesintilerini ele almak için birden fazla mekanizmayla dayanıklılık göz önünde bulundurularak tasarlanmıştır.

- **Ağ Zaman Aşımları ve Yeniden Denemeler:**
   - **Açık Zaman Aşımları:** `samp_network.cpp`’deki ağ soketleri, veri gönderimi ve alımı için zaman aşımlarını (`Constants::QUERY_TIMEOUT_MS`) yapılandırır ve programın yanıt vermeyen bir sunucuyu beklerken kilitlenmesini önler.
      ```cpp
      // samp_network.cpp (zaman aşımı yapılandırması)
      const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
      setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      ```
   - **Çoklu Sorgu Denemeleri:** `Server_Query`, başarısızlık durumunda `Constants::MAX_RETRY_ATTEMPTS` kadar sorgu yapar. Yeniden denemeler arasında ağ yükünü azaltmak için üssel bir *back-off* uygulanır (`std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)))`).
- **Sağlam Bağlantı Kesilmesi Yönetimi:**
   - **Zarif Durum Geçişi:** `server_manager.cpp`’de, bağlantı durumu (`connection_status`), tek bir sorgu hatasında hemen değişmez. Yanıt 15 saniye boyunca alınamazsa (`now - last_successful_query > std::chrono::seconds(15)`), durum `false`’a güncellenir. Bu, küçük paket kayıplarından dolayı Discord durumunda titremeyi önler.
      ```cpp
      // server_manager.cpp (bağlantı kesilmesi mantığı)
      else { // Sorgu başarısız olursa
          if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
              connection_status = false;
              display_image_url = Constants::DEFAULT_IMAGE;
              display_server_data = {};
              current_display_social = {};
          }
      }
      ```
   - **Görsel Yedekleme:** Bağlantı kesildiğinde, Discord durumu `Constants::DEFAULT_IMAGE`’e geri döner ve sunucu/sosyal veriler temizlenir, kullanıcıya bağlı olmadığının açık bir göstergesi sağlanır.
- **Geçersiz Girişlerin Yönetimi:**
   - **`command_line_parser.cpp`:** Port argümanını string’den tamsayıya dönüştürürken (`std::stoi`), `std::invalid_argument` (sayı değil) veya `std::out_of_range` (sayı çok büyük/küçük) hatalarını ele almak için bir `try-catch` bloğu kullanılır. Hata durumunda, varsayılan port korunur veya ayrıştırma kontrollü bir şekilde başarısız olur, kilitlenmeyi önler.
- **API Veri Alımında Dayanıklılık:**
   - **WinHTTP Hataları:** `url_manager.cpp`’deki tüm WinHTTP işlemleri, her adımda (`oturum açma, bağlanma, istek açma, gönderme/alma, veri okuma`) `null` tutamaçlar ve `false` dönüşleri için kontrol edilir, böylece kısmi hatalar yakalanır.
   - **HTTP Durum Kodları:** HTTP isteğinden sonra, `url_manager.cpp`, yalnızca `200 OK`’yi başarı olarak kabul eder ve sunucu veya ağ geçidi hata yanıtlarını atar.
   - **Güvenli JSON Ayrıştırma:** `url_manager.cpp`, `nlohmann::json::parse`’i bir `try-catch(const nlohmann::json::exception&)` bloğunda sarar. Bu, API’den gelen hatalı veya eksik JSON’ların çökmesine neden olmasını önler ve boş stringler veya varsayılan resmi döndürür.
- **Güvenli Güncelleme Mekanizmaları:**
   - **`asi_update.hpp`:** `Check_For_Update`’teki güncelleme kontrol süreci, `try-catch(const std::exception&)` bloğunda kapsüllenir. Bu, GitHub’un çevrimdışı olması, ağın kararsız olması veya JSON yanıtının geçersiz olması durumunda **ASI**’nin çökmesini önler ve oyunun yüklenmeye devam etmesine izin verir, güncelleme kontrolünü güvenli bir şekilde atlar.
   - **WinHTTP Tutamaç Yönetimi:** `asi_update.hpp` ve `url_manager.cpp`’deki `HINTERNET` tutamaçlarının serbest bırakılması, başarı ve başarısızlık yollarında dikkatle planlanır, kaynak sızıntılarını önler.

### Komut Satırı İşleme Sistemi

**SA-MP Rich Presence**, Grand Theft Auto: San Andreas oyununun komut satırından kritik bilgileri (sunucu IP’si, port ve oyuncu adı) çıkarır. Bu yöntem, oyunun başlatıldığı veya bir sunucuya bağlanıldığı anda **ASI**’nin en doğru ve ilgili verileri almasını sağlar.

#### Komut Satırı Ayrıştırıcısı (`command_line_parser.cpp`)

`Command_Line_Parser` sınıfı, işlemin tam komut satırı stringini analiz eder ve SA-MP tarafından kullanılan belirli parametreleri tanımlar ve çıkarır.

- **`Parse()`**: Komut satırı analizinin giriş noktası.
   ```cpp
   // command_line_parser.cpp (Parse’ten anahtar bölüm)
   bool Command_Line_Parser::Parse(const std::wstring_view command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       server_ip = Constants::DEFAULT_SERVER_IP; // Varsayılan değerler
       server_port = Constants::DEFAULT_SERVER_PORT;
   
       if (const auto ip_param = Parse_Parameter(command_line, L"-h"); !ip_param.empty())
           server_ip = Utils::Convert_Wide_To_Utf8_String(ip_param); // IP’yi çıkarır ve dönüştürür
   
       if (const auto port_param = Parse_Parameter(command_line, L"-p"); !port_param.empty()) {
           try {
               server_port = std::stoi(std::wstring(port_param)); // Portu çıkarır ve dönüştürür (hata yönetimi ile)
           }
           catch (const std::invalid_argument&) {}
           catch (const std::out_of_range&) {}
       }
   
       if (const auto name_param = Parse_Parameter(command_line, L"-n"); !name_param.empty())
           player_name = Utils::Convert_Wide_To_Utf8_String(name_param); // Adı çıkarır ve dönüştürür
   
       return !server_ip.empty() && server_port > 0 && !player_name.empty(); // Temel verilerin mevcut olduğunu doğrular
   }
   ```
   Komut satırını (`command_line`) verimli bir şekilde `std::wstring_view` olarak alır. `-h` (host/IP), `-p` (port) ve `-n` (oyuncu adı) ile ilişkili değerleri bulmak ve çıkarmak için `Parse_Parameter`’i kullanır. Çıkarılan değerler (`std::wstring_view`), `Utils::Convert_Wide_To_Utf8_String` kullanılarak `std::string`’e (UTF-8) dönüştürülür. Port için, dönüşüm hatalarını güvenli bir şekilde yönetmek için `std::stoi` etrafında bir `try-catch` bloğu kullanılır. Fonksiyon, temel parametrelerin (IP, geçerli port ve oyuncu adı) alındığını doğrulayarak `true` döndürür.
- **`Parse_Parameter()`**: Tek bir parametrenin çıkarılması için yardımcı fonksiyon.
   ```cpp
   // command_line_parser.cpp (Parse_Parameter’den anahtar bölüm)
   std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring_view command_string, const std::wstring_view parameter) {
       if (const size_t position = command_string.find(parameter); position != std::wstring_view::npos) {
           size_t value_start = position + parameter.length();
           value_start = command_string.find_first_not_of(L" \t", value_start); // Parametreden sonraki boşlukları atlar

           if (value_start == std::wstring_view::npos)
               return L""; // Parametre bulundu ama değer yok
   
           const size_t value_end = command_string.find(L' ', value_start); // Sonraki boşluğu bulur (değerin sonu)
           
           return std::wstring(command_string.substr(value_start, value_end - value_start)); // Değer alt stringini döndürür
       }

       return L""; // Parametre bulunamadı
   }
   ```
   `command_string` içinde `parameter` (`-h`, `-p`, `-n`) alt stringini bulur. Değerin başlangıç konumunu hesaplar, boşlukları/tab’leri atlar. Değerin sonunu (sonraki boşluk) belirler ve parametrenin değerine karşılık gelen alt stringi döndürür.

### SA-MP İletişim Protokolü

**ASI**, gerçek zamanlı önemli bilgileri çıkarmak için SA-MP sunucularıyla doğrudan **UDP** sorgu protokolünü kullanarak etkileşime girer. Bu iletişim, verimli ve ağ hatalarına dayanıklı olacak şekilde uygulanmıştır.

#### Protokol Uygulaması

`Server_Query` sınıfı, bu uygulamanın omurgasıdır ve paket gönderme ile yanıtların yorumlanmasını yönetir.

- **SA-MP Sorgu Paketi Yapısı (`'i'`)**: **ASI**, bilgi sorgusu için 11 baytlık bir **UDP** paketi oluşturur:
   - `BYTE 0-3`: "SAMP" imzası (S A M P).
   - `BYTE 4-9`: Sunucunun istemciyi tanıması için genellikle istek kaynağının IP adresini içeren 6 baytlık rastgele bir dizi.
   - `BYTE 10`: Bilgi sorgusunu (genel bilgiler: sunucu adı, oyuncular, vb.) belirten 'i' tanımlayıcı (ASCII 105).
      ```cpp
      // server_query.cpp (paket oluşturma)
      void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
          memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
          packet = 'i'; // Bilgi (Information) sorgusu
      }
      ```
- **Sunucu Yanıtının Yapısı**: Bir SA-MP sunucusu, 'i' sorgusuna yapılandırılmış veri dizisi içeren bir **UDP** paketiyle yanıt verir ve **ASI** bunu ayrıştırmalıdır:
   - **Yanıt Başlığı:** "SAMP" imzasını ve istek paketinden 6 baytlık diziyi tekrarlar. **ASI**, bu `Constants::QUERY_PACKET_SIZE` baytını basitçe atlar.
   - **Passworded (`bool`):** Sunucunun şifre korumalı olup olmadığını gösteren bir bayt. Okunur, ancak kullanılmaz.
   - **Players (`uint16_t`):** Şu anda sunucuya bağlı oyuncu sayısı.
   - **Max_Players (`uint16_t`):** Sunucunun desteklediği maksimum oyuncu slot sayısı.
   - **Hostname (`uint32_t` ile öneklenmiş string):** Sunucunun kullanıcı dostu adı. Paket, string uzunluğunu belirten bir `uint32_t` ve ardından stringin gerçek baytlarını içerir.
   - **Diğer Alanlar:** SAMP protokolü, boyutla öneklenmiş "gamemode" ve "language" ile devam eder. **ASI**, Rich Presence için gerekli olmayan bu alanları okur ve atlar.

   Bu alanların okunması, `Read_From_Span` ve `Read_String_From_Span` yardımcı fonksiyonlarıyla yapılır; bu fonksiyonlar, **ASI**’nin tampon sınırlarının ötesine okumamasını ve sabit ve değişken uzunluklu veri türlerini (stringler) doğru bir şekilde işlemesini sağlar.
   ```cpp
   // server_query.cpp (yanıt ayrıştırma)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       // ... (boyut kontrolü ve veri için subspan) ...
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // 'passworded' boolean’ını okur
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false; // 'Players’ı okur

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false; // 'Max_Players’ı okur

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false; // 'Hostname’i okur
   
       // 'Gamemode' ve 'Language' alanları, Read_String_From_Span tarafından
       // otomatik olarak atlanır, eğer paket daha fazla veri içeriyorsa.
       uint32_t length_placeholder; // Uzunluğu tutmak için geçici değişken.

       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Gamemode uzunluğunu okur

       if (data_span.size() < length_placeholder)
           return false; // Sınırları kontrol eder

       data_span = data_span.subspan(length_placeholder); // Gamemode verilerini atlar
   
       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Language uzunluğunu okur

       if (data_span.size() < length_placeholder)
           return false; // Sınırları kontrol eder

       data_span = data_span.subspan(length_placeholder); // Language verilerini atlar
   
       return true;
   }
   ```
   Yukarıdaki örnekte, `data_span = data_span.subspan(length_placeholder);` mantığı, Rich Presence için gerekli olmayan bir stringin baytlarını atlamanın etkili bir yoludur.

### SA-MP Rich Presence’ın Avantajları

**SA-MP Rich Presence**, hem oyuncular hem de sunucu yöneticileri için deneyimi önemli ölçüde geliştirir ve dikkate değer avantajlar sunar:

1. **Oyuncular İçin:**
   - **Zahmetsiz Görünürlük:** Oyun durumunuzu arkadaşlarınızla otomatik olarak Discord’da paylaşın ve tam olarak nerede oynadığınızı gösterin.
   - **Zengin Bilgi:** Sunucu detaylarına (ad, oyuncu sayısı, IP, özel logo) doğrudan Discord üzerinden anında erişin, başka yerlerde kontrol etmeye gerek kalmadan.
   - **Topluluğa Hızlı Erişim:** Discord durumunda dönen sosyal ikonlar aracılığıyla sunucunun sosyal medya platformlarını kolayca keşfedin ve erişin, canlı topluluklara katılımı kolaylaştırır.
   - **Arkadaşlarla Hızlı Bağlantı:** "Join" düğmesiyle arkadaşlarınızı oynadığınız sunucuya tek tıkla davet edin veya katılın.
   - **Kesintisiz Deneyim:** Otomatik güncelleme sistemi, her zaman en optimize ve işlevsel **ASI** sürümünü kullanmanızı sağlar.
2. **Sunucular İçin:**
   - **Doğal Viral Pazarlama:** Oyuncularınızın Discord durumu, sunucunuzu organik bir kitleye (oyuncuların arkadaşlarına) 24 saat tanıtan dijital bir reklam panosu gibi çalışır.
   - **Güçlü Görsel Kimlik:** Özelleştirilmiş logo ve sosyal bağlantı rotasyonu, sunucunuzun profesyonel ve modern bir imaj yansıtmasını sağlar.
   - **Artırılmış Katılım:** Yeni ve mevcut oyuncuların sosyal platformlarınıza bağlanmasını kolaylaştırarak topluluğunuzu güçlendirir ve oyun dışı katılımı artırır.
   - **Kolaylaştırılmış Oyuncu Alımı:** "Join" özelliği, yeni oyuncuların katılımını hızlandırır, engelleri kaldırır ve denemeyi teşvik eder.
   - **Tutarlı Veriler:** **AlderGrounds Integration API** entegrasyonu ile bilgi gösterimi birleştirilir ve merkezi olarak güncellenir, sunucunuzun markasının ve iletişim bilgilerinin her zaman doğru olmasını sağlar.

## Lisans

Bu ASI, Apache License 2.0 lisansı altında korunmaktadır ve şunlara izin verir:

- ✔️ Ticari ve özel kullanım
- ✔️ Kaynak kodunda değişiklik
- ✔️ Kod dağıtımı
- ✔️ Patent hakları

### Koşullar:

- Telif hakkı bildirimini korumak
- Önemli değişiklikleri belgelemek
- Apache License 2.0 lisansının bir kopyasını eklemek

Lisans hakkında daha fazla bilgi için: http://www.apache.org/licenses/LICENSE-2.0

**Telif Hakkı (c) Calasans - Tüm hakları saklıdır**