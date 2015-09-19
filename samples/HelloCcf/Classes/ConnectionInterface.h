//
//  ConnectionInterface.h
//  HelloCcf
//
//  Implement interface of Intel® Common Connectivity Framework
//  eg. PeerUpdate Invite ReceiveInvite SendMessage ReceiveMessage Disconnect
//
//  Created by calf on 14-7-24.
//
//

#ifndef __HelloCcf__ConnectionInterface__
#define __HelloCcf__ConnectionInterface__

#include <iostream>
#include <list>
#include <iterator>

typedef struct tagPEER{
    std::string _sessionName;
    std::string _sessionId;
    bool _availability;
    bool _availability_cloud;
    bool _availability_proximity;
    bool add;
};

class ConnectionInterface {
public:

    static void InvitePeer(tagPEER peer);
    
    static void SendInviteResponse(bool value);

    static void SendMessage(std::string msg);

    static void Disconnect();

    static void OnPeerUpdate(tagPEER peer);

    static void OnReciveInvite(std::string sessionId);
    
    static void OnReceiveMessage(std::string message);
    
    static void OnAcknowledgment();
    
    static void OnDisconnect();

    static void getPeerList(std::list<tagPEER> &listPeer);

    static void getMessageList(std::list<std::string> &listMessage);
    
protected:
    static std::list<tagPEER>::iterator queryPeer(tagPEER &peer);

    static std::mutex _mutex;

    static std::mutex _mutexMessage;
    
    static std::list<tagPEER> _listPeer;

    static std::list<std::string> _listMessage;
    
    static bool _bConnect;
};

#endif /* defined(__HelloCcf__ConnectionInterface__) */
