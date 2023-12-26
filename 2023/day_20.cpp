#include "../headers/day_20.h"
using namespace std;

struct module{
    string name;
    string type;
    vector<string> dests;

    bool state = 0;
    unordered_map<string, string> last_recordered_inputs;
};

typedef unordered_map<string, module> input_type;

input_type get_input_day_20();

string day_20::part1(){
    auto module_map = get_input_day_20();

    uint64_t low_cnt = 0, high_cnt = 0;
    for(int _ = 0; _ < 1000; _++){

        queue<tuple<string, string, string>> q;
        for(auto kv : module_map["broadcaster"].dests){
            q.push({"broadcaster", kv, "low"});
        }

        ++low_cnt;
        while(!q.empty()){
            const auto &t = q.front();
            q.pop();

            string source = get<0>(t), target = get<1>(t), pulse = get<2>(t);

            if(pulse == "low")
                ++low_cnt;
            else if(pulse == "high")
                ++high_cnt;

            if(module_map.find(target) == module_map.end())continue;

            auto &mod = module_map[target];

            if(mod.type == "flip_flop"){
                if(pulse == "low"){
                    mod.state = !mod.state;
                    
                    for(auto dest : mod.dests){
                        q.push({mod.name, dest, (mod.state ? "high" : "low")});
                    }
                }
            }else if(mod.type == "conjunction"){
                mod.last_recordered_inputs[source] = pulse;
                bool flag = all_of(mod.last_recordered_inputs.begin(), mod.last_recordered_inputs.end(), [](auto el){
                    return el.second == "high";
                });

                for(auto dest : mod.dests){
                    q.push({mod.name, dest, (flag ? "low" : "high")});
                }
            }
        }
    }

    return to_string(low_cnt * high_cnt);
}

string day_20::part2(){
    auto module_map = get_input_day_20();

    unordered_map<string, int> results;
    unordered_map<string, int> visited;
    for(auto kv : module_map)
        if(find(kv.second.dests.begin(), kv.second.dests.end(), "ft") != kv.second.dests.end())
            visited[kv.first] = 0;

    int counter = 0;
    uint64_t res = 1;
    while(1){
        counter++;

        queue<tuple<string, string, string>> q;
        for(auto kv : module_map["broadcaster"].dests){
            q.push({"broadcaster", kv, "low"});
        }

        bool breaked = 0;
        while(!q.empty()){
            const auto &t = q.front();
            q.pop();

            string source = get<0>(t), target = get<1>(t), pulse = get<2>(t);

            if(module_map.find(target) == module_map.end())continue;

            auto &mod = module_map[target];

            if(mod.name == "ft" && pulse == "high"){
                visited[source]++;

                if(results.find(source) == results.end())
                    results[source] = counter;

                if(all_of(visited.begin(), visited.end(), [](auto el){return el.second > 0;})){
                    for(auto kv : results)
                        res = res * kv.second / __gcd(res, (uint64_t)kv.second);

                    breaked = 1;
                    break;
                }
            }

            if(mod.type == "flip_flop"){
                if(pulse == "low"){
                    mod.state = !mod.state;
                    
                    for(auto dest : mod.dests){
                        q.push({mod.name, dest, (mod.state ? "high" : "low")});
                    }
                }
            }else if(mod.type == "conjunction"){
                mod.last_recordered_inputs[source] = pulse;
                bool flag = all_of(mod.last_recordered_inputs.begin(), mod.last_recordered_inputs.end(), [](auto el){
                    return el.second == "high";
                });

                for(auto dest : mod.dests){
                    q.push({mod.name, dest, (flag ? "low" : "high")});
                }
            }
        }
        if(breaked)break;
    }
    return to_string(res);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

input_type get_input_day_20(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input20.txt" : "inputs/input20.txt");

    input_type map;

    string line;
    while(getline(file, line)){
        istringstream iss(line);
        string name;

        iss >> name;
        iss.ignore(256, ' ');
        iss.ignore(256, ' ');
        char ch = name[0];

        if(ch != 'b'){
            name = name.substr(1);
        }
        map[name].name = name;

        if(ch == '%'){
            map[name].type = "flip_flop";
        }else if(ch == '&'){
            map[name].type = "conjunction";
        }else{
            map[name].type = "broadcaster";
        }

        string token;
        while(iss >> token){
            if(token.back() == ',')
                token = token.substr(0, token.size() - 1);

            map[name].dests.push_back(token);
        }
    }

    for(auto kv : map){
        for(auto str : kv.second.dests){
            if(map.count(str) > 0 && map[str].type == "conjunction"){
                map[str].last_recordered_inputs[kv.first] = "low";
            }
        }
    }

    return map;
}
