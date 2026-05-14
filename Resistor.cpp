/*
____________________________________________
RESISTOR IMPLEMENTATION
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
Implementation file for Resistor class.

Created by Kuba Kane (ID: 11019699)
Created on Fri 08 May 2026
*/

#include<iostream>
#include "Resistor.h"


//CONSTRUCTORS
//Default constructor
Resistor::Resistor() :
    Component(RESISTOR_TEXT), resistance{0} {}

//Paramterised constructor
Resistor::Resistor(const double frequency_in, const double resistance_in) :
    Component(frequency_in, RESISTOR_TEXT), resistance{resistance_in} {}


//SETTERS
//Setter for frequency
void Resistor::set_frequency(const double frequency_in) 
{
    frequency = frequency_in;
}

//Setter for resistance
void Resistor::set_resistance(const double resistance_in)
{
    resistance = resistance_in;
}


//GETTERS
const double& Resistor::get_frequency() const {return frequency;}
const std::complex<double> Resistor::get_impedance() const {return std::complex<double> (resistance, 0.0);}
const double Resistor::get_impedance_magnitude() const {return abs(get_impedance());}
const double Resistor::get_phase_difference() const {return arg(get_impedance());}


//SETTERS
void Resistor::info() const
{
    std::cout<<"RESISTOR"<<std::endl;
    std::cout<<"Resistance: "<<resistance<<" Ohms"<<std::endl;
    base_info();
}

void Resistor::component_info() const
{
    info();
}