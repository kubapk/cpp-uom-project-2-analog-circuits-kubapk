### Kuba Kane
# PHYS30762 Project - Analogue Circuits

## Program Summary
A brief summary of the program will go here

## User Guidelines
### Running the program as-is
This code was run on VSC using a Windows 11 device. The compilation line used was `ADDHERE`. The program can then be run by calling the file `main.exe`.

Test run line:
`g++ -std=c++17 test.cpp Circuit.cpp Resistor.cpp Capacitor.cpp Inductor.cpp Component.cpp -o test.exe -Wall`

### Modifying the main file, `main.cpp`
These guidelines are for a user who wishes to use the classes in this program, but modify the main file provided (or make their own).


## Program reasoning
### Having frequency as data member of individual components
- Doesn't make sense as the circuit sets the frequency, and all components of that circuit must be the same frequency - hence it can be kept as a property of the circuit, disallowing any individual components from setting their frequencies
- However, the assignment requires Pure virtual functions to set and get frequency  in base Component class - technically should not be a property of the components since the source (e.g. battery) drives the same frequency V (as sin wave) - in that case frequency should be a component of circuit (not of components) and components can take this frequency as an input
- The Circuit class contains components as a vector of POINTERS - this means that when we add a component to the vector, we must add a pointer to that component in order to add it to the vector 
- It is either a temporary which we cannot access, or if it is a pointer to a component we defined before (i.e. from the library as the assignment requires), then we have to use move semantics meaning the owner of the pointer is within that vector - which cannot be accessed!
```
auto r = std::make_unique<Resistor>(100, 50);
Circuit circuit(CircuitType::Series, 2000);
circuit.add_component(std::move(r));
```
- That's to say, the frequency cannot be modified via a component's setter - so we just need to ensure everything is handled correctly via the circuit setters 
- We do not need to be concerned with the constructor, since it initially has no components - the frequency set there can only be set at the beginning


### Rule of 0/3/5
- Circuit class involves a smart pointer, we must implement the rule of 3 at least (to define destruction & copy semantics). As we need to move components from their library into a circuit (and Circuit is derived from Component), we have to use std::move and so we need move semantics and so must implement the rule of 5.
- Need to manually copy over all components of circuit if I want to use copy semantics?
- When deleting a derived object through a base pointer, C++ must destroy the derived-specific state first, then the base part afterward (since derived objects depend on base, you cannot delete base first), e.g.
```
Component* ptr = new Circuit(...); //Circuit object stored as a pointer to a Component object
delete ptr;
```
Here, Circuit members destroyed first, then Component members - correct (virtual destructor in Component ensures it is ovewritten with Circuit destructor)
- 


### Constructor of Component class
- ALL properties can be set via constructor of Component so that it can be used by derived classes - otherwise resistor has impedance but it is never actually set/assigned to resistance
- Impedance is a property which is derived from other properties of a component, so it should not be stored as a data member - this would mean that it would need to be updated constantly anytime one of the other component features are changed (MS says only setter for frequency - suggests nothing else needs to be stored, as in general all data members should have setters)

### Shared or unique pointer
- Why not shared pointer for vector of components? Components would need to be shared by multiple owners, e.g. two different circuits sharing the ownership of the same resistor - no advantage to this given the complexities shared pointers bring in terms of when they go out of scope etc.
- If you use shared_ptr, then multiple owners are allowed, and so the object which is being added to the Circuit could be modified? The user still has access to that object

