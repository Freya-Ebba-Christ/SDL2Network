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

#ifndef XBOX360GAMEPADCLIENT_H
#define XBOX360GAMEPADCLIENT_H

#include <TCP_Client.h>
#include <iostream>
#include <SDL2Image.h>
#include <SDL2/SDL_image.h>
#include <SDL2_framerate.h>
#include <threadworker.h>
#include <thread.h>
#include <XBOX360Gamepad.h>
#include <XBOX360GamepadEventHandler.h>
#include <chrono>
#include <bitset>
#include <XBOX360DataPacket.h>
#include <RGBA.h>
#include <CalibrationButtonEventHandler.h>
#include <button.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <Descriptor.h>
#include <Vector3.h>
#include <PID.h>
#include <Datapanel.h>
#include <ringbuffer.h>
#include <synchedcamera2.h>
#include <limits>

//tracker
#include <Calibration.h>
#include <tracker.h>
#include <trackinghelper.h>
#include <KinectHomogeneity.h>
#include <KinectBackgroundModel.h>
#include <GrahamScanConvexHull.h>
#include <Rat.h>

using namespace std;

class XBOX360GamepadClient : public XBOX360GamepadEventHandler, ThreadWorker {
public:

    XBOX360GamepadClient(const char* host, int port, int width, int height) : running(false), width(width), height(height) {
        aSynchedCamera.init();
        aSynchedCamera.start();
        normalizedDepthMap.resize(aSynchedCamera.getDepthData().size(), 0.0f);
        anSDL2ImagePtr = new SDL2Image("XBOX360GamepadClient", 0, 0, getWidth(), getHeight());
        tcp_client.setHost(host);
        tcp_client.setPort(port);

        initButtons();
        initSurfacesAndTextures();
        initTTF();
        initPIDSystemResponsePanel();
        initCalibrationProgressBar();
        initTracker();
        aRat.initDescriptors();
        //smooth coordinates by averaging over 5 values
        aRat.setMeanOverValues(5);
    }

    virtual ~XBOX360GamepadClient() {
        aSynchedCamera.shutDown();
        SDL_Quit();
    }

    void setHeight(int value) {

        this->height = value;
    }

    void setWidth(int value) {

        this->width = value;
    }

    int getWidth() {

        return this->width;
    }

    int getHeight() {

        return this->height;
    }

    void start() {
        SDL_Init(SDL_INIT_GAMECONTROLLER);

        if (!isNetworkDisabled()) {
            initDataPacket();
            tcp_client.start();
            tcp_client.connect();
        }
        gamecontroller = SDL_GameControllerOpen(0);
        gamepad.addEventHandler(this);
        this->setActive(true);
        mySDLEventhandlingThread.setThreadWorker(this);
        mySDLEventhandlingThread.start();
        this->running = true;
        float averageDepth = 0.0f;
        int axisAlignedBB_x0 = 0;
        int axisAlignedBB_x1 = 0;
        int axisAlignedBB_y0 = 0;
        int axisAlignedBB_y1 = 0;

        vector<float> oldDepthData;
        oldDepthData.resize(aSynchedCamera.getDepthData().size());
        float alpha = 0.85f;
        RGBA ballCenterColor(255, 0, 255, 255);

        //PID
        unsigned long currentTime = getCurrentTime();
        double distance;
        //Define Variables we'll be connecting to
        double setpoint, input, output;
        //Specify the links and initial tuning parameters
        double kp = 1.0, ki = 0, kd = 0.0125;
        PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);
        setpoint = 1.0;
        int value = 0;
        distance = 0.0;
        double speed = 1.0;
        //402 , 286 562 , 159
        //turn the PID on
        myPID.setOutputLimits(-1.0, 1.0);
        myPID.setMode(AUTOMATIC);
        myPID.setSampleTime(33);
        setPIDEnabled(true);
        cnt = 0;
        double xScale = anSDL2ImagePtr->getWidth() / aSynchedCamera.getDepthFrameWidth();
        double yScale = anSDL2ImagePtr->getHeight() / aSynchedCamera.getDepthFrameHeight();

