#ifndef ANGIE_SINGLETON_HPP
#define ANGIE_SINGLETON_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 Fabio Polimeni										
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-02-09													
/// Updated : 																
/// Licence : This source is under MIT License								
/// File    : singleton.hpp 														
///////////////////////////////////////////////////////////////////////////////
/// Description:															
///																			
///	Singleton pattern implementation
///////////////////////////////////////////////////////////////////////////////
#include <bitset>
#include <type_traits>

#include <angie/config.hpp>
#include <angie/report.hpp>

namespace angie
{
	template < typename TYPE >
	class singleton
	{
		
	private:

		// Prevent copying/assignment.
		singleton( const singleton & );
		singleton &operator = ( const singleton & );

	protected:

		static TYPE* m_Instance;

		singleton( void )
		{
			angie_error_msg( !TYPE::m_Instance, "An instance of this singleton class already exists!" );
			m_Instance = static_cast< TYPE* >( this );
		}

		virtual ~singleton( void ) { m_Instance = nullptr; }

	public:
		
		static TYPE* get( void ) { return TYPE::m_Instance; }

		static TYPE* swap( TYPE* new_inst )
		{
			TYPE* ret_inst = TYPE::m_Instance;
			TYPE::m_Instance = new_inst;
			return ret_inst;
		}

	};

	template < typename TYPE >
	class Singleunit
	{
		
	public:
		
		// NOTE: A different reference will be generated for each compilation unit.
		//		 Use this singleton implementation carefully with shared libaries.
		static TYPE& Get( void )
		{
			static TYPE s_Reference;
			return s_Reference;
		}

	};

}

#endif // ANGIE_SINGLETON_HPP
