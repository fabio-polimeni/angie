///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2012 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-01-27													///
/// Updated : 																///
/// Licence : This source is under MIT License								///
/// File    : main.cpp 														///
///////////////////////////////////////////////////////////////////////////////
/// Test main.																///
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <exception>

#include <angie/test.hpp>
#include "test_simple.hpp"


int main( int argc, const char* argv[] )
{
	try
	{
		angie::test::Simple simple_test;

		std::vector<const angie::test::Unit> basic_set;
		basic_set.push_back(simple_test);

		angie::test::Result basic_result = angie::test::suite("Basic Tests",basic_set);
		angie::output( basic_result._message );
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
