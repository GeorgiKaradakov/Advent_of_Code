#include "../headers/day_8.h"
using namespace std;
typedef vector<vector<int>> input_type;

input_type get_input_day_8(const string &file_path);
bool check_visibility(int x, int y, const vector<vector<int>> &map);

string day_8::part1(const string &file_path){
    auto input = get_input_day_8(file_path);

    int res = 0;
    for(int x = 1; x < input.size() - 1; x++){
        for(int y = 1; y < input[0].size() - 1; y++){
            res += check_visibility(x, y, input);
        }
    }
    return to_string(input.size() * 2 + input[0].size() * 2 - 4 + res);
}

string day_8::part2(const string &file_path){
    auto input = get_input_day_8(file_path);

    int res = INT_MIN;
    for(int x = 1; x < input.size() - 1; x++){
        for(int y = 1; y < input[0].size() - 1; y++){
            
            int curr = 1, cnt = 0, prev = input[x][y];
            for(int left = y - 1; left >= 0; left--){
                cnt++;
                if(input[x][left] >= prev)break;
            }
            curr *= cnt;

            cnt = 0;prev = input[x][y];
            for(int right = y + 1; right < input[0].size(); right++){
                cnt++;
                if(input[x][right] >= prev)break;
            }
            curr *= cnt;

            cnt = 0;prev = input[x][y];
            for(int up = x - 1; up >= 0; up--){
                cnt++;
                if(input[up][y] >= prev)break;
            }
            curr *= cnt;

            cnt = 0;prev = input[x][y];
            for(int down = x + 1; down < input.size(); down++){
                cnt++;
                if(input[down][y] >= prev)break;
            }
            curr *= cnt;

            res = max(curr, res);
        }
    }

    return to_string(res);
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------
    
bool check_visibility(int x, int y, const vector<vector<int>> &map){
    int prev = map[x][y];
    bool breaked = 0;
    for(int left = y - 1; left >= 0; left--)
        if(map[x][left] >= prev){
            breaked = 1;
            break;
        }
    if(!breaked)return 1;

    prev = map[x][y];
    breaked = 0;
    for(int right = y + 1; right < map[0].size(); right++)
        if(map[x][right] >= prev){
            breaked = 1;
            break;
        }
    if(!breaked)return 1;


    prev = map[x][y];
    breaked = 0;
    for(int up = x - 1; up >= 0; up--)
        if(map[up][y] >= prev){
            breaked = 1;
            break;
        }
    if(!breaked)return 1;

    prev = map[x][y];
    breaked = 0;
    for(int down = x + 1; down < map.size(); down++)
        if(map[down][y] >= prev){
            breaked = 1;
            break;
        }
    if(!breaked)return 1;

    return 0;
}

input_type get_input_day_8(const string &file_path){
    ifstream file(file_path);
    input_type out;

    string line;
    while(getline(file, line)){
        vector<int> t;
        for(auto ch : line)
            t.push_back(ch - '0');
        out.push_back(t);
    }

    file.close();

    return out;
}