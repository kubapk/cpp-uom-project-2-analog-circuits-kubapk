#include <map>

std::map<std::string,int>
Circuit::count_components() const
{
    std::map<std::string,int> counts;

    for(const auto& component : components)
    {
        // If nested circuit
        if(auto subcircuit =
           dynamic_cast<Circuit*>(
               component.get()))
        {
            auto subcounts =
                subcircuit->count_components();

            for(const auto& [type,count]
                : subcounts)
            {
                counts[type] += count;
            }
        }

        else
        {
            counts[
                component->get_type()
            ]++;
        }
    }

    return counts;
}