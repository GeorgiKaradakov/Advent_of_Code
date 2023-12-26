#include "../headers/day_8.h"
#include <numeric>
using namespace std;
typedef pair<string, unordered_map<string, vector<string>>> input_type;
typedef unsigned long long ull;

vector<string> start_nodes;

input_type get_input_day_8(int part);
int find_path(const string &seq, unordered_map<string, vector<string>> &adj, string curr_node, int ind);
ull lcm(vector<ull> nums);

string day_8::part1(){
    auto kv = get_input_day_8(1);
    auto seq = kv.first;
    auto adj = kv.second;

    int path = find_path(seq, adj, "AAA", 0);

    return to_string(path);
}

string day_8::part2(){
    auto kv = get_input_day_8(2);
    auto seq = kv.first;
    auto adj = kv.second;

    vector<ull> cycles;
    for(auto node : start_nodes){
        string curr = node;
        ull i = 0;

        while(1){
            curr = adj[curr][seq[i % seq.size()] == 'R' ? 1 : 0];
            ++i;
            if(curr.back() == 'Z')
                break;
        }

        cycles.push_back(i);
    }
    
    return to_string(lcm(cycles));
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

ull lcm(vector<ull> nums){
    ull ans = nums[0];

    for(int i = 1; i < nums.size(); i++){
        ans = (nums[i] * ans) / __gcd(nums[i], ans);
    }

    return ans;
}

int find_path(const string &seq, unordered_map<string, vector<string>> &adj, string curr_node, int ind){
    if(curr_node == "ZZZ") return 0;

    return 1 + find_path(seq, adj, adj[curr_node][(seq[ind % seq.size()] == 'R' ? 1 : 0)], ind + 1);
}


input_type get_input_day_8(int part){
    int t = 1;
    string f = t == 0 ? "inputs/sample_input8.txt" : "inputs/input8.txt";
    if(part == 2)
        f = t == 0 ? "inputs/sample_input8_part2.txt" : "inputs/input8.txt";

    ifstream file(f);

    string seq;
    unordered_map<string, vector<string>> adj;

    string line;
    bool first = 1;
    while(getline(file, line)){
        if(line.find("=") != string::npos){
            string key, value;
            istringstream iss(line);

            iss >> key;
            if(part == 2 && key.back() == 'A')
                start_nodes.push_back(key);

            iss.ignore(256, '(');
            iss >> value;
            adj[key].push_back(value.substr(0, value.size() - 1));

            iss.ignore(256, ' ');
            iss >> value;
            adj[key].push_back(value.substr(0, value.size() - 1));

        }else{
            istringstream iss(line);
            string t;

            while(!iss.eof()){
                iss >> t;
                seq += t;
            }
        }
    }

    return {seq, adj};
}