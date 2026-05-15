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
        //Create a library of different components
        vector<std::unique_ptr<Component>> library;

        //Add components to the library
        library.push_back(std::make_unique<Resistor>(50, 100)); //freq, resistace
        library.push_back(std::make_unique<Capacitor>(50, 10e-6)); //freq, resistance
        library.push_back(std::make_unique<Inductor>(50, 0.01)); //freq, resistance

        Circuit series_circuit(60, ConnectionType::Series);
        series_circuit.add_component(library[0]->clone()); //freq, capacitance (10x10-12)
        series_circuit.add_component(library[1]->clone());

        series_circuit.info();
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