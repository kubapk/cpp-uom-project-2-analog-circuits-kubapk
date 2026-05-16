/*
____________________________________________
COMPONENT IMPLEMENTATION
(Part of PHYS30762 Analogue Circuit Project)
____________________________________________
Implementation file for "Component" class.

Created by Kuba Kane (ID: 11019699)
Created on Mon 04 May 2026
*/

#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream> //reading files
#include "Component.h"
using std::string;

//CONSTRUCTORS
//Default constructor
Component::Component() :
  frequency{0} {}

//Paramterised constructor
Component::Component(const double frequency_in) :
    frequency{frequency_in} {}

//Copy constructor
//Copy assignment operator
//Move constructor
//Move assignment operator


//SETTERS
//Validation for setter
//You may want private member function which does general validatio needed in setter and 
//parameterised constructor 
//Maybe validation comes after implementing everything else

//Setter for frequency
/* Could have the setter below - but its pointless because in .h we have defined it as pure virtual
so it will be ovewritten anyway
void Component::set_frequency(const double frequency_in)
{
  frequency = frequency_in;
}
*/

//Getter
//Component ID getter
const string& Component::get_id() const
{
  return component_id;
}

//Behaviour getter
string Component::get_behaviour() const
{
  double phase{get_phase_difference()};

  if(phase > numerical_tolerance) //phase>0
    return "Inductive (voltage leads current)";
  
  else if(phase < -numerical_tolerance) //phase<0
    return "Capacitive (current leads voltage)";

  else
    return "Resistive";
}


//MEMBER FUNCTIONS
//Base info protected member function
void Component::base_info() const
{
  string symbol{""};
  double impedance_real{get_impedance().real()};
  double impedance_imag{get_impedance().imag()}; 

  if(impedance_imag >= 0)
    symbol = "+ ";

  std::cout<<"==="<<type_to_string(get_type())<<"==="<<std::endl;
  std::cout<<"ID: "<<component_id<<std::endl;
  std::cout<<"Impedance: "<<impedance_real<<" "<<symbol<<impedance_imag<<"i Ohms"<<std::endl;
  std::cout<<"Frequency: "<<frequency<<" Hertz"<<std::endl;
  std::cout<<"Impedance magnitude: "<<get_impedance_magnitude()<<" Ohms"<<std::endl;
  std::cout<<"Phase difference: "<<get_phase_difference()<<" rad"<<std::endl;
  std::cout<<"Behaviour: "<<get_behaviour()<<std::endl;
}

//Static protected member function to convert types to string output
string Component::type_to_string(const ComponentType type_in)
{
  switch(type_in)
  {
    case ComponentType::Resistor:
      return "Resistor";

    case ComponentType::Capacitor:
      return "Capacitor";

    case ComponentType::Inductor:
      return "Inductor";

    case ComponentType::Circuit:
      return "Circuit";
  }
  throw std::logic_error("Unknown component type when trying to convert type to string.");
}

//Static protected member function to load in validation file
void Component::load_validation_file(const string& file_name_in, vector<ValidationRecord>& all_records, 
  const ComponentType type_in)
  {
    string component_type_str{type_to_string(type_in)};

    std::ifstream read_file(file_name_in);

    //Check if file opened correctly
    if(!read_file.good())
      throw std::runtime_error(component_type_str+" validation file '"+file_name_in+" could not be opened");

    //Clear record in case there is something carried over
    all_records.clear(); //reason record_in cannot be const

    string line; //read in one whole line from data file

    //For each line in the file
    while(std::getline(read_file, line))
    {
      //Ignore blank lines or header lines
      if(line.empty() || line[0]=='#')
        continue;

      //Create string stream and one Record object to store data
      std::stringstream ss(line);
      ValidationRecord record;

      //Check correct delimiter between all fields in line
      string name_str, min_str, max_str, tolerance_str, frequency_str;
      if
      (
        !std::getline(ss, name_str, ';') ||
        !std::getline(ss, min_str, ';') ||
        !std::getline(ss, max_str, ';') ||
        !std::getline(ss, tolerance_str, ';') ||
        !std::getline(ss, frequency_str, ';')
      )
      {
        //Show error message but continue program
        std::cerr<<component_type_str<<" validation file error: The line {"<<line<<"} in '"<<
          file_name_in<<"' is incorrectly formatted. Line will not contribute."<<std::endl;

        continue;
      }

      //Lamba function applied to each field to check for blank lines
      auto check_blank = [&line, &component_type_str](const string& field, const string& field_name)
      {
        if(field.empty())
        {
          std::cerr<<component_type_str<<" validation file error: The line {"<<line<<
            "} contains a blank"<<field_name<<". Line will not contribute."<<std::endl;

          return true; //is blank
        }

        return false; //is not blank
      };
      //[] part says it has acces by reference to the line variable & component type str
      //() part defines what the function takes as an input
      //{} part is the definition of the funtion
      //Why lambda? Has access to line without needing to pass it in each time (and we are on
      //the same line within one loop)

      //Blank line checks for each field
      if(check_blank(name_str, "name")) {continue;}
      if(check_blank(min_str, "min "+component_type_str+" value")) {continue;}
      if(check_blank(max_str, "max "+component_type_str+" value")) {continue;}
      if(check_blank(tolerance_str, "tolerance")) {continue;}
      if(check_blank(frequency_str, "maximum frequency")) {continue;}

      //Lambda function to check for extra characters at end of each field
      auto parse_double = [&line, &component_type_str](const string& field, const string& field_name, double& output)
      {
        std::stringstream field_ss(field); //Create new steam to capture just one field (not whole line/record)
        string extra; //empty string to catch anything extra after double

        //Return true if field_ss cannot extract double from output (the field), or if it can extract more characters after 
        //reading output
        if(!(field_ss >> output) || (field_ss>>extra))
        {
          std::cerr<<component_type_str<<" validation file error: Extra or invalid characters in "<<
            field_name<<" in the line {"<<line<<"}. Line will not contribute."<<std::endl;

          return false; //parse failed
        }

        return true;
      };

      //Extra character checks for each field (also adds to record)
      if(!parse_double(min_str, "min "+component_type_str+" value", record.min_value)) {continue;}
      if(!parse_double(max_str, "max "+component_type_str+" value", record.max_value)) {continue;}
      if(!parse_double(tolerance_str, "tolerance", record.tolerance)) {continue;}
      if(!parse_double(frequency_str, "maximum frequency", record.max_frequency)) {continue;}

      //No need to parse string for extra characters
      record.name = name_str;

      //Add record to vector of records
      all_records.push_back(record);

    }

    //ADD CHECKS FOR MIN, MAX, TOLERANCE, FREQUENCY, NAME CANNOT BE TOO LONG
  }

//Protected member function to validate component (check exists in file)
void Component::validate_component(const vector<ValidationRecord>& all_records, const ComponentType& type_in,
        const string& name_in, const double frequency_in, const double value_in, const double tolerance_in)
{
  //Get component name string
  string type_str{type_to_string(type_in)};

  //For each record in all_records (vector of records)
  for(const ValidationRecord& record : all_records)
  {
    //Check if name matches
    if()
  }

}