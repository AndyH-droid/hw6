#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				unsigned long long w[5] = {0};
				int strLength = k.length();

				for(int i = 0; i < 5; i++){
					int currLength = std::min(strLength, 6);
					unsigned long long val = 0;
					for(int j = 0; j < currLength; j++){
						val = val*36+ letterDigitToNumber(k[strLength - currLength + j]);
					}
					w[4-i] = val;
					strLength -= currLength;
				}

				unsigned long long hash = 0;
				for(int i = 0; i < 5; i++){
					hash += rValues[i] * w[i];
				}
				return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				letter = std::tolower(letter);
				if(letter >= 'a' && letter <= 'z'){
					return letter - 'a';
				}
				else
					return 26 + (letter - '0');
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
