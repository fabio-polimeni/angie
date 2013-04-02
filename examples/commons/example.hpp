#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

#include <angie/config.hpp>
#include <angie/report.hpp>
#include <angie/json/application.hpp>

#include "main_window.hpp"

class Example : public angie::json::application
{

private:

	std::string m_Name;

	MyWindow* m_MainWindow;
	MyWindow* m_ChildWindow;

	bool onInit( int32_t arg_c, const char* arg_v[] )
	{
		if ( angie::json::application::onInit(arg_c,arg_v) )
		{
			m_Name = std::string(arg_v[0]);
			angie::window::flag_type win_flags;

			win_flags.reset();
			win_flags |= angie::window::flag::eEXITONCLOSE;
			win_flags |= angie::window::flag::ePAINTONREQUEST;
			//win_flags |= angie::window::flag::ePOPUPWINDOW;
			m_MainWindow = new MyWindow();
			m_MainWindow->create("Angie - Main Window",1024,768,win_flags);

			win_flags.reset();
			win_flags |= angie::window::flag::ePARENTRELATIVE;
			//win_flags |= angie::window::flag::ePOPUPWINDOW;
			m_ChildWindow = new MyWindow();
			m_ChildWindow->create("Angie - Child Window",800,600,win_flags,m_MainWindow);

			m_MainWindow->move(10,10);
			angie::output(angie::string::format<64>("Client Area - w:%d, y:%d",
				m_MainWindow->getClientWidth(),m_MainWindow->getClientHeight()));

			return true;
		}

		return false;
	}

	void onTick( void )
	{
		angie::json::application::onTick();
		m_MainWindow->paint();
	}

	void onRelease( void )
	{
		angie::json::application::onRelease();
		angie_info(m_Name.c_str());
	}

};

#endif
