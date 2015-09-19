//******************************************************************
//
// Copyright 2011-2014 Intel Corporation All Rights Reserved.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//
//******************************************************************
// File name:
//     stcapi.h
//
//
//*********************************************************************

#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <WinSock2.h>
#ifdef STCAPI_EXPORTS
#define STC_API __declspec(dllexport)
#else
#define STC_API __declspec(dllimport)
#endif
// Temporarily only available for Windows, remove when portable implemenation available
#define HAVE_APP_SPECIFIC_ADVERTISEMENT
#else
#define SOCKET int*
#include "guids.h"
typedef unsigned short WORD;
typedef void *PVOID;
typedef DWORD *PDWORD;
typedef BYTE *PBYTE;
#define CALLBACK
#define MAX_PATH (260)
#define STC_API

#if defined(ANDROID) || defined(__linux__)
#define ENABLE_CLOUD_REGISTRATION
#endif

#endif

#ifndef __STCAPI_H
#define __STCAPI_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
typedef int bool;
#define TRUE 1
#define FALSE 0
#endif

/**
 * @defgroup STCMacros Macros
 *
 * @brief These defines specify flags that the CCF C/C++ SDK accepts
 * or returns in its calls and callback functions.
 */
///@{

/**
 * @defgroup STCResultCodes  STC Result Codes
 *
 * @brief The result of an STC API call; either success or a reason for failure
 */
///@{

#define STC_SUCCESS                          (S_OK)         ///< Returned when method has been completed with success
#define STC_WARNING_DEPRECATED_METHOD        (0x00000002)   ///< Returned when method's functionality has been removed because of deprecation.
#define STC_ERROR_NOT_INITIALIZED            (0x87FF0001)   ///< Error returned when STCInitialize() has not been called
#define STC_ERROR_COMPLETE_CALLBACK_NOT_SET  (0x87FF0002)   ///< Error returned when the callback is not set correctly
#define STC_ERROR_STREAM_CLOSED              (0x87FF0003)   ///< Error returned when the stream is closed
#define STC_ERROR_INVALID_LISTENING_TYPE     (0x87FF0004)   ///< Error returned when STCListenForInvites() is called with an invalid "mode" parameter.
#define STC_ERROR_OOB_DATA_SIZE_INVALID      (0x87FF0005)   ///< Error returned when too large an out-of-band invite data buffer is specified.

///@}

/**
  * @defgroup STCSessionUpdateTypes  STC Session Update Types
  * @brief An integer indicating the event that triggered a session update
  */
///@{

#define STC_UPDATE_AVAILABLE (1)  ///< Remote session is active and ready for connections.
#define STC_UPDATE_EXPIRED   (2)  ///< Remote session has expired.
#define STC_UPDATE_DISCOVERED (3) ///< Remote session has been discovered.
#define STC_UPDATE_INRANGE  (4)   ///< Remote session is in range.
#define STC_UPDATE_SHUTDOWN (5)   ///< Remote session has shutdown.
#define STC_UPDATE_UNKNOWN (6)    ///< Remote session has an unknown update type. This may be due to local version being out of date.

///@}

/**
  * @defgroup STCStreamEventTypes STC Stream Event Types
  * @brief An integer indicating the event that triggered a stream event
  *
  * When Intel CCF loses all available transports from the local session
  * to a remote session, the stream is suspended until communication can
  * be reestablished. When communication is reesstablished, CCF will send
  * a resume event to tell the application it can expect the stream to
  * be able to send and receive data again.
  */
///@{

#define STC_STREAM_EVENT_RESUMED (1)    ///< A suspended stream has resumed sending data
#define STC_STREAM_EVENT_SUSPENDED (2)  ///< A currently open stream has been suspended

///@}

/**
  * @defgroup STCAvatarTypes   STC Avatar Types
  * @brief An integer indicating the format of the Avatar
  */
///@{

#define STC_FORMAT_NONE      (0)  ///< No image available.
#define STC_FORMAT_BMP       (1)  ///< BMP format.

///@}

/**
  * @defgroup STCDiscoveryFlags STC Discovery Flags
  * @brief Flags indicating the discovery properties of a session
  *
  * A user-supplied custom avatar could contain an image of anything that
  * the user chooses.  Application authors may choose to handle custom
  * avatars differently from built-in avatars if they are concerned about
  * the content a user may add to their avatar.
  */
///@{

#define STC_DISCOVERY_FLAGS_IS_SELF       (0x00000001)  ///< The discovered session is "self" (owned by the local user)
#define STC_DISCOVERY_FLAGS_IS_REGISTERED (0x00000002)  ///< The discovered session is registered with Intel<SUP>&reg;</SUP> Identity Services
#define STC_DISCOVERY_AVATAR_IS_CUSTOM    (0x00000010)  ///< The discovered session uses a custom, user-defined avatar

///@}

/**
  * @defgroup STCListenType STC Listen Type
  * @brief An integer indicating the mode in which the @ref STCSessionUpdateCallback callback will operate.
  */
///@{

#define STC_ACCEPT_NONE  (0)    ///< Do not accept any invitation.
#define STC_ACCEPT_ONE   (1)    ///< Accept only one invitation. Ignore all invitations that follow.
#define STC_ACCEPT_MANY  (3)    ///< Accept multiple invitations.

///@}

/**
  * @defgroup STCInvitationAndStatusCodes   STC Invitation and Status Codes
  * @brief An integer indicating the status of a pending invitation.
  */
///@{

#define STC_INVITE_STATUS_GADGET_NOT_REGISTERED (2)         ///< Application is not registered.
#define STC_INVITE_STATUS_ATTEMPTING_REMOTE_CONNECTION (3)  ///< Attempting to create a connection with remote session.
#define STC_INVITE_STATUS_FAILED_REMOTE_CONNECTION (4)      ///< Connection with remote session has failed.
#define STC_INVITE_STATUS_WAITING_FOR_GADGET_RESPONSE (5)   ///< Connecting in progress.
#define STC_INVITE_STATUS_WAITING_FOR_CONNECT_BACK (6)      ///< Connecting is progress.
#define STC_INVITE_STATUS_GADGET_NOT_INSTALLED (7)          ///< Application is not installed.
#define STC_INVITE_STATUS_GADGET_LAUNCH_FAILURE (8)         ///< Failed to launch the application.
#define STC_INVITE_STATUS_INVITE_IGNORED (9)                ///< Invitation has been ignored.
#define STC_INVITE_STATUS_INVITE_TIMEOUT (10)               ///< Invitation has timed out.
#define STC_INVITE_STATUS_INVITE_CANCELLED (11)             ///< Invitation has been cancelled.
#define STC_INVITE_STATUS_INVITE_ACCEPTED (12)              ///< Invitation has been accepted by remote session.
#define STC_INVITE_STATUS_INVITE_REJECTED (13)              ///< Invitation has been rejected by remote session.
#define STC_INVITE_STATUS_INVITE_COMPLETE (14)              ///< Invitation process completed.

///@}

/**
  * @defgroup STCDiscoveryNodeServiceStatus STC Discovery Node Service Status
  * @brief An integer indicating the status of the service for Discovery Nodes.
  */
///@{

#define STC_SERVICESTATUS_SERVICEONLINE (0)             ///< Service is online.
#define STC_SERVICESTATUS_NETWORKNOTAVAILABLE (1)       ///< Network is not available. --Not implemented in CCF 3.0 Beta
#define STC_SERVICESTATUS_SERVERNOTAVAILABLE (2)        ///< Server is not available.  --Not implemented in CCF 3.0 Beta
#define STC_SERVICESTATUS_NOTAUTHORIZED (3)             ///< Not authorized.           --Not implemented in CCF 3.0 Beta
#define STC_SERVICESTATUS_SERVICENOTAVAILABLE (4)       ///< Service is not available.

///@}

/**
  * @defgroup STCDiscoveryNodeStatus    STC Discovery Node Status
  * @brief An integer indicating the status of a Discovery Node.
  */
///@{

#define STC_DISCOVERYNODESTATUS_UNDEFINED (0)           ///< Discovery Node status is undefined.
#define STC_DISCOVERYNODESTATUS_CREATING (1)            ///< Sending request to create Discovery Node.
#define STC_DISCOVERYNODESTATUS_SUBSCRIBING (2)         ///< Discovery Node is being subscribed to.
#define STC_DISCOVERYNODESTATUS_SUBSCRIBED (3)          ///< Discovery Node is subscribed to.
#define STC_DISCOVERYNODESTATUS_PUBLISHING (4)          ///< Publishing this session to the Discovery Node.
#define STC_DISCOVERYNODESTATUS_PUBLISHED (5)           ///< This session has been published to the Discovery Node.
#define STC_DISCOVERYNODESTATUS_RETRACTING (6)          ///< Discovery Node is in the process of being deleted.
#define STC_DISCOVERYNODESTATUS_UNSUBSCRIBING (7)       ///< Discovery Node is being unsubscribed to.
#define STC_DISCOVERYNODESTATUS_DELETING (8)            ///< Sending request to delete this Discovery Node.
#define STC_DISCOVERYNODESTATUS_DELETED (9)             ///< This Discovery Node has been deleted.

///@}

/**
  * @defgroup   STCSubscriptionResult STC Subscription Result
  * @brief      Status Codes for Subscription Result
  */
///@{

#define STC_SUBSCRIPTIONRESULT_STCNOTINITIALIZED (-2)               ///< CCF has not been initialized.
#define STC_SUBSCRIPTIONRESULT_FAILED (-1)                          ///< Failure using Discovery Node API.
#define STC_SUBSCRIPTIONRESULT_SUBSCRIPTIONCHANGED (0)              ///< Service status for cloud communications has completed succesfully/updated. 
#define STC_SUBSCRIPTIONRESULT_SUBSCRIPTIONNOTFOUND (1)             ///< Service status for cloud communications was not found.
#define STC_SUBSCRIPTIONRESULT_SUBSCRIPTIONEXISTS (2)               ///< Discovery Node already exists.
#define STC_SUBSCRIPTIONRESULT_SUBSCRIPTIONDENIED (3)               ///< Service status for cloud communications has denied your request.
#define STC_SUBSCRIPTIONRESULT_PUBLICATIONEXISTS (4)                ///< Social Node already exists with same credentials.
#define STC_SUBSCRIPTIONRESULT_PUBLICATIONNOTFOUND (5)              ///< Social Node doesn't exist. Check your discovery node credentials and try again.
#define STC_SUBSCRIPTIONRESULT_PUBLICATIONREFERENCENOTFOUND (6)     ///< Social Node doesn't exist. Check your discovery node credentials and try again.
#define STC_SUBSCRIPTIONRESULT_SERVICENOTAVAILABLE (7)              ///< Service for cloud communications is not available. Please try again later.
#define STC_SUBSCRIPTIONRESULT_NETWORKNOTAVAILABLE (8)              ///< Network not found.

