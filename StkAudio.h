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

#ifndef THEREMIN_STKAUDIO_H
#define THEREMIN_STKAUDIO_H

#include "SineWave.h"
#include "RtWvOut.h"
#include <cstdlib>

using namespace stk;

struct t_sine_w_volume {
  SineWave* sine;
  float* volume;
};


class StkAudio {
  private:
    SineWave sine;
    RtAudio dac;
    float _freq;
    float _volume;
    RtAudio::StreamParameters parameters;
    RtAudioFormat format;
    t_sine_w_volume sineWVolume;
  public:
    int initializeAudio();
    int play(float freq, float volume);
    void destroy();
    ~StkAudio();
};

#endif
