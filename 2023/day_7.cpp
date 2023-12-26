#include "../headers/day_7.h"
using namespace std;
typedef vector<pair<pair<string, string>, int>> input_type;

unordered_map<char, int> comparer_cards{
    {'A', 14}, {'K', 13}, {'Q', 12}, {'T', 10}, {'9', 9},
    {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}
};

unordered_map<string, int> comparer_hands{
    {"hc", 1}, {"op", 2}, {"tp", 3}, {"tok", 4}, {"fh", 5}, {"fook", 6}, {"fiok", 7}
};

input_type get_input_day_7(int part);
bool compare_hands(const pair<pair<string, string>, int> &lhs, const pair<pair<string, string>, int> &rhs);
string get_type(const string &hand);
string get_type2(string hand, const unordered_set<char> &js, string curr_max_type, int ind);


string day_7::part1(){
    auto hands = get_input_day_7(1);

    sort(hands.begin(), hands.end(), compare_hands);

    unsigned long long sum = 0;
    int rank = 1;
    for(auto hand : hands){
        sum += rank * hand.second;
        rank++;
    }

    return to_string(sum);
}

string day_7::part2(){
    auto hands = get_input_day_7(2);

    sort(hands.begin(), hands.end(), compare_hands);

    unsigned long long sum = 0;
    int rank = 1;
    for(auto hand : hands){
        sum += rank * hand.second;
        rank++;
    }

    return to_string(sum);
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

string get_type2(string hand, const unordered_set<char> &js, string curr_max_type, int ind){
    if(ind == 5){
        return get_type(hand);
    }

    if(hand[ind] != 'J')
        return get_type2(hand, js, curr_max_type, ind + 1);

    string max_type = curr_max_type;

    for(auto ch : js){
        hand[ind] = ch;
        string t = get_type2(hand, js, max_type, ind + 1);
        max_type = max(comparer_hands[max_type], comparer_hands[t]) == comparer_hands[t] ? t : max_type;
    }
    hand[ind] = 'J';

    return max_type;
}

bool compare_hands(const pair<pair<string, string>, int> &lhs, const pair<pair<string, string>, int> &rhs){
    if(comparer_hands[lhs.first.second] > comparer_hands[rhs.first.second])return 0;
    else if(comparer_hands[lhs.first.second] < comparer_hands[rhs.first.second])return 1;
    int ind = 0;
    while(comparer_cards[lhs.first.first[ind]] == comparer_cards[rhs.first.first[ind]])++ind;

    return comparer_cards[lhs.first.first[ind]] < comparer_cards[rhs.first.first[ind]];
}

input_type get_input_day_7(int part){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input7.txt" : "inputs/input7.txt");
    input_type out;

    if(part == 2)
        comparer_cards['J'] = 1;
    else
        comparer_cards['J'] = 11;

    while(!file.eof()){
        string hand, type;
        int bid;

        file >> hand;
        file >> bid;

        if(part == 1)type = get_type(hand);
        else if(part == 2){
            if(hand == "JJJJJ"){
                type = "fiok";
            }else if(hand.find('J') != string::npos){
                unordered_set<char> js;
                for(auto ch : hand){
                    if(ch != 'J')
                        js.insert(ch);
                }

                type = get_type2(hand, js, "hc", 0);
            }else{
                type = get_type(hand);
            }
        }

        out.push_back({{hand, type}, bid});
    }

    return out;
}

string get_type(const string &hand){
    unordered_map<char, int> counter;
    for(auto ch : hand){
        counter[ch]++;
    }

    if(counter.size() == 1)return "fiok";
    else if(counter.size() == 2){
        for(auto kv : counter){
            if(kv.second == 1 || kv.second == 4)return "fook";
            else if(kv.second == 2 || kv.second == 3)return "fh"; 
        }
    }else if(counter.size() == 3){
        for(auto kv : counter){
            if(kv.second == 3)return "tok";
            else if(kv.second == 2)return "tp";
        }
    }else if(counter.size() == 4){
        return "op";
    }else if(counter.size() == 5){
        return "hc";
    }

    return "";
}