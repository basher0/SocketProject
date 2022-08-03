#include "Server.hpp"


namespace SP
{
	Core::Core(boost::asio::io_context& io_context, u_short port) : _io(io_context),
		_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
	{
		start_accept();
	}
	void Core::start_accept()
	{
		boost::function<void(Session*)> disconnect =
			boost::bind(&Core::OnClientDisconnect, this, _1);

		boost::function<void(Message)> message =
			boost::bind(&Core::OnClientMessage, this, _1);

		
		std::size_t id = m_clients.size();
		Session* session = new Session(_io, id, disconnect, message);

		_acceptor.async_accept(session->socket(),
			boost::bind(&Server::accept, this, session,
				boost::asio::placeholders::error));
	}

	void Core::accept(Session* sessionPtr, const boost::system::error_code& error)
	{
		if (!error)
		{
			sessionPtr->start(m_clients);
			OnClientConnect(sessionPtr);

			m_clients.push_back(sessionPtr);
		}
		else
		{
			delete sessionPtr;
		}
		start_accept();
	}

	Server::Server(boost::asio::io_context& io_context, u_short port)
		: Core(io_context, port)
	{
		std::cout << "Server is listening on port " << port << " ..." << std::endl;
	}
}
