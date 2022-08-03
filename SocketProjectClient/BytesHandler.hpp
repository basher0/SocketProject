#pragma once
#include "Header.hpp"
namespace SP
{
	class BytesHandler
	{
	private:
		bytes m_bytes;
	public:
		BytesHandler(bytes& bytes)
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

		const char* data() const 
		{
			return _strdup(m_bytes);
		}

		std::size_t size(bool raw = true) const
		{
			if (raw)
				return BUFFER_SIZE;

			std::size_t s = 0;
			while (m_bytes[s] != 0)
				s++;

			return s;
		}
		std::string to_string() const
		{
			return std::string(m_bytes);
		}
	};
}

