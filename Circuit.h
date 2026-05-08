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

enum class CircuitType {Series, Parallel};

class Circuit
{
private:
    vector<std::unique_ptr<Component>> components;
    CircuitType type;
    double frequency;

public:
    //Declare default constructor
    Circuit();

    //Declare parameterised constructor
    Circuit();

    //Destructor
    ~Circuit() {};

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

    //Member functions
    void add_component()
};

#endif