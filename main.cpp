//	##########################################################
//	By Philip Murgatroyd
//	##########################################################

#include <iostream>
#include <string>
#include "Ticker.h"
#include "Water.h"

using namespace std;

bool isRunning;                 // main loop state

Water *water;       // declare water
Ticker *ticker;     // declare ticker

/****************************** MAIN METHOD ******************************/
int main(int argc, char**argv)
{
    water = new Water();


    // set states
    isRunning = true;


    ticker = new Ticker(1, -88.3, 63420000);

    while (isRunning) {
          isRunning = ticker->newTick();
          water->render(*ticker);
    }



   return 0;
}
