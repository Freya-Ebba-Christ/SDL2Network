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

#ifndef XBOX360DATAPACKET_H
#define XBOX360DATAPACKET_H
#include <DataPacket.h>

class XBOX360DataPacket : public DataPacket {
public:

    uint64_t A_DOWN_EVENT;
    uint64_t B_DOWN_EVENT;
    uint64_t X_DOWN_EVENT;
    uint64_t Y_DOWN_EVENT;
    uint64_t START_DOWN_EVENT;
    uint64_t BACK_DOWN_EVENT;
    uint64_t DPAD_DOWN_DOWN_EVENT;
    uint64_t DPAD_UP_DOWN_EVENT;
    uint64_t DPAD_LEFT_DOWN_EVENT;
    uint64_t DPAD_RIGHT_DOWN_EVENT;
    uint64_t LEFTSHOULDER_DOWN_EVENT;
    uint64_t RIGHTSHOULDER_DOWN_EVENT;
    uint64_t LEFTSTICK_DOWN_EVENT;
    uint64_t RIGHTSTICK_DOWN_EVENT;
    uint64_t A_UP_EVENT;
    uint64_t B_UP_EVENT;
    uint64_t X_UP_EVENT;
    uint64_t Y_UP_EVENT;
    uint64_t START_UP_EVENT;
    uint64_t BACK_UP_EVENT;
    uint64_t DPAD_DOWN_UP_EVENT;
    uint64_t DPAD_UP_UP_EVENT;
    uint64_t DPAD_LEFT_UP_EVENT;
    uint64_t DPAD_RIGHT_UP_EVENT;
    uint64_t LEFTSHOULDER_UP_EVENT;
    uint64_t RIGHTSHOULDER_UP_EVENT;
    uint64_t LEFTSTICK_UP_EVENT;
    uint64_t RIGHTSTICK_UP_EVENT;
    uint64_t AXIS_LEFTX_EVENT;
    uint64_t AXIS_RIGHTX_EVENT;
    uint64_t AXIS_LEFTY_EVENT;
    uint64_t AXIS_RIGHTY_EVENT;
    uint64_t AXIS_TRIGGERLEFT_EVENT;
    uint64_t AXIS_TRIGGERRIGHT_EVENT;

    XBOX360DataPacket(int messageSize = 90) : DataPacket(messageSize) {
        //make sure this is an XBOX360 related packet
        setType(XBOX360);
        clearEventMask();
        A_DOWN_EVENT = 0x01;
        B_DOWN_EVENT = 0x02;
        X_DOWN_EVENT = 0x04;
        Y_DOWN_EVENT = 0x08;
        START_DOWN_EVENT = 0x10;
        BACK_DOWN_EVENT = 0x20;
        DPAD_DOWN_DOWN_EVENT = 0x40;
        DPAD_UP_DOWN_EVENT = 0x80;
        DPAD_LEFT_DOWN_EVENT = 0x100;
        DPAD_RIGHT_DOWN_EVENT = 0x200;
        LEFTSHOULDER_DOWN_EVENT = 0x400;
        RIGHTSHOULDER_DOWN_EVENT = 0x800;
        LEFTSTICK_DOWN_EVENT = 0x1000;
        RIGHTSTICK_DOWN_EVENT = 0x2000;
        A_UP_EVENT = 0x4000;
        B_UP_EVENT = 0x8000;
        X_UP_EVENT = 0x10000;
        Y_UP_EVENT = 0x20000;
        START_UP_EVENT = 0x40000;
        BACK_UP_EVENT = 0x80000;
        DPAD_DOWN_UP_EVENT = 0x100000;
        DPAD_UP_UP_EVENT = 0x200000;
        DPAD_LEFT_UP_EVENT = 0x400000;
        DPAD_RIGHT_UP_EVENT = 0x800000;
        LEFTSHOULDER_UP_EVENT = 0x1000000;
        RIGHTSHOULDER_UP_EVENT = 0x2000000;
        LEFTSTICK_UP_EVENT = 0x4000000;
        RIGHTSTICK_UP_EVENT = 0x8000000;
        AXIS_LEFTX_EVENT = 0x10000000;
        AXIS_RIGHTX_EVENT = 0x20000000;
        AXIS_LEFTY_EVENT = 0x40000000;
        AXIS_RIGHTY_EVENT = 0x80000000;
        AXIS_TRIGGERLEFT_EVENT = 0x100000000;
        AXIS_TRIGGERRIGHT_EVENT = 0x200000000;
    }

