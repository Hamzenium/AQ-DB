#include "server.h"
#include "connection.h"

#include <iostream>

using boost::asio::ip::tcp;

server::server(boost::asio::io_context& io, unsigned short port)
    : acceptor_(io, tcp::endpoint(tcp::v4(), port))
{
    std::cout << "Async TCP server running on port " << port << std::endl;
    do_accept();
}

void server::do_accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::cout << "Client connected\n";
                auto conn = connection::create(std::move(socket));
                conn->start();
            }

            do_accept(); // keep accepting
        }
    );
}
