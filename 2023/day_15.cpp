#include "../headers/day_15.h"
using namespace std;
typedef vector<string> input_type;
typedef uint64_t ui64;

input_type get_input_day_15();
int get_hash(const string &str);

string day_15::part1(){
    auto input = get_input_day_15();
    ui64 sum = 0;

    for(auto str : input){
        int hash = get_hash(str);
        sum += hash;
    }

    return to_string(sum);
}

string day_15::part2(){
    auto input = get_input_day_15();
    vector<vector<pair<string, int>>> boxes(256);

    for(auto line : input){
        istringstream iss(line);
        int box;
        string label;

        if(line.find('=') != string::npos){
            int num;
            getline(iss, label, '=');
            iss >> num;
            box = get_hash(label);

            bool found = 0;
            for(int i = 0; i < boxes[box].size(); i++){
                if(boxes[box][i].first == label){
                    boxes[box][i].second = num;
                    found = 1;
                    break;
                }
            }
            if(!found)
                boxes[box].push_back({label, num});
        }else{
            getline(iss, label, '-');
            box = get_hash(label);

            if(boxes[box].empty())continue;

            if(boxes[box].back().first == label){
                boxes[box].pop_back();
                continue;
            }

            bool found = 0;
            for(int i = 0; i < boxes[box].size() - 1; i++){
                if(boxes[box][i].first == label)
                    found = 1;

                if(found){
                    swap(boxes[box][i], boxes[box][i + 1]);
                }
            }

            if(found)
                boxes[box].pop_back();
        }
    }

    ui64 sum = 0;
    for(int i = 0; i < 256; i++){
        if(!boxes[i].empty()){
            for(int j = 0; j < boxes[i].size(); j++){
                sum += (i + 1) * (j + 1) * boxes[i][j].second;
            }
        }
    }

    return to_string(sum);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

int get_hash(const string &str){
    int res = 0;
     
    for(auto ch : str){
        res += (int)ch;
        res *= 17;
        res %= 256;
    }

    return res;
}

input_type get_input_day_15(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input15.txt" : "inputs/input15.txt");

    input_type out;
    string line;
    while(getline(file, line, ',')){
        out.push_back(line);
    }

    return out;
}