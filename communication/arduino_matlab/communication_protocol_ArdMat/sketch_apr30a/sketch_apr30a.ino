void setup() 
{
  

}

void loop()
{



       if ( Serial.available() )
       {

          float tag;
          tag =Serial.parseFloat(); 
          if (abs(tag - 111.1) <= 1.0e-05)
          {
              Serial.println("RighT");
              right_message_arrived=1;
              state = Waiting_variables;
          }


          Serial.println("s"); 
          Serial.println(prop1_temprature);
          Serial.println(heater_temperature);
          Serial.println(Velocity_m_per_s);
          
}
