#ifndef CHANNEL
#define CHANNEL

class Client;
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <vector>
#include <sys/fcntl.h>
#include <cstring>
#include <csignal>
#include "client.hpp"

class Channel;
void removeChannel(std::vector<Channel*> &channels, std::string channelName);

class Channel
{
private:
    std::string name;
    bool inviteOnly;
    bool flagT;
    std::string pass;
    std::string topic;
    std::string operatorNick;
    int maxClients;
    int clients;

public:
    std::string getName() {return name; }
    void setName(std::string name) { this->name = name; }
    Channel(std::string name) : name(name)
    {
        inviteOnly = false;
        maxClients = -1;
        clients = 1;
        topic.clear();
        pass.clear();
        flagT = false;
    }
    bool getT() { return flagT; }
    void setT(bool a) { flagT = a; }
    void setOperatorNick(std::string nick) { operatorNick = nick; }
    std::string getPass() { return pass; }
    void setPass(std::string pass) { this->pass = pass; }
    void removePass() {pass.clear(); }
    std::string getOperatorNick() { return operatorNick; }
    bool getInviteOnly() { return inviteOnly; }
    void setInviteOnly(bool a) { inviteOnly = a; }
    int getMaxClients() { return maxClients; }
    void setMaxClients(int q) { maxClients = q; }
    int getClients() { return clients; }
    void addClient() { clients++; }
    void removeClient(std::vector<Channel*> &channels)
    {
        clients--;
        if (clients < 1)
            removeChannel(channels, name);        
    }
    std::string getTopic() { return topic; }
    void setTopic(std::string newTopic)
    {
        topic.clear();
        topic = newTopic;
    }
    void removeTopic() { topic.clear(); }
    void sendToEverybody(std::string stringToSend, std::vector<Client*> clients);

};

#endif