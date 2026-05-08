### Kuba Kane
# PHYS30762 Project - Analogue Circuits

## Program Summary
A brief summary of the program will go here

## User Guidelines
### Running the program as-is
This code was run on VSC using a Windows 11 device. The compilation line used was `g++ -std=c++17 main.cpp Neutrino.cpp Tau.cpp Muon.cpp Electron.cpp Lepton.cpp FourMomentum.cpp -o main.exe -Wall`. The program can then be run by calling the file `main.exe`.

Test run line:
`g++ -std=c++17 test.cpp Resistor.cpp Capacitor.cpp Inductor.cpp Component.cpp -o test.exe -Wall`

### Modifying the main file, `main.cpp`
These guidelines are for a user who wishes to use the classes in this program, but modify the main file provided (or make their own).

## Notes
- A resistor has a defined resistance, so it should be a VARIABLE of the resistor - user can then specify what type of resistor / its resistance
- if the derived class doesn’t manage any resources itself, it does not need its own destructor - uses virtual destructor from Component
- since get_frequency is pure virtual, no point in implementing it - but could implement a validation function which is later used
- ALL properties can be set via constructor of Component so that it can be used by derived classes - otherwise resistor has impedance but it is never actually set/assigned to resistance
- Impedance is a property which is derived from other properties of a component, so it should not be stored as a data member - this would mean that it would need to be updated constantly anytime one of the other component features are changed (MS says only setter for frequency - suggests nothing else needs to be stored, as in general all data members should have setters)
- Info function to print out all info of a component
- If you add more functions to derived Component classes, can have base info function so that you can print out name - otherwise add name as a property in the base class
- Get impedance magnitude & phase difference can be non-virtual in base class as they both do the same thing no matter the component
- Do not allow maths constant to be redefined twice - ifdef for maths consts?
- Use phase difference to print out a message saying whether current leads or lags voltage
- inductors have positive phase angle, capacitors negative phase angle -> enforce this?
- Use template class since all of them are very similar?
- Angular frequency is a function in base class? Best to avoid repeated code
- Restrict user to selecting from a file / database of given capacitors/resistors/inductors
- Components in Circuit class stored as a vector of unique pointers to Component abstract class objects so that objects of derived classes can also be stored
- Pure virtual functions to set and get frequency are required in base Component class - technically should not be a property of the components since the source (e.g. battery) drives the same frequency V (as sin wave) - in that case frequency should be a component of circuit (not of components) and components can take this frequency as an input
- Why not shared pointer for vector of components? Components would need to be shared by multiple owners, e.g. two different circuits sharing the ownership of the same resistor - no advantage to this given the complexities shared pointers bring in terms of when they go out of scope etc.
- Circuit class uses rule of 3 since there are smart pointers where we wish to use copy semantics - Do you need Circuit c2 = c1?
- Right now Circuit class will update the frequency of all of the components??
- User can create library of components - these are components they are allowed to construct their circuit, but these components must be defined in a validationf file? E.g. specific real resistors are specified in validation file, and user can add the ones they want to their library? Disallow user from adding something into library which already exists

## To do
- Probably in main circuit function you want to have components be pointers - see in assignment 5 why you wanted FourMomentum to be a pointer to explain a choice of pointers
- Use alias for complex object as in std::map example