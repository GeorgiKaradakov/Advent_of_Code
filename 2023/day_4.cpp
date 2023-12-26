#include "../headers/day_4.h"
using namespace std;

struct card{
    vector<int> winning;
    vector<int> have;
};

typedef vector<card> input_type;

input_type get_input_day_4();
bool binary_search(const vector<int> &vec, int elem);

string day_4::part1(){
    auto lines = get_input_day_4();
    int sum = 0;
    for(auto card : lines){
        int factor = -1;
        for(auto num : card.winning){
            if(binary_search(card.have, num))
                factor++;
        }

        if(factor != -1)
            sum += int(pow(2, factor));
    }

    return to_string(sum);
}

string day_4::part2(){
    auto cards = get_input_day_4();
    vector<int> instances(cards.size(), 1);

    for(int i = 0 ; i < cards.size(); i++){
        int cnt = 0;
        for(auto num : cards[i].winning){
            if(binary_search(cards[i].have, num))cnt++;
        }

        for(int j = i + 1; j < i + 1 + cnt; j++){
            instances[j] += instances[i];
        }
    }

    return (to_string(accumulate(instances.begin(), instances.end(), 0)));
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

bool binary_search(const vector<int> &vec, int elem){
    int l = 0, h = vec.size() - 1;

    while(l <= h){
        int mid = l + (h - l) / 2;

        if(vec[mid] == elem)return 1;
        else if(vec[mid] > elem)h = mid - 1;
        else l = mid + 1;
    }

    return 0;
}

input_type get_input_day_4(){
    int t = 1;
    ifstream file(t == 0  ? "inputs/sample_input4.txt" :"inputs/input4.txt");
    input_type cards;

    string line;
    while(getline(file, line)){
        string num;
        istringstream iss(line);
        vector<int> winning, have;

        iss.ignore(265, ':');

        while(1){
            iss >> num;
            if(num == "|")break;
            winning.push_back(atoi(num.c_str()));
        }

        while(iss >> num){
            have.push_back(atoi(num.c_str()));
        }

        sort(have.begin(), have.end());
        cards.push_back(card{winning, have});
    }

    return cards;
}