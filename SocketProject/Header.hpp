#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <format>
#include <vector>
#include <thread>


/* BOOST */
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace boost::asio::ip;

#define BUFFER_SIZE 1024

namespace SP 
{
	using bytes = char[BUFFER_SIZE];
	using context = boost::asio::io_context;
	using ushort = unsigned short;

	template <typename... Args>
	static std::string format(std::string_view rt_fmt_str, Args&&... args) {
		return std::vformat(rt_fmt_str, std::make_format_args(args...));
	}
}

#ifdef _DEBUG
#include "Logger.hpp"
#endif
