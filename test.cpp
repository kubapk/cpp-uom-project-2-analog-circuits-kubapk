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
        std::cout<<"\nCreating a resistor"<<std::endl;
        Resistor r1(100, 10);
        r1.info();

        std::cout<<"\nTesting resistor getters"<<std::endl;
        std::cout<<"Frequency = "<<r1.get_frequency()<<std::endl;
        std::cout<<"Impedance = "<<r1.get_impedance()<<std::endl;
        std::cout<<"Impedance magnitude = "<<r1.get_impedance_magnitude()<<std::endl;
        std::cout<<"Phase difference = "<<r1.get_phase_difference()<<std::endl;

        std::cout<<"\nCreating a capacitor"<<std::endl;
        Capacitor c1(100, 10);
        c1.info();

        std::cout<<"\nCreating an inductor"<<std::endl;
        Inductor i1(100, 10);
        i1.info();

        //Build simple series circuit
        std::cout<<"\nSimple series circuit"<<std::endl;
        Circuit test_circuit(1000, ConnectionType::Series);

        std::cout<<">>Added resistor:"<<std::endl;
        std::unique_ptr<Component> r1_ptr = std::make_unique<Resistor>(100, 50);
        r1_ptr->info();
        test_circuit.add_component(std::move(r1_ptr));

        std::cout<<">>Added capacitor:"<<std::endl;
        std::unique_ptr<Component> c1_ptr = std::make_unique<Capacitor>(50, 50);
        c1_ptr->info();
        test_circuit.add_component(std::move(c1_ptr));

        std::cout<<"\nCombined circuit impedance: "<<test_circuit.get_impedance()<<std::endl;


        //Build simple parallel circuit
        std::cout<<"\nSimple parallel circuit"<<std::endl;
        Circuit parallel_circuit(1000, ConnectionType::Parallel);

        parallel_circuit.add_component(std::make_unique<Resistor>(100, 50));
        parallel_circuit.add_component(std::make_unique<Capacitor>(50, 50));

        std::cout<<"Combined circuit impedance: "<<parallel_circuit.get_impedance()<<std::endl;


        //Realistic combined circuits
        //Typical AC circuit frequency values are 50 Hz or 60 Hz for mains power, representing cycles per second
        //10 Ω through 22 MΩ
        //1pF - 1,000 microF (10pF, 22pF, 47pF, 100pF, 1nF, 10nF, 0.1µF, 1µF, 10µF, and 100µF)
        //0.5nH - 100 nH
        std::cout<<"\nRealistic combined circuit"<<std::endl;

        Circuit realistic_series(60, ConnectionType::Series); //freq, circuit type
        realistic_series.add_component(std::make_unique<Capacitor>(50, 10e-12)); //freq, capacitance (10x10-12)
        realistic_series.add_component(std::make_unique<Capacitor>(50, 10e-9));
        std::cout<<"Realistic series circuit impedance: "<<realistic_series.get_impedance()<<std::endl;
        std::cout<<"Realistic series circuit frequency: "<<realistic_series.get_frequency()<<std::endl;

        Circuit realistic_parallel(70, ConnectionType::Parallel); //freq, circuit type
        realistic_parallel.add_component(std::make_unique<Circuit>(std::move(realistic_series)));
        realistic_parallel.add_component(std::make_unique<Resistor>(45, 40)); //freq, resistance
        std::cout<<"Realistic parallel circuit impedance: "<<realistic_parallel.get_impedance()<<std::endl;
        std::cout<<"Realistic parallel circuit frequency: "<<realistic_parallel.get_frequency()<<std::endl;
        realistic_parallel.info();
        realistic_parallel.component_info();

    }
    catch(const std::exception& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}