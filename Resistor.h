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
//public ensures Lepton protected members remain protected, and private members
//remain private
{
private:
    double resistance;

public:
    //Default constructor
    Resistor();

    //Declare parameterised constructor
    Component(const double frequency_in); //frequency_in should not be modified

    //Destructor
    virtual ~Component() {}

    //Move/copy semantics if there is pointer involved

    //Setters
    virtual void set_frequency(const double frequency_in) = 0;

    //Getters
    virtual const double& get_frequency() const = 0;
    virtual const std::complex<double>& get_impedance() const = 0;
    virtual const double& get_impedance_magnitude() const = 0;
    virtual const double& get_phase_difference() const = 0;

};

#endif