#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <angie/config.hpp>
#include <angie/report.hpp>
#include <angie/string.hpp>
#include <angie/gui/window.hpp>

class MainWindow : public angie::gui::Window
{

private:

	void onCreate( void )
	{
		angie_info("");
	}

	void onDestroy( void)
	{
		angie_info("");
	}

	void onPaint( void )
	{
		angie_info("");
	}

	void onHide( void )
	{
		angie_info("");
	}

	void onRestore( void )
	{
		angie_info("");
	}

	void onMove( int32_t x, int32_t y )
	{
		angie_info(angie::string::format<32>("Args - x:%d y:%d",x,y).c_str());
	}

	void onResize( uint32_t w, uint32_t h )
	{
		angie_info(angie::string::format<32>("Args - x:%d y:%d",w,h).c_str());
	}

	void onFullscreen( uint32_t w, uint32_t h )
	{
		angie_info(angie::string::format<32>("Args - x:%d y:%d",w,h).c_str());
	}

public:

	MainWindow( angie::gui::Window::flag_type ft )
		: angie::gui::Window(ft) { }
	~MainWindow( void ) { }

};

#endif
