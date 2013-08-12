PROGRAMS = theremin
RM = /bin/rm
SRC_PATH=.
vpath %.o $(OBJECT_PATH)

INCLUDE = 
ifeq ($(strip $(INCLUDE)), )
	INCLUDE = /usr/include/csound
endif
vpath %.h $(INCLUDE)

CC       = g++
CFLAGS   = -O3 -Wall
CFLAGS  += -I$(INCLUDE)
DEFS	= -D__LINUX_ALSA__ -D__LITTLE_ENDIAN__
LIBRARY = -Llib/linux -lcsound64 -lLeap

%.o : $(SRC_PATH)/%.cpp
	$(CC) $(CFLAGS) $(DEFS) -c $(<) -o $(OBJECT_PATH)/$@

all : $(PROGRAMS)

clean : 
	$(RM) -f $(PROGRAMS) *.exe
	$(RM) -fR *~ *.dSYM

distclean: clean
	$(RM) Makefile

strip : 
	strip $(PROGRAMS)

theremin: theremin.cpp CsAudio.cpp
	$(CC) $(LDFLAGS) $(CFLAGS) $(DEFS) -o theremin theremin.cpp CsAudio.cpp $(LIBRARY)
