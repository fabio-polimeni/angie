#ifndef ANGIE_BITFIELDTESTS_HPP
#define ANGIE_BITFIELDTESTS_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2012 Fabio Polimeni										
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-01-27													
/// Updated : 																
/// Licence : This source is under MIT License								
/// File    : bitfield_tests.hpp											
///////////////////////////////////////////////////////////////////////////////
/// Tests for the bitfield class									
///////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <angie/test.hpp>
#include <angie/bitfield.hpp>

namespace angie
{
	namespace test
	{
		class BitfieldTests : public unit
		{
			enum class InOut : char
			{
				eNONE	= 0,
				eIN		= 1,
				eOUT	= 2,
				eIN_And_OUT	= eIN | eOUT
			};

		public:

			BitfieldTests( void ) : unit( "Bitfield Tests", [](std::vector<const result>& results)
			{
				angie::bitfield<InOut> in_bf(InOut::eIN);
				
				angie_test_check(results,in_bf.Bitset().any(),
					"There should be at least one bit set");
				
				angie_test_check(results,in_bf.Bitset().count() == 1,
					"There should be only one bit set (1)");
				
				angie_test_check(results,in_bf == InOut::eIN,
					"The bitfiled expected to be equal to InOut::In");

				angie_test_check(results,in_bf.has(InOut::eIN),
					"The bitfiled should have the InOut::In bit set to 1");

				angie::bitfield<InOut> out_bf(InOut::eOUT);
				
				out_bf |= InOut::eNONE;
				angie_test_check(results,out_bf.has(InOut::eNONE),
					"The bitfiled should have the InOut::eNONE bit set to 1");

				out_bf &= ~angie::bitfield<InOut>(InOut::eNONE);
				angie_test_check(results,!out_bf.has(InOut::eNONE),
					"The bitfiled shouldn't have the InOut::eNONE bit set to 1");

				angie::bitfield<InOut> in_to_out(InOut::eIN);
				in_to_out <<= 1;

				angie_test_check(results,in_to_out == InOut::eIN,
					"The bitfiled expected to be equal to InOut::In");

				angie::bitfield<InOut> in_and_out(InOut::eIN | InOut::eOUT);
				angie_test_check(results,in_and_out.has(InOut::eIN) && in_and_out.has(InOut::eOUT),
					"The bitfiled should have set both InOut::In && InOut::Out");

				auto none_bf(in_and_out & (InOut::eOUT));
				angie_test_check(results,none_bf.any(),
					"The bitfiled should have set both InOut::In && InOut::Out");

			}) { }
		};
	}
}

#endif // ANGIE_BITFIELDTESTS_HPP