///@}

/**
  * @defgroup   STCNodeType STC Node Type
  * @brief      Status Codes for Node Types
  */
///@{

#define STC_NODE_TYPE_NONE (0)      ///< If passed as parameter to @ref STCCreateDiscoveryNode or @ref STCJoinDiscoveryNode, the current user will not be visible to any users also marked as STC_NODE_TYPE_NONE.
#define STC_NODE_TYPE_PUBLISH (4)   ///< If passed as parameter to @ref STCCreateDiscoveryNode or @ref STCJoinDiscoveryNode, the current user will be visible to all others subscribed to node.

///@}

/**
  * @defgroup  STCNodeLastError STC Discovery Node Last Error
  * @brief  Last Error cases for Discovery Node Updates
  * @remarks Errors are only valid if and only if the
  *          Discovery Node Status is "Deleted."
  */
///@{

#define STC_NODE_ERROR_NOERROR (0)        ///< The node update was processed without error.
#define STC_NODE_ERROR_NODEEXISTS (1)    ///< The node trying to be created already exists.
#define STC_NODE_ERROR_NODENOTFOUND (2)  ///< The node does not exist.
#define STC_NODE_ERROR_INSUFFICIENTPRIVILEGES (3)  ///< Insufficient privileges.
#define STC_NODE_ERROR_INTERNALERROR (4) ///< The process performed on the node has experienced an internal error. If the problem persists, please contact a member of the CCF team.
#define STC_NODE_ERROR_UNKNOWNERROR (5)  ///< The process performed on the node has experienced an unknown error. If the problem persists, please contact a member of the CCF team.

///@}

/**
  * @defgroup   STCStringLength STC String Length
  * @brief  Maximum values for lengths of char arrays.
  */
///@{

#define STC_MAX_VERSION_LENGTH (250)                    ///< Maximum length of Platform and SDK Version.
#define STC_MAX_DISCOVERYNODEDATA_LENGTH (250)          ///< Maximum length of STCDiscoveryNode Name.
#define STC_MAX_CLIENTID_LENGTH (250)                   ///< Maximum length of Client Id.
#define STC_MAX_CLIENTSECRET_LENGTH (250)               ///< Maximum length of Client Secret.
#define STC_MAX_CHAR_ARRAY_LENGTH (250)                 ///< General maximum length of char arrays for STCAPI C/C++ SDK.
#define STC_MAX_REDIRECTURI_LENGTH (250)                ///< Maximum length of RedirectURI
#define STC_MAX_LASTERROR_LENGTH (250)                  ///< Maximum length of the Last Error found in Discovery Node Updates. @ref STCDiscoveryNodeUpdateCallback
#define STC_MAX_OOB_INVITE_DATA_SIZE (16384)            ///< Maximum supported length of the invitation out-of-band data payload. @ref STCInviteRequest
#ifdef HAVE_APP_SPECIFIC_ADVERTISEMENT
#define STC_MAX_ADVERTISEMENT_DATA_SIZE (8192)          ///< Maximum supported length of the advertisement payload.  @ref STCSetLocalAdvertisement
#endif

#if defined(ANDROID) || defined(__linux__)
#define STC_MAX_APP_NAME_LENGTH (41)
#define STC_MAX_APP_DESCRIPTION_LENGTH (241)
#define STC_MAX_INTENT_LENGTH (241)
#define STC_MAX_ACTIVITY_LENGTH (241)
#define STC_MAX_USER_NAME_LENGTH (129)
#define STC_MAX_SESSION_NAME_LENGTH (257)
#endif
///@}

/**
  * @brief  Variable types defined to identify handles.
  */
///@{
typedef long  STC_RESULT;
typedef PVOID STC_HANDLE,
        *PSTC_HANDLE; ///< Pointer to an SDK handle. A handle can be retrieved by calling STCInit().
typedef DWORD HSTCINVITE, *PSTCINVITE;  ///< Invitation Handle.
typedef PVOID HSTCSTREAM, *PSTCSTREAM;  ///< Stream Handle.

///@}



/**
  * @defgroup  STCTransportMode   STC Transport Mode
  * @brief An integer indicating the type of transport available. Types of transports available for STCSetAllowedTransports and STCGetAllowedTransports.
  */
///@{

#define STC_TRANSPORT_NONE          (0x00)  ///< STCSetAllowedTransports or STCGetAllowedTransports to allow no transport.  
#define STC_TRANSPORT_BLUETOOTH  (0x01)  ///< STCSetAllowedTransports or STCGetAllowedTransports to allow Bluetooth transport. 
#define STC_TRANSPORT_INET          (0x02)  ///< STCSetAllowedTransports or STCGetAllowedTransports to allow WiFi or Ethernet transport. 
#define STC_TRANSPORT_CLOUD     (0x04)  ///< STCSetAllowedTransports or STCGetAllowedTransports to allow Cloud transport using STUN and TURN.  
#define STC_TRANSPORT_ALL        (0xFFFFFFFF) ///< STCSetAllowedTransports or STCGetAllowedTransports to allow all transports.  

//TODO: Future use
//#define STC_TRANSPORT_INET_WIFI             (0x00000002)
//#define STC_TRANSPORT_WIFI_DIRECT       (0x00000004)
//#define STC_TRANSPORT_CLOUD_P2P             (0x00000008)
//#define STC_TRANSPORT_CLOUD_RELAY       (0x00000010)
//#define STC_TRANSPORT_TRANSPORT_ALL         (0xFFFFFFFF)

///@}


/**
  * @defgroup LogLevel Level Types
  * @brief The log level ordered from lowest to highest priority
  */
///@{
typedef enum
{
    LogLevel_None = 0,      ///< Always First
    LogLevel_Verbose,
    LogLevel_Debug,
    LogLevel_Info,
    LogLevel_Warning,
    LogLevel_Error,
    LogLevel_Fatal,
    LogLevel_Max,           ///< Always Last

} LogLevel;
///@}



/**
  * @defgroup LogMode LogMode Types
  * @brief Log mode to log to a file or live to Developer Central
  */
///@{
typedef enum
{
    LogMode_None = 0,   ///< Always First
    LogMode_Offline,
    LogMode_Online,
    LogMode_Both,
    LogMode_Max,        ///< Always Last

} LogMode;
///@}

/**
  * @defgroup Module Module Types
  * @brief Filter the log based on modules
  */
///@{
typedef enum
{
    Module_None = 0,
    Module_Application = 1,
    Module_Registration = 2,
    Module_ProximityDiscovery = 4,
    Module_CloudDiscovery = 8,
    Module_Invitation = 16,
    Module_DataStream = 32,
    Module_AllModules = 0x0000003f,
    Module_Max,

} Module;
///@}

///@}
/**
  * @defgroup   STCStruct STC Structure
  * @brief  This structure is passed when initializing the STC framework by calling @ref STCInit.
  *         It stores the information necessary for platform and cloud registration.
  */
///@{
typedef struct _STCAPPLICATIONID
{
    GUID    applicationId;                              ///< The application Id that identifies the application.
    char    clientId[STC_MAX_CLIENTID_LENGTH];          ///< The identifier for the user (if the application is user-specific) or application (if application not user-specific).
    char    clientSecret[STC_MAX_CLIENTSECRET_LENGTH];  ///< The passphrase for the user (if the application is user-specific) or application (if application not user-specific).
#if defined(ANDROID) || defined(__linux__)
    char    applicationName[STC_MAX_APP_NAME_LENGTH];   ///< Name of the application to be presented by dashboard (if present)
    char    applicationDescription[STC_MAX_APP_DESCRIPTION_LENGTH]; ///< Description of the application to be presented by dashboard (if present)
    char    inviteIntent[STC_MAX_INTENT_LENGTH];        ///<Intent launched (by dashboard, if present) to send an invite to an app that is not active
    char    launchActivity[STC_MAX_ACTIVITY_LENGTH];    ///<Intent launched (by dashboard, if present) to start an app
    DWORD   numPlayers;                                 ///<Number of simultaneous sessions able to participate in a single app session as defined by the app
    DWORD   applicationIconFormat;                      ///<Format of the app icon, to be used by dashboard (if present)
    DWORD   applicationIconSize;                        ///<Size of the app icon, to be used by dashboard (if present)
    BYTE    applicationIcon[];                          ///<The app icon, to be used by dashboard (if present)
#endif
} STCApplicationId, *PSTCApplicationId;

#if defined(ANDROID) || defined(__linux__)
#define STC_APPLICATION_ID_SIZE(_x_)  (sizeof(STCApplicationId) - sizeof(Byte_t) + (sizeof(Byte_t) * _x_))
#endif
///@}

/**
  * @brief This structure stores the information relating to the discovered
  *         or changed session.
  *
  * @note Additional information regarding local session registration with
  *             the cloud can be obtained from either
  *             @ref STCCheckCloudAuthorization or @ref STCQueryRegistrationStatus.
  */
