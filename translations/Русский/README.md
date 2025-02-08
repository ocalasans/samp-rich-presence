# SA-MP Rich Presence

SA-MP Rich Presence - это ASI для SA-MP (San Andreas Multiplayer), который автоматически обновляет ваш статус Discord с подробной информацией о сервере. ASI внедряется в игру при подключении к серверу SA-MP, отображая информацию о сервере.

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
  - [Что такое ASI?](#что-такое-asi)
  - [Функциональность](#функциональность)
    - [Discord Rich Presence](#discord-rich-presence)
  - [Требования](#требования)
  - [Установка](#установка)
  - [Подробная техническая архитектура](#подробная-техническая-архитектура)
    - [Основная система (main.cpp)](#основная-система-maincpp)
    - [Менеджер Discord (discord\_manager.cpp)](#менеджер-discord-discord_managercpp)
    - [Менеджер сервера (server\_manager.cpp)](#менеджер-сервера-server_managercpp)
    - [Сетевая система (network\_manager.cpp)](#сетевая-система-network_managercpp)
    - [Запрос к серверу (server\_query.cpp)](#запрос-к-серверу-server_querycpp)
  - [Интеграция с SPC](#интеграция-с-spc)
    - [Что такое SPC Integration?](#что-такое-spc-integration)
    - [Как это работает](#как-это-работает)
    - [Менеджер URL (url\_manager.cpp)](#менеджер-url-url_managercpp)
  - [Для Разработчиков Сервера](#для-разработчиков-сервера)
  - [Структура Кода](#структура-кода)
    - [Глобальные Константы (constants.h)](#глобальные-константы-constantsh)
    - [Структуры Данных (server\_types.h)](#структуры-данных-server_typesh)
  - [Обработка Ошибок](#обработка-ошибок)
  - [Система Обработки Командной Строки](#система-обработки-командной-строки)
    - [Парсер Командной Строки (command\_line\_parser.cpp)](#парсер-командной-строки-command_line_parsercpp)
  - [Протокол Коммуникации SA-MP](#протокол-коммуникации-sa-mp)
    - [Реализация Протокола](#реализация-протокола)
  - [Преимущества SA-MP Rich Presence](#преимущества-sa-mp-rich-presence)
  - [Дополнительные Технические Заметки](#дополнительные-технические-заметки)
  - [Лицензия](#лицензия)
    - [Условия:](#условия)

## Что такое ASI?

ASI - это динамическая библиотека (.dll), переименованная с расширением .asi, которая автоматически загружается ASI loader'ом при запуске GTA San Andreas. Плагины ASI позволяют модифицировать или добавлять функциональность в игру без изменения оригинальных файлов, являясь одним из самых популярных способов моддинга для GTA San Andreas и других игр серии GTA. С установленным ASI loader'ом вы можете легко устанавливать или удалять модификации, просто добавляя или удаляя файлы .asi из папки игры.

## Функциональность

### Discord Rich Presence

Discord Rich Presence - это функция, которая позволяет приложениям показывать подробную информацию о том, что делает пользователь, прямо в профиле Discord. В случае SA-MP Rich Presence отображается следующая информация:
- Название сервера (Hostname)
- Имя игрока
- Текущее количество игроков и максимальное количество игроков
- IP и порт сервера
- Пользовательское изображение сервера (требуется плагин [SPC Integration](https://github.com/spc-samp/spc-integration))
- Время игры
- Статус подключения

## Требования

- Клиент SA-MP (если нет: [clients-samp](https://github.com/spc-samp/clients-samp))
- Приложение Discord Desktop
- Операционная система Windows
- Visual C++ Runtime
- ASI Loader, установленный в GTA San Andreas

## Установка

1. Скачайте последнюю версию скомпилированного ASI в [releases](https://github.com/ocalasans/samp-rich-presence/releases)
2. Убедитесь, что у вас установлен ASI Loader в GTA San Andreas
3. Скопируйте скачанный файл .asi в папку GTA San Andreas
4. Запустите игру с SA-MP
5. ASI автоматически инициализируется при входе на сервер

## Подробная техническая архитектура

### Основная система (main.cpp)

Файл main.cpp является точкой входа ASI и отвечает за:
1. Инициализацию системы:
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

2. Управление потоком обновления:
   ```cpp
   DWORD WINAPI Update_Thread(LPVOID) {
       // Инициализация WSA для сетевых операций
       WSAData wsa_data;
       if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
           return 1;
       
       // Обработка параметров командной строки
       std::string server_ip, player_name;
       int server_port;
       
       // Инициализация менеджеров
       Global_Server_Manager = std::make_unique<Server_Manager>(server_ip, server_port, player_name);
       Global_Discord_Manager = std::make_unique<Discord_Manager>();
       
       // Основной цикл обновления
       while (true) {
           Global_Server_Manager->Update();
           Global_Discord_Manager->Update_Presence(...);
           Sleep(Constants::PRESENCE_UPDATE_INTERVAL);
       }
   }
   ```

### Менеджер Discord (discord_manager.cpp)

Discord_Manager отвечает за всю интеграцию с Discord Rich Presence:
1. Инициализация Discord RPC:
   ```cpp
   void Discord_Manager::Initialize() noexcept {
       Sleep(5000);  // Ожидание инициализации Discord
       
       DiscordEventHandlers discord_handlers{};
       Discord_Initialize("DISCORD_APP_ID", &discord_handlers, 1, NULL); // "DISCORD_APP_ID > Application ID"
       
       start_timestamp = time(nullptr);  // Отметка начала сессии
   }
   ```

2. Обновление присутствия:
   ```cpp
   void Discord_Manager::Update_Presence(const Server_Information& server_info, std::string_view player_name, std::string_view current_image, bool is_connected) noexcept {
       DiscordRichPresence discord_presence{};
       
       // Настройка базовой информации
       discord_presence.state = player_name.data();
       discord_presence.details = server_info.Hostname.c_str();
       discord_presence.largeImageKey = current_image.data();
       
       // Добавление информации о сервере
       discord_presence.largeImageText = server_info.Server_Address.c_str();
       discord_presence.startTimestamp = start_timestamp;
       discord_presence.partySize = server_info.Players;
       discord_presence.partyMax = server_info.Max_Players;
       
       Discord_UpdatePresence(&discord_presence);
   }
   ```

### Менеджер сервера (server_manager.cpp)

Server_Manager координирует все операции, связанные с сервером:
1. Управление состоянием:
   ```cpp
   Server_Manager::Server_Manager(const std::string& ip, int port, const std::string& name)
       : connection_status(false)
       , server_ip(ip)
       , server_port(port)
       , player_name(name)
       , current_image_url(Constants::DEFAULT_IMAGE)
   {}
   ```

2. Обновление информации:
   ```cpp
   bool Server_Manager::Update() {
       bool query_success = server_query.Query(server_data);
       
       if (query_success) {
           connection_status = true;
           server_data.Server_Address = Get_Server_Address();
           
           // Попытка получить пользовательское изображение сервера
           std::string new_image_url = url_manager.Get_Image_URL(server_data.Server_Address);

           if (!new_image_url.empty())
               current_image_url = new_image_url;
       }
       // ...
   }
   ```

### Сетевая система (network_manager.cpp)

Network_Manager реализует всю сетевую коммуникацию:
1. Инициализация сокета:
   ```cpp
   bool Network_Manager::Initialize(std::string_view ip, int port) noexcept {
       network_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       
       // Настройка таймаута
       timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
       setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
       
       // Настройка адреса сервера
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(port);
       inet_pton(AF_INET, ip.data(), &server_address.sin_addr);
       
       return true;
   }
   ```

### Запрос к серверу (server_query.cpp)

Server_Query реализует протокол запросов SA-MP:
1. Сборка пакета запроса:
   ```cpp
   bool Server_Query::Assemble_Query_Packet(char* packet) noexcept {
       memcpy(packet, QUERY_SIGNATURE, 4);  // "SAMP"
       packet[10] = 'i';  // Information query

       return true;
   }
   ```

2. Обработка ответа:
   ```cpp
   bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
       // Извлечение информации, такой как:
       // - Количество игроков
       // - Максимальное количество игроков
       // - Hostname
   }
   ```

## Интеграция с SPC

### Что такое SPC Integration?

[SPC Integration](https://github.com/spc-samp/spc-integration) - это плагин, разработанный для **SA-MP** (San Andreas Multiplayer) и **open.mp** (Open Multiplayer), который служит мостом между серверами и экосистемой **SPC**. Плагин собирает важную информацию о сервере, включая:
- IP и порт
- URL сайта сервера
- URL пользовательского изображения
- Информацию о конфигурации

Эта информация отправляется и безопасно хранится в хранилище данных **SPC (SA-MP Programming Community)**, позволяя интеграцию с различными приложениями **SPC**, включая Rich Presence.

### Как это работает

1. Сервер использует плагин [SPC Integration](https://github.com/spc-samp/spc-integration) для регистрации своего пользовательского изображения
2. Изображение сохраняется в хранилище данных **SPC** внутри JSON-файла сервера
3. Когда игрок подключается к серверу:
    - URL_Manager ASI пытается получить JSON-файл сервера (формат: `ip-port.json`)
    - Если файл найден, извлекается URL изображения из параметра `spc_integration_image`
    - Затем изображение отображается в Discord Rich Presence игрока

### Менеджер URL (url_manager.cpp)

URL_Manager отвечает за всю коммуникацию с хранилищем данных **SPC**:
1. Получение изображения сервера:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       std::string formatted_address = server_address;
       // Преобразование ":" в "-" в адресе
       size_t colon_pos = formatted_address.find(':');

       if (colon_pos != std::string::npos)
           formatted_address.replace(colon_pos, 1, "-");
       
       // Получение JSON сервера
       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;
       
       return image_url;
   }
   ```

2. Обработка JSON:
   ```cpp
   std::string URL_Manager::Parse_JSON(const std::string& json_content) {
       const std::string key = "\"spc_integration_image\":";
       size_t key_pos = json_content.find(key);
       
       // Извлечение URL изображения из JSON
       // ...
       
       return image_url;
   }
   ```

## Для Разработчиков Сервера

Если вы разработчик сервера SA-MP, мы настоятельно рекомендуем установить плагин [SPC Integration](https://github.com/spc-samp/spc-integration) по следующим причинам:
1. Видимость:
    - Пользовательское изображение вашего сервера будет отображаться в Discord у всех игроков, использующих этот ASI.
    - Повышает узнаваемость бренда вашего сервера.
    - Обеспечивает более профессиональную презентацию.

2. Преимущества:
    - Повышенная вовлеченность игроков.
    - Визуальное отличие в Discord.
    - Автоматическая интеграция с Rich Presence.

3. Как реализовать:
   - Прочитайте репозиторий плагина [SPC Integration](https://github.com/spc-samp/spc-integration), чтобы узнать, как реализовать.

## Структура Кода

Проект организован в несколько компонентов:
```
src/
├── discord/               # Библиотека Discord RPC
├── command_line_parser.*  # Обработка аргументов
├── constants.h           # Глобальные константы
├── discord_manager.*      # Интеграция с Discord
├── main.cpp              # Точка входа
├── network_manager.*      # Сетевые операции
├── server_manager.*      # Управление сервером
├── server_query.*        # Протокол SA-MP
├── server_types.h        # Структуры данных
└── url_manager.*         # Интеграция с SPC
```

### Глобальные Константы (constants.h)

Файл определяет несколько важных констант:
```cpp
namespace Constants {
    // Значения по умолчанию
    inline constexpr char DEFAULT_SERVER_IP[] = "127.0.0.1";
    inline constexpr int DEFAULT_SERVER_PORT = 7777;
    
    // Сетевые настройки
    inline constexpr int QUERY_TIMEOUT = 1000;
    inline constexpr int QUERY_PACKET_SIZE = 11;
    inline constexpr int QUERY_BUFFER_SIZE = 512;
    
    // Настройки повторных попыток
    inline constexpr int MAX_RETRY_ATTEMPTS = 3;
    
    // Интервалы
    inline constexpr int PRESENCE_UPDATE_INTERVAL = 5000;
}
```

### Структуры Данных (server_types.h)

Определяет основные структуры:
```cpp
struct Server_Information {
    uint16_t Players{ 0 };           // Игроки онлайн
    uint16_t Max_Players{ 0 };       // Максимум игроков
    std::string Hostname;            // Имя сервера
    std::string Server_Image;        // URL изображения
    std::string Server_Address;      // Адрес сервера
};
```

## Обработка Ошибок

Система реализует надежную систему обработки ошибок:
1. Сетевой таймаут:
   ```cpp
   timeval Socket_Timeout{ 0, Constants::QUERY_TIMEOUT };
   setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Socket_Timeout), sizeof(Socket_Timeout));
   ```

2. Система повторных попыток:
   ```cpp
   bool Server_Query::Try_Query(Server_Information& server_data, int retry_count) noexcept {
       for (int attempt = 0; attempt <= retry_count; attempt++) {
           if (network_manager.Send_Query(...))
               return true;
           
           // Ждем перед повторной попыткой
           std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
       }

       return false;
   }
   ```

3. Резервное изображение по умолчанию:
   ```cpp
   std::string URL_Manager::Get_Image_URL(const std::string& server_address) {
       // Если что-то пойдет не так, возвращаем изображение по умолчанию
       if (!session_handle)
           return Constants::DEFAULT_IMAGE;

       std::string image_url;

       if (!Get_URL_From_File(formatted_address, image_url))
           return Constants::DEFAULT_IMAGE;

       return image_url;
   }
   ```

4. Мониторинг состояния подключения:
   ```cpp
   bool Server_Manager::Update() {
       auto current_time = std::chrono::steady_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_successful_query);
       
       // Если нет ответа более 15 секунд, считаем отключенным
       if (duration.count() > 15) {
           connection_status = false;
           current_image_url = Constants::DEFAULT_IMAGE;
       }
   }
   ```

## Система Обработки Командной Строки

ASI реализует гибкую систему для обработки аргументов командной строки:

### Парсер Командной Строки (command_line_parser.cpp)

1. Основная обработка:
   ```cpp
   bool Command_Line_Parser::Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name) {
       // Устанавливаем значения по умолчанию
       server_ip = Constants::DEFAULT_SERVER_IP;
       server_port = Constants::DEFAULT_SERVER_PORT;

       // Обрабатываем каждый параметр
       std::wstring ip_parameter = Parse_Parameter(command_string, L"-h");
       std::wstring port_parameter = Parse_Parameter(command_string, L"-p");
       std::wstring name_parameter = Parse_Parameter(command_string, L"-n");

       // Конвертируем и проверяем значения
       if (!ip_parameter.empty())
           server_ip = Convert_To_String(ip_parameter);

       if (!port_parameter.empty())
           server_port = std::stoi(port_parameter);

       if (!name_parameter.empty())
           player_name = Convert_To_String(name_parameter);

       // Проверяем наличие всех необходимых параметров
       return !server_ip.empty() && server_port > 0 && !player_name.empty();
   }
   ```

2. Извлечение параметров:
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

## Протокол Коммуникации SA-MP

ASI реализует протокол запросов SA-MP для получения информации о сервере:
1. Структура пакета запроса:
    - 4 байта: Подпись "SAMP"
    - 7 байтов: Дополнительные данные
    - Последний байт: 'i' (указывает на запрос информации)

2. Структура ответа:
    - Заголовок пакета
    - Players (uint16_t)
    - Max_Players (uint16_t)
    - Hostname (string)

### Реализация Протокола

```cpp
bool Server_Query::Parse_Response(char* response_buffer, int received_bytes, Server_Information& server_data) noexcept {
    char* current_pos = response_buffer + Constants::QUERY_PACKET_SIZE;
    const char* buffer_end = response_buffer + received_bytes;

    // Пропускаем "password"
    current_pos += sizeof(bool);
    
    // Читаем фиксированные данные
    memcpy(&server_data.Players, current_pos, sizeof(server_data.Players));
    current_pos += sizeof(server_data.Players);
    
    memcpy(&server_data.Max_Players, current_pos, sizeof(server_data.Max_Players));
    current_pos += sizeof(server_data.Max_Players);

    // Читаем Hostname и пропускаем "gamemode" и "language"
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
    
    // Пропускаем "gamemode" и "language"
    // ...

    return true;
}
```

## Преимущества SA-MP Rich Presence

1. Для Игроков:
    - Быстрый просмотр текущего сервера.
    - Подробная информация о сервере.
    - Идеальная интеграция с Discord.
    - Более социальный игровой опыт.

2. Для Серверов:
    - Повышенная видимость через Discord.
    - Органический маркетинг через игроков.
    - Персонализированная визуальная идентичность (с плагином [SPC Integration](https://github.com/spc-samp/spc-integration)).
    - Статистика в реальном времени.

## Дополнительные Технические Заметки

1. Потокобезопасность:
    - ASI использует один поток для обновлений.
    - Менеджеры потокобезопасны по дизайну.
    - Ресурсы правильно синхронизированы.

2. Использование Памяти:
    - Минимальное выделение памяти.
    - Предварительно выделенные буферы для запросов.
    - Автоматическое управление ресурсами (RAII).

3. Производительность:
    - Оптимизированные запросы с таймаутом.
    - Умная система повторных попыток.
    - Настраиваемый интервал обновления.

4. Совместимость:
    - Поддержка Unicode.
    - Совместимость с современным Windows.
    - Поддержка IPv4.

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