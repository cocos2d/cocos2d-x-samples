//******************************************************************
//
// Copyright 2007-2014 Intel Corporation All Rights Reserved.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//
//******************************************************************
// File name:
//     compatibility.h
//
// Description:
//     Header for Intel Common_Library cross-platform compatibility.
//
//
//
//*********************************************************************


#ifndef __COMPATIBILITYH__
#define __COMPATIBILITYH__

// Remove this flag to return to using the non-CS output debug logging.
#define USE_STC_DEBUG_LOGGING 1

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>
#include <wctype.h>
#include <limits.h>

// Workaround for a re-def issue between stdint.h and intsafe.h in VS-2010
#if defined(WIN32) || defined(_WIN32)
#undef INT8_MIN
#undef INT16_MIN
#undef INT32_MIN
#undef INT8_MAX
#undef INT16_MAX
#undef INT32_MAX
#undef UINT8_MAX
#undef UINT16_MAX
#undef UINT32_MAX
#undef INT64_MIN
#undef INT64_MAX
#undef UINT64_MAX
#include <intsafe.h>
#undef INT8_MIN
#undef INT16_MIN
#undef INT32_MIN
#undef INT8_MAX
#undef INT16_MAX
#undef INT32_MAX
#undef UINT8_MAX
#undef UINT16_MAX
#undef UINT32_MAX
#undef INT64_MIN
#undef INT64_MAX
#undef UINT64_MAX
#endif

#include <stdint.h>

#ifdef _WINRT
#include "debug.h"
#endif

#if defined(_WINRT) || defined(__APPLE__)
#define _RT(str)  str
#define RTCHAR  char
#else
#define _RT(str)  _T(str)
#define RTCHAR  TCHAR
#endif

#if defined(WIN32) || defined(_WIN32) || defined(WINCE) || defined(_WIN32_WCE)
#include <tchar.h>
#include <oaidl.h>
#include <xstring>
#include <boost/shared_ptr.hpp>
#else
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <new>
#include <memory>
#if !defined(__ANDROID__)
#include <algorithm>
#include <sys/msg.h>
#endif
//  #include <tr1/memory>
#include "wintypes.h"

#define GCC_VERSION (__GNUC__*10000+__GNUC_MINOR__*100+__GNUC_PATCHLEVEL__)
#endif

#define __COMMONLIBDECL__
#define __COMMONLIBEXTERN__

// Make certain that both _DEBUG and DEBUG are defined if either is defined
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif
#if defined(DEBUG) && !defined(_DEBUG)
#define _DEBUG
#endif

#if (defined(DEBUG) || defined(_DEBUG)) && defined(NDEBUG)
#undef NDEBUG
#endif

#if defined(WIN32) || defined(_WIN32) || defined(WINCE) || defined(_WIN32_WCE)

#ifndef min
#define min(x, y) (((x)<(y))? (x): (y))
#endif
#ifndef max
#define max(x, y) (((x)>(y))? (x): (y))
#endif

/* The MS compiler has issues exporting templates with nested types
   from a DLL, so this option is not expected to be used.*/
#ifdef COMMONLIB_RELEASE_DLL
#undef __COMMONLIBDECL__
#undef __COMMONLIBEXTERN__
#ifdef __IMPORTDLL__
#define __COMMONLIBDECL__ __declspec(dllimport)
#define __COMMONLIBEXTERN__ extern
#else
#ifdef __EXPORTDLL__
#define __COMMONLIBDECL__ __declspec(dllexport)
#define __COMMONLIBEXTERN__
#else
#define __COMMONLIBDECL__
#define __COMMONLIBEXTERN__
#endif
#endif
#endif

#ifdef __cplusplus
class InterlockLockDebugMsg
{
    public:
        InterlockLockDebugMsg();
        ~InterlockLockDebugMsg();
};
#define DEBUGMSG_TRANSACT() InterlockLockDebugMsg()
#else
#define DEBUGMSG_TRANSACT()
#endif

#if !defined(WINCE) && !defined(_WIN32_WCE)
#if (defined(WIN32) || defined(_WIN32)) && !defined(_WINRT)
#if defined(USE_STC_DEBUG_LOGGING) && defined(__cplusplus)
#include "DebugLogging.h"

#define RETAILMSG(cond, printf_exp) ((cond)? (::Intel::DebugLogging::DbgPrintF printf_exp): 0)
#ifdef DEBUG
#define DEBUGMSG(cond, printf_exp) ((cond)? (::Intel::DebugLogging::DbgPrintF printf_exp): 0)
#else
#define DEBUGMSG(cond, printf_exp) (0)
#endif
#else
/* Create a mapping for RETAILMSG and DEBUGMSG in the non-CE Windows C++ environment */
#ifdef __cplusplus
extern "C" {
#endif
size_t EXTOutputDebugStringFT(const TCHAR *format, ...);
#ifdef __cplusplus
}
#endif