        while (this->running) {
            aSynchedCamera.getSynchedFrames();
            aSynchedCamera.mirrorHorizontally(aSynchedCamera.getDepthData());

            for (int i = 0; i < oldDepthData.size(); i++) {
                oldDepthData.at(i) = alpha * aSynchedCamera.getDepthData().at(i) + (1.0f - alpha) * oldDepthData.at(i);
            }

            std::copy(aSynchedCamera.getRegisteredData().begin(), aSynchedCamera.getRegisteredData().end(), (uint8_t*) kinectVideoSurface->pixels);
            normalize(oldDepthData, this->normalizedDepthMap, 10000.0f);
            averageDepth = (averageDepth + getValue(oldDepthData, true, aSynchedCamera.getDepthFrameWidth() / 2, aSynchedCamera.getDepthFrameHeight() / 2, aSynchedCamera.getDepthFrameWidth(), aSynchedCamera.getDepthFrameHeight())) / 2.0f;
            clip(this->normalizedDepthMap, 0.13);
            trackingHelper->convertFloatToUint16(normalizedDepthMap, currentDepthMap);
            anSDL2ImagePtr->_boxRGBA(0, 0, width, height, 0, 0, 0, 255);
            SDL_UpdateTexture(kinectVideoTexture, NULL, kinectVideoSurface->pixels, kinectVideoSurface->pitch);
            SDL_RenderClear(anSDL2ImagePtr->getRenderer());
            SDL_RenderCopyEx(anSDL2ImagePtr->getRenderer(), kinectVideoTexture, NULL, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);

            if (recordingState == CALIBRATING) {
                if (!aCalibration->calibrate(currentDepthMap.data())) {
                    aCalibration->getProgressBar().paint(anSDL2ImagePtr);
                    aCalibration->getProgressBar().update(aCalibration->getProgress());
                } else {
                    cout << "CALIBRATION DONE" << endl;
                    recordingState = RECORDING_STOPPED;
                    //trackingHelper->applyMask(noTrackMask, aCalibration->getAverageINTSurface(), size);

                    memcpy(trackingHelper->getHomogeneity()->getThresholds(), aCalibration->getAverageINTSurface(), currentDepthMap.size() * sizeof (uint16_t));

                    setEnabled(true);
                    setCalibrated(true);
                }
            }

            if (isEnabled() && isCalibrated()) {
                Contour& contours = trackingHelper->process(currentDepthMap.data(), aSynchedCamera.getDepthFrameWidth(), aSynchedCamera.getDepthFrameHeight());
                int start;
                int end;
                trackingHelper->getLargestContour(contours, &start, &end);
                if ((end - start) > trackingHelper->getConfiguration().tracker_min_contour_length) {
                    trackingHelper->draw_single_contour(contours, anSDL2ImagePtr, start, end, lineColor);
                    int x;
                    int y;
                    trackingHelper->getMedianCenterOfMass(contours, start, end, &x, &y);
                    x = (int) x * trackingHelper->getScalingX();
                    y = (int) y * trackingHelper->getScalingY();

                    Point<int> center(x, y);
                    aRat.setCenterOfMass(center);
                    int x_ab, y_ab, x_bc, y_bc, x_cd, y_cd, x_da, y_da;
                    int x0, y0, x1, y1, x2, y2, x3, y3;

                    trackingHelper->getOBB(contours, start, end, &x0, &y0, &x1, &y1, &x2, &y2, &x3, &y3);
                    trackingHelper->getConvexCombination(x0, y0, x1, y1, x2, y2, x3, y3, &x_ab, &y_ab, &x_bc, &y_bc, &x_cd, &y_cd, &x_da, &y_da);
                    trackingHelper->getAxisAlignedBoundingBox(contours, start, end, &axisAlignedBB_x0, &axisAlignedBB_y0, &axisAlignedBB_x1, &axisAlignedBB_y1);
                    makeNormalMap(normalizedDepthMap, axisAlignedBB_x0, axisAlignedBB_y0, axisAlignedBB_x1, axisAlignedBB_y1);
                    detectFeatures(aRat);
                }
            }

            //if (aRat.isVisible()) {
            anSDL2ImagePtr->_lineRGBA(aRat.getCenterOfMass().getX() - 10, aRat.getCenterOfMass().getY(), aRat.getCenterOfMass().getX() + 10, aRat.getCenterOfMass().getY(), 255, 0, 0, 255);
            anSDL2ImagePtr->_lineRGBA(aRat.getCenterOfMass().getX(), aRat.getCenterOfMass().getY() - 10, aRat.getCenterOfMass().getX(), aRat.getCenterOfMass().getY() + 10, 255, 0, 0, 255);

            anSDL2ImagePtr->_lineRGBA(aRat.getCenterOfMass().getX(), aRat.getCenterOfMass().getY(), getBallCenter().getX(), getBallCenter().getY(), 255, 0, 0, 255);

            //anSDL2ImagePtr->_lineRGBA(aRat.getCenterOfMass().getX(), aRat.getCenterOfMass().getY(), getBallCenter().getX(), getBallCenter().getY(), 255, 127, 0, 255);
            anSDL2ImagePtr->_lineRGBA((aRat.getHeadPosition().getX() + axisAlignedBB_x0 - 32) * trackingHelper->getScalingX(), (aRat.getHeadPosition().getY() + axisAlignedBB_y0 - 32) * trackingHelper->getScalingY(), getBallCenter().getX(), getBallCenter().getY(), 255, 127, 0, 255);
            //} else {
            //    cout << "no rat" << endl;
            //}
            drawBallCenter(ballCenterColor);

            if (isPIDEnabled()) {
                //if (cnt++ % 100 == 99) {


                //cout << "distance: " << distance << endl;

                //0.5 - (setpoint / (speed + setpoint))
                //speed = 1.0 - (distance / setpoint);
                //double normalizedDistance = (setpoint) / (distance + setpoint);
                //cout << "Output: " << normalizedDistance << endl;
                //cout << "speed: " << speed << endl;

                Vector3<double> ratPosition(aRat.getCenterOfMass().getX() * xScale, aRat.getCenterOfMass().getY() * yScale, 0);
                Vector3<double> ballCenterPosition(getBallCenter().getX(), getBallCenter().getY(), 0);

                cout << "Rat position: " << ratPosition.x << " , " << ratPosition.y << endl;
                cout << "Ball center position: " << ballCenterPosition.x << " , " << ballCenterPosition.y << endl;
                double vectorLength = abs(ratPosition.distance(ballCenterPosition));
                cout << "vectorLength " << vectorLength / 150.0 << endl;
                Vector3<double> directionVector = ballCenterPosition - ratPosition;
                directionVector.normalize();
                //cout << "Normalized movement direction vector: " << directionVector.x << " , " << -directionVector.y << endl;
                //cout << "Normalized movement velocity vector: " << directionVector.x * speed << " , " << -directionVector.y * speed << endl;
                input = 1.0 - (vectorLength / 150.0);
                myPID.compute();
                //speed += output;
                //speed = vectorLength / 150.0;
                //speed += output;
                //speed -= output;
                speed = vectorLength / 150.0;
                //velocityDataPanel.addNormalizedValue(df.length());
                if (!isNetworkDisabled()) {
                    cout << "move ball" << endl;
                    double x = (directionVector.x * output);
                    double y = (directionVector.y * output);
                    //cout << "move ball x: " << x << " y:" << y << " speed " << speed << " input " << input << " output " << output << " 1.0 - vectorLength / 150.0 " << (1.0 - vectorLength / 150.0) << endl;
                    //cout << "speed " << speed << " output " << output << endl;
                    moveBall(x, y);
                }
                pidSystemResonseDataPanel.addNormalizedValue((output / 2.0) + 0.5);
                pidSetPointDataPanel.addNormalizedValue(1.0 - 0.5);
                //}
            }

            /*
                         if (isPIDEnabled()) {
                //if (cnt++ % 100 == 99) {


                //cout << "distance: " << distance << endl;

                //0.5 - (setpoint / (speed + setpoint))
                //speed = 1.0 - (distance / setpoint);
                //double normalizedDistance = (setpoint) / (distance + setpoint);
                //cout << "Output: " << normalizedDistance << endl;
                //cout << "speed: " << speed << endl;

                Vector3<double> ratPosition(aRat.getCenterOfMass().getX() * xScale, aRat.getCenterOfMass().getY() * yScale, 0);
                Vector3<double> ballCenterPosition(getBallCenter().getX(), getBallCenter().getY(), 0);

                cout << "Rat position: " << ratPosition.x << " , " << ratPosition.y << endl;
                cout << "Ball center position: " << ballCenterPosition.x << " , " << ballCenterPosition.y << endl;
                double vectorLength = abs(ratPosition.distance(ballCenterPosition));
                cout << "vectorLength " << vectorLength / setpoint << endl;
                //speed = vectorLength / setpoint;
                Vector3<double> directionVector = ballCenterPosition - ratPosition;
                directionVector.normalize();
                //cout << "Normalized movement direction vector: " << directionVector.x << " , " << -directionVector.y << endl;
                //cout << "Normalized movement velocity vector: " << directionVector.x * speed << " , " << -directionVector.y * speed << endl;
                input = vectorLength / setpoint;
                myPID.compute();
                speed += output;
                //velocityDataPanel.addNormalizedValue(df.length());
                if (!isNetworkDisabled()) {
                    cout << "move ball" << endl;
                    double x = (directionVector.x * speed / setpoint);
                    double y = (directionVector.y * speed / setpoint);
                    cout << "move ball x: " << x << " y:" << y << " speed " << speed / setpoint << endl;
                    moveBall(x, y);
                }
                //distance += output;
                //pidSystemResonseDataPanel.addNormalizedValue(speed / 2.0);
                //pidSetPointDataPanel.addNormalizedValue(1.0 - 0.5);
                //}
            }
             */

            pidSetPointDataPanel.paint(anSDL2ImagePtr);
            pidSystemResonseDataPanel.paint(anSDL2ImagePtr);
            velocityDataPanel.paint(anSDL2ImagePtr);

            if (pidSystemResonseDataPanel.isVisible() && pidSetPointDataPanel.isVisible()) {
                anSDL2ImagePtr->_stringRGBA(pidSystemResonseDataPanel.getX() + 15, pidSystemResonseDataPanel.getY() + 15, "PID SYSTEM RESPONSE", 255, 0, 0, 255);
                anSDL2ImagePtr->_stringRGBA(pidSetPointDataPanel.getX() + 15, pidSetPointDataPanel.getY() + 30, "PID SET POINT", 0, 0, 255, 255);

                anSDL2ImagePtr->_stringRGBA(pidSetPointDataPanel.getX() + 15, pidSetPointDataPanel.getY() + pidSetPointDataPanel.getHeight() - 45, ("KP: " + std::to_string(kp)).c_str(), 255, 255, 255, 255);
                anSDL2ImagePtr->_stringRGBA(pidSetPointDataPanel.getX() + 15, pidSetPointDataPanel.getY() + pidSetPointDataPanel.getHeight() - 30, ("KI: " + std::to_string(ki)).c_str(), 255, 255, 255, 255);
                anSDL2ImagePtr->_stringRGBA(pidSetPointDataPanel.getX() + 15, pidSetPointDataPanel.getY() + pidSetPointDataPanel.getHeight() - 15, ("KD: " + std::to_string(kd)).c_str(), 255, 255, 255, 255);
            }

            if (!isPIDEnabled()) {
                anSDL2ImagePtr->_stringRGBA(15, 15, "PID DISABLED", 255, 0, 0, 255);
            }
            calibrationButton->paint(anSDL2ImagePtr);
            anSDL2ImagePtr->paint();
        }
        mySDLEventhandlingThread.stop();
        this->setActive(false);
        if (!isNetworkDisabled()) {

            tcp_client.disconnect();
            tcp_client.stop();
        }
    }

    void execute() {

        while (SDL_PollEvent(&event)) {
            calibrationButton->checkCollision(&event);
            if (event.type == SDL_CONTROLLERAXISMOTION || SDL_CONTROLLERBUTTONDOWN || SDL_CONTROLLERBUTTONUP) {
                if (gamecontroller != NULL) {
                    //aXBOX360DataPacket.clear();
                    aXBOX360DataPacket.clearEventMask();
                    gamepad.processEvent(&event, gamecontroller); // this will call one or more callback methods, which will set values and modify the event mask.
                    aXBOX360DataPacket.setSequenceNumber(sequenceNumber++);
                    aXBOX360DataPacket.setTimestamp(getCurrentTime());
                    aXBOX360DataPacket.copyValuesToBuffer();
                    cout << "aXBOX360DataPacket: " << aXBOX360DataPacket.getOn_AXIS_LEFTX() << " , " << aXBOX360DataPacket.getOn_AXIS_LEFTY() << endl;
                    if (!isNetworkDisabled()) {
                        tcp_client.sendDataPacket(aXBOX360DataPacket);
                    }
                }
            }

            switch (event.type) {
                case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                            cout << "SPACE" << endl;
                            cv::imwrite("./" + std::to_string(cnt++) + "template_image.jpg", grayScaleFrame);
                            break;

                        case SDLK_F1:
                            pidSystemResonseDataPanel.setVisible(!pidSystemResonseDataPanel.isVisible());
                            pidSetPointDataPanel.setVisible(!pidSetPointDataPanel.isVisible());
                            break;

                        case SDLK_F2:
                            setPIDEnabled(!isPIDEnabled());
                            break;
                    }
                    break;
                }
                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_CLOSE:
                        {
                            this->running = false;
                        }
                    }
                    windowEventHandler.perform(event.window.event);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                {
                    if ((int) event.button.state) {

                        if (event.motion.y < calibrationButton->getPosition()->second) {
                            getBallCenter().setX(event.motion.x);
                            getBallCenter().setY(event.motion.y);
                        }
                        cout << "x: " << event.motion.x << " y: " << event.motion.y << endl;
                    }
                }
                    break;
            }
            break;
        }
    }

    virtual void on_A_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_A_Down(1);
        aXBOX360DataPacket.setOn_A_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.A_DOWN_EVENT);
    }

    virtual void on_B_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_B_Down(1);
        aXBOX360DataPacket.setOn_B_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.B_DOWN_EVENT);
    }

    virtual void on_X_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_X_Down(1);
        aXBOX360DataPacket.setOn_X_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.X_DOWN_EVENT);
    }

    virtual void on_Y_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_Y_Down(1);
        aXBOX360DataPacket.setOn_Y_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.Y_DOWN_EVENT);
    }

    virtual void on_START_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_START_Down(1);
        aXBOX360DataPacket.setOn_START_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.START_DOWN_EVENT);
    }

    virtual void on_BACK_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_BACK_Down(1);
        aXBOX360DataPacket.setOn_BACK_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.BACK_DOWN_EVENT);
    }

    virtual void on_DPAD_DOWN_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_DPAD_DOWN_Down(1);
        aXBOX360DataPacket.setOn_DPAD_DOWN_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.DPAD_DOWN_DOWN_EVENT);
    }

    virtual void on_DPAD_UP_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_DPAD_UP_Down(1);
        aXBOX360DataPacket.setOn_DPAD_UP_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.DPAD_UP_DOWN_EVENT);
    }

    virtual void on_DPAD_LEFT_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_DPAD_LEFT_Down(1);
        aXBOX360DataPacket.setOn_DPAD_LEFT_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.DPAD_LEFT_DOWN_EVENT);
    }

    virtual void on_DPAD_RIGHT_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_DPAD_RIGHT_Down(1);
        aXBOX360DataPacket.setOn_DPAD_RIGHT_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.DPAD_RIGHT_DOWN_EVENT);
    }

    virtual void on_LEFTSHOULDER_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_LEFTSHOULDER_Down(1);
        aXBOX360DataPacket.setOn_LEFTSHOULDER_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.LEFTSHOULDER_DOWN_EVENT);
    }

    virtual void on_RIGHTSHOULDER_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_RIGHTSHOULDER_Down(1);
        aXBOX360DataPacket.setOn_RIGHTSHOULDER_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.RIGHTSHOULDER_DOWN_EVENT);
    }

    virtual void on_LEFTSTICK_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_LEFTSTICK_Down(1);
        aXBOX360DataPacket.setOn_LEFTSTICK_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.LEFTSTICK_DOWN_EVENT);
    }

    virtual void on_RIGHTSTICK_Down(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_RIGHTSTICK_Down(1);
        aXBOX360DataPacket.setOn_RIGHTSTICK_Up(0);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.RIGHTSTICK_DOWN_EVENT);
    }

    virtual void on_A_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_A_Down(0);
        aXBOX360DataPacket.setOn_A_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.A_UP_EVENT);
    }

    virtual void on_B_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_B_Down(0);
        aXBOX360DataPacket.setOn_B_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.B_UP_EVENT);
    }

    virtual void on_X_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_X_Down(0);
        aXBOX360DataPacket.setOn_X_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.X_UP_EVENT);
    }

    virtual void on_Y_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_Y_Down(0);
        aXBOX360DataPacket.setOn_Y_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.Y_UP_EVENT);
    }

    virtual void on_START_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_START_Down(0);
        aXBOX360DataPacket.setOn_START_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.START_UP_EVENT);
    }

    virtual void on_BACK_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_BACK_Down(0);
        aXBOX360DataPacket.setOn_BACK_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.BACK_UP_EVENT);
    }

    virtual void on_DPAD_DOWN_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_DPAD_DOWN_Down(0);
        aXBOX360DataPacket.setOn_DPAD_DOWN_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.DPAD_DOWN_UP_EVENT);
    }

    virtual void on_DPAD_UP_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_DPAD_UP_Down(0);
        aXBOX360DataPacket.setOn_DPAD_UP_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.DPAD_UP_UP_EVENT);
    }

    virtual void on_DPAD_LEFT_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_DPAD_LEFT_Down(0);
        aXBOX360DataPacket.setOn_DPAD_LEFT_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.DPAD_LEFT_UP_EVENT);
    }

    virtual void on_DPAD_RIGHT_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_DPAD_RIGHT_Down(0);
        aXBOX360DataPacket.setOn_DPAD_RIGHT_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.DPAD_RIGHT_UP_EVENT);
    }

    virtual void on_LEFTSHOULDER_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_LEFTSHOULDER_Down(0);
        aXBOX360DataPacket.setOn_LEFTSHOULDER_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.LEFTSHOULDER_UP_EVENT);
    }

    virtual void on_RIGHTSHOULDER_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_RIGHTSHOULDER_Down(0);
        aXBOX360DataPacket.setOn_RIGHTSHOULDER_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.RIGHTSHOULDER_UP_EVENT);
    }

    virtual void on_LEFTSTICK_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_LEFTSTICK_Down(0);
        aXBOX360DataPacket.setOn_LEFTSTICK_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.LEFTSTICK_UP_EVENT);
    }

    virtual void on_RIGHTSTICK_Up(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_RIGHTSTICK_Down(0);
        aXBOX360DataPacket.setOn_RIGHTSTICK_Up(1);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.RIGHTSTICK_UP_EVENT);
    }

    virtual void on_AXIS_LEFTX(SDL_GameController* gamecontroller) {
        //cout << "on_AXIS_LEFTX" << endl;

        aXBOX360DataPacket.setOn_AXIS_LEFTX(SDL_GameControllerGetAxis(gamecontroller, SDL_CONTROLLER_AXIS_LEFTX));
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.AXIS_LEFTX_EVENT);
    }

    virtual void on_AXIS_RIGHTX(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_AXIS_RIGHTX(SDL_GameControllerGetAxis(gamecontroller, SDL_CONTROLLER_AXIS_RIGHTX));
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.AXIS_RIGHTX_EVENT);
    }

    virtual void on_AXIS_LEFTY(SDL_GameController* gamecontroller) {
        //cout << "on_AXIS_LEFTY" << endl;

        aXBOX360DataPacket.setOn_AXIS_LEFTY(SDL_GameControllerGetAxis(gamecontroller, SDL_CONTROLLER_AXIS_LEFTY));
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.AXIS_LEFTY_EVENT);
    }

    virtual void on_AXIS_RIGHTY(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_AXIS_RIGHTY(SDL_GameControllerGetAxis(gamecontroller, SDL_CONTROLLER_AXIS_RIGHTY));
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.AXIS_RIGHTY_EVENT);
    }

    virtual void on_AXIS_TRIGGERLEFT(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_AXIS_TRIGGERLEFT(SDL_GameControllerGetAxis(gamecontroller, SDL_CONTROLLER_AXIS_TRIGGERLEFT));
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.AXIS_TRIGGERLEFT_EVENT);
    }

    virtual void on_AXIS_TRIGGERRIGHT(SDL_GameController* gamecontroller) {

        aXBOX360DataPacket.setOn_AXIS_TRIGGERRIGHT(SDL_GameControllerGetAxis(gamecontroller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT));
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.AXIS_TRIGGERRIGHT_EVENT);
    }

    void setNetworkDisabled(bool value) {

        this->networkDisabled = value;
    }

    bool isNetworkDisabled() {

        return this->networkDisabled;
    }

    void calibrate() {
        if (recordingState == RECORDING_STOPPED) {

            aCalibration->reset();
            recordingState = CALIBRATING;
            setEnabled(false);
            setCalibrated(false);
        }
    }

    void setBallCenter(Point<int>& value) {

        this->ballCenter.setX(value.getX());
        this->ballCenter.setY(value.getY());
    }

    Point<int>& getBallCenter() {

        return this->ballCenter;
    }


