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

//Set counter to 0
int Inductor::inductor_counter{0};

//CONSTRUCTORS
//Paramterised constructor
Inductor::Inductor(const double frequency_in, const double inductance_in, const double tolerance_in, 
   const string name_in, const bool assign_id) :
        Component(frequency_in), inductance{inductance_in}, tolerance{tolerance_in}, name{name_in}
        {
            validate_component(valid_inductors, ComponentType::Inductor, name_in, frequency_in, inductance_in,
                tolerance_in);

            if(assign_id)
                component_id = "I"+std::to_string(++inductor_counter); //add 1 to counter
        }

//Copy constructor
Inductor::Inductor(const Inductor& ind):
    Component(ind),
    inductance{ind.inductance}
    {
        component_id = "I"+std::to_string(++inductor_counter);
    }

//Copy assignment operator
Inductor& Inductor::operator=(const Inductor& ind)
{
    if(&ind != this)
    {
        frequency = ind.frequency;
        inductance = ind.inductance;
        //component_id not copied or updated
    }

    return *this;
}    

//SETTERS
//Setter for frequency
void Inductor::set_frequency(const double frequency_in) 
{
    validate_component(valid_inductors, ComponentType::Inductor, name, frequency_in, inductance,
                tolerance);

    frequency = frequency_in;
}

//Setter for inductance
void Inductor::set_inductance(const double inductance_in)
{
    validate_component(valid_inductors, ComponentType::Inductor, name, frequency, inductance_in,
                tolerance);

    inductance = inductance_in;
}

//Setter for tolerance
void Inductor::set_tolerance(const double tolerance_in)
{
    validate_component(valid_inductors, ComponentType::Inductor, name, frequency, inductance,
                tolerance_in);

    tolerance = tolerance_in;
}

//Setter for name
void Inductor::set_name(const string name_in)
{
    validate_component(valid_inductors, ComponentType::Inductor, name_in, frequency, inductance,
                tolerance);

    name = name_in;
}

//GETTERS
//Frequency getter
const double& Inductor::get_frequency() const {return frequency;}

//Impedance getter
std::complex<double> Inductor::get_impedance() const
//Z_C = iX_L, X_L = wL
{
    double angular_freq{2.0 * M_PI * frequency};

    return std::complex<double> (0, angular_freq*inductance);
}

double Inductor::get_impedance_magnitude() const {return abs(get_impedance());}
double Inductor::get_phase_difference() const {return arg(get_impedance());}
ComponentType Inductor::get_type() const {return ComponentType::Inductor;}
const double& Inductor::get_inductance() const {return inductance;}
const double& Inductor::get_tolerance() const {return tolerance;}


//MEMBER FUNCTION
//Info member function
void Inductor::info() const
{
    base_info();
    std::cout<<"Inductance: "<<inductance<<" Henries"<<std::endl;
    std::cout<<"Tolerance: "<<tolerance*100<<"%"<<std::endl;
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

//Static public member function to load in validation file
void Inductor::load_validation_file(const string& inductor_file_name)
{
    Component::load_validation_file(inductor_file_name, valid_inductors, 
        ComponentType::Inductor);
} 