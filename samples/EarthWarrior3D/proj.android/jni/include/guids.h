//******************************************************************
//
// Copyright 2005-2014 Intel Corporation All Rights Reserved.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//
//******************************************************************
// File name:
//     guids.h
//
// Description:
//     Header for Intel GUID parsing/storage helper functions
//
//
//
//*********************************************************************


#pragma once

#ifndef __GUIDSH__
#define __GUIDSH__

//NOTE: This is a temporary fix.  A better solution would be to remove
//the dependency on APIs that are not intended to be public from libraries
//that use these APIs (portable C SDK)
#pragma GCC visibility push(default)

#include "compatibility.h"

#if defined(_WIN32) || defined(WIN32) || defined(WINCE) || defined(_WIN32_WCE)
#include "STLSupport.h"
#include "hash.h"
#include <Guiddef.h>
#include <cguid.h>
#endif

#ifdef __ANDROID__
#include "wintypes.h"
#endif

#if !defined(_WIN32) && !defined(WIN32) && !defined(WINCE) && !defined(_WIN32_WCE) && !defined(GUID_NULL)
#include "uuid.h"
#define GUID_NULL NULL_GUID
#endif

// If this is not a WINDOWS or ANDROID platform, define GUID
#if !defined(WIN32) && !defined(WINCE) && !defined(__ANDROID__) && !defined(__CYGWIN__) && !defined(__APPLE__) && !defined(__linux__)
typedef struct GUID
{
    unsigned int   Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} GUID_t;
#endif

#if defined(WIN32) && !defined(_WINRT)
typedef struct _GUID UUID_t;
#endif

// If we are not using the local STL implementation or the STLPort
#if !defined(USE_STC_STL_LITE) && !defined(USE_STLPORT_STL)

// ... and if this is a windows platform
#if defined(_WIN32) || defined(WIN32) || defined(WINCE) || defined(_WIN32_WCE)

/// Specialization of the hash_compare traits template to provide hashing behavior using GUIDs as keys.
template <> class __COMMONLIBDECL__ stdext_dropin::hash_compare<GUID>
{
    public:
        /// Default bucket_size parameter
        static const size_t bucket_size = 4;
        /// Default minimum number of hash buckets
        static const size_t min_buckets = 8;

        /// Functor implementing a hashing function on a GUID. This function uses a straighforward
        /// hashing function on the entire GUID value (since some parts of a GUID are MAC-addresses
        /// and remain the same on some architectures for multiple GUID instances).
        /// \param[in] guid Globally unique identifier to hash.
        /// \return 32-bit hash of the passed-in GUID value.
        size_t operator()(const GUID &guid) const
        {
            size_t hash_val = 0;
            for (int i = 0; i < sizeof(guid) / sizeof(DWORD); ++i)
            {
                hash_val <<= 3;
                hash_val  ^= ((DWORD *)&guid)[i];
            }
            return hash_val;
        }

        /// Functor implementing a less-than operator between GUIDs.
        /// \param[in] guid1 GUID to compare.
        /// \param[in] guid2 GUID to compare to guid1.
        /// \return true iff guid1 is less than guid2 in the sense of being of a numerically smaller
        ///         value when the GUIDs are taken to be a 16-byte integers.
        bool operator()(const GUID &guid1, const GUID &guid2) const
        {
            return memcmp(&guid1, &guid2, sizeof(guid1)) < 0;
        }
};


namespace std
{
    /// Specialization of the less functor to provide sorting behavior using GUIDs as keys.
    /// \todo Convert to use std_dropin
    template <> class __COMMONLIBDECL__ less<GUID>
    {
        public:
            /// Functor implementing a less-than operator between GUIDs.
            /// \param[in] guid1 GUID to compare.
            /// \param[in] guid2 GUID to compare to guid1.
            /// \return true iff guid1 is less than guid2 in the sense of being of a numerically smaller
            ///         value when the GUIDs are taken to be a 16-byte integers.
            bool operator()(const GUID &guid1, const GUID &guid2) const
            {
                return memcmp(&guid1, &guid2, sizeof(guid1)) < 0;
            }
    };
}
#endif
#endif  // !USE_STC_STL_LITE


#if (defined(_WIN32) || defined(WIN32) || defined(WINCE) || defined(_WIN32_WCE)) && !defined(_WINRT)

