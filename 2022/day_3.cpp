#include "../headers/day_3.h"
using namespace std;
typedef vector<string> input_type;

input_type get_input_day_3(const string &file_path);

string day_3::part1(const string &file_path){
    auto input = get_input_day_3(file_path);
    vector<char> cont;

    for(auto line : input){
        int mid = line.size() / 2;

        unordered_map<char, bool> cnt;
        for(int i = 0; i < mid; i++){
            cnt[line[i]] = 0;
        }

        for(int i = mid; i < line.size(); i++){
            if(cnt.count(line[i]) > 0)
                cnt[line[i]] = 1;
        }

        for(auto kv : cnt){
            if(kv.second)
                cont.push_back(kv.first);
        }
    }

    int res = 0;
    for_each(cont.begin(), cont.end(), [&res](auto ch){
        if('a' <= ch && ch <= 'z'){
            res += ch - 'a' + 1;
        }else{
            res += ch - 'A' + 1 + 26;
        }
    });

    return to_string(res);
}

string day_3::part2(const string &file_path){
    auto input = get_input_day_3(file_path);
    vector<char> cont;

    for(int i = 0; i < input.size() - 2; i+=3){
        unordered_map<char, bool> cnt1;

        for(int j = 0; j < input[i].size(); j++)
            cnt1[input[i][j]] = 0;

        for(int j = 0; j < input[i + 1].size(); j++)
            if(cnt1.count(input[i + 1][j]) > 0)
                cnt1[input[i + 1][j]] = 1;

        for(auto kv : cnt1)
            if(cnt1[kv.first] && input[i + 2].find(kv.first) != string::npos){
                cont.push_back(kv.first);
                break;
            }
    }

    int res = 0;
    for_each(cont.begin(), cont.end(), [&res](auto ch){
        if('a' <= ch && ch <= 'z'){
            res += ch - 'a' + 1;
        }else{
            res += ch - 'A' + 1 + 26;
        }
    });

    return to_string(res);
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

input_type get_input_day_3(const string &file_path){
    ifstream file(file_path);

    input_type out;

    string line;
    while(getline(file, line))
        out.push_back(line);

    file.close();

    return out;
}