private:

    enum RECORDING_STATE {
        RECORDING = 0, RECORDING_STOPPED = 1, RECORDING_PAUSED = 2, CALIBRATING = 3
    };
    TCP_Client tcp_client;
    bool running;
    int width;
    int height;
    Thread mySDLEventhandlingThread;
    SDL_Event event;
    SDL2Helper anSDL2Helper;
    SDL2Image* anSDL2ImagePtr;
    XBOX360Gamepad<XBOX360GamepadClient> gamepad;
    SDL_GameController* gamecontroller;
    XBOX360DataPacket aXBOX360DataPacket;
    u_int64_t sequenceNumber = 0;
    bool networkDisabled = false;
    SynchedCamera2 aSynchedCamera;
    bool trackingEnabled;
    RGBA lineColor;
    RECORDING_STATE recordingState;
    Calibration* aCalibration;
    TTF_Font * liberationTrueTypeFont;
    bool calibrated = false;
    vector<uint16_t> currentDepthMap;
    TrackingHelper<KinectHomogeneity < KinectBackgroundModel>>*trackingHelper;
    Point<int> ballCenter;
    std::vector<float_t> normalizedDepthMap;
    SDL_Surface* kinectDepthSurface;
    SDL_Texture* kinectDepthTexture;
    SDL_Surface* backgroundModelSurface;
    SDL_Texture* backgroundModelTexture;
    SDL_Surface* kinectVideoSurface;
    SDL_Texture* kinectVideoTexture;
    Button<CalibrationButtonEventHandler<XBOX360GamepadClient> >* calibrationButton;
    CalibrationButtonEventHandler<XBOX360GamepadClient>* calibrationButtonEventHandler;
    Rat aRat;
    int cnt = 0;
    Datapanel pidSystemResonseDataPanel;
    Datapanel pidSetPointDataPanel;
    Datapanel velocityDataPanel;
    bool pidEnabled;

    //opencv
    cv::Mat grayScaleFrame;

    void setPIDEnabled(bool value) {

        this->pidEnabled = value;
    }

    bool isPIDEnabled() {

        return this->pidEnabled;
    }

    bool isEnabled() {

        return trackingEnabled;
    }

    void setEnabled(bool value) {

        trackingEnabled = value;
    }

    uint64 getCurrentTime() {

        return chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    void moveBall(double x, double y) {

        int16_t xValue = x > 0 ? (std::numeric_limits<int16_t>::max() * x) : (abs(std::numeric_limits<int16_t>::min()) * x);
        int16_t yValue = y > 0 ? (std::numeric_limits<int16_t>::max() * y) : (abs(std::numeric_limits<int16_t>::min()) * y);

        cout << "yValue " << yValue << endl;

        aXBOX360DataPacket.clearEventMask();
        aXBOX360DataPacket.setOn_AXIS_LEFTX(xValue);
        aXBOX360DataPacket.setOn_AXIS_LEFTY(yValue);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.AXIS_LEFTX_EVENT);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.AXIS_LEFTY_EVENT);
        aXBOX360DataPacket.setSequenceNumber(sequenceNumber++);
        aXBOX360DataPacket.setTimestamp(getCurrentTime());
        aXBOX360DataPacket.copyValuesToBuffer();
        if (!isNetworkDisabled()) {
            cout << "sending packet" << endl;
            tcp_client.sendDataPacket(aXBOX360DataPacket);
        }

        /*
        aXBOX360DataPacket.clearEventMask();
        aXBOX360DataPacket.setOn_AXIS_LEFTY(yValue);
        aXBOX360DataPacket.setOn_AXIS_LEFTX(xValue);
        aXBOX360DataPacket.setEventMaskBits(aXBOX360DataPacket.AXIS_LEFTY_EVENT);
        aXBOX360DataPacket.setSequenceNumber(sequenceNumber++);
        aXBOX360DataPacket.setTimestamp(getCurrentTime());
        aXBOX360DataPacket.copyValuesToBuffer();
        if (!isNetworkDisabled()) {
            cout << "sending packet" << endl;
            tcp_client.sendDataPacket(aXBOX360DataPacket);
        }
         */
    }

    void initPIDSystemResponsePanel() {

        RGBA pidSystemResonseLineColor(255, 0, 0, 255);
        pidSystemResonseDataPanel.resizeBuffer(300);
        pidSystemResonseDataPanel.setX(50);
        pidSystemResonseDataPanel.setY(getHeight() / 2 + 125);
        pidSystemResonseDataPanel.setWidth(getWidth() - 100);
        pidSystemResonseDataPanel.setHeight(getHeight() / 2 - 150);
        pidSystemResonseDataPanel.setLineColor(pidSystemResonseLineColor);
        pidSystemResonseDataPanel.setVisible(true);

        RGBA pidSetPointLineColor(0, 0, 255, 255);
        pidSetPointDataPanel.resizeBuffer(300);
        pidSetPointDataPanel.setX(50);
        pidSetPointDataPanel.setY(getHeight() / 2 + 125);
        pidSetPointDataPanel.setWidth(getWidth() - 100);
        pidSetPointDataPanel.setHeight(getHeight() / 2 - 150);
        pidSetPointDataPanel.setLineColor(pidSetPointLineColor);
        pidSetPointDataPanel.setBackgroundEnabled(false);
        pidSetPointDataPanel.setVisible(true);
    }

    void initVelocityMonitorPanel() {

        RGBA velocityDataPanelColor(255, 255, 255, 255);
        velocityDataPanel.resizeBuffer(300);
        velocityDataPanel.setX(50);
        velocityDataPanel.setY(getHeight() / 2 + 125);
        velocityDataPanel.setWidth(getWidth() - 100);
        velocityDataPanel.setHeight(getHeight() / 2 - 150);
        velocityDataPanel.setLineColor(velocityDataPanelColor);
        velocityDataPanel.setBackgroundEnabled(false);
        velocityDataPanel.setVisible(true);
    }

    void initTracker() {

        setEnabled(true);
        setCalibrated(false);
        recordingState = RECORDING_STOPPED;
        currentDepthMap.resize(aSynchedCamera.getDepthData().size());
        lineColor.setColor(255, 0, 0, 255);
        Configuration config;
        config.tracker_min_contour_length = 150;
        trackingHelper = new TrackingHelper < KinectHomogeneity < KinectBackgroundModel >> (config, aSynchedCamera.getDepthFrameWidth(), aSynchedCamera.getDepthFrameHeight());
        trackingHelper->setScalingX((float) getWidth() / (float) aSynchedCamera.getDepthFrameWidth());
        trackingHelper->setScalingY((float) getHeight() / (float) aSynchedCamera.getDepthFrameHeight());
        trackingHelper->getHomogeneity()->setMinDistance(300);
        trackingHelper->getHomogeneity()->setMaxDistance(1300);
        trackingHelper->getHomogeneity()->setThresholdOffset(20);
    }

    void setCalibrated(bool value) {

        this->calibrated = value;
    }

    bool isCalibrated() {

        return this->calibrated;
    }

    void initSurfacesAndTextures() {

        kinectDepthSurface = anSDL2Helper.createSurface(aSynchedCamera.getDepthFrameWidth(), aSynchedCamera.getDepthFrameHeight(), anSDL2ImagePtr->getWindow());
        kinectDepthTexture = SDL_CreateTextureFromSurface(anSDL2ImagePtr->getRenderer(), kinectDepthSurface);

        backgroundModelSurface = anSDL2Helper.createSurface(aSynchedCamera.getDepthFrameWidth(), aSynchedCamera.getDepthFrameHeight(), anSDL2ImagePtr->getWindow());
        backgroundModelTexture = SDL_CreateTextureFromSurface(anSDL2ImagePtr->getRenderer(), backgroundModelSurface);

        kinectVideoSurface = anSDL2Helper.createSurface(aSynchedCamera.getRegisteredFrameWidth(), aSynchedCamera.getRegisteredFrameHeight(), anSDL2ImagePtr->getWindow());
        kinectVideoTexture = SDL_CreateTextureFromSurface(anSDL2ImagePtr->getRenderer(), kinectVideoSurface);

        //noTrackSurface = IMG_Load(recordingSetupPtr->getNoTrackAreaMask().c_str());
        //noTrackTexture = SDL_CreateTextureFromSurface(anSDL2ImagePtr->getRenderer(), noTrackSurface);

        SDL_SetRenderDrawBlendMode(anSDL2ImagePtr->getRenderer(), SDL_BLENDMODE_BLEND);
        SDL_SetTextureBlendMode(kinectDepthTexture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureBlendMode(kinectVideoTexture, SDL_BLENDMODE_BLEND);
        //
        //SDL_SetTextureBlendMode(noTrackTexture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureBlendMode(backgroundModelTexture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(kinectDepthTexture, 128);
        SDL_SetTextureAlphaMod(kinectVideoTexture, 255);
        //SDL_SetTextureAlphaMod(noTrackTexture, 255);
        SDL_SetTextureAlphaMod(backgroundModelTexture, 255);
    }

    void initTTF() {

        anSDL2ImagePtr->initTTF();
    }

    inline int getValue(const int* map, int wrap, int x, int y, int w, int h) {
        if (x < 0) x = wrap ? (x + w) : 0;
        if (y < 0) y = wrap ? (y + h) : 0;
        if (x >= w) x = wrap ? (x - w) : (w - 1);
        if (y >= h) y = wrap ? (y - h) : (h - 1);
        int idx = x + y * w;

        return map[idx];
    }

    inline float_t getValue(vector<float_t>& map, int wrap, int x, int y, int w, int h) {
        if (x < 0) x = wrap ? (x + w) : 0;
        if (y < 0) y = wrap ? (y + h) : 0;
        if (x >= w) x = wrap ? (x - w) : (w - 1);
        if (y >= h) y = wrap ? (y - h) : (h - 1);
        int idx = x + y * w;

        return map.at(idx);
    }

    void normalize(vector<float_t>& depthMap, vector<float_t>& normalizedMap, float_t value) {
        for (int i = 0; i < depthMap.size(); i++) {

            normalizedMap.at(i) = depthMap.at(i) / value;
            //normalizedMap.at(i) = (normalizedMap.at(i) + depthMap.at(i) / value) / 2.0f;
        }
    }

    void clip(vector<float_t>& normalizedMap, float_t value = 1.0f) {
        for (int i = 0; i < normalizedMap.size(); i++) {
            if (normalizedMap.at(i) >= value) {
                normalizedMap.at(i) = 0.0f;
            }
        }
    }

    void makeNormalMap(vector<float_t>& depthMap, int x0, int y0, int x1, int y1) {
        const int width = aSynchedCamera.getRegisteredFrameWidth();
        const int height = aSynchedCamera.getRegisteredFrameHeight();
        cv::Mat frame = cv::Mat::zeros(y1 - y0 + 64, x1 - x0 + 64, CV_8UC3);
        vector<cv::Mat> channels;
        cv::split(frame, channels);
        const float extrusion = 32.0;
        const float depth = 1.0f / extrusion;
        const int wrap = 1;

        for (int y = y0; y < y1; y++) {
            for (int x = x0; x < x1; x++) {
                if (getValue(depthMap, wrap, x, y, width, height) != 0.0 && getValue(trackingHelper->getOccu(), wrap, x, y, width, height) != 0) {
                    const float up = getValue(depthMap, wrap, x, y - 1, width, height);
                    const float down = getValue(depthMap, wrap, x, y + 1, width, height);
                    const float left = getValue(depthMap, wrap, x - 1, y, width, height);
                    const float right = getValue(depthMap, wrap, x + 1, y, width, height);
                    const float upleft = getValue(depthMap, wrap, x - 1, y - 1, width, height);
                    const float upright = getValue(depthMap, wrap, x + 1, y - 1, width, height);
                    const float downleft = getValue(depthMap, wrap, x - 1, y + 1, width, height);
                    const float downright = getValue(depthMap, wrap, x + 1, y + 1, width, height);

                    const float vert = (down - up) * extrusion + downright + downleft - upright - upleft;
                    const float horiz = (right - left) * extrusion + upright + downright - upleft - downleft;
                    const float scale = 0.5 / sqrt(vert * vert + horiz * horiz + depth * depth);

                    channels.at(0).at<unsigned char>(y - y0 + 32, x - x0 + 32) = (uint8_t) ((0.5 + depth * scale)*255.0);
                    channels.at(1).at<unsigned char>(y - y0 + 32, x - x0 + 32) = (uint8_t) ((0.5 + vert * scale)*255.0);
                    channels.at(2).at<unsigned char>(y - y0 + 32, x - x0 + 32) = (uint8_t) ((0.5 - horiz * scale)*255.0);
                } else {

                    channels.at(0).at<unsigned char>(y - y0 + 32, x - x0 + 32) = 0;
                    channels.at(1).at<unsigned char>(y - y0 + 32, x - x0 + 32) = 0;
                    channels.at(2).at<unsigned char>(y - y0 + 32, x - x0 + 32) = 0;
                }
            }
        }

        grayScaleFrame = cv::Mat::zeros(frame.rows, frame.cols, CV_8UC1);
        cv::merge(channels, frame);
        cv::cvtColor(frame, grayScaleFrame, CV_BGR2GRAY);
    }

    void detectFeatures(Rat& rat) {
        aRat.setVisible(false);
        std::vector<cv::KeyPoint> currentKPTS;
        cv::Mat img_keypoints;
        cv::OrbFeatureDetector aOrbFeatureDetector(5500);
        aOrbFeatureDetector.detect(grayScaleFrame, currentKPTS);
        Descriptor aDescriptor;
        aDescriptor.setROI(0, 0, grayScaleFrame.cols, grayScaleFrame.rows);
        aDescriptor.create(grayScaleFrame, currentKPTS);
        vector<double> xValuesHead;
        vector<double> yValuesHead;
        std::vector< cv::DMatch > headMatches;

        if (aDescriptor.getDescriptors().rows > 0) {
            //matcher.knnMatch(aDescriptor.getDescriptors(), aHeadDescriptor.getDescriptors(), knnMatches, 2);
            //matcher.match(aDescriptor.getDescriptors(), aHeadDescriptor.getDescriptors(), matches);
            aRat.matchHead(aDescriptor.getDescriptors(), headMatches);
            double max_dist = 0;

            double min_dist = 10000;

            //HEAD -- BEGIN
            //-- Quick calculation of max and min distances between keypoints
            for (int i = 0; i < aDescriptor.getDescriptors().rows; i++) {
                double dist = headMatches[i].distance;
                if (dist < min_dist) min_dist = dist;
                if (dist > max_dist) max_dist = dist;
            }

            for (int i = 0; i < aDescriptor.getDescriptors().rows; i++) {
                if (headMatches[i].distance <= 100) {
                    xValuesHead.push_back(currentKPTS.at(headMatches[i].queryIdx).pt.x);
                    yValuesHead.push_back(currentKPTS.at(headMatches[i].queryIdx).pt.y);
                }
            }

            if (xValuesHead.size() != 0 && yValuesHead.size() != 0) {

                aRat.setVisible(true);
                std::nth_element(xValuesHead.begin(), xValuesHead.begin() + xValuesHead.size() / 2, xValuesHead.end());
                int medianX = xValuesHead[xValuesHead.size() / 2];
                std::nth_element(yValuesHead.begin(), yValuesHead.begin() + yValuesHead.size() / 2, yValuesHead.end());
                int medianY = yValuesHead[yValuesHead.size() / 2];
                int thickness = -1;
                int lineType = 8;
                Point<int> currentPosition(medianX, medianY);
                aRat.setHeadPosition(currentPosition);
                cv::Point point(aRat.getHeadPosition().getX(), aRat.getHeadPosition().getY());
                //HEAD -- END
                //cv::circle(grayScaleFrame, point, 1, cv::Scalar(255), 8, -1);
            }
        }

        cv::imshow("blubb2", grayScaleFrame);
        cv::waitKey(1);
    }

    void drawBallCenter(RGBA& color) {

        anSDL2ImagePtr->_lineRGBA(getBallCenter().getX() - 10, getBallCenter().getY(), getBallCenter().getX() + 10, getBallCenter().getY(), color.getR(), color.getG(), color.getB(), color.getA());
        anSDL2ImagePtr->_lineRGBA(getBallCenter().getX(), getBallCenter().getY() - 10, getBallCenter().getX(), getBallCenter().getY() + 10, color.getR(), color.getG(), color.getB(), color.getA());
        anSDL2ImagePtr->_circleRGBA(getBallCenter().getX(), getBallCenter().getY(), 10, color.getR(), color.getG(), color.getB(), color.getA());
    }

    void initButtons() {

        SDL_Surface * calibrationButtonImage = IMG_Load("./button_calibrate_no_glow_small.png");
        SDL_Surface * calibrationButtonPressedImage = IMG_Load("./button_calibrate_glow_small.png");

        calibrationButton = new Button<CalibrationButtonEventHandler<XBOX360GamepadClient> > ();
        calibrationButton->setCaption("calibration");
        calibrationButton->setCaptionXoffset(-25);
        calibrationButton->setTexture(SDL_CreateTextureFromSurface(anSDL2ImagePtr->getRenderer(), calibrationButtonImage));
        calibrationButton->setMousePressedTexture(SDL_CreateTextureFromSurface(anSDL2ImagePtr->getRenderer(), calibrationButtonPressedImage));
        calibrationButton->setMouseOverTexture(calibrationButton->getTexture());
        calibrationButton->setDimensions(calibrationButtonImage->w, calibrationButtonImage->h);
        calibrationButton->setPosition(width - calibrationButton->getWidth(), height - calibrationButton->getHeight());
        calibrationButtonEventHandler = new CalibrationButtonEventHandler<XBOX360GamepadClient > (this);
        calibrationButton->addEventHandler(calibrationButtonEventHandler);
    }

    void initDataPacket() {

        aXBOX360DataPacket.clearEventMask();
        aXBOX360DataPacket.clear();
        aXBOX360DataPacket.setLeftStickDeadZoneX(500);
        aXBOX360DataPacket.setLeftStickDeadZoneY(500);
        aXBOX360DataPacket.setRightStickDeadZoneX(1000);
        aXBOX360DataPacket.setRightStickDeadZoneY(1000);
    }

    void initCalibrationProgressBar() {
        //calibration duration set to 300 frames 
        aCalibration = new Calibration(aSynchedCamera.getDepthFrameHeight() * aSynchedCamera.getDepthFrameWidth(), 300);
        aCalibration->getProgressBar().setWidth(anSDL2ImagePtr->getWidth() / 2);
        aCalibration->getProgressBar().setHeight(anSDL2ImagePtr->getHeight() / 5);
        aCalibration->getProgressBar().setPosition(aCalibration->getProgressBar().getWidth() / 2, (anSDL2ImagePtr->getHeight() / 2) - (aCalibration->getProgressBar().getHeight()));
        aCalibration->getProgressBar().setColor(100, 100, 100, 100);
        aCalibration->getProgressBar().setNumSteps(aCalibration->getNumFrames());

        liberationTrueTypeFont = anSDL2ImagePtr->openTrueTypeFont("/usr/share/fonts/truetype/liberation/LiberationSerif-Bold.ttf", 32);
        if (liberationTrueTypeFont == nullptr) {

            cout << "could not load the true type font" << endl;
        }
        SDL_Color textColor = {255, 255, 255};
        SDL_Surface *surf = TTF_RenderText_Blended(liberationTrueTypeFont, "CALIBRATING...", textColor);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(anSDL2ImagePtr->getRenderer(), surf);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture, 200);
        aCalibration->getProgressBar().setText(texture);
        SDL_FreeSurface(surf);
    }

    class SDL2ImageWindowEventHandler : public WindowEventhandler {
    public:

        SDL2ImageWindowEventHandler() {

        }

        virtual ~SDL2ImageWindowEventHandler() {

        }

        void onEnter() {

            cout << "SDL_WINDOWEVENT_ENTER" << endl;
        }

        SDL2Image* getWindow() {

            return image;
        }

        void setWindow(SDL2Image* image) {

            this->image = image;
        }

        void onClose() {

            cout << "SDL_WINDOWEVENT_CLOSE" << endl;
        }

        void onExposed() {

            cout << "SDL_WINDOWEVENT_EXPOSED" << endl;
        }

        void onFocusGained() {

            cout << "SDL_WINDOWEVENT_FOCUS_GAINED" << endl;
        }

        void onFocusLost() {

            cout << "SDL_WINDOWEVENT_FOCUS_LOST" << endl;
        }

        void onHidden() {

            cout << "SDL_WINDOWEVENT_HIDDEN" << endl;
        }

        void onLeave() {

            cout << "SDL_WINDOWEVENT_LEAVE" << endl;
        }

        void onMaximized() {

            cout << "SDL_WINDOWEVENT_MAXIMIZED" << endl;
        }

        void onMinimized() {

            cout << "SDL_WINDOWEVENT_MINIMIZED" << endl;
        }

        void onMoved() {

            cout << "SDL_WINDOWEVENT_MOVED" << endl;
        }

        void onResized() {

            cout << "SDL_WINDOWEVENT_RESIZED" << endl;
        }

        void onRestored() {

            cout << "SDL_WINDOWEVENT_RESTORED" << endl;
        }

        void onShown() {

            cout << "SDL_WINDOWEVENT_SHOWN" << endl;
        }

        void onSizeChanged() {
            cout << "SDL_WINDOWEVENT_SIZE_CHANGED" << endl;
        }

    private:
        SDL2Image* image;
    } windowEventHandler;
};


#endif /* XBOX360GAMEPADCLIENT_H */

