#ifndef ANGIE_REPORT_INL
#define ANGIE_REPORT_INL

#include <iostream>

#include <angie/report.hpp>
#include <angie/exception.hpp>
#include <angie/log.hpp>

namespace angie
{
	namespace report
	{
#if (ANGIE_CONFIG & ANGIE_CHECK)
		
		implement
		bool handle(
			const report::type r_type, bool expr,
			const std::char8_t* expr_string,
			const std::char8_t* func_name, 
			const std::char8_t* file_name,
			const int32_t line_num,
			const std::char8_t* message )
		{
			std::string text_line;
			switch ( r_type )
			{
			case report::type::eCRTIICAL:
				if ( expr == false )
				{
					text_line = string::format<512>(
						"ERROR:\t%s\n\tFunction - %s\n\tEvaluating - %s\n\tFile - %s : %d\n",
						message, func_name, expr_string, file_name, line_num);
					throw angie::Exception(text_line);
				}
				return false;

			case report::type::eWARNING:
				if ( expr == false )
				{
					text_line = string::format<512>(
						"WARNING:\t%s\n\tFunction - %s\n\tEvaluating - %s\n\tFile - %s : %d\n",
						message, func_name, expr_string, file_name, line_num );
				#if ( ANGIE_WARNASERROR )
					throw angie::Exception(text_line);
				#else
					angie::output(text_line);
				#endif
				}
				return false;

			case report::type::eINFO:
				text_line = string::format<512>(
					"INFO:\t%s\n\tFunction - %s\n\tFile - %s : %d\n",
					message, func_name, file_name, line_num );
				angie::output(text_line);
				return true;
			
			default: return false;
			}
		}

#else // ANGIE_CHECK

		implement
		bool handle(
			const report::type, bool,
			const std::char8_t*,
			const std::char8_t*,
			const std::char8_t*,
			const int32_t,
			const std::char8_t* )
		{ return true; }

#endif // ANGIE_CHECK
	} // namespace report
} // namespace angie

#endif // ANGIE_REPORT_INL
