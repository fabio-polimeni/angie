///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2012 Fabio Polimeni
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-01-27
/// Updated :
/// Licence : This source is under MIT License
/// File    : main.cpp
///////////////////////////////////////////////////////////////////////////////
/// Example main
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <exception>
#include <memory>

#include <angie/test.hpp>

#include "example.hpp"

int main( int argc, const char* argv[] )
{
	try
	{
		std::unique_ptr<Example> example( new Example );
		example->run(argc,argv);
	}
	catch( std::exception& e )
	{
		std::string e_msg("!!! EXCEPTION COUGHT !!!\n");
		e_msg.append(e.what());
		
		angie::output(e_msg);
		std::abort();
	}

	std::exit(EXIT_SUCCESS);
}
