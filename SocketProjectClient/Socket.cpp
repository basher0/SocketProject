#include "Socket.hpp"

namespace SP 
{
	SP::Socket::Socket(context& io, const char* ip, ushort port) :
		m_socket(io),
		m_endpoint(tcp::endpoint(address::from_string(ip), port)),
		m_running(true)
	{
		start_connection();
	}

	void Socket::start_connection()
	{
		m_running = true;

		m_socket.async_connect(m_endpoint,
			boost::bind(&Socket::handle_connect, this,
				boost::placeholders::_1));
	}

	void Socket::disconnect()
	{
		m_running = false;
		m_socket.close();
	}

	void Socket::handle_connect(const boost::system::error_code& ec)
	{
		if (!m_running)
			return;

		if (!m_socket.is_open())
		{
			start_connection();
		}
		else if (ec)
		{
			std::cout << "Connect error: " << ec.message() << "\n";

			// We need to close the socket used in the previous connection attempt
			// before starting a new one.
			disconnect();

			// Try the next available endpoint.
			start_connection();
		}
		else
		{
			OnServerConnect();

			// Start read
			start_read();
		}
	}

	void Socket::write(const std::string& data)
	{
		boost::asio::async_write(m_socket, boost::asio::buffer(data.data(), data.size()),
			boost::bind(&Socket::handle_write, this, boost::asio::placeholders::error));
	}

	void Socket::write(const std::string& data, std::size_t size)
	{
		boost::asio::async_write(m_socket, boost::asio::buffer(data.data(), size),
			boost::bind(&Socket::handle_write, this, boost::asio::placeholders::error));
	}
	void Socket::handle_write(const boost::system::error_code& ec) 
	{
		if (!ec) 
		{
			if (!m_socket.is_open()) 
			{
				disconnect();

				start_connection();
			}
		}
		else
		{
			LOGGER(debug) << "Could not write to server.";
		}
		
	}
	void Socket::start_read()
	{
		// Start an asynchronous operation to read a newline-delimited message.

		m_socket.async_read_some(boost::asio::buffer(m_bytes, BUFFER_SIZE),
			boost::bind(&Socket::handle_read, this,
				boost::placeholders::_1, boost::placeholders::_2));

	}
	void Socket::handle_read(const boost::system::error_code& ec, std::size_t n)
	{
		if (!m_running)
			return;

		if (!ec)
		{
			OnServerMessage(BytesHandler(m_bytes));
			start_read();
		}
		else
		{
			std::cout << "Error on receive: " << ec.message() << "\n";

			disconnect();
		}
	}

}
