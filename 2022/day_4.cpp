#include "../headers/day_4.h"
using namespace std;
typedef vector<vector<int>> input_type;

input_type get_input_day_4(const string &file_path);

string day_4::part1(const string &file_path){
    auto input = get_input_day_4(file_path);

    int cnt = 0;
    for(auto vec : input){
        if((vec[0] <= vec[2] && vec[1] >= vec[3]) || (vec[2] <= vec[0] && vec[3] >= vec[1]))
            cnt++;
    }

    return to_string(cnt);
}

string day_4::part2(const string &file_path){
    auto input = get_input_day_4(file_path);

    int cnt = 0;
    for(auto vec : input){
        if(vec[0] <= vec[3] && vec[2] <= vec[1])
            cnt++;
    }

    return to_string(cnt);
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

input_type get_input_day_4(const string &file_path){
    ifstream file(file_path);
    input_type out;

    string line;
    while(getline(file, line)){
        vector<int> t;

        int n = 0, ind = 0;

        while(ind < line.size() && isdigit(line[ind])){
            n *= 10;
            n += line[ind++] - '0';
        }
        ++ind;
        t.push_back(n);
        n = 0;

        while(ind < line.size() && isdigit(line[ind])){
            n *= 10;
            n += line[ind++] - '0';
        }
        ++ind;
        t.push_back(n);
        n = 0;

        while(ind < line.size() && isdigit(line[ind])){
            n *= 10;
            n += line[ind++] - '0';
        }
        ++ind;
        t.push_back(n);
        n = 0;

        while(ind < line.size() && isdigit(line[ind])){
            n *= 10;
            n += line[ind++] - '0';
        }
        t.push_back(n);

        out.push_back(t);
    }

    file.close();

    return out;
}