#include <iostream>

float add(float a, float b, bool debug) {

    if (debug == true) {
        std::cout << "adding " << a << " and " << b << std::endl;
    }

    return a+b;
}