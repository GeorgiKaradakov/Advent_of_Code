#include "../headers/day_10.h"
using namespace std;
typedef pair<pair<int, int>, vector<vector<char>>> input_type;

unordered_map<char, vector<pair<int, int>>> dxy{
    {'|', {{1, 0}, {-1, 0}}}, {'-', {{0, 1}, {0, -1}}}, {'L', {{-1, 0}, {0, 1}}}, 
    {'J', {{-1, 0}, {0, -1}}}, {'7', {{0, -1}, {1, 0}}}, {'F', {{0, 1}, {1, 0}}},
    {'.', {}}
};

input_type get_input_day_10();
int cast_ray(const vector<vector<char>> &mat, const vector<vector<bool>> &visited, pair<int, int> inds);

string day_10::part1(){
    auto kv = get_input_day_10();
    auto start_node = kv.first;
    auto mat = kv.second;

    queue<pair<int, int>> q;
    vector<vector<int>> distances(mat.size(), vector<int>(mat[0].size(), INT_MAX));

    q.push(start_node);
    distances[start_node.first][start_node.second] = 0;

    while(!q.empty()){
        auto curr = q.front();
        q.pop();

        for(auto d : dxy[mat[curr.first][curr.second]]){
            pair<int, int> next = {curr.first + d.first, curr.second + d.second};

            if(0 <= next.first && next.first < mat.size() && 0 <= next.second && next.second < mat[next.first].size()){
                if(mat[next.first][next.second] != '.'){
                    int new_dist = distances[curr.first][curr.second] + 1;

                    if(new_dist < distances[next.first][next.second]){
                        distances[next.first][next.second] = new_dist;
                        q.push(next);
                    }
                }
            }
        }
    }

    int max_d = INT_MIN;
    for(int x = 0; x < distances.size(); x++){
        for(int y = 0; y < distances[x].size(); y++){
            if(mat[x][y] != '.' && distances[x][y] != INT_MAX){
                max_d = max(max_d, distances[x][y]);
            }
        }
    }

    return to_string(max_d);
}

string day_10::part2(){
    auto kv = get_input_day_10();
    auto start_node = kv.first;
    auto mat = kv.second;
    
    vector<vector<bool>> visited(mat.size(), vector<bool>(mat[0].size(), 0));
    queue<pair<int, int>> q;

    q.push(start_node);

    while(!q.empty()){
        auto curr = q.front();
        q.pop();

        if(visited[curr.first][curr.second])
            continue;
        visited[curr.first][curr.second] = 1;

        for(auto d : dxy[mat[curr.first][curr.second]]){
            pair<int, int> next = {curr.first + d.first, curr.second + d.second};

            if(0 <= next.first && next.first < mat.size() && 0 <= next.second && next.second < mat[next.first].size()){
                if(mat[next.first][next.second] != '.'){
                    q.push(next);
                }
            }
        }
    }

    int res = 0;
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat[i].size(); j++){
            if(!visited[i][j]){
                int ray_hits = cast_ray(mat, visited, {i, j});

                if(ray_hits > 0){
                    if(ray_hits % 2 == 1)
                        res++;
                }
            }
        }
    }
    
    return to_string(res);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

int cast_ray(const vector<vector<char>> &mat, const vector<vector<bool>> &visited, pair<int, int> inds){
    auto line = mat[inds.first];

    int cnt = 0;
    for(int i = 0; i < inds.second; i++){
        if(!visited[inds.first][i])continue;

        cnt += line[i] == 'J' || line[i] == 'L' || line[i] == '|';
    }

    return cnt;
}

input_type get_input_day_10(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input10.txt" : "inputs/input10.txt");

    pair<int, int> start;
    vector<vector<char>> adj;

    string line;
    int x = 0;
    while(getline(file, line)){
        vector<char> v;
        for(int y = 0; y < line.size(); y++){
            if(line[y] == 'S'){
                start = pair<int, int>{x, y};
                if(t == 0){
                    v.push_back('F');
                }else if(t == 1){
                    v.push_back('|');
                }
            }else
                v.push_back(line[y]);
            
        }
        ++x;
        adj.push_back(v);
    }

    return {start, adj};
}