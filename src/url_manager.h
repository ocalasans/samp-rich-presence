#ifndef URL_MANAGER_H
    #define URL_MANAGER_H

    #include <string>
    #include <winsock2.h>
    #include <winhttp.h>

    #pragma comment(lib, "winhttp.lib")

    class URL_Manager {
        public:
            URL_Manager();
            ~URL_Manager();

            std::string Get_Image_URL(const std::string& server_address);
        private:
            bool Get_URL_From_File(const std::string& server_address, std::string& image_url);
            std::string Parse_JSON(const std::string& json_content);

            HINTERNET session_handle;
            static constexpr wchar_t BASE_HOST[] = L"example_site.com";
            static constexpr wchar_t BASE_PATH[] = L"/example_directory/";
    };
#endif