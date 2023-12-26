#include "../headers/day_17.h"
using namespace std;
typedef vector<vector<int>> input_type;

struct state{
    int x, y, weight, moves, dir;

    bool operator==(const state& rhs) const {
        return this->x == rhs.x && this->y == rhs.y && this->weight == rhs.weight && this->moves == rhs.moves && this->dir == rhs.dir;
    }
};

struct comparer{
    bool operator()(const state &lhs, const state &rhs){
        return lhs.weight > rhs.weight;
    }
};

struct hasher{
    size_t operator()(const state& st) const {
        return st.x + st.y;
    }
};

input_type get_input_day_17();
int in_limits(const vector<vector<int>> &map, int x, int y){return 0 <= x && x < map.size() && 0 <= y && y < map[0].size();}

string day_17::part1(){
    auto input = get_input_day_17();
    priority_queue<state, vector<state>, comparer> pq; 
    unordered_set<state, hasher> seen;
    vector<pair<int, int>> dxy = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    state st;
    st.x = 0;st.y = 0;
    st.dir = 1;
    st.moves = 0;
    st.weight = 0;
    pq.push(st);
    st.dir = 2;
    pq.push(st);

    while(!pq.empty()) {
        st = pq.top();
        pq.pop();
        if (seen.find(st) != seen.end())  {
            continue;
        }

        seen.insert(st);
        if (st.x == input.size() - 1 && st.y == input[0].size() - 1) {
            return to_string(st.weight);
        }
        // Move left
        {
            state new_state;
            new_state.dir = (st.dir - 1 + 4) % 4;
            new_state.x = dxy[new_state.dir].first + st.x;
            new_state.y = dxy[new_state.dir].second + st.y;
            if (in_limits(input, new_state.x, new_state.y)) {
                new_state.weight  = st.weight + input[new_state.x][new_state.y];
                new_state.moves = 0;
                pq.push(new_state);
            }
        }
        // Move right
        {
            state new_state;
            new_state.dir = (st.dir + 1 + 4) % 4;
            new_state.x = dxy[new_state.dir].first + st.x;
            new_state.y = dxy[new_state.dir].second + st.y;
            if (in_limits(input, new_state.x, new_state.y)) {
                new_state.weight  = st.weight + input[new_state.x][new_state.y];
                new_state.moves = 0;
                pq.push(new_state);
            }
        }
        // Move Straight
        {
            if (st.moves < 2) {
                    state new_state = st;
                    new_state.x = dxy[new_state.dir].first + st.x;
                    new_state.y = dxy[new_state.dir].second + st.y;
                    if (in_limits(input, new_state.x, new_state.y)) {
                    new_state.weight  = st.weight + input[new_state.x][new_state.y];
                    new_state.moves++;
                    pq.push(new_state);
                }
            }
        }
    } 

    return "1";
}

string day_17::part2(){
    return "2";
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

input_type get_input_day_17(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input17.txt" : "inputs/input17.txt");

    input_type out;

    string line;
    while(getline(file, line)){
        vector<int> v;
        for(auto ch : line)
            v.push_back(ch - '0');
        out.push_back(v);
    }

    return out;
}