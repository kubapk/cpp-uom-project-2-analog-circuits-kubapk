//Test main file

#include<iostream>
#include<stdexcept>
#include "Resistor.h"
#include "Capacitor.h"

int main()
{
    try
    {
        //Try here
        Resistor r1(100, 10);
        r1.info();

        Capacitor c1(100, 10);
        c1.info();

    }
    catch(const std::exception& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}