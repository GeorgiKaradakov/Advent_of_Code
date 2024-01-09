#include "../headers/day_14.h"
#include <array>
using namespace std;
typedef vector<vector<char>> input_type;

int MOD;
const int OFFSET = 175;//hardcoded for part 2

input_type get_input_day_14(const string &file_path);
int y(int i){return i % MOD;}
bool dfs(vector<vector<char>> &input, int i, int j, int part);

string day_14::part1(const string &file_path){
    auto input = get_input_day_14(file_path);

    int res = 0;
    while(dfs(input, 0, y(500), 1))res++;

    return to_string(res);
}

string day_14::part2(const string &file_path){
    auto input = get_input_day_14(file_path);
    for(int i = 0; i < 350; i++){
        for(auto &vec : input){
            if(i < OFFSET){
                vec.insert(vec.begin(), '.');
            }else{
                vec.push_back('.');
            }
        }
    }
    input.push_back(vector<char>(input[0].size(), '.'));
    input.push_back(vector<char>(input[0].size(), '#'));

    int res = 0;
    while(dfs(input, 0, y(500 + OFFSET), 2))res++;

    return to_string(res);
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

bool dfs(vector<vector<char>> &input, int i, int j, int part){
    if(part == 1 && (i + 1 >= input.size() || j - 1 < 0 || j + 1 >= input[0].size()))return 0;
    if(part == 2 && input[0][y(500 + OFFSET)] == 'o')return 0;
    if(input[i + 1][j] != '.' && input[i + 1][j - 1] != '.' && input[i + 1][j + 1] != '.'){
        input[i][j] = 'o';
        return 1;
    }

    if(input[i + 1][j] == '.')return dfs(input, i + 1, j, part);
    if(input[i + 1][j - 1] == '.')return dfs(input, i + 1, j - 1, part);
    if(input[i + 1][j + 1] == '.')return dfs(input, i + 1, j + 1, part);

    return 1;
}

input_type get_input_day_14(const string &file_path){
    ifstream file(file_path);
    input_type out;
    vector<vector<pair<int, int>>> lines;

    int max_h = INT_MIN, min_h = INT_MAX, max_w = max_h, min_w = min_h;
    string line;
    while(getline(file, line)){
        istringstream iss(line);
        string token;
        vector<pair<int, int>> t;

        while(iss >> token){
            if(token != "->"){
                int ind = 0, num = 0;
                pair<int, int> t_p;
                while(token[ind] != ','){
                    num *= 10;
                    num += token[ind++] - '0';
                }
                t_p.first = num;num = 0;++ind;
                while(ind < token.size()){
                    num *= 10;
                    num += token[ind++] - '0';
                }
                t_p.second = num;
                t.push_back(t_p);

                max_h = max(t_p.second, max_h);
                max_w = max(t_p.first, max_w);
                min_h = min(t_p.second, min_h);
                min_w = min(t_p.first, min_w);
            }
        }

        lines.push_back(t);
    }

    MOD = min_w;
    out = vector<vector<char>>(max_h + 1, vector<char>(max_w - min_w + 1, '.'));

    for(auto line : lines){
        for(int i = 1; i < line.size(); i++){
            int x1, y1, x2, y2;
            tie(y1, x1) = line[i - 1];tie(y2, x2) = line[i];

            if(x1 == x2){
                int t = max(y1, y2);y1 = min(y1, y2);y2 = t;

                for(int i = y1; i <= y2; i++){
                    out[x1][y(i)] = '#';
                }
            }else{
                int t = max(x1, x2);x1 = min(x1, x2);x2 = t;

                for(int i = x1; i <= x2; i++){
                    out[i][y(y1)] = '#';
                }
            }
        }
    }

    file.close();
    return out;
}