#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

#include <angie/config.hpp>
#include <angie/report.hpp>
#include <angie/application.hpp>

#include "main_window.hpp"

class Example : public angie::Application
{

private:

	MainWindow* m_MainWindow;

	bool onInit( int32_t arg_c, const char* arg_v[] )
	{
		angie_info(angie::string::format<32>("Args - #:%d",arg_c).c_str());

		using namespace angie::gui;
		
		Window::flag_type win_flags(Window::Flag::eEXITONCLOSE);
		win_flags |= Window::Flag::ePAINTONREQUEST;
		m_MainWindow = new MainWindow(win_flags);

		m_MainWindow->create("Angie - Main Window",800,600);
		return true;
	}

	void onTick( void )
	{
		m_MainWindow->paint();
	}

	void onRelease( void )
	{
		angie_info("");
	}

public:

	Example( void ) { }
	~Example( void ) { }

};

#endif
