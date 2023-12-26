#include "../headers/day_25.h"
using namespace std;
typedef unordered_map<string, vector<string>> adj_list;
typedef unordered_set<string> edge_list;
typedef pair<adj_list, vector<string>> input_type;

struct hasher{
    size_t operator()(const pair<string, string> &p) const {
        size_t hash = 0;
        for (char ch : p.first) {
            hash = (hash * 131) + ch; 
        }

        for (char ch : p.second) {
            hash = (hash * 131) + ch; 
        }

        return hash;
    }
};

input_type get_input_day_25();
vector<string> get_path(adj_list &adj, string &start, string &end);
int get_size_of_component(adj_list &adj, string &root, vector<pair<string, string>> &cutted);

string day_25::part1(){
    auto input = get_input_day_25();
    auto adj = input.first;
    auto edges = input.second;

    srand(time(0));

    unordered_map<pair<string, string>, int, hasher> edge_freq;

    for(int _ = 0; _ < 200 /*works best for me you can change it for your input*/; _++){
        auto node1 = edges[rand() % edges.size()];
        auto node2 = edges[rand() % edges.size()];
        
        auto path = get_path(adj, node1, node2);
        for(int i = 1; i < path.size(); i++){
            pair<string, string> edge = {min(path[i - 1], path[i]), max(path[i - 1], path[i])};
            edge_freq[edge]++;
        }
    }
    
    pair<string, string> t1, t2, t3;
    int max1 = INT_MIN, max2 = max1, max3 = max2;
    for(auto kv : edge_freq){
        if(kv.second > max1){
            max3 = max2;t3 = t2;
            max2 = max1;t2 = t1;
            max1 = kv.second;t1 = kv.first;
        }else if(max2 < kv.second){
            max3 = max2;t3 = t2;
            max2 = kv.second;t2 = kv.first;
        }else if(max3 < kv.second){
            max3 = kv.second;t3 = kv.first;
        }
    }
    
    vector<pair<string, string>> cutted = {t1, t2, t3};
    
    auto res1 = get_size_of_component(adj, t1.first, cutted);
    auto res2 = get_size_of_component(adj, t1.second, cutted);

    assert(res1 + res2 == adj.size());
    
    return to_string(res1 * res2);
}

string day_25::part2(){
    return "There is no part 2 because it is the last puzzle!!!";
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

int get_size_of_component(adj_list &adj, string &root, vector<pair<string, string>> &cutted){
    unordered_set<string> visited;
    vector<string> nodes;
    nodes.push_back(root);
    visited.insert(root);

    while(!nodes.empty()){
        vector<string> new_nodes;

        for(auto node : nodes){
            for(auto n : adj[node]){
                if(visited.count(n) || any_of(cutted.begin(), cutted.end(), [=](auto el){
                    return (el.first == n || el.first == node) && (el.second == n || el.second == node);
                })){
                    continue;
                }

                visited.insert(n);
                new_nodes.push_back(n);
            }
        }

        nodes = new_nodes;
    }

    return visited.size();
}

vector<string> get_path(adj_list &adj, string &start, string &end){
    unordered_map<string, string> prev;
    vector<string> nodes;
    unordered_set<string> seen;

    prev[start] = start;
    nodes.push_back(start);
    seen.insert(start);

    while (!nodes.empty()) {
        std::vector<string> new_nodes;
        for (string node : nodes) {
            for (string neighbour : adj[node]) {
                if (seen.count(neighbour) > 0) {
                    continue;
                }
                seen.insert(neighbour);
                prev[neighbour] = node;
                new_nodes.push_back(neighbour);
            }
        }
        nodes = new_nodes;
    }
    if (prev.find(end) == prev.end()) {
        return {};
    }
    vector<string> path;
    string node = end;
    while (node != start) {
        path.push_back(node);
        node = prev[node];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

input_type get_input_day_25(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input25.txt" : "inputs/input25.txt");

    adj_list adj;
    edge_list edges;

    string line;
    while(getline(file, line)){
        istringstream iss(line);
        string node;

        iss >> node;
        node = node.substr(0, node.size() - 1);
        edges.insert(node);

        string token;
        while(iss >> token){
            adj[node].push_back(token);
            adj[token].push_back(node);
            edges.insert(token);
        }
    }
    return {adj, vector<string>(edges.begin(), edges.end())};
}