///@{
typedef struct _STCSESSIONUPDATE
{
    STC_HANDLE
    sdkHandle;                ///< This updated tuple has come through this instance of the SDK.
    char    szUserName[MAX_PATH];        ///< A UTF-8 encoded C string containing the user name associated with an incoming session update.
    char    szSessionName[MAX_PATH];     ///< A UTF-8 encoded C string containing the name associated with incoming session update(UTF-8).
    char    szStatusText[MAX_PATH];      ///< A UTF-8 encoded C string containing the status text associated with user of incoming session update(UTF-8).
    DWORD   avatarSize;                  ///< The number of bytes in the avatar associated with incoming session update.
    PBYTE   avatar;                      ///< The avatar associated with incoming session update.
    BYTE    avatarType;                  ///< Format of the avatar associated with incoming session update.
    GUID      sessionId;                   ///< Session id associated with incoming session update.
    GUID      userId;                      ///< User id associated with incoming session update.
    BYTE    updateType;                  ///< Type of session update. @ref STCSessionUpdateTypes
    char    szIdentityIssuer[MAX_PATH];  ///< [Local Session Only]The security issuer (signer for the certificate) for the identity. Empty if not registered(UTF-8).
    char    szSecurityCode[MAX_PATH];    ///< [Local Session Only]The security code for the local session's relationship with the cloud(UTF-8).
    WORD    applicationCount;            ///< Number of items in applications[] associated with session update.
    GUID   *applications;                ///< Array of applications associated with incoming session update.
    WORD    cloudSourcesCount;           ///< Number of items in sources[] associated with session update.
    char  **cloudSources;                ///< Array of discovery Node sources associated with incoming session update (UTF-8). STC_MAX_DISCOVERYNODEDATA_LENGTH
    DWORD   flags;                       ///< Flag providing additional information of discovered session. @ref STCDiscoveryFlags
    bool    isRegistered;                ///< [Local Session Only]If the local session is registered with the cloud, this will be true.
    bool    isSelf;                      ///< If a remote session is owned by the same user as the local session, this will be true.
    bool    isAvailable;                 ///< If session associated with incoming session update's update type is STC_UPDATE_AVAILABLE, this flag is true. (@ref STCSessionUpdateTypes)
    bool    isAvailableProximity;        ///< If session associated with incoming session update is available via proximity transport(s) (i.e. wifi, bluetooth), this will be true.
    bool    isAvailableCloud;            ///< If session associated with incoming session update is available via cloud, this will be true.
} STCSessionUpdate, *PSTCSessionUpdate, STCSession, *PSTCSession;
///@}

#ifdef HAVE_APP_SPECIFIC_ADVERTISEMENT
/**
  * @brief  This is the structure passed when STCAdvertisementCallback is triggered.
  *
  */
///@{
typedef struct _STCADVERTISEMENTUPDATE
{
    GUID sessionId;                     ///< Identifies the session advertising this data
    GUID type;                          ///< RESERVED
    unsigned long recordId;             ///< Identifies the advertisement record.
    size_t size;                        ///< size of the data in the data buffer
    BYTE data[STC_MAX_ADVERTISEMENT_DATA_SIZE];     ///< The data advertised by the session
} STCAdvertisementUpdate, *PSTCAdvertisementUpdate;
#endif
///@}

/**
  * @brief  This is the structure passed when STCInviteRequestCallback is triggered.
  *
  */
///@{
typedef struct _INVITEREQUEST
{
    STC_HANDLE   sdkHandle;          ///< This invite request has come through this instance of the SDK.
    HSTCINVITE   hInvite;                ///< Invitation handle.
    GUID         sessionId;              ///< SessionId of the remote user sending Invitation Request.
    GUID         applicationId;          ///< ApplicationId of the application trying to connect.
    GUID         protocolId;             ///< Protocol ID (RESERVED).
    DWORD        protocolRevision;       ///< Protocol revision (RESERVED).
    GUID         instanceId;             ///< Instance ID (RESERVED).
    DWORD
    oobDataSize;           ///< Out-of-band data buffer size (0<=oobDataSize<=STC_MAX_OOB_INVITE_DATA_SIZE)
    BYTE         oobData[STC_MAX_OOB_INVITE_DATA_SIZE];  ///< Out-of-band data buffer.
} STCInviteRequest, *PSTCInviteRequest;
///@}

/**
  * @brief  This structure is passed when @ref STCInviteCompleteCallback is triggered.
  */
///@{
typedef struct _INVITECOMPLETE
{
    STC_HANDLE
    sdkHandle;              ///< This invitation complete struct has come through this instance of the SDK.
    HSTCINVITE   hInvite;                ///< Invitation handle.
    DWORD        statusCode;             ///< Status of the invitation.\ref STCInvitationAndStatusCodes
    GUID         sessionId;            ///< Session ID of remote user with whom you are connected.
    HSTCSTREAM
    hStream;                ///< Stream handle, if invitation is accepted and connection is successful.
} STCInviteComplete, *PSTCInviteComplete;
///@}

/**
 * @brief This structure is passed when @ref STCStreamEventUpdateCallback is triggered.
 */
///@{
typedef struct _STREAMEVENT
{
    STC_HANDLE sdkHandle; ///< This stream event update has come through this instance of the SDK.
    HSTCSTREAM hStream;   ///< Handle to the stream.
    DWORD streamEvent;    ///<  A stream event type. @ref STCStreamEventTypes
} STCStreamEvent, *PSTCStreamEvent;
///@}

/**
 * @brief This structure is passed when @ref STCCloudURIUpdateCallback is triggered.
 */
///@{
typedef struct _CLOUDLOGINURI
{
    STC_HANDLE sdkHandle; ///< This cloud update has come through this instance of the SDK.
    char *LoginURI;       ///< The URI used to login to the cloud.
    DWORD queryId;        ///<  Job number associated with original call to STCQueryLoginURI.
} STCCloudLoginURI, *PSTCCloudLoginURI;
///@}

/**
 * @brief This structure is passed when @ref STCCloudAuthorizationUpdateCallback is triggered.
 */
///@{
typedef struct _CLOUDAUTHORIZATION
{
    STC_HANDLE
    sdkHandle;               ///< This cloud update has come through this instance of the SDK.
    bool isRegistered;                  ///< Denotes whether or not the local service is registered with the cloud.
    char *deviceCertExpiryTime;         ///< Time at which the local service certificate with the cloud will expire.
    char *deviceCertExpiryEpochTime;    ///< Time at which the local service certificate with the cloud was created/updated last.
    char *LoginURI;                     ///< The URI used to login to the cloud.
    char *accessTokenExpiryTime;        ///< Time at which the server's valet key expires. (Note: The term 'valet key' is used to explain in few words that the cloud servers are permitted to do work on behalf of this service on this machine in the cloud.)
    DWORD queryId;                      ///< Job number associated with original call to STCQueryLoginURI.
} STCCloudAuthorization, *PSTCCloudAuthorization;
///@}

/**
 * @brief This structure is passed when @ref STCCloudRegistrationStatusChangedCallback is triggered.
 */
///@{
typedef struct _CLOUDREGISTRATION
{
    STC_HANDLE sdkHandle;            ///< This cloud update has come through this instance of the SDK.
    bool isRegistered;               ///< Denotes whether or not the local service is registered with the cloud.
    char *deviceCertExpiryTime;      ///< Time at which the local service certificate with the cloud will expire.
    char *deviceCertExpiryEpochTime; ///< Time at which the local service certificate with the cloud was created/updated last.
    DWORD queryId;                   ///< Job number associated with original call to STCQueryLoginURI.
} STCCloudRegistration, *PSTCCloudRegistration;
///@}

/**
  * @brief @ref STCDiscoveryNodeCredentials contains metadata describing
  *        a discovery node.
  *
  *  The @ref STCDiscoveryNodeCredentials struct is passed to
  *  @ref STCDiscoveryNodeCreate, @ref STCDiscoveryNodeJoin, and
  *  @ref STCSicoveryNodeLeave to identify which discovery node to create,
  *  join, or leave and to specify options to create, join, or leave.
  */
///@{
typedef struct _STCDISCOVERYNODECREDENTIALS
{
    /// @brief String describing, naming, or passphrase of Discovery Node.
    ///
    /// The data field is treated as a '\0' terminated C string and must
    /// contain at least one character and no more than
    /// @ref MAX_DISCOVERYNODEDATA_LEN characters including the terminating
    /// '\0'. The data field can be parsed however the developer would like.
    char data[STC_MAX_DISCOVERYNODEDATA_LENGTH];
    /// @brief Options for joining and creating discovery nodes
    ///
    /// A value of 0 is default.  A 0 means not to publish the local
    /// session's presence to anyone except the owner of the node.
    /// @ref STC_NODE_TYPE_PUBLISH, a value of 4, is to publish your
    /// presence to all node subscribers.
    DWORD nodeFlags;
    GUID applicationId;                         ///< The application ID of the application using the node
} STCDiscoveryNodeCredentials, *PSTCDiscoveryNodeCredentials;
///@}

/**
  * @brief STCDiscoveryNodeCredentialsUpdate notifies the application
  *        about changes to a discovery node.
  */
///@{
typedef struct _STCDISCOVERYNODECREDENTIALSUPDATE
{
    STC_HANDLE sdkHandle;        ///<The SDK handle used to create the discovery node being updated
    STCDiscoveryNodeCredentials
    discoveryNodeCredentials;    ///< Credentials for the discovery node being updated
    /// @brief The last error detected for the reported discovery node
    ///
    /// This field is set before the call to @ref STCDiscoveryNodeUpdateCallback.
    /// If it is not @ref STC_NODE_ERROR_NOERROR, there was an error.
    /// For a complete list of errors, see @ref STCNodeLastError.
    DWORD lastError;
    /// @brief Current state of the Discovery Node, see @ref STCDiscoveryNodeStatus for details
    DWORD status;
} STCDiscoveryNodeCredentialsUpdate, *PSTCDiscoveryNodeCredentialsUpdate;
///@}

/**
  * @brief STCSignalingUpdate notifies the application
  *        about recieved out of band signal events.
  */
///@{
typedef struct _STCSIGNALSENGINGUPDATE
{
    STC_HANDLE sdkHandle;        ///<The SDK handle used to create the discovery node being updated
    GUID sessionId;  ///< source session id.
    char message[MAX_PATH];  ///< message from source.
} STCSignalingUpdate, *PSTCSignalingUpdate;
///@}


/**
  * @brief  STC Extended Property (char* key, char* value) contains information
  *         used to add extended properties to the QueryLoginURI call.
  */
///@{
typedef struct _STCEXTENDEDPROPERTY
{
    char *key;      ///< Additional key to add.
    char *value;    ///< Value to assign to key.
} STCExtendedProperty, *PSTCExtendedProperty;
///@}

