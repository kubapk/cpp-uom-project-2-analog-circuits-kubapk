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
#include "Component.h"

class Resistor : public Component
//public ensures Component protected members remain protected, and public members
//remain public
{
private:
    double resistance;

public:
    //Default constructor
    Resistor();

    //Declare parameterised constructor
    Resistor(const double frequency_in, const double resistance_in); //frequency_in should not be modified


    //Move/copy semantics if there is pointer involved

    //Setters
    void set_frequency(const double frequency_in) {frequency=frequency_in;}
    void set_resistance(const double resistance_in) {resistance=resistance_in;}

    //Getters
    const double& get_frequency() const {return frequency;}
    const std::complex<double>& get_impedance() const {return impedance;}
    const double& get_impedance_magnitude() const {}
    const double& get_phase_difference() const;

};

#endif