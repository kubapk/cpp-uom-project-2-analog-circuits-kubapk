/*
____________________________________________
INDUCTOR IMPLEMENTATION
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
Implementation file for Inductor class.

Created by Kuba Kane (ID: 11019699)
Created on Fri 08 May 2026
*/

#include<iostream>
#define _USE_MATH_DEFINES
#include<cmath>
#include "Inductor.h"


//CONSTRUCTORS
//Default constructor
Inductor::Inductor() :
    Component(), inductance{0} {}

//Paramterised constructor
Inductor::Inductor(const double frequency_in, const double inductance_in) :
    Component(frequency_in), inductance{inductance_in} {}


//SETTERS
//Setter for frequency
void Inductor::set_frequency(const double frequency_in) 
{
    frequency = frequency_in;
}

//Setter for inductance
void Inductor::set_inductance(const double inductance_in)
{
    inductance = inductance_in;
}


//GETTERS
//Frequency getter
const double& Inductor::get_frequency() const {return frequency;}

//Impedance getter
const std::complex<double> Inductor::get_impedance() const
//Z_C = iX_L, X_L = wL
{
    double angular_freq{2.0 * M_PI * frequency};

    return std::complex<double> (0, angular_freq*inductance);
}

const double Inductor::get_impedance_magnitude() const {return abs(get_impedance());}
const double Inductor::get_phase_difference() const {return arg(get_impedance());}
const ComponentType Inductor::get_type() const {return ComponentType::Inductor;}


//MEMBER FUNCTION
//Info member function
void Inductor::info() const
{
    base_info();
    std::cout<<"Inductance: "<<inductance<<" Henries"<<std::endl;
}

void Inductor::component_info() const
{
    info();
}

//Clone member function
std::unique_ptr<Component> Inductor::clone() const
{
    return std::make_unique<Inductor>(*this);
}