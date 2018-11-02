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

#ifndef XBOX360NETWORKGAMEPAD_H
#define	XBOX360NETWORKGAMEPAD_H

#include <iostream>
#include <vector>
#include <string>
#include <XBOX360NetworkGamepadEventHandler.h>
#include "XBOX360DataPacket.h"

using namespace std;

template <typename T> class XBOX360NetworkGamepad {
public:

    XBOX360NetworkGamepad() {
    }

    void addEventHandler(T* value) {
        eventHandler.push_back(value);
    }

    T* removeEventHandler(T* value) {
        for (int i = 0; i < eventHandler.size(); i++) {
            if (eventHandler[i] == value) {
                eventHandler.erase(eventHandler.begin() + i);
            }
        }
    }

    void processEvent(XBOX360DataPacket& dataPacket) {
        //int numberOfEvents = dataPacket.getNumberOfEvents();
        uint64_t eventmask = dataPacket.getEventMask();

        if (eventmask & dataPacket.A_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_A_Down(dataPacket);
            }
        }

        if (eventmask & dataPacket.B_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_B_Down(dataPacket);
            }
        }

        if (eventmask & dataPacket.X_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_X_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.Y_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_Y_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.START_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_START_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.BACK_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_BACK_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.DPAD_DOWN_DOWN_EVENT) {
            //cout << "dataPacket.DPAD_DOWN_DOWN_EVENT" << endl;
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_DPAD_DOWN_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.DPAD_UP_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_DPAD_UP_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.DPAD_LEFT_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_DPAD_LEFT_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.DPAD_RIGHT_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_DPAD_RIGHT_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.LEFTSHOULDER_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_LEFTSHOULDER_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.RIGHTSHOULDER_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_RIGHTSHOULDER_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.LEFTSTICK_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_LEFTSTICK_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.RIGHTSTICK_DOWN_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_RIGHTSTICK_Down(dataPacket);
            }
        }
        if (eventmask & dataPacket.A_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_A_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.X_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_X_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.Y_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_Y_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.START_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_START_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.BACK_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_BACK_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.DPAD_DOWN_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_DPAD_DOWN_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.DPAD_UP_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_DPAD_UP_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.DPAD_LEFT_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_DPAD_LEFT_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.DPAD_RIGHT_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_DPAD_RIGHT_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.LEFTSHOULDER_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_LEFTSHOULDER_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.RIGHTSHOULDER_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_RIGHTSHOULDER_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.LEFTSTICK_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_LEFTSTICK_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.RIGHTSTICK_UP_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_RIGHTSTICK_Up(dataPacket);
            }
        }
        if (eventmask & dataPacket.AXIS_LEFTX_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_AXIS_LEFTX(dataPacket);
            }
        }
        if (eventmask & dataPacket.AXIS_RIGHTX_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_AXIS_RIGHTX(dataPacket);
            }
        }
        if (eventmask & dataPacket.AXIS_LEFTY_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_AXIS_LEFTY(dataPacket);
            }
        }
        if (eventmask & dataPacket.AXIS_RIGHTY_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_AXIS_RIGHTY(dataPacket);
            }
        }
        if (eventmask & dataPacket.AXIS_TRIGGERLEFT_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_AXIS_TRIGGERLEFT(dataPacket);
            }
        }
        if (eventmask & dataPacket.AXIS_TRIGGERRIGHT_EVENT) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->on_AXIS_TRIGGERRIGHT(dataPacket);
            }
        };
        dataPacket.clearEventMask();
    }

    virtual ~XBOX360NetworkGamepad() {

    }

private:
    vector<T*> eventHandler;
};

#endif	/* XBOX360NETWORKGAMEPAD_H */

