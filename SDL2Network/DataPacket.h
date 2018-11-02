/* 
 *    Copyright [2014] Olaf - blinky0815 - christ ]
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

#ifndef DATAPACKET_H
#define DATAPACKET_H

#include <string>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;

class DataPacket {
public:

    static const int XBOX360 = 2;
    static const int MCS16 = 4;
    static const int MCS32 = 8;
    static const int GCODE_SEQUENCE = 16;
    static const int EXIT = 32;
    static const int HEADER_SIZE = 64;
    static const int HANDSHAKE = 128;
    static const int DEFAULT_MAX_MESSAGE_SIZE = 8192 - HEADER_SIZE;

    DataPacket(int messageSize = DEFAULT_MAX_MESSAGE_SIZE) {
        if (messageSize < 1 && messageSize > DEFAULT_MAX_MESSAGE_SIZE) {
            throw range_error("Message size should be between 1 and DEFAULT_MAX_MESSAGE_SIZE");
        } else {
            dataBuffer.resize(messageSize, 0);
            numBytes.value = messageSize;
        }
    }

    virtual void clearDataBuffer() {
        dataBuffer.clear();
    }

    virtual void clearHeader() {
        setNumBytes(0);
        //setCommand(0);
        setTimestamp(0);
        setSequenceNumber(0);
        setFirstBlockIndex(0);
        setCurrentBlockIndex(0);
        setLastBlockIndex(0);
        setUserValue(0);
    }

    virtual int size() {
        return this->dataBuffer.size() + HEADER_SIZE;
    }

    virtual uint64_t getNumBytes() {
        return numBytes.value;
    }

    virtual void setType(uint64_t value) {
        this->type.value = value;
    }

    virtual uint64_t getType() {
        return type.value;
    }

    virtual void setTimestamp(uint64_t value) {
        this->timeStamp.value = value;
    }

    virtual uint64_t getTimestamp() {
        return timeStamp.value;
    }

    virtual void setSequenceNumber(uint64_t value) {
        this->sequenceNumber.value = value;
    }

    virtual uint64_t getSequenceNumber() {
        return sequenceNumber.value;
    }

    virtual void setFirstBlockIndex(uint64_t value) {
        this->blockIndexFirst.value = value;
    }

    virtual uint64_t getFirstBlockIndex() {
        return blockIndexFirst.value;
    }

    virtual void setLastBlockIndex(uint64_t value) {
        this->blockIndexLast.value = value;
    }

    virtual uint64_t getLastBlockIndex() {
        return blockIndexLast.value;
    }

    virtual void setCurrentBlockIndex(uint64_t value) {
        this->currentBlockIndex.value = value;
    }

    virtual uint64_t getCurrentBlockIndex() {
        return currentBlockIndex.value;
    }

    virtual void setUserValue(uint64_t value) {
        this->user.value = value;
    }

    virtual uint64_t getUserValue() {
        return this->user.value;
    }

    virtual std::vector<uint8_t>& getDataBuffer() {
        return this->dataBuffer;
    }

    virtual void setDataPacketData(std::vector<uint8_t>& packetArray) {
        setHeader(packetArray);
        setDataBuffer(packetArray);
    }

    virtual void getDataPacketData(std::vector<uint8_t>& packetArray) {
        getHeader(packetArray);
        getDataBuffer(packetArray);
    }

    virtual ~DataPacket() {
    }

private:

    std::vector<uint8_t> dataBuffer;

    union byteArrayType {
        uint8_t data[8];
        uint64_t value;
    };

    void setHeader(std::vector<uint8_t>& packetArray) {
        //copy header
        copy(packetArray.begin(), packetArray.begin() + 8, numBytes.data);
        copy(packetArray.begin() + 8, packetArray.begin() + 16, type.data);
        copy(packetArray.begin() + 16, packetArray.begin() + 24, timeStamp.data);
        copy(packetArray.begin() + 24, packetArray.begin() + 32, sequenceNumber.data);
        copy(packetArray.begin() + 32, packetArray.begin() + 40, blockIndexFirst.data);
        copy(packetArray.begin() + 40, packetArray.begin() + 48, blockIndexLast.data);
        copy(packetArray.begin() + 48, packetArray.begin() + 56, currentBlockIndex.data);
        copy(packetArray.begin() + 56, packetArray.begin() + 64, user.data);
    }

    void getHeader(std::vector<uint8_t>& packetArray) {
        //copy header
        copy(numBytes.data, numBytes.data + 8, packetArray.begin());
        copy(type.data, type.data + 8, packetArray.begin() + 8);
        copy(timeStamp.data, timeStamp.data + 8, packetArray.begin() + 16);
        copy(sequenceNumber.data, sequenceNumber.data + 8, packetArray.begin() + 24);
        copy(blockIndexFirst.data, blockIndexFirst.data + 8, packetArray.begin() + 32);
        copy(blockIndexLast.data, blockIndexLast.data + 8, packetArray.begin() + 40);
        copy(currentBlockIndex.data, currentBlockIndex.data + 8, packetArray.begin() + 48);
        copy(user.data, user.data + 8, packetArray.begin() + 56);
    }

    void setDataBuffer(std::vector<uint8_t>& packetArray) {
        //copy byte data
        copy(packetArray.begin() + HEADER_SIZE, packetArray.end(), dataBuffer.begin());
    }

    void getDataBuffer(std::vector<uint8_t>& packetArray) {
        //copy byte data
        copy(dataBuffer.begin(), dataBuffer.end(), packetArray.begin() + HEADER_SIZE);
    }

    byteArrayType numBytes;
    byteArrayType type;
    byteArrayType timeStamp;
    byteArrayType sequenceNumber;
    byteArrayType blockIndexFirst;
    byteArrayType blockIndexLast;
    byteArrayType currentBlockIndex;
    byteArrayType user;

    void setNumBytes(int value) {
        numBytes.value = value;
    }
};

#endif /* DATAPACKET_H */

/*payloadSize, &type, &timeStamp, &sequenceNumber*/