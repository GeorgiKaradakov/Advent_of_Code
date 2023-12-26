#include "../headers/day_23.h"
using namespace std;
typedef vector<string> input_type;

struct hasher{
    size_t operator()(const pair<int, int> &p) const {
        return (p.first * p.first) * (p.second * p.second);
    }
};

typedef unordered_map<pair<int, int>, unordered_map<pair<int, int>, int, hasher>, hasher> adj_list;
typedef unordered_set<pair<int, int>, hasher> vis_set;

input_type get_input_day_23();
void dfs(const vector<string> &map, vis_set &visited, adj_list &adj, const pair<int, int> node, int steps, int &max_steps);

string day_23::part1(){
    auto map = get_input_day_23();

    unordered_set<pair<int, int>, hasher> points;
    points.insert({0, 1});
    points.insert({map.size() - 1, map.back().size() - 2});
    
    for(int x = 0; x < map.size(); x++){
        for(int y = 0; y < map[0].size(); y++){
            if(map[x][y] == '#')continue;
            int n_cnt = 0;

            for(auto n : vector<vector<int>>{{x - 1, y}, {x, y + 1}, {x + 1, y}, {x, y - 1}}){
                if(0 <= n[0] && n[0] < map.size() && 0 <= n[1] && n[1] < map[0].size() && map[n[0]][n[1]] != '#'){
                    n_cnt++;
                }
            }

            if(n_cnt >= 3)
                points.insert({x, y});
        }
    }

    adj_list adj;
    unordered_map<char, vector<vector<int>>> dirs = {
        {'^', {{-1, 0}}}, {'>', {{0, 1}}}, {'v', {{1, 0}}}, {'<', {{0, -1}}},
        {'.', {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}}
    };

    for(auto start : points){
        stack<pair<int, pair<int, int>>> s;
        unordered_set<pair<int, int>, hasher> visited;

        s.push({0, start});
        visited.insert(start);

        while(!s.empty()){
            int dist = s.top().first;
            auto pos = s.top().second;
            s.pop();

            if(dist != 0 && points.find(pos) != points.end()){
                adj[start][pos] = dist;
                continue;
            }

            for(auto dxy : dirs[map[pos.first][pos.second]]){
                int nx = dxy[0] + pos.first;
                int ny = dxy[1] + pos.second;

                if(0 <= nx && nx < map.size() && 0 <= ny && ny < map[0].size() && map[nx][ny] != '#' && visited.find({nx, ny}) == visited.end()){
                    s.push({dist + 1, {nx, ny}});
                    visited.insert({nx, ny});
                }
            }
        }
    }

    vis_set visited;
    int steps = INT_MIN;
    dfs(map, visited, adj, {0, 1}, 0, steps);
    return to_string(steps);
}

string day_23::part2(){ //too slow (like 40 seconds)
    auto map = get_input_day_23();

    unordered_set<pair<int, int>, hasher> points;
    points.insert({0, 1});
    points.insert({map.size() - 1, map.back().size() - 2});
    
    for(int x = 0; x < map.size(); x++){
        for(int y = 0; y < map[0].size(); y++){
            if(map[x][y] == '#')continue;
            int n_cnt = 0;

            for(auto n : vector<vector<int>>{{x - 1, y}, {x, y + 1}, {x + 1, y}, {x, y - 1}}){
                if(0 <= n[0] && n[0] < map.size() && 0 <= n[1] && n[1] < map[0].size() && map[n[0]][n[1]] != '#'){
                    n_cnt++;
                }
            }

            if(n_cnt >= 3)
                points.insert({x, y});
        }
    }

    adj_list adj;
    for(auto start : points){
        stack<pair<int, pair<int, int>>> s;
        unordered_set<pair<int, int>, hasher> visited;

        s.push({0, start});
        visited.insert(start);

        while(!s.empty()){
            int dist = s.top().first;
            auto pos = s.top().second;
            s.pop();

            if(dist != 0 && points.find(pos) != points.end()){
                adj[start][pos] = dist;
                continue;
            }

            for(auto n : vector<vector<int>>{{pos.first - 1, pos.second}, {pos.first, pos.second + 1}, {pos.first + 1, pos.second}, {pos.first, pos.second - 1}}){
                if(0 <= n[0] && n[0] < map.size() && 0 <= n[1] && n[1] < map[0].size() && map[n[0]][n[1]] != '#' && visited.find({n[0], n[1]}) == visited.end()){
                    s.push({dist + 1, {n[0], n[1]}});
                    visited.insert({n[0], n[1]});
                }
            }
        }
    }

    vis_set visited;
    int steps = INT_MIN;
    dfs(map, visited, adj, {0, 1}, 0, steps);
    return to_string(steps);
}
//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

void dfs(const vector<string> &map, vis_set &visited, adj_list &adj, const pair<int, int> node, int steps, int &max_steps){
    if(node.first == map.size() - 1 && node.second == map.back().size() - 2){
        max_steps = max(steps, max_steps);
        return;
    }

    if(visited.find(node) != visited.end())
        return;
    visited.insert(node);
    for(auto next : adj[node]){
        dfs(map, visited, adj, next.first, steps + adj[node][next.first], max_steps);
    }
    visited.erase(node);
}

input_type get_input_day_23(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input23.txt" : "inputs/input23.txt");

    input_type res;

    string line;
    while(getline(file, line))
        res.push_back(line);

    return res;
}