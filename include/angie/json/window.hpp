#ifndef ANGIE_JSON_WINDOW_HPP
#define ANGIE_JSON_WINDOW_HPP

#include <angie/config.hpp>
#include <angie/report.hpp>
#include <angie/string.hpp>
#include <angie/window.hpp>
#include <angie/json/json.hpp>

namespace angie
{
	namespace json
	{
		class window : public angie::window
		{

		public:

			window( void ) : angie::window() { }
			virtual ~window( void ) { }

			virtual bool make( json::value json_obj )
			{
				if ( json_obj.is<json::object>() )
				{
					// TODO: Parse json object and create
					// the window with appropriate parameters.
					return angie::window::create("title",800,600);
				}

				return false;
			}

		};
	}
}

#endif // ANGIE_JSON_WINDOW_HPP
