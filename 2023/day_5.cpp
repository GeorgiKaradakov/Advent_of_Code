#include "../headers/day_5.h"
using namespace std;
typedef uint64_t ull;
typedef pair<vector<ull>, vector<pair<string, vector<ull>>>> input_type;

input_type get_input_day_5();
ull get_loc(const vector<ull>& seeds, const vector<pair<string, vector<ull>>> &intervals, ull seed);

string day_5::part1(){
    auto kv = get_input_day_5();
    auto seeds = kv.first;
    auto intervals = kv.second;

    ull min_loc = INT_MAX;
    for(auto seed : seeds){
        min_loc = min(get_loc(seeds, intervals, seed), min_loc);
    }

    return to_string(min_loc);
}

string day_5::part2(){
    auto kv = get_input_day_5();
    auto seed_intervals = kv.first;
    auto intervals = kv.second;

    ull min_loc = INT_MAX;

    for(int i = 0; i < seed_intervals.size() - 1; i += 2){
        ull start = seed_intervals[i], end = start + seed_intervals[i + 1] - 1;

        ull loc = get_loc(seed_intervals, intervals, start);

        if(start != end){
            ull last_seed_loc = get_loc(seed_intervals, intervals, end);
            loc = min(loc, last_seed_loc);
        }

        min_loc = min(min_loc, loc);
    }

    return to_string(min_loc);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

ull get_loc(const vector<ull>& seeds, const vector<pair<string, vector<ull>>> &intervals, ull seed){
    ull loc = seed;
    for(int i = 0; i < intervals.size(); i++){
        auto name = intervals[i].first;
        auto interval = intervals[i].second;

        if(interval[1] <= loc && loc <= interval[1] + interval[2]){
            loc = interval[0] + (loc - interval[1]);

            while(name == intervals[++i].first);
            --i;
        }
    }

    return loc;
}

input_type get_input_day_5(){
    int t = 0;
    ifstream file(t == 0 ? "inputs/sample_input5.txt" : "inputs/input5.txt");
    vector<ull> seeds;
    vector<pair<string, vector<ull>>> intervals;

    string line;
    while(getline(file, line)){
        istringstream iss(line);
        if(line.find("seeds:") != string::npos){
            ull num;
            iss.ignore(256, ':');
            while(!iss.eof()){
                iss >> num;
                seeds.push_back(num);
            }
        }else if(line.find("map:") != string::npos){
            string name;
            getline(iss, name, '-');
            while(getline(file, line)){
                istringstream t(line);
                if(line.empty())break;
                ull num1, num2, num3;
                t >> num1 >> num2 >> num3;
                intervals.push_back({name, {num1, num2, num3}});
            }
        }
    }

    return {seeds, intervals};
}