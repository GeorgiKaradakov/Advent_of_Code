#include "../headers/day_11.h"
using namespace std;
typedef pair<vector<vector<vector<int>>>, vector<vector<char>>> input_type;

input_type get_input_day_11(int part);

string day_11::part1(){
    auto kv = get_input_day_11(1);
    auto offsets = kv.first;
    auto mat = kv.second;

    vector<pair<int, int>> hashes;

    for(int x = 0; x < mat.size(); x++){
        for(int y = 0; y < mat[x].size();y++){
            if(mat[x][y] == '#'){
                hashes.push_back({x + offsets[x][y][1], y + offsets[x][y][0]});
            }
        }
    }

    int sum = 0;

    for(int i = 0; i < hashes.size(); i++){
        for(int j = i + 1; j < hashes.size(); j++){
            auto lhs = hashes[i], rhs = hashes[j];

            sum += abs(lhs.first - rhs.first) + abs(lhs.second - rhs.second);
        }
    }

    return to_string(sum);
}

string day_11::part2(){//has a problem does not work
    auto kv = get_input_day_11(2);
    auto offsets = kv.first;
    auto mat = kv.second;

    vector<pair<int, int>> hashes;

    for(int x = 0; x < mat.size(); x++){
        for(int y = 0; y < mat[x].size();y++){
            if(mat[x][y] == '#'){
                hashes.push_back({x + offsets[x][y][1], y + offsets[x][y][0]});
            }
        }
    }

    uint64_t sum = 0;

    for(int i = 0; i < hashes.size(); i++){
        for(int j = i + 1; j < hashes.size(); j++){
            auto lhs = hashes[i], rhs = hashes[j];

            sum += abs(lhs.first - rhs.first) + abs(lhs.second - rhs.second);
        }
    }

    return to_string(sum);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

input_type get_input_day_11(int part){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input11.txt" : "inputs/input11.txt");

    vector<vector<char>> map;
    
    string line;
    while(getline(file, line)){
        map.push_back({line.begin(), line.end()});
    }

    unordered_map<int, int> rows, cols;

    int tmp = 0;
    int prev = 0;
    for(int y = 0; y < map[0].size(); y++){
        bool contains_hash = 0;
        for(int x = 0; x < map.size(); x++){
            if(map[x][y] == '#'){
                contains_hash = 1;
                break;
            }
        }

        if(!contains_hash){
            for(int i = prev; i < y; i++){
                rows[i] = tmp;
            }
            tmp += part == 1 ? 1 : 1000000;
            prev = y;
        }
    }
    for(int i = prev; i <= map[0].size(); i++)
        rows[i] = tmp;

    tmp = 0;
    prev = 0;
    for(int x = 0; x < map.size(); x++){
        bool contains_hash = 0;
        for(int y = 0; y < map[x].size(); y++){
            if(map[x][y] == '#'){
                contains_hash = 1;
                break;
            }
        }
        if(!contains_hash){
            for(int i = prev; i < x; i++){
                cols[i] = tmp;
            }
            tmp += part == 1 ? 1 : 1000000;
            prev = x;
        }
    }
    for(int i = prev; i <= map.size(); i++)
        cols[i] = tmp;

    vector<vector<vector<int>>> offsets;
    for(int x = 0; x < map.size(); x++){
        vector<vector<int>> p;
        for(int y = 0; y < map[x].size(); y++){
            p.push_back({rows[y], cols[x]});
        }
        offsets.push_back(p);
    }

    return {offsets, map};
}