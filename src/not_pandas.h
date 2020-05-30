//
// Created by notpyxl on 16/05/20.
//

#ifndef BAYESIAN_NETWORK_NOT_PANDAS_H
#define BAYESIAN_NETWORK_NOT_PANDAS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "variable.h"

typedef std::vector<std::vector<std::string>> dataframe;

class not_pandas {
    dataframe df;
    std::vector<std::string> headers;
    unsigned long rows;
    unsigned long cols;

public:

    not_pandas();
    explicit not_pandas(std::string& filename);
    void read_csv(const std::string& filename);
    void head();
    void head(int n);
    std::pair<int,int> shape();

    std::vector<std::string> operator [](int col);

    std::vector<std::string> get_headers();

    variable value_counts(const int &j);

    variable value_counts(const int &j, const bool&);

    variable value_counts(const int &j, const int&);

    std::map<std::vector<std::string>, float> joint_prob(const std::vector<int>& vars, int hyper_alpha);
    std::map<std::vector<std::string>, float> cond_prob(const int&j, const std::vector<int>& conditionals,
        int hyper_alpha, bool normalize);
};

#endif //BAYESIAN_NETWORK_NOT_PANDAS_H