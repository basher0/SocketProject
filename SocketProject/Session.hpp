#pragma once
#include "Header.hpp"
#include "BytesHandler.hpp"


namespace SP
{
    class Session;

    struct Message
    {
        Session* client;
        BytesHandler message;
    };

    class Session
    {
    private:
        mutable tcp::socket _socket;
        mutable SP::bytes received{};
        mutable std::size_t _id{};

        std::vector<Session*>* m_cMgnt = nullptr;
        std::size_t* m_clientsCount = nullptr;

        boost::function<void(Session*)> _disconnect;
        boost::function<void(Message)> _message;

    public:
        Session(boost::asio::io_context& io_context, std::size_t id,
            boost::function<void(Session*)> disconnect,
            boost::function<void(Message)> message);

        ~Session() = default;

        /* Get Session Socket */
        tcp::socket& socket() const;

        /* Get connection ID */
        uint32_t getId() const;

        void start(std::vector<Session*>& clients);

        /* Send socket message */
        void write(const std::string& data) const;

        /* Send socket message */
        void write(const std::string& data, size_t size) const;

        /* Close client connection */
        void close();

    private:
        void readHandler(const boost::system::error_code& error, size_t bytes_transferred);
        void writeHandler(const boost::system::error_code& error);

    };
}
