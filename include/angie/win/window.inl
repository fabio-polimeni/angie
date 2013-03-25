#ifndef ANGIE_GUI_WIN_WINDOW_INL
#define ANGIE_GUI_WIN_WINDOW_INL

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-03-10													///
/// Updated : 																///
/// License : This source is under MIT License								///
/// File    : window.inl 													///
///////////////////////////////////////////////////////////////////////////////
/// Description:															///
///																			///
///	Window Win32 wrapper class												///
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>

#include <angie/config.hpp>
#include <angie/report.hpp>
#include <angie/win/includes.hpp>
#include <angie/window.hpp>

namespace angie
{
	namespace win
	{
		class window_handler : public window_base
		{

		private:

			implement static
			LRESULT CALLBACK proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
			{
				window_handler* win = reinterpret_cast<window_handler*>(GetWindowLongPtr(hWnd,GWLP_USERDATA));
				switch (message)
				{
				case  WM_CREATE:
					{
						CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
						win = reinterpret_cast<window_handler*>(pCreate->lpCreateParams);
						
						if ( win )
						{
							SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)win);
							win->m_HWND = hWnd;
							win->onCreate();
						}

						break;
					}
					
				case  WM_DISPLAYCHANGE:
					if ( win == nullptr ) break;
					if ( win->m_States.has(state::eFULLSCREEN) )
					{
						win->m_States &= ~state::eFULLSCREEN;
					}
					else
					{
						win->m_States |= state::eFULLSCREEN;
							
						// We can't relay on the following code, because
						// if the fullscreen happened on a display device
						// different from the default one, than these information
						// is not what we want to communicate.
						//uint32_t width = (uint32_t)LOWORD(lParam);
						//uint32_t height = (uint32_t)HIWORD(lParam);

						DEVMODE devMode;
						ZeroMemory(&devMode,sizeof(DEVMODE));
						devMode.dmSize = sizeof(DEVMODE);

						// Get current display settings for the default display device.
						EnumDisplaySettings(win->m_fsDevice.DeviceName,ENUM_CURRENT_SETTINGS,&devMode);
						uint32_t width = (uint32_t)devMode.dmPelsWidth;
						uint32_t height = (uint32_t)devMode.dmPelsHeight;

						win->onFullscreen(width,height);
					}
					break;

				case WM_SHOWWINDOW:
				case WM_PAINT:
				case WM_SYNCPAINT:
					if ( win == nullptr ) break;
					if ( win->m_States.has(state::eTOPAINT) )
					{
						// If the user paint is active, then, the window's painting
						// must be requested, in order to generate a paint callback.
						if ( win->m_Flags.has(flag::ePAINTONREQUEST) )
						{
							win->onPaint();
							win->m_States &= ~state::eTOPAINT;
						}
					}
					else
					{
						// If the user paint is not active, we generate a
						// paint callback whenever we receive a paint message.
						win->onPaint();
					}
					break;

				case WM_SIZE:
					if ( win == nullptr ) break;
					if ( (wParam == SIZE_MAXIMIZED && win->m_States.has(state::eHIDDEN)) )
					{
						win->m_States &= ~(state::eHIDDEN);
						win->onRestore();
					}
					else if ( wParam == SIZE_MINIMIZED )
					{
						win->m_States |= state::eHIDDEN;
						win->onHide();
					}

					if ( win->m_States.has(state::eFULLSCREEN) == false )
					{
						win->onResize( (uint32_t)LOWORD(lParam), (uint32_t)HIWORD(lParam) );
					}

					break;

				case WM_MOVE:
					if ( win == nullptr ) break;
					{
						int32_t xPos = (int32_t)(short) LOWORD(lParam);   // horizontal position 
						int32_t yPos = (int32_t)(short) HIWORD(lParam);   // vertical position 

						int32_t winX = win->getX();
						int32_t winY = win->getY();
						if ( xPos != winX || yPos != winY )
						{
							win->onMove(winX,winY);
						}
					}
					break;

				case WM_CLOSE:
					DestroyWindow(hWnd);
					break;
  
				case WM_DESTROY:
					if ( win == nullptr ) break;
						
					win->onDestroy();
					SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)NULL);
						
					if ( win->m_Flags.has(flag::eEXITONCLOSE) )
					{	
						PostQuitMessage(0);
					}

