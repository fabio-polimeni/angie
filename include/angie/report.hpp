#ifndef ANGIE_REPORT_HPP
#define ANGIE_REPORT_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2012 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2012-10-28													///
/// Updated : 2013-01-19													///
/// Licence : This source is under MIT License								///
/// File    : report.hpp 													///
///////////////////////////////////////////////////////////////////////////////
/// Description:															///
///																			///
///	Report declataration. It is in chardge of tell the user what			///
///	 what is happening under some cirumstances defined by the programmer.	///
///////////////////////////////////////////////////////////////////////////////

#include <angie/config.hpp>
#include <angie/types.hpp>

namespace angie
{
	namespace report
	{
		enum class type
		{
			eCRTIICAL	= 0,
			eWARNING,
			eINFO
		};
	}
}

#if ANGIE_USER_REPORT
namespace angie
{
	namespace report
	{
		bool handle(
			const report::type r_type, bool expr,
			const std::char8_t* expr_string,
			const std::char8_t* func_name,
			const std::char8_t* file_name,
			const std::int32_t line_num,
			const std::char8_t* message );
	}
}
#else
#	include <angie/impl/report.inl>
#endif  // ANGIE_HADER_ONLY

/// Namespace definition
namespace angie
{
    bool critical( bool expression, const std::char8_t* message )
    {
        return report::handle( report::type::eCRTIICAL, expression, "", "", "", -1,message );
    }

    bool warning( bool expression, const std::char8_t* message )
    {
        return report::handle( report::type::eWARNING, expression, "", "", "", -1, message);
    }

    bool info( const std::char8_t* message )
    {
        return report::handle( report::type::eINFO, true, "", "", "", -1, message);
    }
} // angie

#if ANGIE_HEADER_ONLY
#	include <angie/impl/report.inl>
#endif  // ANGIE_HADER_ONLY

#define angie_error_msg( expr, msg ) \
	angie::report::handle( angie::report::type::eCRTIICAL, (expr), (#expr), __FUNCTION__, __FILE__, __LINE__, (msg) )

#define angie_error( expr ) angie_error_msg(expr,"")

#define angie_warning_msg( expr, msg ) \
	angie::report::handle( angie::report::type::eWARNING, (expr), (#expr), __FUNCTION__, __FILE__, __LINE__, (msg) )

#define angie_warning( expr ) angie_warning_msg(expr,"")

#define angie_info( msg ) \
	angie::report::handle( angie::report::type::eINFO, true, __FUNCTION__, __FILE__, __LINE__, -1, (msg) )

#endif // ANGIE_REPORT_HPP