///@}

/**
  *******************************************************************************************
  *  @defgroup SDKInstanceAPI  SDK Instance
  *
  *  @brief The SDK Instance API allows applications to initialize and
  *         uninitialize the CCF Framework and access properties related
  *         to the local session. \ref TutorialDiscovery "How to Use"
  *
  *  @remarks CCFManager must be running or must have run and initialized against the Intel
  *             CCF service before this application or DLL initializes against the CCF service.
  *             If this is not done various or unknown error cases (STC_RESULT codes) will
  *             arise pertaining to Windows Component Object Module (COM).
  *
  *  @note To retrieve Intel verified members for STCApplicationId,
  *         please refer to the Intel CCF Programmers Guide.
  *
  *******************************************************************************************
  */
///@{
#if !defined(ANDROID) && !defined(__linux__)
/**
 *  @brief  This function initializes the STC framework and registers your
 *  application with the framework.
 *
 *  @remarks @ref STCInit should be the first function called by the application
 *              or DLL. All API calls made before calling @ref STCInit will return
 *              @ref STC_ERROR_NOT_INITIALIZED.
 *
 *  @param[out] sdkHandle - Returns the handle to an instance of the CCF SDK.
 *
 *  @param[in] id - Holds information about the application such as the
 *                          Application Id, Client Id and Client Secret.
 *  @param[in] reserved - Reserved for future use. Must be 0.
 *
 *  @return STCInit returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle is an invalid double pointer.)
 *  <dt>E_FAIL
 *  <dd>Initialization failed for some unspecified reason
 *  </dl>
 */

STC_API STC_RESULT STCInit(PSTC_HANDLE sdkHandle, STCApplicationId id, DWORD reserved);
#else

/**
 *  @brief  This function initializes the STC framework and registers your
 *  application with the framework.
 *
 *  @remarks @ref STCInit should be the first function called by the application
 *              or DLL. All API calls made before calling @ref STCInit will return
 *              @ref STC_ERROR_NOT_INITIALIZED.
 *  @param [in] applicationPath - Hold the path of the application.
 *  @param[out] sdkHandle - Returns the handle to an instance of the Intel CCF SDK.
 *
 *  @param[in] id - Holds information about the application such as the
 *                          Application Id, Client Id and Client Secret.
 *  @param[in] reserved - Reserved for future use. Must be 0.
 *
 *  @return STCInit returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle is an invalid double pointer.)
 *  <dt>E_FAIL
 *  <dd>Initialization failed for some unspecified reason
 *  </dl>
 */
STC_API STC_RESULT STCInit(const char *applicationPath, PSTC_HANDLE sdkHandle, STCApplicationId id,
                           DWORD reserved);
/**
 *  This function will set the local user name.
 *
 *  @remarks Null terminated user name, max char length = STC_MAX_USER_NAME_LENGTH.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] szUserName - the screen name to be associated with Intel CCF.
 *
 *  @return STCSetUserName returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle is an invalid double pointer.)
 *  <dt>E_FAIL
 *  <dd>Initialization failed for some unspecified reason
 *  </dl>
 */
STC_API STC_RESULT STCSetUserName(STC_HANDLE sdkHandle, const char *szUserName);
/**
 *  This function will set the local device name.
 *
 *  @remarks Null terminated user name, max char length = STC_MAX_USER_NAME_LENGTH.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] szDeviceName - the Device name to be associated with Intel CCF.
 *
 *  @return STCSetDeviceName returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle is an invalid double pointer.)
 *  <dt>E_FAIL
 *  <dd>Initialization failed for some unspecified reason
 *  </dl>
 */
STC_API STC_RESULT STCSetDeviceName(STC_HANDLE sdkHandle, const char *szDeviceName);
/**
 *  This function will set the local user avatar
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *  @param[in] avatarSize - The size of the app icon[Avatar].
 *  @param[in] avatarType - The format of the app icon[Avatar].
 *  @param[in] avatar     - The bytes of the local session's avatar.
 *
 *  @return STCSetAvatar returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle is an invalid double pointer.)
 *  <dt>E_FAIL
 *  <dd>Initialization failed for some unspecified reason
 *  </dl>
 */
STC_API STC_RESULT STCSetAvatar(STC_HANDLE sdkHandle, DWORD avatarSize, BYTE avatarType,
                                PBYTE avatar);
/**
 *  This function will set the local session status[Mood of the user]
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] szStatus - The Status of the Session[Mood of the Session].
 *
 *
 *  @return STCSetStatus returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle is an invalid double pointer.)
 *  <dt>E_FAIL
 *  <dd>Initialization failed for some unspecified reason
 *  </dl>
 */
STC_API STC_RESULT STCSetStatus(STC_HANDLE sdkHandle, const char *szStatus);
/**
 *  This function will provide unboxed state of the app.
 *
 *  @remarks isUnboxed will be true if avatar, session name, and user name have been set.

 *  @param[in] sdkHandle - The handle to the instance of the CCF SDK to use for this API.
 *
 *  @param[in] isUnboxed - The Status does APP is unboxed.
 *
 *
 *  @return STCSetStatus returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle is an invalid double pointer.)
 *  <dt>E_FAIL
 *  <dd>Initialization failed for some unspecified reason
 *  </dl>
 */
STC_API STC_RESULT STCQueryUnboxedState(STC_HANDLE sdkHandle, bool *isUnboxed);

#endif
/**
 * @brief STCInitialize is provided for backwards compatibility with
 * earlier versions of Intel CCF.
 */
#define STCInitialize STCInit

/**
 *  @brief This function will release all resources associated with the STC
 *  API. All CCF Framework calls made after calling STCCleanUp() will return
 *  @ref STC_ERROR_NOT_INITIALIZED.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @return STCCleanUp returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application is not initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  <dt>E_FAIL
 *  <dd>De-Initialization against the CCF service has failed. This possibly due to WINAPI SOCKET_ERROR. According to  [WSAGetLastError()](http://msdn.microsoft.com/en-us/library/windows/desktop/ms741580.aspx) may provide a specific error code for further debugging.
 *  </dl>
 */
STC_API STC_RESULT STCCleanUp(STC_HANDLE sdkHandle);

/**
 *  @brief This function gets the local session Id.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[out] LocalSessionId A pointer to the local session Id.
 *
 *  @return STCGetLocalSessionId returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCGetLocalSessionId(STC_HANDLE sdkHandle, GUID *LocalSessionId);

/**
 *  @brief This function gets the local session's discovery flags.
 *
 *  @remarks Valid session flags are: @ref STC_DISCOVERY_FLAGS_IS_SELF, @ref STC_DISCOVERY_FLAGS_IS_REGISTERED
 *                                      and @ref STC_DISCOVERY_AVATAR_IS_CUSTOM
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[out] flags A set of flags, bitwise OR'ed together describing local session state
 *
 *  @return STCGetLocalSessionFlags returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCGetLocalSessionFlags(STC_HANDLE sdkHandle, PDWORD flags);

/**
 *  @brief This function gets the Device GUID for a given Session GUID.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] sessionId The Session GUID whose Device GUID is sought.
 *
 *  @param[out] deviceId A pointer to the remote Device GUID.
 *
 *  @return STCLookupDeviceId returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle is an invalid pointer.)
 *  <dt>E_FAIL
 *  <dd>The sessionId is not a valid GUID or the sessionId is not a known sessionId.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCLookupDeviceId(STC_HANDLE sdkHandle, GUID sessionId, GUID *deviceId);

/**
 *  @brief This function gets the version information of STCServ.exe, the
 *  Intel CCF service running on Windows.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[out] platformVersion - A pointer to a string that will be populated with the Platform Version by this call.
 *                                  Make sure to allocate enough memory to platformVersion. Refer to STC_MAX_VERSION_LENGTH in group of defines: @ref STCStringLength
 *
 *  @return STCQueryPlatformVersion returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle or platformVersion is an invalid pointer.)
 *  <dt>E_FAIL
 *  <dd>"STCServ.exe" is/was not properly installed on this machine. More than likely, CCFManager was not installed correctly.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCQueryPlatformVersion(STC_HANDLE sdkHandle, char *platformVersion);

/**
 *  @brief This function gets the version information of STCAPI.dll, the Intel CCF
 *  SDK library that allows for integration with the CCF platform.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[out] sdkVersion - A pointer to a string that will be populated with SDK Version by this call.
 *                             Make sure to allocate enough memory to sdkVersion. Refer to STC_MAX_VERSION_LENGTH in group of defines: @ref STCStringLength
 *
 *  @return STCQuerySDKVersion returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle or sdkVersion is an invalid pointer.)
 *  <dt>E_FAIL
 *  <dd>"STCAPI.dll" is/was not properly installed on this machine. More than likely, CCFManager was not installed correctly.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCQuerySDKVersion(STC_HANDLE sdkHandle, char *sdkVersion);

/**
 *  @brief This function allows to send out of band signaling to remote device using session ID.
 *
 *  @param[in] sdkHandle - The handle to the instance of the CCF SDK to use for this API.
 *  @param[in] sessionId -  remote session ID.
 *  @param[in] pMessage -  siganling message.
 *
 *  @return STCSendSignalData returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e., sdkHandle or platformVersion is an invalid pointer.)
 *  <dt>E_FAIL
 *  <dd>"STCServ.exe" is/was not properly installed on this machine. More than likely, CCFManager was not installed correctly.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 */
STC_API STC_RESULT STCSendSignalDataW(STC_HANDLE sdkHandle, GUID sessionId, wchar_t *pMessage);

STC_API STC_RESULT STCSendSignalDataA(STC_HANDLE sdkHandle, GUID sessionId, char *pMessage);




/**
 *  @brief This function allows to choose which transports should be used for Intel CCF connectivity.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *  @param[in] transports - The type of transports chosen by the application. NOTE: @ref STC_TRANSPORT_INET will always be enabled.
 *
 *  @return STCSetAllowedTransports returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e. sdkHandle or platformVersion is an invalid pointer.)
 *  <dt>E_FAIL
 *  <dd>"STCServ.exe" is/was not properly installed on this machine. More than likely, CCFManager was not installed correctly.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 */