					break;

				// Some default key handling
				case WM_KEYUP:
					if ( win == nullptr ) break;
					if ( wParam == VK_ESCAPE )
					{
						win->destroy();
					}
					else if ( wParam == 0x46 ) // F
					{
						if ( win->m_States.has(state::eFULLSCREEN) )
						{
							win->restore();
						}
						else if ( win->getParent() == nullptr )
						{
							win->fullscreen();
						}
					}
				}

				return DefWindowProc(hWnd, message, wParam, lParam);  
			}

			WNDCLASSEX		m_WCX;
			HWND			m_HWND;
			DISPLAY_DEVICE	m_fsDevice;

			state_type	m_States;
			flag_type	m_Flags;

			private:

				DWORD getExStyle( bool has_parent ) const
				{
					DWORD dwExStyle = 0x0;
					if ( !has_parent ) dwExStyle |= WS_EX_APPWINDOW;

					return dwExStyle;
				}

				DWORD getStyle( bool has_parent ) const
				{
					DWORD dwStyle = WS_CLIPCHILDREN;
					if ( has_parent )
					{
						if ( m_Flags.has(flag::ePARENTRELATIVE) )
						{
							dwStyle |= WS_CHILDWINDOW;
						}

						dwStyle |= (m_Flags.has(flag::ePOPUPWINDOW))
							? WS_BORDER|WS_SYSMENU : WS_OVERLAPPEDWINDOW;
					}
					else
					{
						dwStyle |= (m_Flags.has(flag::ePOPUPWINDOW))
							? WS_POPUP|WS_SYSMENU : WS_OVERLAPPEDWINDOW;
					}

					return dwStyle;
				}

		public:
				
			explicit window_handler( flag_type flags = flag::eEXITONCLOSE )
				: window_base(flags), m_HWND(NULL), m_Flags(flags)
			{
				ZeroMemory(&m_WCX,sizeof(WNDCLASSEX));
				m_WCX.cbSize = sizeof(WNDCLASSEX);
				m_WCX.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
				m_WCX.lpfnWndProc = (WNDPROC)window_handler::proc;
				m_WCX.cbClsExtra = 0;
				m_WCX.cbWndExtra = 0;  
				m_WCX.hInstance = GetModuleHandle(NULL);
				m_WCX.hIcon = LoadIcon(NULL, IDI_APPLICATION);
				m_WCX.hCursor = LoadCursor(NULL, IDC_ARROW);
				m_WCX.hbrBackground = NULL;
				m_WCX.lpszMenuName = NULL; 
				m_WCX.lpszClassName = "Angie - Window Class";
				m_WCX.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
				m_WCX.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

				// NOTE: Since a class is only registered once, the second caller will fail when
				//		 it tries to register the class again. Never check for the return value
				//		 of RegisterClass/Ex though.
				RegisterClassEx( &m_WCX );
			}

			virtual ~window_handler( void )
			{
				destroy();
			}

			void create( std::string title,
				uint32_t width, uint32_t height,
				window_base* parent = nullptr )
			{
				if ( parent )
				{
					// Only main windows can request an application to exit.
					m_Flags &= ~flag::eEXITONCLOSE;
				}

				DWORD dwExStyle = getExStyle( parent != nullptr );
				DWORD dwStyle = getStyle( parent != nullptr );
												
				HWND parent_hwnd = parent ? reinterpret_cast<window_handler*>(parent)->m_HWND : NULL;
				CreateWindowEx(
					dwExStyle,					// extended window styles
					m_WCX.lpszClassName,		// class name
					title.c_str(),				// window name
					dwStyle,					// window style
					CW_USEDEFAULT,				// default horizontal position
					CW_USEDEFAULT,				// default vertical position
					(int)width,					// default width
					(int)height,				// default height
					parent_hwnd,				// parent or owner window
					(HMENU) NULL,				// class menu used
					GetModuleHandle(NULL),		// instance handle
					this);						// user creation data

				if ( m_HWND )
				{
					// WM_SHOWWINDOW
					ShowWindow(m_HWND, SW_SHOWDEFAULT);

					// WM_PAINT
					UpdateWindow(m_HWND);
				}

				angie_error_msg(m_HWND != NULL,
					angie::string::format<128>("Can't create the window: %s", title.c_str()).c_str());
			}
				
			void destroy( void )
			{
				DestroyWindow(m_HWND);
			}

			void move( int32_t x, int32_t y )
			{
				win::window_handler* win_handler = reinterpret_cast<win::window_handler*>(this);
				if ( win_handler && win_handler->m_HWND )
				{
					SetWindowPos(win_handler->m_HWND,HWND_TOP,(int)x,(int)y,0,0,(SWP_NOSIZE|SWP_SHOWWINDOW));
				}
			}

			void resize( uint32_t width, uint32_t height )
			{
				win::window_handler* win_handler = reinterpret_cast<win::window_handler*>(this);
				if ( win_handler && win_handler->m_HWND )
				{
					SetWindowPos(win_handler->m_HWND,HWND_TOP,0,0,(int)width,(int)height,(SWP_NOMOVE|SWP_SHOWWINDOW));
				}
			}

			bool fullscreen( uint32_t width = 0, uint32_t height = 0, int16_t screen = -1 )
			{
				if ( this->m_HWND && (width != this->getWidth() || height != this->getHeight()) )
				{
					// Get the nearest monitor to the window
					MONITORINFOEX monitorInfo;
					monitorInfo.cbSize = sizeof(MONITORINFOEX);
					GetMonitorInfo(MonitorFromWindow(
						m_HWND, MONITOR_DEFAULTTONEAREST),&monitorInfo);

					// Now we can use the adapter to retrieve display devices associated o it.
					ZeroMemory(&m_fsDevice,sizeof(DISPLAY_DEVICE));
					m_fsDevice.cb = sizeof(DISPLAY_DEVICE);

					DWORD dispId = 0;
					bool dispFound = false;
					while ( EnumDisplayDevices(NULL,dispId++,&m_fsDevice,EDD_GET_DEVICE_INTERFACE_NAME) )
					{
						// We compare the display device with the screen-id, if provided,
						// with the monitor the window lies in, otherwise.
						if ( screen > -1 )
						{
							if ( screen == dispId-1 )
							{
								dispFound = true;
								break;
							}
						}
						else if ( strcmp(monitorInfo.szDevice,m_fsDevice.DeviceName) == 0 )
						{
							dispFound = true;
							break;
						}
					}

					if ( dispFound == false ) return false;

					DEVMODE devMode;
					ZeroMemory(&devMode,sizeof(DEVMODE));
					devMode.dmSize = sizeof(DEVMODE);

					// Get current display settings for the default display device.
					EnumDisplaySettings(m_fsDevice.DeviceName,ENUM_CURRENT_SETTINGS,&devMode);
					devMode.dmPelsWidth		= width > 0 ? width : getWidth();
					devMode.dmPelsHeight	= height > 0 ? height : getHeight();
					devMode.dmFields		= DM_PELSWIDTH | DM_PELSHEIGHT;

					LONG dispChangeResult = ChangeDisplaySettingsEx(
						m_fsDevice.DeviceName,	// Default display device
						&devMode,				// Current display mode with resolution changes
						NULL,					// Reserved
						CDS_TEST,				// We just want to check now
						NULL);					// No video parameters

					if ( dispChangeResult == DISP_CHANGE_SUCCESSFUL )
					{							
						dispChangeResult = ChangeDisplaySettingsEx(
							m_fsDevice.DeviceName,	// Default display device
							&devMode,				// Current display mode with resolution changes
							NULL,					// Reserved
							CDS_FULLSCREEN,			// Temporarily change display settings
							NULL);					// No video parameters

						SetWindowPos(m_HWND, HWND_TOPMOST,
							devMode.dmPosition.x, devMode.dmPosition.y,
							devMode.dmPelsWidth, devMode.dmPelsHeight,
							SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

						SetWindowLongPtr(m_HWND, GWL_EXSTYLE, WS_EX_TOPMOST);
						SetWindowLongPtr(m_HWND, GWL_STYLE, WS_POPUP | WS_VISIBLE);

						return true;
					}
				}

				return false;
			}

			void paint( bool paint_children = true )
			{
				win::window_handler* win_handler = reinterpret_cast<win::window_handler*>(this);
				if ( win_handler && win_handler->m_HWND
					&& win_handler->m_Flags.has(flag::ePAINTONREQUEST) )
				{
					UINT flags = RDW_UPDATENOW | RDW_INTERNALPAINT | RDW_VALIDATE;
					if ( paint_children )
					{
						flags |= RDW_ALLCHILDREN;
					}

					// WM_PAINT
					m_States |= state::eTOPAINT;
					RedrawWindow(win_handler->m_HWND, NULL, NULL, flags);
				}
			}

			void hide( void )
			{
				win::window_handler* win_handler = reinterpret_cast<win::window_handler*>(this);
				if ( win_handler && win_handler->m_HWND )
				{
					m_States |= state::eHIDDEN;
					ShowWindow(win_handler->m_HWND,SW_HIDE) ? true : false;
				}
			}

			void restore( void )
			{
				win::window_handler* win_handler = reinterpret_cast<win::window_handler*>(this);
				if ( win_handler && win_handler->m_HWND )
				{
					// Check if it was in fullscreen, and if so, then,
					// we need to restore display changes accordingly.
					if ( m_States.has(state::eFULLSCREEN) )
					{
						const uint32_t width = this->getWidth();
						const uint32_t height = this->getHeight();

						// Reset display mode
						//m_States &= ~state::eFULLSCREEN;
						ChangeDisplaySettingsEx(
							m_fsDevice.DeviceName,	// Default display device
							NULL,					// Previous display
							NULL,					// Reserved
							CDS_RESET,				// We just want to check now
							NULL);					// No video parameters
							
						SetWindowLongPtr(m_HWND, GWL_EXSTYLE, getExStyle(getParent() != nullptr));
						SetWindowLongPtr(m_HWND, GWL_STYLE, getStyle(getParent() != nullptr)|WS_VISIBLE);							
						SetWindowPos(m_HWND, HWND_NOTOPMOST, 0,0,width,height, SWP_SHOWWINDOW);
					}

					ShowWindow(win_handler->m_HWND,SW_RESTORE);
				}
			}

			uint32_t getClientWidth( void ) const
			{
				const win::window_handler* win_handler = reinterpret_cast<const win::window_handler*>(this);
				if ( win_handler && win_handler->m_HWND )
				{
					RECT clientRect;
					if ( GetClientRect(win_handler->m_HWND,&clientRect) )
					{
						return clientRect.right;
					}
				}

				return 0;
			}

			uint32_t getClientHeight( void ) const
			{
				const win::window_handler* win_handler = reinterpret_cast<const win::window_handler*>(this);
				if ( win_handler && win_handler->m_HWND )
				{
					RECT clientRect;
					if ( GetClientRect( win_handler->m_HWND,&clientRect) )
					{
						return clientRect.bottom;
					}
				}

				return 0;
			}

			uint32_t getWidth( void ) const
			{
				if ( this->m_HWND )
				{
					RECT winRect;
					if ( GetWindowRect( this->m_HWND,&winRect) )
					{
						return winRect.right-winRect.left;
					}
				}

				return 0;
			}

			uint32_t getHeight( void ) const
			{
				if ( this->m_HWND )
				{
					RECT winRect;
					if ( GetWindowRect( this->m_HWND,&winRect) )
					{
						return winRect.bottom-winRect.top;
					}
				}

				return 0;
			}

			int32_t	getX( void ) const
			{
				if ( this->m_HWND )
				{
					RECT winRect;
					if ( GetWindowRect( this->m_HWND,&winRect) )
					{
						return winRect.left;
					}
				}

				return 0xffffffff;
			}

			int32_t	getY( void ) const
			{
				if ( this->m_HWND )
				{
					RECT winRect;
					if ( GetWindowRect( this->m_HWND,&winRect) )
					{
						return winRect.top;
					}
				}

				return 0xffffffff;
			}

			std::string getTitle( void ) const
			{
				std::string title;
				if ( this->m_HWND )
				{
					TCHAR winText[128];
					GetWindowText(this->m_HWND,winText,128);
					title.append(winText);
				}

				return title;
			}

			window_base* getParent( void ) const
			{
				if ( this->m_HWND )
				{
					HWND parentHwnd = GetParent(this->m_HWND);
					if ( parentHwnd )
					{
						return reinterpret_cast<window_base*>(GetWindowLongPtr(parentHwnd,GWLP_USERDATA));
					}
				}

				return nullptr;
			}
		};
	} // win
} // angie

#endif // ANGIE_GUI_WIN_WINDOW_INL
