#include<iostream>
#include<cstdlib>
#include<ctime>
#include <cstdio>
#include "kolorywyswietlane.h"
#include "szescianrubika.h"
int main()
{
    srand(time(NULL));
    rubic kostka;
    kostka.freeplay(1,1);
    return 0;
}