STC_API STC_RESULT STCSetAllowedTransports(STC_HANDLE sdkHandle, DWORD transports);

/**
*  @brief this function returns transports allowed to be used for Intel CCF connectivity.
*
*  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
*  @param[out] transports - The type of transports chosen by the application. NOTE: @ref STC_TRANSPORT_INET will always be enabled.
*
*  @return STCGetAllowedTransports returns @ref STC_SUCCESS upon success or a code indicating
*  why it failed.  The return code may be a STC Result Code
*  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
*  Common error STC_RESULT%s include:
*  <dl>
*  <dt>E_INVALIDARG
*   <dd>One of the parameters passed is invalid (i.e. sdkHandle or platformVersion is an invalid pointer.)
*  <dt>E_FAIL
*  <dd>"STCServ.exe" is/was not properly installed on this machine. More than likely, CCFManager was not installed correctly.
*  <dt>STC_ERROR_NOT_INITIALIZED
*  <dd>The application has not been initialized against the Intel CCF service.
*  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
*  <dd>The application needs to re-initialize with the Intel CCF service.
*  </dl>
*/

STC_API STC_RESULT STCGetAllowedTransports(STC_HANDLE sdkHandle, PDWORD transports);
///@}

/**
  *******************************************************************************************
  *  @defgroup DiscoveryAPI   Discovery/Session Update
  *
  *  @brief This API alerts the application to changes in remote sessions
  *
  *  Upon registration for Discovery event, the @ref STCSessionUpdateCallback will be triggered
  *  every time the STC framework discovers a new session or observes a change in a remote session. \ref TutorialDiscovery "How to use".
  *
  *
  *  @remarks Session Ids are only valid for the lifetime of Intel CCF platform.
  *          Suspend/resume, reboot, and restarting the Intel CCF platform invalidates
  *          the session Id. Some versions of Intel CCF keep the session Id constant
  *          across system events. Relying on this constancy will create problems
  *          with other STC releases. The device and session Ids are constant.
  *          These should be used for purposes of constancy instead of the session GUID.
  *
  * @note Calling other STC functions from a callback is discouraged
  *                 as it may result in a deadlock.
  *******************************************************************************************
  */

///@{


/**
 *      The Intel CCF service calls this callback upon any/all updates to either local or remote
 *          session updates.
 *
 *   @remarks To get local session info/updates, use @ref STCSetLocalSessionInfoCallback.
 *  @remarks To get remote session presence/info/updates, use @ref STCSetSessionUpdateCallback.
 *
 *  @param[out] update - A pointer to a @ref _STCSESSIONUPDATE struct containing the most up-to-date
 *                              information about the session.
 *
 *  @param[out] callbackArg - The pointer passed when registering the callback.
 *
 */
typedef void (CALLBACK *STCSessionUpdateCallback)(PSTCSessionUpdate update, PVOID callbackArg);

/**
 *    This function registers the callback to be associated with any/all updates to
 *          remote session(s).
 *
 *  @remarks    Upon initial registration of this callback, the callback will be called
 *                  immediately and sequentially for each and every currently known session.
 *  @remarks    It is the application's responsibility to maintain the session list.
 *  @remarks    Setting this callback to NULL at any time will end further announcements.
 *   @remarks   Calling the function again with the same callback function will cause the
 *                  STC service to resend the list of remote sessions again.
 *  @remarks   It is the application's responsibility to copy the 'update' struct or its
 *             contents. This needs to be done to avoid losing data the Intel CCF Service or SDK
 *             may release or overwrite at anytime after the callback.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] callback - Callback that will be called by the Intel CCF service upon any/all
 *                          updates to remote sessions.
 *
 *  @param[in] callbackArg (OPTIONAL) - Verifying argument to be sent back with callback.
 *
 *  @return STCSetSessionUpdateCallback returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */

STC_API STC_RESULT STCSetSessionUpdateCallback(STC_HANDLE sdkHandle,
        STCSessionUpdateCallback callback, PVOID callbackArg);


/**
 *    This function registers the callback to be associated with any/all updates to the
 *          local session.
 *
 *  @remarks Upon initial registration of this callback, the callback will be called
 *              immediately by the Intel CCF service.
 *   @remarks Setting this callback to NULL at any time will end further announcements.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] callback - Callback that will be called by the Intel CCF service upon any/all
 *                          updates to the local session.
 *
 *  @param[in]  callbackArg (OPTIONAL) - Verifying argument to be sent back with callback.
 *
 *  @return STCSetLocalSessionInfoCallback returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSetLocalSessionInfoCallback(STC_HANDLE sdkHandle,
        STCSessionUpdateCallback callback, PVOID callbackArg);

#ifdef HAVE_APP_SPECIFIC_ADVERTISEMENT
/**
 *  The CCF service calls this callback upon any updates to session adverisements.
 *
 *  @remarks If the session has stopped advertising data, update->size will be zero.
 *
 *  @param[out] update - A pointer to a @ref _STCADVERTISEMENTUPDATE struct containing the most recent
 *                       advertised data.
 *
 *  @param[out] callbackArg - The pointer passed when registering the callback.
 */
typedef void(CALLBACK *STCAdvertisementUpdateCallback)(PSTCAdvertisementUpdate update,
        PVOID callbackArg);

/**
 *  This function registers the callback to be associated with any updates to session
 *  advertised data.
 *
 *  @remarks Setting this callback to NULL at any time will end further announcements.
 *
 *  @param[in] sdkHandle - The handle to the instance of the CCF SDK to use for this API.
 *
 *  @param[in] callback - Callback that will be called by the CCF service.
 *
 *  @param[in]  callbackArg (OPTIONAL) - Verifying argument to be sent back with callback.
 *
 *  @return STCSetAdvertisementUpdateCallback returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *    <dt>E_INVALIDARG
 *      <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
 *    <dt>STC_ERROR_NOT_INITIALIZED
 *      <dd>The application has not been initialized against the CCF service.
 *    <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *      <dd>The application needs to re-initialize with the CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSetAdvertisementUpdateCallback(STC_HANDLE sdkHandle,
        STCAdvertisementUpdateCallback callback, PVOID callbackArg);

/**
 * @brief Reserved
 */
typedef void STC_ADVERTISEMENT_FILTER;

/*
 *  This function registers advertisement data that will be visible to other sessions.
 */

STC_API STC_RESULT STCSetLocalAdvertisement(STC_HANDLE sdkHandle, GUID type, size_t size,
        void *data, STC_ADVERTISEMENT_FILTER *filter);

/*
 * This function clears any previously set advertisement data.  To change the data
 * advertised, multiple STCSetLocalAdvertisement calls can be made in a row
 * (i.e. it is _not_ necessary to clear the advertisement data before setting new data).
 *
 * Use this function to stop advertising any data.
*/

STC_API STC_RESULT STCClearLocalAdvertisement(STC_HANDLE sdkHandle);
#endif
///@}

/**
  *******************************************************************************************
  *  @defgroup InvitationAndConnectionAPI   Invitation & Connection
  *
  *  @brief This API allows for application control over invitations and connections.
  *
  *  For the purpose of Intel CCF, an invitation is defined as a request to connect. The invitation
  *     can be accepted, rejected or ignored by the remote session.\ref TutorialInvites "How to use"
  *
  * @note Calling other STC functions from a callback is discouraged
  *                 as it may result in a deadlock.
  *******************************************************************************************
  */
///@{

/**
 *    The Intel CCF service calls this callback when a remote session
 *          wishes to connect to the local session.
 *
 *   @remarks The application should respond by calling @ref STCSendInviteResponse,
 *              either during the callback, or after the callback without the timeout period.
 *  @remarks It is the application's responsibility to copy the 'message' struct or its
 *          contents. This needs to be done to avoid losing data the Intel CCF Service or SDK
 *          may release or overwrite at anytime after the callback.
 *
 *  @param[out] message - A pointer to STCInviteRequest struct.
 *
 *  @param[out] callbackArg - The pointer passed when registering the callback.
 *
 */
typedef void (CALLBACK *STCInviteRequestCallback)(PSTCInviteRequest message, PVOID callbackArg);

/**
 *     The Intel CCF service calls this callback when an invitation handshake
 *          completes. It will be called in response to calling
 *          @ref STCSendInviteResponse or @ref STCSendInviteRequest. If the
 *          invitation was accepted, a valid HSTCSTREAM will be sent to be used
 *          for communications with the remote session.
 *
 *  @remarks   It is the application's responsibility to copy the 'message' struct or its
 *             contents. This needs to be done to avoid losing data the Intel CCF service
 *             or SDK may release or overwrite at anytime after the callback.
 *
 *  @param[out] message - A pointer to STCInviteComplete struct.
 *
 *  @param[out] callbackArg - The pointer passed when registering the callback.
 *
 */
typedef void (CALLBACK *STCInviteCompleteCallback)(PSTCInviteComplete message, PVOID callbackArg);

/**
 *    The Intel CCF service calls this callback when a stream with a
 *       a remote session either becomes suspended, or resumes
 *       from being suspended.
 *
 * @param[out] message - A pointer to a @ref _STREAMEVENT struct containing a stream event.
 *
 * @param[out] callbackArg - The pointer passed when registering the callback.
 *
 */
typedef void (CALLBACK *STCStreamEventUpdateCallback)(PSTCStreamEvent message, PVOID callbackArg);

/**
 *    The Intel CCF service calls this callback for incoming out of band signaling message.
 *
 * @param[out] update - A pointer to a @ref PSTCSignalingUpdate struct containing a signaling message.
 *
 * @param[out] callbackArg - The pointer passed when registering the callback.
 *
 */
typedef void (CALLBACK *STCSignalingUpdateCallback)(PSTCSignalingUpdate update, PVOID callbackArg);

