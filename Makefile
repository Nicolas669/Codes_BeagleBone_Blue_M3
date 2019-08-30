CC = gcc
EXEC = slide
CFLAGS = -DBB_BLUE

all: clean $(EXEC)

$(EXEC):  gpio.o motor.o deplacement.o main.o adc.o pwm.o

	$(CC) -o $(EXEC) main.o gpio.o deplacement.o motor.o adc.o pwm.o

gpio.o:

	$(CC) -o gpio.o -c gpio.c $(CFLAGS)
	
motor.o: 
	$(CC) -o motor.o -c motor.c $(CFLAGS)
	
deplacement.o:
	$(CC) -o deplacement.o -c deplacement.c $(CFLAGS)

main.o:
	$(CC) -o main.o -c main.c $(CFLAGS)

adc.o:
	$(CC) -o adc.o -c adc.c $(CFLAGS)

pwm.o:
	$(CC) -o pwm.o -c pwm.c $(CFLAGS)
		
clean:

	rm -rf *.o 
	rm -rf $(EXEC)
	