### Adding components to the circuit (std::move)
- std::move(component_ptr) is required to add the component to the vector of components so the ownership transfers to the pointer inside the vector
- This is because unique_ptr cannot have multiple owners
- Related to lvalue & rvalue - lvalues have an adress and rvalues do not (x=5) - rvalues are temporary, and we can only do move semantics on rvalues (n lvalue as something the user still needs to use, whereas if it an rvalue it is seen as something the user doesn’t mind having emptied.)
- When we define r in the code above, it is an lvalue, and so to add it to the vector we need to change its pointer, i.e. move it, and this requires us to change it to an rvalue - done via the std::move command
- Note this can't be fixed via using move/copy semantics of the Component or Circuit classes - the issue is with moving the UNIQUE_PTR itself, not an object which contains a UNIQUE_PTR 
- That's why when we define copy/move semantics of Circuit which contains a smart pointer, but we can do it via std::move thanks to it being a smart pointer
- Long story short: if you want to MOVE where unique_ptr is (its address), you must use std::move 
- If you create unique_ptr as a temporary, i.e. `test_circuit.add_component(std::make_unique<Resistor>(100, 50));` then there is no need to move it (it is already an lvalue which can be assigned to the pointer in the vector)

### Printing components in circuit
- Initital difficulty in using component->info(), since Circuit is also inherented from Component and so any nested circuits would also be printed, and it becomes quite cofusing which component belongs to which nested circuit
- Also difficult to read as different layers were all being printed with the same indentation etc
- Introduced component_info() function as virtual function in Component class, which for the true components would jusr reprint their info function
- For the Circuit class however, component_info() took all elements in its "components" vector and printed out their component_info() (and importantly not info()) function, and so nested circuits info were not printed themsleves - only the components inside each nested circuit were printed
```
NEW LAYER
 print loop

```
But need a way to determine this layer (i.e. give it a name - or just generic layers?)

### Counting the number of components
- Requires recursive function as a component might be a Circuit itself, in which case need to count the number of components inside that component as well
- Want to count total number of resistors, capacitors, inductors as well as number of nested series and parallel circuits
- Store the type as a data member inside the Component class which is then a constant inside the derived classes, and can be used to identify which of the components are which when doing the count
- It also allows for the component type to be printed in the base function, and as such reduce repeated code
- Another alternative is to use an enum class which stores the type, which although avoids any errors in different ways of writing a string or user changes (it must be written as is or C++ doesn't recognise it, even before compiling), is an overcomplication (adding an enum class can make it more difficult to follow/messy)
- Attempted to write `const string type{"Resistor"};` in Resistor class with `const string type;` in Component class - creates two different type variables (the one inhereted from Component and the one defined in Resistor class), When calling type the derived type gets used
- Benefit of using enum class in the end is that it allows for all of the different components to be stored in one place and accessed when needed 
- Also, the counter function needs to compare the type getter of each component to the different possible values of the components. Where do these values come from? Without enum class, need to type out the different possibilities again, leading ot even more potential issues with capitalisaiton etc, as well as more repeated code
- Use dyamic cast over static cast, even though you check that type of Component is Circuit, as it is safer - dynamic cast returns null ptr so problem can be caught (IMPLEMENT TRY CATCH)


## Notes
- A resistor has a defined resistance, so it should be a VARIABLE of the resistor - user can then specify what type of resistor / its resistance
- if the derived class doesn’t manage any resources itself, it does not need its own destructor - uses virtual destructor from Component
- since get_frequency is pure virtual, no point in implementing it - but could implement a validation function (range of frequencies) which is later used
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
- Circuit class uses rule of 3 since there are smart pointers where we wish to use copy semantics - Do you need Circuit c2 = c1?
- Right now Circuit class will update the frequency of all of the components??
- User can create library of components - these are components they are allowed to construct their circuit, but these components must be defined in a validationf file? E.g. specific real resistors are specified in validation file, and user can add the ones they want to their library? Disallow user from adding something into library which already exists
- Danger of user changing enumerator class for circuit type?
- If get amplitude and phase is the same in all classes, no need for virtual - just define it as a normal function in Component class

## To do
- Probably in main circuit function you want to have components be pointers - see in assignment 5 why you wanted FourMomentum to be a pointer to explain a choice of pointers
- Use alias for complex object as in std::map example
- typedef std::complex<double> complex;?
- Overrride info func for circuit so that it prints out info of all components & have base class virtual info func which is reused - allows for names to be printed
- Circuit class able to detect how many resistors, capacitors, etc in total (component_info, component_list, info)