    virtual ~XBOX360DataPacket() {
    }

    void clear() {
        setGamepadID(0);
        setOn_A_Down(0);
        setOn_B_Down(0);
        setOn_X_Down(0);
        setOn_Y_Down(0);
        setOn_START_Down(0);
        setOn_BACK_Down(0);
        setOn_DPAD_DOWN_Down(0);
        setOn_DPAD_UP_Down(0);
        setOn_DPAD_LEFT_Down(0);
        setOn_DPAD_RIGHT_Down(0);
        setOn_LEFTSHOULDER_Down(0);
        setOn_RIGHTSHOULDER_Down(0);
        setOn_LEFTSTICK_Down(0);
        setOn_RIGHTSTICK_Down(0);
        setOn_A_Down(0);
        setOn_B_Down(0);
        setOn_X_Down(0);
        setOn_Y_Down(0);
        setOn_START_Down(0);
        setOn_BACK_Down(0);
        setOn_DPAD_DOWN_Down(0);
        setOn_DPAD_DOWN_Up(0);
        setOn_DPAD_LEFT_Down(0);
        setOn_DPAD_LEFT_Up(0);
        setOn_DPAD_RIGHT_Down(0);
        setOn_DPAD_RIGHT_Up(0);
        setOn_DPAD_UP_Down(0);
        setOn_DPAD_UP_Up(0);
        setOn_LEFTSHOULDER_Up(0);
        setOn_LEFTSTICK_Up(0);
        setOn_RIGHTSTICK_Up(0);
        setOn_AXIS_LEFTX(0);
        setOn_AXIS_LEFTY(0);
        setOn_AXIS_RIGHTX(0);
        setOn_AXIS_RIGHTY(0);
        setOn_AXIS_TRIGGERLEFT(0);
        setOn_AXIS_TRIGGERRIGHT(0);
        setLeftStickDeadZoneX(0);
        setLeftStickDeadZoneY(0);
        setRightStickDeadZoneX(0);
        setRightStickDeadZoneY(0);
        setLeftTriggerDeadZone(0);
        setRightTriggerDeadZone(0);
        setOn_A_Up(0);
        setOn_BACK_Up(0);
        setOn_B_Up(0);
        setOn_X_Up(0);
        setOn_Y_Up(0);
        setOn_START_Up(0);
    }

    inline float toFloat(short value) {
        return value > 0 ? value / (float) std::numeric_limits<short>::max() : value / (float) abs(std::numeric_limits<short>::min());
    }

    inline short toShort(float value) {
        return value > 0 ? value * std::numeric_limits<short>::max() : value * abs(std::numeric_limits<short>::min());
    }

    inline int getNumberOfEvents() {
        return __builtin_popcount(eventMask.value);
    }

    uint64_t getEventMask() {
        return this->eventMask.value;
    }

    inline void setEventMaskBits(uint64_t value) {
        eventMask.value |= value;
    }

    void clearEventMaskBits(uint64_t value) {
        eventMask.value &= value;
    }

    void setGamepadID(int16_t value) {
        this->gamepadID.value = value;
    }

    int16_t getGamepadID() {
        return this->gamepadID.value;
    }

    void setOn_A_Down(int16_t value) {
        this->on_A_Down.value = value;
        setEventMaskBits(A_DOWN_EVENT);
    }

    int16_t getOn_A_Down() {
        return this->on_A_Down.value;
    }

    void setOn_B_Down(int16_t value) {
        this->on_B_Down.value = value;
        setEventMaskBits(B_DOWN_EVENT);
    }

    int16_t getOn_B_Down() {
        return this->on_B_Down.value;
    }

    void setOn_X_Down(int16_t value) {
        this->on_X_Down.value = value;
        setEventMaskBits(X_DOWN_EVENT);
    }

    int16_t getOn_X_Down() {
        return this->on_X_Down.value;
    }

