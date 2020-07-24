delete(instrfindall);
com_name = find_arduino_com_windowsOS();
connection = serial(com_name,'BaudRate',2000000);
fopen(connection);
pause(1) % withouth this the serial print dont have enough time to reach arduino

send_tag = 222;
send_variable1=12;
send_variable2=44.4;
send_variable3=5542.2;

recieve_tag =111;
recieve_variable1=0;
recieve_variable2=0;
recieve_variable3=0;

% send_send_variables(connection,send_tag,send_variable1,send_variable2,send_variable3)
recieve_variable1_Array=[]
recieve_variable2_Array=[]
recieve_variable3_Array=[]
pause(1)


while(1==1)

        [recieve_variable1, recieve_variable2, recieve_variable3]=update_recive_variables(connection,recieve_tag,recieve_variable1,recieve_variable2,recieve_variable3);
         recieve_variable1_Array=[recieve_variable1_Array recieve_variable1 ];
         recieve_variable2_Array=[recieve_variable2_Array recieve_variable2 ];
         recieve_variable3_Array=[recieve_variable3_Array recieve_variable3 ];

end

