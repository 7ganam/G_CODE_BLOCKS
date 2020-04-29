//communication variables ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
int RECIEVE_TAG=555;
float RECIEVED_VAR_1=0;
float RECIEVED_VAR_2=0;
float RECIEVED_VAR_3=0;

int SEND_START_TAG=666;

float SEND_VAR_1=0;
float SEND_VAR_2=0;
float SEND_VAR_3=0;

//communication variabse eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee


void setup() 
{
  Serial.begin(9600);
}



void loop() 
{
 
   update_recieved_variables(); 

  //send the recieved data back 
   SEND_VAR_1=RECIEVED_VAR_1;
   SEND_VAR_2=RECIEVED_VAR_2;
   SEND_VAR_3=RECIEVED_VAR_3;
   
   send_send_variables();
 
}





// communication functions 
      void update_recieved_variables()
      {
      
          if ( Serial.available() )
             {
                int recieved_tag =(int)Serial.parseFloat(); // the expected input is in the format of four numbers separated by any charachter EX: 145*11*18*19 .. parse float reads one number at a time. the first number is the tag.
                if (RECIEVE_TAG == recieved_tag )
                {
                  RECIEVED_VAR_1= Serial.parseFloat();
                  RECIEVED_VAR_2= Serial.parseFloat();
                  RECIEVED_VAR_3= Serial.parseFloat();  
                }
              }
              
      }
      
      void send_send_variables()
      {
      
            String String_To_Send;
            String_To_Send=String(SEND_START_TAG);
            String_To_Send.concat(",");
            String_To_Send.concat(String(SEND_VAR_1));
            String_To_Send.concat(",");
            String_To_Send.concat(String(SEND_VAR_2));
            String_To_Send.concat(",");                          
            String_To_Send.concat(String(SEND_VAR_3));
            String_To_Send.concat('\n');
            Serial.print(String_To_Send); 
      
      
      }
