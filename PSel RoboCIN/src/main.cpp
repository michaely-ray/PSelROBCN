#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     2000


DigitalOut led(LED1); //Include LED as digital output
int counter=0;

static BufferedSerial serial_port(USBTX, USBRX, 230400);

FileHandle *mbed::mbed_override_console(int fd)
{
   return &serial_port;
}


int main()
{
    while (true) {
        led=!led; //Reading and change the status led
        if(led.read()){
            counter++;
            printf("Blink! LED is now %d\n", counter);
        } 
    
        ThisThread::sleep_for(BLINKING_RATE); //Delay
    }   
}