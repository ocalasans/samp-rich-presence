#ifndef COMMAND_LINE_PARSER_H
    #define COMMAND_LINE_PARSER_H

    #include <string>
    #include <windows.h>

    class Command_Line_Parser {
        public:
            static bool Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name);
        private:
            static std::string Convert_To_String(const std::wstring& wide_string);
            static std::wstring Parse_Parameter(const std::wstring& command_string, const wchar_t* parameter);
    };
#endif