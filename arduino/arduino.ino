#include <SoftwareSerial.h>
#include <virtuabotixRTC.h> //Library used

SoftwareSerial esp8266(2, 3); // RX, TX

struct pin
{
  int pinNum;
  int hourOn = 99;
  int hourOff = 99;
  int minuteOn = 99;
  int minuteOff = 99;
  //boolean onOff=99;

  boolean timeSet = false;
  boolean timer = false;

} p[3];

int add = 0;

//typedef struct pin ;

//Wiring SCLK -> 6, I/O -> 7, CE -> 8
//Or CLK -> 6 , DAT -> 7, Reset -> 8

virtuabotixRTC myRTC(8, 7, 6); //If you change the wiring change the pins here also

void setup()
{

  //**relay*************************************************************
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  Serial.begin(9600);    // serial port used for debugging
  esp8266.begin(115200); // your ESP's baud rate might be different

  // sendToWifi("AT");
  //esp8266.println("AT");

  // esp8266.println("AT");
  delay(200);
  esp8266.println("AT+CWMODE=2");
  delay(200);
  esp8266.println("AT+CIPMUX=1");
  delay(200);
  esp8266.println("AT+CIPSERVER=1,333");
  delay(200);

  //AT+CWSAP="ESP","password",1,4
  //AT+CWSAP="Smart Controller Module","scm12345",1,4
  // esp8266.println("AT+CWJAP=\"Fenil\",\"48964896\"");
  //*******************************************************************

  //**time*****************************************************************
  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  // myRTC.setDS1302Time(40, 26, 13, 6, 27, 5, 2018); //Here you write your actual time/date as shown above
  //but remember to "comment/remove" this function once you're done
  //The setup is done only one time and the module will continue counting it automatically

  //*******************************************************************
}

