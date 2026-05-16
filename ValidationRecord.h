/*
____________________________________________
VALIDATION RECORD STRUCT
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
This header file (interface) defines a struct with
components storing data from validation files.

Created by Kuba Kane (ID: 11019699)
Created on Sat 16 May 2026
*/

//Include guard
#ifndef VALIDATION_RECORD_H
#define VALIDATION_RECORD_H

#include<iostream>
#include<string>
using std::string;

struct ValidationRecord
{
    string name;
    double min_value;
    double max_value;
    double tolerance;
    double max_frequency;
};


#endif