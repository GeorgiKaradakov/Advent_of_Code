#include "../headers/day_16.h"
using namespace std;
typedef vector<string> input_type;

input_type get_input_day_16();
int trace_ray(const vector<string> &input, int x, int y, char dir);
bool in_map(const vector<string> &map, int x, int y){return 0 <= x && x < map.size() && 0 <= y && y < map[0].size();}
pair<int, int> calc_coords(int x, int y, char dir);

string day_16::part1(){
    auto input = get_input_day_16();

    return to_string(trace_ray(input, 0, 0, 'r'));
}

string day_16::part2(){
    auto input = get_input_day_16();

    int total = INT_MIN;
    for(int x = 0; x < input.size(); x++){
        total = max(total, trace_ray(input, x, 0, 'r'));
        total = max(total, trace_ray(input, x, input[0].size() - 1, 'l'));
    }

    for(int y = 0; y < input[0].size(); y++){
        total = max(total, trace_ray(input, 0, y, 'd'));
        total = max(total, trace_ray(input, input.size() - 1, y, 'u'));
    }

    return to_string(total);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

int trace_ray(const vector<string> &input, int x, int y, char dir){ 
    queue<pair<pair<int, int>, char>> q;
    set<pair<pair<int, int>, char>> visited;
    vector<vector<bool>> counter(input.size(), vector<bool>(input[0].size(), 0));

    q.push({{x, y}, dir});

    while(!q.empty()){
        const auto &ray = q.front();
        q.pop();

        if(visited.count(ray) == 1)continue;
        visited.insert(ray);

        pair<int, int> coord = ray.first;
        char dir = ray.second;

        while(in_map(input, coord.first, coord.second) && 
                (input[coord.first][coord.second] == '.' || 
                (input[coord.first][coord.second] == '|' && (dir == 'u' || dir == 'd')) || 
                (input[coord.first][coord.second] == '-' && (dir == 'r' || dir == 'l')))){
            counter[coord.first][coord.second] = 1;
            coord = calc_coords(coord.first, coord.second, dir);
        }

        if(!in_map(input, coord.first, coord.second))continue;
        counter[coord.first][coord.second] = 1;

        if(input[coord.first][coord.second] == '/'){
            switch(dir){
                case 'u': q.push({calc_coords(coord.first, coord.second, 'r'), 'r'});
                break;

                case 'r': q.push({calc_coords(coord.first, coord.second, 'u'), 'u'});
                break;

                case 'd': q.push({calc_coords(coord.first, coord.second, 'l'), 'l'});
                break;

                case 'l': q.push({calc_coords(coord.first, coord.second, 'd'), 'd'});
                break;
            }
        }

        if(input[coord.first][coord.second] == '\\'){
            switch(dir){
                case 'u': q.push({calc_coords(coord.first, coord.second, 'l'), 'l'});
                break;

                case 'r': q.push({calc_coords(coord.first, coord.second, 'd'), 'd'});
                break;

                case 'd': q.push({calc_coords(coord.first, coord.second, 'r'), 'r'});
                break;

                case 'l': q.push({calc_coords(coord.first, coord.second, 'u'), 'u'});
                break;
            }
        }

        if(input[coord.first][coord.second] == '|' && (dir == 'l' || dir == 'r')){
            q.push({calc_coords(coord.first, coord.second, 'u'), 'u'});
            q.push({calc_coords(coord.first, coord.second, 'd'), 'd'});
        }

        if(input[coord.first][coord.second] == '-' && (dir == 'u' || dir == 'd')){
            q.push({calc_coords(coord.first, coord.second, 'l'), 'l'});
            q.push({calc_coords(coord.first, coord.second, 'r'), 'r'});
        }
    }

    int res = 0;
    for(auto vec : counter)
        for(auto el : vec)
            res += el;

    return res;
}

pair<int, int> calc_coords(int x, int y, char dir){
    switch(dir){
        case 'u':
            return {x - 1, y};
        case 'r':
            return {x, y + 1};
        case 'd':
            return {x + 1, y};
        case 'l': return {x, y - 1};

        default:return {};
    }    
}

input_type get_input_day_16(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input16.txt" : "inputs/input16.txt");

    input_type out;
    string line;
    while(getline(file, line))
        out.push_back(line);

    return out;
}