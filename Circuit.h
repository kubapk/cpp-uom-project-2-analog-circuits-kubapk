/*
____________________________________________
CIRCUIT CLASS
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
This header file (interface) defines a class for a 
circuit containing components (objects derived from
Component class).

Created by Kuba Kane (ID: 11019699)
Created on Fri 08 May 2026
*/

//Include guard
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>
#include<memory> //using smart pointers
#include<vector>
#include "Component.h"
using std::vector;


//Struct for counting component types
//Struct more effective than class as we don't need any class-like features
//(no methods or functions are needed, and hence no encapsulation)
struct CircuitStats
{
    int num_resistors{0};
    int num_capacitors{0};
    int num_inductors{0};
    int num_nested_series{0};
    int num_nested_parallel{0};
};


//Enumerator class for circuit type
enum class ConnectionType {Series, Parallel};


//Circuit class inherits from Component
class Circuit : public Component
{
private:
    vector<std::unique_ptr<Component>> components;
    ConnectionType connection;
    static constexpr const char* CIRCUIT_TEXT = "Circuit";

public:
    //Declare default constructor
    Circuit(ConnectionType connection_in); //cannot have circuit without defined type
    //this circuit will have f = 0Hz

    //Declare parameterised constructor
    Circuit(const double frequency_in, ConnectionType connection_in);

    //Destructor inherited from Component class
    
    //Copy/move semantics needed if we don't want to copy/move a Circuit?

    //Setters
    void set_frequency(const double frequency_in);
    void set_connection(const ConnectionType connection_in); //allows user to change mind of how circuit is connected

    //Getters
    const int& get_components() const;
    const ConnectionType& get_connection() const;
    const double& get_frequency() const;

    const std::complex<double> get_impedance() const;
    const double get_impedance_magnitude() const;
    const double get_phase_difference() const;
    const int get_number_components() const;

    const ComponentType get_type() const;

    //Member functions
    void add_component(std::unique_ptr<Component> component_ptr_in);
    //Using pointer to component means the input parameter of this function
    //can be any of derived classes - can be directly added to vector
    
    void info() const;
    void component_info() const;
    CircuitStats count_components() const;
    std::unique_ptr<Component> clone() const;
};

#endif