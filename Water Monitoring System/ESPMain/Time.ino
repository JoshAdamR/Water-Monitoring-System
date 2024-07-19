#include <WiFiUdp.h>
#include <NTPClient.h>

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int GMT = 8;
int offset = 3600*GMT;

void timeSetup()
{
  Serial.begin(57600);
  Serial.println() ;
  Serial.println() ;
  Serial.println() ;

  char buf[ 80 ] ;

  sprintf( buf, "sizeof( unsigned long ): %d \n", sizeof( unsigned long ) ) ;
  Serial.print(buf) ;
  sprintf( buf, "sizeof( time_t ): %d \n", sizeof( time_t ) ) ;
  Serial.print(buf) ;

  timeClient.setTimeOffset(offset);
}

String getTime(String type){
  time_t epochTime = timeClient.getEpochTime();
  timeClient.update();
  String formattedTime = timeClient.getFormattedTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;
  String currentMonthName = months[currentMonth - 1];
  int currentYear = ptm->tm_year + 1900;
  //Print complete date:
  String currentDate = (String) currentYear + "-" + (String) currentMonth + "-" + (String) monthDay;
  
  if (type == "time"){
    return currentDate;
  }
  else if (type == "date"){
    return formattedTime;
  }
  else {return "null";}
}
  