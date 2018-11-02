/* 
 *    Copyright [2015] Olaf - blinky0815 - christ ]
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 * 
 * Author: blinky0815
 * email: christ_o@gmx.de
 */

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_net.h>
#include <iostream>
#include <DataPacket.h>
using namespace std;

class TCP_Client {
public:

    TCP_Client() {
    }

    TCP_Client(const char* host, int port) : host(host), port(port) {

    }

    void setHost(const char* host) {
        this->host = host;
    }

    void setPort(int port) {
        this->port = port;
    }

    virtual ~TCP_Client() {
    }

    const char* getHost() {
        return this->host;
    }

    int getPort() {
        return this->port;
    }

    void start() {

        if (SDLNet_Init() < 0) {
            fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }

        /* Resolve the host we are connecting to */
        if (SDLNet_ResolveHost(&ip, host, port) < 0) {
            fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }
    }

    bool connect() {
        /* Open a connection with the IP provided (listen on the host's port) */
        if (!(sd = SDLNet_TCP_Open(&ip))) {
            fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
            //exit(EXIT_FAILURE);
            return false;
        }
        connected = true;
        return true;
    }

    void getDataPacket(DataPacket& dataPacket) {
        if (connected) {
            packetArray.resize(dataPacket.size(), 0);
            int len = SDLNet_TCP_Recv(sd, packetArray.data(), dataPacket.size());
            if (len > 0) {
                dataPacket.setDataPacketData(packetArray);
            }
        }
    }

    void sendDataPacket(DataPacket& dataPacket) {
        if (connected) {
            packetArray.resize(dataPacket.size(), 0);
            dataPacket.getDataPacketData(packetArray);
            if (SDLNet_TCP_Send(sd, (void *) packetArray.data(), dataPacket.size()) < dataPacket.size()) {
                fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
                exit(EXIT_FAILURE);
            }
        }
    }

    void readACK() {
        if (connected) {

        }
    }

    void disconnect() {
        connected = false;
        SDLNet_TCP_Close(sd);
    }

    void stop() {
        SDLNet_Quit();
    }

private:
    IPaddress ip; /* Server address */
    TCPsocket sd; /* Socket descriptor */
    const char* host;
    int port;
    vector<uint8_t> packetArray;
    bool connected;
};

#endif /* TCP_CLIENT_H */

