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
        std::cout<<"\nSimple series circuit"<<std::endl;
        Circuit test_circuit(1000, CircuitType::Series);

        std::cout<<">>Added resistor:"<<std::endl;
        std::unique_ptr<Component> r1_ptr = std::make_unique<Resistor>(100, 50);
        r1_ptr->info();
        test_circuit.add_component(std::move(r1_ptr));

        std::cout<<">>Added capacitor:"<<std::endl;
        std::unique_ptr<Component> c1_ptr = std::make_unique<Capacitor>(1000, 50);
        c1_ptr->info();
        test_circuit.add_component(std::move(c1_ptr));


        std::cout<<"\nCombined circuit impedance: "<<test_circuit.get_impedance()<<std::endl;

    }
    catch(const std::exception& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}