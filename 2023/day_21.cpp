#include "../headers/day_21.h"
#include <cmath>
using namespace std;
typedef pair<pair<int, int>, vector<string>> input_type;

input_type get_input_day_21();

int simulate_steps(pair<int, int> source, int path_len, vector<string> &map);

string day_21::part1(){
    int t = 1;

    auto input = get_input_day_21();
    auto start_pos = input.first;
    auto map = input.second;

    return to_string(simulate_steps(start_pos, (t == 0 ? 6 : 64), map));
}

string day_21::part2(){
    auto input = get_input_day_21();
    auto start_pos = input.first;
    auto map = input.second;

    int height = map.size(), width = map[0].size();
    const int steps = 26501365;

    int u1, u2, u3;
    // for (int x = 0; x < 3; x++) {
    //     u1 = bfs(garden, start, 65 + garden.rows * x);
    // }
    //
    u1 = simulate_steps(start_pos, 65 + height * 0, map);
    u2 = simulate_steps(start_pos, 65 + height * 1, map);
    u3 = simulate_steps(start_pos, 65 + height * 2, map);

    
    uint64_t diff1 = u2 - u1;
    
    uint64_t diff2 = u3 - u2 - diff1;
    
    uint64_t a = diff2 / 2;
    
    uint64_t b = diff1 - (3 * a);
    
    uint64_t c = u1 - a - b;
    
    uint64_t n = ceil(steps / height);
    return to_string((a * pow(n, 2)) + (b * n) + c);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

int simulate_steps(pair<int, int> source, int path_len, vector<string> &map){
    const pair<int, int> offsets[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    queue<pair<int, pair<int, int>>> q;
    set<pair<int, int>> visited;

    q.push({0, source});

    uint64_t res = 0;
    while(!q.empty()){
        const auto &el = q.front();
        q.pop();

        auto curr = el.second;
        auto path_cnt = el.first;

        if(visited.find(curr) != visited.end())continue;
        visited.insert(curr);

        if(path_cnt % 2 == path_len % 2)
            ++res;

        if(path_cnt >= path_len)continue;

        for(auto offset : offsets){
            int x = curr.first + offset.first, y = curr.second + offset.second;

            if(map[x % map.size()][y % map[0].size()] == '#')continue;

            q.push({path_cnt + 1, {x, y}});
        }
    }

    return res;
}

input_type get_input_day_21(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input21.txt" : "inputs/input21.txt");

    vector<string> out;
    pair<int, int> start_pos;

    string line;
    int x = 0;
    while(getline(file, line)){
        for(int y = 0; y < line.size(); y++)
            if(line[y] == 'S')
                start_pos = {x, y};

        out.push_back(line);
        ++x;
    }

    return {start_pos, out};
}
