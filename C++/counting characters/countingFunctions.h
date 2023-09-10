#include <iostream>
#include <string>
using namespace std;

#define UPPERCONS "BCDFGHJKLMNPQRSTVWXYZ"
#define LOWERCONS "bcdfghjklmnpqrstvwxyz"
#define UPPERVOWELS "AEIOU"
#define LOWERVOWELS "aeiou"
#define SPACE ' '

void count(string str, int * counter, const char LOWER[], const char UPPER[])
{
    size_t indexLOWER, indexUPPER;
    if ((indexLOWER = str.find_first_of(LOWER)) != string::npos)
        *counter += 1;
    if ((indexUPPER = str.find_first_of(UPPER)) != string::npos)
        *counter += 1;

    while (indexLOWER != string::npos || indexUPPER != string::npos)
    {
        if (indexLOWER != string::npos)
        {
            if((indexLOWER = str.find_first_of(LOWER, indexLOWER + 1)) != string::npos)
                *counter += 1;
        }

        if (indexUPPER != string::npos)
        {
            if((indexUPPER = str.find_first_of(UPPER, indexUPPER + 1)) != string::npos)
                *counter += 1;
        }
    }
}

void countSpaces(string str, int * space)
{
    size_t index;
    if((index = str.find_first_of(SPACE)) != string::npos && str.at(index + 1) != SPACE)
        *space += 1;

    while (index != string::npos)
    {
        if((index = str.find_first_of(SPACE, index + 1)) && str.at(index + 1) != SPACE)
            *space += 1;
    }
}