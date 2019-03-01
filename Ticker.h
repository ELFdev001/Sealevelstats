#ifndef TICKER_H
#define TICKER_H

#include <iostream>
#include <string>
#include <cmath>

class Ticker
{
private:
  static const int starthr = 0;
  static const int startday = 1;
  static const int startmth = 1;
  static const int startyr = -13000;
  int tick, hr, day, mth, yr, tickhrs, finaltick;
  float baseWaterHeight;


public:
  int getHour();
  int getDay();
  int getMonth();
  int getYear();
  int getTick();
  bool newTick();
  std::string getHrStr();
  std::string getDayStr();
  std::string getMthStr();
  std::string getYrStr();
  float getWaterHeight();

  Ticker(int tkhrs, float wtrhgt, int finaltck);
  ~Ticker();
};

#endif
