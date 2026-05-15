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

//Set counter to 0
int Capacitor::capacitor_counter{0};

//CONSTRUCTORS
//Default constructor
Capacitor::Capacitor() :
    Capacitor(0.0, 0.0) {}

//Paramterised constructor
Capacitor::Capacitor(const double frequency_in, const double capacitance_in) :
    Component(frequency_in), capacitance{capacitance_in}
    {
        component_id = "C"+std::to_string(++capacitor_counter); //add 1 to counter
    }


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
const ComponentType Capacitor::get_type() const {return ComponentType::Capacitor;}


//MEMBER FUNCTIONS
//Info member function
void Capacitor::info() const
{
    base_info();
    std::cout<<"Capacitance: "<<capacitance<<" Farads"<<std::endl;
}

void Capacitor::component_info() const
{
    info();
}

//Clone member function
std::unique_ptr<Component> Capacitor::clone() const
{
    return std::make_unique<Capacitor>(*this);
}