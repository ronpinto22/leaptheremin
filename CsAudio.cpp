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

#include "CsAudio.h"

#define CSD_FILE "oscils.csd"

uintptr_t csThread(void *data);

int CsAudio::initializeAudio(int argc,char** argv) { 

	//int finish;

	/*char filename[11];
	const char* p=CSD_FILE;
	for(int i=0;(filename[i]=p[i]);i++);

	argv[0]=filename;
	argv[1]=filename;*/

	/*finish=csoundInitialize(&argc, &argv, 0);  

	if(finish<0){
		printf("\nError initializing CSOUND");		
		exit(0);
	}*/

	ud.csound=csoundCreate(NULL);  
	if(ud.csound == NULL){
		printf("\nError creating CSOUND");
		exit(0);
	}
	ud.result=csoundCompile(ud.csound,argc,argv);

	if(!ud.result)  {  
		ud.PERF_STATUS=1; 
		ThreadID = csoundCreateThread(csThread, (void*)&ud); 
	} else { 
		return 0; 
	}  

	if(csoundGetChannelPtr(ud.csound,&pvalue, "pitch", CSOUND_INPUT_CHANNEL | CSOUND_CONTROL_CHANNEL)!=0) printf("\nError getting control channel");
	if(csoundGetChannelPtr(ud.csound,&vvalue, "volume", CSOUND_INPUT_CHANNEL | CSOUND_CONTROL_CHANNEL)!=0) printf("\nError getting control channel");
	*pvalue=(MYFLT)0.0;	
	*vvalue=(MYFLT)0.0;
	return 1; 
} 

int CsAudio::play(double pitch,double volume){
	*pvalue=(MYFLT)pitch;
	*vvalue=(MYFLT)volume;
	return 1;
}

void CsAudio::destroy(){
	ud.PERF_STATUS=0;
	csoundDestroy(ud.csound);
}

CsAudio::~CsAudio(){
	destroy();
}

//performance thread function
uintptr_t csThread(void *data) 
{ 
  t_userdata* udata = (t_userdata*)data; 
      if(!udata->result) 
        { 
        while((csoundPerformKsmps(udata->csound) == 0) &&(udata->PERF_STATUS==1)); 
    	csoundDestroy(udata->csound); 
        }        
  udata->PERF_STATUS = 0;    
  return 1; 
}  
