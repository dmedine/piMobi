# set this to your preferred cross compiler
# leave empty if compiling natively on the pi
CROSS_PRE=#arm-bcm2708-linux-gnueabi-

CC=$(CROSS_PRE)gcc


INCLUDE=-I./ -I./ads1015drvr

# change the second path to point to your copy of liblslARM

LIBPATH=-L./ -L./ads1015drvr
LIBS= -pthread -llsl64 #-lads1015drvr -lpwm -llslARM

all: piMobi #libpwm.so

#libpwm.so:
#	$(CC) -shared -o libpwm.so -fPIC pwm.c

piMobi:
	$(CC)  -o piMobi piMobi.c -Wl,-rpath ./ $(INCLUDE) $(LIBPATH) $(LIBS) 


clean:
	rm piMobi
