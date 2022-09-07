#include "mbed.h"
// Blinking rate in milliseconds
#define BLINKING_RATE     2000ms

InterruptIn sensor(PB_1);
// PwmOut pwm(PA_8);
DigitalOut test(PA_8); //Using a LED indicator

float period = 0.001f;
Timer t;
uint8_t counter_pulse = 0;
uint64_t current_p = 0, last_t = 0;
float f = 0;

void frequenceCounterISR();

int main() {

    t.start();
    sensor.rise(NULL);
    while(1){
        if (current_p != 0){
            f = 1000000 * ((float)(counter_pulse)/current_p); // Calculate frequency Hz
        }
        else{
        f = 0;
    }
        // Reset pulse parameters
        counter_pulse = 0;                          
        current_p = 0;                  
        last_t = t.elapsed_time().count();
        printf("%d\n", int(last_t));        
        sensor.rise (&frequenceCounterISR); // start interrupt
        printf("%d\n", int(f*30)); //speed in RPM
        ThisThread::sleep_for(500ms);  // Wait new measure
    }   
}

void frequenceCounterISR(){
    counter_pulse++;
    printf("%d\n", int(counter_pulse));                  // Counter of pulse
    current_p += t.elapsed_time().count() - last_t;     // Size of pulse
    last_t = t.elapsed_time().count();                  // Reset timer     
    test = !test;
}