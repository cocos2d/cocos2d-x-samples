//******************************************************************
//
// Copyright 2010-2014 Intel Corporation All Rights Reserved.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//
//******************************************************************
// File name:
//     osal.h
//
// Description:  Interface to the Operating System Abstraction Layer (OSAL).  This
//               module is used to facilitate porting to different OSes.
//
//
//*********************************************************************

#ifndef __CS_OSAL__
#define __CS_OSAL__

#include "platformtypes.h"

typedef void *Mutex_t;
typedef void *RemoveLock_t;
typedef void *Thread_t;
typedef void *Event_t;

// OSAL is only used in the portable stack
#define PORTABLE_STACK 1

#define OSAL_MAX(a, b)       ((a) > (b)?(a):(b))
#define OSAL_MIN(a, b)       ((a) < (b)?(a):(b))

#define OSAL_TIMEOUT_INFINITE               (0)
#define OSAL_TIMEOUT                        (1)
#define OSAL_DEFAULT_STACK_SIZE             (0)
#define OSAL_THREAD_CLOSE_MILLISECOND_WAIT (500)_

/* Error codes return by this module */
#define OSAL_ERROR                    (-200)
#define OSAL_ERROR_INVALID_PARAMETER  (-201)
#define OSAL_ERROR_OVERFLOW           (-202)
#define OSAL_ERROR_BUSY               (-203)

/*
   Description: Prototype for the thread functions (See OSAL_Thread*).
   context  - optional parameter passed with the call the OSAL_ThreadCreate.
   returns  - not used
 */
typedef int (*OSAL_ThreadFunction_t)(void *context);

//TODO In progress
RemoveLock_t OSAL_RemoveLockCreate(const char *name);
void         OSAL_RemoveLockWaitAndFree(RemoveLock_t removeLock);
void         OSAL_RemoveLockLock(RemoveLock_t removeLock);
void         OSAL_RemoveLockRelease(RemoveLock_t removeLock);

/*
   Description: Creates a mutex
   name    - Name of the mutex (used for debugging error reporting)
   returns - A Mutex_t on success. NULL on error.
*/
Mutex_t OSAL_MutexCreate(const char *name);

/*
   Description: Frees a previously create mutex
   mutex - mutex from a successful call to OSAL_MutexCreate.
*/
void OSAL_MutexFree(Mutex_t mutex);

/*
   Description: Locks a the mutex.
   mutex - mutex from a successful call to OSAL_MutexCreate.
*/
void OSAL_MutexLock(Mutex_t mutex);

/*
   Description: Locks a the mutex
   mutex - mutex from a successful call to OSAL_MutexCreate.
*/
int OSAL_MutexTryLock(Mutex_t mutex);

/*
   Description: Releases a previously locked mutex (call to OSAL_MutexLock).
   mutex - mutex from a successful call to OSAL_MutexCreate.
*/
void OSAL_MutexRelease(Mutex_t mutex);

#define THREAD_SELF_CLEAN      0x1

/*
   Description: Creates a thread
   startAddress  - Function to be run as a thread (see OSAL_ThreadFunction_t).
   threadContext - optional parameter (which will be included in OSAL_ThreadFunction_t parameter.
   stackSize     - Size of the thread stack, or OSAL_DEFAULT_STACK_SIZE;
   flags         - reserved .
   name          - Name of the thread (used for debugging error reporting).
   return        - handle to the thread, NULL on error.
*/
Thread_t OSAL_ThreadCreate(OSAL_ThreadFunction_t startAddress, void *threadContext,
                           DWord_t stackSize, int flags = 0, const char *threadName = "");

/*
   Description: Closes a previously created thread.  This function will block waiting for
                the thread up to OSAL_THREAD_CLOSE_MILLISECOND_WAIT.  After the timeout,
                if the thread has not closed the thread context will not be free (error
                condition).
   handle  - Previously created handle (from OSAL_ThreadCreate).
*/
void OSAL_ThreadClose(Thread_t handle);

/*
   Description: Set the name of the current thread

   name     - The name to assign to the current thread

   return   - 0 on success, otherwise, and error code
 */
