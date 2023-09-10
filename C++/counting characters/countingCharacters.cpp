#include <iostream>
#include <string>
#include "countingFunctions.h"
using namespace std;

#define UPPERCONS "BCDFGHJKLMNPQRSTVWXYZ"
#define LOWERCONS "bcdfghjklmnpqrstvwxyz"
#define UPPERVOWELS "AEIOU"
#define LOWERVOWELS "aeiou"
#define SPACE ' '

int main(void)
{   
    int vowels = 0, consonants = 0, spaces = 0;
    string str;
    
    cout << "Enter an phrase: ";
    getline(cin, str);

    count(str, &vowels, LOWERVOWELS, UPPERVOWELS);
    count(str, &consonants, LOWERCONS, UPPERCONS);
    countSpaces(str, &spaces);

    cout << "Vowels: " << vowels << endl;
    cout << "Consonants: " << consonants << endl;
    cout << "Words: " << spaces << endl;

    return 0;
}