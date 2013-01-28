#ifndef ANGIE_WIN_DEBUGGER_HPP
#define ANGIE_WIN_DEBUGGER_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2012 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-01-29													///
/// Updated : 																///
/// Licence : This source is under MIT License								///
/// File    : debugger.inl 													///
///////////////////////////////////////////////////////////////////////////////
/// Description:															///
///																			///
///	Window platform debugger specialization.								///
///////////////////////////////////////////////////////////////////////////////

#include <angie/config.hpp>
#include <angie/win/includes.hpp>

#include <string>
#include <iostream>

namespace angie
{
	namespace debugger
	{
		implement bool present( void ) { return IsDebuggerPresent() ? true : false; }
		
		implement void write( const std::string msg )
		{
			if ( debugger::present() )
			{
				OutputDebugString( msg.c_str() );
			}
			else
			{
				std::cerr << msg << std::endl;
			}
		}

		implement void breakpoint( void )
		{
			if ( debugger::present() )
			{
				DebugBreak();
			}
		}
	}
}

#endif // ANGIE_WIN_DEBUGGER_HPP
