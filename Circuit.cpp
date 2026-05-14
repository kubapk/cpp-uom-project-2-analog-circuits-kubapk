/*
____________________________________________
CIRCUIT IMPLEMENTATION
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
Implementation file for Circuit class.

Created by Kuba Kane (ID: 11019699)
Created on Fri 08 May 2026
*/

#include<iostream>
#include "Circuit.h"
using std::string;

//CONSTRUCTORS
//Default constructor
Circuit::Circuit(ConnectionType connection_in) :
    Component(), connection{connection_in} {}

//Paramterised constructor
Circuit::Circuit(const double frequency_in, ConnectionType connection_in) :
    Component(frequency_in), connection{connection_in} {}


//SETTERS
//Setter for frequency
void Circuit::set_frequency(const double frequency_in) 
{
    frequency = frequency_in;

    //Syncronise: Set frequency of each component to match frequency_in
    for(const auto& component_ptr_i : components)
        component_ptr_i->set_frequency(frequency_in);
    //"component_ptr_i" is std::unique_ptr<Component> but can let compiler decide with auto
    //cannot pass component_ptr_i by value as unique pointer cannot be copied (it can only have one owner at once)
    //Set the reference to std::unique_ptr<Component> to be const as it shouldn't be modified -
    //each component in components should not change
}

//Setter for connection type
void Circuit::set_connection(const ConnectionType connection_in)
{
    connection = connection_in;
}


//GETTERS
//Getter for frequency
const double& Circuit::get_frequency() const {return frequency;}

//Getter for impedance
const std::complex<double> Circuit::get_impedance() const
{
    std::complex<double> total_impedance(0.0, 0.0);

    if(components.empty())
        return total_impedance;

    else if(connection == ConnectionType::Series)
    {
        for(const auto& component_ptr_i : components)
            total_impedance += component_ptr_i->get_impedance();

        return total_impedance;
    }
    else
    {
        for(const auto& component_ptr_i : components)
            total_impedance += 1.0/(component_ptr_i->get_impedance());

        return 1.0/total_impedance;
    }
    //Switch not used as the cases don't depend on same variable
}

const double Circuit::get_impedance_magnitude() const {return abs(get_impedance());}
const double Circuit::get_phase_difference() const {return arg(get_impedance());}

const int Circuit::get_number_components() const {return components.size();}
const ComponentType Circuit::get_type() const {return ComponentType::Circuit;}


//MEMBER FUNCTIONS
//Function to add component to circuit
void Circuit::add_component(std::unique_ptr<Component> component_ptr)
{
    //Syncronise: Set the frequency of component to match that of circuit
    component_ptr->set_frequency(frequency);

    //Add component to vector
    components.emplace_back(std::move(component_ptr));

}

//Info member function
void Circuit::info() const
{
    std::cout<<"CIRCUIT"<<std::endl;
    std::cout<<"Circuit type: ";
    if(connection == ConnectionType::Series)
        std::cout<<"Series "<<std::endl;
    else
        std::cout<<"Parallel"<<std::endl;

    base_info();
    std::cout<<"Number of components: "<<get_number_components()<<std::endl;
    //This needs to be recursive - find number of components in circuits inside circuits etc.

}

void Circuit::component_info() const
{
    std::cout<<string(10, '=')<<" Circuit component info "<<string(10, '=')<<std::endl;

    for(const auto& component : components)
        {
            component->component_info();
            std::cout<<std::endl;
        }
        //"i" is std::unique_ptr<Component> where "Component" changes dependent on the inhereted class
        //cannot pass i by value as smart pointers (used in Circuit derived from Component) cannot be copied 
        //- pass by reference
        //Set the reference to std::unique_ptr<Lepton> (i.e "i") to be const as it shouldn't be modified -
        //each component in components should not change
}