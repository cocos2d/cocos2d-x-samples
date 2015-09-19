/*
 * STC_RESULTS.h
 *
 *  Created on: Jan 22, 2014
 *      Author: joseph
 */

#ifndef STC_RESULTS_H_
#define STC_RESULTS_H_
#if !defined(_WIN32) && !defined(_WIN64)

#define STC_ABORT_CMD			(0x80004004)	//Operation aborted
#define STC_ERROR_FAIL			(0x80004005)	//Unspecified failure
#define STC_ERROR_INVALIDARG	(0x80070057)	//One or more arguments are not valid
#define STC_ERROR_NOTIMPL		(0x80004001)	//Feature is not implemented
#define STC_ERROR_UNEXPECTED	(0x8000FFFF)	//Unexpected failure

#define STC_INVALID_SOCKET		(-1);

#include <android/log.h>
#define CSDK_TAG "C_NativeChat"

#endif
#endif /* STC_RESULTS_H_ */
