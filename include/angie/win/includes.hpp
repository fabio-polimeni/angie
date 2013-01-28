#ifndef ANGIE_WIN_INCLUDES_HPP
#define ANGIE_WIN_INCLUDES_HPP

// All following macros reduce the window header at minimum.
// In order to active missing functionalities, comment the
// required preprocessor directive.

//#define NOGDICAPMASKS
//#define NOVIRTUALKEYCODES
//#define NOWINMESSAGES
//#define NOWINSTYLES
#define NOSYSMETRICS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
//#define NOCOLOR
//#define NODRAWTEXT
//#define NOGDI
#define NOKERNEL
//#define NOUSER
#define NONLS
#define NOMB
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
//#define NOMSG
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
//#define NOWINOFFSETS
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

#endif // ANGIE_WIN_INCLUDES_HPP
