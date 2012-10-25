#define DLL_EXPORT

#ifdef _WINDOWS
#   pragma warning( disable: 4251 4099 4204 4275 )
#	ifdef DLL_EXPORT
#		define LIBEXPORT __declspec(dllexport)
#	else
#		define LIBEXPORT __declspec(dllimport)
#	endif
#else
#	define LIBEXPORT
#endif