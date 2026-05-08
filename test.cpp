//Test main file

#include<iostream>
#include<stdexcept>
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"

int main()
{
    try
    {
        //Try here
        std::cout<<"\nResistor"<<std::endl;
        Resistor r1(100, 10);
        r1.info();

        std::cout<<"\nCapacitor"<<std::endl;
        Capacitor c1(100, 10);
        c1.info();

        std::cout<<"\nInductor"<<std::endl;
        Inductor i1(100, 10);
        i1.info();

    }
    catch(const std::exception& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}