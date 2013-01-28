#ifndef ANGIE_DEBUGGER_HPP
#define ANGIE_DEBUGGER_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2012 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-01-29													///
/// Updated : 																///
/// Licence : This source is under MIT License								///
/// File    : debugger.hpp 													///
///////////////////////////////////////////////////////////////////////////////
/// Description:															///
///																			///
///	Debugger handlers														///
///////////////////////////////////////////////////////////////////////////////

#include <angie/config.hpp>
#include <angie/types.hpp>

#if ANGIE_PLATFORM & ANGIE_WIN
#	include <angie/win/debugger.inl>
#else

#include <iostream>

namespace angie
{
	namespace debugger
	{
		implement bool present( void ) { return false; }
		
		implement void write( const std::string msg )
		{
			std::cerr << msg << std::endl;
		}

		implement void breakpoint( void ) { }
	}
}
#endif  // ANGIE_PLATFORM


#endif // ANGIE_DEBUGGER_HPP
