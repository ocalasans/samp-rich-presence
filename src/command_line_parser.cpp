#include "command_line_parser.h"
#include "constants.h"

bool Command_Line_Parser::Parse(const wchar_t* command_line, std::string& server_ip, int& server_port, std::string& player_name) {
    server_ip = Constants::DEFAULT_SERVER_IP;
    server_port = Constants::DEFAULT_SERVER_PORT;

    std::wstring command_string(command_line);

    std::wstring ip_parameter = Parse_Parameter(command_string, L"-h");

    if (!ip_parameter.empty())
        server_ip = Convert_To_String(ip_parameter);

    std::wstring port_parameter = Parse_Parameter(command_string, L"-p");

    if (!port_parameter.empty())
        server_port = std::stoi(port_parameter);

    std::wstring name_parameter = Parse_Parameter(command_string, L"-n");

    if (!name_parameter.empty())
        player_name = Convert_To_String(name_parameter);

    return !server_ip.empty() && server_port > 0 && !player_name.empty();
}

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

std::string Command_Line_Parser::Convert_To_String(const std::wstring& wide_string) {
    if (wide_string.empty()) 
        return "";

    int required_size = WideCharToMultiByte(CP_UTF8, 0, wide_string.c_str(), -1, NULL, 0, NULL, NULL);
    std::string result(required_size - 1, 0);
    WideCharToMultiByte(CP_UTF8, 0, wide_string.c_str(), -1, &result[0], required_size, NULL, NULL);

    return result;
}