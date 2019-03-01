//	##########################################################
//	By Philip Murgatroyd and Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ Water Class for OpenGL
//
//	The water class calculates and draws the sea level
//
//	##########################################################

#ifndef WATER_H
#define WATER_H

/******************************** includes ********************************/
#include "Ticker.h"

/******************************** Class ********************************/
class Water
{
private:
	float waterWidth;	// the width of water
	float waterBreadth;	// the breadth of the water
  float waterHeight; // the height of the water
	float atmospress; // atmospheric pressure
	float waterHeightAdj; // user adjustable water height

public:
	Water();								// the empty default constructor
	void render(Ticker &tick);				// Draw Water

	~Water();							// the destructor
};

#endif
