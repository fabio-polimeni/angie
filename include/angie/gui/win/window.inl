#ifndef ANGIE_GUI_WIN_WINDOW_INL
#define ANGIE_GUI_WIN_WINDOW_INL

///////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 Fabio Polimeni										///
///////////////////////////////////////////////////////////////////////////////
/// Created : 2013-03-10													///
/// Updated : 																///
/// Licence : This source is under MIT License								///
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
#include <angie/gui/window.hpp>

namespace angie
{
	namespace gui
	{
		namespace win
		{
			class WindowHandler : public WindowBase
			{

			private:

				implement static
				LRESULT CALLBACK proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
				{
					WindowHandler* win = reinterpret_cast<WindowHandler*>(GetWindowLongPtr(hWnd,GWLP_USERDATA));
					switch (message)
					{
					case  WM_CREATE:
						{
							CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
							win = reinterpret_cast<WindowHandler*>(pCreate->lpCreateParams);
						
							if ( win )
							{
								win->onCreate();
								SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)win);
							}

							break;
						}
					
					case  WM_DISPLAYCHANGE:
						if ( win == nullptr ) break;
						if ( win->m_States.has(State::eFULLSCREEN ) )
						{
							win->onFullscreen((uint32_t)LOWORD(lParam), (uint32_t)HIWORD(lParam));
						}
						else
						{
							win->onResize((uint32_t)LOWORD(lParam), (uint32_t)HIWORD(lParam));
						}
						break;

					case WM_SHOWWINDOW:
					case WM_PAINT:
					case WM_SYNCPAINT:
						if ( win == nullptr ) break;
						if ( win->m_States.has(State::eTOPAINT) )
						{
							// If the user paint is active, then, the window's painting
							// must be requested, in order to generate a paint callback.
							if ( win->m_Flags.has(Flag::ePAINTONREQUEST) )
							{
								win->onPaint();
								win->m_States &= ~State::eTOPAINT;
							}
						}
						else
						{
							// If the user paint is not active, we generate a
							// paint callback whenever we recieve a paint message.
							win->onPaint();
						}
						break;

					case WM_SIZE:
						if ( win == nullptr ) break;
						if ( (wParam == SIZE_MAXIMIZED) || (wParam == SIZE_RESTORED) )
						{
							win->m_States &= ~State::eHIDDEN;
							win->onRestore();
						}
						else if ( wParam == SIZE_MINIMIZED )
						{
							win->m_States |= State::eHIDDEN;
							win->onHide();
						}

						win->onResize( (uint32_t)LOWORD(lParam), (uint32_t)HIWORD(lParam) );
						break;

					case WM_WINDOWPOSCHANGED:
						if ( win == nullptr ) break;
						{
							WINDOWPOS* win_pos = reinterpret_cast<WINDOWPOS*>(lParam);
							win->onMove(win_pos->x,win_pos->y);
						}
						break;

					case WM_CLOSE:
						DestroyWindow(hWnd);
						break;
  
					case WM_DESTROY:
						if ( win == nullptr ) break;
						
						win->onDestroy();
						SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)NULL);
						
						if ( win->m_Flags.has(Flag::eEXITONCLOSE) )
						{	
							PostQuitMessage(0);
						}

						break;
					}

					return DefWindowProc(hWnd, message, wParam, lParam);  
				}

				WNDCLASSEX	m_WCX;
				HWND		m_HWND;

				state_type	m_States;
				flag_type	m_Flags;

			public:
				
				explicit WindowHandler( flag_type flags = Flag::eEXITONCLOSE )
					: WindowBase(flags), m_HWND(NULL), m_Flags(flags)
				{
					ZeroMemory(&m_WCX,sizeof(WNDCLASSEX));
					m_WCX.cbSize = sizeof(WNDCLASSEX);
					m_WCX.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
					m_WCX.lpfnWndProc = (WNDPROC)WindowHandler::proc;
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

				virtual ~WindowHandler( void )
				{
					destroy();
				}

				void create( std::string title,
					uint32_t width, uint32_t height,
					WindowBase* parent = nullptr )
				{
					if ( parent )
					{
						// Only main windows can request an application to exit.
						m_Flags &= ~Flag::eEXITONCLOSE;
					}

					DWORD dwStyle = (flag_type(m_Flags & Flag::ePOPUPWINDOW).any() && parent == nullptr)
						? WS_POPUPWINDOW : WS_OVERLAPPEDWINDOW;
						
					if ( parent ) dwStyle |= WS_CHILDWINDOW;

					DWORD dwExStyle = ( parent == nullptr ) ? WS_EX_APPWINDOW : 0x0;
												
					HWND parent_hwnd = parent ? reinterpret_cast<WindowHandler*>(parent)->m_HWND : NULL;
					m_HWND = CreateWindowEx(
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
					win::WindowHandler* win_handler = reinterpret_cast<win::WindowHandler*>(this);
					if ( win_handler && win_handler->m_HWND )
					{
						SetWindowPos(win_handler->m_HWND,HWND_TOP,(int)x,(int)y,0,0,(SWP_NOSIZE|SWP_SHOWWINDOW));
					}
				}

				void resize( uint32_t width, uint32_t height )
				{
					win::WindowHandler* win_handler = reinterpret_cast<win::WindowHandler*>(this);
					if ( win_handler && win_handler->m_HWND )
					{
						SetWindowPos(win_handler->m_HWND,HWND_TOP,0,0,(int)width,(int)height,(SWP_NOMOVE|SWP_SHOWWINDOW));
					}
				}

				bool fullscreen( uint32_t width, uint32_t height )
				{
					m_States |= State::eFULLSCREEN;
					return false;
				}

				void paint( bool paint_children = true )
				{
					win::WindowHandler* win_handler = reinterpret_cast<win::WindowHandler*>(this);
					if ( win_handler && win_handler->m_HWND
						&& win_handler->m_Flags.has(Flag::ePAINTONREQUEST) )
					{
						UINT flags = RDW_UPDATENOW | RDW_INTERNALPAINT | RDW_VALIDATE;
						if ( paint_children )
						{
							flags |= RDW_ALLCHILDREN;
						}

						// WM_PAINT
						m_States |= State::eTOPAINT;
						RedrawWindow(win_handler->m_HWND, NULL, NULL, flags);
					}
				}

				bool hide( void )
				{
					win::WindowHandler* win_handler = reinterpret_cast<win::WindowHandler*>(this);
					if ( win_handler && win_handler->m_HWND )
					{
						m_States |= State::eHIDDEN;
						return ShowWindow(win_handler->m_HWND,SW_HIDE) ? true : false;
					}

					return false;
				}

				void restore( void )
				{
					win::WindowHandler* win_handler = reinterpret_cast<win::WindowHandler*>(this);
					if ( win_handler && win_handler->m_HWND )
					{
						m_States &= ~(State::eHIDDEN|State::eFULLSCREEN);

						// TODO: Check if it was in fullscreen, and if so, then,
						//		 we need to restore display changes accordingly.
						ShowWindow(win_handler->m_HWND,SW_RESTORE);
					}
				}

				uint32_t getWidth( void ) const
				{
					const win::WindowHandler* win_handler = reinterpret_cast<const win::WindowHandler*>(this);
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

				uint32_t getHeight( void ) const
				{
					const win::WindowHandler* win_handler = reinterpret_cast<const win::WindowHandler*>(this);
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
			};
		} // win

		// Expose Window interface
		typedef win::WindowHandler Window;

	} // gui
} // angie

#endif // ANGIE_GUI_WIN_WINDOW_INL
