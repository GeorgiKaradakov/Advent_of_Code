#include "../headers/day_12.h"
using namespace std;
typedef int64_t i64;
typedef multimap<string, vector<int>> input_type;

input_type get_input_day_12(int part);
i64 recurse(const string &line, const vector<int> &groups, map<tuple<int, int, int>, i64> &memo, int line_ind, int hash_cnt, int group_ind);

string day_12::part1(){
    auto cont = get_input_day_12(1);
    map<tuple<int, int, int>, i64> memo;
    i64 sum = 0;
    
    for(auto kv : cont){
        i64 score = recurse(kv.first, kv.second, memo, 0, 0, 0);
        sum += score;
        memo.clear();
    }


    return to_string(sum);
}

string day_12::part2(){
    auto cont = get_input_day_12(2);
    map<tuple<int, int, int>, i64> memo;
    i64 sum = 0;
    
    for(auto kv : cont){
        i64 score = recurse(kv.first, kv.second, memo, 0, 0, 0);
        sum += score;
        memo.clear();
    }


    return to_string(sum);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

i64 recurse(const string &line, const vector<int> &groups, map<tuple<int, int, int>, i64> &memo, int line_ind, int hash_cnt, int group_ind){
    if(memo.find({line_ind, hash_cnt, group_ind}) != memo.end())
        return memo.find({line_ind, hash_cnt, group_ind})->second;

    if(line_ind == line.size()){
        if(hash_cnt == 0 && group_ind == groups.size())return 1;
        else if(group_ind == groups.size() - 1 && groups[group_ind] == hash_cnt)return 1;
        else return 0;
    }

    i64 total = 0;
    const auto &ch = line[line_ind];

    if(ch == '#' || ch == '?'){
        total += recurse(line, groups, memo, line_ind + 1, hash_cnt + 1, group_ind);
    }

    if(ch == '.' || ch == '?'){
        if(hash_cnt == 0)
            total += recurse(line, groups, memo, line_ind + 1, 0, group_ind);
        else if(group_ind < groups.size() && groups[group_ind] == hash_cnt)
            total += recurse(line, groups, memo, line_ind + 1, 0, group_ind + 1);
    }

    memo[{line_ind, hash_cnt, group_ind}] = total;
    return total;
}

input_type get_input_day_12(int part){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input12.txt" : "inputs/input12.txt");

    input_type out;

    string line;
    while(getline(file, line)){
        istringstream iss(line);

        string s;
        iss >> s;

        vector<int> v;
        int num;
        while(iss >> num){
            v.push_back(num);
            iss.ignore(1);
        }

        if(part == 2){
            stringstream folded_str;
            vector<int> folded_v;
            folded_str << s << '?' << s << '?' << s << '?'<< s << '?'<< s;
            for(int _ = 0; _ < 5; _++){
                for(int i = 0; i < v.size(); i++){
                    folded_v.push_back(v[i]);
                }
            }

            out.emplace(folded_str.str(), folded_v);
        }else if(part == 1)
            out.emplace(s, v);
    }

    return out;
}