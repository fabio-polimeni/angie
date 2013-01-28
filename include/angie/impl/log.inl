#ifndef ANGIE_LOG_INL
#define ANGIE_LOG_INL

#include <iostream>
#include <functional>
#include <string>

#include <angie/log.hpp>

// TODO:
//	0.	Make it thread safe!
//	1.	We can catch any \n in the message and add a \t, or
//		any kind of identifier, to each line before printing.
//	2.	On platforms, such as Windows, we can catach if
//		a debugger is attached, and print the message to
//		it, instead of printing to the standard output.

namespace angie
{
	namespace log
	{
		std::function< void (std::string message) > handler = [](std::string message)
		{
			std::cout << message << std::endl;
		};
	}
}

#endif // ANGIE_LOG_INL
