#include "../headers/day_9.h"
using namespace std;
typedef vector<pair<char, int>> input_type;

struct hasher{
    size_t operator()(const pair<int, int> &p) const {
        const int prime = 31; 
        size_t hash1 = p.first;
        size_t hash2 = p.second;

        size_t combinedHash = hash1 * prime + hash2;
        return combinedHash;
    }
};

const int ROPE_SIZE = 10;

int hx, hy, tx, ty;
int rope_x[ROPE_SIZE];
int rope_y[ROPE_SIZE];

input_type get_input_day_9(const string &file_path);
void move_tail(int &hx, int &hy, int &tx, int &ty);
void move_head(int &hx, int &hy, char dir);

string day_9::part1(const string &file_path){
    auto input = get_input_day_9(file_path);
    unordered_set<pair<int, int>, hasher> seen;

    rope_x[0] = 0; rope_y[0] = 0; rope_x[1] = rope_x[0]; rope_y[1] = rope_y[0];
    seen.insert({rope_x[1], rope_y[1]});
    for(int i = 0; i < input.size(); i++){
        int cnt = input[i].second;

        while(cnt--){
            //move head
            move_head(rope_x[0], rope_y[0], input[i].first);

            // move tail
            move_tail(rope_x[0], rope_y[0], rope_x[1], rope_y[1]);

            if(seen.find({rope_x[1], rope_y[1]}) == seen.end())
                seen.insert({rope_x[1], rope_y[1]});
        }
    }

    return to_string(seen.size());
}

string day_9::part2(const string &file_path){
    auto input = get_input_day_9(file_path);
    unordered_set<pair<int, int>, hasher> seen;

    for(int i = 0; i < ROPE_SIZE; i++){
        rope_x[i] = 0;
        rope_y[i] = 0;
    }
    seen.insert({rope_x[1], rope_y[1]});
    for(int i = 0; i < input.size(); i++){
        int cnt = input[i].second;

        while(cnt--){
            //move head
            move_head(rope_x[0], rope_y[0], input[i].first);

            // move tail
            for(int i = 1; i < ROPE_SIZE; i++){
                move_tail(rope_x[i - 1], rope_y[i - 1], rope_x[i], rope_y[i]);
            }

            if(seen.find({rope_x[9], rope_y[9]}) == seen.end())
                seen.insert({rope_x[9], rope_y[9]});
        }
    }

    return to_string(seen.size());
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

void move_head(int &hx, int &hy, char dir){
    switch(dir){
        case 'R':hy++;break;
        case 'L':hy--;break;
        case 'U':hx--;break;
        case 'D':hx++;break;
    }
}

void move_tail(int &hx, int &hy, int &tx, int &ty){
    int diff_x = hx - tx, diff_y = hy - ty;

    if(abs(diff_x) > 1 || abs(diff_y) > 1){
        tx += (diff_x > 0 ? 1 : (diff_x < 0 ? -1 : 0));
        ty += (diff_y > 0 ? 1 : (diff_y < 0 ? -1 : 0));
    }
}

input_type get_input_day_9(const string &file_path){
    ifstream file(file_path);
    input_type out;

    string line;
    while(getline(file, line)){
        char dir = line[0];
        int cnt = 0, ind = 2;
        while(isdigit(line[ind])){
            cnt *= 10;
            cnt += line[ind++] - '0';
        }

        out.push_back({dir, cnt});
    }

    file.close();

    return out;
}