    void setOn_Y_Down(int16_t value) {
        this->on_Y_Down.value = value;
        setEventMaskBits(Y_DOWN_EVENT);
    }

    int16_t getOn_Y_Down() {
        return this->on_Y_Down.value;
    }

    void setOn_START_Down(int16_t value) {
        this->on_START_Down.value = value;
        setEventMaskBits(START_DOWN_EVENT);
    }

    int16_t getOn_START_Down() {
        return this->on_START_Down.value;
    }

    void setOn_BACK_Down(int16_t value) {
        this->on_BACK_Down.value = value;
        setEventMaskBits(BACK_DOWN_EVENT);
    }

    int16_t getOn_BACK_Down() {
        return this->on_BACK_Down.value;
    }

    void setOn_DPAD_DOWN_Down(int16_t value) {
        this->on_DPAD_DOWN_Down.value = value;
        setEventMaskBits(DPAD_DOWN_DOWN_EVENT);
    }

    int16_t getOn_DPAD_DOWN_Down() {
        return this->on_DPAD_DOWN_Down.value;
    }

    void setOn_DPAD_UP_Down(int16_t value) {
        this->on_DPAD_UP_Down.value = value;
        setEventMaskBits(DPAD_DOWN_UP_EVENT);
    }

    int16_t getOn_DPAD_UP_Down() {
        return this->on_DPAD_UP_Down.value;
    }

    void setOn_DPAD_LEFT_Down(int16_t value) {
        this->on_DPAD_LEFT_Down.value = value;
        setEventMaskBits(DPAD_LEFT_DOWN_EVENT);
    }

    int16_t getOn_DPAD_LEFT_Down() {
        return this->on_DPAD_LEFT_Down.value;
    }

    void setOn_DPAD_RIGHT_Down(int16_t value) {
        this->on_DPAD_RIGHT_Down.value = value;
        setEventMaskBits(DPAD_RIGHT_DOWN_EVENT);
    }

    int16_t getOn_DPAD_RIGHT_Down() {
        return this->on_DPAD_RIGHT_Down.value;
    }

    void setOn_LEFTSHOULDER_Down(int16_t value) {
        this->on_LEFTSHOULDER_Down.value = value;
        setEventMaskBits(LEFTSHOULDER_DOWN_EVENT);
    }

    int16_t getOn_LEFTSHOULDER_Down() {
        return this->on_LEFTSHOULDER_Down.value;
    }

    void setOn_RIGHTSHOULDER_Down(int16_t value) {
        this->on_RIGHTSHOULDER_Down.value = value;
        setEventMaskBits(RIGHTSHOULDER_DOWN_EVENT);
    }

    int16_t getOn_RIGHTSHOULDER_Down() {
        return this->on_RIGHTSHOULDER_Down.value;
    }

    void setOn_LEFTSTICK_Down(int16_t value) {
        this->on_LEFTSTICK_Down.value = value;
        setEventMaskBits(LEFTSTICK_DOWN_EVENT);
    }

    int16_t getOn_LEFTSTICK_Down() {
        return this->on_LEFTSTICK_Down.value;
    }

    void setOn_RIGHTSTICK_Down(int16_t value) {
        this->on_RIGHTSTICK_Down.value = value;
        setEventMaskBits(RIGHTSTICK_DOWN_EVENT);
    }

    int16_t getOn_RIGHTSTICK_Down() {
        return this->on_RIGHTSTICK_Down.value;
    }

    void setOn_A_Up(int16_t value) {
        this->on_A_Up.value = value;
        setEventMaskBits(A_UP_EVENT);
    }

    int16_t getOn_A_Up() {
        return this->on_A_Up.value;
    }

    void setOn_B_Up(int16_t value) {
        this->on_B_Up.value = value;
        setEventMaskBits(B_UP_EVENT);
    }

    int16_t getOn_B_Up() {
        return this->on_B_Up.value;
    }

    void setOn_X_Up(int16_t value) {
        this->on_X_Up.value = value;
        setEventMaskBits(X_UP_EVENT);
    }

    int16_t getOn_X_Up() {
        return this->on_X_Up.value;
    }

    void setOn_Y_Up(int16_t value) {
        this->on_Y_Up.value = value;
        setEventMaskBits(Y_UP_EVENT);
    }

