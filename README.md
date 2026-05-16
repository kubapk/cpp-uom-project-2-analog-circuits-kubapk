### Kuba Kane
# PHYS30762 Project - Analogue Circuits

## Program Summary
This program allows a user to build their own circuit using a Resistor, Capacitor or Inductor. These are all classes derived from a Component abstract base class, which contains a frequency and a unique ID, as well as a function to calculate the impedance of the component, and its magntiude and phase difference (angle). The impedance function uses the complex number library from C++. All of the derived classes are then given a name (e.g. "Wirewound reistor") and a tolerance (e.g. 20%) which is not in the Component abstract class.
 - **Resistor:** Also has resistance as member function, and then overrides impedance function to return 0 as the real entry, and $Z_C = -iX_C, X_C = 1/wC$ as the imaginary entry.
 - **Capacitor:** Also has capacitance as member function, and then overrides impedance function to return the resistance value as the real entry, and 0 as the imaginary entry.

The Component class has a base info function which outputs the component type, its ID, impedance, frequency, behaviour and impedance magnitude and phase difference. The derived classes also output the name and resistance, capacitance and inductance respectively.

## User Guidelines
### Running the program as-is
This code was run on VSC using a Windows 11 device. The compilation line used was `g++ -std=c++17 main.cpp Circuit.cpp Resistor.cpp Capacitor.cpp Inductor.cpp Component.cpp -o main.exe -Wall`. The program can then be run by calling the file `main.exe`.

### Modifying the main file, `main.cpp`
These guidelines are for a user who wishes to use the classes in this program, but modify the main file provided (or make their own).

## Additional information

See [analogue_circuits_report.pdf](Report/analogue_circuits_report.pdf).


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
- Clone requires Circuit to be copyable so need rule of 3 at least
- Give user freedom to move one Circuit to another so implement rule of 5


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

### Library of components
- User should be able to take a component from a library and use it in a given circuit, and hence cannot use std::move as in test
- Cannot use shared ptr: if two circuits share the same Resistor object, then changing its frequency/value in one circuit could accidentally affect the other circuit too
- Shared ptr messes up the program logic - when a component is added to a circuit, that circuit now owns that component and so controls its frequency (frequency propagates to all components)
- If shared ptr, then when same component is added to second circuit, it changes the frequency of that component again - this may initially not seem like a problem (we add to one circuit and then another and they update the frequency when the component is added), but what if we add the same component to two circuits, and then ask to print out the results? 
```
circuit1.setFrequency(50);
circuit2.setFrequency(1000);  // overwrites the component's frequency!
circuit1.print();             // component now thinks f=1000
```
The only places where frequeny is updated when we add component (this is done beforehand), and where we set frequency of circuit (it sets for all components in circuit also) - so then component will have frequency of circuit 2 even though we want to print info for circuit 1 

- select components from the library to use in circuits, leaving the library intact --> cannot use unique_ptr and std::move 

- Imagine the library as the lab demonstrator having a selection of components which they want you to use. The lab demonstrator is the owner of these components, and they have infinitely many copies of each of them. You can add one of the components to your circuit, in which case you ask the component to clone itself. You are now the owner of this copy of the component. When you add it to the circuit, std::move changes the owner from yourself to the circuit.  
- Avoid code repetition if you want to use more than one component with the same properties (would need ot be added twice to the library)

### Push back vs emplace back
- https://www.geeksforgeeks.org/cpp/push_back-vs-emplace_back-in-cpp-stl-vectors/
- Push back is a disavtange when we declare new objects within push_back, as this means the copy constructor of that object needs to be called
- Every time there is push_back, cpp will create a new vector which COPEIS the new value from parameter which is being push backed and it also COPIES all values in the old vector to the new vector (this copying of all values can be reduced by declaring vector size in advance)
- Emplace back does not need copy constructor as it can insert the object without calling the copy constructor
- Pushing back pointers however, this has no effect as there is no new object which is being added - it already exists in memory if it is a pointer

