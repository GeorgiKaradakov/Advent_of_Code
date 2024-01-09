#include "../headers/day_1.h"
using namespace std;
typedef vector<string> input_type;

input_type get_input_day_1(const string &file_path);

string day_1::part1(const string &file_path){
    auto input = get_input_day_1(file_path);

    int res = INT_MIN, curr = 0;

    for(auto str : input){
        if(str.empty()){
            res = max(res, curr);
            curr = 0;
        }else   
            curr += atoi(str.c_str());
    }

    return to_string(max(res, curr));
}

string day_1::part2(const string &file_path){
    auto input = get_input_day_1(file_path);

    int max1 = INT_MIN, max2 = max1, max3 = max2, curr = 0;

    for(auto str : input){
        if(str.empty()){
            if(max1 < curr){
                max3 = max2;
                max2 = max1;
                max1 = curr;
            }else if(max2 < curr){
                max3 = max2;
                max2 = curr;
            }else if(max3 < curr)
                max3 = curr;

            curr = 0;
        }else   
            curr += atoi(str.c_str());
    }

    return to_string(max1 + max2 + max(max3, curr));
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

input_type get_input_day_1(const string &file_path){
    ifstream file(file_path);
    input_type out;

    string line;
    while(getline(file, line)){
        out.push_back(line);
    }

    file.close();

    return out;
}