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

//Set counter to 0
int Resistor::resistor_counter{0};


//CONSTRUCTORS
//Default constructor
Resistor::Resistor() :
    Resistor(0.0, 0.0) {}
    //Use parameterised constructor to avoid repeating ID update code

//Paramterised constructor
Resistor::Resistor(const double frequency_in, const double resistance_in, const bool assign_id) :
    Component(frequency_in), resistance{resistance_in} 
    {
        if(assign_id)
            component_id = "R"+std::to_string(++resistor_counter); //add 1 to counter
    }

//Copy constructor
Resistor::Resistor(const Resistor& res):
    Component(res), //use default copy constructor from Component class (freq & ID)
    resistance{res.resistance} //copy res resistance into current resistance
{
    component_id = "R"+std::to_string(++resistor_counter);
}

//Copy assignment operator
Resistor& Resistor::operator=(const Resistor& res)
{
    if(&res != this)
    {
        frequency = res.frequency;
        resistance = res.resistance;
        //component_id not copied or updated
    }

    return *this;
}


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
std::complex<double> Resistor::get_impedance() const {return std::complex<double> (resistance, 0.0);}
double Resistor::get_impedance_magnitude() const {return abs(get_impedance());}
double Resistor::get_phase_difference() const {return arg(get_impedance());}
ComponentType Resistor::get_type() const {return ComponentType::Resistor;}
const double& Resistor::get_resistance() const {return resistance;}


//MEMBER FUNCTIONS
void Resistor::info() const
{
    base_info();
    std::cout<<"Resistance: "<<resistance<<" Ohms"<<std::endl;
}

void Resistor::component_info() const
{
    info();
}

//Clone member function
std::unique_ptr<Component> Resistor::clone() const
{
    return std::make_unique<Resistor>(*this);
    //this is a ptr to the Resistor object itself, and clone
    //returns a copy of the object (dereferences "this")
}