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
	class application_base : public singleton< application_base >
	{
		
	public:

		enum class state : uint8_t
		{
			eINVALID		= 0,
			eINITIALISED	= 1,
			eRUNNING		= 2,
			eEXITREQUESTED	= 3	
		};

		typedef bitfield<state> state_type;

	private:
			
		application_base( const application_base& );				//= delete
		application_base& operator = ( const application_base& );	//= delete

	protected:

		state_type	m_States;

		application_base( void ) : singleton(), m_States(state::eINVALID) { }

		virtual ~application_base( void ) { }

		virtual bool onInit( int32_t arg_c, const char* arg_v[] )	= 0;
		virtual void onTick( void )									= 0;
		virtual void onRelease( void )								= 0;

	public:
						
		virtual void run( int32_t arg_c, const char* arg_v[] ) { }
		void exit( void ) { m_States |= state::eEXITREQUESTED; }

		bool isExitRequested( void ) const { return m_States.has(state::eEXITREQUESTED); }
	};
}

#if ANGIE_HEADER_ONLY
#	if ANGIE_PLATFORM & ANGIE_WIN
#		include <angie/win/application.inl>
#	endif
#endif

// Expose Application interface
namespace angie {
#if ANGIE_PLATFORM & ANGIE_WIN
	typedef win::application_handler application;
#endif
}

#endif // ANGIE_WINDOW_HPP
