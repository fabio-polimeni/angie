#ifndef ANGIE_LOG_INL
#define ANGIE_LOG_INL

#include <iostream>
#include <functional>
#include <string>
#include <thread>

#include <angie/log.hpp>
#include <angie/debugger.hpp>

namespace angie
{
	namespace log
	{
		std::function< void (std::string message) > handler = [](std::string message)
		{
			static std::mutex s_log_mutex;
			std::lock_guard<std::mutex> log_lock(s_log_mutex);

			if ( debugger::present() )
			{
				debugger::write( message );
			}
			else
			{
				std::cout << message << std::endl;
			}
		};
	}
}

#endif // ANGIE_LOG_INL
