### Kuba Kane
# PHYS30762 Project - Analogue Circuits

## Program Summary
A brief summary of the program will go here

## User Guidelines
### Running the program as-is
This code was run on VSC using a Windows 11 device. The compilation line used was `g++ -std=c++17 main.cpp Neutrino.cpp Tau.cpp Muon.cpp Electron.cpp Lepton.cpp FourMomentum.cpp -o main.exe -Wall`. The program can then be run by calling the file `main.exe`.

### Modifying the main file, `main.cpp`
These guidelines are for a user who wishes to use the classes in this program, but modify the main file provided (or make their own).

## Notes
- A resistor has a defined resistance, so it should be a VARIABLE of the resistor - user can then specify what type of resistor / its resistance
- if the derived class doesn’t manage any resources itself, it does not need its own destructor - uses virtual destructor from Component
- since get_frequency is pure virtual, no point in implementing it - but could implement a validation function which is later used
- ALL properties can be set via constructor of Component so that it can be used by derived classes - otherwise resistor has impedance but it is never actually set/assigned to resistance

## To do
- Probably in main circuit function you want to have components be pointers - see in assignment 5 why you wanted FourMomentum to be a pointer to explain a choice of pointers