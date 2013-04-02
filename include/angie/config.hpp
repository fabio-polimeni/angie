#ifndef ANGIE_CONFIG_HPP
#define ANGIE_CONFIG_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2012 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2012-10-27													///
/// Updated : 																///
/// License : This source is under MIT License								///
/// File    : config.hpp 													///
///////////////////////////////////////////////////////////////////////////////
/// Description:															///
///																			///
///	This file is use to configure the library and its dependencies.			///
///	 Each preprocessor macro is explained on top of its declaration.		///
///////////////////////////////////////////////////////////////////////////////

/// If this directive is 1, the library won't be compiled,
/// and everything will be included from the headers.
#define ANGIE_HEADER_ONLY	1

/// Traits warning as errors
#define ANGIE_WARNASERROR	1

/// If this directive is 0, then the user can skip the 
/// log function definition. She has to provide it otherwise.
/// See log.hpp/.inl for implementation.
#define ANGIE_USER_LOG 0

/// If this directive is 0, then the user can skip the 
/// report function definition. She has to provide it otherwise.
/// See report.hpp/.inl for implementation.
#define ANGIE_USER_REPORT 0

/// Configuration settings
#define ANGIE_DEBUG		0x01
#define ANGIE_CHECK		0x02
#define ANGIE_RELEASE	0x04

#if defined( _DEBUG ) || defined( DEBUG )
#	define ANGIE_CONFIG (ANGIE_DEBUG | ANGIE_CHECK)
#elif defined( _CHECK )
#	define ANGIE_CONFIG (ANGIE_RELEASE | ANGIE_CHECK)
#else
#	define ANGIE_CONFIG ANGIE_RELEASE
#endif

/// In order to avoid multiple dependencies, we define this
/// preprocessor directive, which makes everything inline
/// for header only library.
#if ANGIE_HEADER_ONLY
#	define implement inline
#else
#	define implement
#endif

#ifndef thread_local
#	ifdef _MSC_VER
#		define thread_local __declspec( thread )
#	else
#		define thread_local __thread
#	endif
#endif

#ifndef noexcept
#	ifdef _MSC_VER
#		define noexcept _NOEXCEPT
#	endif
#endif

/// Platform identifications
#define ANGIE_WIN		0x01
#define ANGIE_WIN32		0x02
#define ANGIE_WIN64		0x04

/// Very simple platform identification
#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#	if defined(_WIN64)
#		define ANGIE_PLATFORM ANGIE_WIN | ANGIE_WIN64
#	else
#		define ANGIE_PLATFORM ANGIE_WIN | ANGIE_WIN32
#	endif
#endif

/// Namespace definition
namespace angie
{

}

#endif // ANGIE_CONFIG_HPP
