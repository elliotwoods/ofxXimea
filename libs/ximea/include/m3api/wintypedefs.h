#ifndef __WINTYPEDEFS_H
#define __WINTYPEDEFS_H

#define _WINDEF_

#define WINAPI
#define IN
#define INOUT
#define OUT
#define __cdecl
#define _cdecl
#define dllimport
#define dllexport
#ifndef __INTEL_COMPILER
#define __declspec(x) __attribute__((x))
#define align aligned
#endif

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define MAX_PATH	PATH_MAX
#define _MAX_PATH	PATH_MAX

#define INVALID_HANDLE_VALUE ((void*)-1)
#define ERROR_SUCCESS 0
#ifndef FALSE
#define FALSE   0
#endif
#ifndef TRUE
#define TRUE    1
#endif

#define CONST	const
#define VOID	void

#ifdef __x86_64__
#define __int3264 long
#else
#define __int3264 int
#endif
typedef void*				HANDLE;
typedef HANDLE*				PHANDLE;
typedef HANDLE*				LPHANDLE;
typedef unsigned short		USHORT;
typedef uint32_t			DWORD;
typedef int					BOOL;
typedef unsigned char		BYTE;
typedef BYTE				byte;
typedef unsigned short		WORD;
typedef float				FLOAT;
typedef float*				PFLOAT;
typedef int*				PBOOL;
typedef float*				LPBOOL;
typedef BYTE*				PBYTE;
typedef BYTE*				LPBYTE;
typedef int*				PINT;
typedef int*				LPINT;
typedef WORD*				PWORD;
typedef WORD*				LPWORD;
typedef int32_t*			LPLONG;
typedef DWORD*				PDWORD;
typedef DWORD*				LPDWORD;
typedef void*				LPVOID;
typedef void*				PVOID;
typedef	size_t				SIZE_T;
typedef char				CHAR;
typedef wchar_t				WCHAR;
typedef char*				PCHAR;
typedef char*				PSTR;
typedef unsigned char		UCHAR;
typedef unsigned char*		PUCHAR;
typedef short				SHORT;
typedef int32_t				LONG;
typedef uint32_t			ULONG;
typedef uint64_t			ULONGLONG;
typedef uint64_t			ULONG64;
typedef int64_t				LONGLONG;
typedef BYTE				BOOLEAN;
typedef int					INT;
typedef unsigned int		UINT;
typedef uint16_t			UINT16;
typedef uint32_t			UINT32;
typedef int64_t				INT64;
typedef unsigned int*		PUINT;
typedef const char*			LPCSTR;
typedef char*				LPSTR;
typedef wchar_t*			LPWSTR;
typedef const wchar_t*		LPCWSTR;
typedef ULONGLONG			DWORDLONG;
typedef ULONGLONG*			PDWORDLONG;
typedef unsigned __int3264	UINT_PTR;
typedef __int3264			LONG_PTR;
typedef LPCSTR				LPCTSTR;
typedef LPSTR				LPTSTR;
typedef unsigned __int3264	ULONG_PTR;

typedef struct _GUID {
	DWORD Data1;
	WORD  Data2;
	WORD  Data3;
	BYTE  Data4[8];
} GUID;
typedef union _LARGE_INTEGER {
	struct {
		DWORD LowPart;
		LONG  HighPart;
	} ;
	struct {
		DWORD LowPart;
		LONG  HighPart;
	} u;
	LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
typedef union _ULARGE_INTEGER {
	struct {
		DWORD LowPart;
		DWORD HighPart;
	} ;
	struct {
		DWORD LowPart;
		DWORD HighPart;
	} u;
	ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;
typedef struct tagSIZE
{
	LONG        cx;
	LONG        cy;
} SIZE, *PSIZE, *LPSIZE;
typedef struct tagPOINT {
	LONG x;
	LONG y;
} POINT, *PPOINT;

#endif // __WINTYPEDEFS_H
