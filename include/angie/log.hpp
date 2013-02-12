#ifndef ANGIE_LOG_HPP
#define ANGIE_LOG_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2012 Fabio Polimeni										
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-01-22													
/// Updated : 																
/// Licence : This source is under MIT License								
/// File    : log.hpp 														
///////////////////////////////////////////////////////////////////////////////
/// Description:															
///																			
///	Log output handler. By default it prints the message to the standard	
///	output, but we use an handler, that is, the user can catch any message	
///	and act according.														
///////////////////////////////////////////////////////////////////////////////

#include <angie/config.hpp>
#include <angie/types.hpp>

#if ANGIE_USER_LOG
namespace angie
{
	namespace log
	{
		std::function< void (std::string message) > handler;
	}
}
#else
#	include <angie/log.inl>
#endif  // ANGIE_HADER_ONLY

namespace angie
{
	implement
	void output(std::string message) { log::handler(message); }
}


#endif // ANGIE_LOG_HPP
