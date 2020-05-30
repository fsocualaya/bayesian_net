//
// Created by notpyxl on 30/05/20.
//

#include "bayesian_net.h"

bayesian_net::bayesian_net() {
    states = std::vector<std::vector<bool>> (not_pd.shape().second,
        std::vector<bool> (not_pd.shape().second, false)) ;

}
