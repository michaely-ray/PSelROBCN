#include "mbed.h"

float vel = 0;
float e = 0;
float eant = 0;
float Vatual = 0;
float Vdes = 0; 
float aatual = 0;
float aant = 0;
float dt = 0;


float prop = 0;
float derr = 0;
float deri = 0;
float inte = 0;
float calc = 0;

float kp = 0, 730;
float kd = 0, 008;
float ki = 1, 247;

void Controller( ) {
     
    vel = Vatual ;
    e = Vdes - vel ;   //caalculate error   (vdes= value set) (vel= value wish)

    prop = (e * kp)/10 ;   // proporcional

    aatual = ((e + eant) / 2) * dt; 
    aatual = e * dt; 
    aatual = aatual + aant;
    inte = (aatual * ki)/100 ;                    // integral

    derr = (e - eant) / dt;
    deri = derr * kd;                             // derivative

    calc = prop + inte + deri;                   // calculate PID

 //   Set PWM with the new PID value
    eant = e; // the last error
    aant = aatual; //last value
    vel = 0;   //Reset the value until a new measure in dt+1    
}