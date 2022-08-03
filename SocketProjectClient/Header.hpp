#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <format>
#include <vector>
#include <thread>
#include <memory>


/* BOOST */
#include <boost/asio.hpp>
#include <boost/asio/error.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace boost::asio::ip;


namespace SP
{
	#define BUFFER_SIZE 1024

	using bytes = char[BUFFER_SIZE];
	using ushort = unsigned short;
	using context = boost::asio::io_context;

	template <typename... Args>
	static std::string format(std::string_view rt_fmt_str, Args&&... args) {
		return std::vformat(rt_fmt_str, std::make_format_args(args...));
	}
}

#ifdef _DEBUG
#include "Logger.hpp"
#endif
