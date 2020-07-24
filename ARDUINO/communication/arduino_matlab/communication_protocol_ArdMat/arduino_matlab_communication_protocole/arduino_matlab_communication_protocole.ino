//communication variables ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
int RECIEVE_TAG=222;
float RECIVE_VAR1=0;
float RECIVE_VAR2=0;
float RECIVE_VAR3=0;

int SEND_TAG=111;
float SEND_VAR1=0;
float SEND_VAR2=0;
float SEND_VAR3=0;
//communication variabse eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee


void setup() 
{
    Serial.begin(9600);
}



void loop()
{
      update_recieve_variables();
       
      SEND_VAR1=RECIVE_VAR1;
      SEND_VAR2=RECIVE_VAR2;
      SEND_VAR3=RECIVE_VAR3;
      
      send_send_variables();

}



// communication functions 
void update_recieve_variables()
{
 if ( Serial.available() )
 {
    int tag;
    tag =int(Serial.parseFloat()); 
    if (tag==RECIEVE_TAG)
    {
            RECIVE_VAR1=Serial.parseFloat();
            RECIVE_VAR2= Serial.parseFloat();
            RECIVE_VAR3= Serial.parseFloat();
    }

}
}
void send_send_variables()
{
      Serial.println(SEND_TAG); 
      Serial.println(SEND_VAR1);
      Serial.println(SEND_VAR2);
      Serial.println(SEND_VAR3);

}
