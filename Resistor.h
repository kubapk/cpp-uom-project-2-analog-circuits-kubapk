/*
____________________________________________
RESISTOR CLASS
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
This header file (interface) defines a class for a resistor,
inhereted from "Component" class.

Created by Kuba Kane (ID: 11019699)
Created on Mon 04 May 2026
*/

//Include guard
#ifndef RESISTOR_H
#define RESISTOR_H

#include<iostream>
#include<memory>
#include "Component.h"

class Resistor : public Component
//public ensures Component protected members remain protected, and public members
//remain public
{
private:
    double resistance;
    //char* as string is array of const characters, and char is better at being 
    //compile time const compared to string (string may use dynamic memory allocation
    //even though unecessary)

public:
    //Default constructor
    Resistor();

    //Declare parameterised constructor
    Resistor(const double frequency_in, const double resistance_in);

    //Destructor from Component class used

    //Setters
    void set_frequency(const double frequency_in);
    void set_resistance(const double resistance_in);

    //Getters
    const double& get_frequency() const;
    const std::complex<double> get_impedance() const;
    const double get_impedance_magnitude() const;
    const double get_phase_difference() const;
    const ComponentType get_type() const;

    //Member functions
    void info() const;
    void component_info() const;
    std::unique_ptr<Component> clone() const;

};

#endif