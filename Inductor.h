/*
____________________________________________
INDUCTOR CLASS
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
This header file (interface) defines a class for an inductor,
inhereted from "Component" class.

Created by Kuba Kane (ID: 11019699)
Created on Fri 08 May 2026
*/

//Include guard
#ifndef INDUCTOR_H
#define INDUCTOR_H

#include<iostream>
#include "Component.h"

class Inductor : public Component
{
private:
    double inductance; //Henrys, H

public:
    //Default constructor
    Inductor();

    //Declare parameterised constructor
    Inductor(const double frequency_in, const double inductance_in);

    //Destructor from Component class used

    //Setters
    void set_frequency(const double frequency_in);
    void set_inductance(const double inductance_in);

    //Getters
    const double& get_frequency() const;
    const std::complex<double> get_impedance() const;
    const double get_impedance_magnitude() const;
    const double get_phase_difference() const;

    //Member functions
    void info() const;
};

#endif