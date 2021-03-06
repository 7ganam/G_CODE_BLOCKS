// PID control of DC motor experiment.
#include <stdio.h>

//PID variables and Control SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS       
#include <PID_v1.h>

double  Kp =0.025;
double  Ki = 0.00;
double  Kd = .0005;
double  CONTROL_GOAL_SETPOINT =90;
double  PID_SENSOR_INPUT, PID_OUTPUT_COMMAND; //Define Variables we'll be connecting to
boolean set_pid = false;


float CYCLE_PERCENTAGE = 80;     //variable used in the function that generats the control signal .. ( I should make it passed to the function as aparamter later..no need for it to be a global variable) 
PID myPID(&PID_SENSOR_INPUT, &PID_OUTPUT_COMMAND, &CONTROL_GOAL_SETPOINT, Kp, Ki, Kd, DIRECT);


//PID variables and Control eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee


//MOTOR DRIVER variables  SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
    #define clock_wise_ENA 10
    #define anti_clock_wise_ENA 11
   
//MOTOR DRIVER variables eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee


// ENCODER variables SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
      #define pinA 3
      #define pinB 2
      #define pinZ 5
      volatile int   aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
      volatile int   bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
      volatile long int   ENCODER_CLICKS = 0;//this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
      long int ANGLE;
// ENCODER variables eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee



//#######################################################################################//

void setup()
{
  // Setup encoder 
      pinMode(pinA, INPUT_PULLUP); // set pinA as an PID_SENSOR_INPUT, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
      pinMode(pinB, INPUT_PULLUP); // set pinB as an PID_SENSOR_INPUT, pulled HIGH to thxxe logic voltage (5V or 3.3V for most cases)
      attachInterrupt(digitalPinToInterrupt(pinB), PinA_ISR,  RISING); // set an interrupt on PinA_ISR, looking for a rising edge signal and executing the "PinA_ISR" Interrupt Service Routine (below)
      attachInterrupt(digitalPinToInterrupt(pinA), PinB_ISR,  RISING); // set an interrupt on PinB_ISR, looking for a rising edge signal and executing the "PinB_ISR" Interrupt Service Routine (below).

  // motor driver setup
      pinMode(clock_wise_ENA, OUTPUT);
      pinMode(anti_clock_wise_ENA, OUTPUT);
     
      

    Serial.begin(9600);

    
  //turn the PID on
      myPID.SetOutputLimits(-1,1);
      myPID.SetMode(AUTOMATIC);
      myPID.SetMode(AUTOMATIC);
      myPID.SetSampleTime(50);


}

//#######################################################################################//
void loop()
{


    ANGLE = float(ENCODER_CLICKS) / 2000 * 360;
    PID_SENSOR_INPUT = ANGLE;
    myPID.Compute();
    give_command_to_motor_drive(PID_OUTPUT_COMMAND);
    Serial.print(CONTROL_GOAL_SETPOINT);
    Serial.print(",");              //seperator
    Serial.println(ANGLE);


}

//#######################################################################################//



void give_command_to_motor_drive(double pid_output)  
//the blue motor driver version .. change this function based on your motor driver
//this function depends on the fact that the pid output is limited between -1 1 
{
  
  double dead_band = 0.1; //identify the deadband pwm value and divide it by 255 to find this value

//      //remap the output to delete deadband (this part needs further investigation later)
//      if(pid_output > 0)
//      {
//         pid_output=pid_output + dead_band;
//      }
//      else if(pid_output < 0)
//      {
//         pid_output=pid_output - dead_band;
//      }
      
      //trim output greater than 1
       if (pid_output > 1)
        {
          pid_output = 1;
        }
        if (pid_output < -1)
        {
          pid_output = -1;
        }

      //this part depends on the interface of the motor driver.. change it for your motor driver to change directions.
      int signed_pwm_output=pid_output/1*255;
      if (signed_pwm_output > 0 )
      {
          analogWrite(anti_clock_wise_ENA ,0);
          analogWrite(clock_wise_ENA , abs(signed_pwm_output));
      }
    
      if (signed_pwm_output < 0 )
      {
        analogWrite(anti_clock_wise_ENA , abs(signed_pwm_output));
        analogWrite(clock_wise_ENA , 0);

  }

}


//encoder functions
      inline  void PinA_ISR()
              {  
                cli(); //stop interrupts happening before we read pin values
                int a= digitalRead(pinA);
                int b= digitalRead(pinB);
                if (a==1 && b==1 && aFlag)
                {
                  //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
                  ENCODER_CLICKS --; //decrement the encoder's position count
                  analogWrite(5 , ENCODER_CLICKS*2/360*255);
                  bFlag = 0; //reset flags for the next turn
                  aFlag = 0; //reset flags for the next turn
                }
                else if (b==1 && a==0) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
                sei(); //restart interrupts
              }
              
        inline void PinB_ISR()
              {
                
                  cli(); //stop interrupts happening before we read pin values
                  int a= digitalRead(pinA);
                  int b= digitalRead(pinB);
                  if (a && b && bFlag)
                  { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
                    ENCODER_CLICKS ++; //increment the encoder's position count
                    analogWrite(5 , ENCODER_CLICKS*2/360*255);
                    bFlag = 0; //reset flags for the next turn
                    aFlag = 0; //reset flags for the next turn
                  }
                  else if (a==1 && b==0) aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
                  sei(); //restart interrupts
              }
