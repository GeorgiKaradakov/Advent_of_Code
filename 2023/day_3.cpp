#include "../headers/day_3.h"
using namespace std;
typedef pair<vector<pair<int, set<pair<int, int>>>>, vector<pair<int, int>>> input_type;

int dx[8] = {-1, 0, 1, 0, -1, 1, 1, -1},
    dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};

input_type get_input3(int part);

string day_3::part1(){
    auto kv = get_input3(1);
    auto nums = kv.first;
    auto symbols = kv.second;

    int sum = 0;
    
    for(auto p : nums){
        int num = p.first;
        for(auto xy : symbols){
            int x = xy.first, y = xy.second;

            for(int i = 0; i < 8; i++){
                auto newxy = pair<int, int>{x + dx[i], y + dy[i]};

                if(p.second.count(newxy)){
                    sum += num;
                    break;
                }
            }
        }
    }
    
    return to_string(sum);
}

string day_3::part2(){
    auto kv = get_input3(2);
    auto nums = kv.first;
    auto symbols = kv.second;

    int sum = 0;

    for(auto p : symbols){
        int x = p.first, y = p.second;
        int cnt = 0;
        int mult = 1;
        unordered_set<int> visited;
        
        for(int i = 0; i < 8; i++){
            auto newxy = pair<int, int>{x + dx[i], y + dy[i]};
            for(auto n : nums){
                if(!visited.count(n.first) && n.second.count(newxy)){
                    cnt++;
                    visited.insert(n.first);
                    mult *= n.first;
                }
            }
        }

        if(cnt == 2){
            sum += mult;
        }
    }

    return to_string(sum);
}

input_type get_input3(int part){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input3.txt" : "inputs/input3.txt");

    vector<pair<int, set<pair<int, int>>>> nums;
    vector<pair<int, int>> symbols;

    string line;
    int j = 0;
    while(getline(file, line)){
        int cnt_nums = 0;
        set<pair<int, int>> p;

        string num;
        for(int i = 0; i < line.size(); i++){
            if(isdigit(line[i])){
                num += line[i];
                p.insert({j, i});
            }else{
                if(!num.empty()){
                    nums.push_back({atoi(num.c_str()), p});
                    num = "";
                    p.clear();
                }
                if(part == 1 && line[i] != '.'){
                    symbols.push_back({j, i});
                }

                if(part == 2 && line[i] == '*'){
                    symbols.push_back({j, i});
                }
            }
        }
        if(!num.empty()){
            nums.push_back({atoi(num.c_str()), p});
            num = "";
            p.clear();
        }

        j++;
    }

    return {nums, symbols};
}