#ifndef ANGIE_WIN_APPLICATION_INL
#define ANGIE_WIN_APPLICATION_INL

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-03-10													///
/// Updated : 																///
/// Licence : This source is under MIT License								///
/// File    : application.inl												///
///////////////////////////////////////////////////////////////////////////////
/// Description:															///
///																			///
///	Application Win32 wrapper class											///
///////////////////////////////////////////////////////////////////////////////
#include <angie/config.hpp>
#include <angie/report.hpp>
#include <angie/application.hpp>
#include <angie/win/includes.hpp>

namespace angie
{
	ApplicationBase* ApplicationBase::m_Instance = nullptr;
	namespace win
	{
		class ApplicationHandler : public ApplicationBase
		{
		
		private:

			HINSTANCE m_Hinstance;

		public:

			void run( int32_t arg_c, const char* arg_v[] )
			{
				ApplicationHandler* app = reinterpret_cast<ApplicationHandler*>(ApplicationBase::get());
				if ( app == nullptr ) return;
		
				// Get the the application handler
				app->m_Hinstance = GetModuleHandle(arg_v[0]);
				app->m_States |= State::eINITIALISED;
				if ( app->onInit( arg_c, arg_v ) )
				{
					app->m_States |= State::eRUNNING;
					while ( !app->m_States.has(State::eEXITREQUESTED) )
					{
						MSG msg;

						// If we have a message to process
						if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
						{
							if (msg.message == WM_QUIT)
							{
								app->exit();
							}
							else
							{
								TranslateMessage(&msg);
								DispatchMessage(&msg);
							}
						}
						
						// We give the opportunity to check
						// from the on-tick function, if this
						// is going to be the last frame before
						// exit te main loop. Just check
						// Application::isExitRequested().
						app->onTick();
					}

					app->m_States &= ~State::eRUNNING;
					app->onRelease();
				}
			}

		};
	} // win
} // angie

#endif // ANGIE_GUI_WIN_WINDOW_INL
