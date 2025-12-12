#include "connection.h"
#include <iostream>

using boost::asio::ip::tcp;

connection::connection(tcp::socket socket)
    : socket_(std::move(socket)) {}

connection::ptr connection::create(tcp::socket socket) {
    return std::make_shared<connection>(std::move(socket));
}

void connection::start() {
    do_read();
}

void connection::do_read() {
    auto self = shared_from_this();

    socket_.async_read_some(
        boost::asio::buffer(buffer_),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::string msg(buffer_.data(), length);
                std::cout << "Received: " << msg << std::endl;

                // keep reading
                do_read();
            }
        }
    );
}