/**
 *    This function enables the application to accept invitation requests
 *      from remote sessions. The Intel CCF service executes the callback when
 *      an invitation request is received and allows the application to
 *      accept or reject the invitation using STCSendInviteResponse().
 *
 *  @remarks    Mode can be defined as operational mode as defined below:\n
 *              STC_ACCEPT_NONE  - No longer accept invitations.\n
 *              STC_ACCEPT_ONE   - Accept one invitation only.\n
 *              STC_ACCEPT_MANY  - Accept until disabled.\n
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] callback - Callback that will be called by the Intel CCF service upon any/all incoming invites.
 *
 *  @param[in]  callbackArg (OPTIONAL) - Verifying argument to be sent back with callback.
 *
 *  @param[in] mode - Allow multiple invitations per this session, allow only one, or allow none. @ref STCListenType
 *
 *  @return STCListenForInvites returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer or mode is not a valid selection.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCListenForInvites(STC_HANDLE sdkHandle, STCInviteRequestCallback callback,
                                       PVOID callbackArg, BYTE mode);

/**
 *    This function registers the callback that will be associated with a successful connection to a remote session.
 *
 *  @remarks This function must be called on both sides, Inviter and Invitee, before calling @ref STCListenForInvites or @ref STCSendInviteRequest.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] callback - Callback that the Intel CCF service will call upon a successful connection to a remote session.
 *
 *  @param[in] callbackArg (OPTIONAL) - Verifying argument to be sent back with callback.
 *
 *  @return STCSetInviteCallback returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSetInviteCallback(STC_HANDLE sdkHandle, STCInviteCompleteCallback callback,
                                        PVOID callbackArg);

/**
 *    This function registers the callback that will be associated with any stream event/update.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] callback - Callback that the Intel CCF service will call upon any stream event/update.
 *
 *  @param[in] callbackArg (OPTIONAL) - Verifying argument to be sent back with callback.
 *
 *  @return STCSetInviteCallback returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSetStreamEventCallback(STC_HANDLE sdkHandle,
        STCStreamEventUpdateCallback callback, PVOID callbackArg);



/**
 *    This function registers the callback that will be associated with any out of band siganling message.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] callback - Callback that the Intel CCF service will call upon any stream event/update.
 *
 *  @param[in] callbackArg (OPTIONAL) - Verifying argument to be sent back with callback.
 *
 *  @return STCSetInviteCallback returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSetSignalingUpdateCallback(STC_HANDLE sdkHandle,
        STCSignalingUpdateCallback callback, PVOID callbackArg);


/**
 *    This function sets the maximum number of invites per remote session.
 *          A remote session may only be able to send X amount of invites
 *          for this app only. Default value of 0 defaults within the SDK.
 *
 *  @remarks    In most cases this API function does not need to be called.
 *                  Without calling this, the default value is 0.
 *                  Max incoming invites is set by the service in default mode.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] maxIncomingInvites The maximum number of invites the application is willing to process at one time.
 *
 *  @return STCSetMaxIncomingInvites returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSetMaxIncomingInvites(STC_HANDLE sdkHandle, int maxIncomingInvites);

/**
 *     This function sends an invitation request to a remote session. The response
 *          is received using the STCInvitationCompleteCallback that is set
 *          using STCSetInviteCallback().
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[out] hInvite - Handle to the invitation.
 *
 *  @param[out] sessionId - session Id of remote session you are trying to connect.
 *
 *  @param[out] applicationId - Your application Id used during STCInitialize.
 *
 *  @param[in] dwTimeout - Timeout for invitation request.
 *
 *  @return STCSendInviteRequest returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle or hInvite is an invalid pointer.)
 *  <dt>E_FAIL
 *  <dd>Possible Reason: The remote session has been lost in the duration of this request.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSendInviteRequest(STC_HANDLE sdkHandle, PSTCINVITE hInvite, GUID sessionId,
                                        GUID applicationId, DWORD dwTimeout);

/**
 *     This function sends an invitation request to a remote session. The response
 *          is received using the STCInvitationCompleteCallback that is set
 *          using STCSetInviteCallback().
 *
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[out] hInvite - Handle to the invitation.
 *
 *  @param[out] sessionId - session Id of remote session you are trying to connect.
 *
 *  @param[out] applicationId - Your application Id used during STCInitialize.
 *
 *  @param[in] dwTimeout - Timeout for invitation request.
 *
 *  @param[in] OOBData - Out-of-band data to send with the invitation request. If NULL, no data will be sent.
 *
 *  @param[in] OOBDataSize - Size of the out-of-band data buffer. Sending a buffer of length greater than STC_MAX_OOB_INVITE_DATA_SIZE
 *                           will result in an error.
 *
 *  @return STCSendInviteRequest returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle, hInvite, or OOBData is an invalid pointer.)
 *  <dt>E_FAIL
 *  <dd>Possible Reason: The remote session has been lost in the duration of this request.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_ERROR_OOB_DATA_SIZE_INVALID
 *  <dd>The specified out-of-band invitation data buffer is too large.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSendInviteRequestEx(STC_HANDLE sdkHandle, PSTCINVITE hInvite, GUID sessionId,
        GUID applicationId, DWORD dwTimeout, const BYTE *OOBData, size_t OOBDataSize);


/**
 *    The application should call this function in response to the
 *          invitation request given in the STCInviteCompleteCallback. Once
 *          the invitation is accepted and the stream is established,
 *          the invitation complete callback will be executed.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] hInvite - The invitation handle passed in from STCInviteRequestCallback.
 *
 *  @param[in] response - TRUE to accept and FALSE to reject.
 *
 *  @return STCSendInviteResponse returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle or hInvite is an invalid pointer.)
 *  <dt>E_FAIL
 *  <dd>Possible Reason: The remote session has been lost in the duration of this call.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSendInviteResponse(STC_HANDLE sdkHandle, HSTCINVITE hInvite, bool response);

///@}


/**
  *******************************************************************************************
  *  @defgroup CommunicationAPI   Communication
  *
  *  @brief This API allows you to send and receive data to and from the remote sessions.\ref TutorialComms "How to use"
  *
  * @note Calling other STC functions from a callback is discouraged
  *                 as it may result in a deadlock.
  *******************************************************************************************
  */
///@{

/**
 *       This function connects the supplied socket to the datasource represented by hSteram.
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[in] sock - A valid WinSock2 socket created for AF_INET, SOCK_STREAM, IPPROTO_TCP.
 *
 * @param[in] hStream - The stream given in the invite complete callback.
 *
 *  @return STCConnectSocket returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer or the socket is invalid, corrupt, or already connected.)
 *  <dt>E_FAIL
 *  <dd>Possible Reason: Socket failed to connect on WINAPI connect function. According to http://msdn.microsoft.com, WSAGetLastError() may provide a specific error code for further debugging.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 * @code
// create the socket
sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if( sock != INVALID_SOCKET ){
    // Initialize the socket with hstream got from the callback on STCInviteCompleteCallback.
    STC_RESULT = STCConnectSocket(sock, hStream);
    if(! SUCCEEDED( STC_RESULT ) )
    {
    //ERROR:STCConnectSocket connect Failed
    return E_HANDLE;
    }
}
 * @endcode
 *
 */
STC_API STC_RESULT STCConnectSocket(STC_HANDLE sdkHandle, SOCKET sock, HSTCSTREAM hStream);

///@}
#ifdef ENABLE_CLOUD_REGISTRATION
/**
  *******************************************************************************************
  *  @defgroup CloudCheckAPI      Cloud Registration
  *
  *  @brief This API allows you to perform checks and the initial steps needed to
  *             register and communicate with the Cloud.
  *
  * @remarks On Windows, it is suggested to use the ISVLib APIs for cloud registration.
  *
  * @note  Calling other STC functions from a callback is discouraged
  *                 as it may result in a deadlock.
  *******************************************************************************************
  */
///@{

/**
 * @brief This callback is used to obtain the LoginURI from the service.
 *
 * @param[out] message - A pointer to a @ref _CLOUDLOGINURI struct containing LoginURI from the service.
 *
 */
typedef void (CALLBACK *STCCloudURIUpdateCallback)(PSTCCloudLoginURI message, PVOID callbackArg);

/**
 * @brief This callback is used to obtain the LoginURI Properties from the service.
 * @note This callback will be returned on any/all updates to the authorization (including registration status).
 *
 * @param[out] message - A pointer to a @ref _CLOUDAUTHORIZATION struct containing authorization properties.
 *
 */

typedef void (CALLBACK *STCCloudAuthorizationUpdateCallback)(PSTCCloudAuthorization message,
        PVOID callbackArg);

/**
 * @brief This callback is used to obtain information about the status of Registration with the Cloud from the service.
 *
 * @note This callback is guaranteed to only be returned immediately after calling @ref STCQueryRegistrationStatus.
 *
 * @param[out] message - A pointer to a @ref _CLOUDREGISTRATION struct containing registration properties.
 *
 */

typedef void (CALLBACK *STCCloudRegistrationStatusChangedCallback)(PSTCCloudRegistration message,
        PVOID callbackArg);

