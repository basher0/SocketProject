#pragma once
#include "Header.hpp"
#include "Session.hpp"

namespace SP
{
    class Core
    {
    private:
        boost::asio::io_context& _io;
        tcp::acceptor _acceptor;



    public:
        Core(boost::asio::io_context& io_context, u_short port);

    protected:
        std::size_t m_clientsCount = 0;
        std::vector<Session*> m_clients;

        virtual void OnClientConnect(Session*) {};
        virtual void OnClientDisconnect(Session*) {};
        virtual void OnClientMessage(Message) {};

    private:
        void start_accept();
        void accept(Session* sessionPtr, const boost::system::error_code& error);
    };

    class Server : public Core
    {
    public:
        Server(boost::asio::io_context& io_context, u_short port);
    };
}



