#include "../headers/day_10.h"
using namespace std;
typedef vector<pair<string, int>> input_type;

input_type get_input_day_10(const string &file_path);

string day_10::part1(const string &file_path){
    auto input = get_input_day_10(file_path);

    int X = 1, res = 0;
    int cycles = 0, factor = 20;
    for(auto line : input){
        int ticks;
        bool is_addx = 0;
        if(line.first == "noop"){
            ticks = 1;
        }else{
            ticks = 2;
            is_addx = 1;
        }

        while(ticks--){
            cycles++;
            if(cycles == factor){
                res += X * cycles;
                factor += 40;
            }
        }

        if(is_addx)X += line.second;
    }
    
    return to_string(res);
}

string day_10::part2(const string &file_path){
    auto input = get_input_day_10(file_path);
    const int HEIGHT = 6;

    auto get_index = [](int cycles) -> int{
        if(cycles < 40)return 0;
        else if(cycles < 80)return 1;
        else if(cycles < 120)return 2;
        else if(cycles < 160)return 3;
        else if(cycles < 200)return 4;
        else if(cycles < 240)return 5;
        else return -1;
    };

    string CRT[HEIGHT]{""};

    int X = 1;
    int cycles = 0;
    for(auto line : input){
        int ticks;
        bool is_addx = 0;
        if(line.first == "noop"){
            ticks = 1;
        }else{
            ticks = 2;
            is_addx = 1;
        }

        while(ticks--){
            int ind = cycles % 40;
            if(ind == X - 1 || ind == X || ind == X + 1){
                CRT[get_index(cycles)] += '#';
            }else{
                CRT[get_index(cycles)] += '.';
            }
            cycles++;
        }

        if(is_addx)X += line.second;
    }

    string res;
    for(int i = 0; i < HEIGHT; i++){
        res += CRT[i];
        res += '\n';
    }

    return res;
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

input_type get_input_day_10(const string &file_path){
    ifstream file(file_path);
    input_type out;

    string line;
    while(getline(file, line)){
        istringstream iss(line);
        string token;

        iss >> token;

        if(token == "noop")
            out.push_back({token, 0});
        else{
            int val;
            iss >> val;
            out.push_back({token, val});
        }
    }

    file.close();
    return out;
}