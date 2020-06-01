//
// Created by notpyxl on 30/05/20.
//

#include <cmath>
#include "bayesian_net.h"

bayesian_net::bayesian_net() {
    states = std::vector<std::vector<bool>> (not_pd.shape().second,
        std::vector<bool> (not_pd.shape().second, false)) ;
}

void bayesian_net::add_edge(int src, int dest) {
    states[src][dest] = true;
}

bayesian_net::bayesian_net(std::string filename) {
    not_pd.read_csv(filename);
    states = std::vector<std::vector<bool>> (not_pd.shape().second,
                                             std::vector<bool> (not_pd.shape().second, false)) ;
    v = states.size();
}

void bayesian_net::print_net() {
    for(auto&i:states) {
        for (auto j:i)
            std::cout << j << ' ';
        std::cout << '\n';
    }
    std::cout<<'\n';
}

std::vector<int> bayesian_net::get_parents(int j) {
    std::vector<int> parents;
    for(int i=0;i<not_pd.shape().second;++i){
        if(states[i][j])
            parents.push_back(i);
    }
    return parents;
}

// The target has to be always in the last column
std::string bayesian_net::inference(const int& target,const std::vector<std::string>& parameters) {
    std::vector<std::string> classes;
    for(auto&i:not_pd.value_counts(target).counting)
        classes.push_back(i.first);

    std::map<std::vector<std::string>, float> scores;
    for(auto&i:classes)
        scores[not_pd.tmp_insert(parameters, i)] = 1;

    for(auto&score:scores){
        for(int p=0;p<states.size();++p){
            std::vector<std::string> parent_params;
            for(auto&i:get_parents(p))
                parent_params.push_back(score.first[i]);

            parent_params.push_back(score.first[p]);
            float f = not_pd.
                cond_prob(p, get_parents(p), 1, true)[parent_params];
            score.second *= f;
        }
    }

    std::string predict;
    float max = 0;
    for(auto&i:scores){
        if(i.second > max) {
            max = i.second;
            predict = i.first[i.first.size() - 1];
        }
    }

    return predict;
}

float bayesian_net::bic() {

    float log_likelihood = 0;

    float dim_g = 0;
    for(int x=1;x<states.size();++x){
        for(auto&c:not_pd.value_counts(x).counting){
            auto cond_prob = not_pd.cond_prob(x,get_parents(x), 1, true);
            std::map<std::vector<std::string>, int> reps;

            for(auto&i:cond_prob){
                auto tmp_string = i.first[i.first.size()-1];
                std::vector<std::string> tmp_vector;
                i.first.pop_back();
                tmp_vector = i.first;
                reps[tmp_vector]++;
                i.first.push_back(tmp_string);
            }
            for(auto&prob:cond_prob){
                for(auto&rep:reps) {
                    if ((std::equal(prob.first.begin(), prob.first.end()-1, rep.first.begin()))
                        and c.first == prob.first[prob.first.size()-1]
                    ) {
                        log_likelihood += c.second * log2(prob.second);
                    }
                }
            }
        }
    }

    std::cout<<dim_g<<'\n';
    return log_likelihood - (log2(not_pd.shape().first)/2 + dim_g);
}

