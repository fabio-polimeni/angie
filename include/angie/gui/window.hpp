#ifndef ANGIE_WINDOW_HPP
#define ANGIE_WINDOW_HPP

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
///	GUI window interface.
///////////////////////////////////////////////////////////////////////////////
#include <angie/config.hpp>
#include <angie/bitfield.hpp>

namespace angie
{
	namespace gui
	{
		class WindowBase
		{
		
		public:

			enum class State : uint8_t
			{
				eINVALID		= 0,	// Invalid
				eFULLSCREEN		= 1,	// Whether or not the window is in fullscreen
				eHIDDEN			= 2,	// Whether or not the window is reduced at icon
				eTOPAINT		= 3		// Whether or not the window has got a pending paint request
			};

			enum class Flag : uint8_t
			{
				eEXITONCLOSE	= 0,	// If set, exit the application when close this window
				ePAINTONREQUEST	= 1,	// If set, paint() function must be called by the user explicitely
				ePOPUPWINDOW	= 2,	// No menu or border frames
				ePARENTRELATIVE	= 3		// Child client rectangle will be relative to its parent
			};

			typedef Bitfield<State> state_type;
			typedef Bitfield<Flag>	flag_type;

		private:
			
			WindowBase( const WindowBase& );				//= delete
			WindowBase& operator = ( const WindowBase& );	//= delete

		protected:

			WindowBase( void ) { }
			explicit WindowBase( flag_type flags ) { }

			virtual ~WindowBase( void ) { }

			virtual void onCreate( void )						= 0;
			virtual void onDestroy( void)						= 0;
			virtual void onPaint( void )						= 0;
			virtual void onHide( void )							= 0;
			virtual void onRestore( void )						= 0;
			virtual void onMove( int32_t x, int32_t y )			= 0;
			virtual void onResize( uint32_t w, uint32_t h )		= 0;
			virtual void onFullscreen( uint32_t w, uint32_t h )	= 0;	

		public:

			virtual void create( std::string title,
				uint32_t width, uint32_t height,
				WindowBase* parent = nullptr )							= 0;

			virtual void destroy( void )								= 0;

			virtual void move( int32_t x, int32_t y )					= 0;
			virtual void resize( uint32_t width, uint32_t height )		= 0;
			virtual bool fullscreen(
				uint32_t width, uint32_t height, int16_t screen = -1 )	= 0;

			virtual void paint( bool paint_children )					= 0;
			virtual void hide( void )									= 0;
			virtual void restore( void )								= 0;
			
			virtual uint32_t getClientWidth( void ) const				= 0;
			virtual uint32_t getClientHeight( void ) const				= 0;

			virtual uint32_t getWidth( void ) const						= 0;
			virtual uint32_t getHeight( void ) const					= 0;

			virtual int32_t	getX( void ) const							= 0;
			virtual int32_t	getY( void ) const							= 0;

			virtual std::string getTitle( void ) const					= 0;

			virtual WindowBase* getParent( void ) const					= 0;
			
		};
	}
}

#if ANGIE_HEADER_ONLY
#	if ANGIE_PLATFORM & ANGIE_WIN
#		include <angie/gui/win/window.inl>
#	endif
#endif

// Expose Window interface
namespace angie { namespace gui {
#if ANGIE_PLATFORM & ANGIE_WIN
	typedef win::WindowHandler Window;
#endif
} }

#endif // ANGIE_WINDOW_HPP
