//
// Created by notpyxl on 16/05/20.
//


#include "not_pandas.h"

std::vector<std::string> tmp_insert(std::vector<std::string> c, std::string value){
    c.push_back(value);
    return c;
}

std::vector<std::vector<std::string>> row_product(const std::vector<std::string>& r1,const std::vector<std::vector<std::string>>& comb){
    std::vector<std::vector<std::string>> perm;
    for(auto&i:comb){
        for(auto&j:r1){
            auto tmp = tmp_insert(i, j);
            perm.push_back(tmp);
        }
    }
    return perm;
}

void not_pandas::read_csv(const std::string&filename) {
    std::fstream file(filename, std::ios::in);
    std::string tmp_line;

    std::string field;

    // Read Headers
    getline(file, tmp_line);
    std::istringstream iss(tmp_line);
    while(std::getline(iss, field, ',')){
        headers.push_back(field);
    }

    cols = (headers.size()!=0)?headers.size():cols;

    while(file >> tmp_line) {
        iss.clear();
        iss.str(tmp_line);
        std::vector<std::string> row;
        while(std::getline(iss, field, ',')){
            row.push_back(field);
        }
        df.push_back(row);
    }
    file.close();

    rows = (df.size()!=0)?df.size():rows;

    // Add counting for each variable
    // count();
}


not_pandas::not_pandas() {
    rows = cols = 0;
}

void not_pandas::head(int n) {
    for(auto&i:headers)
        std::cout<<i<<',';
    std::cout<<'\n';

    if(rows < n)
        n = (int)rows;

    for(int i=0; i < n; ++i) {
        for(auto&j:df[i])
            std::cout<<j<<',';
        std::cout<<'\n';
    }
}

void not_pandas::head() {
    head(5);
}

std::pair<int, int> not_pandas::shape() {
    return {rows, cols};
}

std::vector<std::string> not_pandas::operator[](int col) {
    std::vector<std::string> column(rows);
    for(int row=0;row<rows;++row)
        column[row] = df[row][col];
    return column;
}

std::vector<std::string> not_pandas::get_headers() {
    return headers;
}

variable not_pandas::value_counts(const int& j) {
    variable var;
    var.name = headers[j];

    for(int i=0;i<rows;++i){
        var.counting[df[i][j]]++;
    }

    return var;
}

variable not_pandas::value_counts(const int& j, const bool& normalize) {
    auto var = value_counts(j);
    if(normalize) {
        for (auto &i:var.counting)
            i.second = (float) i.second / rows;
    }
    return var;
}

variable not_pandas::value_counts(const int &j, const int& hyper_alpha) {
    auto var = value_counts(j);

    for(auto &i:var.counting){
        i.second = (i.second + (float)hyper_alpha) / (float)(rows + hyper_alpha * var.counting.size());
    }

    return var;
}

not_pandas::not_pandas(std::string& filename) {
    read_csv(filename);

    rows = df.size();
    cols = headers.size();
}

std::map<std::vector<std::string>, float> not_pandas::joint_prob(const std::vector<int>& vars, int hyper_alpha) {

    std::vector<std::vector<std::string>> classes;

    // Get all the classes for each variable into one vector of vectors
    for(int var : vars) {
        std::vector<std::string> variable_tmp;
        for (auto &obs:value_counts(var).counting) {
            variable_tmp.push_back(obs.first);
        }
        classes.push_back(variable_tmp);
    }

    int den = 1;
    for(auto&i:classes){
        den*=i.size();
    }

    // Initialize the vector that will contain all the permutations
    std::vector<std::vector<std::string>> comb;
    for(auto&i:classes[0]){
        std::vector<std::string> tmp(1, i);
        comb.push_back(tmp);
    }

    // Do the permutations
    for(int i=1;i<classes.size();++i){
        comb = row_product(classes[i], comb);
    }

    // Initialize the map for all the permutations in zero
    std::map<std::vector<std::string>, float> count;
    for(auto&i:comb)
        count[i] = 0;

    // Do the math: increment all the occurrences in the dataset for each permutation
    std::vector<std::string> tmp(vars.size());
    for(int i=0;i<rows;++i){
        for(int j=0;j<vars.size();j++){
            tmp[j] =  df[i][vars[j]];
        }
        count[tmp]++;
    }

    // Do the math: normalize all the frequencies in the count map

    for(auto&i:count){
        i.second = (i.second + hyper_alpha) / (float)(rows + den * hyper_alpha);
    }

    return count;

}

std::map<std::vector<std::string>, float>
not_pandas::cond_prob(const int &j, const std::vector<int> &conditionals, int hyper_alpha, bool normalize) {

    auto tmp = conditionals;
    tmp.push_back(j);

    auto den = joint_prob(conditionals, hyper_alpha);
    auto num = joint_prob(tmp, hyper_alpha);

    std::map<std::vector<std::string>, float> sums;

    for(auto &i:num){
        for(auto&k:den){
            if(std::equal(i.first.begin(), i.first.end()-1, k.first.begin())){
                i.second = i.second / k.second;
                sums[k.first] += i.second;
            }
        }
    }

    if(normalize) {
        for (auto &i:num) {
            std::string tmp_var = i.first[i.first.size()-1];
            i.first.pop_back();
            i.second = i.second / sums[i.first];
            i.first.push_back(tmp_var);
        }
    }
    return num;
}




/*
void not_pandas::count() {
    counting.resize(shape().second);

    for(int i=0;i<shape().second;++i){
        auto _count = value_counts(i, 1); // do the count for each parameter
        counting[i] = _count;
    }
}*/