int OSAL_ThreadSetName(const char *name);


template <class T>
Thread_t StartSharedThread(const T &sharedPtr, OSAL_ThreadFunction_t funct, const char *name,
                           int flags = 0)
{
    Thread_t retVal = 0;

    // myInterface is a pointer to a shared pointer, because we cannot cast
    // a shared pointer to (void *) to pass it to InterfaceThread.  When
    // the thread terminates, it is responsible for freeing newInterface.
    T *myPtr = new T();
    (*myPtr) = sharedPtr;

    retVal = OSAL_ThreadCreate(funct, myPtr, 0, flags, name);

    return retVal;
}

/*
   Description: Sleeps given amount of time.
   milliseconds - number of milliseconds to sleep
*/
void OSAL_Sleep(int milliseconds);

/*
   Description: Find the system current millisecond count
   return - arbitrary start value revolving counter;
*/
DWord_t OSAL_GetTickCount(void);

/*
   Description: Create an event object
   name    - Name of the event (used for debugging and error reporting)
   returns - The Event_t used for all other OSAL_Event functions
*/
Event_t OSAL_EventCreate(const char *name);

/*
   Description: Free a previously created event object
   event   - Event_t from a successful call to OSAL_EventCreate.
*/
void OSAL_EventFree(Event_t event);

/*
   Description: Set an event on a previously created event object
   event           - Event_t from a successful call to OSAL_EventCreate.
   eventFlagsToSet - This value will be logically ORed into the event value.  The OSAL_EventWait
                     will get the combinations of all events set.
*/
void OSAL_EventSet(Event_t event, DWord_t eventFlagsToSet);

/*
   Description: Wait on an event.
   event               - Event_t from a successful call to OSAL_EventCreate.
   eventFlagsSet       - Logical OR of all calls to OSAL_EventSet.  Note, this value is not
                         cleared; therefore, any value passed in will be ORed with any events
                         values set.
   millisecondTimeout  - number of milliseconds to wait for the event.  This value can be set
                         to OSAL_TIMEOUT_INFINITE.
   returns             - Negative value on error, 0 for event, and OSAL_TIMEOUT for timeout.
*/
int OSAL_EventWait(Event_t event, DWord_t *eventFlagsSet, int millisecondTimeout);


/*
   Description: Generates a pseudo random number
   returns - The random number generated.
*/
DWord_t OSAL_PseudoRandomWord();

/*
 Description: gets the cloud.xml file path, that overrides built in settings
 returns - wether it got path
 */
extern "C" bool OSAL_GetCloudPath(char *buf, unsigned int length);

/*
 Description:  get the proxy host server, port, and URI (if applicable)
 returns - whether the command was successful, true does not mean there is a valid proxy (it could be empty)
 */
extern "C" bool OSAL_GetProxyInfo(const char *serverURI, char *proxyHost, int hostlen,
                                  int *proxyPort, char *proxyURI, int urilen);

/*
 Description:  get the default directory in which we save agent logs.
 returns - the character length of the path.  if the length passed is less than the length required
           call again passing a buffer and length that match the return of the first call.
 */
extern "C" DWord_t OSAL_GetDefaultAgentLoggingPath(char *buf, unsigned int length);

/*
 Description:  get the version of the current OS as a string.
 returns - the character length of the version.  if the length passed is less than the length required
           call again passing a buffer and length that match the return of the first call.
 */
extern "C" DWord_t OSAL_GetOSVersionString(char *buf, unsigned int length);

/*
 Description:  get the memory size of the current device, in kilobytes.
 returns - the memory size of the current device, in kilobytes, or 0 on error.
 */
extern "C" DWord_t OSAL_GetDeviceMemoryInKilobytes();

/*
 Description:  get the available disk size of the current device, in megabytes.
 returns - the available disk size of the current device, in megabytes, or 0 on error.
 */
extern "C" DWord_t OSAL_GetDeviceSpaceInMegabytes();

int OSAL_DWordToString(DWord_t dword, char *outString, int outStringLength, int radix);

// The following is declared extern "C" because iOS needs it
extern "C" bool OSAL_GetLocale(char *locale, int *localeLen);

#endif
