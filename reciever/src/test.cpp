#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg) {
    try {
        // Convert payload to integer
        int received_int = std::stoi(msg->get_payload());
        std::cout << "Received integer: " << received_int << std::endl;
        
        // Echo back the received integer
    } catch (const std::exception& e) {
        std::cerr << "Error processing message: " << e.what() << std::endl;
        s->send(hdl, "Error: Invalid integer format", websocketpp::frame::opcode::text);
    }
}

int main() {
    server ws_server;

    // Initialize ASIO
    ws_server.init_asio();

    ws_server.set_access_channels(websocketpp::log::alevel::none);
    ws_server.set_error_channels(websocketpp::log::elevel::none);

    // Set up handlers
    ws_server.set_message_handler([&ws_server](auto hdl, auto msg) {
        on_message(&ws_server, hdl, msg);
    });

    // Listen on port 5000
    ws_server.listen(5000);

    // Start the server
    ws_server.start_accept();
    std::cout << "WebSocket server started on port 5000" << std::endl;

    // Run the ASIO io_service
    ws_server.run();

    return 0;
}
