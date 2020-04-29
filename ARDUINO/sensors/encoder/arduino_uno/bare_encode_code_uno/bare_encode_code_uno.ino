//tested 

// ENCODER variables SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
      #define pinA 3
      #define pinB 2
      #define pinZ 5
      volatile int   aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
      volatile int   bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
      volatile int   ENCODER_CLICKS = 0;//this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
      int ANGLE;
// ENCODER variables eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee





//Main Setup Function--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Main Setup Function--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Main Setup Function--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
      // Setup encoder 
      pinMode(pinA, INPUT_PULLUP); // set pinA as an PID_SENSOR_INPUT, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
      pinMode(pinB, INPUT_PULLUP); // set pinB as an PID_SENSOR_INPUT, pulled HIGH to thxxe logic voltage (5V or 3.3V for most cases)
      attachInterrupt(digitalPinToInterrupt(pinB), PinA_ISR,  RISING); // set an interrupt on PinA_ISR, looking for a rising edge signal and executing the "PinA_ISR" Interrupt Service Routine (below)
      attachInterrupt(digitalPinToInterrupt(pinA), PinB_ISR,  RISING); // set an interrupt on PinB_ISR, looking for a rising edge signal and executing the "PinB_ISR" Interrupt Service Routine (below).


    //Serial setup
      Serial.begin(9600);

}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void loop()
{
  // put your main code here, to run repeatedly:
                      ANGLE = float(ENCODER_CLICKS) / 2000 * 360;
                      Serial.println(ENCODER_CLICKS);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
