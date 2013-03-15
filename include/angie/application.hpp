#ifndef ANGIE_APPLICATION_HPP
#define ANGIE_APPLICATION_HPP

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 Fabio Polimeni										
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-02-09													
/// Updated : 																
/// Licence : This source is under MIT License								
/// File    : application.hpp 														
///////////////////////////////////////////////////////////////////////////////
/// Description:															
///																			
///	Application interface.
///////////////////////////////////////////////////////////////////////////////
#include <angie/config.hpp>
#include <angie/bitfield.hpp>
#include <angie/singleton.hpp>

namespace angie
{
	class ApplicationBase : public Singleton< ApplicationBase >
	{
		
	public:

		enum class State : uint8_t
		{
			eINVALID		= 0,
			eINITIALISED	= 1,
			eRUNNING		= 2,
			eEXITREQUESTED	= 3	
		};

		typedef Bitfield<State> state_type;

	private:
			
		ApplicationBase( const ApplicationBase& );				//= delete
		ApplicationBase& operator = ( const ApplicationBase& );	//= delete

	protected:

		state_type	m_States;

		ApplicationBase( void ) : Singleton(), m_States(State::eINVALID) { }

		virtual ~ApplicationBase( void ) { }

		virtual bool onInit( int32_t arg_c, const char* arg_v[] )	= 0;
		virtual void onTick( void )									= 0;
		virtual void onRelease( void )								= 0;

	public:
						
		virtual void run( int32_t arg_c, const char* arg_v[] ) { }
		void exit( void ) { m_States |= State::eEXITREQUESTED; }
	};
}

#if ANGIE_HEADER_ONLY
#	if ANGIE_PLATFORM & ANGIE_WIN
#		include <angie/win/application.inl>
#	endif
#endif

#endif // ANGIE_WINDOW_HPP
