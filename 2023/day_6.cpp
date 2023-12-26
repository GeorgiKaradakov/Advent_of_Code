#include "../headers/day_6.h"
using namespace std;
typedef uint64_t uint;
typedef vector<vector<uint>> input_type;

input_type get_input_day_6(int part);

string day_6::part1(){
    auto td = get_input_day_6(1);
    int size = td[0].size();

    int sum = 1;
    for(int i = 0; i < size; i++){
        int time = td[0][i], dist = td[1][i];

        uint start, end;
        for(uint j = 1; j <= time; j++){
            if(j * (time - j) > dist){
                start = j;
                break;
            }
        }

        for(uint j = time; j >= 0; j--){
            if(j * (time - j)> dist){
                end = j;
                break;
            }
        }

        sum *= (end - start + 1);
    }

    return to_string(sum);
}

string day_6::part2(){
    auto td = get_input_day_6(2);

    uint time = td[0][0], dist = td[1][0];

    uint start, end;
    for(uint j = 1; j <= time; j++){
        if(j * (time - j) > dist){
            start = j;
            break;
        }
    }

    for(uint j = time; j >= 0; j--){
        if(j * (time - j)> dist){
            end = j;
            break;
        }
    }

    return to_string(end - start + 1);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

input_type get_input_day_6(int part){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input6.txt" : "inputs/input6.txt");
    input_type out(2);

    string line;
    int i = 0;
    while(getline(file, line)){
        string num;
        for(auto ch : line){
            if('0' <= ch && ch <= '9'){
                num += ch;
            }else if(!num.empty()){
                if(part == 1){
                    uint n = stoull(num);
                    num = "";
                    out[i].push_back(n);
                }
            }
        }
        if(!num.empty()){
            uint n = stoull(num);
            out[i].push_back(n);
        }

        i++;
    }

    return out;
}