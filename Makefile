PROGRAMS = theremin
RM = /bin/rm
SRC_PATH=.
vpath %.o $(OBJECT_PATH)

INCLUDE = 
ifeq ($(strip $(INCLUDE)), )
	INCLUDE = /usr/include/stk
endif
vpath %.h $(INCLUDE)

CC       = g++
CFLAGS   = -O3 -Wall
CFLAGS  += -I$(INCLUDE)
DEFS	= -D__UNIX_JACK__ -D__LITTLE_ENDIAN__
LIBRARY = -lstk -lm -lpthread -lLeap

%.o : $(SRC_PATH)/%.cpp
	$(CC) $(CFLAGS) $(DEFS) -c $(<) -o $(OBJECT_PATH)/$@

all : $(PROGRAMS)

$(OBJECTS) : Stk.h

clean : 
	$(RM) -f $(PROGRAMS) *.exe
	$(RM) -fR *~ *.dSYM

distclean: clean
	$(RM) Makefile

strip : 
	strip $(PROGRAMS)

theremin: theremin.cpp StkAudio.cpp
	$(CC) $(LDFLAGS) $(CFLAGS) $(DEFS) -o theremin theremin.cpp StkAudio.cpp $(LIBRARY)
