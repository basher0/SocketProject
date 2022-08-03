#pragma once
#include <boost/log/trivial.hpp>

/*
  * levels *

    debug
    info
    error
    fatal
    warning
    trace

*/

#define LOGGER(level)\
    BOOST_LOG_STREAM_WITH_PARAMS(::boost::log::trivial::logger::get(),\
        (::boost::log::keywords::severity = ::boost::log::trivial::level))
