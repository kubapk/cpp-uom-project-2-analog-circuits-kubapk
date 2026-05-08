//Test main file

#include<iostream>
#include<stdexcept>
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Circuit.h"

int main()
{
    try
    {
        //Try components
        std::cout<<"\nResistor"<<std::endl;
        Resistor r1(100, 10);
        r1.info();

        std::cout<<"\nTesting resistor getters"<<std::endl;
        std::cout<<"Frequency = "<<r1.get_frequency()<<std::endl;
        std::cout<<"Impedance = "<<r1.get_impedance()<<std::endl;
        std::cout<<"Impedance magnitude = "<<r1.get_impedance_magnitude()<<std::endl;
        std::cout<<"Phase difference = "<<r1.get_phase_difference()<<std::endl;

        std::cout<<"\nCapacitor"<<std::endl;
        Capacitor c1(100, 10);
        c1.info();

        std::cout<<"\nInductor"<<std::endl;
        Inductor i1(100, 10);
        i1.info();

        //Build simple series circuit
        //Components to add
        r1_ptr = 

        Circuit test_circuit(1000, CircuitType::Series);
        test_circuit.add_component(r1);

    }
    catch(const std::exception& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}