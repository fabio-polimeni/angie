#ifndef ANGIE_TEST_HPP
#define ANGIE_TEST_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-01-19													///
/// Updated : 																///
/// Licence : This source is under MIT License								///
/// File    : test.hpp 														///
///////////////////////////////////////////////////////////////////////////////
/// Description:															///
///																			///
///	Unit test classes and functions declarations.							///
///////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <exception>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>
#include <future>

#include <angie/config.hpp>
#include <angie/string.hpp>
#include <angie/report.hpp>
#include <angie/log.hpp>

namespace angie
{
	namespace test
	{
		struct Result
		{
			enum class type
			{
				eFAILURE = 0x0,
				eSUCCESS = 0x1
			};

			type		_type;
			std::string	_message;

			Result( void )
				: _type(type::eSUCCESS)
				, _message("") { }

			Result( type t, std::string message )
				: _type(t), _message(message) { }
			
			Result( Result&& other )
				: _type(other._type)
				, _message(std::move(other._message)) { }

			Result& operator= ( Result&& other )
			{
				if ( this != &other )
				{
					_type = other._type;
					_message = std::move(other._message);
				}

				return *this;
			}
		};

		// NOTE! - Don't call this function directly, use angie_test_check macro instead. -
		implement
		Result check( bool expr, std::string msg, std::string filename = "",
			std::int32_t fileline = -1, std::string expr_str = "" )
		{
			Result result;

			if ( expr == false )
			{
				result._type = Result::type::eFAILURE;

				result._message.append("\tFailure! ");
				
				if ( !expr_str.empty() )
				{
					result._message.append("(" + expr_str + ") is false - ");
				}

				result._message.append(msg);

				if ( !filename.empty() )
				{
					result._message.append("\n\tIn - " + filename );
					if ( fileline >= 0 )
					{
						result._message.append(" : " + std::to_string(fileline) );
					}
				}
				
				result._message.append("\n");
			}
			else
			{
				result._type = Result::type::eSUCCESS;
				result._message = msg;
			}

			return result;
		}

		/// Unit test definition. Each of these is identified by a name
		/// and a function, the actual test. You can has as many tests
		/// as you want, per test-suite.
		struct Unit
		{
			std::function< void ( std::vector<const Result>& ) > _exec;

			Unit( std::string name, decltype(_exec) exec_func )
				: _exec(exec_func) { }
		};

		/// Test suite class definition. The contructor receives a vector
		/// of unit tests, and per each of them execute the test-function.
		/// E.g.
		///	std::vector<angie::test::Unit> test_set;
		/// test_set.push_back( angie::test::Unit("My 1st Test", [](){ angie::check(true,"!!!success!!!"); }) );
		///	angie::test::Suite test_suite("My Test Suite", test_set);

		Result suite( std::string name, const std::vector<const Unit>& unit_set )
		{				
			std::promise<std::vector<const Result>> promises;
			auto ftr = promises.get_future();
				
			std::thread suite_thread([&unit_set]( decltype(promises)& proms )
			{
				try
				{
					std::vector<const Result> test_results;
					std::for_each(unit_set.begin(),unit_set.end(),[&test_results](const Unit& unit_test)
					{
						unit_test._exec(test_results);
					});

					proms.set_value(std::move(test_results));
				}
				catch( ... )
				{
					proms.set_exception(std::current_exception());
				}
			}, std::ref(promises));

			suite_thread.join();

			size_t n_successes = 0;
			auto test_results = ftr.get();
			std::for_each( test_results.begin(), test_results.end(),
				[&n_successes](const Result& result)
				{
					if ( result._type == Result::type::eSUCCESS ) ++n_successes;
				});
			
			angie_error(n_successes <= test_results.size());

			Result suite_result;
			suite_result._message = name;

			if ( n_successes == test_results.size() )
			{
				suite_result._type = Result::type::eSUCCESS;
				suite_result._message += angie::string::format<64>(
					": (%d successes of %d) -> Ok!\n",
					n_successes, test_results.size());
			}
			else
			{
				suite_result._type = Result::type::eFAILURE;
				suite_result._message += angie::string::format<64>(
					": (%d fails of %d) -> Ko!\n",
					test_results.size()-n_successes, test_results.size());
			}

			std::for_each( test_results.begin(), test_results.end(),
				[&suite_result](const Result& result)
				{
					if ( result._type == Result::type::eFAILURE )
					{
						suite_result._message.append(result._message);
					}
				});

			return suite_result;
		}

	} // test
} // angie

#define angie_test_check(tr,expr,msg) \
	tr.push_back(angie::test::check((expr),(msg),__FILE__,__LINE__,(#expr)))

#endif // ANGIE_TEST_HPP
