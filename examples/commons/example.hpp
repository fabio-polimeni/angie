#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

#include <angie/config.hpp>
#include <angie/report.hpp>
#include <angie/application.hpp>

#include "main_window.hpp"

class Example : public angie::application
{

private:

	MyWindow* m_MainWindow;
	MyWindow* m_ChildWindow;

	bool onInit( int32_t arg_c, const char* arg_v[] )
	{
		angie_info(angie::string::format<64>("%s",arg_v[0]).c_str());
				
		angie::window::flag_type win_flags;

		win_flags.reset();
		win_flags |= angie::window::flag::eEXITONCLOSE;
		win_flags |= angie::window::flag::ePAINTONREQUEST;
		//win_flags |= angie::window::flag::ePOPUPWINDOW;
		m_MainWindow = new MyWindow(win_flags);
		m_MainWindow->create("Angie - Main Window",1024,768);

		win_flags.reset();
		win_flags |= angie::window::flag::ePARENTRELATIVE;
		//win_flags |= angie::window::flag::ePOPUPWINDOW;
		m_ChildWindow = new MyWindow(win_flags);
		m_ChildWindow->create("Angie - Child Window",800,600,m_MainWindow);

		m_MainWindow->move(10,10);
		angie::output(angie::string::format<64>("Client Area - w:%d, y:%d",
			m_MainWindow->getClientWidth(),m_MainWindow->getClientHeight()));

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

};

#endif
