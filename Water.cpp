//	##########################################################
//	By Philip Murgatroyd and Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ Water Class for OpenGL
//
//	The water class calculates and draws the sea level
//
//	##########################################################

#include "Water.h"
#include <cmath>
#include <iostream>
#include <fstream>


using namespace std;

static const float LUNARTIDALRANGE = 2;
static const float LUNARDAY = 24.84;
static const float ANOMALISTIC = 661.309;
static const float SOLARDAY = 24;
static const float SOLARTIDALRANGE = LUNARTIDALRANGE / 2;
static const float MINATM[12] = { 925.6, 942.3, 946.2, 952.9, 968, 968.4, 967.9, 967.7, 957.1, 946.8, 939.7, 927.2 };
static const float MAXATM[12] = { 1053.6, 1052.9, 1047.9, 1044.5, 1042.2, 1043.1, 1039.2, 1037.4, 1042, 1045.6, 1046.7, 1051.9 };
static const float WINDEFFECT = 0.1;
static const float SOLAREFFECT = SOLARTIDALRANGE / 10;
static const float LUNAREFFECT = LUNARTIDALRANGE / 10;
float ave = 0;
int windspd = 0;
float windeffect = 0.0f;
float atmeffect = 0;
float solar = 0;
float lunar = 0;
float selleff = 0;
float luneff = 0;
ofstream out("out.txt");

Water::Water()
{
	out << "Hour,Day,Year,waterHeight,baseWaterHeight,lunar,luneff,solar,soleff,atmeffect,windeffect,windspd" << endl;

	waterHeight = 0;
	atmospress = 1013;
	waterHeightAdj = 0;
}

/******************************** methods ********************************/
void Water::render(Ticker &tick)
{

	// Lunar tide
	lunar = tick.getTick() / (LUNARDAY / 2);
	lunar = lunar - (int) lunar;
	lunar = abs(lunar - 0.5);
	lunar = ((lunar * LUNARTIDALRANGE) / 0.5) - (LUNARTIDALRANGE / 2);

	luneff = tick.getTick() / ANOMALISTIC;
	luneff = luneff - (int) luneff;
	luneff = abs(luneff - 0.5);
	luneff = ((luneff * LUNAREFFECT) / 0.5) - (LUNAREFFECT / 2);

	lunar = lunar + luneff;

	// Solar tide
	solar = tick.getTick() / (SOLARDAY / 2);
	solar = solar - (int) solar;
	solar = abs(solar - 0.5);
	solar = ((solar * SOLARTIDALRANGE) / 0.5) - (SOLARTIDALRANGE / 2);

	selleff = abs(tick.getDay() - 183);
	selleff = (selleff * SOLAREFFECT) / 183;

	solar = solar + selleff;

	// Air pressure
	ave = ((MAXATM[tick.getMonth() - 1] - MINATM[tick.getMonth() - 1]) / 2) + MINATM[tick.getMonth() - 1] + 15;
	float atm = 0;

	if (atmospress < ave) {
		if (rand() % 100 > 45) {
			atm = rand() % 3;
		} else {
			atm = 0 - (rand() % 3);
		}
	} else {
		if (rand() % 100 > 45) {
			atm = 0 - (rand() % 3);
		} else {
			atm = rand() % 3;
		}
	}

	if (atmospress < MINATM[tick.getMonth() - 1] && atm < 0) {
		atm = 0;
	} else if (atmospress > MAXATM[tick.getMonth() - 1] && atm > 0) {
		atm = 0;
	}
	atmospress = atmospress + atm;
	atmeffect = (1013 - atmospress) * 0.01;

	// Wind
	if (atm > 0) {
		if (atmospress > 1013) {
			windspd = rand() % 3;
		} else {
			windspd = (rand() % 3) + 2;
		}
	} else if (atm < 0) {
		if (atmospress > 1013) {
			windspd = (rand() % 3) + 1;
		} else {
			windspd = (rand() % 3) + 3;
		}
	}

	if (tick.getMonth() > 2 && tick.getMonth() < 11 && windspd > 0) {
		windspd--;
	}

	//by now windspd will be between 0-5, which is wave height in feet
	if (windspd != 0) {
		windeffect = ((rand() % (windspd * 2)) - windspd) * 0.3;
	} else {
		windeffect = 0.0f;
	}
	windeffect = windeffect + (float)((rand() % 30) - 15) / 100;

	waterHeight = tick.getWaterHeight() + lunar + solar + atmeffect + windeffect;

	out << tick.getHrStr() << "," << tick.getDayStr() << "," << tick.getYrStr() << "," << waterHeight << "," << tick.getWaterHeight() << "," << lunar << "," << luneff << "," << solar << "," << selleff << "," << atmeffect << "," << windeffect << "," << windspd << endl;
	/*
	cout << "Tick is " << tick.getTick() << ": Lunar component is " << lunar << " and Solar component is " << solar << endl;
	cout << " atmospheric pressure is " << atmospress << ", change is " << atm << " and windspeed is " << windspd << " so wind effect is " << windeffect << endl;
	cout << " and atmos effect is " << atmeffect << " so height = " << baseWaterHeight << " actually " << waterHeight << endl;
	*/

}

/******************************** destructor ********************************/
Water::~Water()
{
	out.close();
	cout << "water destroyed" << endl;
}