    int16_t getOn_Y_Up() {
        return this->on_Y_Up.value;
    }

    void setOn_START_Up(int16_t value) {
        this->on_START_Up.value = value;
        setEventMaskBits(START_UP_EVENT);
    }

    int16_t getOn_START_Up() {
        return this->on_START_Up.value;
    }

    void setOn_BACK_Up(int16_t value) {
        this->on_BACK_Up.value = value;
        setEventMaskBits(BACK_UP_EVENT);
    }

    int16_t getOn_BACK_Up() {
        return this->on_BACK_Up.value;
    }

    void setOn_DPAD_DOWN_Up(int16_t value) {
        this->on_DPAD_DOWN_Up.value = value;
        setEventMaskBits(DPAD_DOWN_UP_EVENT);
    }

    int16_t getOn_DPAD_DOWN_Up() {
        return this->on_DPAD_DOWN_Up.value;
    }

    void setOn_DPAD_UP_Up(int16_t value) {
        this->on_DPAD_UP_Up.value = value;
        setEventMaskBits(DPAD_UP_UP_EVENT);
    }

    int16_t getOn_DPAD_UP_Up() {
        return this->on_DPAD_UP_Up.value;
    }

    void setOn_DPAD_LEFT_Up(int16_t value) {
        this->on_DPAD_LEFT_Up.value = value;
        setEventMaskBits(DPAD_LEFT_UP_EVENT);
    }

    int16_t getOn_DPAD_LEFT_Up() {
        return this->on_DPAD_LEFT_Up.value;
    }

    void setOn_DPAD_RIGHT_Up(int16_t value) {
        this->on_DPAD_RIGHT_Up.value = value;
        setEventMaskBits(DPAD_RIGHT_UP_EVENT);
    }

    int16_t getOn_DPAD_RIGHT_Up() {
        return this->on_DPAD_RIGHT_Up.value;
    }

    void setOn_LEFTSHOULDER_Up(int16_t value) {
        this->on_LEFTSHOULDER_Up.value = value;
        setEventMaskBits(LEFTSHOULDER_UP_EVENT);
    }

    int16_t getOn_LEFTSHOULDER_Up() {
        return this->on_LEFTSHOULDER_Up.value;
    }

    void setOn_RIGHTSHOULDER_Up(int16_t value) {
        this->on_RIGHTSHOULDER_Up.value = value;
        setEventMaskBits(RIGHTSHOULDER_UP_EVENT);
    }

    int16_t getOn_RIGHTSHOULDER_Up() {
        return this->on_RIGHTSHOULDER_Up.value;
    }

    void setOn_LEFTSTICK_Up(int16_t value) {
        this->on_LEFTSTICK_Up.value = value;
        setEventMaskBits(LEFTSTICK_UP_EVENT);
    }

    int16_t getOn_LEFTSTICK_Up() {
        return this->on_LEFTSTICK_Up.value;
    }

    void setOn_RIGHTSTICK_Up(int16_t value) {
        this->on_RIGHTSTICK_Up.value = value;
        setEventMaskBits(RIGHTSTICK_UP_EVENT);
    }

    int16_t getOn_RIGHTSTICK_Up() {
        return this->on_RIGHTSTICK_Up.value;
    }

    void setOn_AXIS_LEFTX(int16_t value) {
        this->on_AXIS_LEFTX.value = value;
        setEventMaskBits(AXIS_LEFTX_EVENT);
    }

    int16_t getOn_AXIS_LEFTX() {
        return this->on_AXIS_LEFTX.value;
    }

    void setOn_AXIS_RIGHTX(int16_t value) {
        this->on_AXIS_RIGHTX.value = value;
        setEventMaskBits(AXIS_RIGHTX_EVENT);
    }

    int16_t getOn_AXIS_RIGHTX() {
        return this->on_AXIS_RIGHTX.value;
    }

    void setOn_AXIS_LEFTY(int16_t value) {
        this->on_AXIS_LEFTY.value = value;
        setEventMaskBits(AXIS_LEFTY_EVENT);
    }

    int16_t getOn_AXIS_LEFTY() {
        return this->on_AXIS_LEFTY.value;
    }

