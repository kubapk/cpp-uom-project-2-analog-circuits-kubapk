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
    static int circuit_counter; 
    //bool moved_from{false};

public:
    //Declare default constructor
    Circuit(ConnectionType connection_in); //cannot have circuit without defined type
    //this circuit will have f = 0Hz

    //Declare parameterised constructor
    Circuit(const double frequency_in, ConnectionType connection_in, const bool assign_id = true);

    //Destructor inherited from Component class
    
    //Declare copy constructor & assignment operator
    Circuit(const Circuit&); //constructor
    Circuit& operator=(const Circuit&); //assignment op

    //Declare copy & move assignment operators
    Circuit(Circuit&&) noexcept = default; //constructor
    Circuit& operator=(Circuit&&) noexcept = default; //assignment op
    //if exception thrown during move, the vector stays in a broken state
    //User cannot handle the exception because everything is in an nondeterministic state
    //compiler doesn't like this so may use copy instead - but here we are moving pointers
    //so there is no risk - we tell compiler that move will not throw any exceptions
    //use default move semantics as unique_ptr has std::move (transfers ownership of all pointers
    //in vector)

    //Setters
    void set_frequency(const double frequency_in);
    void set_connection(const ConnectionType connection_in); //allows user to change mind of how circuit is connected

    //Getters
    const double& get_frequency() const;
    std::complex<double> get_impedance() const;
    double get_impedance_magnitude() const;
    double get_phase_difference() const;
    ComponentType get_type() const;
    const ConnectionType& get_connection() const;

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