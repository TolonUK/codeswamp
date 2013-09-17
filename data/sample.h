/************************************************************************
*                                                                       *
*   winerror.h --  error code definitions for the Win32 API functions   *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/

#ifndef _WINERROR_
#define _WINERROR_

#if defined (_MSC_VER) && (_MSC_VER >= 1020) && !defined(__midl)
#pragma once
#endif

#ifndef FORCEINLINE
#if (_MSC_VER >= 1200)
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE __inline
#endif
#endif

#include <specstrings.h>

//
// Note: There is a slightly modified layout for HRESULT values below,
//        after the heading "COM Error Codes".
//
// Search for "**** Available SYSTEM error codes ****" to find where to
// insert new error codes
//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-------------------------------+
//  |S|R|C|N|r|    Facility         |               Code            |
//  +-+-+-+-+-+---------------------+-------------------------------+
//
//  where
//
//      S - Severity - indicates success/fail
//
//          0 - Success
//          1 - Fail (COERROR)
//
//      R - reserved portion of the facility code, corresponds to NT's
//              second severity bit.
//
//      C - reserved portion of the facility code, corresponds to NT's
//              C field.
//
//      N - reserved portion of the facility code. Used to indicate a
//              mapped NT status value.
//
//      r - reserved portion of the facility code. Reserved for internal
//              use. Used to indicate HRESULT values that are not status
//              values, but are instead message ids for display strings.
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_XPS                     82
#define FACILITY_XAML                    43
#define FACILITY_USN                     129

//
// Define the severity codes
//


//
// MessageId: ERROR_SUCCESS
//
// MessageText:
//
// The operation completed successfully.
//
#define ERROR_SUCCESS                    0L

#define NO_ERROR 0L                                                 // dderror
#define SEC_E_OK                         ((HRESULT)0x00000000L)

//
// MessageId: ERROR_INVALID_FUNCTION
//
// MessageText:
//
// Incorrect function.
//
#define ERROR_INVALID_FUNCTION           1L    // dderror

//
// MessageId: ERROR_FILE_NOT_FOUND
//
// MessageText:
//
// The system cannot find the file specified.
//
#define ERROR_FILE_NOT_FOUND             2L

//
// MessageId: ERROR_DS_BAD_INSTANCE_TYPE
//
// MessageText:
//
// The specified instance type is not valid.
//
#define ERROR_DS_BAD_INSTANCE_TYPE       8313L

//
// MessageId: ERROR_DS_MASTERDSA_REQUIRED
//
// MessageText:
//
// The operation must be performed at a master DSA.
//
#define ERROR_DS_MASTERDSA_REQUIRED      8314L


////////////////////////////////////
//                                //
//     COM Error Codes            //
//                                //
////////////////////////////////////


//
// The return value of COM functions and methods is an HRESULT.
// This is not a handle to anything, but is merely a 32-bit value
// with several fields encoded in the value. The parts of an
// HRESULT are shown below.
//
// Many of the macros and functions below were orginally defined to
// operate on SCODEs. SCODEs are no longer used. The macros are
// still present for compatibility and easy porting of Win16 code.
// Newly written code should use the HRESULT macros and functions.
//

//
//  HRESULTs are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-------------------------------+
//  |S|R|C|N|r|    Facility         |               Code            |
//  +-+-+-+-+-+---------------------+-------------------------------+
//
//  where
//
//      S - Severity - indicates success/fail
//
//          0 - Success
//          1 - Fail (COERROR)
//
//      R - reserved portion of the facility code, corresponds to NT's
//              second severity bit.
//
//      C - reserved portion of the facility code, corresponds to NT's
//              C field.
//
//      N - reserved portion of the facility code. Used to indicate a
//              mapped NT status value.
//
//      r - reserved portion of the facility code. Reserved for internal
//              use. Used to indicate HRESULT values that are not status
//              values, but are instead message ids for display strings.
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

//
// Severity values
//

#define SEVERITY_SUCCESS    0
#define SEVERITY_ERROR      1


//
// Generic test for success on any status value (non-negative numbers
// indicate success).
//

#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)

//
// and the inverse
//

#define FAILED(hr) (((HRESULT)(hr)) < 0)


//
// Generic test for error on any status value.
//

#define IS_ERROR(Status) (((unsigned long)(Status)) >> 31 == SEVERITY_ERROR)

//
// Return the code
//

#define HRESULT_CODE(hr)    ((hr) & 0xFFFF)
#define SCODE_CODE(sc)      ((sc) & 0xFFFF)

//
//  Return the facility
//

#define HRESULT_FACILITY(hr)  (((hr) >> 16) & 0x1fff)
#define SCODE_FACILITY(sc)    (((sc) >> 16) & 0x1fff)

//
//  Return the severity
//

#define HRESULT_SEVERITY(hr)  (((hr) >> 31) & 0x1)
#define SCODE_SEVERITY(sc)    (((sc) >> 31) & 0x1)

//
// Create an HRESULT value from component pieces
//

#define MAKE_HRESULT(sev,fac,code) \
    ((HRESULT) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )
#define MAKE_SCODE(sev,fac,code) \
    ((SCODE) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )


//
// Map a WIN32 error value into a HRESULT
// Note: This assumes that WIN32 errors fall in the range -32k to 32k.
//
// Define bits here so macros are guaranteed to work

#define FACILITY_NT_BIT                 0x10000000

//
// HRESULT_FROM_WIN32(x) used to be a macro, however we now run it as an inline function
// to prevent double evaluation of 'x'. If you still need the macro, you can use __HRESULT_FROM_WIN32(x)
//
#define __HRESULT_FROM_WIN32(x) ((HRESULT)(x) <= 0 ? ((HRESULT)(x)) : ((HRESULT) (((x) & 0x0000FFFF) | (FACILITY_WIN32 << 16) | 0x80000000)))

#if !defined(_HRESULT_DEFINED) && !defined(__midl)
#define _HRESULT_DEFINED
typedef _Return_type_success_(return >= 0) long HRESULT;
#endif

#ifndef __midl
FORCEINLINE HRESULT HRESULT_FROM_WIN32(unsigned long x) { return (HRESULT)(x) <= 0 ? (HRESULT)(x) : (HRESULT) (((x) & 0x0000FFFF) | (FACILITY_WIN32 << 16) | 0x80000000);}
#else
#define HRESULT_FROM_WIN32(x) __HRESULT_FROM_WIN32(x)
#endif

//
// Map an NT status value into a HRESULT
//

#define HRESULT_FROM_NT(x)      ((HRESULT) ((x) | FACILITY_NT_BIT))


// ****** OBSOLETE functions

// HRESULT functions
// As noted above, these functions are obsolete and should not be used.


// Extract the SCODE from a HRESULT

#define GetScode(hr) ((SCODE) (hr))

// Convert an SCODE into an HRESULT.

#define ResultFromScode(sc) ((HRESULT) (sc))


// PropagateResult is a noop
#define PropagateResult(hrPrevious, scBase) ((HRESULT) scBase)

//
// MessageId: ERROR_NOT_FOUND
//
// MessageText:
//
// Element not found.
//
#define ERROR_NOT_FOUND                  1168L

//
// MessageId: ERROR_INVALID_STATE
//
// MessageText:
//
// The group or resource is not in the correct state to perform the requested operation.
//
#define ERROR_INVALID_STATE              5023L

//
// MessageId: ERROR_INSUFFICIENT_BUFFER
//
// MessageText:
//
// The data area passed to a system call is too small.
//
#define ERROR_INSUFFICIENT_BUFFER        122L    // dderror

// ****** End of OBSOLETE functions.

#define E_NOT_SET                HRESULT_FROM_WIN32(ERROR_NOT_FOUND)
#define E_NOT_VALID_STATE        HRESULT_FROM_WIN32(ERROR_INVALID_STATE)
#define E_NOT_SUFFICIENT_BUFFER  HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER)

// ---------------------- HRESULT value definitions -----------------
//
// HRESULT definitions
//

#ifdef RC_INVOKED
#define _HRESULT_TYPEDEF_(_sc) _sc
#else // RC_INVOKED
#define _HRESULT_TYPEDEF_(_sc) ((HRESULT)_sc)
#endif // RC_INVOKED

#define NOERROR             0

//
// Error definitions follow
//

//
// Codes 0x4000-0x40ff are reserved for OLE
//
//
// Error codes
//
//
// MessageId: E_UNEXPECTED
//
// MessageText:
//
// Catastrophic failure
//
#define E_UNEXPECTED                     _HRESULT_TYPEDEF_(0x8000FFFFL)

#if defined(_WIN32) && !defined(_MAC)
//
// MessageId: E_NOTIMPL
//
// MessageText:
//
// Not implemented
//
#define E_NOTIMPL                        _HRESULT_TYPEDEF_(0x80004001L)

//
// MessageId: E_OUTOFMEMORY
//
// MessageText:
//
// Ran out of memory
//
#define E_OUTOFMEMORY                    _HRESULT_TYPEDEF_(0x8007000EL)

//
// MessageId: E_INVALIDARG
//
// MessageText:
//
// One or more arguments are invalid
//
#define E_INVALIDARG                     _HRESULT_TYPEDEF_(0x80070057L)

//
// MessageId: E_NOINTERFACE
//
// MessageText:
//
// No such interface supported
//
#define E_NOINTERFACE                    _HRESULT_TYPEDEF_(0x80004002L)

//
// MessageId: E_POINTER
//
// MessageText:
//
// Invalid pointer
//
#define E_POINTER                        _HRESULT_TYPEDEF_(0x80004003L)

//
// MessageId: E_HANDLE
//
// MessageText:
//
// Invalid handle
//
#define E_HANDLE                         _HRESULT_TYPEDEF_(0x80070006L)

//
// MessageId: E_ABORT
//
// MessageText:
//
// Operation aborted
//
#define E_ABORT                          _HRESULT_TYPEDEF_(0x80004004L)

//
// MessageId: E_FAIL
//
// MessageText:
//
// Unspecified error
//
#define E_FAIL                           _HRESULT_TYPEDEF_(0x80004005L)

//
// MessageId: E_ACCESSDENIED
//
// MessageText:
//
// General access denied error
//
#define E_ACCESSDENIED                   _HRESULT_TYPEDEF_(0x80070005L)

#else
//
// MessageId: E_NOTIMPL
//
// MessageText:
//
// Not implemented
//
#define E_NOTIMPL                        _HRESULT_TYPEDEF_(0x80000001L)

//
// MessageId: E_OUTOFMEMORY
//
// MessageText:
//
// Ran out of memory
//
#define E_OUTOFMEMORY                    _HRESULT_TYPEDEF_(0x80000002L)

//
// MessageId: E_INVALIDARG
//
// MessageText:
//
// One or more arguments are invalid
//
#define E_INVALIDARG                     _HRESULT_TYPEDEF_(0x80000003L)

//
// MessageId: E_NOINTERFACE
//
// MessageText:
//
// No such interface supported
//
#define E_NOINTERFACE                    _HRESULT_TYPEDEF_(0x80000004L)

//
// MessageId: ERROR_GRAPHICS_MCA_INVALID_TECHNOLOGY_TYPE_RETURNED
//
// MessageText:
//
// The monitor returned an invalid monitor technology type. CRT, Plasma and LCD (TFT) are examples of monitor technology types. This error implies that the monitor violated the MCCS 2.0 or MCCS 2.0 Revision 1 specification.
//
#define ERROR_GRAPHICS_MCA_INVALID_TECHNOLOGY_TYPE_RETURNED _HRESULT_TYPEDEF_(0xC02625DEL)

//
// MessageText:
//
// The specified pack is not the primary pack.
//
#define ERROR_VOLMGR_NOT_PRIMARY_PACK    _NDIS_ERROR_TYPEDEF_(0xC0380052L)

//
// MessageId: ERROR_VOLMGR_PACK_LOG_UPDATE_FAILED
//
// MessageText:
//
// All disks failed to be updated with the new content of the log.
//
#define ERROR_VOLMGR_PACK_LOG_UPDATE_FAILED _NDIS_ERROR_TYPEDEF_(0xC0380053L)

// CorError.h

#define CLDB_S_TRUNCATION SMAKEHR(0x1106)
#define CLDB_S_NULL SMAKEHR(0x1109)
#define CLDB_S_INDEX_TABLESCANREQUIRED SMAKEHR(0x1125)

// AdsErr.h

// Define the facility codes
//
#define FACILITY_WINDOWS                 8
#define FACILITY_STORAGE                 3
#define FACILITY_RPC                     1
#define FACILITY_SSPI                    9
#define FACILITY_WIN32                   7
#define FACILITY_CONTROL                 10
#define FACILITY_NULL                    0
#define FACILITY_ITF                     4
#define FACILITY_DISPATCH                2

//
// MessageId: E_ADS_BAD_PATHNAME
//
// MessageText:
//
//  An invalid directory pathname was passed
//
#define E_ADS_BAD_PATHNAME               _HRESULT_TYPEDEF_(0x80005000L)

//
// MessageId: E_ADS_INVALID_DOMAIN_OBJECT
//
// MessageText:
//
//  An unknown directory domain object was requested
//
#define E_ADS_INVALID_DOMAIN_OBJECT      _HRESULT_TYPEDEF_(0x80005001L)

//
// MessageId: E_ADS_INVALID_USER_OBJECT
//
// MessageText:
//
//  An unknown directory user object was requested
//
#define E_ADS_INVALID_USER_OBJECT        _HRESULT_TYPEDEF_(0x80005002L)

// asferr.h

#define STATUS_SEVERITY(hr)  (((hr) >> 30) & 0x3)

#ifdef RC_INVOKED
#define _ASF_HRESULT_TYPEDEF_(_sc) _sc
#else // RC_INVOKED
#define _ASF_HRESULT_TYPEDEF_(_sc) ((HRESULT)_sc)
#endif // RC_INVOKED


///////////////////////////////////////////////////////////////////////////
//
// Advanced Streaming Format (ASF) Errors (2000 - 2999)
//
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_NS                      0xD


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: ASF_E_BUFFEROVERRUN
//
// MessageText:
//
//  An attempt was made to seek or position past the end of a buffer.%0
//
#define ASF_E_BUFFEROVERRUN              _ASF_HRESULT_TYPEDEF_(0xC00D07D0L)

//
// MessageId: ASF_E_BUFFERTOOSMALL
//
// MessageText:
//
//  The supplied input or output buffer was too small.%0
//
#define ASF_E_BUFFERTOOSMALL             _ASF_HRESULT_TYPEDEF_(0xC00D07D1L)

//
// MessageId: ASF_E_BADLANGUAGEID
//
// MessageText:
//
//  The language ID was not found.%0
//
#define ASF_E_BADLANGUAGEID              _ASF_HRESULT_TYPEDEF_(0xC00D07D2L)

// BitsMsg.h

//
// MessageId: BG_E_ERROR_CONTEXT_QUEUE_MANAGER_NOTIFICATION
//
// MessageText:
//
// The error occurred while the notification callback was being processed. Background Intelligent Transfer Service (BITS) will try again later.
//
#define BG_E_ERROR_CONTEXT_QUEUE_MANAGER_NOTIFICATION 0x8020000CL

//
// MessageId: BG_E_DESTINATION_LOCKED
//
// MessageText:
//
// The destination file system volume is not available. Verify that another program, such as CheckDisk, is not running, which would lock the volume. When the volume is available, Background Intelligent Transfer Service (BITS) will try again.
//
#define BG_E_DESTINATION_LOCKED          0x8020000DL

// d2derr.h

//
// The supplied buffer was too small to accomodate the data.
//
#define D2DERR_INSUFFICIENT_BUFFER          HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER)


//
// D2D specific codes
//

//
// The object was not in the correct state to process the method.
//
#define D2DERR_WRONG_STATE                  MAKE_D2DHR_ERR(0x001)

//
// The object has not yet been initialized.
//
#define D2DERR_NOT_INITIALIZED              MAKE_D2DHR_ERR(0x002)

//
// The requested opertion is not supported.
//
#define D2DERR_UNSUPPORTED_OPERATION        MAKE_D2DHR_ERR(0x003)

//
// The geomery scanner failed to process the data.
//
#define D2DERR_SCANNER_FAILED               MAKE_D2DHR_ERR(0x004)