/**
 *    This function registers the callback that will be called in response to @ref STCQueryLoginURI.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] callback - Callback that the Intel CCF SDK will call in response to @ref STCQueryLoginURI.
 *
 *  @param[in] callbackArg (OPTIONAL) - Verifying argument to be sent back with callback.
 *
 *  @return STCSetCloudURIUpdateCallback returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *  <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSetCloudURIUpdateCallback(STC_HANDLE sdkHandle,
        STCCloudURIUpdateCallback callback, PVOID callbackArg);

/**
 *    This function registers the callback that will be called in response to any cloud authorization updates.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] callback - Callback that the Intel CCF SDK will call in response to @ref STCRegisterWithCloud or
 *                          @ref STCCheckCloudAuthorization.
 *
 *  @param[in] callbackArg (OPTIONAL) - Verifying argument to be sent back with callback.
 *
 *  @return STCSetCloudAuthorizationUpdateCallback returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *  <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSetCloudAuthorizationUpdateCallback(STC_HANDLE sdkHandle,
        STCCloudAuthorizationUpdateCallback callback, PVOID callbackArg);

/**
 *    This function registers the callback that will be called in response to any cloud authorization updates.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] callback - Callback that the Intel CCF SDK will call in response to @ref STCQueryRegistrationStatus.
 *
 *  @param[in] callbackArg (OPTIONAL) - Verifying argument to be sent back with callback.
 *
 *  @return STCSetCloudRegistrationStatusChangedCallback returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *  <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSetCloudRegistrationStatusChangedCallback(STC_HANDLE sdkHandle,
        STCCloudRegistrationStatusChangedCallback callback, PVOID callbackArg);

/**
 * @brief Set the cloud token and query ID to use for connecting to cloud resources.
 *
 * After calling STCQueryLoginURI, Intel CCF will call the STCCloudURIUpdateCallback
 * function passed to STCQueryLoginURI with the login URI as a parameter.
 * The registration token and query Id will be included as GET parmeters
 * on the login URI.
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API
 *
 * @param[in] registrationToken[STC_MAX_CHAR_ARRAY_LENGTH] - The token for use with registering with cloud
 *
 * @param[out] queryId - JobId/queryId returns 0 if error. Otherwise it is the jobId.
 *
 *  @return STCRegisterWithCloud returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle or queryId is an invalid pointer.)
 *  <dt>E_FAIL | E_NOT_VALID_STATE
 *  <dd>Check internet connectivity.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCRegisterWithCloud(STC_HANDLE sdkHandle, char registrationToken[1024],
                                        PDWORD queryId);

/**
 * @brief This function sets the callback for URI Updates and retrieves the jobId number.
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[in] callback - Upon callback, will return the LoginURI Properties.
 *
 * @param[in] clientID[STC_MAX_CHAR_ARRAY_LENGTH] - The session or application(if applicable) Id registered with FedId.
 *
 * @param[in] redirectURI[STC_MAX_CHAR_ARRAY_LENGTH] - URI/URL to be used as the redirect from the cloud servers. (i.e. https://www.google.com)
 *
 * @param[out] queryId - JobId /queryId returns 0 if error. Otherwise it is the jobId.
 *
 *  @return STCQueryLoginURI returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG</dt>
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle or queryId is an invalid pointer.)
 *       @ref STCInit was called with incorrect parameters for @ref _STCAPPLICATIONID struct.
 *       One or more of the parameters given in this call were incorrect or invalid.
 *  <dt>E_FAIL | E_NOT_VALID_STATE</dt>
 *       <dd>Check internet connectivity.
 *  <dt>STC_ERROR_NOT_INITIALIZED</dt>
 *       <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *       <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCQueryLoginURI(STC_HANDLE sdkHandle, char clientID[STC_MAX_CHAR_ARRAY_LENGTH],
                                    char redirectURI[STC_MAX_CHAR_ARRAY_LENGTH], PDWORD queryId);

/**
 * @brief This function is used for expansion of LoginURI properties.
 *
 *  It works in accordance with the STCQueryLoginURI() function. Any
 *      properties added with this method will be passed once STCQueryLoginURI() is called.
 *
 *  @note Do not add parameters that are already included in the STCQueryLoginURI() function call.
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[in] extendedProperty[] - Array of parameters to be added to LoginURI Properties list.
 *
 * @param[in] sizeOfArray - Number of properties to be added to the LoginURI properties list. 0 is not a valid.
 *
 *  @return STCAddExtendedProperty returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle or extendedProperty is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCAddExtendedProperty(STC_HANDLE sdkHandle,
        STCExtendedProperty *extendedProperty[], int sizeOfArray);

/**
 *  @brief This call obtains the status of Registration with the Cloud from the service. The jobId is handed back.
 *
 *  @note This callback is only guaranteed to be returned immediately after making this call.
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[in] callback - Upon callback, hands up status information regarding the cloud servers/local service certificates/tokens.
 *
 * @param[out] queryId - JobId/QueryId returns 0 if error, otherwise it is the jobId.
 *
 *  @return STCQueryRegistrationStatus returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle queryId is an invalid pointer.)
 *  <dt>E_FAIL | E_NOT_VALID_STATE
 *  <dd>Check internet connectivity.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCQueryRegistrationStatus(STC_HANDLE sdkHandle, PDWORD queryId);

/**
 *  @brief This call obtains the local service's authorization status with the cloud servers.
 *  @note This callback will be returned on any/all updates to the authorization (including registration status).
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[in] callback - Upon callback, hands up status information regarding the cloud servers/local service certificates/tokens.
 *
 *  @return STCCheckCloudAuthorization returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
 *  <dt>E_FAIL | E_NOT_VALID_STATE
 *  <dd>Check internet connectivity.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCCheckCloudAuthorization(STC_HANDLE sdkHandle, PDWORD queryId);

///@}

#endif //ENABLE_CLOUD_REGISTRATION



/**
  *******************************************************************************************
  *  @defgroup DiscoveryNodeAPI   Discovery Node
  *
  *  @brief This API allows creating, joining & leaving the node in Discovery Node services.
  *         Updates for these functionalities will be provided in STCDiscoveryNodeUpdateCallback()
  *         by registering the function in STCSetDiscoveryNodeUpdateCallback().  \ref TutorialDiscoveryoverNode "How to Use"
  *
  * @note Calling other STC functions from a callback is discouraged
  *                 as it may result in a deadlock.
  *******************************************************************************************
  */
///@{

/**
 *  This callback is called from the CCF service whenever an update to a discovery node is available.
 *
 *  @param[out] discoveryNode_Update - A pointer to @ref _STCDISCOVERYNODECREDENTIALSUPDATE struct that contains information pertaining to a specific discovery node.
 *
 *  @param[out] callbackArg - The pointer passed when setting the callback.
 *
 *  @remarks Your application must handle the possible error cases appropriately. @ref STCNodeLastError
 *
 */
typedef void (CALLBACK *STCDiscoveryNodeUpdateCallback)(PSTCDiscoveryNodeCredentialsUpdate
        discoveryNode_Update, PVOID callbackArg);

/**
 *    This function sets the callback that will be called when a discovery node is updated from the cloud.
 *
 *  @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 *  @param[in] callback - The callback to be associated with any/all Discovery Node updates.
 *
 *  @param[in] callbackArg (OPTIONAL) - Verifying argument to be sent back with callback.
 *
 *  @return STCSetDiscoveryNodeUpdateCallback returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
 *  <dt>STC_ERROR_COMPLETE_CALLBACK_NOT_SET | E_FAIL
 *  <dd>Invalid pointer to callback.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCSetDiscoveryNodeUpdateCallback(STC_HANDLE sdkHandle,
        STCDiscoveryNodeUpdateCallback callback, PVOID callbackArg);


/**
 * @brief This function joins the current session to the Discovery Node specified by the discoveryNodeCredentials parameter.
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[in] discoveryNodeCredentials - A populated @ref _STCDISCOVERYNODECREDENTIALS struct to choose the proper node to join (data(Node Name) & nodeFlags are the arguments need to be updated in the struct).
 *
 * @param[out] SubscriptionResult - A result of type @ref STCSubscriptionResult handed down from the stack regarding the cloud connections.
 *
 * @remark You may only have one subscription to a specific Discovery Node.
 *
 *  @return STCJoinDiscoveryNode returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle, discoveryNodeCredentials, or SubscriptionResult is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCJoinDiscoveryNode(STC_HANDLE sdkHandle,
                                        STCDiscoveryNodeCredentials *discoveryNodeCredentials, PDWORD SubscriptionResult);

/**
 * @brief This function creates a Discovery Node specified by the discoveryNodeCredentials parameter.
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[in] discoveryNodeCredentials - A populated @ref _STCDISCOVERYNODECREDENTIALS struct to choose the proper node to create/join (data(Nodename) & nodeFlags are the arguments need to be updated in the struct).
 *
 * @param[out] SubscriptionResult - A result of type @ref STCSubscriptionResult handed down from the stack regarding the cloud connections.
 *
 * @remark You may only have one subscription to a specific Discovery Node.
 *
 *  @return STCCreateDiscoveryNode returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle, discoveryNodeCredentials, or SubscriptionResult is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 * @code
    STC_RESULT STC_RESULT = STC_SUCCESS;
    discveroyNodeCredentials structName = {0};         //Initialize struct to 0.
    DWORD subscriptionResult = 0;
    structName.data = NodeA ;
    structName.nodeFlags = STC_NODE_TYPE_PUBLISH;
    STC_RESULT = STCCreateDiscoveryNode(&structName, &subscriptionResult);
    if(STC_RESULT == STC_SUCCESS)
    {
         If(subscriptionResult == STC_SUBSCRIPTIONRESULT_SUBSCRIPTIONCHANGED)
         {
            //Request send to the Discovery Node server to create your discovery Node
         }
    }
 * @endcode
 *
 */
STC_API STC_RESULT STCCreateDiscoveryNode(STC_HANDLE sdkHandle,
        STCDiscoveryNodeCredentials *discoveryNodeCredentials, PDWORD SubscriptionResult);

/**
 * @brief This function unjoins the current session from the Discovery Node specified by the discoveryNodeCredentials parameter.
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[in] discoveryNodeCredentials - A populated @ref _STCDISCOVERYNODECREDENTIALS struct to choose the proper node to leave (data(Node Name) & nodeFlags are the arguments need to be updated in the struct)
 *
 * @param[out] SubscriptionResult - A result of type @ref STCSubscriptionResult handed down from the stack regarding the cloud connections.
 *
 *  @return STCLeaveDiscoveryNode returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *  <dd>One of the parameters passed is invalid (i.e.sdkHandle, discoveryNodeCredentials, or SubscriptionResult is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCLeaveDiscoveryNode(STC_HANDLE sdkHandle,
        STCDiscoveryNodeCredentials *discoveryNodeCredentials, PDWORD SubscriptionResult);

#ifndef ANDROID
/**
 * @brief This function indicates which transports are enabled on this device.
 *
 * @param[in] STC_HANDLE - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[out] DWORD - Bit values indicating which transports are enabled.
 *                            Possible values are: STC_TRANSPORT_NONE       (0x00)
 *                                                 STC_TRANSPORT_BLUETOOTH  (0x01)
 *                                                 STC_TRANSPORT_ALL        (0xFFFFFFFF)
 *  @return STCActiveDiscoveryIsEnabled returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  This API indicates which transports, in any, are enabled.
 *  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 * @code
    STC_RESULT                      stcResult;
    STCTransport                    transport;

    STC_RESULT = STCActiveDiscoveryIsEnabled(&sdkHandle, &transport);
 * @endcode
 *
 */
