/*
____________________________________________
COMPONENT CLASS
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
This header file (interface) defines a class for a 
general component

Created by Kuba Kane (ID: 11019699)
Created on Mon 04 May 2026
*/

//Include gaurd
#ifndef COMPONENT_H
#define COMPONENT_H

#include<iostream>
#include<complex> //for using complex numbers

//Abstract component class
class Component
{
protected:
    double frequency;
    std::complex<double> impedance;
    double phase_difference;

public:
    //Default constructor
    Component(); //IS THERE POINT IN HAVING DEFAULT WHICH SETS ALL TO 0?
    //Sets all to 0 - what does paramterised do with impedance, phase_diff?

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

    //Member functions

    //Friend functions
};

#endif