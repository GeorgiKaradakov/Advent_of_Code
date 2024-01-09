#include "../headers/day_6.h"
using namespace std;
typedef vector<string> input_type;

input_type get_input_day_6(const string &file_path);
int get_start_pos(const string &str, int part);

string day_6::part1(const string &file_path){
    auto input = get_input_day_6(file_path);
    int res = 0;

    for_each(input.begin(), input.end(), [&res](auto el){res += get_start_pos(el, 1);});//did it this way because I i stacked the sample input into one file and read it into vector of strings

    return to_string(res);
    // return to_string(get_start_pos(input[0], 1));          //for the input you can do this instead
}

string day_6::part2(const string &file_path){
    auto input = get_input_day_6(file_path);
    int res = 0;

    for_each(input.begin(), input.end(), [&res](auto el){res += get_start_pos(el, 2);});//did it this way because I i stacked the sample input into one file and read it into vector of strings

    return to_string(res);
    // return to_string(get_start_pos(input[0], 2));          //for the input you can do this instead
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

int get_start_pos(const string &str, int part){
    unordered_map<char, int> sw;

    for(int i = 0; i < str.size(); i++){
        if(part == 1 && i < 4){
            sw[str[i]]++;
        }else if(part == 2 && i < 14){
            sw[str[i]]++;
        }else{
            if(all_of(sw.begin(), sw.end(), [](auto kv){return kv.second == 1 || kv.second == 0;}))
                return i;

            sw[str[i - (part == 1 ? 4 : 14)]]--;
            sw[str[i]]++;
        }
    }

    return -1;
}

input_type get_input_day_6(const string &file_path){
    ifstream file(file_path);
    input_type out;

    string line;
    while(getline(file, line))
        out.push_back(line);

    file.close();

    return out;
}