STC_API STC_RESULT STCActiveDiscoveryIsEnabled(STC_HANDLE sdkHandle, DWORD *pTransport);

/**
 * @brief This function indicates the transports on which we are visible to others.
 *
 * @param[in] STC_HANDLE - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[out] DWORD - Bit values indicating the transports on which we are visible to others.
 *                            Possible values are: STC_TRANSPORT_NONE       (0x00)
 *                                                 STC_TRANSPORT_BLUETOOTH  (0x01)
 *                                                 STC_TRANSPORT_ALL        (0xFFFFFFFF)
 *  @return STCActiveDiscoveryIsVisible returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  This API indicating the transports on which we are visible to others.
 *  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 * @code
    STC_RESULT                      stcResult;
    STCTransport                    transport;

    STC_RESULT = STCActiveDiscoveryIsVisible(&sdkHandle, *pTransport);
 * @endcode
 *
 */
STC_API STC_RESULT STCActiveDiscoveryIsVisible(STC_HANDLE sdkHandle, DWORD *pTransport);

/**
 * @brief This function enables visiblity on the transports that are functionally enabled.
 *
 * @param[in] STC_HANDLE - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[out] STCTransport - Enum bit values indicating the transports where we will be visible to others.
 *                            Possible values are: STC_TRANSPORT_NONE       (0x00)
 *                                                 STC_TRANSPORT_BLUETOOTH  (0x01)
 *                                                 STC_TRANSPORT_ALL        (0xFFFFFFFF)
 *  @return STCActiveDiscoveryEnableVisibility returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  This API indicates which transports, in any, will allow you to be visible
 *  to others. The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>E_FAIL
 *  <dd>The requested transport failed to make this device become visible.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 * @code
    STC_RESULT                      stcResult;
    STCTransport                    transport;

    STC_RESULT = STCActiveDiscoveryEnableVisibility(&sdkHandle, *pTransport);
 * @endcode
 *
 */
STC_API STC_RESULT STCActiveDiscoveryEnableVisibility(STC_HANDLE sdkHandle, DWORD transport);

/**
 * @brief This function initiates a BlueTooth discovery.
 *
 * @param[in] STC_HANDLE - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[in] long - A value indicating how long a scan will run.
 *
 *  @return STCActiveDiscoveryTriggerDiscovery returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed. This API starts a BlueTooth discovery only. The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid.
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  <dt>E_FAIL
 *  <dd>The transport failed to start a discovery process.
 *  </dl>
 * @code
    STC_RESULT                      stcResult;
    STC_HANDLE                      sdkHandle = NULL;         //Initialize.

    STC_RESULT = STCActiveDiscoveryTriggerDiscovery(&sdkHandle, timeout);
 * @endcode
 *
 */
STC_API STC_RESULT STCActiveDiscoveryTriggerDiscovery(STC_HANDLE sdkHandle, long timeout);
#endif // ANDROID

/**
 * @brief This function gets the status of the Discovery Node Service.
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 *
 * @param[out] status - The Discovery Node Service Status
 *
 *  @return STCQueryDiscoveryNodeServiceStatus returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e., sdkHandle or status is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCQueryDiscoveryNodeServiceStatus(STC_HANDLE sdkHandle, PDWORD status);

///@}



/**
  *******************************************************************************************
  *  @defgroup Logging Logging APIs
  *
  *  @brief This API allows starting, stopping the Debug Agent and writing log
  *
  *******************************************************************************************
  */
///@{
#if defined(UNICODE) && !defined(STC_NO_UNICODE)
#define STCStartAgent   STCStartAgentW
#define STCWriteLog     STCWriteLogW

#define STCSendSignalData STCSendSignalDataW
#else
#define STCStartAgent   STCStartAgentA
#define STCWriteLog     STCWriteLogA

#define STCSendSignalData STCSendSignalDataA
#endif
/**
 *      This function starts the Debug Agent and specifies a log file to write to.
 *
 * @remarks   The following parameters can be used as default values if you don't require extra functionality:
 *                pFileName = NULL, module = Module_AllModules, logLevel = LogLevel_Info, enableDataLogging = false
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 * @param[in] appGuid - The GUID of the application calling this function.
 * @param[in] pAppName - A pointer to the wchar_t array with the name of the application calling this function.
 * @param[in] loggingMode - A list of flags that determine the logging modes to be used: (defined above)
 *                          Offline logging only = 1
 *                          Online logging only = 2
 *                          Both offline and online logging = 3
 * @param[in] pFileName - A pointer to the wchar_t array of the offline logging file name. If pFileName == NULL, a default name is used.
 *                             This parameter must only contain a file name and must not include a path. All logs are save to user's "temp" directory
 * @param[in] module - The modules that will act as a filter for logging messages. Consists of several tags as a bitmask.
 * @param[in] logLevel - The lowest(inclusive) log level, per tag, to include in the file.
 * @param[in] enableDataLogging - A flag, enabling/disabling data logging.
 *
 *  @return STCStartAgentW returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle, pAppName, or pFileName is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */

STC_API STC_RESULT STCStartAgentW(STC_HANDLE sdkHandle, GUID appGuid, wchar_t *pAppName,
                                  LogMode loggingMode, wchar_t *pFileName, Module module, LogLevel logLevel, bool enableDataLogging);

/**
 *      This function starts the Debug Agent and specifies a log file to write to.
 *
 * @remarks   The following parameters can be used as default values if you don't require extra functionality:
 *                pFileName = NULL, module = Module_AllModules, logLevel = LogLevel_Info, enableDataLogging = false
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 * @param[in] appGuid - The GUID of the application calling this function.
 * @param[in] szAppName - A pointer to the char array with the name of the application calling this function.
 * @param[in] loggingMode - A list of flags that determine the logging modes to be used: (defined above)
 *                          Offline logging only = 1
 *                          Online logging only = 2
 *                          Both offline and online logging = 3
 * @param[in] szFileName - A pointer to the char array of the offline logging file name. If szFileName == NULL, a default name is used.
 *                             This parameter must only contain a file name and must not include a path. All logs are save to user's "temp" directory
 * @param[in] module - The modules that will act as a filter for logging messages. Consists of several tags as a bitmask.
 * @param[in] logLevel - The lowest(inclusive) log level, per tag, to include in the file.
 * @param[in] enableDataLogging - A flag, enabling/disabling data logging.
 *
 *  @return STCStartAgent returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle, pAppName, or pFileName is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */

STC_API STC_RESULT STCStartAgentA(STC_HANDLE sdkHandle, GUID appGuid, char *szAppName,
                                  LogMode loggingMode, char *szFileName, Module module, LogLevel logLevel, bool enableDataLogging);

/**
*      This function stops the Debug Agent.
*
* @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
* @param[in] appGuid - The GUID of the application calling this function.
*
*  @return STCStopAgent returns @ref STC_SUCCESS upon success or a code indicating
*  why it failed.  The return code may be a STC Result Code
*  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
*  Common error STC_RESULT%s include:
*  <dl>
*  <dt>E_INVALIDARG
*   <dd>One of the parameters passed is invalid (i.e.sdkHandle is an invalid pointer.)
*  <dt>STC_ERROR_NOT_INITIALIZED
*  <dd>The application has not been initialized against the Intel CCF service.
*  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
*  <dd>The application needs to re-initialize with the Intel CCF service.
*  </dl>
*
*/
STC_API STC_RESULT STCStopAgent(STC_HANDLE sdkHandle, GUID appGuid);

/**
 *      This function writes a log entry.
 *
 * @remarks   The following parameters can be used as default values if you don't require extra functionality:
 *                pMessage = NULL, sizeInBytes = 0, pData = NULL
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 * @param[in] appGuid - The GUID of the application calling this function.
 * @param[in] module - The tag (source module) of this entry.
 * @param[in] logLevel - The log level of this entry.
 * @param[in] pMessage - Text message of the log entry (NULL Terminated).
 * @param[in] sizeInBytes - The size (in bytes) of the data (optional) that may be associated with this message. May Be Zero.
 * @param[in] pData - A pointer to binary data. May Be NULL.
 *
 *  @return STCWriteLogW returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle, pMessage, or pData is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCWriteLogW(STC_HANDLE sdkHandle, GUID appGuid, Module module,
                                LogLevel logLevel, wchar_t *pMessage, int sizeInBytes, char *pData);

/**
 *      This function writes a log entry.
 *
 * @remarks   The following parameters can be used as default values if you don't require extra functionality:
 *                pMessage = NULL, sizeInBytes = 0, pData = NULL
 *
 * @param[in] sdkHandle - The handle to the instance of the Intel CCF SDK to use for this API.
 * @param[in] appGuid - The GUID of the application calling this function.
 * @param[in] module - The tag (source module) of this entry.
 * @param[in] logLevel - The log level of this entry.
 * @param[in] szMessage - Text message of the log entry (NULL Terminated).
 * @param[in] sizeInBytes - The size (in bytes) of the data (optional) that may be associated with this message. May Be Zero.
 * @param[in] pData - A pointer to binary data. May Be NULL.
 *
 *  @return STCWriteLog returns @ref STC_SUCCESS upon success or a code indicating
 *  why it failed.  The return code may be a STC Result Code
 *  or a Windows [STC_RESULT](http://msdn.microsoft.com/en-us/library/cc704587.aspx).
 *  Common error STC_RESULT%s include:
 *  <dl>
 *  <dt>E_INVALIDARG
 *   <dd>One of the parameters passed is invalid (i.e.sdkHandle, pMessage, or pData is an invalid pointer.)
 *  <dt>STC_ERROR_NOT_INITIALIZED
 *  <dd>The application has not been initialized against the Intel CCF service.
 *  <dt>STC_RESULT Error Code: 0x800706BA "The RPC Server is unavailable"
 *  <dd>The application needs to re-initialize with the Intel CCF service.
 *  </dl>
 *
 */
STC_API STC_RESULT STCWriteLogA(STC_HANDLE sdkHandle, GUID appGuid, Module module,
                                LogLevel logLevel, char *szMessage, int sizeInBytes, char *pData);
///@}

/**
*  INTEL(R) CONFIDENTIAL
*/

///@}


#ifdef __cplusplus
}
#endif

#endif
