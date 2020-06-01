//
// Created by notpyxl on 30/05/20.
//

#ifndef BAYESIAN_NETWORK_BAYESIAN_NET_H
#define BAYESIAN_NETWORK_BAYESIAN_NET_H

#include "not_pandas.h"

typedef std::vector<std::vector<bool>> graph;

class bayesian_net {
    graph states;
public:
    int v;
    int dim;
    not_pandas not_pd;
    bayesian_net();
    bayesian_net(std::string filename);
    void add_edge(int src, int dest);

    void print_net();
    std::vector<int> get_parents(int);
    float bic();
    std::string inference(const int &target,const std::vector<std::string> &parameters);
};


#endif //BAYESIAN_NETWORK_BAYESIAN_NET_H
