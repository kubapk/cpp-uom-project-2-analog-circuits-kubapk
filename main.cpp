/*
_____________________________TITLE_____________________________
PHYS30762 Project - Analogue Circuits
_______________________________________________________________
This C++ script is the main file for this project.

Created by Kuba Kane (ID: 11019699)
Created on Fri 15 May 2026
*/

#include<iostream>
#include<stdexcept>
#include<vector>
#include<memory>
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Circuit.h"
using std::vector;

void print_all_circuit_info(const std::unique_ptr<Circuit>& circuit_in, const string& circuit_name)
{
    std::cout<<std::endl;
    std::cout<<circuit_name<<" info\n"<<string(60, '-')<<std::endl;
    circuit_in->info();

    std::cout<<std::endl;
    std::cout<<circuit_name<<" component info\n"<<string(60, '-')<<std::endl;
    circuit_in->component_info();
}

int main()
{
    try
    {
        //Load validation files
        Resistor::load_validation_file("resistor_validation.txt");
        Capacitor::load_validation_file("capacitor_validation.txt");
        Inductor::load_validation_file("inductor_validation.txt");

        //Create a library of different components
        vector<std::unique_ptr<Component>> library;

        //Add components to the library
        library.push_back(std::make_unique<Resistor>(100, 1e2, 0.2, "Wirewound", false)); //freq, value, tolerance, name, assignID
        library.push_back(std::make_unique<Capacitor>(1000, 5e-7, 0.1, "Ceramic capacitor", false));
        library.push_back(std::make_unique<Inductor>(60, 0.5, 0.2, "Power inductor", false)); 
        library.push_back(std::make_unique<Resistor>(2e4, 3, 0.05, "Carbon film", false));
        library.push_back(std::make_unique<Capacitor>(200, 2.4e-6, 0.1, "Tantalum capacitor", false));
        library.push_back(std::make_unique<Inductor>(1e6, 45e-8, 0.05, "RF choke", false));

        //Can clone separately if you wish
        auto wirebound_cloned = library[0]->clone();
        
        //Create a series circuit with resistor, inductor, capacitor (RLC)
        auto rlc_circuit = std::make_unique<Circuit>(50, ConnectionType::Series);
        rlc_circuit->add_component(std::move(wirebound_cloned)); //Wirebound resistor
        rlc_circuit->add_component(library[4]->clone()); //Tantalum capacitor
        rlc_circuit->add_component(library[2]->clone()); //Power inductor

        //Print info about RLC circuit
        print_all_circuit_info(rlc_circuit, "RLC circuit");

        //Create another series circuit with inductor & capacitor (LC)
        auto lc_circuit = std::make_unique<Circuit>(60, ConnectionType::Series);
        lc_circuit->add_component(library[4]->clone()); //Tantalum capacitor
        lc_circuit->add_component(library[5]->clone()); //RF choke inductor

        //Print info about LC circuit
        print_all_circuit_info(lc_circuit, "LC circuit");


        //Add series circuits together in parallel
        auto combined_parallel = std::make_unique<Circuit>(55, ConnectionType::Parallel);
        combined_parallel->add_component(std::move(rlc_circuit));
        combined_parallel->add_component(std::move(lc_circuit));

        //Print info about parallel circuit
        print_all_circuit_info(combined_parallel, "Parallel (RLC + LC) circuit");

        //Try to modify frequency of circuit to a high value
        //combined_parallel->set_frequency(30e6);

        //Try to print out info of moved circuit
        print_all_circuit_info(rlc_circuit, "RLC circuit (moved from)");
        
    }
    catch(const std::exception& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}