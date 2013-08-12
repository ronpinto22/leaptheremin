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

#ifndef THEREMIN_CSAUDIO_H
#define THEREMIN_CSAUDIO_H

#define  USE_DOUBLE 
#include <unistd.h>
#include <stdio.h> 
#include <csound/csound.h>
#include <cstdlib>
#include "audiolib.h"


struct t_userdata { 
	int result; 
	CSOUND* csound; 
	int PERF_STATUS; 
}; 

class CsAudio : public AudioLib {
  private:    
	t_userdata ud;
	MYFLT* pvalue;
	MYFLT* vvalue;
	MYFLT* wvalue;
	void* ThreadID; 
  public:
    int initializeAudio(int argc,char**argv);
    int play(double freq, double volume);
    int setSound(int waveshape);
    void destroy();
    ~CsAudio();
};

#endif
