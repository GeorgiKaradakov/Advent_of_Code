#include "../headers/day_5.h"
using namespace std;
typedef pair<vector<vector<char>>, vector<vector<int>>> input_type;

input_type get_input_day_5(const string &file_path);

string day_5::part1(const string &file_path){
    auto input = get_input_day_5(file_path);
    auto crates = input.first;
    auto cmds = input.second;

    for(auto cmd : cmds){
        while(cmd[0]--){
            crates[cmd[2]].push_back(crates[cmd[1]].back());
            crates[cmd[1]].pop_back();
        }
    }

    string res;
    for(int i = 0; i < crates.size(); i++){
        if(crates[i].empty())continue;
        res += crates[i].back();
    }

    return res;
}

string day_5::part2(const string &file_path){
    auto input = get_input_day_5(file_path);
    auto crates = input.first;
    auto cmds = input.second;

    for(auto cmd : cmds){
        int t = cmd[0];
        while(t--){
            crates[cmd[2]].push_back(crates[cmd[1]].back());
            crates[cmd[1]].pop_back();
        }
        if(cmd[0] == 1)continue;

        reverse(crates[cmd[2]].end() - cmd[0], crates[cmd[2]].end());
    }

    string res;
    for(int i = 0; i < crates.size(); i++){
        if(crates[i].empty())continue;
        res += crates[i].back();
    }

    return res;
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

input_type get_input_day_5(const string &file_path){
    /*
        changed the input: for each create do that -> number: chars (ex. "1: Z N")
    */

    ifstream file(file_path);

    vector<vector<char>> crates(10);
    vector<vector<int>> commands;

    string line;
    while(getline(file, line)){
        if(line.empty())continue;

        istringstream iss(line);
        if(isdigit(line[0])){
            int ind = 0;
            string token;
            iss >> token;
            ind = stoi(token.substr(0, token.size() - 1));

            while(iss >> token){
                crates[ind].push_back(token[0]);
            }
        }else{
            vector<int> t;

            string token;
            while(iss >> token){
                if(isdigit(token[0]))
                    t.push_back(stoi(token));
            }

            commands.push_back(t);
        }
    }

    file.close();

    return {crates, commands};
}