#include "../headers/day_1.h"
using namespace std;

vector<string> get_lines1();
int get_num(const string &line);

string day_1::part1(){
    auto lines = get_lines1();

    int sum = 0;
    for(auto line : lines){
        sum += get_num(line);
    }

    return to_string(sum);
}

string day_1::part2(){
    auto lines = get_lines1();
    unordered_map<string, char> digs{
        {"one", '1'}, {"two", '2'}, {"three", '3'}, {"four", '4'}, {"five", '5'}, {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'}
    };
    set<char> check = {'o', 't', 'f', 's', 'e', 'n'};

    int sum = 0;
    for(auto line : lines){
        string transformed, t;
        for(int i = 0; i < line.size(); i++){
            if(isdigit(line[i])) // add the digits
                transformed += line[i];
            if(check.count(line[i])){ //check if any of the digits' first char equals line[i] and build the digit if it is correct
                for(int j = i; j <= i + 5; j++){
                    t += line[j];
                    if(digs.count(t)){
                        transformed += digs[t];
                        break;
                    }
                }
                t = "";
            }
        }

        if(!t.empty()){
            if(digs.count(t))
                transformed += digs[t];
        }

        sum += get_num(transformed);
    }

    return to_string(sum);
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

int get_num(const string &line){
    int ind = 0;
    string num;
    while(!isdigit(line[ind]))++ind;
    num += line[ind];
    ind = line.size() - 1;
    while(!isdigit(line[ind]))--ind;
    num += line[ind];

    return atoi(num.c_str());
}

vector<string> get_lines1(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input1.txt" : "inputs/input1.txt");

    string line;
    vector<string> v;
    while(getline(file, line)){
        v.push_back(line);
    }

    return v;
}