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

public:
    //Default constructor
    Component();

    //Declare parameterised constructor
    Component(const double frequency_in); 
    //frequency_in, impedance_in are const as should not be modified

    //Destructor
    virtual ~Component() {}

    //Move/copy semantics if there is pointer involved

    //Setters
    virtual void set_frequency(const double frequency_in) = 0;

    //Getters
    virtual const double& get_frequency() const = 0;
    virtual const std::complex<double>& get_impedance() const = 0;
    virtual const double& get_impedance_magnitude() const;
    virtual const double& get_phase_difference() const;

    //Member functions
    void component_info() const;

    //Friend functions
};

#endif