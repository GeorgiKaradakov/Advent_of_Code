#include "../headers/day_14.h"
using namespace std;
typedef pair<vector<pair<int, int>>, vector<string>> input_type;
const int part2_cnt = 1000000000;

input_type get_input_day_14();
int calculate_north_pos(int x, int y, vector<string> &mat);
pair<int, int> calculate_west_pos(int x, int y, vector<string> &mat);
pair<int, int> calculate_south_pos(int x, int y, vector<string> &mat);
int calculate_east_pos(int x, int y, vector<string> &mat);

string day_14::part1(){
    auto kv = get_input_day_14();
    auto mat = kv.second;
    auto visited = kv.first;

    int sum = 0;

    for(auto Os : visited){
        sum += mat.size() - calculate_north_pos(Os.first, Os.second, mat);
    }

    return to_string(sum);
}

string day_14::part2(){
    auto kv = get_input_day_14();
    auto mat = kv.second;
    unordered_map<string, uint64_t> dp;

    uint64_t sum = 0;
    bool first = 1;
    for(uint64_t _ = 0; _ < part2_cnt; _++){
        uint64_t curr_sum = 0;
        for(int x = 0; x < mat.size(); x++){
            for(int y = 0; y < mat[0].size(); y++){
                if(mat[x][y] == 'O')
                    calculate_north_pos(x, y, mat);
            }
        }

        for(int x = 0; x < mat.size(); x++){
            for(int y = 0; y < mat[0].size(); y++){
                if(mat[x][y] == 'O')
                    calculate_west_pos(x, y, mat);
            }
        }

        for(int x = mat.size() - 1; x >= 0; x--){
            for(int y = 0; y < mat[0].size(); y++){
                if(mat[x][y] == 'O')
                    calculate_south_pos(x, y, mat);
            }
        }

        for(int x = 0; x < mat.size(); x++){
            for(int y = mat[0].size(); y >= 0; y--){
                if(mat[x][y] == 'O')
                    curr_sum += calculate_east_pos(x, y, mat);
            }
        }
        sum = curr_sum;
        
        string dp_state;
        for(int x = 0; x < mat.size(); x++)
            for(int y = 0; y < mat[0].size(); y++)
                dp_state += mat[x][y];

        if(dp.count(dp_state) != 0){
            uint64_t loop_offset = dp[dp_state];
            uint64_t len = _ - loop_offset;

            _ = part2_cnt - (part2_cnt - loop_offset) % len;
            dp.clear();
        }

        dp[dp_state] = _;
    }

    return to_string(sum);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

int calculate_north_pos(int x, int y, vector<string> &mat){
    mat[x][y] = '.';

    while(x >= 0 && mat[x][y] == '.'){
        x--;
    }
    mat[x + 1][y] = 'O';
    return x + 1;
}

pair<int, int> calculate_west_pos(int x, int y, vector<string> &mat){
    mat[x][y] = '.';

    while(y >= 0 && mat[x][y] == '.')--y;

    mat[x][y + 1] = 'O';
    return {x, y + 1};
}

pair<int, int> calculate_south_pos(int x, int y, vector<string> &mat){
    mat[x][y] = '.';

    while(x < mat.size() && mat[x][y] == '.')x++;

    mat[x - 1][y] = 'O';
    return {x - 1, y};
}

int calculate_east_pos(int x, int y, vector<string> &mat){
    mat[x][y] = '.';

    while(y < mat[0].size() && mat[x][y] == '.')y++;

    mat[x][y - 1] = 'O';
    return mat.size() - x;
}

input_type get_input_day_14(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input14.txt" : "inputs/input14.txt");

    vector<string> mat;
    vector<pair<int, int>> visited;

    string line;
    int x = 0;
    while(getline(file, line)){
        for(int i = 0; i < line.size(); i++)
            if(line[i] == 'O')
                visited.push_back({x, i});

        mat.push_back(line);
        ++x;
    }

    return {visited, mat};
}