void loop()
{

  //**relay*************************************************************
  //delay(10);

  // listen for communication from the ESP8266 and then write it to the serial monitor
  if (esp8266.available())
  {

    // char c=(char)esp8266.read();
    //Serial.write(c); c=0;
    String s = "";
    while (esp8266.available())
    {
      delay(1);
      s = s + (char)esp8266.read(); // read the next character.
                                    //Serial.write( esp8266.read() );
    }

    if (s.length() > 0)
    {
      char a[s.length()];

      s.toCharArray(a, s.length());

      // for(int i=0;i<s.length();i++)

      Serial.print(s);
      //Serial.write(a);  // writes data to the serial monitor }
      /* String firstOn="!";
           String firstOff="%";

           String secondOn="b";
           String secondOff="A";

           String thirdOn="T";
           String thirdOff="X";

           String fourthOn="v";
           String fourthOff="z";*/

      char firstOn = '!';
      char firstOff = '%';

      char secondOn = 'b';
      char secondOff = 'A';

      char thirdOn = 'T';
      char thirdOff = 'X';

      char fourthOn = 'v';
      char fourthOff = 'z';

      //           Serial.print(s.indexOf(p));
      //    Serial.print(s.lastIndexOf(p));

      // Serial.print("!");
      // Serial.print(s.indexOf(secondOff));
      //   Serial.print("!");
      //  Serial.print(s.lastIndexOf(secondOff));
      //   Serial.print("!");

      //if(s.indexOf(p)==11)
      //    Serial.print("!1fenil1!!");
      // if( a[11]=='a')
      //  Serial.print(s.indexOf(firstOn));
      // Serial.print("!!2fenil2!!");
      //                 if(s.indexOf(t)!=-1)
      //11,15   //11,20                 {   Serial.write("!3fenil3!");  }

      /* if( s.indexOf(firstOn)>15 && s.indexOf(firstOn)<19 )
                       {   digitalWrite(10,LOW);  }
                    else if( s.indexOf(firstOff)>15 && s.indexOf(firstOff)<19 )
                       {   digitalWrite(10,HIGH);  }

                     else if( s.indexOf(secondOn)>15 && s.indexOf(secondOn)<19 )
                       {   digitalWrite(11,LOW);  }
                   else  if( s.indexOf(secondOff)>15 && s.indexOf(secondOff)<19 )
                       {   digitalWrite(11,HIGH);  }

                      else if( s.indexOf(thirdOn)>15 && s.indexOf(thirdOn)<19 )
                       {   digitalWrite(12,LOW);  }
                    else if( s.indexOf(thirdOff)>15 && s.indexOf(thirdOff)<19 )
                       {   digitalWrite(12,HIGH);  }

                    else  if( s.indexOf(fourthOn)>15 && s.indexOf(fourthOn)<19 )
                       {   digitalWrite(13,LOW);  }
                    else if( s.indexOf(fourthOff)>15 && s.indexOf(fourthOff)<19 )
                       {   digitalWrite(13,HIGH);  }*/

      if (a[18] == firstOn && a[19] == firstOn || a[19] == firstOn && a[20] == firstOn)
      {
        digitalWrite(10, LOW);
      }
      else if (a[18] == firstOff && a[19] == firstOff || a[19] == firstOff && a[20] == firstOff)
      {
        digitalWrite(10, HIGH);
      }

      else if (a[18] == secondOn && a[19] == secondOn || a[19] == secondOn && a[20] == secondOn)
      {
        digitalWrite(11, LOW);
      }
      else if (a[18] == secondOff && a[19] == secondOff || a[19] == secondOff && a[20] == secondOff)
      {
        digitalWrite(11, HIGH);
      }

      else if (a[18] == thirdOn && a[19] == thirdOn || a[19] == thirdOn && a[20] == thirdOn)
      {
        digitalWrite(12, LOW);
      }
      else if (a[18] == thirdOff && a[19] == thirdOff || a[19] == thirdOff && a[20] == thirdOff)
      {
        digitalWrite(12, HIGH);
      }

      else if (a[18] == fourthOn && a[19] == fourthOn || a[19] == fourthOn && a[20] == fourthOn)
      {
        digitalWrite(13, LOW);
      }
      else if (a[18] == fourthOff && a[19] == fourthOff || a[19] == fourthOff && a[20] == fourthOff)
      {
        digitalWrite(13, HIGH);
      }

      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      int temp = s.indexOf("n");
      int temp2 = s.indexOf("f");
      int temp3 = s.indexOf("r");
      //int temp4=s.indexOf("j");
      /* int x=(int)(a[temp+3]);
             Serial.print("||");
            Serial.print(temp);
            Serial.print("||");
            Serial.print(a[12]);
            Serial.print("||");
            Serial.print(a[12+1]);
            Serial.print("||");
            Serial.print(a[12+2]);
            Serial.print("||");
            Serial.print((int)(a[temp+3] - 48));
            Serial.print("||");
            Serial.print((int)(a[temp+4] - 48));
            Serial.print("||");
            Serial.print((int)(a[temp+5] - 48));
            Serial.print("||");
            Serial.print((int)(a[temp+6] - 48));
            Serial.print("||");
            Serial.print((int)(a[temp+7] - 48));
            Serial.print("||");
            Serial.print((int)(a[temp+8] - 48));
            Serial.print("||");
            Serial.print(((int)(a[temp+3] - 48)+(int)(a[temp+4] - 48)+(int)(a[temp+5] - 48)+(int)(a[temp+6] - 48)));
            Serial.print("||");
            Serial.print(( ((int)(a[temp+7] - 48)*10)+(int)(a[temp+8] - 48) ));

            Serial.print("||");
            Serial.print((((int)(a[temp+2])=='N')));
             Serial.print("||");
            Serial.print(( ((int)(a[temp+3] - 48)+(int)(a[temp+4] - 48)+(int)(a[temp+5] - 48)+(int)(a[temp+6] - 48))==( ((int)(a[temp+7] - 48)*10)+(int)(a[temp+8] - 48) )  ));
            Serial.print("||");*/

      if (temp != -1 || temp2 != -1 || temp3 != -1)
      {
        int numOdd = 0;
        int numSum = 0;
        if (temp != -1)
        {
          for (int i = 1; i < 6; i++)
          {
            if ((((int)(a[temp + i] - 48)) % 2) != 0)
            {
              numOdd++;
            }
          }
        }

        if (temp != -1)
        {
          for (int i = 1; i < 7; i++)
          {

            numSum = numSum + ((int)(a[temp + i] - 48));
          }
        }

        if (temp2 != -1)
        {
          for (int i = 1; i < 6; i++)
          {
            if ((((int)(a[temp2 + i] - 48)) % 2) != 0)
            {
              numOdd++;
            }
          }
        }

        if (temp2 != -1)
        {
          for (int i = 1; i < 7; i++)
          {

            numSum = numSum + ((int)(a[temp2 + i] - 48));
          }
        }

        //reset
        if (temp3 != -1 && ((a[temp3]) == 'r') && ((int)(a[temp3 + 2] - 48)) == 1 && ((int)(a[temp3 + 3] - 48)) == 2 && ((int)(a[temp3 + 4] - 48)) == 3)
        {
          if (((int)(a[temp3 + 1] - 48)) == 5)
          {
            Serial.print("@@@@resetall@@@@@@resetall@@@@@@resetall@@@resetall@@");
            for (int i = 0; i < 4; i++)
            {
              p[i].timeSet = false;
              p[i].timer = false;
            }
          }

          else
          {

            Serial.print("@@@@reset@@@@@@reset@@@@@@reset@@@reset@@");
            p[((int)(a[temp3 + 1] - 48)) - 1].timeSet = false;
            p[((int)(a[temp3 + 1] - 48)) - 1].timer = false;
          }
        }

        //TimerOn
        else if (temp != -1 && ((a[temp]) == 'n') && ((a[temp - 1]) == 'j') && (((int)(a[temp + 6] - 48)) == numOdd) && ((((int)(a[temp + 7] - 48) * 10)) + (int)(a[temp + 8] - 48)) == numSum)
        {

          if (((int)(a[temp + 1] - 48)) == 5)
          {
            Serial.print("@@@@TimerOnall@@TimerOnall@@@@TimerOnall@@@@TimerOnall@@@@@TimerOnall@@");
            for (int i = 0; i < 4; i++)
            {
              p[i].timer = true;
              p[i].timeSet = false;

              add = 0;
              if ((myRTC.minutes + ((int)(a[temp + 4] - 48) * 10) + (int)(a[temp + 5] - 48)) > 59)
              {

                p[i].minuteOn = (myRTC.minutes + ((int)(a[temp + 4] - 48) * 10) + (int)(a[temp + 5] - 48)) - 60;
                add = 1;
              }
              else
              {
                p[i].minuteOn = myRTC.minutes + ((int)(a[temp + 4] - 48) * 10) + (int)(a[temp + 5] - 48);
              }

              if (((myRTC.hours + ((int)(a[temp + 2] - 48) * 10) + (int)(a[temp + 3] - 48)) + add) > 23)
              {
                p[i].hourOn = ((myRTC.hours + ((int)(a[temp + 2] - 48) * 10) + (int)(a[temp + 3] - 48)) + add) - 24;
              }
              else
              {
                p[i].hourOn = ((myRTC.hours + ((int)(a[temp + 2] - 48) * 10) + (int)(a[temp + 3] - 48)) + add);
              }
            }
          }

          else
          {

            Serial.print("@@@@TimerOn@@TimerOn@@@@TimerOn@@@@TimerOn@@@@@TimerOn@@");
            p[((int)(a[temp + 1] - 48)) - 1].timer = true;
            p[((int)(a[temp + 1] - 48)) - 1].timeSet = false;

            add = 0;
            if ((myRTC.minutes + ((int)(a[temp + 4] - 48) * 10) + (int)(a[temp + 5] - 48)) > 59)
            {

              p[((int)(a[temp + 1] - 48)) - 1].minuteOn = (myRTC.minutes + ((int)(a[temp + 4] - 48) * 10) + (int)(a[temp + 5] - 48)) - 60;
              add = 1;
            }
            else
            {
              p[((int)(a[temp + 1] - 48)) - 1].minuteOn = myRTC.minutes + ((int)(a[temp + 4] - 48) * 10) + (int)(a[temp + 5] - 48);
            }

            if (((myRTC.hours + ((int)(a[temp + 2] - 48) * 10) + (int)(a[temp + 3] - 48)) + add) > 23)
            {
              p[((int)(a[temp + 1] - 48)) - 1].hourOn = ((myRTC.hours + ((int)(a[temp + 2] - 48) * 10) + (int)(a[temp + 3] - 48)) + add) - 24;
            }
            else
            {
              p[((int)(a[temp + 1] - 48)) - 1].hourOn = ((myRTC.hours + ((int)(a[temp + 2] - 48) * 10) + (int)(a[temp + 3] - 48)) + add);
            }

            /*  p[((int)(a[temp+1] - 48))-1].hourOn=myRTC.hours+((int)(a[temp+2] - 48)*10)+(int)(a[temp+3] - 48);
                            p[((int)(a[temp+1] - 48))-1].minuteOn=myRTC.minutes+((int)(a[temp+4] - 48)*10)+(int)(a[temp+5] - 48);*/

            Serial.print("||");
            Serial.print(p[((int)(a[temp + 1] - 48)) - 1].hourOn);
            Serial.print("||");
            Serial.print(p[((int)(a[temp + 1] - 48)) - 1].minuteOn);
            Serial.print("||");
          }
        }

        //TimerOff
        else if (temp2 != -1 && ((a[temp2]) == 'f') && ((a[temp2 - 1]) == 'j') && (((int)(a[temp2 + 6] - 48)) == numOdd) && ((((int)(a[temp2 + 7] - 48) * 10)) + (int)(a[temp2 + 8] - 48)) == numSum)
        {

          if (((int)(a[temp2 + 1] - 48)) == 5)
          {
            Serial.print("@@@@TimerOffall@@TimerOffall@@@@TimerOffall@@@@Offall@@@@@TimerOffall@@");
            for (int i = 0; i < 4; i++)
            {
              p[i].timer = true;
              p[i].timeSet = false;

              add = 0;
              if ((myRTC.minutes + ((int)(a[temp2 + 4] - 48) * 10) + (int)(a[temp2 + 5] - 48)) > 59)
              {

                p[i].minuteOff = (myRTC.minutes + ((int)(a[temp2 + 4] - 48) * 10) + (int)(a[temp2 + 5] - 48)) - 60;
                add = 1;
              }
              else
              {
                p[i].minuteOff = myRTC.minutes + ((int)(a[temp2 + 4] - 48) * 10) + (int)(a[temp2 + 5] - 48);
              }

              if (((myRTC.hours + ((int)(a[temp2 + 2] - 48) * 10) + (int)(a[temp2 + 3] - 48)) + add) > 23)
              {
                p[i].hourOff = ((myRTC.hours + ((int)(a[temp2 + 2] - 48) * 10) + (int)(a[temp2 + 3] - 48)) + add) - 24;
              }
              else
              {
                p[i].hourOff = ((myRTC.hours + ((int)(a[temp2 + 2] - 48) * 10) + (int)(a[temp2 + 3] - 48)) + add);
              }

              /*p[i].hourOff=myRTC.hours+((int)(a[temp2+2] - 48)*10)+(int)(a[temp2+3] - 48);
                                   p[i].minuteOff=myRTC.minutes+((int)(a[temp2+4] - 48)*10)+(int)(a[temp2+5] - 48);*/
            }
          }

          else
          {

            Serial.print("@@@@TimerOff@@TimerOff@@@@TimerOff@@@@Off@@@@@TimerOff@@");
            p[((int)(a[temp2 + 1] - 48)) - 1].timer = true;
            p[((int)(a[temp2 + 1] - 48)) - 1].timeSet = false;

            add = 0;
            if ((myRTC.minutes + ((int)(a[temp2 + 4] - 48) * 10) + (int)(a[temp2 + 5] - 48)) > 59)
            {

              p[((int)(a[temp2 + 1] - 48)) - 1].minuteOff = (myRTC.minutes + ((int)(a[temp2 + 4] - 48) * 10) + (int)(a[temp2 + 5] - 48)) - 60;
              add = 1;
            }
            else
            {
              p[((int)(a[temp2 + 1] - 48)) - 1].minuteOff = myRTC.minutes + ((int)(a[temp2 + 4] - 48) * 10) + (int)(a[temp2 + 5] - 48);
            }

            if (((myRTC.hours + ((int)(a[temp2 + 2] - 48) * 10) + (int)(a[temp2 + 3] - 48)) + add) > 23)
            {
              p[((int)(a[temp2 + 1] - 48)) - 1].hourOff = ((myRTC.hours + ((int)(a[temp2 + 2] - 48) * 10) + (int)(a[temp2 + 3] - 48)) + add) - 24;
            }
            else
            {
              p[((int)(a[temp2 + 1] - 48)) - 1].hourOff = ((myRTC.hours + ((int)(a[temp2 + 2] - 48) * 10) + (int)(a[temp2 + 3] - 48)) + add);
            }

            /*      p[((int)(a[temp2+1] - 48))-1].hourOff=myRTC.hours+((int)(a[temp2+2] - 48)*10)+(int)(a[temp2+3] - 48);
                            p[((int)(a[temp2+1] - 48))-1].minuteOff=myRTC.minutes+((int)(a[temp2+4] - 48)*10)+(int)(a[temp2+5] - 48);*/
          }
          Serial.print("||");
          Serial.print(p[((int)(a[temp2 + 1] - 48)) - 1].hourOff);
          Serial.print("||");
          Serial.print(p[((int)(a[temp2 + 1] - 48)) - 1].minuteOff);
          Serial.print("||");
        }

        //on   temp!=-1 && ((a[temp])=='n') && ((a[temp-1])=='j') && (((int)(a[temp+6] - 48))==numOdd)  && ((((int)(a[temp+7] - 48)*10))+(int)(a[temp+8] - 48))==numSum
        else if (temp != -1 && ((a[temp]) == 'n') && ((a[temp - 1]) == 'd') && (((int)(a[temp + 6] - 48)) == numOdd) && ((((int)(a[temp + 7] - 48) * 10)) + (int)(a[temp + 8] - 48)) == numSum)
        {

          if (((int)(a[temp + 1] - 48)) == 5)
          {
            for (int i = 0; i < 4; i++)
            {
              p[i].timer = false;
              p[i].timeSet = true;
              p[i].hourOn = ((int)(a[temp + 2] - 48) * 10) + (int)(a[temp + 3] - 48);
              p[i].minuteOn = ((int)(a[temp + 4] - 48) * 10) + (int)(a[temp + 5] - 48);
            }
          }

          else
          {

            Serial.print("@on@@@@@on@@@@on@@@@@@on@@on@@");
            //timePinOn[(int)(a[temp+1] - 48)]=true;
            p[((int)(a[temp + 1] - 48)) - 1].timeSet = true;
            p[((int)(a[temp + 1] - 48)) - 1].timer = false;
            p[((int)(a[temp + 1] - 48)) - 1].hourOn = (((int)(a[temp + 2] - 48) * 10)) + (int)(a[temp + 3] - 48);
            p[((int)(a[temp + 1] - 48)) - 1].minuteOn = ((int)(a[temp + 4] - 48) * 10) + (int)(a[temp + 5] - 48);
          }

          Serial.print("||");
          Serial.print(p[((int)(a[temp + 1] - 48)) - 1].hourOn);
          Serial.print("||");
          Serial.print(p[((int)(a[temp + 1] - 48)) - 1].minuteOn);
          Serial.print("||");
        }
        //Off
        else if (temp2 != -1 && ((a[temp2]) == 'f') && ((a[temp2 - 1]) == 'd') && (((int)(a[temp2 + 6] - 48)) == numOdd) && ((((int)(a[temp2 + 7] - 48) * 10)) + (int)(a[temp2 + 8] - 48)) == numSum)
        {

          if (((int)(a[temp2 + 1] - 48)) == 5)
          {
            for (int i = 0; i < 4; i++)
            {
              p[i].timer = false;
              p[i].timeSet = true;
              p[i].hourOff = ((int)(a[temp2 + 2] - 48) * 10) + (int)(a[temp2 + 3] - 48);
              p[i].minuteOff = ((int)(a[temp2 + 4] - 48) * 10) + (int)(a[temp2 + 5] - 48);
            }
          }

          else
          {

            Serial.print("@@@@Off@@Off@@@@Off@@@@Off@@@@@Off@@");
            p[((int)(a[temp2 + 1] - 48)) - 1].timeSet = true;
            p[((int)(a[temp2 + 1] - 48)) - 1].timer = false;
            p[((int)(a[temp2 + 1] - 48)) - 1].hourOff = ((int)(a[temp2 + 2] - 48) * 10) + (int)(a[temp2 + 3] - 48);
            p[((int)(a[temp2 + 1] - 48)) - 1].minuteOff = ((int)(a[temp2 + 4] - 48) * 10) + (int)(a[temp2 + 5] - 48);
          }

          Serial.print("||");
          Serial.print(p[((int)(a[temp2 + 1] - 48)) - 1].hourOff);
          Serial.print("||");
          Serial.print(p[((int)(a[temp2 + 1] - 48)) - 1].minuteOff);
          Serial.print("||");
        }

        /*{ //  Serial.print("!!!!!!!!!!!!!!!!!!!!");
                 if( ((int)(a[temp])=='N')
                 {  
                          
                            Serial.print("@@@@@@@@@@@@@@@@@@@@@");
                            hourOn=((int)(a[temp+1] - 48)*10)+(int)(a[temp+2] - 48);
                            minuteOn=((int)(a[temp+3] - 48)*10)+(int)(a[temp+4] - 48);
                 }
                 if( ((int)(a[temp])=='F') &&  ( ((int)(a[temp+1] - 48)+(int)(a[temp+2] - 48)+(int)(a[temp+3] - 48)+(int)(a[temp+4] - 48))==( ((int)(a[temp+5] - 48)*10)+(int)(a[temp+6] - 48) )  )  &&  ((int)(a[temp+6] - 48)==(int)(a[temp+7] - 48)) )
                 {  
                          
                            Serial.print("@@@@@@@@@@@@@@@@@@@@@");
                            hourOff=((int)(a[temp+1] - 48)*10)+(int)(a[temp+2] - 48);
                            minuteOff=((int)(a[temp+3] - 48)*10)+(int)(a[temp+4] - 48);
                 }
                
                       
             }*/

        // Serial.print("\n");
        // Serial.print("hourOn");
        //  Serial.print("\n");
        // Serial.print("minuteOn");

        s = "";
      }
    }
  }
  //delay(5);
  //Serial.write("!");
  // listen for user input and send it to the ESP8266
  if (Serial.available())
  {

    char c = (char)Serial.read();

    esp8266.print(c);
    c = 0;
  }
  //*******************************************************************

  //**time*****************************************************************
  // This allows for the update of variables for time or accessing the individual elements.
  myRTC.updateTime();

  // Start printing elements as individuals
  /*Serial.print("Current Date / Time: ");
 Serial.print(myRTC.dayofmonth); //You can switch between day and month if you're using American system
 Serial.print("/");
 Serial.print(myRTC.month);
 Serial.print("/");
 Serial.print(myRTC.year);
 Serial.print(" ");
 Serial.print(myRTC.hours);
 Serial.print(":");
 Serial.print(myRTC.minutes);
 Serial.print(":");
 Serial.println(myRTC.seconds);*/

  // Delay so the program doesn't print non-stop
  // delay(1000);

  //*******************************************************************

  for (int i = 0; i < 4; i++)
  {
    if (p[i].timeSet)
    {
      if (p[i].hourOn == myRTC.hours && p[i].minuteOn == myRTC.minutes && myRTC.seconds == 0)
      {
        digitalWrite((10 + i), LOW);
      }
    }
  }

  for (int i = 0; i < 4; i++)
  {
    if (p[i].timeSet)
    {
      if (p[i].hourOff == myRTC.hours && p[i].minuteOff == myRTC.minutes && myRTC.seconds == 0)
      {
        digitalWrite((10 + i), HIGH);
      }
    }
  }

  for (int i = 0; i < 4; i++)
  {
    if (p[i].timer)
    {
      if (p[i].hourOn == myRTC.hours && p[i].minuteOn == myRTC.minutes && myRTC.seconds == 0)
      {
        digitalWrite((10 + i), LOW);
        p[i].timer = false;
      }
    }
  }
  for (int i = 0; i < 4; i++)
  {

    if (p[i].timer)
    {
      if (p[i].hourOff == myRTC.hours && p[i].minuteOff == myRTC.minutes && myRTC.seconds == 0)
      {
        digitalWrite((10 + i), HIGH);
        p[i].timer = false;
      }
    }
  }
}
