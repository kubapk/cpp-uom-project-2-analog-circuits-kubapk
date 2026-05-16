/*
____________________________________________
CAPACITOR CLASS
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
This header file (interface) defines a class for a capacitor,
inhereted from "Component" class.

Created by Kuba Kane (ID: 11019699)
Created on Fri 08 May 2026
*/

//Include guard
#ifndef CAPACITOR_H
#define CAPACITOR_H

#include<iostream>
#include "Component.h"

class Capacitor : public Component
{
private:
    double capacitance; //Farads, F
    double tolerance;
    static int capacitor_counter; 
    static vector<ValidationRecord> valid_capacitors;

public:
    //Default constructor
    Capacitor();

    //Declare parameterised constructor
    Capacitor(const double frequency_in, const double capacitance_in, const double tolerance_in, 
        const bool assign_id = true);

    //Destructor from Component class used

    //Declare copy constructor (update ID)
    Capacitor(const Capacitor&);

    //Declare copy assignment operator (do not copy ID)
    Capacitor& operator=(const Capacitor&);

    //Setters
    void set_frequency(const double frequency_in);
    void set_capacitance(const double capacitance_in);

    //Getters
    const double& get_frequency() const;
    std::complex<double> get_impedance() const;
    double get_impedance_magnitude() const;
    double get_phase_difference() const;
    ComponentType get_type() const;
    const double& get_capacitance() const;

    //Member functions
    void info() const;
    void component_info() const;
    std::unique_ptr<Component> clone() const;
    static void load_validation_file(const string& capacitor_file_name);
};

#endif