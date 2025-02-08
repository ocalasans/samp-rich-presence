# SA-MP Rich Presence

SA-MP Rich Presence, sunucu hakkında detaylı bilgileri Discord durumunuzda otomatik olarak güncelleyen SA-MP (San Andreas Multiplayer) için bir ASI'dir. ASI, bir SA-MP sunucusuna bağlandığınızda oyuna enjekte edilir ve sunucu bilgilerini görüntüler.

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
  - [ASI Nedir?](#asi-nedir)
  - [Özellikler](#özellikler)
    - [Discord Rich Presence](#discord-rich-presence)
  - [Gereksinimler](#gereksinimler)
  - [Kurulum](#kurulum)
  - [Detaylı Teknik Mimari](#detaylı-teknik-mimari)
    - [Ana Sistem (main.cpp)](#ana-sistem-maincpp)
    - [Discord Yöneticisi (discord\_manager.cpp)](#discord-yöneticisi-discord_managercpp)
    - [Sunucu Yöneticisi (server\_manager.cpp)](#sunucu-yöneticisi-server_managercpp)
    - [Ağ Sistemi (network\_manager.cpp)](#ağ-sistemi-network_managercpp)
    - [Sunucu Sorgusu (server\_query.cpp)](#sunucu-sorgusu-server_querycpp)
  - [SPC Entegrasyonu](#spc-entegrasyonu)
    - [SPC Integration Nedir?](#spc-integration-nedir)
    - [Nasıl Çalışır](#nasıl-çalışır)
    - [URL Yöneticisi (url\_manager.cpp)](#url-yöneticisi-url_managercpp)
  - [Sunucu Geliştiricileri İçin](#sunucu-geliştiricileri-i̇çin)
  - [Kod Yapısı](#kod-yapısı)
    - [Global Sabitler (constants.h)](#global-sabitler-constantsh)
    - [Veri Yapıları (server\_types.h)](#veri-yapıları-server_typesh)
  - [Hata Yönetimi](#hata-yönetimi)
  - [Komut Satırı İşleme Sistemi](#komut-satırı-i̇şleme-sistemi)
    - [Komut Satırı Ayrıştırıcı (command\_line\_parser.cpp)](#komut-satırı-ayrıştırıcı-command_line_parsercpp)
  - [SA-MP İletişim Protokolü](#sa-mp-i̇letişim-protokolü)
    - [Protokol Uygulaması](#protokol-uygulaması)
  - [SA-MP Rich Presence'ın Faydaları](#sa-mp-rich-presenceın-faydaları)
  - [Ek Teknik Notlar](#ek-teknik-notlar)
  - [Lisans](#lisans)
    - [Koşullar:](#koşullar)

## ASI Nedir?

ASI, GTA San Andreas başlatıldığında bir ASI yükleyici tarafından otomatik olarak yüklenen .asi uzantılı yeniden adlandırılmış bir dinamik kütüphanedir (.dll). ASI eklentileri, orijinal dosyaları değiştirmeden oyuna işlevsellik eklemeye veya değiştirmeye olanak tanır ve GTA San Andreas ve diğer GTA serisi oyunları için en popüler modding biçimlerinden biridir. Yüklü bir ASI yükleyici ile, oyunun klasörüne .asi dosyaları ekleyerek veya kaldırarak kolayca modifikasyonlar yükleyebilir veya kaldırabilirsiniz.

## Özellikler

### Discord Rich Presence

Discord Rich Presence, uygulamaların kullanıcının ne yaptığı hakkında detaylı bilgileri doğrudan Discord profilinde göstermesine olanak tanıyan bir özelliktir. SA-MP Rich Presence durumunda, aşağıdaki bilgiler görüntülenir:
- Sunucu adı (Hostname)
- Oyuncu adı
- Mevcut oyuncu sayısı ve maksimum oyuncu sayısı
- Sunucu IP'si ve portu
- Özelleştirilmiş sunucu resmi (sunucunun [SPC Integration](https://github.com/spc-samp/spc-integration) eklentisine sahip olmasını gerektirir)
- Oyun süresi
- Bağlantı durumu

## Gereksinimler

- SA-MP İstemcisi (eğer yoksa: [clients-samp](https://github.com/spc-samp/clients-samp))
- Discord Masaüstü Uygulaması
- Windows İşletim Sistemi
- Visual C++ Runtime
- GTA San Andreas'ta kurulu ASI Loader

## Kurulum

1. En son derlenmiş ASI sürümünü [releases](https://github.com/ocalasans/samp-rich-presence/releases) adresinden indirin.
2. GTA San Andreas'ınızda bir ASI Loader'ın kurulu olduğundan emin olun.
3. İndirilen .asi dosyasını GTA San Andreas klasörünüze kopyalayın.
4. Oyunu SA-MP ile başlatın.
5. Bir sunucuya girdiğinizde ASI otomatik olarak başlatılacaktır.

## Detaylı Teknik Mimari

### Ana Sistem (main.cpp)

main.cpp, ASI'nin giriş noktasıdır ve şunlardan sorumludur:
1. Sistem başlatma:
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

2. Güncelleme thread'inin yönetimi:
   ```cpp
   DWORD WINAPI Update_Thread(LPVOID) {
       // Ağ işlemleri için WSA başlatılır
       WSAData wsa_data;
       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
       
       // Komut satırı parametrelerini işle
       std::string server_ip, player_name;
       int server_port;
       
       // Yöneticileri başlat
       Global_Server_Manager = std::make_unique<Server_Manager>(server_ip, server_port, player_name);
       Global_Discord_Manager = std::make_unique<Discord_Manager>();
       
       // Ana güncelleme döngüsü
       while (true) {
           Global_Server_Manager->Update();
           Global_Discord_Manager->Update_Presence(...);
           Sleep(Constants::PRESENCE_UPDATE_INTERVAL);
       }
   }
   ```

### Discord Yöneticisi (discord_manager.cpp)

Discord_Manager, tüm Discord Rich Presence entegrasyonundan sorumludur:
1. Discord RPC başlatma:
   ```cpp
   void Discord_Manager::Initialize() noexcept {
       Sleep(5000);  // Discord başlatılmasını bekle
       
       DiscordEventHandlers discord_handlers{};
       Discord_Initialize("DISCORD_APP_ID", &discord_handlers, 1, NULL); // "DISCORD_APP_ID > Application ID"
       
       start_timestamp = time(nullptr);  // Oturum başlangıcını işaretle
   }
   ```

2. Presence güncelleme:
   ```cpp
   void Discord_Manager::Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept {
       DiscordRichPresence discord_presence{};
       
       // Temel bilgileri ayarla
       discord_presence.state = player_name.data();
       discord_presence.details = server_info.Hostname.c_str();
       discord_presence.largeImageKey = current_image.data();
       
       // Sunucu bilgilerini ekle
       discord_presence.largeImageText = server_info.Server_Address.c_str();
       discord_presence.startTimestamp = start_timestamp;
       discord_presence.partySize = server_info.Players;
       discord_presence.partyMax = server_info.Max_Players;
       
       Discord_UpdatePresence(&discord_presence);
   }
   ```

### Sunucu Yöneticisi (server_manager.cpp)

Server_Manager, sunucuyla ilgili tüm işlemleri koordine eder:
1. Durum yönetimi:
   ```cpp
   Server_Manager::Server_Manager(const std::string& ip, int port, const std::string& name)
       : connection_status(false)
       , server_ip(ip)
       , server_port(port)
       , player_name(name)
       , current_image_url(Constants::DEFAULT_IMAGE)
   {}
   ```

2. Bilgi güncelleme:
   ```cpp
   bool Server_Manager::Update() {
       bool query_success = server_query.Query(server_data);
       
       if (query_success) {
           connection_status = true;
           server_data.Server_Address = Get_Server_Address();
           
           // Sunucunun özel resmini almayı dene
           std::string new_image_url = url_manager.Get_Image_URL(server_data.Server_Address);

           if (!new_image_url.empty())
               current_image_url = new_image_url;
       }
       // ...
   }
   ```

### Ağ Sistemi (network_manager.cpp)

Network_Manager tüm ağ iletişimini uygular:
1. Socket başlatma:
   ```cpp
   bool Network_Manager::Initialize(std::string_view ip, int port) noexcept {
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       
       // Timeout ayarla
       timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
       
       // Sunucu adresini ayarla
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(port);
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr);
       
       return true;
   }
   ```

### Sunucu Sorgusu (server_query.cpp)

Server_Query, SA-MP sorgu protokolünü uygular:
1. Sorgu paketinin oluşturulması:
   ```cpp
   bool Server_Query::Assemble_Query_Packet(char* packet) noexcept {
       memcpy(packet, QUERY_SIGNATURE, 4);  // "SAMP"
       packet[10] = 'i';  // Information query

       return true;
   }
   ```

2. Yanıt işleme:
   ```cpp
   bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
       // Şu bilgileri çıkar:
       // - Oyuncu sayısı
       // - Maksimum oyuncu sayısı
       // - Hostname
   }
   ```

## SPC Entegrasyonu

### SPC Integration Nedir?

[SPC Integration](https://github.com/spc-samp/spc-integration), **SA-MP** (San Andreas Multiplayer) ve **open.mp** (Open Multiplayer) için geliştirilmiş, sunucular ile **SPC** ekosistemi arasında köprü görevi gören bir eklentidir. Eklenti sunucudan şu önemli bilgileri toplar:
- IP ve port
- Sunucu web sitesi URL'si
- Özel resim URL'si
- Yapılandırma bilgileri

Bu bilgiler **SPC (SA-MP Programming Community)** veri deposunda güvenli bir şekilde saklanır ve Rich Presence dahil olmak üzere çeşitli **SPC** uygulamalarıyla entegrasyona olanak tanır.

### Nasıl Çalışır

1. Sunucu, özel resmini kaydetmek için [SPC Integration](https://github.com/spc-samp/spc-integration) eklentisini kullanır.
2. Resim, sunucunun JSON dosyasında **SPC** veri deposunda saklanır.
3. Bir oyuncu sunucuya bağlandığında:
    - ASI'nin URL_Manager'ı sunucunun JSON dosyasını almaya çalışır (format: `ip-port.json`).
    - Bulunursa, `spc_integration_image` parametresinden resim URL'sini çıkarır.
    - Resim daha sonra oyuncunun Discord Rich Presence'ında görüntülenir.

### URL Yöneticisi (url_manager.cpp)

URL_Manager, **SPC** veri deposuyla tüm iletişimden sorumludur:
1. Sunucu resmini alma:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       std::string formatted_address = server_address;
       // ":" karakterini "-" ile değiştir
       size_t colon_pos = formatted_address.find(':');

       if (colon_pos != std::string::npos)
           formatted_address.replace(colon_pos, 1, "-");
       
       // Sunucu JSON'ını al
       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;
       
       return image_url;
   }
   ```

2. JSON işleme:
   ```cpp
   std::string URL_Manager::Parse_JSON(const std::string& json_content) {
       const std::string key = "\"spc_integration_image\":";
       size_t key_pos = json_content.find(key);
       
       // JSON'dan resim URL'sini çıkar
       // ...
       
       return image_url;
   }
   ```

## Sunucu Geliştiricileri İçin

Eğer bir SA-MP sunucu geliştiricisiyseniz, aşağıdaki nedenlerden dolayı [SPC Integration](https://github.com/spc-samp/spc-integration) eklentisini kurmanızı şiddetle tavsiye ederiz:
1. Görünürlük:
    - Sunucunuzun özel resmi, bu ASI'yi kullanan tüm oyuncuların Discord'unda görüntülenecektir.
    - Sunucunuzun marka bilinirliğini artırır.
    - Daha profesyonel bir sunum sağlar.

2. Faydalar:
    - Daha fazla oyuncu katılımı.
    - Discord'da görsel farklılaşma.
    - Rich Presence ile otomatik entegrasyon.

3. Nasıl uygulanır:
   - Nasıl uygulayacağınızı öğrenmek için [SPC Integration](https://github.com/spc-samp/spc-integration) eklentisinin deposunu okuyun.

## Kod Yapısı

Proje çeşitli bileşenlere ayrılmıştır:
```
src/
├── discord/               # Discord RPC kütüphanesi
├── command_line_parser.*  # Argüman işleme
├── constants.h            # Global sabitler
├── discord_manager.*      # Discord entegrasyonu
├── main.cpp               # Giriş noktası
├── network_manager.*      # Ağ işlemleri
├── server_manager.*       # Sunucu yönetimi
├── server_query.*         # SA-MP protokolü
├── server_types.h         # Veri yapıları
└── url_manager.*          # SPC entegrasyonu
```

### Global Sabitler (constants.h)

Dosya önemli sabitleri tanımlar:
```cpp
namespace Constants {
    // Varsayılan değerler
    inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
    inline constexpr int DEFAULT_SERVER_PORT = 7777;
    
    // Ağ ayarları
    inline constexpr int QUERY_TIMEOUT = 1000;
    inline constexpr int QUERY_PACKET_SIZE = 11;
    inline constexpr int QUERY_BUFFER_SIZE = 512;
    
    // Yeniden deneme ayarları
    inline constexpr int MAX_RETRY_ATTEMPTS = 3;
    
    // Aralıklar
    inline constexpr int PRESENCE_UPDATE_INTERVAL = 5000;
}
```

### Veri Yapıları (server_types.h)

Ana yapıları tanımlar:
```cpp
struct Server_Information {
    uint16_t Players{ 0 };           // Çevrimiçi oyuncular
    uint16_t Max_Players{ 0 };       // Maksimum oyuncu sayısı
    std::string Hostname;            // Sunucu adı
    std::string Server_Image;        // Resim URL'si
    std::string Server_Address;      // Sunucu adresi
};
```

## Hata Yönetimi

Sistem sağlam bir hata yönetim sistemi uygular:
1. Ağ zaman aşımı:
   ```cpp
   timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
   setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
   ```

2. Yeniden deneme sistemi:
   ```cpp
   bool Server_Query::Try_Query(Server_Information& server_data, int retry_count) noexcept {
       for (int attempt = 0; attempt <= retry_count; attempt++) {
           if (network_manager.Send_Query(...))
               return true;
           
           // Yeniden denemeden önce bekle
           std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
       }

       return false;
   }
   ```

3. Varsayılan resme dönüş:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       // Bir şeyler ters giderse, varsayılan resmi döndür
       if (!session_handle)
           return Constants::DEFAULT_IMAGE;

       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;

       return image_url;
   }
   ```

4. Bağlantı durumu izleme:
   ```cpp
   bool Server_Manager::Update() {
       auto current_time = std::chrono::steady_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_successful_query);
       
       // 15 saniyeden fazla yanıt alınamazsa, bağlantı kesilmiş sayılır
       if (duration.count() > 15) {
           connection_status = false;
           current_image_url = Constants::DEFAULT_IMAGE;
       }
   }
   ```

## Komut Satırı İşleme Sistemi

ASI, komut satırı argümanlarını işlemek için esnek bir sistem uygular:

### Komut Satırı Ayrıştırıcı (command_line_parser.cpp)

1. Ana işleme:
   ```cpp
   bool Command_Line_Parser::Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       // Varsayılan değerleri ayarla
       server_ip = Constants::DEFAULT_SERVER_IP;
       server_port = Constants::DEFAULT_SERVER_PORT;

       // Her parametreyi işle
       std::wstring ip_parameter = Parse_Parameter(command_string, L"-h");
       std::wstring port_parameter = Parse_Parameter(command_string, L"-p");
       std::wstring name_parameter = Parse_Parameter(command_string, L"-n");

       // Değerleri dönüştür ve doğrula
       if (!ip_parameter.empty())
           server_ip = Convert_To_String(ip_parameter);

       if (!port_parameter.empty())
           server_port = std::stoi(port_parameter);

       if (!name_parameter.empty())
           player_name = Convert_To_String(name_parameter);

       // Gerekli tüm parametrelerin mevcut olup olmadığını kontrol et
       return !server_ip.empty() && server_port > 0 && !player_name.empty();
   }
   ```

2. Parametre çıkarma:
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

## SA-MP İletişim Protokolü

ASI, sunucu bilgilerini almak için SA-MP sorgu protokolünü uygular:
1. Sorgu paketi yapısı:
    - 4 byte: "SAMP" imzası
    - 7 byte: Ek veriler
    - Son byte: 'i' (bilgi sorgusu göstergesi)

2. Yanıt yapısı:
    - Paket başlığı
    - Players (uint16_t)
    - Max_Players (uint16_t)
    - Hostname (string)

### Protokol Uygulaması

```cpp
bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
    char* current_pos = response_buffer + Constants::QUERY_PACKET_SIZE;
    const char* buffer_end = response_buffer + received_bytes;

    // "password"u atla
    current_pos += sizeof(bool);
    
    // Sabit verileri oku
    memcpy(&server_data.Players, current_pos, sizeof(server_data.Players));
    current_pos += sizeof(server_data.Players);
    
    memcpy(&server_data.Max_Players, current_pos, sizeof(server_data.Max_Players));
    current_pos += sizeof(server_data.Max_Players);

    // Hostname'i oku ve "gamemode" ve "language"ı atla
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
    
    // "gamemode" ve "language"ı atla
    // ...

    return true;
}
```

## SA-MP Rich Presence'ın Faydaları

1. Oyuncular İçin:
    - Mevcut sunucunun hızlı görüntülenmesi.
    - Sunucu hakkında detaylı bilgiler.
    - Discord ile kusursuz entegrasyon.
    - Daha sosyal bir oyun deneyimi.

2. Sunucular İçin:
    - Discord üzerinden daha fazla görünürlük.
    - Oyuncular aracılığıyla organik pazarlama.
    - Özelleştirilmiş görsel kimlik ([SPC Integration](https://github.com/spc-samp/spc-integration) eklentisi ile).
    - Gerçek zamanlı istatistikler.

## Ek Teknik Notlar

1. Thread Güvenliği:
    - ASI güncellemeler için tek bir thread kullanır.
    - Yöneticiler tasarım gereği thread-safe'dir.
    - Kaynaklar uygun şekilde senkronize edilir.

2. Bellek Kullanımı:
    - Minimum bellek tahsisi.
    - Sorgular için önceden ayrılmış tamponlar.
    - Otomatik kaynak yönetimi (RAII).

3. Performans:
    - Zaman aşımı ile optimize edilmiş sorgular.
    - Akıllı yeniden deneme sistemi.
    - Yapılandırılabilir güncelleme aralığı.

4. Uyumluluk:
    - Unicode desteği.
    - Modern Windows ile uyumlu.
    - IPv4 desteği.

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