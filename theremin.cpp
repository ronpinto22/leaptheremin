/*****************************************************************************\
 * This file is part of LeapTheremin.                                        *
 *                                                                           *
 * LeapTheremin is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation, either version 3 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * LeapTheremin is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License         *
 * along with LeapTheremin.  If not, see <http://www.gnu.org/licenses/>.     *
\*****************************************************************************/
#include <iostream>
#include <unistd.h>
#include "Leap.h"
#include "CsAudio.h"

//This constants will modify controller behavior
//FLOOR sets the base height to measure volume. Defaults to 100 milimeters
//FREQ_M sets frequence multiplier. Higher values will increase theremin's sensitivity
//VOLUME_M sets volume multipliyer. Have in mind that valid volume range goes from 0.0 to 1.0 
#define THMN_FLOOR 100
#define THMN_FREQ_M 0.6
#define THMN_VOLUME_M 100

using namespace Leap;

class ThereminController : public Listener {
  private:
    AudioLib* audio;
    double freq;
    double volume;
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    void setAudio(AudioLib* audio);
    ThereminController();
    void play();
};

ThereminController::ThereminController() : Listener() {
  freq=440.0;
  volume=0.001;
  audio=NULL;
}

void ThereminController::setAudio(AudioLib* audio) {
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

    //freq=(pHand.palmPosition().x)*THMN_FREQ_M-200;
    volume=(vHand.palmPosition().y-THMN_FLOOR)*THMN_VOLUME_M;

    double x=0,y=0,z=0;
    x=pHand.palmPosition().x;
    y=(pHand.palmPosition().y-THMN_FLOOR);
    z=0;//abs(pHand.palmPosition().z);
    /*int fingerCount;
    
    
    fingerCount=pHand.pointables().count();
    if(fingerCount){
	    for(int i=0; i<fingerCount;i++){
	    	x+=abs(pHand.pointables()[i].tipPosition().x);
	    	y+=abs(pHand.pointables()[i].tipPosition().y);
	    	z+=abs(pHand.pointables()[i].tipPosition().z);	
	    }
	    x=x/fingerCount;
	    y=y/fingerCount-THMN_FLOOR;
	    z=z/fingerCount;

	    std::cout << "X: " << x << " Y: " << y << " Z: " << z << std::endl;


	    volume=(vHand.palmPosition().y-THMN_FLOOR)*THMN_VOLUME_M;*/
	    
	    freq=(x+y+z)*THMN_FREQ_M;
	    if(volume<0) volume=0;
	    //else if(volume>1) volume=1;
	    if(freq<0) freq=0;
	    play();
	    //std::cout << "Frequency: " << freq << ", Volume: " << volume << std::endl;
    //}
  }
}

void ThereminController::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void ThereminController::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

ThereminController listener;

int main(int argc,char** argv) {

  CsAudio audio;
  Controller controller;
  audio.initializeAudio(argc,argv);
  listener.setAudio(&audio);

  // Have the sample listener receive events from the controller
  controller.addListener(listener);

  // Keep this process running until Enter is pressed
  std::cout << "Press any key to exit... " << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}
