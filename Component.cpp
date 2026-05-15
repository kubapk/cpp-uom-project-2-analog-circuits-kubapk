/*
____________________________________________
COMPONENT IMPLEMENTATION
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
Implementation file for "Component" class.

Created by Kuba Kane (ID: 11019699)
Created on Mon 04 May 2026
*/

#include<iostream>
#include "Component.h"
#include<stdexcept>
using std::string;

//CONSTRUCTORS
//Default constructor
Component::Component() :
  frequency{0} {}

//Paramterised constructor
Component::Component(const double frequency_in) :
    frequency{frequency_in} {}

//Copy constructor
//Copy assignment operator
//Move constructor
//Move assignment operator


//SETTERS
//Validation for setter
//You may want private member function which does general validatio needed in setter and 
//parameterised constructor 
//Maybe validation comes after implementing everything else

//Setter for frequency
/* Could have the setter below - but its pointless because in .h we have defined it as pure virtual
so it will be ovewritten anyway
void Component::set_frequency(const double frequency_in)
{
  frequency = frequency_in;
}
*/

//Getter
//Component ID getter
const string& Component::get_id() const
{
  return component_id;
}

//MEMBER FUNCTIONS
//Base info protected member function
void Component::base_info() const
{
  string symbol{""};
  double impedance_real{get_impedance().real()};
  double impedance_imag{get_impedance().imag()}; 

  if(impedance_imag >= 0)
    symbol = "+ ";

  std::cout<<"==="<<type_to_string(get_type())<<"==="<<std::endl;
  std::cout<<"ID: "<<component_id<<std::endl;
  std::cout<<"Impedance: "<<impedance_real<<" "<<symbol<<impedance_imag<<"i Ohms"<<std::endl;
  std::cout<<"Frequency: "<<frequency<<" Hertz"<<std::endl;
  std::cout<<"Impedance magnitude: "<<get_impedance_magnitude()<<" Ohms"<<std::endl;
  std::cout<<"Phase difference: "<<get_phase_difference()<<" rad"<<std::endl;
}

//Static member function to convert types to string output
string Component::type_to_string(const ComponentType type_in)
{
  switch(type_in)
  {
    case ComponentType::Resistor:
      return "Resistor";

    case ComponentType::Capacitor:
      return "Capacitor";

    case ComponentType::Inductor:
      return "Inductor";

    case ComponentType::Circuit:
      return "Circuit";
  }
  throw std::logic_error("Unknown component type when trying to convert type to string.");
}