namespace STC_std
{
    // Specialization of the hash functor to provide hashing behavior on the GUID type.
    template <> struct hash<GUID>
    {
        /// Functor implementing a hashing operator on a GUID type.
        /// \param[in] guid GUID to hash.
        /// \return 32-bit hash code representing the value of this GUID in the
        ///         finite group of hash codes.
        size_t operator()(const GUID &guid) const
        {
            size_t hash_val = 0;
            for (int i = 0; i < sizeof(guid) / sizeof(DWORD); ++i)
            {
                hash_val <<= 3;
                hash_val  ^= ((DWORD *)&guid)[i];
            }
            return hash_val;
        }
    };

    /// Specialization of the equal_to functor to provide an equality comparison on the GUID type.
    template <> struct equal_to<GUID>
    {
        /// Functor implementing an equality operator on a GUID type.
        /// \param[in] guid1 GUID to compare.
        /// \param[in] guid2 GUID to compare to guid1.
        /// \return true if guid1==guid2, false otherwise
        bool operator()(const GUID &guid1, const GUID &guid2) const
        {
            return !memcmp(&guid1, &guid2, sizeof(guid1));
        }
    };

    /// Specialization of the less functor to provide sorting behavior using GUIDs as keys.
    template <> struct less<GUID>
    {
        /// Functor implementing a less-than operator between GUIDs.
        /// \param[in] guid1 GUID to compare.
        /// \param[in] guid2 GUID to compare to guid1.
        /// \return true iff guid1 is less than guid2 in the sense of being of a numerically smaller
        ///         value when the GUIDs are taken to be a 16-byte integers.
        bool operator()(const GUID &guid1, const GUID &guid2) const
        {
            return memcmp(&guid1, &guid2, sizeof(guid1)) < 0;
        }
    };

}

namespace Intel
{
    /// A global helper function to write a GUID to the kernel debug message
    /// output queue in debug mode (only).
    void debugWriteGUID(const GUID &guid);
    /// A global helper function to write a GUID to the kernel debug message
    /// output queue.
    void retailWriteGUID(const GUID &guid);
}
#endif  // defined(_WIN32) || defined(WIN32) || defined(WINCE) || defined(_WIN32_WCE)


namespace Intel
{
    class GUIDObjectBase
    {
        public:
            GUIDObjectBase(GUID guid = GUID_NULL) : _guid(guid) {}

            inline operator const GUID() const throw() { return _guid; }
            inline operator       GUID() const throw() { return _guid; }

            static GUID          createGUID();

            inline bool operator==(const GUID &right) const throw() { return memcmp(&_guid, &right, sizeof(GUID)) == 0; }
            inline bool operator!=(const GUID &right) const throw() { return memcmp(&_guid, &right, sizeof(GUID)) != 0; }
            inline bool operator< (const GUID &right) const throw() { return memcmp(&_guid, &right, sizeof(GUID)) <  0; }
            inline bool operator> (const GUID &right) const throw() { return memcmp(&_guid, &right, sizeof(GUID)) >  0; }
            inline bool operator<=(const GUID &right) const throw() { return memcmp(&_guid, &right, sizeof(GUID)) <= 0; }
            inline bool operator>=(const GUID &right) const throw() { return memcmp(&_guid, &right, sizeof(GUID)) >= 0; }

            inline const GUID   &GetGuid() const { return _guid; }

        protected:
            inline void          SetGuid(const GUID &guid) { _guid = guid; }
        private:
            GUIDObjectBase(const GUIDObjectBase &);
            GUIDObjectBase &operator=(const GUIDObjectBase &);

        private:
            /// The object GUID
            GUID _guid;
    };
}


namespace Intel
{
    /// Global comparison operators on GUID
#if !defined(_WIN32) && !defined(WIN32) && !defined(WINCE) && !defined(_WIN32_WCE)
    bool operator==(const GUID &guid1, const GUID &guid2);
    bool operator!=(const GUID &guid1, const GUID &guid2);
#endif


    struct GUIDUtils
    {
#if defined(WIN32) || defined(_WIN32) || defined(WINCE) || defined(_WIN32_WCE)
        static std::string GUIDToString(const GUID &id);
#else
        static std::string GUIDToString(const UUID_t &id);
#endif

        static GUID stringToGUID(const std::string &source);
    };
}

bool operator<(const GUID &guid1, const GUID &guid2);
std::ostream &operator<<(std::ostream &os, const GUID &g);
std::istream &operator>>(std::istream &is, GUID &g);
GUID operator^(const GUID &guid1, const GUID &guid2);
GUID operator|(const GUID &guid1, const GUID &guid2);
GUID operator&(const GUID &guid1, const GUID &guid2);


#pragma GCC visibility pop

#endif // __GUIDSH__
