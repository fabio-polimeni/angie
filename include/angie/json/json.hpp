#ifndef ANGIE_JSON_HPP
#define ANGIE_JSON_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 Fabio Polimeni										
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-03-29													
/// Updated : 																
/// License : This source is under MIT License								
/// File    : json/json.hpp 														
///////////////////////////////////////////////////////////////////////////////
/// Description:															
///																			
///	JSON parser interface.
///////////////////////////////////////////////////////////////////////////////
#include <angie/config.hpp>
#include <angie/report.hpp>

#include <picojson.h>

namespace angie
{
	namespace json
	{
		using namespace picojson;
	}
}

#endif // ANGIE_JSON_HPP
