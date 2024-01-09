#include "../headers/day_12.h"
using namespace std;
typedef tuple<pair<int, int>, pair<int, int>, vector<string>> input_type;

struct hasher{
    size_t operator()(const pair<int, int> &p) const {
        const int prime = 31; 
        size_t hash1 = p.first;
        size_t hash2 = p.second;

        size_t combinedHash = hash1 * prime + hash2;
        return combinedHash;
    }
};

input_type get_input_day_12(const string &file_path);
int dijkstra(const vector<string> &map, const vector<pair<int, int>> &starts, const pair<int, int> &end);

string day_12::part1(const string &file_path){
    auto t = get_input_day_12(file_path);
    pair<int, int> start, end;vector<string> map;
    tie(start, end, map) = t;

    vector<pair<int, int>> starts = {start};

    return to_string(dijkstra(map, starts, end));
}

string day_12::part2(const string &file_path){
    auto t = get_input_day_12(file_path);
    pair<int, int> start, end;vector<string> map;
    tie(start, end, map) = t;

    vector<pair<int, int>> starts;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].size(); j++){
            if(map[i][j] == 'a')
                starts.emplace_back(i, j);
        }
    }

    return to_string(dijkstra(map, starts, end));
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

int dijkstra(const vector<string> &map, const vector<pair<int, int>> &starts, const pair<int, int> &end){//multiple source node one dest dijkstra's
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    unordered_set<pair<int, int>, hasher> seen;
    vector<vector<int>> dist(map.size(), vector<int>(map[0].size(), INT_MAX));

    for(auto start : starts){
        pq.push({0, start});
        seen.insert(start);
        dist[start.first][start.second] = 0;
    }

    while(!pq.empty()){
        int steps = pq.top().first;
        int x, y;tie(x, y) = pq.top().second;
        pq.pop();

        if(pair<int, int>{x, y} == end)return steps;

        for(auto n : vector<vector<int>>{{x - 1, y}, {x, y + 1}, {x + 1, y}, {x, y - 1}}){
            if(0 <= n[0] && n[0] < map.size() && 0 <= n[1] && n[1] < map[0].size() && map[n[0]][n[1]] - map[x][y] <= 1 && seen.find({n[0], n[1]}) == seen.end()){
                if(steps + 1 < dist[n[0]][n[1]]){
                    dist[n[0]][n[1]] = steps + 1;
                    pq.push({steps + 1, {n[0], n[1]}});
                    seen.insert({n[0], n[1]});
                }
            }
        }
    }

    return -1;
}

input_type get_input_day_12(const string &file_path){
    ifstream file(file_path);
    vector<string> out;
    pair<int, int> start_coords;
    pair<int, int> end_coords;

    string line;
    int x=0;
    while(getline(file, line)){
        for(int i = 0; i < line.size(); i++) if(line[i] == 'E'){
            end_coords = {x, i};
            line[i] = 'z';
        }else if(line[i] == 'S'){
            start_coords = {x, i};
            line[i] = 'a';
        }
        out.push_back(line);
        x++;
    }


    file.close();
    return {start_coords, end_coords, out};
}