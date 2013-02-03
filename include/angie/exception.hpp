#ifndef ANGIE_EXCEPTION_HPP
#define ANGIE_EXCEPTION_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-01-19													///
/// Updated : 																///
/// Licence : This source is under MIT License								///
/// File    : exception.hpp 												///
///////////////////////////////////////////////////////////////////////////////
/// Description:															///
///																			///
///	Derived exception classes declataration.								///
///////////////////////////////////////////////////////////////////////////////

#include <exception>

#include <angie/string.hpp>

namespace angie
{
	/// Generic exception
	class Exception : public std::exception
	{

	private:

		std::string m_Message;

	public:

		explicit Exception( const std::string message )
			: m_Message(message) { }

		virtual const char* what( void ) const throw()
		{
			return m_Message.c_str();
		}

	}; // Exception
} // angie

#endif //ANGIE_EXCEPTION_HPP
