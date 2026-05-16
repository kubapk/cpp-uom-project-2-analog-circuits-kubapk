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
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Circuit.h"
using std::vector;

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
        library.push_back(std::make_unique<Resistor>(100, 1e4, 0.2, "Wirewound", false)); //freq, resistace, tolerance, name, assignID
        //library.push_back(std::make_unique<Capacitor>(50, 10e-6, false)); //freq, resistance, assignID
        //library.push_back(std::make_unique<Inductor>(50, 0.01, false)); //freq, inductance, assignID
        //library.push_back(std::make_unique<Resistor>(20, 100, false)); //freq, resistance, assignID

        Circuit series_circuit(60, ConnectionType::Series);
        series_circuit.add_component(library[0]->clone());
        //series_circuit.add_component(library[1]->clone());
        //series_circuit.add_component(library[0]->clone());
        //series_circuit.add_component(library[3]->clone());

        //Instead have a map which means the components from the library can be called with something that the user
        //recognises - that way it is clear what is being called

        std::cout<<"Circuit info"<<std::endl;
        series_circuit.info();

        std::cout<<"\nCircuit component info"<<std::endl;
        series_circuit.component_info();

        //Or make it a map so you can call it by a name - i.e. give the component a nickname
        //(all nicknames would need to be unique - could not have two components exactly the same as
        //how would you extract one and not the other?)
        //Use std map or container to manage IDs of components - much better to make hard copy so that
        //IDs of the resistors are unique (resistor cannot physically be in 2 places at once)

    }
    catch(const std::exception& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}