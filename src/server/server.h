#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
//https://www.boost.org/doc/libs/latest/doc/html/boost_asio/tutorial/tutdaytime3/src.html
class server {
public:
    server(boost::asio::io_context& io, unsigned short port);

private:
    void do_accept();

    boost::asio::ip::tcp::acceptor acceptor_;
};