    void setOn_AXIS_RIGHTY(int16_t value) {
        this->on_AXIS_RIGHTY.value = value;
        setEventMaskBits(AXIS_RIGHTY_EVENT);
    }

    int16_t getOn_AXIS_RIGHTY() {
        return this->on_AXIS_RIGHTY.value;
    }

    void setOn_AXIS_TRIGGERLEFT(int16_t value) {
        this->on_AXIS_TRIGGERLEFT.value = value;
        setEventMaskBits(AXIS_TRIGGERLEFT_EVENT);
    }

    int16_t getOn_AXIS_TRIGGERLEFT() {
        return this->on_AXIS_TRIGGERLEFT.value;
    }

    void setOn_AXIS_TRIGGERRIGHT(int16_t value) {
        this->on_AXIS_TRIGGERRIGHT.value = value;
        setEventMaskBits(AXIS_TRIGGERRIGHT_EVENT);
    }

    int16_t getOn_AXIS_TRIGGERRIGHT() {
        return this->on_AXIS_TRIGGERRIGHT.value;
    }

    void setLeftStickDeadZoneX(int16_t value) {
        this->leftStickDeadZoneX.value = value;

    }

    int16_t getLeftStickDeadZoneX() {
        return this->leftStickDeadZoneX.value;
    }

    void setLeftStickDeadZoneY(int16_t value) {
        this->leftStickDeadZoneY.value = value;
    }

    int16_t getLeftStickDeadZoneY() {
        return this->leftStickDeadZoneY.value;
    }

    void setRightStickDeadZoneX(int16_t value) {
        this->rightStickDeadZoneX.value = value;
    }

    int16_t getRightStickDeadZoneX() {
        return this->rightStickDeadZoneX.value;
    }

    void setRightStickDeadZoneY(int16_t value) {
        this->rightStickDeadZoneY.value = value;
    }

    int16_t getRightStickDeadZoneY() {
        return this->rightStickDeadZoneY.value;
    }

    void setLeftTriggerDeadZone(int16_t value) {
        this->leftTriggerDeadZone.value = value;
    }

    int16_t getLeftTriggerDeadZone() {
        return this->leftTriggerDeadZone.value;
    }

    void setRightTriggerDeadZone(int16_t value) {
        this->rightTriggerDeadZone.value = value;
    }

    int16_t getRightTriggerDeadZone() {
        return this->rightTriggerDeadZone.value;
    }

    void clearEventMask() {
        eventMask.value = 0;
    }

    void applyDeadZone() {
        this->on_AXIS_LEFTX.value = abs(getOn_AXIS_LEFTX()) < getLeftStickDeadZoneX() ? 0 : getOn_AXIS_LEFTX();
        this->on_AXIS_LEFTY.value = abs(getOn_AXIS_LEFTY()) < getLeftStickDeadZoneY() ? 0 : getOn_AXIS_LEFTY();
        this->on_AXIS_RIGHTX.value = abs(getOn_AXIS_RIGHTX()) < getRightStickDeadZoneX() ? 0 : getOn_AXIS_RIGHTX();
        this->on_AXIS_RIGHTY.value = abs(getOn_AXIS_RIGHTY()) < getRightStickDeadZoneY() ? 0 : getOn_AXIS_RIGHTY();
    }

