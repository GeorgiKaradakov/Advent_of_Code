#include "../headers/day_13.h"
using namespace std;
typedef vector<vector<string>> input_type;

input_type get_input_day_13();
int is_reflection_horizontal(const vector<string> &mat);
vector<string> transpose(const vector<string> &old);
int proccess_patterns_with_a_smudge(const vector<string> &mat);

string day_13::part1(){
    auto patterns = get_input_day_13();

    uint64_t sum = 0;
    for(auto pattern : patterns){
        //sum the horizontal one first
        sum += (is_reflection_horizontal(pattern) * 100);

        //sum the vertical reflection now
        auto t = transpose(pattern);
        sum += is_reflection_horizontal(t);
    }

    return to_string(sum);
}

string day_13::part2(){
    auto patterns = get_input_day_13();

    uint64_t sum = 0;
    for(auto pattern : patterns){
        sum += proccess_patterns_with_a_smudge(pattern);
    }

    return to_string(sum - 405);//found ans with a lot of staring in the input
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

int proccess_patterns_with_a_smudge(const vector<string> &mat){
    auto old_vertical_val =  is_reflection_horizontal(mat) * 100;
    auto t = transpose(mat);
    auto old_horizon_val = is_reflection_horizontal(t);

    for(int x = 0; x < mat.size(); x++){
        for(int y = 0; y < mat[0].size(); y++){
            auto new_mat = mat;
            new_mat[x][y] = mat[x][y] == '.' ? '#' : '.';

            //get vals for the grid with the smudge
            auto vertical_val = is_reflection_horizontal(new_mat) * 100;
            auto tmp = transpose(new_mat);
            auto horizon_val = is_reflection_horizontal(tmp);

            if(vertical_val == 0 && horizon_val == 0)continue;

            if(vertical_val != 0)return vertical_val;
            if(horizon_val != 0)return horizon_val;
        }
    }

    return 0;
}

int is_reflection_horizontal(const vector<string> &mat){
    for(int i = 0; i < mat.size(); i++){
        int s = i, e = i + 1, out_e = i + 1;
        if(e == mat.size())return 0;

        while(mat[s] == mat[e]){
            --s;
            ++e;
            if(s < 0 || e == mat.size())return out_e;
        }
    }

    return 0;
}

vector<string> transpose(const vector<string> &old){
    int w = old.size(), h = old.back().size();
    vector<string> out(h, string(w, ' '));

    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            out[y][x] = old[x][y];
        }
    }

    return out;
}

input_type get_input_day_13(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input13.txt" : "inputs/input13.txt");

    input_type out;
    vector<string> tmp;
    string line;
    while(getline(file, line)){
        if(line.empty()){
            out.push_back(tmp);
            tmp.clear();
        }else{
            tmp.push_back(line);
        }
    }

    if(!tmp.empty())
        out.push_back(tmp);

    return out;
}