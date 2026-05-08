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

//MEMBER FUNCTIONS
void Component::info() const
{
  std::cout<<"Component name"<<std::endl;
  std::cout<<"Impedance = "<<get_impedance()<<std::endl;
  std::cout<<"Frequency = "<<frequency<<std::endl;
  std::cout<<"Impedance magnitude = "<<get_impedance_magnitude()<<std::endl;
  std::cout<<"Phase difference = "<<get_phase_difference()<<std::endl;
}

//FRIEND FUNCTIONS