#define RETAILMSG(cond, printf_exp) ((cond)? (EXTOutputDebugStringFT printf_exp): 0)
#ifdef DEBUG
#define DEBUGMSG(cond, printf_exp) ((cond)? (EXTOutputDebugStringFT printf_exp): 0)
#else
#define DEBUGMSG(cond, printf_exp) (0)
#endif
#endif
#elif defined(__ANDROID__) || defined(__APPLE__) || defined(_WINRT)
#define RETAILMSG(cond, printf_exp) DebugPrint(cond, printf_exp)
#ifdef DEBUG
#define DEBUGMSG(cond, printf_exp) DebugPrint(cond, printf_exp)
#else
#define DEBUGMSG(cond, printf_exp) (0)
#endif
#endif
#endif
#else /* defined(WIN32) || defined(_WIN32) || defined(WINCE) || defined(_WIN32_WCE) */

#define __COMMONLIBDECL__

#if !defined(__CYGWIN__) && !defined(__stdcall)
#define __stdcall
#endif

typedef void *LPVOID;
typedef unsigned int DWORD;
typedef unsigned int BOOL;
typedef unsigned char BYTE;
typedef signed long LONG;
typedef wchar_t TCHAR;
typedef wchar_t OLECHAR;
typedef OLECHAR *BSTR;
typedef const OLECHAR *CONST_BSTR;
typedef void *HANDLE;
typedef void *HMODULE;
typedef void (*FARPROC)(void);
typedef unsigned long long ULONGLONG;

#if defined(UNICODE) || defined(_UNICODE)
#define _T(str) L##str
#define _stprintf(buf, fmt, args...) swprintf((buf), INT_MAX, (fmt), args)
#define _tcscmp(str1, str2) wcscmp((str1), (str2))
#define _tcsstr(str1, str2) wcsstr((str1), (str2))
#define _tcsncpy_s(str1, n1, str2, n2) wcsncpy((str1), (str2), (n2))
#define _stscanf(str, fmt, args...) swscanf((str), (fmt), args)
#define _tcslen(str) wcslen((str))
#define _tprintf(fmt, args...) wprintf((fmt), args)
#else
#ifndef _T
#define _T(str) str
#endif
#define _stprintf(buf, fmt, args...) sprintf((buf), (fmt), args)
#define _tcscmp(str1, str2) strcmp((str1), (str2))
#define _tcsstr(str1, str2) strstr((str1), (str2))
#define _tcsncpy_s(str1, n1, str2, n2) strncpy((str1), (str2), (n2))
#define _stscanf(str, fmt, args...) sscanf((str), (fmt), args)
#define _tcslen(str) strlen((str))
#define _tprintf(fmt, args...) printf((fmt), args)
#endif

#define RETAILMSG(zone, macro) ((zone)? _tprintf macro: 0)

#ifdef DEBUG
#define DEBUGMSG(zone, macro) ((zone)? _tprintf macro: 0)
#else
#define DEBUGMSG(zone, macro) ((void)0)
#endif

#define DEBUGMSG_TRANSACT()

#define INFINITE 0xFFFFffff
#define WAIT_OBJECT_0 0

#define SUCCEEDED(result) ((result)>=0)
#define FAILED(result) ((result)<0)
#define S_FALSE 1
#define S_OK 0

#if !defined(ERROR_SUCCESS)
#define ERROR_SUCCESS 0
#endif

// This may or may not function properly on multi-core systems.
/// \todo Improve this behavior or use library functions
#define InterlockedIncrement(value) ((*(value))++)
#define InterlockedDecrement(value) ((*(value))--)

using std::max;
using std::min;

#endif /* defined(WIN32) || defined(_WIN32) || defined(WINCE) || defined(_WIN32_WCE) */

/// Helper function to swap an array of bytes (used for GUID processing). In general this is
/// used as a replacement for ntohs and ntohl, which are not guaranteed to be available.
/// \todo Move this into a utility class as a static function
void swap_byte_array(void *vec, const size_t bytes);

#ifndef stc_new
#if defined(WIN32) || defined(_WIN32) || defined(WINCE) || defined(_WIN32_WCE)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#ifdef DEBUG
#define stc_new new (_CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define stc_new new (std::nothrow)
#endif
#endif

#endif /*__COMPATIBILITYH__*/
