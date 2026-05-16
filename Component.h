/*
____________________________________________
COMPONENT CLASS
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
This header file (interface) defines a class for a 
general component

Created by Kuba Kane (ID: 11019699)
Created on Mon 04 May 2026
*/

//Include gaurd
#ifndef COMPONENT_H
#define COMPONENT_H

#include<iostream>
#include<complex> //for using complex numbers
#include<memory> //for unique ptr
#include<string>
#include<vector>
#include "ValidationRecord.h"
using std::string;
using std::vector;


//Enumerator class for all types of components
//Useful for counts used in Circuit class and avoiding repeating code
enum class ComponentType
{
    Resistor,
    Capacitor,
    Inductor,
    Circuit
};


//Abstract component class
class Component
{
protected:
    //Variables/consts
    double frequency; //Hz
    string component_id;
     
    //Functions
    void base_info() const; //info in common for all components

    //Consts
    static constexpr double numerical_tolerance = 1e-12;
    //much smaller than any physical parameters but greater than double precison (1e-15)

    static void validate_component(const vector<ValidationRecord>& all_records, const ComponentType& comp_type,
        const string& comp_name, const double comp_frequency, const double comp_value, const double comp_tolerance);

    static void load_validation_file(const string& file_name_in, 
        vector<ValidationRecord>& all_records, const ComponentType type_in);
        //pass all_records by reference so that original record is edited
        //passing by value would give temporary of all_records which does not 
        //modify all_records data member of derived classes

    static string type_to_string(const ComponentType type_in);
    

public:
    //Default constructor
    Component();

    //Declare parameterised constructor
    Component(const double frequency_in); 

    //Destructor
    virtual ~Component() {}

    //Setters
    virtual void set_frequency(const double frequency_in) = 0;

    //Getters
    virtual const double& get_frequency() const = 0;
    virtual std::complex<double> get_impedance() const = 0;
    virtual double get_impedance_magnitude() const = 0;
    virtual double get_phase_difference() const = 0;
    virtual ComponentType get_type() const = 0;
    const string& get_id() const;
    string get_behaviour() const;

    //get_impedance, get_impedance_magnitude, get_phase_difference, get_type 
    //cannot be returned by reference as they return temporary objects

    //Member functions
    virtual void info() const = 0; //info including circuits
    virtual void component_info() const = 0; //info just for components
    //want to print out the info of any arbitrary component so component_info
    //is not used for Circuit class

    virtual std::unique_ptr<Component> clone() const = 0;

};

#endif