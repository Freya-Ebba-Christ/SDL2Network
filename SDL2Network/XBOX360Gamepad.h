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

#ifndef XBOX360GAMEPAD_H
#define	XBOX360GAMEPAD_H

#include <iostream>
#include <vector>
#include <string>
#include <XBOX360GamepadEventHandler.h>

template <typename T> class XBOX360Gamepad {
public:

    XBOX360Gamepad() {

    }

    XBOX360Gamepad(const XBOX360Gamepad& orig) {
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

    void processEvent(SDL_Event* event, SDL_GameController* gamecontroller) {
        switch (event->type) {

            case SDL_CONTROLLERDEVICEADDED:
            {
                std::cout << "SDL_CONTROLLERDEVICEADDED" << std::endl;
            }
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
            {
                std::cout << "SDL_CONTROLLERDEVICEREMOVED" << std::endl;
            }
                break;
            case SDL_CONTROLLERBUTTONDOWN:
            {
                switch (event->cbutton.button) {
                    case SDL_CONTROLLER_BUTTON_A:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_A_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_B:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_B_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_X:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_X_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_Y:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_Y_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_START:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_START_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_BACK:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_BACK_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_DPAD_DOWN_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_DPAD_UP_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_DPAD_LEFT_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_DPAD_RIGHT_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_LEFTSHOULDER_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_RIGHTSHOULDER_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_LEFTSTICK:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_LEFTSTICK_Down(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_RIGHTSTICK_Down(gamecontroller);
                        }
                        break;
                }
                break;
            }
                break;

            case SDL_CONTROLLERBUTTONUP:
            {
                switch (event->cbutton.button) {
                    case SDL_CONTROLLER_BUTTON_A:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_A_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_B:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_B_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_X:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_X_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_Y:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_Y_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_START:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_START_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_BACK:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_BACK_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_DPAD_DOWN_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_DPAD_UP_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_DPAD_LEFT_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_DPAD_RIGHT_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_LEFTSHOULDER_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_RIGHTSHOULDER_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_LEFTSTICK:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_LEFTSTICK_Up(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_RIGHTSTICK_Up(gamecontroller);
                        }
                        break;
                }
                break;
            }
                break;

            case SDL_CONTROLLERAXISMOTION:
            {
                //cout << "SDL_CONTROLLERAXISMOTION" << endl;
                switch (event->cbutton.button) {
                    case SDL_CONTROLLER_AXIS_LEFTX:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_AXIS_LEFTX(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_AXIS_RIGHTX:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_AXIS_RIGHTX(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_AXIS_LEFTY:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_AXIS_LEFTY(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_AXIS_RIGHTY:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_AXIS_RIGHTY(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_AXIS_TRIGGERLEFT(gamecontroller);
                        }
                        break;
                    case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                        for (int i = 0; i < eventHandler.size(); i++) {
                            eventHandler[i]->on_AXIS_TRIGGERRIGHT(gamecontroller);
                        }
                        break;
                }
                break;
            }
                break;
        }
    }

    virtual ~XBOX360Gamepad() {
    }

private:
    std::vector<T*> eventHandler;
};

#endif	/* XBOX360GAMEPAD_H */

