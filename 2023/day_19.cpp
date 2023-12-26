#include "../headers/day_19.h"
using namespace std;

enum operators{
    greater_than = 0,
    less_than
};

struct condition{
    string parameter;
    operators comparer;
    int value;
    string dest;
};

struct part{
    int x, m, a, s;

    int get_parameter(const string &str){
        if(str == "x")
            return x;
        else if(str == "m")
            return m;
        else if(str == "a")
            return a;
        else 
            return s;
    }
    static int get_parameter_ind(const string &str){
        if(str == "x")
            return 0;
        else if(str == "m")
            return 1;
        else if(str == "a")
            return 2;
        else 
            return 3;
    }
    int get_part_sum(){return x + m + a + s;}
};

struct workflow{
    string name, dest;
    vector<condition> conditions;

    string get_next_workflow(part &current){
        for(auto cond : conditions){
            auto param = current.get_parameter(cond.parameter);

            if(cond.comparer == operators::greater_than){
                if(param > cond.value)return cond.dest;
            }else{
                if(param < cond.value)return cond.dest;
            }
        }

        return this->dest;
    }
};

typedef pair<vector<part>, unordered_map<string, workflow>> input_type;

input_type get_input_day_19();
bool dfs(string curr_node, unordered_map<string, workflow> &workflows, part &curr_part);
 
string day_19::part1(){
    auto kv = get_input_day_19();
    auto parts = kv.first;
    auto workflows = kv.second;

    uint64_t res = 0;
    for(auto curr_part : parts){
        if(dfs("in", workflows, curr_part))
            res += curr_part.get_part_sum();
    }

    return to_string(res);
}

string day_19::part2(){
    auto kv = get_input_day_19();
    auto parts = kv.first;
    auto workflows = kv.second;

    queue<pair<string, vector<pair<int, int>>>> q;
    q.push({"in", {{1, 4000}, {1, 4000}, {1, 4000}, {1, 4000}}});

    uint64_t res = 1;
    while(!q.empty()){
        auto kv = q.front();
        q.pop();

        auto wf_name = kv.first;
        auto vec = kv.second;

        if(wf_name == "A" || wf_name == "B"){
            if(wf_name == "A")
                for(auto interval : vec)
                    res *= interval.second - interval.first + 1;
            continue;
        }

        for(auto cond : workflows[wf_name].conditions){
            int ind = part::get_parameter_ind(cond.parameter);
            int lo = vec[ind].first, hi = vec[ind].second;

            if((cond.comparer == operators::greater_than && cond.value >= hi) ||
               (cond.comparer == operators::less_than && cond.value <= lo))continue;

            if((cond.comparer == operators::greater_than && cond.value < lo) ||
               (cond.comparer == operators::less_than && cond.value > hi)){
                q.push({cond.dest, vec});
                continue;
            }

            pair<int, int> transfer, pass;
            if(cond.comparer == operators::greater_than){
                transfer = {cond.value + 1, hi};
                pass = {lo, cond.value};
            }else{
                transfer = {lo, cond.value + 1};
                pass = {cond.value, hi};
            }
            vec[ind] = pass;
            auto intervals = vec;
            intervals[ind] = transfer;
            q.push({cond.dest, intervals});
        }

        q.push({workflows[wf_name].dest, vec});
    }

    return to_string(res);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

bool dfs(string curr_node, unordered_map<string, workflow> &workflows, part &curr_part){
    if(curr_node == "A")return 1;
    if(curr_node == "R")return 0;

    return dfs(workflows[curr_node].get_next_workflow(curr_part), workflows, curr_part);
}

input_type get_input_day_19(){
    int t = 0;
    ifstream file(t == 0 ? "inputs/sample_input19.txt" : "inputs/input19.txt");

    unordered_map<string, workflow> workflows;
    vector<part> parts;

    string line;
    while(getline(file, line)){
        if(line.empty())continue;
        if(line.find('=') != string::npos){
            istringstream iss(line);
            int x, m, a, s;
            iss.ignore(256, '=');iss >> x;
            iss.ignore(256, '=');iss >> m;
            iss.ignore(256, '=');iss >> a;
            iss.ignore(256, '=');iss >> s;

            parts.push_back({.x = x, .m = m, .a = a, .s = s});
        }else{
            int cnt = count_if(line.begin(), line.end(), [](auto el){return el == ',';});
            istringstream iss(line);
            workflow wf;

            string name;
            char c;
            while((c = iss.get()) != '{'){
                name += c;
            }
            wf.name = name;

            while(cnt--){
                string param, _operator, number, dest;
                char c;

                c = iss.get();
                param += c;
                c = iss.get();
                _operator += c;

                while(isdigit((c = iss.get()))){
                    number += c;
                }

                while((c = iss.get()) != ','){
                    dest += c;
                }


                wf.conditions.push_back(
                    condition{
                        .parameter = param,
                        .comparer = (_operator == ">" ? operators::greater_than : operators::less_than),
                        .value = atoi(number.c_str()),
                        .dest = dest
                    }
                );
            }
            string dest;
            getline(iss, dest, '}');
            wf.dest = dest;
            workflows[name] = wf;
        }
    }
    return {parts, workflows};
}
