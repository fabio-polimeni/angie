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
		class BitfieldTests : public Unit
		{
			enum class InOut : char
			{
				eNONE	= 0,
				eIN		= 1,
				eOUT	= 2,
				eIN_And_OUT	= eIN | eOUT
			};

		public:

			BitfieldTests( void ) : Unit( "Bitfield Tests", [](std::vector<const Result>& results)
			{
				angie::Bitfield<InOut> in_bf(InOut::eIN);
				
				angie_test_check(results,in_bf.Bitset().any(),
					"There should be at least one bit set");
				
				angie_test_check(results,in_bf.Bitset().count() == 1,
					"There should be only one bit set (1)");
				
				angie_test_check(results,in_bf == InOut::eIN,
					"The bitfiled expected to be equal to InOut::In");

				angie_test_check(results,in_bf.Has(InOut::eIN),
					"The bitfiled should have the InOut::In bit set to 1");

				angie::Bitfield<InOut> out_bf(InOut::eOUT);
				
				out_bf |= InOut::eNONE;
				angie_test_check(results,out_bf.Has(InOut::eNONE),
					"The bitfiled should have the InOut::eNONE bit set to 1");

				out_bf &= ~angie::Bitfield<InOut>(InOut::eNONE);
				angie_test_check(results,!out_bf.Has(InOut::eNONE),
					"The bitfiled shouldn't have the InOut::eNONE bit set to 1");

				angie::Bitfield<InOut> in_to_out(InOut::eIN);
				in_to_out <<= 1;

				angie_test_check(results,in_to_out == InOut::eIN,
					"The bitfiled expected to be equal to InOut::In");

				angie::Bitfield<InOut> in_and_out(InOut::eIN | InOut::eOUT);
				angie_test_check(results,in_and_out.Has(InOut::eIN) && in_and_out.Has(InOut::eOUT),
					"The bitfiled should have set both InOut::In && InOut::Out");

			}) { }
		};
	}
}
