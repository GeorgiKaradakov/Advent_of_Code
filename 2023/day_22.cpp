#include "../headers/day_22.h"
using namespace std;

struct cube{
    pair<int, int> x, y, z;
    unordered_set<string> supporters;
};

typedef vector<cube> input_type;

input_type get_input_day_22();
bool intersect(const cube &lhs, const cube &rhs);

string day_22::part1(){
    auto cubes = get_input_day_22();
    unordered_map<int, vector<int>> i_contains_j; 
    unordered_map<int, vector<int>> j_contains_i; 

    for(int i = 0; i < cubes.size(); i++){
        for(int j = 0; j < i; j++){
            if(intersect(cubes[i], cubes[j]) && cubes[i].z.first == cubes[j].z.second + 1){
                i_contains_j[j].push_back(i);
                j_contains_i[i].push_back(j);
            }
        }
    }

    int res = 0;
    for(int i = 0; i < cubes.size(); i++){
        res += all_of(i_contains_j[i].begin(), i_contains_j[i].end(), [&](auto ind){return j_contains_i[ind].size() >= 2;});
    }

    return to_string(res);
}

string day_22::part2(){
    auto cubes = get_input_day_22();
    unordered_map<int, vector<int>> i_contains_j; 
    unordered_map<int, vector<int>> j_contains_i; 

    for(int i = 0; i < cubes.size(); i++){
        for(int j = 0; j < i; j++){
            if(intersect(cubes[i], cubes[j]) && cubes[i].z.first == cubes[j].z.second + 1){
                i_contains_j[j].push_back(i);
                j_contains_i[i].push_back(j);
            }
        }
    }

    int res = 0;
    for(int i = 0; i < cubes.size(); i++){
        queue<int> q;
        unordered_set<int> falling;
        for(auto j : i_contains_j[i]){
            if(j_contains_i[j].size() == 1){
                q.push(j);
                falling.insert(j);
            }
        }
        falling.insert(i);

        while(!q.empty()){
            int j = q.front();
            q.pop();

            for(auto k : i_contains_j[j]){
                if(falling.count(k) == 0){
                    if(all_of(j_contains_i[k].begin(), j_contains_i[k].end(), [&](auto el){return falling.count(el) > 0;})){
                        q.push(k);
                        falling.insert(k);
                    }
                }
            }
        }

        res += falling.size() - 1;
    }

    return to_string(res);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

bool intersect(const cube &lhs, const cube &rhs){
    return max(lhs.x.first, rhs.x.first) <= min(lhs.x.second, rhs.x.second) && max(lhs.y.first, rhs.y.first) <= min(lhs.y.second, rhs.y.second);
}

input_type get_input_day_22(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input22.txt" : "inputs/input22.txt");

    input_type cubes;

    string line;
    while(getline(file, line)){
        istringstream iss(line);
        cube _cube;

        string str;
        vector<int> coords;
        while(getline(iss, str, '~')){
            istringstream tokens(str);
            string token;
            while(getline(tokens, token, ',')){
                coords.push_back(atoi(token.c_str()));
            }
        }

        _cube = {
            .x = {coords[0], coords[3]},
            .y = {coords[1], coords[4]},
            .z = {coords[2], coords[5]}
        };
        cubes.push_back(_cube);
    }

    sort(cubes.begin(), cubes.end(), [](auto lhs, auto rhs){return lhs.z.first < rhs.z.first;});
    for(int i = 0; i < cubes.size(); i++){
        int maxz = 1;
        for(int j = 0; j < i; j++){
            if(intersect(cubes[i], cubes[j]))
                maxz = max(maxz, cubes[j].z.second + 1);
        }
        cubes[i].z.second -= cubes[i].z.first - maxz;
        cubes[i].z.first = maxz;
    }
    sort(cubes.begin(), cubes.end(), [](auto lhs, auto rhs){return lhs.z.first < rhs.z.first;});

    return cubes;
}