/*
____________________________________________
RESISTOR CLASS
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
This header file (interface) defines a class for a resistor,
inhereted from "Component" class.

Created by Kuba Kane (ID: 11019699)
Created on Mon 04 May 2026
*/

//Include guard
#ifndef RESISTOR_H
#define RESISTOR_H

#include<iostream>
#include<memory>
#include<vector>
#include<string>
#include "Component.h"
#include "ValidationRecord.h"
using std::vector;
using std::string;


class Resistor : public Component
//public ensures Component protected members remain protected, and public members
//remain public
{
private:
    double resistance;
    double tolerance;
    string name;
    static int resistor_counter; 
    //static so there is one counter for for all resistors, not one counter for each resistor object
    static vector<ValidationRecord> valid_resistors;

public:
    //Default constructor
    Resistor()=delete; //must be a resistor in validation file so no default

    //Declare parameterised constructor
    Resistor(const double frequency_in, const double resistance_in, const double tolerance_in, const string name_in,
        const bool assign_id = true);

    //Destructor from Component class used

    //Declare copy constructor (update ID)
    Resistor(const Resistor&);

    //Declare copy assignment operator (do not copy ID)
    Resistor& operator=(const Resistor&);

    //Default move constructor & assignment op

    //Setters
    void set_frequency(const double frequency_in);
    void set_resistance(const double resistance_in);
    void set_tolerance(const double tolerance_in);
    void set_name(const string name);

    //Getters
    const double& get_frequency() const;
    std::complex<double> get_impedance() const;
    double get_impedance_magnitude() const;
    double get_phase_difference() const;
    ComponentType get_type() const;
    const double& get_resistance() const;
    const double& get_tolerance() const;
    const string& get_name() const;
    
    //Member functions
    void info() const;
    void component_info() const;
    std::unique_ptr<Component> clone() const;
    static void load_validation_file(const string& resistor_file_name);

};

#endif