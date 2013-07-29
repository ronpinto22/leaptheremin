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


#include "SineWave.h"
#include <cstdlib>
#include "StkAudio.h"

using namespace stk;

int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *dataPointer )
{
  t_sine_w_volume* swv = (t_sine_w_volume*) dataPointer;
  SineWave *sine = swv->sine;
  register StkFloat *samples = (StkFloat *) outputBuffer;

  for ( unsigned int i=0; i<nBufferFrames; i++ )
    *samples++ = sine->tick()*(*(swv->volume));

  return 0;
}

int StkAudio::initializeAudio(){
  Stk::setSampleRate( 44100.0 );
  Stk::showWarnings( true );

  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 1;
  format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
  unsigned int bufferFrames = RT_BUFFER_SIZE;
  sineWVolume.sine=&sine;
  sineWVolume.volume=&_volume;
  try {
    dac.openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&sineWVolume );
  }
  catch ( RtError &error ) {
    error.printMessage();
    return 0;
  }

  play(0.0,0.0);

  try {
    dac.startStream();
  }
  catch ( RtError &error ) {
    error.printMessage();
    return 0;
  }
  
return 1;
}

int StkAudio::play(float freq, float volume){  
    try{
      sine.setFrequency(freq);
    } catch ( RtError &error ){
      error.printMessage();
    }
    _freq=freq;
    _volume=volume;
    return 0;
}


void StkAudio::destroy(){
    dac.closeStream();
}

StkAudio::~StkAudio(){
  destroy();
}
