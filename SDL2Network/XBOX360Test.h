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

#ifndef XBOX360TEST_H
#define XBOX360TEST_H
#include <SDL2Image.h>
#include <SDL2/SDL_image.h>
#include <SDL2_framerate.h>
#include <threadworker.h>
#include <thread.h>
#include <XBOX360Gamepad.h>
#include <XBOX360GamepadEventHandler.h>

using namespace std;

class XBOX360Test : public ThreadWorker {
public:

    XBOX360Test(int width, int height) : running(false), width(width), height(height) {
        anSDL2ImagePtr = new SDL2Image("XBOX360Test", 0, 0, getWidth(), getHeight());

    }

    XBOX360Test(const XBOX360Test& orig) {

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
        gamecontroller = SDL_GameControllerOpen(0);
        gamepad.addEventHandler(&gamepadEventhandler);
        this->setActive(true);
        mySDLEventhandlingThread.setThreadWorker(this);
        mySDLEventhandlingThread.start();
        this->running = true;
        while (this->running) {
            anSDL2ImagePtr->updateAcceleratedRenderer();
            anSDL2ImagePtr->paint();
        }
        mySDLEventhandlingThread.stop();
        this->setActive(false);
    }

    void execute() {
        while (SDL_PollEvent(&event)) {
            if (gamecontroller != NULL) {
                gamepad.processEvent(&event, gamecontroller);
            }

            switch (event.type) {
                case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                            cout << "SPACE" << endl;
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
                        cout << "x: " << event.
                                motion.x << " y: " << event.motion.y << endl;
                    }
                }
                    break;
            }
            break;
        }
    }

    virtual ~XBOX360Test() {

    }

private:
    bool running;
    int width;
    int height;
    Thread mySDLEventhandlingThread;
    SDL_Event event;
    SDL2Helper anSDL2Helper;
    SDL2Image* anSDL2ImagePtr;
    XBOX360GamepadEventHandler gamepadEventhandler;
    XBOX360Gamepad<XBOX360GamepadEventHandler> gamepad;
    SDL_GameController* gamecontroller;

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

#endif /* XBOX360TEST_H */

