#ifndef ANGIE_JSON_APPLICATION_HPP
#define ANGIE_JSON_APPLICATION_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 Fabio Polimeni										
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-03-29													
/// Updated : 																
/// License : This source is under MIT License								
/// File    : json/application.hpp 														
///////////////////////////////////////////////////////////////////////////////
/// Description:															
///																			
///	JSON application interface.
///////////////////////////////////////////////////////////////////////////////
#include <sstream>
#include <fstream>

#include <angie/application.hpp>
#include <angie/json/json.hpp>
#include <angie/json/window.hpp>

namespace angie
{
	namespace json
	{
		class application : public angie::application
		{

		private:

			std::vector<angie::json::window> m_windows;

			application( const application& );				//= delete
			application& operator = ( const application& );	//= delete

			std::string load( std::string filename )
			{
				std::ifstream config_file;

				std::ios_base::openmode open_mode = std::ios_base::in;
				open_mode |= std::ios_base::binary;

				config_file.open(filename.c_str(), open_mode);
				if ( config_file.good() )
				{
					std::stringbuf config_strbuf;
					config_file.get(config_strbuf,config_file.eof());
					config_file.close();
					
					return config_strbuf.str();
				}

				return std::string();
			}

		public:

			application( void ) : angie::application() { }
			virtual ~application( void ) { }

			virtual void run( int32_t arg_c, const char* arg_v[] )
			{
				for ( int32_t arg_it = 0; arg_it < arg_c; ++arg_it )
				{
					std::string arg(arg_v[arg_it]);
					if ( arg_it+1 < arg_c && arg == "-config" )
					{
						json::value json_config;
						std::string json_string = load(arg_v[++arg_it]);
						std::string err = json::parse(json_config,json_string.begin(),json_string.end());
						angie_error_msg( err.empty(), err.c_str() );

						if ( err.empty() )
						{
							// TODO: Iterate throw all windows object
							// call json::window::make(json_win_obj)
							// for each of them.

							angie::application::run(arg_c,arg_v);
							return;
						}
					}
				}
			}

			virtual bool onInit( int32_t arg_c, const char* arg_v[] ) { return true; }
			virtual void onTick( void )	{ }
			virtual void onRelease( void ) { }
		};
	}
}

#endif // ANGIE_JSON_APPLICATION_HPP
