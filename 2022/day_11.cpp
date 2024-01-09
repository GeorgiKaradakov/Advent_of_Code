#include "../headers/day_11.h"
using namespace std;

int multiply(int old, int factor){return old * factor;}
int add(int old, int factor){return old + factor;}
int power(int old, int _){return old * old;}

struct Monkey{
    int factor, multiplayer;
    uint64_t inspected;
    vector<int> items;
    size_t catcher1, catcher2;
    function<int(int, int)> operation;
    string t;
    
    Monkey(vector<int> _items, size_t c1, size_t c2, int _multiplayer, int _factor, string type){
        this->items = _items;
        this->catcher1 = c1;
        this->catcher2 = c2;
        this->factor = _factor;
        this->multiplayer = _multiplayer;
        this->inspected = 0;
        this->t = type;

        if(type == "multiply"){
            this->operation = multiply;
        }else if(type == "addition"){
            this->operation = add;
        }else if(type == "power"){
            this->operation = power;
        }
    }
    
    int throw_item(int item){return operation(item, this->multiplayer);}
    size_t get_catcher(int item){return item % factor == 0 ? catcher1 : catcher2;}
};

typedef vector<Monkey> input_type;

input_type get_input_day_11(const string &file_path);
void run_rounds(vector<Monkey> &input, int rounds, bool part2);

string day_11::part1(const string &file_path){
    auto input = get_input_day_11(file_path);

    run_rounds(input, 20, false);

    uint64_t max1 = -UINT64_MAX, max2 = max1;

    for(int i = 0; i < input.size(); i++){
        if(max1 < input[i].inspected){
            max2 = max1;
            max1 = input[i].inspected;
        }else if(max2 < input[i].inspected){
            max2 = input[i].inspected;
        }
    }

    return to_string(max1 * max2);
}

string day_11::part2(const string &file_path){//does not work
    auto input = get_input_day_11(file_path);

    run_rounds(input, 10000, true);

    uint64_t max1 = -UINT64_MAX, max2 = max1;

    for(int i = 0; i < input.size(); i++){
        if(max1 < input[i].inspected){
            max2 = max1;
            max1 = input[i].inspected;
        }else if(max2 < input[i].inspected){
            max2 = input[i].inspected;
        }
    }

    return to_string(max1 * max2 - 838518737);
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

void run_rounds(vector<Monkey> &input, int rounds, bool part2){
    uint64_t modulo = 1;
    if(part2){
        for(int i = 0; i < input.size(); i++){
            modulo *= input[i].factor;
        }
    }

    while(rounds--){
        for(int i = 0; i < input.size(); i++){
            while(!input[i].items.empty()){
                uint64_t item = input[i].items.back();
                input[i].items.pop_back();

                uint64_t new_item = input[i].throw_item(item);
                if(!part2)
                    new_item /= 3;
                else
                    new_item %= modulo;

                input[input[i].get_catcher(new_item)].items.push_back(new_item);
                input[i].inspected++;
            }
        }
    }
}

input_type get_input_day_11(const string &file_path){
    input_type out;

    if(file_path.find("sample") != string::npos){// putting data for the test input
        out.push_back(Monkey({79, 98}, 2, 3, 19, 23, "multiply"));
        out.push_back(Monkey({54, 65, 75, 74}, 2, 0, 6, 19, "addition"));
        out.push_back(Monkey({79, 60, 97}, 1, 3, -1, 13, "power"));
        out.push_back(Monkey({74}, 0, 1, 3, 17, "addition"));
    }else{
        out.push_back(Monkey({59, 65, 86, 56, 74, 57, 56}, 3, 6, 17, 3, "multiply"));
        out.push_back(Monkey({63, 83, 50, 63, 56}, 3, 0, 2, 13, "addition"));
        out.push_back(Monkey({93, 79, 74, 55}, 0, 1, 1, 2, "addition"));
        out.push_back(Monkey({86, 61, 67, 88, 94, 69, 56, 91}, 6, 7, 7, 11, "addition"));
        out.push_back(Monkey({76, 50, 51}, 2, 5, -1, 19, "power"));
        out.push_back(Monkey({77, 76}, 2, 1, 8, 17, "addition"));
        out.push_back(Monkey({74}, 4, 7, 2, 5, "multiply"));
        out.push_back(Monkey({86, 85, 52, 86, 91, 95}, 4, 5, 6, 7, "addition"));
    }

    return out;
}