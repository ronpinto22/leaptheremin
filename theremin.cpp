/******************************************************************************\
* Copyright (C) 2012-2013 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#include <iostream>
#include <pthread.h>
#include "Leap.h"
#include "StkAudio.h"

#define FLOOR 200
#define FREQ_M 6
#define VOLUME_M 0.0025

using namespace Leap;

class ThereminController : public Listener {
  private:
    StkAudio* audio;
    float freq;
    float volume;
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    void setAudio(StkAudio* audio);
    ThereminController();
    void play();
};

ThereminController::ThereminController() : Listener() {
  freq=440.0;
  volume=0.001;
  audio=NULL;
}

void ThereminController::setAudio(StkAudio* audio) {
  this->audio=audio;
}

void ThereminController::play(){
  if(audio)
  	audio->play(freq,volume);
}

void ThereminController::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void ThereminController::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
}

void ThereminController::onDisconnect(const Controller& controller) {
  //Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void ThereminController::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void ThereminController::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
  const Frame frame = controller.frame();
  /*std::cout << "Frame id: " << frame.id()
            << ", timestamp: " << frame.timestamp()
            << ", hands: " << frame.hands().count()
            << ", fingers: " << frame.fingers().count()
            << ", tools: " << frame.tools().count()
            << ", gestures: " << frame.gestures().count() << std::endl;
  */

  if (frame.hands().count()>=2) {
    // Get the first hand
    const Hand vHand = frame.hands().leftmost();
    const Hand pHand = frame.hands().rightmost();

    freq=(pHand.palmPosition().x)*FREQ_M;
    volume=(vHand.palmPosition().y-FLOOR)*VOLUME_M;
    if(volume<0) volume=0;
    else if(volume>1) volume=1;
    if(freq<0) freq=0;

    //std::cout << "Frequency: " << freq << ", Volume: " << volume << std::endl;
  }
}

void ThereminController::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void ThereminController::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

ThereminController listener;
float flag=1;

void* audioThread(void *v){
  while(flag)
    listener.play();
  pthread_exit(0);
}

int main() {
  // Create a sample listener and controller

  StkAudio stkaudio;
  Controller controller;
  pthread_t audio;
  //Stk::setSampleRate( 44100.0 );
  //Stk::showWarnings( true );
  stkaudio.initializeAudio();
  listener.setAudio(&stkaudio);

  // Have the sample listener receive events from the controller
  controller.addListener(listener);
  pthread_create(&audio,NULL,audioThread,NULL);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();
  flag=0;
  pthread_join(audio,NULL);
  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}
