//******************************************************************
//
// Copyright 2010-2014 Intel Corporation All Rights Reserved.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//
//******************************************************************
// File name:
//     uuid.h
//
// Description:  Helper UUID funtions
//
//
//
//*********************************************************************

#ifndef __CS_UUID__H
#define __CS_UUID__H

//NOTE: This is a temporary fix.  A better solution would be to remove
//the dependency on APIs that are not intended to be public from libraries
//that use these APIs (portable C SDK)
#pragma GCC visibility push(default)

#include <string>
#include <list>

#define UUID_STRING_SIZE                            (37) //AAAABBBB-CCCC-DDDD-EEEE-001122334455


#ifdef _WINRT

// The UUID definition comes from windows
#include "stcdef.h"

#else  //_WINRT

typedef struct UUID_t
{
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t   data4[8];
} UUID_t;

#define DECLARE_GUID(name)  extern "C" const UUID_t  name

#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) extern "C" const UUID_t name = { l,w1,w2, {b1,b2,b3,b4,b5,b6,b7,b8} }


//#define DECLARE_GUID(name) extern const UUID_t name = { l,w1,w2, {b1,b2,b3,b4,b5,b6,b7,b8} }

#define IS_UUID_EQUAL(_x, _y)  ((_x.data1 == _y.data1) && (_x.data2 == _y.data2) && (_x.data3 == _y.data3) && (_x.data4[0] == _y.data4[0]) && (_x.data4[1] == _y.data4[1]) && (_x.data4[2] == _y.data4[2]) && (_x.data4[3] == _y.data4[3]) && (_x.data4[4] == _y.data4[4]) && (_x.data4[5] == _y.data4[5]) && (_x.data4[6] == _y.data4[6]) && (_x.data4[7] == _y.data4[7]))
#define IS_UUID_NULL(_x)  ((_x.data1 == 0) && (_x.data2 == 0) && (_x.data3 == 0) && (_x.data4[0] == 0) && (_x.data4[1] == 0) && (_x.data4[2] == 0) && (_x.data4[3] == 0) && (_x.data4[4] == 0) && (_x.data4[5] == 0) && (_x.data4[6] == 0) && (_x.data4[7] == 0))

#define ASSIGN_UUID_TO_UUID(_dst, _src) ((UUID_t *)_src)->data1 = ((UUID_t *)_dst)->data1; \
                                             ((UUID_t *)_src)->data2 = ((UUID_t *)_dst)->data2; \
                                             ((UUID_t *)_src)->data3 = ((UUID_t *)_dst)->data3; \
                                             ((UUID_t *)_src)->data4[0] = ((UUID_t *)_dst)->data4[0]; \
                                             ((UUID_t *)_src)->data4[1] = ((UUID_t *)_dst)->data4[1]; \
                                             ((UUID_t *)_src)->data4[2] = ((UUID_t *)_dst)->data4[2]; \
                                             ((UUID_t *)_src)->data4[3] = ((UUID_t *)_dst)->data4[3]; \
                                             ((UUID_t *)_src)->data4[4] = ((UUID_t *)_dst)->data4[4]; \
                                             ((UUID_t *)_src)->data4[5] = ((UUID_t *)_dst)->data4[5]; \
                                             ((UUID_t *)_src)->data4[6] = ((UUID_t *)_dst)->data4[6]; \
                                             ((UUID_t *)_src)->data4[7] = ((UUID_t *)_dst)->data4[7];

#endif // _WINRT


DECLARE_GUID(NULL_GUID);

typedef char UUIDString_t[UUID_STRING_SIZE];

/*
 * Converts a uuid string to the qwarq ipc uuid
 */
int StringToUuid(const char *guidString, UUID_t *out);

/*
 * Converts a uuid string to the transport uuid
 */
//int UuidStringToTransportUuid(char *guidString, UUID_t *out);

/*
 * Converts a uuid to a string
 */
void UuidToString(const UUID_t &uuid, char *guidString, bool lowerCase = false);


std::string UuidToString(const UUID_t &uuid, bool lowerCase = false);

/**
 * Generate a UUID.
 */
void OSAL_GenerateUUID(UUID_t *uuid);

void DebugMessageUuid(const UUID_t &uuid);

typedef std::list<UUID_t> GuidList_t;

#pragma GCC visibility pop
#endif
