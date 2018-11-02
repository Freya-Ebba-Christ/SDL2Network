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

#ifndef XBOX360GAMEPADEVENTHANDLER_H
#define	XBOX360GAMEPADEVENTHANDLER_H
#include <iostream>
#include <vector>
#include <SDL2Image.h>

class XBOX360GamepadEventHandler {
public:

    XBOX360GamepadEventHandler() {
    }

    XBOX360GamepadEventHandler(const XBOX360GamepadEventHandler& orig) {
    }

    virtual ~XBOX360GamepadEventHandler() {
    }

    virtual int getGamepadID() {
        return this->gamepadID;
    }

    virtual void setGamepadID(int value) {
        this->gamepadID = value;
    }

    virtual void on_A_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_A" << std::endl;
    }

    virtual void on_B_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_B" << std::endl;
    }

    virtual void on_X_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_X" << std::endl;
    }

    virtual void on_Y_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_Y" << std::endl;
    }

    virtual void on_START_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_START" << std::endl;
    }

    virtual void on_BACK_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_BACK" << std::endl;
    }

    virtual void on_DPAD_DOWN_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_DPAD_DOWN" << std::endl;
    }

    virtual void on_DPAD_UP_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_DPAD_UP" << std::endl;
    }

    virtual void on_DPAD_LEFT_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_DPAD_LEFT" << std::endl;
    }

    virtual void on_DPAD_RIGHT_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_DPAD_RIGHT" << std::endl;
    }

    virtual void on_LEFTSHOULDER_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_LEFTSHOULDER" << std::endl;
    }

    virtual void on_RIGHTSHOULDER_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_RIGHTSHOULDER" << std::endl;
    }

    virtual void on_LEFTSTICK_Down(SDL_GameController* gamecontroller) {

        std::cout << "SDL_CONTROLLER_BUTTON_LEFTSTICK" << std::endl;
    }

    virtual void on_RIGHTSTICK_Down(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_RIGHTSTICK" << std::endl;
    }

    virtual void on_A_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_A" << std::endl;
    }

    virtual void on_B_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_B" << std::endl;
    }

    virtual void on_X_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_X" << std::endl;
    }

    virtual void on_Y_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_Y" << std::endl;
    }

    virtual void on_START_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_START" << std::endl;
    }

    virtual void on_BACK_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_BACK" << std::endl;
    }

    virtual void on_DPAD_DOWN_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_DPAD_DOWN" << std::endl;
    }

    virtual void on_DPAD_UP_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_DPAD_UP" << std::endl;
    }

    virtual void on_DPAD_LEFT_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_DPAD_LEFT" << std::endl;
    }

    virtual void on_DPAD_RIGHT_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_DPAD_RIGHT" << std::endl;
    }

    virtual void on_LEFTSHOULDER_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_LEFTSHOULDER" << std::endl;
    }

    virtual void on_RIGHTSHOULDER_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_RIGHTSHOULDER" << std::endl;
    }

    virtual void on_LEFTSTICK_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_LEFTSTICK" << std::endl;
    }

    virtual void on_RIGHTSTICK_Up(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_BUTTON_RIGHTSTICK" << std::endl;
    }

    virtual void on_AXIS_LEFTX(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_AXIS_LEFTX" << std::endl;
    }

    virtual void on_AXIS_RIGHTX(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_AXIS_RIGHTX" << std::endl;
    }

    virtual void on_AXIS_LEFTY(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_AXIS_LEFTY" << std::endl;
    }

    virtual void on_AXIS_RIGHTY(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_AXIS_RIGHTY" << std::endl;
    }

    virtual void on_AXIS_TRIGGERLEFT(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_AXIS_TRIGGERLEFT" << std::endl;
    }

    virtual void on_AXIS_TRIGGERRIGHT(SDL_GameController* gamecontroller) {
        std::cout << "SDL_CONTROLLER_AXIS_TRIGGERRIGHT" << std::endl;
    }

    virtual void setLeftStickDeadZoneX(int value) {
        this->leftStickDeadZoneX = value;
    }

    int getLeftStickDeadZoneX() {
        return this->leftStickDeadZoneX;
    }

    virtual void setLeftStickDeadZoneY(int value) {
        this->leftStickDeadZoneY = value;
    }

    virtual int getLeftStickDeadZoneY() {
        return this->leftStickDeadZoneY;
    }

    virtual void setRightStickDeadZoneX(int value) {
        this->rightStickDeadZoneX = value;
    }

    virtual int getRightStickDeadZoneX() {
        return this->rightStickDeadZoneX;
    }

    virtual void setRightStickDeadZoneY(int value) {
        this->rightStickDeadZoneY = value;
    }

    virtual int getRightStickDeadZoneY() {
        return this->rightStickDeadZoneY;
    }

    virtual void setLeftTriggerDeadZone(int value) {
        this->leftTriggerDeadZone = value;
    }

    virtual int getLeftTriggerDeadZone() {
        return this->leftTriggerDeadZone;
    }

    virtual void setRightTriggerDeadZone(int value) {
        this->rightTriggerDeadZone = value;
    }

    virtual int setRightTriggerDeadZone() {
        return this->rightTriggerDeadZone;
    }

private:
    int gamepadID = 0;
    int leftStickDeadZoneX = 0;
    int leftStickDeadZoneY = 0;

    int rightStickDeadZoneX = 0;
    int rightStickDeadZoneY = 0;

    int leftTriggerDeadZone = 0;
    int rightTriggerDeadZone = 0;
};

#endif	/* XBOX360GAMEPADEVENTHANDLER_H */