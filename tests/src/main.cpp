///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2012 Fabio Polimeni
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-01-27
/// Updated :
/// Licence : This source is under MIT License
/// File    : main.cpp
///////////////////////////////////////////////////////////////////////////////
/// Test main.
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <exception>

#include <angie/test.hpp>

#include "test_simple.hpp"
#include "bitfield_tests.hpp"


int main( int argc, const char* argv[] )
{
	try
	{
		angie::test::BitfieldTests bitfield_tests;

		std::vector<const angie::test::unit> container_set;
		container_set.push_back(bitfield_tests);

		angie::test::result container_result = angie::test::suite("Container Tests",container_set);
		angie::output( container_result._message );
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
