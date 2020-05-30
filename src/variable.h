//
// Created by notpyxl on 27/05/20.
//

#ifndef BAYESIAN_NETWORK_VARIABLE_H
#define BAYESIAN_NETWORK_VARIABLE_H

#include <map>
#include <vector>

class variable{
public:
    std::string name;
    std::map<std::string, float> counting;
    variable();
};

#endif //BAYESIAN_NETWORK_VARIABLE_H
