### Kuba Kane
# PHYS30762 Project - Analogue Circuits

## Program Summary
This program allows a user to build their own circuit using a Resistor, Capacitor or Inductor. These are all classes derived from a Component abstract base class, which contains a frequency and a unique ID, as well as a function to calculate the impedance of the component, and its magntiude and phase difference (angle). The impedance function uses the complex number library from C++. All of the derived classes are then given a name (e.g. "Wirewound reistor") and a tolerance (e.g. 20%) which is not in the Component abstract class.
 - **Resistor:** Also has capacitance as member function, and then overrides impedance function to return the resistance value as the real entry, and 0 as the imaginary entry.
 - **Capacitor:** Also has resistance as member function, and then overrides impedance function to return 0 as the real entry, and $Z_C = -X_C$ as the imaginary entry (where $Z_C$ is the capacitor impedance, $X_C = 1/\omega C$ is the capacitor reactance, $\omega$ is the angular frequency and $C$ is the capacitance).
 - **Inductor:** Also has inductance as member function, and then overrides impedance function to return 0 as the real entry, and $Z_L = X_L$ as the imaginary entry (where $Z_L$ is the inductor impedance, $X_L = \omega L$ is the inductor reactance, $\omega$ is the angular frequency and $L$ is the inductance).

The Component class has a base info function which outputs the component type, its ID, impedance, frequency, behaviour and impedance magnitude and phase difference. The derived classes also output the name and resistance, capacitance and inductance respectively.

The Circuit class inherits from the Component class, and contains connection as an additional data member which can be Series or Parallel (via enum class). It also contains components as a data member which is a vector of unique pointers to Component objects which stores all of the components in the Circuit. A component is added to a Circuit object via `add_component(std::unique_ptr<Component> component_ptr_in)` (must be a unique pointer to a component). The Circuit class overrides the impedance function and combines the impedances in the components vector (directly if its a series circuit or their inverses if its a parallel circuit). The user is able to add a Circuit as a Component in the Circuit, thus allowing for nesting of circuits.

There is a validation file for the resistors, capacitors and inductors which restrict what values the user can give an object of these types. The code which checks for this is in the Component class, although it is the derived classes which handle the checks.

## User Guidelines
### Running the program as-is
This code was run on VSC using a Windows 11 device. The compilation line used was `g++ -std=c++17 main.cpp Circuit.cpp Resistor.cpp Capacitor.cpp Inductor.cpp Component.cpp -o main.exe -Wall`. The program can then be run by calling the file `main.exe`.

The main file `main.cpp` creates a library of components with no IDs (hence the `false` as the last parameter). Two resistors, two capacitors and two inductors are added (`push_back`) to this library. Components from this library are then cloned into two different series circuits - an RC circuit and an RLC circuit. These circuits are then added in parallel circuit to make one combined circuit. The function `print_all_circuit_info` in the main file is used to print out the overall information of the circuits, as well as the information about all of the components which they contain.

Uncommenting the final two lines inside `main()` show the error message given when the frequency of a circuit is set to a value higher than allowed for one of the components in that circuit.


### Modifying the main file, `main.cpp`
These guidelines are for a user who wishes to use the classes in this program, but modify the main file provided (or make their own).

A user using the classes should note that the Component class is an abstract base class and so cannot be constructed - the derived classes are the only ones which can be used.

The validation files are examples of the constraints imposed on the resistors, capacitors and inductors. A user can add their own file and use the `load_validation_file` function for the three components. That being said, they must only contain the fields listed below, and they must all be seprated by a semicolon. A header can be used at the beginning of the file as long as its on the first line only and starts with a `#`.

 - Component name (i.e. material)
 - Min possible value of component (resistance, capacitance or inductance)
 - Max possible value of component (resistance, capacitance or inductance)
 - Tolerance (0 to 1)
 - Maximum frequency compatible with component 

Note that in the `main.cpp` file, circuits have been initialised as unique pointers, e.g. `auto rlc_circuit = std::make_unique<Circuit>(50, ConnectionType::Series)`. This makes it convenient when adding circuits into circuits, as the `add_component` function for circuits only accepts unique pointers to components.

It is also possible to initialise a circuit normally, e.g. `Circuit series_circuit(60, ConnectionType::Series)`, but if this is then inserted into another circuit, it must be made into a unique pointer first. For example, if adding `series_circuit` to `parallel_circuit`, use:
```
parallel_circuit.add_component(std::make_unique<Circuit>(std::move(series_circuit)))
```
Note the use of `std::move` - this is required in all cases as parallel_circuit will become the owner of series_circuit, so it must be moved from its old address.

In the case where `series_circuit` is not initialised via a unqiue pointer, trying to print the `info()` function after it has been moved will return 0 for all values in the circuit.


## Additional information
For more information on this program, including how it works and design choices, please see [analogue_circuits_report.pdf](Report/analog_circuits_report.pdf).

For an enlarged version of the UML diagram, please see [analogue_circuits_uml.pdf](Report/analog_circuits_uml.pdf), or visit the link https://lucid.app/lucidchart/df2df27e-50a9-475c-90f7-234e81378d8d/view.


## Disclosure of Delegation to Generative AI
The author (Kuba Kane) declares the use of generative AI in the research and coding process. The following tasks were delegated to GAI tools under full human supervision:

- Idea generation
- Code generation
- Code optimisation
- Code debugging

The GAI tools used for these tasks were: ChatGPT-5.2 (Plus), Claude Sonnet 4.6.

The author declares that the work does not contain any AI-generated code or text. GAI was used as a source of information for explaining code only, and as an inspiration to write original code. 

Responsibility for the final manuscript lies entirely with the author.

GAI tools are not listed as authors and do not bear responsibility for the final outcomes.