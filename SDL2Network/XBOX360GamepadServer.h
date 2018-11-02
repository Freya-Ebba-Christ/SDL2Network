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

#ifndef XBOX360GAMEPADSERVER_H
#define	XBOX360GAMEPADSERVER_H
#include <TCP_Server.h>
#include <iostream>
#include <threadworker.h>
#include <thread.h>
#include <XBOX360NetworkGamepad.h>
#include <chrono>

using namespace std;

class XBOX360GamepadServer : public XBOX360NetworkGamepadEventHandler {
public:

    XBOX360GamepadServer(int port) {
        tcp_server.setPort(port);
    }

    virtual ~XBOX360GamepadServer() {
    }

    void start() {
        initDataPacket();
        tcp_server.start();
        while (tcp_server.connect() == false) {
        }

        gamepad.addEventHandler(this);
        this->running = true;

        while (this->running) {
            tcp_server.getDataPacket(aXBOX360DataPacket);
            aXBOX360DataPacket.copyBufferToValues();
            aXBOX360DataPacket.applyDeadZone();
            cout << "Type: " << aXBOX360DataPacket.getType() << endl;
            cout << "CurrentBlockIndex: " << aXBOX360DataPacket.getCurrentBlockIndex() << endl;
            cout << "FirstBlockIndex: " << aXBOX360DataPacket.getFirstBlockIndex() << endl;
            cout << "LastBlockIndex: " << aXBOX360DataPacket.getLastBlockIndex() << endl;
            cout << "SequenceNumber: " << aXBOX360DataPacket.getSequenceNumber() << endl;
            cout << "Timestamp: " << aXBOX360DataPacket.getTimestamp() << endl;
            cout << "NumBytes: " << aXBOX360DataPacket.getNumBytes() << endl;
            cout << "setOn_Y_Up " << aXBOX360DataPacket.getOn_Y_Up() << endl;
            cout << "getOn_A_Down " << aXBOX360DataPacket.getOn_A_Down() << endl;
            cout << "getOn_Y_Down " << aXBOX360DataPacket.getOn_Y_Down() << endl;
            cout << "getOn_AXIS_TRIGGERRIGHT " << aXBOX360DataPacket.getOn_AXIS_TRIGGERRIGHT() / 32767.0 << endl;
            cout << "getOn_AXIS_LEFTX " << aXBOX360DataPacket.getOn_AXIS_LEFTX() / 32767.0 << endl;
            cout << "getOn_AXIS_LEFTY() " << aXBOX360DataPacket.getOn_AXIS_LEFTY() / 32767.0 << endl;
        }
        tcp_server.disconnect();
        tcp_server.stop();
    }

private:

    bool running;
    TCP_Server tcp_server;
    XBOX360NetworkGamepad<XBOX360GamepadServer> gamepad;
    XBOX360DataPacket aXBOX360DataPacket;

    void initDataPacket() {
        aXBOX360DataPacket.clearEventMask();
        aXBOX360DataPacket.clear();
    }
};

#endif	/* XBOX360GAMEPADSERVER_H */

