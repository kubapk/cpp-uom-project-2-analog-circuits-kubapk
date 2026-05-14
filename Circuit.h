/*
____________________________________________
CIRCUIT CLASS
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
This header file (interface) defines a class for a 
circuit containing components (objects derived from
Component class).

Created by Kuba Kane (ID: 11019699)
Created on Fri 08 May 2026
*/

//Include guard
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>
#include<memory> //using smart pointers
#include<vector>
#include "Component.h"
using std::vector;


//Enumerator class for circuit type
enum class CircuitType {Series, Parallel};


//Circuit class inherits from Component
class Circuit : public Component
{
private:
    vector<std::unique_ptr<Component>> components;
    CircuitType type;

public:
    //Declare default constructor
    Circuit(CircuitType type_in); //cannot have circuit without defined type
    //this circuit will have f = 0Hz

    //Declare parameterised constructor
    Circuit(const double frequency_in, CircuitType type_in);

    //Destructor inherited from Component class
    
    //Copy/move semantics needed if we don't want to copy/move a Circuit?

    //Setters
    void set_frequency(const double frequency_in);
    void set_type(const CircuitType type_in); //allows user to change mind of how circuit is connected

    //Getters
    const int& get_components() const;
    const CircuitType& get_type() const;
    const double& get_frequency() const;

    const std::complex<double> get_impedance() const;
    const double get_impedance_magnitude() const;
    const double get_phase_difference() const;
    const int get_number_components() const;

    //Member functions
    void add_component(std::unique_ptr<Component> component_ptr_in);
    //Using pointer to component means the input parameter of this function
    //can be any of derived classes - can be directly added to vector
    
    void info() const;
    void component_info() const;
};

#endif