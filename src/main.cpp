#include "not_pandas.h"

int main() {
    not_pandas not_pd;
    not_pd.read_csv("../../res/weather.csv");

    not_pd.head();
    std::cout<<"shape: "<<not_pd.shape().first<<' '<< not_pd.shape().second<<'\n';

    // Marginal Prob for each variable:}
    /*
    for(int i = 0; i<not_pd.get_headers().size(); ++i) {
        std::cout<<not_pd.get_headers()[i] <<'\n';
        for(auto&j:not_pd.value_counts(i,1).counting){
            std::cout<<'\t'<<j.first<<": "<<j.second<<'\n';
        }
    }*/

    for(auto&i:not_pd.cond_prob(0, {3,4}, 1, true)){
        for(auto&j:i.first)
            std::cout<<j<<' ';
        std::cout<<"\n\t";
        std::cout<<i.second<<'\n';
    }

    return 0;
}
