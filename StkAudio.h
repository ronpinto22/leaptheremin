#ifndef THEREMIN_STKAUDIO_H
#define THEREMIN_STKAUDIO_H

#include "SineWave.h"
#include "RtWvOut.h"
#include <cstdlib>

using namespace stk;

class StkAudio {
  private:
    SineWave sine;
    RtWvOut *dac;
  public:
    StkAudio();
    int initializeAudio();
    int play(float freq, float volume);
    void destroy();
    ~StkAudio();
};

#endif
