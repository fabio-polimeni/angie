#ifndef ANGIE_STRING_HPP
#define ANGIE_STRING_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2012 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2012-10-28													///
/// Updated : 																///
/// License : This source is under MIT License								///
/// File    : string.hpp 													///
///////////////////////////////////////////////////////////////////////////////
/// Description:															///
///																			///
///	 Utility functions for string manipulation.								///
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <cstdio>

#ifdef _MSC_VER
#include <cstdarg>
#endif

#include <angie/config.hpp>
#include <angie/types.hpp>

/// Namespace definition
namespace angie
{
	namespace string
	{
		template< size_t buff_size >
		inline std::string format( const char_t* format_string, ... )
		{
			char_t char_buff[buff_size] = {0};

			va_list vargs;
			va_start( vargs, format_string );
			
			int written_chars =
		#ifdef _MSC_VER
			vsnprintf_s( char_buff, buff_size, _TRUNCATE, format_string, vargs );
		#else
			vsnprintf( char_buff, buff_size, format_string, vargs );
		#endif
			va_end( vargs );

			return written_chars > 0 ? std::string( char_buff, written_chars ) : std::string();
		}
	}

	namespace wstring
	{
		template< size_t buff_size >
		inline std::wstring format( const wchar_t* format_string, ... )
		{
			wchar_t char_buff[buff_size] = {0};

			va_list vargs;
			va_start( vargs, format_string );
			
			int written_chars =
		#ifdef _MSC_VER
			vswnprintf_s( char_buff, buff_size, _TRUNCATE, format_string, vargs );
		#else
			vswnprintf( char_buff, buff_size, format_string, vargs );
		#endif
			va_end( vargs );

			return written_chars > 0 ? std::wstring( char_buff, written_chars ) : std::wstring();
		}
	}
}

#endif 
