#pragma once
#include "Header.hpp"
#include "BytesHandler.hpp"

namespace SP 
{
	class Socket
	{
	private:
		tcp::socket m_socket;
		tcp::endpoint m_endpoint;

		bytes m_bytes;

		bool m_running;

	private:
		void handle_connect(const boost::system::error_code& ec);
		void start_connection();
		void start_read();
		void handle_read(const boost::system::error_code& ec, std::size_t n);

		void handle_write(const boost::system::error_code& ec);
		void disconnect();
	protected:
		virtual void OnServerConnect() {}
		virtual void OnServerDisconnect() {}
		virtual void OnServerMessage(BytesHandler bytes) {}

		

		void write(const std::string& data);
		void write(const std::string& data, std::size_t size);

		//void write
	public:
		Socket(context& io, const char* ip, ushort port);
	};
}

