
#include "Ticker.h"

using namespace std;

static constexpr int monthdays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//SLC is sea level change in mm/yr per milennium from present
static const float SLC[21] = { 0.6, 0.8, 1.1, 1.5, 1.7, 2.4, 3.3, 7.8, 8.8, 8.1, 13.3, 5.6, 4.7, 14.4, 14.2, 3.2, 4.0, 3.6, 1.2, 0.6, -2.7 };

Ticker::Ticker(int tkhrs, float wtrhgt, int finaltck)
{
  hr = starthr;
  yr = startyr;
  day = startday;
  mth = startmth;
  tick = 1;
  tickhrs = tkhrs;
  baseWaterHeight = wtrhgt;
  finaltick = finaltck;
  cout << "Initialising ticker at " << tkhrs << " per tick" << endl;
}

int Ticker::getTick()
{
    return tick;
}

int Ticker::getHour()
{
  return hr;
}


int Ticker::getDay()
{
  return day;
}

int Ticker::getMonth()
{
  int runtot = 0;
  if (yr % 4 != 0)
  {
    for (int i = 0; i < 12; i++)
    {
      if (day <= runtot + monthdays[i])
      {
        return i + 1;
      } else {
        runtot = runtot + monthdays[i];
      }
    }
  } else {
    for (int i = 0; i < 12; i++)
    {
      if (i == 1)
      {
        runtot++;
      }
      if (day <= runtot + monthdays[i])
      {
        return i + 1;
      } else {
        runtot = runtot + monthdays[i];
      }
    }
  }
  cout << "Something went wrong with the months" << endl;
  return 11;
}

int Ticker::getYear()
{
  return yr;
}

string Ticker::getHrStr()
{
  if (hr < 1)
  {
    return "00:00";
  } else if (hr < 10)
  {
    return "0" + to_string(hr) + ":00";
  } else
  {
    return to_string(hr) + ":00";
  }
}

string Ticker::getDayStr()
{
    return to_string(day);
}

string Ticker::getMthStr()
{
  int thismth = getMonth();
  switch(thismth)
  {
    case 1 :
      return "January";
    case 2 :
      return "February";
    case 3 :
      return "March";
    case 4 :
      return "April";
    case 5 :
      return "May";
    case 6 :
      return "June";
    case 7 :
      return "July";
    case 8 :
      return "August";
    case 9 :
      return "September";
    case 10 :
      return "October";
    case 11 :
      return "November";
    case 12 :
      return "December";
    default :
      return "ERROR";
  }

}

string Ticker::getYrStr()
{
  return to_string(abs(yr)) + "BC";
}

float Ticker::getWaterHeight()
{
  return baseWaterHeight;
}

bool Ticker::newTick()
{
  tick++;
  if (hr + tickhrs < 23)
  {
    hr = hr + tickhrs;
  } else {
    int newhr = hr + tickhrs;
    int newday = day + (newhr / 24);
    hr = newhr % 24;

    int yrdays = 365;

    if (yr % 4 == 0)
    {
      yrdays = 366;
    }

    // If each tick is longer than 365 days then this will cause slight inaccuracies around leap years
    if (newday > yrdays)
    {
      day = newday % yrdays;
      yr = yr + (newday / yrdays);

      baseWaterHeight = baseWaterHeight + ((SLC[(abs(yr/1000) + 2)] * (newday/yrdays)) / 1000);
      cout << "Year " << getYrStr() << endl;
    } else {
      day = newday;
    }
  }

  if (tick <= finaltick) {
    return true;
  } else {
    return false;
  }
}
