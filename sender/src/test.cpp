#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <thread>
#include <iostream>
#include <climits>
#include <unistd.h>
#include <cstdlib> // for getenv()

typedef websocketpp::client<websocketpp::config::asio_client> client;

// Function to handle messages from the server
void on_message(client* c, websocketpp::connection_hdl hdl, client::message_ptr msg) {
    std::cout << "Received reply: " << msg->get_payload() << std::endl;
}

std::string get_server_uri() {
    const char* ip = std::getenv("WS_SERVER_IP");
    const char* port = std::getenv("WS_SERVER_PORT");

    if (!ip) ip = "localhost"; // default if not set
    if (!port) port = "5000";  // default if not set

    return "ws://" + std::string(ip) + ":" + std::string(port);
}


int main() {
    client ws_client;

    try {
        ws_client.init_asio();

        // Set up handlers
        ws_client.set_message_handler([&ws_client](auto hdl, auto msg) {
            on_message(&ws_client, hdl, msg);
        });
        ws_client.set_access_channels(websocketpp::log::alevel::none);

        ws_client.set_access_channels(websocketpp::log::alevel::connect |
                            websocketpp::log::alevel::disconnect);

        std::string uri = get_server_uri();
        std::cout << "Connecting to: " << uri << std::endl;

        websocketpp::lib::error_code ec;
        auto connection = ws_client.get_connection(uri, ec);
        //connection->append_header("Origin", "http://" + uri); // Some servers require this

        ws_client.set_open_handshake_timeout(5000); // 5 seconds
        if (ec) {
            std::cerr << "Connection error: " << ec.message() << std::endl;
            return 1;
        }

        websocketpp::lib::error_code connect_ec;
        ws_client.connect(connection);
        if (connect_ec) {
            std::cerr << "connect error: " << connect_ec.message() << std::endl;
            return 1;
        }
        
        std::thread t([&ws_client]() { ws_client.run(); });
        
        
        
        for (int i = 0; i < INT_MAX; i++){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            connection->send(std::to_string(i), websocketpp::frame::opcode::text);
            std::cout << "Sent integer: " << i << std::endl;
        } 
        
        connection->close(websocketpp::close::status::normal, "Done");
        t.join();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }    

    return 0;
}
