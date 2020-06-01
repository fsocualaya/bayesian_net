#include <chrono>
#include "bayesian_net.h"

int main() {
    bayesian_net net("../../data/weather.csv");

    //net.not_pd.head();

    for(int i=0; i < net.v - 1; ++i){
        net.add_edge(4, i);
    }

    /*
    int cond = 4;
    for(int i=0;i<net.not_pd.shape().second;++i){
        std::cout<<"***"<<net.not_pd.get_headers()[i]<<'|'<<net.not_pd.get_headers()[cond]<<"***\n";
        for(auto&j:net.not_pd.cond_prob(i,{cond},1,true)){
            for(auto&k:j.first)
                std::cout<<k<<' ';
            std::cout<<"\n\t"<<j.second<<'\n';
        }
    }
*/

    net.print_net();

    for(auto&i:net.get_parents(0))
        std::cout<<i<<"->"<<0<<'\n';

    auto start = std::chrono::steady_clock::now();
    std::cout<<'\n'<<net.inference(4, {"rainy", "cool", "normal", "TRUE"})<<'\n';
    auto end = std::chrono::steady_clock::now();

    auto diff = std::chrono::duration<double , std::milli> (end-start).count();
    std::cout<<diff<<" ms"<<'\n';

    std::cout<<net.bic()<<'\n';

    return 0;
}