    void copyValuesToBuffer() {
        //copy values into the data buffer
        copy(gamepadID.data, gamepadID.data + 2, getDataBuffer().begin());
        copy(on_A_Down.data, on_A_Down.data + 2, getDataBuffer().begin() + 2);
        copy(on_B_Down.data, on_B_Down.data + 2, getDataBuffer().begin() + 4);
        copy(on_X_Down.data, on_X_Down.data + 2, getDataBuffer().begin() + 6);
        copy(on_Y_Down.data, on_Y_Down.data + 2, getDataBuffer().begin() + 8);
        copy(on_START_Down.data, on_START_Down.data + 2, getDataBuffer().begin() + 10);
        copy(on_BACK_Down.data, on_BACK_Down.data + 2, getDataBuffer().begin() + 12);
        copy(on_DPAD_DOWN_Down.data, on_DPAD_DOWN_Down.data + 2, getDataBuffer().begin() + 14);
        copy(on_DPAD_UP_Down.data, on_DPAD_UP_Down.data + 2, getDataBuffer().begin() + 16);
        copy(on_DPAD_LEFT_Down.data, on_DPAD_LEFT_Down.data + 2, getDataBuffer().begin() + 18);
        copy(on_DPAD_RIGHT_Down.data, on_DPAD_RIGHT_Down.data + 2, getDataBuffer().begin() + 20);
        copy(on_LEFTSHOULDER_Down.data, on_LEFTSHOULDER_Down.data + 2, getDataBuffer().begin() + 22);
        copy(on_RIGHTSHOULDER_Down.data, on_RIGHTSHOULDER_Down.data + 2, getDataBuffer().begin() + 24);
        copy(on_LEFTSTICK_Down.data, on_LEFTSTICK_Down.data + 2, getDataBuffer().begin() + 26);
        copy(on_RIGHTSTICK_Down.data, on_RIGHTSTICK_Down.data + 2, getDataBuffer().begin() + 28);
        copy(on_A_Up.data, on_A_Up.data + 2, getDataBuffer().begin() + 30);
        copy(on_B_Up.data, on_B_Up.data + 2, getDataBuffer().begin() + 32);
        copy(on_X_Up.data, on_X_Up.data + 2, getDataBuffer().begin() + 34);
        copy(on_Y_Up.data, on_Y_Up.data + 2, getDataBuffer().begin() + 36);
        copy(on_START_Up.data, on_START_Up.data + 2, getDataBuffer().begin() + 38);
        copy(on_BACK_Up.data, on_BACK_Up.data + 2, getDataBuffer().begin() + 40);
        copy(on_DPAD_DOWN_Up.data, on_DPAD_DOWN_Up.data + 2, getDataBuffer().begin() + 42);
        copy(on_DPAD_UP_Up.data, on_DPAD_UP_Up.data + 2, getDataBuffer().begin() + 44);
        copy(on_DPAD_LEFT_Up.data, on_DPAD_LEFT_Up.data + 2, getDataBuffer().begin() + 46);
        copy(on_DPAD_RIGHT_Up.data, on_DPAD_RIGHT_Up.data + 2, getDataBuffer().begin() + 48);
        copy(on_LEFTSHOULDER_Up.data, on_LEFTSHOULDER_Up.data + 2, getDataBuffer().begin() + 50);
        copy(on_RIGHTSHOULDER_Up.data, on_RIGHTSHOULDER_Up.data + 2, getDataBuffer().begin() + 52);
        copy(on_LEFTSTICK_Up.data, on_LEFTSTICK_Up.data + 2, getDataBuffer().begin() + 54);
        copy(on_RIGHTSTICK_Up.data, on_RIGHTSTICK_Up.data + 2, getDataBuffer().begin() + 56);
        copy(on_AXIS_LEFTX.data, on_AXIS_LEFTX.data + 2, getDataBuffer().begin() + 58);
        copy(on_AXIS_RIGHTX.data, on_AXIS_RIGHTX.data + 2, getDataBuffer().begin() + 60);
        copy(on_AXIS_LEFTY.data, on_AXIS_LEFTY.data + 2, getDataBuffer().begin() + 62);
        copy(on_AXIS_RIGHTY.data, on_AXIS_RIGHTY.data + 2, getDataBuffer().begin() + 64);
        copy(on_AXIS_TRIGGERLEFT.data, on_AXIS_TRIGGERLEFT.data + 2, getDataBuffer().begin() + 66);
        copy(on_AXIS_TRIGGERRIGHT.data, on_AXIS_TRIGGERRIGHT.data + 2, getDataBuffer().begin() + 68);
        copy(leftStickDeadZoneX.data, leftStickDeadZoneX.data + 2, getDataBuffer().begin() + 70);
        copy(leftStickDeadZoneY.data, leftStickDeadZoneY.data + 2, getDataBuffer().begin() + 72);
        copy(rightStickDeadZoneX.data, rightStickDeadZoneX.data + 2, getDataBuffer().begin() + 74);
        copy(rightStickDeadZoneY.data, rightStickDeadZoneY.data + 2, getDataBuffer().begin() + 76);
        copy(leftTriggerDeadZone.data, leftTriggerDeadZone.data + 2, getDataBuffer().begin() + 78);
        copy(rightTriggerDeadZone.data, rightTriggerDeadZone.data + 2, getDataBuffer().begin() + 80);
        copy(eventMask.data, eventMask.data + 8, getDataBuffer().begin() + 82);
    }

