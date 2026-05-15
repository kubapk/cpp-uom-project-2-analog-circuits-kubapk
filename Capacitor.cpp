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
Capacitor::Capacitor(const double frequency_in, const double capacitance_in, const bool assign_id ) :
    Component(frequency_in), capacitance{capacitance_in}
    {
        if(assign_id)
            component_id = "C"+std::to_string(++capacitor_counter); //add 1 to counter
    }

//Copy constructor
Capacitor::Capacitor(const Capacitor& cap):
    Component(cap),
    capacitance{cap.capacitance}
    {
        component_id = "C"+std::to_string(++capacitor_counter);
    }

//Copy assignment operator
Capacitor& Capacitor::operator=(const Capacitor& cap)
{
    if(&cap != this)
    {
        frequency = cap.frequency;
        capacitance = cap.capacitance;
        //component_id not copied or updated
    }

    return *this;
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
std::complex<double> Capacitor::get_impedance() const
//Z_C = -iX_C, X_C = 1/wC
{
    double angular_freq{2.0 * M_PI * frequency};

    return std::complex<double> (0, -1/(angular_freq*capacitance));
}

double Capacitor::get_impedance_magnitude() const {return abs(get_impedance());}
double Capacitor::get_phase_difference() const {return arg(get_impedance());}
ComponentType Capacitor::get_type() const {return ComponentType::Capacitor;}
const double& Capacitor::get_capacitance() const {return capacitance;}


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