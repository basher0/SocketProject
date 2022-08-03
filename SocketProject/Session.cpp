#include "Session.hpp"

namespace SP
{
    Session::Session(boost::asio::io_context& io_context, std::size_t id,
        boost::function<void(Session*)> disconnect,
        boost::function<void(Message)> message) :
        _socket(io_context), _id(id),
        _disconnect(disconnect),
        _message(message)

    {


    }
    Session::~Session()
    {
        std::cout << "A Session was destroyed!" << std::endl;
    }

    tcp::socket& Session::socket() const
    {
        return this->_socket;
    }

    uint32_t Session::getId() const
    {
        return this->_id;
    }

    void Session::start(std::vector<Session*>& clients)
    {
        m_cMgnt = &clients;

        _socket.async_read_some(boost::asio::buffer(received, BUFFER_SIZE),
            boost::bind(&Session::readHandler, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));

    }

    void Session::readHandler(const boost::system::error_code& error, size_t bytes_transferred)
    {

        if (!error)
        {
            _socket.async_read_some(boost::asio::buffer(received, BUFFER_SIZE),
                boost::bind(&Session::readHandler, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));


            BytesHandler _b(received);

            _message({ this, _b });

            memset(received, 0, BUFFER_SIZE);

        }
        else
        {
            _disconnect(this);
            close();
        }
    }

    void Session::writeHandler(const boost::system::error_code& error)
    {
        if (!error)
        {
            _socket.async_read_some(boost::asio::buffer(received, BUFFER_SIZE),
                boost::bind(&Session::readHandler, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
        else
        {
            _disconnect(this);
            close();
        }
    }

    void Session::close()
    {
       _socket.close();

       m_cMgnt->erase(std::remove(m_cMgnt->begin(),
           m_cMgnt->end(), m_cMgnt->at(_id)), m_cMgnt->end());

       std::cout << m_cMgnt->size() << std::endl;
       delete this;
    }



    void Session::write(const std::string& data) const
    {
        boost::asio::write(_socket, boost::asio::buffer(data, data.size()));
    }

    void Session::write(const std::string& data, size_t size) const
    {
        boost::asio::write(_socket, boost::asio::buffer(data, size));
    }
}