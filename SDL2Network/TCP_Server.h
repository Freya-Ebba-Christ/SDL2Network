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

#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#define DEFAULT_MAX_MESSAGE_SIZE 8192
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_net.h>
#include <iostream>

#include "DataPacket.h"
using namespace std;

class TCP_Server {
public:

    TCP_Server() {
    }

    TCP_Server(int port) : port(port) {
    }

    void setPort(int port) {
        this->port = port;
    }

    void start() {
        if (SDLNet_Init() < 0) {
            fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }

        cout << "Resolving the host using NULL make network interface to listen" << endl;
        /* Resolving the host using NULL make network interface to listen */
        if (SDLNet_ResolveHost(&ip, NULL, port) < 0) {
            fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }

        cout << "Open a connection with the IP provided (listen on the host's port)" << endl;
        /* Open a connection with the IP provided (listen on the host's port) */
        if (!(sd = SDLNet_TCP_Open(&ip))) {
            fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }
    }

    bool connect() {
        if ((csd = SDLNet_TCP_Accept(sd))) {
            /* Now we can communicate with the client using csd socket
             * sd will remain opened waiting other connections */

            /* Get the remote address */
            if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd))) {
                /* Print the address, converting in the host format */
                printf("Host connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
                connected = true;
                return true;
            } else {
                fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
                return false;
            }
        }
    }

    bool disconnect() {
        connected = false;
        SDLNet_TCP_Close(sd);
    }

    void stop() {
        SDLNet_Quit();
    }

    void sendDataPacket(DataPacket& dataPacket) {
        if (connected) {
            packetArray.resize(dataPacket.size(), 0);
            dataPacket.getDataPacketData(packetArray);
            if (SDLNet_TCP_Send(csd, (void *) packetArray.data(), dataPacket.size()) < dataPacket.size()) {
                fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
                exit(EXIT_FAILURE);
            }
        }
    }

    void getDataPacket(DataPacket& dataPacket) {
        if (connected) {
            packetArray.resize(dataPacket.size(), 0);
            int len = SDLNet_TCP_Recv(csd, packetArray.data(), dataPacket.size());
            if (len > 0) {
                dataPacket.setDataPacketData(packetArray);
            }
        }
    }

    void sendACK() {
        if (connected) {

        }
    }

    TCPsocket sd, csd; /* Socket descriptor, Client socket descriptor */

private:
    vector<uint8_t> packetArray;
    vector<uint8_t> ackPacket;
    IPaddress ip, *remoteIP;
    int quit, quit2;
    int port;
    bool connected;
};

#endif /* TCP_SERVER_H */

