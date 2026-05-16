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
#include<string>
#include "Circuit.h"
using std::string;

//Set counter to 0
int Circuit::circuit_counter{0};

//CONSTRUCTORS
//Default constructor
Circuit::Circuit(ConnectionType connection_in) :
    Circuit(0.0, connection_in) {}

//Parameterised constructor
Circuit::Circuit(const double frequency_in, ConnectionType connection_in, const bool assign_id) :
    Component(frequency_in), connection{connection_in}
    {
        if(assign_id)
            component_id = "CIRC"+std::to_string(++circuit_counter); //add 1 to counter
    }

//Copy constructor
Circuit::Circuit(const Circuit& circ):
    Component(circ), connection(circ.connection)
    {
        //Deep copy of all pointers inside "components" in "circ" Circuit object
        for(const auto& component_ptr : circ.components)
            //Copy "circ" into current class object - push_back each component from "circ"
            components.push_back(component_ptr->clone());
            //need to push back object of type unique_ptr<Component> so could have
            //components.push_back(std::make_unique<Component>(*circ.component_ptr))
            //but this tries to create a new component object, which cannot be done since
            //it is abstract - require clone() function to deal with each component
            //individually
        
        component_id = "CIRC"+std::to_string(++circuit_counter);
    }

//Copy assignment operator
Circuit& Circuit::operator=(const Circuit& circ)
{
    //If not self assignment
    if(&circ != this)
    {
        frequency = circ.frequency;
        connection = circ.connection;
        //component_id not copied or updated

        components.clear(); //empty current vector first
        
        for(const auto& component_ptr : circ.components)
            components.push_back(component_ptr->clone());
    }

    return *this; //if self-assignment, *this is just returned with no modification

}
//Unlike copy constructor, assignment operator already has an object (which is being allocated to LHS) - must free
//any dynamically allocated memory first
//However, unique_ptr's assignment operator automatically destroys the old object before taking ownership of the new one
//so don't need to free anything
//but here we cannot use the assignment operator as we have a VECTOR of pointers, and we cannot assign vectors (they may be 
//of different dimensions)
//Need to use push_back and so must clear memory first
//Not issue with copy constructor as it does not already have an object 

//SETTERS
//Setter for frequency
void Circuit::set_frequency(const double frequency_in) 
{
    frequency = frequency_in;

    //Syncronise: Set frequency of each component to match frequency_in
    for(const auto& component_ptr_i : components)
    {
        try
        {
            component_ptr_i->set_frequency(frequency_in);
        }
        catch(const std::exception& e)
        {
            throw std::invalid_argument(component_id+" -> "+e.what());
        }
    }
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
std::complex<double> Circuit::get_impedance() const
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

double Circuit::get_impedance_magnitude() const {return abs(get_impedance());}
double Circuit::get_phase_difference() const {return arg(get_impedance());}
ComponentType Circuit::get_type() const {return ComponentType::Circuit;}
const ConnectionType& Circuit::get_connection() const {return connection;}


//MEMBER FUNCTIONS
//Function to add component to circuit
void Circuit::add_component(std::unique_ptr<Component> component_ptr)
{
    try
    {
        component_ptr->set_frequency(frequency);
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument(component_id+" -> "+e.what());
    }

    //Add component to vector
    components.emplace_back(std::move(component_ptr));

}

//Info member function
void Circuit::info() const
{
    base_info();

    std::cout<<"Overall circuit type: ";
    if(connection == ConnectionType::Series)
        std::cout<<"Series "<<std::endl;
    else
        std::cout<<"Parallel"<<std::endl;

    std::cout<<"Number of reistors: "<<count_components().num_resistors<<std::endl;
    std::cout<<"Number of capacitors: "<<count_components().num_capacitors<<std::endl;
    std::cout<<"Number of inductors: "<<count_components().num_inductors<<std::endl;
    std::cout<<"Number of nested series circuits: "<<count_components().num_nested_series<<std::endl;
    std::cout<<"Number of nested parallel circuits: "<<count_components().num_nested_parallel<<std::endl;

}

//Info of all components in circuit (excluding circuits themselves)
void Circuit::component_info() const
{
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

//Counter member function
CircuitStats Circuit::count_components() const
{
    //Stats for this circuit (level 1)
    CircuitStats stats;

    //Loop over all components in this circuit
    for(const auto& component_ptr : components)
    {
        //If component of level 1 circuit is a nested circuit
        if(component_ptr->get_type() == ComponentType::Circuit)
        {
            //In level 1, even though we have checkd it is Circuit, it is stored as
            //std::unique_ptr<Component> so must cast to std::unique_ptr<Circuit> as
            //Component doesn't have count_components() member function
            //so must cast to std::unique_ptr<Circuit> - cast only works on raw
            //pointer so must also use .get() from smart pointers to get raw pointer
            //from unique pointer
            //do not handle raw pointer, e..g delete component.get();, since this deletes twice
            //(Unqiue ptr tries to delete again)

            //Raw pointer to level 2 circuit
            Circuit* sub_circuit_ptr = dynamic_cast<Circuit*>(component_ptr.get());

            //Check if sub_circuit (level 2) is parallel or series and update stats
            if(sub_circuit_ptr->connection == ConnectionType::Series)
                stats.num_nested_series++;
            else
                stats.num_nested_parallel++; 

            //Apply component counter to nested circuit
            CircuitStats sub_stats = sub_circuit_ptr->count_components();

            //Repeat checks for all components in level 2 circuit
            
            stats.num_resistors += sub_stats.num_resistors;
            stats.num_capacitors += sub_stats.num_capacitors;
            stats.num_inductors += sub_stats.num_inductors;
            stats.num_nested_series += sub_stats.num_nested_series; //requires entering level 3 to update count
            stats.num_nested_parallel += sub_stats.num_nested_parallel; //requires entering level 3
        }

        //If component of level 1 circuit is not nested circuit
        else
        {
            switch(component_ptr->get_type())
            {
                case ComponentType::Resistor:
                    stats.num_resistors++; //add 1
                    break;

                case ComponentType::Capacitor:
                    stats.num_capacitors++;
                    break;
                
                case ComponentType::Inductor:
                    stats.num_inductors++;
                    break; 

                default:
                    break;
            }
        }
    }

    return stats;
}

//Clone member function
std::unique_ptr<Component> Circuit::clone() const
{
    return std::make_unique<Circuit>(*this);
    //Requires circuit to be copyable - rule of 5
}