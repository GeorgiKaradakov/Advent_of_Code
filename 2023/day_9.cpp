#include "../headers/day_9.h"
using namespace std;
typedef vector<vector<int>> input_type;

input_type get_input_day_9();
void get_history(const vector<int> &seq, int cnt, int size, int &history, int part);

string day_9::part1(){
    auto nums = get_input_day_9();

    int total = 0;
    for(auto seq : nums){
        int his = 0;
        get_history(seq, 0, seq.size(), his, 1);
        total += his + seq.back();
    }

    return to_string(total);
}

string day_9::part2(){
    auto nums = get_input_day_9();

    int total = 0;
    for(auto seq : nums){
        int his = 0;
        get_history(seq, 0, seq.size(), his, 2);

        his *= -1;
        his += seq.front();
        total += his;
    }

    return to_string(total);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

void get_history(const vector<int> &seq, int cnt, int size, int &history, int part){
    if(cnt == size)return;
    vector<int> t;

    int c = 1;
    for(int i = 1; i < seq.size(); i++){
        t.push_back(seq[i] - seq[i - 1]);

        if(t.size() >= 2){
            c += t[t.size() - 1] == t[t.size() - 2];
        }
    }

    get_history(t, c, size - 1, history, part);

    if(part == 1)
        history += t.back();
    else if(part == 2){
        history *= -1;
        history += t.front();
    }
}

input_type get_input_day_9(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input9.txt" : "inputs/input9.txt");

    input_type out;

    string line;
    while(getline(file, line)){
        istringstream iss(line);
        vector<int> t;

        int num;
        while(!iss.eof()){
            iss >> num;
            t.push_back(num);
        }

        out.push_back(t);
    }

    return out;
}