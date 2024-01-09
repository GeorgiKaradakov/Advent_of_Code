#include "../headers/day_2.h"
using namespace std;

enum choice{
    rock = 0,
    paper,
    scissors,
    wrong,
};

typedef vector<pair<choice, choice>> input_type;

input_type get_input_day_2(const string &file_path);
bool is_win(choice &lhs, choice &rhs);

string day_2::part1(const string &file_path){
    auto input = get_input_day_2(file_path);

    int res = 0;
    for(auto p : input){
        if(p.first == p.second)res += 3 + p.second + 1;
        else if(is_win(p.first, p.second)) res += 6 + p.second + 1;
        else res += p.second + 1;
    }

    return to_string(res);
}

string day_2::part2(const string &file_path){
    auto input = get_input_day_2(file_path);

    auto get_losing = [](choice &c) -> choice{
        return c == choice::paper ? choice::rock : (c == choice::rock ? choice::scissors : choice::paper);
    };

    auto get_winning = [](choice &c) -> choice{
        return c == choice::paper ? choice::scissors : (c == choice::rock ? choice::paper : choice::rock);
    };

    int res = 0;
    for(auto p : input){
        if(p.second == choice::rock){//loosing
            res += get_losing(p.first) + 1;
        }else if(p.second == choice::paper){//draw
            res += p.first + 1 + 3;
        }else{//winning
            res += get_winning(p.first) + 6 + 1;
        }
    }

    return to_string(res);
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

bool is_win(choice &lhs, choice &rhs){
    return (lhs == choice::paper && rhs == choice::scissors) || (lhs == choice::scissors && rhs == choice::rock) || (lhs == choice::rock && rhs == choice::paper);
}

input_type get_input_day_2(const string &file_path){
    ifstream file(file_path);
    input_type out;

    auto get_choice = [](auto ch) -> choice{
        switch(ch){
            case 'A':
            case 'X':
                return choice::rock;
            
            case 'B':
            case 'Y':
                return choice::paper;

            case 'C':
            case 'Z':
                return choice::scissors;

            default:
                return choice::wrong;
        }
    };

    string line;
    while(getline(file, line)){
        out.push_back({get_choice(line[0]), get_choice(line[2])});
    }

    file.close();

    return out;
}