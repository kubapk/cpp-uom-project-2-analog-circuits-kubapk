/*
____________________________________________
CAPACITOR IMPLEMENTATION
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
Implementation file for Capacitor class.

Created by Kuba Kane (ID: 11019699)
Created on Fri 08 May 2026
*/

#include<iostream>
#define _USE_MATH_DEFINES
#include<cmath>
#include "Capacitor.h"


//CONSTRUCTORS
//Default constructor
Capacitor::Capacitor() :
    Component(), capacitance{0} {}

//Paramterised constructor
Capacitor::Capacitor(const double frequency_in, const double capacitance_in) :
    Component(frequency_in), capacitance{capacitance_in} {}


//SETTERS
//Setter for frequency
void Capacitor::set_frequency(const double frequency_in) 
{
    frequency = frequency_in;
}

//Setter for capacitance
void Capacitor::set_capacitance(const double capacitance_in)
{
    capacitance = capacitance_in;
}


//GETTERS
//Frequency getter
const double& Capacitor::get_frequency() const {return frequency;}

//Impedance getter
const std::complex<double> Capacitor::get_impedance() const
//Z_C = -iX_C, X_C = 1/wC
{
    double angular_freq{2.0 * M_PI * frequency};

    return std::complex<double> (0, -1/(angular_freq*capacitance));
}

const double Capacitor::get_impedance_magnitude() const {return abs(get_impedance());}
const double Capacitor::get_phase_difference() const {return arg(get_impedance());}


//MEMBER FUNCTIONS
//Info member function
void Capacitor::info() const
{
    std::cout<<"Component type: Capacitor"<<std::endl;
    std::cout<<"Capacitance: "<<capacitance<<" Farads"<<std::endl;
    base_info();
}