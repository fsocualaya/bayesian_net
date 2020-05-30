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
    not_pandas not_pd;
    bayesian_net();
    void add_edge();


};


#endif //BAYESIAN_NETWORK_BAYESIAN_NET_H
