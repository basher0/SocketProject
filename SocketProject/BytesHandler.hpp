#pragma once
#include "Header.hpp"

namespace SP
{
	class BytesHandler
	{
	private:
		SP::bytes m_bytes;
	public:
		BytesHandler(SP::bytes& bytes)
		{
			memset(m_bytes, 0, BUFFER_SIZE);

			std::size_t i = 0;
			for (auto& c : m_bytes)
			{
				c = bytes[i];
				bytes[i] = 0;

				i++;
			}
		}

		std::size_t size() const
		{
			std::size_t _s{ 0 };

			for (std::size_t i = 0; i < BUFFER_SIZE; i++) 
			{
				if (m_bytes[i] != '\0') 
					_s++;
			}

			return _s;
		}
		const char* data() const
		{
			return _strdup(m_bytes);
		}

		std::string to_string() const 
		{
			return std::string(m_bytes);
		}
	};
}

