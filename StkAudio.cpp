// rtsine.cpp STK tutorial program

#include "SineWave.h"
#include "RtWvOut.h"
#include <cstdlib>
#include "StkAudio.h"

using namespace stk;

int StkAudio::initializeAudio(){
  Stk::setSampleRate( 44100.0 );
  Stk::showWarnings( true );

  try {
    dac = new RtWvOut ( 1 );
  } catch (StkError & ) {
    return 0;
  }

  return 1;
}

int StkAudio::play(float freq, float volume){
  try {
    sine.setFrequency(freq);
    dac->tick( sine.tick() * volume );
  } catch (StkError & ) {
    destroy();
    return 0;
  }
  return 1;
}

void StkAudio::destroy(){
  if(dac)
    delete dac;
}

StkAudio::~StkAudio(){
  destroy();
}

StkAudio::StkAudio(){
  dac=0;
}


