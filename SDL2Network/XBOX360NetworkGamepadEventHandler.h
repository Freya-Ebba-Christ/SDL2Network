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

#ifndef XBOX360NETWORKGAMEPADEVENTHANDLER_H
#define	XBOX360NETWORKGAMEPADEVENTHANDLER_H

#include <iostream>
#include <vector>
#include <XBOX360DataPacket.h>
#include <SDL2Image.h>

using namespace std;

class XBOX360NetworkGamepadEventHandler {
public:

    XBOX360NetworkGamepadEventHandler() {

    }

    virtual int getGamepadID() {
        return this->gamepadID;
    }

    virtual void setGamepadID(int value) {
        this->gamepadID = value;
    }

    virtual void on_A_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_A" << endl;
    }

    virtual void on_B_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_B" << endl;
    }

    virtual void on_X_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_X" << endl;
    }

    virtual void on_Y_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_Y" << endl;
    }

    virtual void on_START_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_START" << endl;
    }

    virtual void on_BACK_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_BACK" << endl;
    }

    virtual void on_DPAD_DOWN_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_DPAD_DOWN" << endl;
    }

    virtual void on_DPAD_UP_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_DPAD_UP" << endl;
    }

    virtual void on_DPAD_LEFT_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_DPAD_LEFT" << endl;
    }

    virtual void on_DPAD_RIGHT_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_DPAD_RIGHT" << endl;
    }

    virtual void on_LEFTSHOULDER_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_LEFTSHOULDER" << endl;
    }

    virtual void on_RIGHTSHOULDER_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_RIGHTSHOULDER" << endl;
    }

    virtual void on_LEFTSTICK_Down(XBOX360DataPacket& dataPacket) {

        //cout << "SDL_CONTROLLER_BUTTON_LEFTSTICK" << endl;
    }

    virtual void on_RIGHTSTICK_Down(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_RIGHTSTICK" << endl;
    }

    virtual void on_A_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_A" << endl;
    }

    virtual void on_B_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_B" << endl;
    }

    virtual void on_X_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_X" << endl;
    }

    virtual void on_Y_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_Y" << endl;
    }

    virtual void on_START_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_START" << endl;
    }

    virtual void on_BACK_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_BACK" << endl;
    }

    virtual void on_DPAD_DOWN_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_DPAD_DOWN" << endl;
    }

    virtual void on_DPAD_UP_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_DPAD_UP" << endl;
    }

    virtual void on_DPAD_LEFT_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_DPAD_LEFT" << endl;
    }

    virtual void on_DPAD_RIGHT_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_DPAD_RIGHT" << endl;
    }

    virtual void on_LEFTSHOULDER_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_LEFTSHOULDER" << endl;
    }

    virtual void on_RIGHTSHOULDER_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_RIGHTSHOULDER" << endl;
    }

    virtual void on_LEFTSTICK_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_LEFTSTICK" << endl;
    }

    virtual void on_RIGHTSTICK_Up(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_BUTTON_RIGHTSTICK" << endl;
    }

    virtual void on_AXIS_LEFTX(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_AXIS_LEFTX" << endl;
    }

    virtual void on_AXIS_RIGHTX(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_AXIS_RIGHTX" << endl;
    }

    virtual void on_AXIS_LEFTY(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_AXIS_LEFTY" << endl;
    }

    virtual void on_AXIS_RIGHTY(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_AXIS_RIGHTY" << endl;
    }

    virtual void on_AXIS_TRIGGERLEFT(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_AXIS_TRIGGERLEFT" << endl;
    }

    virtual void on_AXIS_TRIGGERRIGHT(XBOX360DataPacket& dataPacket) {
        //cout << "SDL_CONTROLLER_AXIS_TRIGGERRIGHT" << endl;
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

    virtual ~XBOX360NetworkGamepadEventHandler() {

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

#endif	/* XBOX360NETWORKGAMEPADEVENTHANDLER_H */