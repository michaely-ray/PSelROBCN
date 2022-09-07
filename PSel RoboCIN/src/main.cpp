#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500

//include an interruption with button 
InterruptIn button(BUTTON1);
DigitalOut led(LED2);
int counter=0;
static BufferedSerial serial_port(USBTX, USBRX, 230400);

FileHandle *mbed::mbed_override_console(int fd)
{
   return &serial_port;
}

void controller1();

int main()
{   
    button.rise(&controller1); //The Led will torn on or off and the counter adds one when the button trigger 

    while (true) {
        printf("Led is now %d\n", led.read());
        printf("contador de clicks %d\n", counter);
        ThisThread::sleep_for(BLINKING_RATE);
    }   
}
void controller1() {
    led=!led;
    counter++;
}