    void copyBufferToValues() {
        //update values from data buffer
        copy(getDataBuffer().begin(), getDataBuffer().begin() + 2, gamepadID.data);
        copy(getDataBuffer().begin() + 2, getDataBuffer().begin() + 4, on_A_Down.data);
        copy(getDataBuffer().begin() + 4, getDataBuffer().begin() + 6, on_B_Down.data);
        copy(getDataBuffer().begin() + 6, getDataBuffer().begin() + 8, on_X_Down.data);
        copy(getDataBuffer().begin() + 8, getDataBuffer().begin() + 10, on_Y_Down.data);
        copy(getDataBuffer().begin() + 10, getDataBuffer().begin() + 12, on_START_Down.data);
        copy(getDataBuffer().begin() + 12, getDataBuffer().begin() + 14, on_BACK_Down.data);
        copy(getDataBuffer().begin() + 14, getDataBuffer().begin() + 16, on_DPAD_DOWN_Down.data);
        copy(getDataBuffer().begin() + 16, getDataBuffer().begin() + 18, on_DPAD_UP_Down.data);
        copy(getDataBuffer().begin() + 18, getDataBuffer().begin() + 20, on_DPAD_LEFT_Down.data);
        copy(getDataBuffer().begin() + 20, getDataBuffer().begin() + 22, on_DPAD_RIGHT_Down.data);
        copy(getDataBuffer().begin() + 22, getDataBuffer().begin() + 24, on_LEFTSHOULDER_Down.data);
        copy(getDataBuffer().begin() + 24, getDataBuffer().begin() + 26, on_RIGHTSHOULDER_Down.data);
        copy(getDataBuffer().begin() + 26, getDataBuffer().begin() + 28, on_LEFTSTICK_Down.data);
        copy(getDataBuffer().begin() + 28, getDataBuffer().begin() + 30, on_RIGHTSTICK_Down.data);
        copy(getDataBuffer().begin() + 30, getDataBuffer().begin() + 32, on_A_Up.data);
        copy(getDataBuffer().begin() + 32, getDataBuffer().begin() + 34, on_B_Up.data);
        copy(getDataBuffer().begin() + 34, getDataBuffer().begin() + 36, on_X_Up.data);
        copy(getDataBuffer().begin() + 36, getDataBuffer().begin() + 38, on_Y_Up.data);
        copy(getDataBuffer().begin() + 38, getDataBuffer().begin() + 40, on_START_Up.data);
        copy(getDataBuffer().begin() + 40, getDataBuffer().begin() + 42, on_BACK_Up.data);
        copy(getDataBuffer().begin() + 42, getDataBuffer().begin() + 44, on_DPAD_DOWN_Up.data);
        copy(getDataBuffer().begin() + 44, getDataBuffer().begin() + 46, on_DPAD_UP_Up.data);
        copy(getDataBuffer().begin() + 46, getDataBuffer().begin() + 48, on_DPAD_LEFT_Up.data);
        copy(getDataBuffer().begin() + 48, getDataBuffer().begin() + 50, on_DPAD_RIGHT_Up.data);
        copy(getDataBuffer().begin() + 50, getDataBuffer().begin() + 52, on_LEFTSHOULDER_Up.data);
        copy(getDataBuffer().begin() + 52, getDataBuffer().begin() + 54, on_RIGHTSHOULDER_Up.data);
        copy(getDataBuffer().begin() + 54, getDataBuffer().begin() + 56, on_LEFTSTICK_Up.data);
        copy(getDataBuffer().begin() + 56, getDataBuffer().begin() + 58, on_RIGHTSTICK_Up.data);
        copy(getDataBuffer().begin() + 58, getDataBuffer().begin() + 60, on_AXIS_LEFTX.data);
        copy(getDataBuffer().begin() + 60, getDataBuffer().begin() + 62, on_AXIS_RIGHTX.data);
        copy(getDataBuffer().begin() + 62, getDataBuffer().begin() + 64, on_AXIS_LEFTY.data);
        copy(getDataBuffer().begin() + 64, getDataBuffer().begin() + 66, on_AXIS_RIGHTY.data);
        copy(getDataBuffer().begin() + 66, getDataBuffer().begin() + 68, on_AXIS_TRIGGERLEFT.data);
        copy(getDataBuffer().begin() + 68, getDataBuffer().begin() + 70, on_AXIS_TRIGGERRIGHT.data);
        copy(getDataBuffer().begin() + 70, getDataBuffer().begin() + 72, leftStickDeadZoneX.data);
        copy(getDataBuffer().begin() + 72, getDataBuffer().begin() + 74, leftStickDeadZoneY.data);
        copy(getDataBuffer().begin() + 74, getDataBuffer().begin() + 76, rightStickDeadZoneX.data);
        copy(getDataBuffer().begin() + 76, getDataBuffer().begin() + 78, rightStickDeadZoneY.data);
        copy(getDataBuffer().begin() + 78, getDataBuffer().begin() + 80, leftTriggerDeadZone.data);
        copy(getDataBuffer().begin() + 80, getDataBuffer().begin() + 82, rightTriggerDeadZone.data);
        copy(getDataBuffer().begin() + 82, getDataBuffer().begin() + 90, eventMask.data);
    }

private:

