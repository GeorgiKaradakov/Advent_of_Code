#include <day_2.h>
using namespace std;

unordered_map<int, vector<vector<int>>> get_input2();

string day_2::part1(){
    auto input = get_input2();

    int res = 0;
    for(auto kv : input){
        bool breaked = 0;
        for(auto num : kv.second[0])
            if(num > 12){breaked = 1;break;}
        if(breaked)continue;

        for(auto num : kv.second[1])
            if(num > 13){breaked = 1;break;}
        if(breaked)continue;

        for(auto num : kv.second[2])
            if(num > 14){breaked = 1;break;}
        if(breaked)continue;

        res += kv.first;
    }

    return to_string(res);
}

string day_2::part2(){
    auto input = get_input2();

    int res = 0;
    for(auto kv : input){
        int max_r = INT_MIN, max_g = INT_MIN, max_b = INT_MIN;
        for(auto num : kv.second[0])
            max_r = max(max_r, num);

        for(auto num : kv.second[1])
            max_g = max(max_g, num);

        for(auto num : kv.second[2])
            max_b = max(max_b, num);

        res += max_r * max_g * max_b;
    }

    return to_string(res);
}

//-------------------------------------------------------------------------User defined functions-------------------------------------------------------------------------------------------

unordered_map<int, vector<vector<int>>> get_input2(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input2.txt" : "inputs/input2.txt");

    unordered_map<string, int> cont{ {"red", 0}, {"red,", 0}, {"red;", 0}, {"green", 1}, {"green,", 1}, {"green;", 1}, {"blue", 2}, {"blue,", 2}, {"blue;", 2}};

    unordered_map<int, vector<vector<int>>> res;
    while(!file.eof()){
        string token, s;
        int game;
        file >> token;
        file >> token;

        int ind = 0;
        while(isdigit(token[ind])){s += token[ind++];}
        game =  atoi(s.c_str());
        res[game] = vector<vector<int>>(3);

        while(file.get() != '\n' && !file.eof()){
            file >> token;
            file >> s;

            res[game][cont[s]].push_back(atoi(token.c_str()));
        }
    }

    return res;
}