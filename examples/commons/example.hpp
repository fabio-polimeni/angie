#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

#include <angie/config.hpp>
#include <angie/report.hpp>
#include <angie/application.hpp>

#include "main_window.hpp"

class Example : public angie::Application
{

private:

	MyWindow* m_MainWindow;
	MyWindow* m_ChildWindow;

	bool onInit( int32_t arg_c, const char* arg_v[] )
	{
		angie_info(angie::string::format<64>("%s",arg_v[0]).c_str());

		using namespace angie::gui;
		
		Window::flag_type win_flags;

		win_flags.reset();
		win_flags |= Window::Flag::eEXITONCLOSE;
		win_flags |= Window::Flag::ePAINTONREQUEST;
		//win_flags |= Window::Flag::ePOPUPWINDOW;
		m_MainWindow = new MyWindow(win_flags);
		m_MainWindow->create("Angie - Main Window",1024,768);

		win_flags.reset();
		win_flags |= Window::Flag::ePARENTRELATIVE;
		//win_flags |= Window::Flag::ePOPUPWINDOW;
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