    union byteArrayType {
        int8_t data[2];
        int16_t value;
    };

    union byteArrayType64 {
        int8_t data[8];
        int64_t value;
    };

    byteArrayType64 eventMask;
    byteArrayType gamepadID;
    byteArrayType on_A_Down;
    byteArrayType on_B_Down;
    byteArrayType on_X_Down;
    byteArrayType on_Y_Down;
    byteArrayType on_START_Down;
    byteArrayType on_BACK_Down;
    byteArrayType on_DPAD_DOWN_Down;
    byteArrayType on_DPAD_UP_Down;
    byteArrayType on_DPAD_LEFT_Down;
    byteArrayType on_DPAD_RIGHT_Down;
    byteArrayType on_LEFTSHOULDER_Down;
    byteArrayType on_RIGHTSHOULDER_Down;
    byteArrayType on_LEFTSTICK_Down;
    byteArrayType on_RIGHTSTICK_Down;
    byteArrayType on_A_Up;
    byteArrayType on_B_Up;
    byteArrayType on_X_Up;
    byteArrayType on_Y_Up;
    byteArrayType on_START_Up;
    byteArrayType on_BACK_Up;
    byteArrayType on_DPAD_DOWN_Up;
    byteArrayType on_DPAD_UP_Up;
    byteArrayType on_DPAD_LEFT_Up;
    byteArrayType on_DPAD_RIGHT_Up;
    byteArrayType on_LEFTSHOULDER_Up;
    byteArrayType on_RIGHTSHOULDER_Up;
    byteArrayType on_LEFTSTICK_Up;
    byteArrayType on_RIGHTSTICK_Up;
    byteArrayType on_AXIS_LEFTX;
    byteArrayType on_AXIS_RIGHTX;
    byteArrayType on_AXIS_LEFTY;
    byteArrayType on_AXIS_RIGHTY;
    byteArrayType on_AXIS_TRIGGERLEFT;
    byteArrayType on_AXIS_TRIGGERRIGHT;
    byteArrayType leftStickDeadZoneX;
    byteArrayType leftStickDeadZoneY;
    byteArrayType rightStickDeadZoneX;
    byteArrayType rightStickDeadZoneY;
    byteArrayType leftTriggerDeadZone;
    byteArrayType rightTriggerDeadZone;
};

#endif /* XBOX360DATAPACKET_H */

/*
 Two bytes meet.  The first byte asks, “Are you ill?”  
The second byte replies, “No, just feeling a bit off.”

Eight bytes walk into a bar.  The bartender asks, “Can I get you anything?”

“Yeah,” reply the bytes.  “Make us a double.”

How many programmers does it take to change a light bulb?
None – It’s a hardware problem

Why do programmers always mix up Halloween and Christmas? 
Because Oct 31 equals Dec 25.

A programmer walks to the butcher shop and buys a kilo of meat.  An hour later he comes back upset that the butcher shortchanged him by 24 grams.
 */