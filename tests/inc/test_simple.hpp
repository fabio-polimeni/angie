///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2012 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-01-27													///
/// Updated : 																///
/// Licence : This source is under MIT License								///
/// File    : test_simple.hpp												///
///////////////////////////////////////////////////////////////////////////////
/// Tests for basic functionalities.										///
///////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <angie/test.hpp>

namespace angie
{
	namespace test
	{
		class Simple : public unit
		{

		public:

			Simple( void ) : unit( "Simple Test", [](std::vector<const result>& results)
			{
				angie_test_check(results,1 != 0,"This is a simple success story.");
				
				//angie_test_check(results,1 == 0,"This is a poor story.");
			}) { }
		};
	}
}