### Component IDs
- Option 1: Each derived class stores its own counter which increments every time the constructor of that derived class is called
- Option 2: Base class stores counters for each component, and a switch is used to update appropriate counter based on ComponentType 
- Option 2 is overcomplication?
- When a component is copied from the library, does it get a new ID or does it keep the same one? When its added to a circuit, its frequency may change and so technically it is not the same object - better to make all copies get a unique ID - they are stored elswhere in memory in any case so are not actually the same
- This requires defining a custom copy constructor 
- This is different for copy assignment operator, which involves 2 objects that already exist, e.g.
```
Resistor r1(50, 100); // Res1
Resistor r2(50, 200); // Res2

r2 = r1;
```
In this case r2 frequency is changed from 200 to 100. But it is still r2, it should not be given a new ID
- On the other hand, we have r1 and want to make a new resistor with exactly the same properties as r1
```
Resistor r1(50, 100); // Res1
Resistor r2{r1};     
```
Then r2 should not be given the same ID as r1, but rather its own ID - it is a copy of it and so then could be placed in a different circuit with a different frequency - if we wanted to move r1, we use move which keeps the same ID
Copy assignment operator is more like changing the properties of a component (since it requires that it already exists) - there would be no point in assigning a new ID
- So no need for custom copy assignment operator or move semantics
- Rule of 3/5 is not applied here since there is not objects of non-class type (like pointer), the Components do not manually manage the memory and so the default ones are ok as long as the desired task is performed

### Input validation
- User is only allowed to enter values which match values in the file
- validate_component and load_validation file are protected member functions (do not want user to be able to see this or adjust anything inside it), and they are static as we don't want each component to have its own copy of this - each derived class can use the function once to make a difference.

### Analogy
- To have some intuition as to how this program works, consider yourself to be a student in an undergraduate circuits lab. You want to build a circuit using components from the lab demonstrator, who has a "library" of components available. The library which the lab demonstrator has must be components which actually exist - they must past the validation checks in the validation file. You could think of the validation files as catalogues of components which the lab demonstrator can browse and use to choose certain materials or properties which they want to "buy" and have available in their library.
- You want to use one of the components from the library of the lab demonstrator, but you cannot take it directly away from the lab demonstrator, as they are the owner of that specific component, and if they let you take that one component which they own, then no one else in the lab could use it (or you wouldn't be able to use it again). So you must make a copy of the component from the library, at which point you can add it to your circuit. You could initialise a component just by itself and then std::move it to the circuit, but its easier to just clone inside the circuit infastructure. 
- Once you add it to the circuit, it is automatically labelled for you. The lab demonstrator doesn't need to deal with many copies of the same component with the same properties (although they could if they wanted to), so there is no need for the library to have labelled components.
- You can only add series or parallel circuits in one go, and then combine one into another to build circuits.

## Notes
- A resistor has a defined resistance, so it should be a VARIABLE of the resistor - user can then specify what type of resistor / its resistance
- if the derived class doesn’t manage any resources itself, it does not need its own destructor - uses virtual destructor from Component
- since get_frequency is pure virtual, no point in implementing it - but could implement a validation function (range of frequencies) which is later used
- Info function to print out all info of a component
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
- If component is not in library, you cannot add it to a circuit
- component_id = "R"+std::to_string(++resistor_counter); is repeated twice

## To do
- Probably in main circuit function you want to have components be pointers - see in assignment 5 why you wanted FourMomentum to be a pointer to explain a choice of pointers
- Use alias for complex object as in std::map example
- typedef std::complex<double> complex;?
- Circuit class able to detect how many resistors, capacitors, etc in total (component_info, component_list, all_info)
- Potential issue with assignment operator - try copying components and see if any error comes up
- check for empty circuits before computing impedance
- Add tolerance check when frequency is updated in circuit
- What if user doesn't load a validation file first?
- Get components from a circuit using their ID - AND MODIFY THEIR PROPERTIES
- If user does not initialise ptr to circuit, they can still access info of moved from circuit - implement custom move which can return custom message if it has been moved from
- Circuit diagram output
- Tolerance - use distribution to randomise number