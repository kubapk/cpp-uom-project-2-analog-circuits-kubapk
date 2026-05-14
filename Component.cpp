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
using std::string;

//CONSTRUCTORS
//Default constructor
Component::Component(const string type_in) :
  frequency{0}, type{type_in} {}

//Paramterised constructor
Component::Component(const double frequency_in, const string type_in) :
    frequency{frequency_in}, type{type_in} {}

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

//MEMBER FUNCTIONS
//Base info protected member function
void Component::base_info() const
{
  string symbol{""};
  double impedance_real{get_impedance().real()};
  double impedance_imag{get_impedance().imag()}; 

  if(impedance_imag >= 0)
    symbol = "+ ";

  std::cout<<"Component type: "<<type<<std::endl;
  std::cout<<"Impedance: "<<impedance_real<<" "<<symbol<<impedance_imag<<"i Ohms"<<std::endl;
  std::cout<<"Frequency: "<<frequency<<" Hertz"<<std::endl;
  std::cout<<"Impedance magnitude: "<<get_impedance_magnitude()<<" Ohms"<<std::endl;
  std::cout<<"Phase difference: "<<get_phase_difference()<<" rad"<<std::endl;
}

//FRIEND FUNCTIONS