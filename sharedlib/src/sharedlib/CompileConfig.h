#define DLL_EXPORT

#ifdef WIN32
#   ifdef _DEBUG
#       define _CRTDBG_MAP_ALLOC
#       define _CRTDBG_MAP_ALLOC_NEW
#       include <stdlib.h>
#       include <crtdbg.h>
#   endif /* Debug */
#endif /* win32*/

#ifdef _WINDOWS
#   pragma warning( disable: 4251 4204 4275 )
#	ifdef DLL_EXPORT
#		define LIBEXPORT __declspec(dllexport)
#	else
#		define LIBEXPORT __declspec(dllimport)
#	endif
#else
#	define LIBEXPORT
#endif