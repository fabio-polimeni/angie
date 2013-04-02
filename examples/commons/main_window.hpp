#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <angie/config.hpp>
#include <angie/report.hpp>
#include <angie/string.hpp>
#include <angie/window.hpp>

class MyWindow : public angie::window
{

private:

	void onCreate( void )
	{
		angie_info(this->getTitle().c_str());
	}

	void onDestroy( void)
	{
		angie_info(this->getTitle().c_str());
	}

	void onPaint( void )
	{
	}

	void onHide( void )
	{
		angie_info(this->getTitle().c_str());
	}

	void onRestore( void )
	{
		angie_info(this->getTitle().c_str());
	}

	void onMove( int32_t x, int32_t y )
	{
		angie_info(angie::string::format<64>("%s - x:%d y:%d",
			this->getTitle().c_str(),x,y).c_str());
	}

	void onResize( uint32_t w, uint32_t h )
	{
		angie_info(angie::string::format<64>("%s - x:%d y:%d",
			this->getTitle().c_str(),w,h).c_str());
	}

	void onFullscreen( uint32_t w, uint32_t h )
	{
		angie_info(angie::string::format<64>("%s - x:%d y:%d",
			this->getTitle().c_str(),w,h).c_str());
	}

public:

	MyWindow( void ) : angie::window() { }
	virtual ~MyWindow( void ) { }

};

#endif
