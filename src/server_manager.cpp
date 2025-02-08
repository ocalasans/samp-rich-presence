#include "server_manager.h"
#include "constants.h"
#include <chrono>

Server_Manager::Server_Manager(const std::string& ip, int port, const std::string& name)
    : connection_status(false)
    , server_ip(ip)
    , server_port(port)
    , player_name(name)
    , current_image_url(Constants::DEFAULT_IMAGE)
    , network_manager()
    , server_query(network_manager)
    , last_successful_query(std::chrono::steady_clock::now())
{}

Server_Manager::~Server_Manager() = default;

bool Server_Manager::Initialize() {
    current_image_url = Constants::DEFAULT_IMAGE;

    return network_manager.Initialize(server_ip, server_port);
}

bool Server_Manager::Update() {
    bool query_success = server_query.Query(server_data);
    auto current_time = std::chrono::steady_clock::now();
    
    if (query_success) {
        connection_status = true;
        last_successful_query = current_time;
        server_data.Server_Address = Get_Server_Address();
        std::string new_image_url = url_manager.Get_Image_URL(server_data.Server_Address);
        
        if (!new_image_url.empty())
            current_image_url = new_image_url;
    }
    else {
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(
            current_time - last_successful_query);
        
        if (duration.count() > 15) {
            connection_status = false;
            current_image_url = Constants::DEFAULT_IMAGE;
        }
    }
    
    return true;
}