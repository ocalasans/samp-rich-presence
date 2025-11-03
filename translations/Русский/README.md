# SA-MP Rich Presence

**SA-MP Rich Presence** — это **ASI** для **SA-MP (San Andreas Multiplayer)**, который автоматически обновляет ваш статус в Discord с подробной информацией о сервере. **ASI** внедряется в игру, когда вы подключаетесь к серверу SA-MP, отображая информацию о сервере.

## Языки

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Содержание

- [SA-MP Rich Presence](#sa-mp-rich-presence)
  - [Языки](#языки)
  - [Содержание](#содержание)
  - [Функциональность](#функциональность)
    - [Discord Rich Presence](#discord-rich-presence)
    - [Система автоматического обновления](#система-автоматического-обновления)
  - [Требования](#требования)
  - [Установка](#установка)
  - [Интеграция с AlderGrounds Integration API](#интеграция-с-aldergrounds-integration-api)
    - [Как информация получается и используется:](#как-информация-получается-и-используется)
  - [Для разработчиков серверов](#для-разработчиков-серверов)
    - [Как внедрить AlderGrounds Integration на вашем сервере:](#как-внедрить-aldergrounds-integration-на-вашем-сервере)
  - [Детальная техническая архитектура](#детальная-техническая-архитектура)
      - [Основная система (`main.cpp`)](#основная-система-maincpp)
      - [Система обновления (`asi_update.hpp`)](#система-обновления-asi_updatehpp)
      - [Менеджер Discord (`discord_manager.cpp`)](#менеджер-discord-discord_managercpp)
      - [Менеджер сервера (`server_manager.cpp`)](#менеджер-сервера-server_managercpp)
      - [Сетевая система (`samp_network.cpp`)](#сетевая-система-samp_networkcpp)
      - [Запрос к серверу (`server_query.cpp`)](#запрос-к-серверу-server_querycpp)
      - [Менеджер URL (`url_manager.cpp`)](#менеджер-url-url_managercpp)
    - [Структура кода](#структура-кода)
      - [Глобальные константы (`constants.hpp`)](#глобальные-константы-constantshpp)
      - [Структуры данных (`server_types.hpp`)](#структуры-данных-server_typeshpp)
      - [Обфускация секретов (`secrets.hpp`)](#обфускация-секретов-secretshpp)
      - [Общие утилиты (`utils.hpp`)](#общие-утилиты-utilshpp)
    - [Обработка ошибок и устойчивость](#обработка-ошибок-и-устойчивость)
    - [Система обработки командной строки](#система-обработки-командной-строки)
      - [Парсер командной строки (`command_line_parser.cpp`)](#парсер-командной-строки-command_line_parsercpp)
    - [Протокол связи SA-MP](#протокол-связи-sa-mp)
      - [Реализация протокола](#реализация-протокола)
    - [Преимущества SA-MP Rich Presence](#преимущества-sa-mp-rich-presence)
  - [Лицензия](#лицензия)
    - [Условия:](#условия)

## Функциональность

### Discord Rich Presence

**Discord Rich Presence** — это функция, которая позволяет приложениям отображать подробную информацию о том, что делает пользователь, прямо в профиле Discord. В случае **SA-MP Rich Presence** отображаются следующие данные:

- **Имя сервера (Hostname):** Основное название сервера.
- **Имя игрока:** Ваш текущий ник в игре.
- **Количество игроков:** Текущее число игроков онлайн и максимальное допустимое количество.
- **Адрес сервера:** IP и порт сервера для удобной идентификации.
- **Персонализированное изображение сервера:** Уникальный логотип сервера, если он доступен.
- **Ротация социальных иконок:** Маленькие иконки, представляющие ссылки на социальные сети сервера (веб-сайт, Discord, YouTube, Instagram, Facebook, TikTok), автоматически сменяющиеся.
- **Время игры:** Сколько времени вы подключены к текущему серверу.
- **Статус подключения:** Показывает, находитесь ли вы онлайн на сервере или в состоянии "Idle" (неактивен).
- **Кнопка "Join" (Присоединиться):** Позволяет вашим друзьям напрямую подключиться к тому же серверу, на котором вы играете.

### Система автоматического обновления

**ASI** включает систему проверки обновлений. При запуске игры она проверяет наличие новых версий в официальном репозитории GitHub проекта. Если обновление обнаружено, пользователю отображается дружелюбное уведомление с предложением:

1. Открыть браузер на странице релизов для скачивания.
2. Продолжить без обновления, с возможностью отключить **ASI** на текущую сессию.

Эта функция гарантирует, что пользователи всегда имеют доступ к последним улучшениям, исправлениям ошибок и новым возможностям, обеспечивая актуальный и бесперебойный опыт.

## Требования

- Клиент SA-MP (если у вас его нет: [clients-samp](https://github.com/aldergrounds/clients-samp)).
- Приложение Discord Desktop.
- Операционная система Windows.
- Visual C++ Runtime.
- Установленный [ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) в вашем Grand Theft Auto: San Andreas.

## Установка

1. Скачайте последнюю версию **ASI**, скомпилированную, непосредственно из раздела [releases](https://github.com/ocalasans/samp-rich-presence/releases) на GitHub.
2. После загрузки найдите файл `.asi`.
3. Скопируйте загруженный файл `.asi` в корневую папку вашего GTA San Andreas (где находится файл `gta_sa.exe`).
4. Запустите игру через клиент SA-MP.
5. **ASI** будет автоматически загружен и инициализирован при подключении к серверу, обновляя ваш статус в Discord.

## Интеграция с AlderGrounds Integration API

**SA-MP Rich Presence** значительно улучшает отображение информации в Discord благодаря интеграции с **AlderGrounds Integration API**. Вместо использования только базовых данных запроса, **ASI** теперь напрямую взаимодействует с этой API для получения визуальной и социальной информации о сервере. Чтобы узнать больше о **AlderGrounds Integration**, посетите официальный репозиторий: [aldergrounds/integration](https://github.com/aldergrounds/integration).

### Как информация получается и используется:

1. **Форматирование адреса:** Когда игрок подключается к серверу (IP и порт), **ASI** форматирует этот адрес (`IP:PORT`) в удобный формат (`IP-PORT`) для запроса API.
2. **Запрос к API:** **ASI** отправляет запрос `GET` на конечную точку **AlderGrounds Integration API**, включая отформатированные IP и порт. Пример того, как URL запроса строится внутри:
   ```cpp
   // Фрагмент адаптирован из url_manager.cpp
   auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
   std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
   path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   const std::string json_data = Request_API_Data(path);
   ```
3. **Обработка ответа JSON:** API возвращает ответ в формате JSON. **ASI** использует библиотеку [nlohmann/json](https://github.com/nlohmann/json) для разбора этого ответа и извлечения соответствующих данных.
   ```json
   // Пример структуры ответа AlderGrounds Integration API
   {
       "success": true,
       "data": {
           "public": {
               "logo": "https://url.do.seu.logo/server_logo.png",
               "website": "https://seu-site.com",
               "discord": "https://discord.gg/seuservidor",
               "youtube": "https://youtube.com/seucanal"
               // ...другие социальные сети
           }
       }
   }
   ```
4. **Извлечение данных:**
   - **Логотип сервера:** URL изображения сервера (поле `logo` в разделе `public`) извлекается и используется как основное изображение (large image) в **Discord Rich Presence**. Это обеспечивает аутентичную и настраиваемую визуальную идентичность для каждого сервера.
   - **Социальные ссылки:** Проверяется заранее определенный список социальных сетей (website, Discord, YouTube, Instagram, Facebook, TikTok) в ответе JSON. Для каждой найденной социальной сети с действительным значением сохраняется название сети и соответствующая ссылка.
5. **Отображение в Discord:** `Server_Manager` использует список извлеченных социальных ссылок для реализации динамической ротации. Каждые 30 секунд в присутствии Discord отображается новая иконка одной из социальных сетей сервера в качестве "small image" (маленькое изображение), вместе со ссылкой или названием платформы, что стимулирует исследование сообществ сервера.

## Для разработчиков серверов

Интеграция вашего сервера с [AlderGrounds Integration](https://github.com/aldergrounds/integration) приносит ряд прямых и косвенных преимуществ, которые повышают видимость и вовлеченность вашего сообщества SA-MP. Если вы разработчик сервера, рассмотрите стратегические преимущества:

1. **Усиление вашего бренда:**
   - **Премиум-видимость:** Персонализированный логотип вашего сервера будет не просто текстом, а ярким и привлекательным изображением, отображаемым в профиле Discord всех игроков, использующих этот **ASI**. Это органичный и постоянный способ брендинга.
   - **Профессиональное присутствие:** Наличие логотипа и хорошо представленных социальных сетей создает более надежный и профессиональный образ сервера, привлекая больше интереса и потенциальных новых игроков.
2. **Расширение сообщества:**
   - **Увеличение каналов доступа:** Благодаря ротации социальных иконок вы можете продвигать различные платформы вашего сообщества — от официального веб-сайта и Discord сервера до страниц на YouTube, Instagram, Facebook или TikTok. Каждая иконка и ссылка в **Discord Rich Presence** напрямую направляет заинтересованных пользователей туда, где ваше сообщество активно.
   - **Мгновенное подключение:** Функция "Join" через Discord позволяет друзьям ваших игроков подключиться к вашему серверу SA-MP одним щелчком, снижая барьеры входа и привлекая новых участников.
3. **Упрощенное обновление контента:**
   - При использовании [AlderGrounds Integration](https://github.com/aldergrounds/integration) любое обновление логотипа вашего сервера или списка социальных сетей, настроенных в плагине [AlderGrounds Integration](https://github.com/aldergrounds/integration) **(на стороне сервера)**, автоматически отобразится для игроков, использующих **ASI**, без необходимости обновления **ASI**. Это гарантирует, что информация всегда актуальна.

### Как внедрить AlderGrounds Integration на вашем сервере:

1. **Плагин AlderGrounds Integration:** Вашему серверу потребуется установить и правильно настроить плагин [AlderGrounds Integration](https://github.com/aldergrounds/integration). Этот плагин является мостом, который отправляет информацию о вашем сервере в список данных **AlderGrounds**, который затем используется **AlderGrounds Integration API** для предоставления публичной информации.
2. **Настройка:** Следуйте инструкциям в репозитории плагина [AlderGrounds Integration](https://github.com/aldergrounds/integration) для настройки:
   - Параметра `logo` с URL логотипа вашего сервера.
   - Параметров социальных сетей (`discord`, `website`, `youtube` и т.д.) с действительными ссылками на ваши платформы.
3. **Автоматическое обновление:** После настройки информации в плагине сервера **SA-MP Rich Presence** автоматически обнаружит и отобразит их. От игрока не требуется никаких действий, кроме начальной установки **ASI**.

Интеграция вашего сервера с [AlderGrounds Integration](https://github.com/aldergrounds/integration) не только улучшает опыт ваших игроков, но и открывает двери для значительного роста и вовлеченности вашего сообщества.

## Детальная техническая архитектура

**SA-MP Rich Presence** имеет четко определенную модульную архитектуру, с компонентами, сосредоточенными на конкретных задачах. Кодовая база соответствует современным стандартам C++ (C++17 и C++20), используя `std::string_view`, `std::span` и семантику перемещения для обеспечения высокой производительности, безопасности и эффективности.

#### Основная система (`main.cpp`)

Сердце **ASI** находится в `main.cpp`, который управляет жизненным циклом приложения, от его инициализации как DLL до непрерывного цикла обновления и плавного завершения.

- **`DllMain`**: Точка входа **ASI** при загрузке операционной системой.
   ```cpp
   // DllMain (упрощенно для акцента на структуре)
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
   В этой функции при присоединении к процессу игры (`DLL_PROCESS_ATTACH`) отключаются ненужные вызовы библиотеки (`DisableThreadLibraryCalls`) и **создается новая нить (`Main_Update_Thread`)** для асинхронного выполнения логики **ASI**, чтобы игра не блокировалась. При завершении (`DLL_PROCESS_DETACH`) вызывается `Shutdown_Managers()` для освобождения ресурсов.
- **`Main_Update_Thread`**: Душа **ASI**, работающая в собственной нити.
   ```cpp
   // Main_Update_Thread (ключевой фрагмент)
   DWORD WINAPI Main_Update_Thread(LPVOID) {
       // 1. Проверка обновления
       if (Asi_Update::Check_For_Update())
           return 0; // Если пользователь решил отключить, завершает.
   
       // 2. Инициализация сети (Winsock)
       WSAData wsa_data;

       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
   
       // 3. Инициализация менеджеров сервера и Discord
       Initialize_Managers();
   
       // 4. Основной цикл обновления
       while (is_running && v_server_manager && v_discord_manager) {
           v_server_manager->Update(); // Запрос сервера, API AlderGrounds, и т.д.
           v_discord_manager->Update_Presence( // Обновляет статус Discord
               v_server_manager->Get_Server_Info(),
               v_server_manager->Get_Display_Social_Link(),
               v_server_manager->Get_Player_Name(),
               v_server_manager->Get_Current_Image_URL(),
               v_server_manager->Is_Connected());
   
           Discord_RunCallbacks(); // Обрабатывает события RPC Discord
           std::this_thread::sleep_for(Constants::MAIN_LOOP_INTERVAL);
       }
   
       // 5. Завершение (если менеджеры существуют)
       if (v_discord_manager)
           v_discord_manager->Shutdown();

       WSACleanup(); // Освобождает Winsock

       return 0;
   }
   ```
   Эта функция сначала проверяет наличие обновлений. Затем инициализирует стек сети Winsock и экземпляры менеджеров сервера и Discord. Постоянный цикл `while` (управляемый `std::atomic<bool> is_running` для безопасного завершения) координирует вызовы `Server_Manager::Update()` (сбор данных) и `Discord_Manager::Update_Presence()` (отправка в Discord). `Discord_RunCallbacks()` обеспечивает обработку событий Rich Presence в Discord. Цикл периодически приостанавливается с помощью `std::this_thread::sleep_for` для оптимизации ресурсов.

#### Система обновления (`asi_update.hpp`)

Этот жизненно важный модуль добавляет интеллектуальность **ASI**, гарантируя, что пользователи остаются в актуальном состоянии.

- **`Check_For_Update()`**: Основная функция проверки.
   ```cpp
   // asi_update.hpp (ключевой фрагмент Check_For_Update)
   inline bool Check_For_Update() {
       HINTERNET h_session = nullptr, h_connect = nullptr, h_request = nullptr;
       bool update_found_and_handled = false;
   
       try {
           h_session = WinHttpOpen(L"SA-MP Rich Presence Update/1.0", ...);
           // ... (запрос GET к Constants::UPDATE_API_PATH в API GitHub) ...
           std::string response_body;
           // ... (чтение ответа HTTP) ...
           nlohmann::json release_info = nlohmann::json::parse(response_body);
   
           std::string latest_tag = release_info["tag_name"].get<std::string>();
           // ... (нормализация и сравнение версий с помощью sscanf_s/sscanf) ...
   
           if (latest_major > current_major || (latest_major == current_major && latest_minor > current_minor)) {
               update_found_and_handled = true;
               std::wstringstream message_stream;
               // ... (подготовка сообщения MessageBox) ...
               int msgbox_result = MessageBoxW(NULL, message_stream.str().c_str(), L"SA-MP Rich Presence - Update Available", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
               
               if (msgbox_result == IDYES)
                   ShellExecuteW(NULL, L"open", Constants::UPDATE_RELEASES_URL, NULL, NULL, SW_SHOWNORMAL);
           }
       }
       catch (const std::exception&) { /* Обработка ошибок */ }
   
       // ... (закрытие дескрипторов WinHttp) ...
       return update_found_and_handled;
   }
   ```
   Используя **API WinHTTP** для сетевых запросов, `Check_For_Update` выполняет запрос `GET` к конечной точке `/releases/latest` API GitHub для репозитория проекта. Ответ в формате JSON разбирается с помощью библиотеки `nlohmann/json`. Последняя версия (`tag_name`) сравнивается численно с версией, скомпилированной в **ASI**. Если обнаружена новая версия, отображается диалоговое окно (`MessageBoxW`), спрашивающее пользователя, хочет ли он перейти на страницу загрузок через `ShellExecuteW`. Весь процесс заключен в блок `try-catch` для обеспечения того, что сбои сети или парсинга не помешают запуску игры.

#### Менеджер Discord (`discord_manager.cpp`)

Класс `Discord_Manager` абстрагирует взаимодействие с библиотекой **Discord RPC**, управляя инициализацией соединения и отправкой данных для статуса присутствия пользователя.

- **`Initialize()`**: Настраивает связь с Discord.
   ```cpp
   // discord_manager.cpp (ключевой фрагмент Initialize)
   void Discord_Manager::Initialize() noexcept {
       DiscordEventHandlers handlers;
       memset(&handlers, 0, sizeof(handlers)); // Гарантирует инициализацию
       
       // App ID деобфусцируется здесь
       auto app_id_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_Discord_App_ID());
       Discord_Initialize(app_id_accessor.Get(), &handlers, 1, nullptr);
   
       start_timestamp_ = time(nullptr); // Регистрирует начало сессии
   }
   ```
   Вызов `Discord_Initialize` критически важен, используя `DISCORD_APP_ID`, который безопасно извлекается через обфускацию строк в `secrets.hpp`. Здесь же устанавливается `start_timestamp_` для расчета времени игры в присутствии Discord.
- **`Update_Presence()`**: Жизненно важная функция, обновляющая Rich Presence в Discord.
   ```cpp
   // discord_manager.cpp (ключевой фрагмент Update_Presence)
   void Discord_Manager::Update_Presence(const Server_Information& server_info, const server_types::Social_Link& social_link, const std::string_view player_name, const std::string_view current_image, const bool is_connected) noexcept {
       DiscordRichPresence discord_presence;
       memset(&discord_presence, 0, sizeof(discord_presence));
   
       discord_presence.startTimestamp = start_timestamp_;
       discord_presence.largeImageKey = current_image.data(); // Логотип сервера
   
       if (is_connected) {
           discord_presence.details = server_info.Hostname.c_str();
           discord_presence.state = player_name.data();
           discord_presence.largeImageText = server_info.Server_Address.c_str(); // IP:Порт
           discord_presence.partySize = server_info.Players;
           discord_presence.partyMax = server_info.Max_Players;
           discord_presence.joinSecret = server_info.Server_Address.c_str(); // Включает кнопку "Join"
   
           // Управляет ротацией социальных иконок
           if (!social_link.first.empty()) {
               current_small_image_key_ = Constants::SOCIAL_ICON_BASE_URL;
               current_small_image_key_ += social_link.first; // Например: "discord.png"
               current_small_image_key_ += ".png";
               discord_presence.smallImageKey = current_small_image_key_.c_str();
               discord_presence.smallImageText = social_link.second.c_str(); // Текст при наведении (ссылка/название)
           }
       }
       else {
           discord_presence.details = "SA-MP"; // Состояние "Idle"
           discord_presence.state = "Idle";
           discord_presence.largeImageText = "San Andreas Multiplayer";
           // smallImageKey и smallImageText остаются пустыми для состояния Idle
       }
   
       Discord_UpdatePresence(&discord_presence);
   }
   ```
   Заполняет структуру `DiscordRichPresence` в зависимости от состояния подключения. Если `is_connected` истинно, отображаются hostname, количество игроков, IP сервера и имя игрока. `largeImageKey` определяет основное изображение сервера. Примечательно, что `joinSecret` устанавливается для прямого подключения друзей, а `smallImageKey` (динамически формируемый на основе переданного `social_link`) отображает ротационные социальные иконки. В состоянии "Idle" присутствие упрощается для отражения неактивности. Наконец, `Discord_UpdatePresence` отправляет данные в Discord.

#### Менеджер сервера (`server_manager.cpp`)

`Server_Manager` — это оркестратор данных, управляющий состоянием подключения, запросами к серверу и **AlderGrounds Integration API**, а также решающий, какие данные должны отображаться и когда.

- **`Update()`**: Основной жизненный цикл для сбора данных.
   ```cpp
   // server_manager.cpp (ключевой фрагмент Update)
   void Server_Manager::Update() {
       const auto now = std::chrono::steady_clock::now();
   
       if (server_query.Query(live_server_data)) { // Пытается получить данные через запрос SAMP
           if (!connection_status) { // Если только что подключился/переподключился
               connection_status = true;
               Fetch_API_Data(); // Запрашивает логотип и социальные данные из API
           }
           
           last_successful_query = now;
   
           // Обновляет данные для отображения в Discord
           display_server_data.Hostname = live_server_data.Hostname;
           display_server_data.Players = live_server_data.Players;
           display_server_data.Max_Players = live_server_data.Max_Players;
           display_server_data.Server_Address = server_ip + ":" + std::to_string(server_port);
   
           if (now - last_api_update > Constants::IMAGE_UPDATE_INTERVAL)
               Fetch_API_Data(); // Повторный запрос API через заданное время
   
           if (now - last_social_rotation > Constants::SOCIAL_UPDATE_INTERVAL)
               Rotate_Social_Link(); // Ротация социальной иконки
       }
       else { // Если запрос не удался
           if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
               connection_status = false; // Отключен после таймаута
               display_image_url = Constants::DEFAULT_IMAGE;
               display_server_data = {}; // Очищает данные
               current_display_social = {}; // Очищает социальные данные
           }
       }
   }
   ```
   Функция `Update` пытается выполнить запрос к серверу. В случае успеха обновляет данные в `live_server_data` и `display_server_data`. Условно вызывает `Fetch_API_Data()` для обновления изображения и социальных ссылок (если это новое подключение или прошло `IMAGE_UPDATE_INTERVAL`) и `Rotate_Social_Link()` для смены социальных иконок (`SOCIAL_UPDATE_INTERVAL`). Если запросы к серверу постоянно не удаются в течение 15 секунд, статус подключения считается потерянным, и отображаемые данные сбрасываются.
- **`Fetch_API_Data()`**: Отвечает за получение визуальных и социальных данных.
   ```cpp
   // server_manager.cpp (ключевой фрагмент Fetch_API_Data)
   void Server_Manager::Fetch_API_Data() {
       display_image_url = url_manager.Get_Image_URL_And_Populate_Socials(server_ip, server_port, live_server_data);
       last_api_update = std::chrono::steady_clock::now();
       current_social_index_ = 0; // Сбрасывает индекс после нового запроса API
       Rotate_Social_Link(); // Гарантирует немедленное отображение социальной иконки
   }
   ```
   Эта функция координирует с `URL_Manager` для получения логотипа и социальных ссылок из API, обновляя `display_image_url` и заполняя `Social_Links` внутри `live_server_data`. Сбрасывает индекс ротации социальных ссылок и вызывает `Rotate_Social_Link()` для немедленного отображения первой иконки.
- **`Rotate_Social_Link()`**: Логика для смены социальных иконок.
   ```cpp
   // server_manager.cpp (ключевой фрагмент Rotate_Social_Link)
   void Server_Manager::Rotate_Social_Link() {
       if (!live_server_data.Social_Links.empty()) {
           if (current_social_index_ >= live_server_data.Social_Links.size())
               current_social_index_ = 0; // Перезапускает цикл
   
           current_display_social = live_server_data.Social_Links[current_social_index_];
           current_social_index_ = (current_social_index_ + 1) % live_server_data.Social_Links.size();
       }
       else
           current_display_social = {}; // Очищает, если социальных ссылок нет
       
       last_social_rotation = std::chrono::steady_clock::now();
   }
   ```
   Эта простая функция циклически выбирает следующий `Social_Link` из списка `live_server_data.Social_Links` и сохраняет его в `current_display_social` для использования `Discord_Manager`.

#### Сетевая система (`samp_network.cpp`)

Класс `Samp_Network` — это низкоуровневая реализация связи **UDP**, отвечающая за открытие и управление сокетом для запросов SA-MP. Теперь он предлагает конструкторы и операторы перемещения для лучшего управления ресурсами.

- **`Initialize()`**: Настраивает сокет для связи **UDP**.
   ```cpp
   // samp_network.cpp (ключевой фрагмент Initialize)
   bool Samp_Network::Initialize(const std::string_view ip, const int port) noexcept {
       if (network_socket != INVALID_SOCKET)
           closesocket(network_socket); // Закрывает существующий сокет
   
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       if (network_socket == INVALID_SOCKET)
           return false;
   
       const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
       setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
   
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(static_cast<u_short>(port));
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr); // Поддержка IPv4
       return true;
   }
   ```
   Инициализирует сокет, устанавливает таймауты для операций отправки и получения, и настраивает структуру адреса (`sockaddr_in`) с IP и портом целевого сервера, используя `inet_pton` для преобразования IP.
- **`Send_Query()`**: Отправляет пакет запроса и получает ответ.
   ```cpp
   // samp_network.cpp (ключевой фрагмент Send_Query)
   bool Samp_Network::Send_Query(const std::span<const char> query_packet, std::span<char> response_buffer, int& received_bytes) noexcept {
       // Отправляет пакет UDP
       if (sendto(network_socket, query_packet.data(), static_cast<int>(query_packet.size()), 0, reinterpret_cast<const sockaddr*>(&server_address), sizeof(server_address)) < 0)
           return false;
   
       sockaddr_in from_address;
       int address_length = sizeof(from_address);
       // Получает ответ
       received_bytes = recvfrom(network_socket, response_buffer.data(), static_cast<int>(response_buffer.size()), 0, reinterpret_cast<sockaddr*>(&from_address), &address_length);
   
       return received_bytes > Constants::QUERY_PACKET_SIZE;
   }
   ```
   Этот метод отправляет `query_packet` (переданный как `std::span` для безопасности буфера) на сервер. Затем пытается получить ответ в `response_buffer`. Возврат указывает, была ли операция успешной и получено ли количество байтов больше размера пакета запроса.

#### Запрос к серверу (`server_query.cpp`)

Класс `Server_Query` посвящен реализации протокола запросов SA-MP (`'i'`), извлекая основную информацию о сервере (игроки, hostname) из ответов **UDP**.

- **`Query()`**: Управляет попытками запросов.
   ```cpp
   // server_query.cpp (ключевой фрагмент Query)
   bool Server_Query::Query(Server_Information& server_data) noexcept {
       for (int attempt = 0; attempt < Constants::MAX_RETRY_ATTEMPTS; ++attempt) {
           if (Try_Query(server_data))
               return true; // Успешный запрос
   
           if (attempt < Constants::MAX_RETRY_ATTEMPTS - 1)
               // Небольшая пауза перед повторной попыткой, чтобы избежать перегрузки
               std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)));
       }

       return false; // Все попытки не удались
   }
   ```
   Реализует стратегию повторных попыток с `MAX_RETRY_ATTEMPTS` и увеличивающимся временем ожидания, чтобы запросы были устойчивы и не перегружали сеть. Вызывает `Try_Query` на каждой попытке.
- **`Assemble_Query_Packet()`**: Собирает пакет запроса SA-MP.
   ```cpp
   // server_query.cpp (ключевой фрагмент Assemble_Query_Packet)
   void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
       memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
       packet = 'i'; // Код запроса информации
   }
   ```
   Стандартный пакет для запроса информации (`'i'`) SA-MP строится, включая подпись "SAMP" и идентификационный байт 'i'.
- **`Parse_Response()`**: Распаковывает бинарный ответ сервера.
   ```cpp
   // server_query.cpp (ключевой фрагмент Parse_Response)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       if (response.size() <= Constants::QUERY_PACKET_SIZE) 
           return false;
   
       auto data_span = response.subspan(Constants::QUERY_PACKET_SIZE); // Пропускает заголовок
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Игнорируется, но читается
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false;

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false;

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false;
   
       // Примечание: Gamemode и Language автоматически пропускаются Read_String_From_Span, если пакет содержит больше данных.
       // Если нужны другие поля, достаточно создать строку и вызвать: Read_String_From_Span(data_span, string_variable);
       return true;
   }
   ```
   Этот метод безопасно читает данные из `response_buffer` (используя `std::span` и вспомогательные функции `Read_From_Span` и `Read_String_From_Span`). Он извлекает количество игроков, максимальное количество игроков и hostname сервера, заполняя структуру `Server_Information`. Неиспользуемые поля (например, защищен ли сервер паролем) читаются, но игнорируются, а другие, такие как "gamemode" и "language", пропускаются, если ответ содержит больше данных, чем нужно **ASI**.
- **Вспомогательные функции чтения:**
   ```cpp
   // server_query.hpp (фрагменты вспомогательных функций чтения)
   template<typename T>
   static bool Read_From_Span(std::span<const char>& s, T& value) noexcept;
   
   static bool Read_String_From_Span(std::span<const char>& s, std::string& str) noexcept;
   ```
   `Read_From_Span` обрабатывает чтение фиксированных типов (целых чисел, булевых значений) из `std::span` и продвигает `span`. `Read_String_From_Span` читает длину строки (как `uint32_t`) и затем саму строку, также продвигая `span`. Это обеспечивает безопасность при разборе байтов и предотвращает чтение за пределами буфера.

#### Менеджер URL (`url_manager.cpp`)

Класс `URL_Manager` управляет коммуникациями HTTPS с **AlderGrounds Integration API**, центральным элементом для новых визуальных и социальных функций **Discord Rich Presence**.

- **`Get_Image_URL_And_Populate_Socials()`**: Метод высокого уровня для получения информации из API.
   ```cpp
   // url_manager.cpp (ключевой фрагмент Get_Image_URL_And_Populate_Socials)
   std::string URL_Manager::Get_Image_URL_And_Populate_Socials(const std::string& ip, const int    port, Server_Information& server_info) {
       if (!session_handle)
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE);
   
       auto api_path_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Path());
       std::wstring path = Utils::Convert_Utf8_To_Wide_String(api_path_accessor.Get());
       path += L"?ip=" + Utils::Convert_Utf8_To_Wide_String(ip) + L"&port=" + std::to_wstring(port);
   
       const std::string json_data = Request_API_Data(path); // HTTP-запрос к API
   
       if (json_data.empty())
           return (server_info.Social_Links.clear(), Constants::DEFAULT_IMAGE); // Ошибка запроса
   
       return Parse_API_Response(json_data, server_info); // Разбирает и заполняет server_info
   }
   ```
   Принимает IP и порт, строит URL API, включая их как параметры. Вызывает `Request_API_Data` для получения данных JSON. В случае успеха `Parse_API_Response` вызывается для извлечения URL изображения (логотипа) и заполнения списка социальных ссылок в `server_info`.
- **`Request_API_Data()`**: Выполняет запрос HTTPS к API.
   ```cpp
   // url_manager.cpp (ключевой фрагмент Request_API_Data)
   std::string URL_Manager::Request_API_Data(const std::wstring& path) {
       auto api_host_accessor = DRALYXOR_SECURE(Secrets::Detail::Get_API_Host());
       const std::wstring wide_host = Utils::Convert_Utf8_To_Wide_String(api_host_accessor.Get());
       HINTERNET connect_handle = WinHttpConnect(session_handle, wide_host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
   
       if (!connect_handle) return "";
   
       HINTERNET request_handle = WinHttpOpenRequest(connect_handle, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
   
       if (!request_handle) return (WinHttpCloseHandle(connect_handle), "");
   
       // Отправить запрос, получить ответ, проверить статус 200, читать данные в цикле
       // ... (детали вызова WinHttpSendRequest, WinHttpReceiveResponse, WinHttpQueryHeaders, WinHttpReadData) ...
       
       WinHttpCloseHandle(request_handle); WinHttpCloseHandle(connect_handle);
       return response_body; // Возвращает JSON как строку
   }
   ```
   Подключается к хосту API (полученному через обфускацию), открывает и отправляет запрос `GET` с указанным путем (`path`). Обрабатывает ответ HTTP, проверяет код статуса (200 OK для успеха) и читает полный текст ответа (должен быть JSON). Все дескрипторы WinHTTP освобождаются в случае успеха или сбоя.
- **`Parse_API_Response()`**: Обрабатывает строку JSON для извлечения данных.
   ```cpp
   // url_manager.cpp (ключевой фрагмент Parse_API_Response)
   std::string URL_Manager::Parse_API_Response(const std::string& json_content,    Server_Information& server_info) {
       server_info.Social_Links.clear(); // Очищает существующие социальные ссылки
       try {
           const auto json = nlohmann::json::parse(json_content);
   
           if (json.value("success", false) && json.contains("data") && json["data"].contains("public")) {
               const auto& public_data = json["data"]["public"];
               const std::vector<std::string> social_keys = { "website", "discord", "youtube", "instagram", "facebook", "tiktok" };
               
               // Извлекает и заполняет социальные ссылки
               for (const auto& key : social_keys) {
                   if (public_data.contains(key)) {
                       std::string value = public_data.value(key, "not-defined");

                       if (!value.empty() && value != "not-defined")
                           server_info.Social_Links.push_back({ key, value });
                   }
               }

               return public_data.value("logo", ""); // Возвращает URL логотипа
           }
       }
       catch (const nlohmann::json::exception&) { /* Обрабатывает ошибку парсинга */ }

       return ""; // Сбой парсинга
   }
   ```
   Использует `nlohmann::json::parse` для преобразования строки JSON в управляемый объект JSON. Перемещается по структуре (`success`, `data`, `public`) и извлекает `logo` (становится `display_image_url`) и перебирает заранее определенные ключи для поиска и заполнения `Social_Links` в `server_info`.

### Структура кода

Проект **SA-MP Rich Presence** тщательно организован в четкой структуре директорий, с исходным кодом (`src/`) и поддиректорией для внешних библиотек (`libraries/`). Имена файлов следуют соглашению `_manager` или `_network` для ясности их назначения. Большинство заголовочных файлов используют расширение `.hpp`, указывая, что это заголовочные файлы C++.

```
src/
├── libraries/               # Содержит необходимые сторонние библиотеки
│   ├── Dralyxor/            # Библиотека обфускации строк
│   ├── Discord/             # Официальная библиотека Discord RPC
│   └── nlohmann/            # Библиотека для работы с JSON
├── asi_update.hpp           # Определение системы автоматического обновления
├── command_line_parser.hpp  # Определение парсера командной строки
├── constants.hpp            # Определения глобальных констант проекта
├── discord_manager.hpp      # Определение менеджера связи с Discord
├── main.cpp                 # Точка входа ASI и основной оркестратор
├── samp_network.hpp         # Определение менеджера сети для запросов SA-MP
├── secrets.hpp              # Определения для обфускации секретов
├── server_manager.hpp       # Определение менеджера информации о сервере
├── server_query.hpp         # Определение логики запросов к серверу SA-MP
├── server_types.hpp         # Определения структур данных сервера
├── url_manager.hpp          # Определение менеджера URL для AlderGrounds Integration API
└── utils.hpp                # Общие утилитарные функции (преобразование строк)
```

#### Глобальные константы (`constants.hpp`)

Этот файл собирает все конфигурации и неизменяемые значения проекта, доступные глобально. Используется `inline constexpr` для обеспечения прямого доступа компилятора к константам, оптимизируя производительность.

```cpp
// constants.hpp (фрагмент)
namespace Constants {
    inline constexpr char ASI_VERSION[] = "1.1"; // Версия для системы обновления
    inline constexpr wchar_t UPDATE_API_HOST[] = L"api.github.com"; // Хост API обновления
    inline constexpr char DEFAULT_IMAGE[] = "https://raw.githubusercontent.com/ocalasans/samp-rich-presence/main/images/default_logo.png"; // Стандартное изображение
    inline constexpr int QUERY_TIMEOUT_MS = 800; // Таймаут запроса в мс
    inline constexpr std::chrono::seconds MAIN_LOOP_INTERVAL = std::chrono::seconds(1); // Интервал основного цикла
}
```
Важные детали, такие как URL API, пути к стандартным изображениям, таймауты сети и интервалы обновления **Discord Rich Presence**, централизованы здесь. Использование `std::chrono::seconds` для интервалов повышает читаемость и предотвращает ошибки с единицами измерения.

#### Структуры данных (`server_types.hpp`)

Этот файл определяет важные `structs` и `using` для организации собираемых и отображаемых данных.

```cpp
// server_types.hpp (фрагмент)
namespace server_types {
    using Social_Link = std::pair<std::string, std::string>; // Кортеж (название сети, URL/значение)
}

struct Server_Information {
    uint16_t Players{0};           // Текущее количество игроков
    uint16_t Max_Players{0};       // Максимальная вместимость игроков
    std::string Hostname{};        // Название сервера
    std::string Server_Address{};  // Например: "192.168.1.1:7777"

    std::vector<server_types::Social_Link> Social_Links{}; // Список социальных ссылок сервера
};
```
`Server_Information` — основная структура для хранения данных сервера. Добавление `std::vector<server_types::Social_Link> Social_Links` отражает новую возможность получения нескольких социальных ссылок из API, организованных как пары `(название_сети, ссылка)`.

#### Обфускация секретов (`secrets.hpp`)

Этот файл посвящен защите конфиденциальной информации, такой как **Discord Application ID** и адреса **AlderGrounds Integration API (пока)**, от легкого обратного проектирования.

```cpp
// secrets.hpp (фрагмент)
#include "libraries/Dralyxor/dralyxor.hpp"

namespace Secrets {
    namespace {
        inline auto& Get_Obfuscated_Discord_App_ID() {
            static auto& dc_app_id_obfuscated = DRALYXOR_KEY("DISCORD_APP_ID", "YOUR_SECRET_KEY_HERE");

            return dc_app_id_obfuscated;
        }
        // ... (другие обфусцированные секреты) ...
    }
    namespace Detail {
        inline auto& Get_Discord_App_ID() {
            return Get_Obfuscated_Discord_App_ID();
        }
        // ... (публичные геттеры для доступа к деобфусцированным секретам) ...
    }
}
```
Библиотека [Dralyxor](https://github.com/ocalasans/dralyxor) используется с макросом `DRALYXOR_KEY` для шифрования строковых литералов в скомпилированном бинарном файле. `DRALYXOR_SECURE` затем используется во время выполнения для деобфускации этих значений при необходимости, добавляя надежный уровень безопасности против статического извлечения ключей.

#### Общие утилиты (`utils.hpp`)

Файл для общих вспомогательных функций, которые могут быть полезны в различных модулях, избегая дублирования кода.

```cpp
// utils.hpp (фрагмент)
namespace Utils {
    inline std::string Convert_Wide_To_Utf8_String(const std::wstring_view wide_string) {
        // ... (реализация преобразования с использованием WideCharToMultiByte) ...
    }

    inline std::wstring Convert_Utf8_To_Wide_String(const std::string_view narrow_string) {
        // ... (реализация преобразования с использованием MultiByteToWideChar) ...
    }
}
```
Содержит функции `Convert_Wide_To_Utf8_String` и `Convert_Utf8_To_Wide_String`, необходимые для взаимодействия с API Windows (использующими UTF-16) и стандартными операциями C++ (обычно использующими UTF-8). Эти функции используют API Windows для безопасного и эффективного преобразования.

### Обработка ошибок и устойчивость

**SA-MP Rich Presence** спроектирован с учетом устойчивости, включая множество механизмов для обработки сетевых ошибок, некорректных входных данных и недоступности сервисов.

- **Таймауты и повторные попытки сети:**
   - **Явные таймауты:** Сокеты сети в `samp_network.cpp` настраивают таймауты (`Constants::QUERY_TIMEOUT_MS`) для операций отправки и получения данных, предотвращая "зависание" программы в ожидании ответа от неактивного сервера.
      ```cpp
      // samp_network.cpp (настройка таймаута)
      const DWORD timeout_ms = Constants::QUERY_TIMEOUT_MS;
      setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      setsockopt(network_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout_ms), sizeof(timeout_ms));
      ```
   - **Многократные попытки запросов:** `Server_Query` выполняет `Constants::MAX_RETRY_ATTEMPTS` запросов в случае сбоя. Реализуется экспоненциальный откат (`std::this_thread::sleep_for(std::chrono::milliseconds(250 * (attempt + 1)))`) перед повторными попытками, снижая нагрузку и увеличивая шансы на успех в условиях нестабильной сети.
- **Устойчивая обработка отключений:**
   - **Плавный переход состояния:** В `server_manager.cpp` статус подключения (`connection_status`) не меняется сразу после одной неудачной попытки запроса. Только если ответ не получен в течение 15 секунд подряд (`now - last_successful_query > std::chrono::seconds(15)`), статус обновляется на `false`. Это предотвращает "мигание" присутствия в Discord из-за небольших потерь пакетов.
      ```cpp
      // server_manager.cpp (логика отключения)
      else { // Если запрос не удался
          if (connection_status && (now - last_successful_query > std::chrono::seconds(15))) {
              connection_status = false;
              display_image_url = Constants::DEFAULT_IMAGE;
              display_server_data = {};
              current_display_social = {};
          }
      }
      ```
   - **Резервное визуальное отображение:** При обнаружении отключения изображение присутствия в Discord возвращается к `Constants::DEFAULT_IMAGE`, а данные сервера/социальные ссылки очищаются, предоставляя пользователю четкую обратную связь о неподключенном состоянии.
- **Обработка некорректных входных данных:**
   - **`command_line_parser.cpp`:** При преобразовании аргумента порта из строки в целое число (`std::stoi`) используется блок `try-catch` для обработки `std::invalid_argument` (не число) или `std::out_of_range` (слишком большое/маленькое число). При ошибке сохраняется порт по умолчанию или парсинг завершается контролируемо, предотвращая сбои.
- **Устойчивость при получении данных API:**
   - **Сбои WinHTTP:** Все операции API WinHTTP в `url_manager.cpp` проверяются на `null` дескрипторы и возвраты `false` на каждом этапе (открытие сессии, подключение, открытие запроса, отправка/получение, чтение данных), гарантируя, что частичные сбои обрабатываются.
   - **Коды статуса HTTP:** После HTTP-запроса `url_manager.cpp` проверяет код статуса HTTP. Только код `200 OK` считается успешным, отбрасывая ответы с ошибками сервера или шлюза.
   - **Безопасное парсинг JSON:** `url_manager.cpp` оборачивает парсинг JSON (`nlohmann::json::parse`) в блок `try-catch(const nlohmann::json::exception&)`. Это предотвращает сбои из-за некорректных или неполных JSON, возвращая пустые строки или стандартное изображение.
- **Безопасные механизмы обновления:**
   - **`asi_update.hpp`:** Процесс проверки обновления в `Check_For_Update` заключен в блок `try-catch(const std::exception&)`. Это гарантирует, что даже если GitHub недоступен, сеть нестабильна или ответ JSON некорректен, **ASI** не завершится с ошибкой, и игра сможет продолжить загрузку, безопасно игнорируя проверку обновления.
   - **Управление дескрипторами WinHTTP:** Освобождение дескрипторов `HINTERNET` в `asi_update.hpp` и `url_manager.cpp` тщательно спланировано для выполнения во всех путях кода (успех и сбой), предотвращая утечки ресурсов.

### Система обработки командной строки

**SA-MP Rich Presence** извлекает важную информацию для своей работы (IP сервера, порт и имя игрока) непосредственно из командной строки игры Grand Theft Auto: San Andreas. Этот метод гарантирует, что **ASI** получает наиболее точные и актуальные данные при запуске игры или подключении к серверу.

#### Парсер командной строки (`command_line_parser.cpp`)

Класс `Command_Line_Parser` отвечает за анализ полной строки команды процесса, идентификацию и извлечение специфичных параметров, используемых SA-MP.

- **`Parse()`**: Точка входа для анализа командной строки.
   ```cpp
   // command_line_parser.cpp (ключевой фрагмент Parse)
   bool Command_Line_Parser::Parse(const std::wstring_view command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       server_ip = Constants::DEFAULT_SERVER_IP; // Значения по умолчанию
       server_port = Constants::DEFAULT_SERVER_PORT;
   
       if (const auto ip_param = Parse_Parameter(command_line, L"-h"); !ip_param.empty())
           server_ip = Utils::Convert_Wide_To_Utf8_String(ip_param); // Извлекает и преобразует IP
   
       if (const auto port_param = Parse_Parameter(command_line, L"-p"); !port_param.empty()) {
           try {
               server_port = std::stoi(std::wstring(port_param)); // Извлекает и преобразует порт (с обработкой ошибок)
           }
           catch (const std::invalid_argument&) {}
           catch (const std::out_of_range&) {}
       }
   
       if (const auto name_param = Parse_Parameter(command_line, L"-n"); !name_param.empty())
           player_name = Utils::Convert_Wide_To_Utf8_String(name_param); // Извлекает и преобразует имя
   
       return !server_ip.empty() && server_port > 0 && !player_name.empty(); // Проверяет наличие необходимых данных
   }
   ```
   Принимает командную строку (`command_line`) как `std::wstring_view` для эффективности. Использует `Parse_Parameter` для поиска и извлечения значений, связанных с `-h` (хост/IP), `-p` (порт) и `-n` (имя игрока). Извлеченные значения (в `std::wstring_view`) преобразуются в `std::string` (UTF-8) с помощью `Utils::Convert_Wide_To_Utf8_String`. Для порта блок `try-catch` окружает `std::stoi` для безопасной обработки ошибок преобразования. Функция возвращает `true`, если все важные параметры (IP, действительный порт и имя игрока) получены.
- **`Parse_Parameter()`**: Вспомогательная функция для извлечения одного параметра.
   ```cpp
   // command_line_parser.cpp (ключевой фрагмент Parse_Parameter)
   std::wstring Command_Line_Parser::Parse_Parameter(const std::wstring_view command_string, const std::wstring_view parameter) {
       if (const size_t position = command_string.find(parameter); position != std::wstring_view::npos) {
           size_t value_start = position + parameter.length();
           value_start = command_string.find_first_not_of(L" \t", value_start); // Пропускает пробелы после параметра

           if (value_start == std::wstring_view::npos)
               return L""; // Параметр найден, но без значения
   
           const size_t value_end = command_string.find(L' ', value_start); // Находит следующий пробел (конец значения)
           
           return std::wstring(command_string.substr(value_start, value_end - value_start)); // Возвращает подстроку значения
       }

       return L""; // Параметр не найден
   }
   ```
   Находит подстроку `parameter` (`-h`, `-p`, `-n`) в `command_string`. Вычисляет начальную позицию значения, игнорируя пробелы/табуляции. Определяет конечную позицию значения (следующий пробел) и возвращает подстроку, соответствующую значению параметра.

### Протокол связи SA-MP

**ASI** напрямую взаимодействует с серверами SA-MP, используя протокол запросов **UDP** для извлечения важной информации в реальном времени. Эта связь реализована для эффективности и устойчивости к сетевым сбоям.

#### Реализация протокола

Класс `Server_Query` — это основа этой реализации, управляющая отправкой пакетов и интерпретацией ответов.

- **Структура пакета запроса SA-MP (`'i'`)**: **ASI** создает пакет **UDP** размером 11 байт для запроса информации:
   - `BYTE 0-3`: Подпись "SAMP" (S A M P).
   - `BYTE 4-9`: Последовательность из 6 байт (обычно адрес IP источника запроса, чтобы сервер мог распознать клиента).
   - `BYTE 10`: Идентификатор запроса 'i' (ASCII 105), указывающий, что **ASI** запрашивает общую информацию о сервере (hostname, игроки и т.д.).
      ```cpp
      // server_query.cpp (сборка пакета)
      void Server_Query::Assemble_Query_Packet(std::span<char> packet) const noexcept {
          memcpy(packet.data(), QUERY_SIGNATURE, sizeof(QUERY_SIGNATURE) - 1); // "SAMP"
          packet = 'i'; // Запрос информации (Information)
      }
      ```
- **Структура ответа сервера**: Когда сервер SA-MP отвечает на запрос 'i', он отправляет пакет **UDP** с последовательностью структурированных данных, которые **ASI** должен разобрать:
   - **Заголовок ответа:** Повторение подписи "SAMP" и 6-байтной последовательности из пакета запроса. **ASI** просто пропускает эти `Constants::QUERY_PACKET_SIZE` байт.
   - **Passworded (`bool`):** Один байт, указывающий, защищен ли сервер паролем. Читается, но не используется.
   - **Players (`uint16_t`):** Количество игроков, подключенных к серверу.
   - **Max_Players (`uint16_t`):** Максимальное количество слотов для игроков, поддерживаемых сервером.
   - **Hostname (строка с префиксом `uint32_t`):** Дружелюбное название сервера. Пакет включает `uint32_t` для указания длины строки hostname, за которой следуют байты самой строки.
   - **Другие поля:** Протокол SA-MP продолжается с "gamemode" и "language", также с префиксом длины. **ASI** читает и пропускает эти поля, чтобы сосредоточиться на необходимых данных `Players`, `Max_Players` и `Hostname`.

   Чтение этих полей выполняется с помощью вспомогательных функций `Read_From_Span` и `Read_String_From_Span`, которые гарантируют, что **ASI** не читает байты за пределами буфера и корректно обрабатывает чтение данных фиксированной и переменной длины (строк).
   ```cpp
   // server_query.cpp (разбор ответа)
   bool Server_Query::Parse_Response(std::span<const char> response, Server_Information& server_data) noexcept {
       // ... (проверка размера и subspan для данных) ...
   
       [[maybe_unused]] bool passworded;

       if (!Read_From_Span(data_span, passworded))
           return false; // Читает булево 'passworded'
   
       if (!Read_From_Span(data_span, server_data.Players))
           return false; // Читает 'Players'

       if (!Read_From_Span(data_span, server_data.Max_Players))
           return false; // Читает 'Max_Players'

       if (!Read_String_From_Span(data_span, server_data.Hostname))
           return false; // Читает 'Hostname'
   
       // Поля 'Gamemode' и 'Language' автоматически пропускаются Read_String_From_Span
       // для перемещения span за их данные в буфере.
       uint32_t length_placeholder; // Временная переменная для хранения длины.

       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Читает длину gamemode

       if (data_span.size() < length_placeholder)
           return false; // Проверяет границы

       data_span = data_span.subspan(length_placeholder); // Пропускает данные gamemode
   
       if (!Read_From_Span(data_span, length_placeholder))
           return false; // Читает длину language

       if (data_span.size() < length_placeholder)
           return false; // Проверяет границы

       data_span = data_span.subspan(length_placeholder); // Пропускает данные language
   
       return true;
   }
   ```
   В приведенном выше примере логика `data_span = data_span.subspan(length_placeholder);` — это эффективный способ "пропуска" количества байт, прочитанных для строки, содержимое которой не требуется для Rich Presence.

### Преимущества SA-MP Rich Presence

**SA-MP Rich Presence** значительно улучшает опыт как для игроков, так и для администраторов серверов, предлагая заметные преимущества:

1. **Для игроков:**
   - **Легкая видимость:** Автоматически делитесь своим игровым статусом в Discord с друзьями, показывая, где вы играете.
   - **Подробная информация:** Мгновенный доступ к данным сервера (название, количество игроков, IP, персонализированный логотип) прямо в Discord, устраняя необходимость искать эту информацию в других местах.
   - **Прямой доступ к сообществу:** Быстро находите и переходите по социальным сетям сервера через ротационные иконки в присутствии Discord, упрощая присоединение к активным сообществам.
   - **Быстрое подключение с друзьями:** Приглашайте или присоединяйтесь к тому же серверу, что и ваши друзья, одним щелчком благодаря функции "Join".
   - **Всегда актуальный опыт:** Система автоматического обновления гарантирует использование самой оптимизированной и функциональной версии **ASI**.
2. **Для серверов:**
   - **Естественный маркетинг:** Присутствие ваших игроков в Discord действует как цифровой билборд, рекламируя ваш сервер органичной аудитории (д朋友ям игроков) 24 часа в сутки.
   - **Сильная визуальная идентичность:** Персонализированный логотип и ротация социальных ссылок позволяют вашему серверу выделяться и создавать профессиональный и современный образ в среде Discord.
   - **Увеличение вовлеченности:** Упростите путь для новых и старых игроков к вашим социальным платформам, укрепляя ваше сообщество и вовлеченность за пределами игры.
   - **Упрощенный рекрутинг:** Функция "Join" ускоряет процесс для новых игроков, устраняя барьеры и поощряя эксперименты.
   - **Консистентные данные:** Благодаря интеграции с **AlderGrounds Integration API** отображение информации унифицировано и обновляется централизованно, гарантируя, что бренд и контакты вашего сервера всегда актуальны.

## Лицензия

Данный ASI лицензирован в соответствии с лицензией Apache License 2.0, которая позволяет:

- ✔️ Коммерческое и частное использование
- ✔️ Модификацию исходного кода
- ✔️ Распространение кода
- ✔️ Предоставление патентных прав

### Условия:

- Сохранение уведомления об авторских правах
- Документирование значительных изменений
- Включение копии лицензии Apache 2.0

Для получения дополнительной информации о лицензии: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Все права защищены**