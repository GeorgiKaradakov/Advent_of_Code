#include "../headers/day_13.h"
using namespace std;

struct Value {
    int i_value = -1;
    vector<Value> l_value;

    Value(int i) { this->i_value = i; }
    Value(vector<Value> i) { this->l_value = i; }
    Value() {
        this->i_value = -1;
        this->l_value.clear();
    }
};

enum result{
    wrong_order = 0,
    correct_order,
    equal_order
};

typedef vector<pair<Value, Value>> input_type;

input_type get_input_day_13(const string &file_path);
Value get_input_util(const std::string& line, int& pos);
void chop_char(string &line, int cnt = 1){line = line.substr(cnt, line.size() - 1);}
result compare_packets(const Value& lhs, const Value& rhs);
result compare_lists(const vector<Value> &lhs, const vector<Value> &rhs);

std::string valueToString(const Value& value) {
    if (value.i_value != -1) {
        // It's an integer
        return std::to_string(value.i_value);
    } else {
        // It's a list
        std::string result = "[";
        for (size_t i = 0; i < value.l_value.size(); ++i) {
            if (i > 0) {
                result += ",";
            }
            result += valueToString(value.l_value[i]);
        }
        result += "]";
        return result;
    }
}

string day_13::part1(const string &file_path){
    auto input = get_input_day_13(file_path);

    int res = 0;
    for(int i = 0; i < input.size(); i++){
        if(compare_packets(input[i].first, input[i].second))
            res += i + 1;
    }

    return to_string(res);
}

string day_13::part2(const string &file_path){
    auto input = get_input_day_13(file_path);
    vector<Value> packets;
    string dec1 = "[[2]]", dec2 = "[[6]]";
    int ind = 0;
    auto v1 = get_input_util(dec1, ind); ind = 0; auto v2 = get_input_util(dec2, ind);
    packets.push_back(v1);packets.push_back(v2);

    for(auto p : input){
        packets.push_back(p.first);packets.push_back(p.second);
    }

    sort(packets.begin(), packets.end(), [](const auto &lhs, const auto &rhs){return compare_packets(lhs, rhs);});

    int res = 1;
    for(int i = 0; i < packets.size(); i++){
        if(compare_packets(packets[i], v1) == result::equal_order || compare_packets(packets[i], v2) == result::equal_order)res *= i + 1;
    }

    return to_string(res);
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

result compare_lists(const vector<Value> &lhs, const vector<Value> &rhs){
    for(int i = 0; i < max(lhs.size(), rhs.size()); ++i){
        if(i == lhs.size())return result::correct_order;
        else if(i == rhs.size())return result::wrong_order;
        else{
            auto res = compare_packets(lhs[i], rhs[i]);
            if(res != result::equal_order)return res;
        }
    }

    return result::equal_order;
}

result compare_packets(const Value& lhs, const Value& rhs){
    if(lhs.i_value != -1 && rhs.i_value != -1){
        return (lhs.i_value < rhs.i_value ? result::correct_order : (lhs.i_value > rhs.i_value ? result::wrong_order : result::equal_order)); 
    }else if(lhs.i_value == -1 && rhs.i_value == -1)return compare_lists(lhs.l_value, rhs.l_value);
    else if(lhs.i_value == -1)return compare_lists(lhs.l_value, {rhs});
    else return compare_lists({lhs}, rhs.l_value);
}

Value get_input_util(const std::string& line, int& pos) {
    if (line[pos] == '[') {
        std::vector<Value> listValues;
        pos++;
        while (line[pos] != ']') {
            if (line[pos] == ',') {
                pos++;
                continue;
            }
            listValues.push_back(get_input_util(line, pos));
        }
        pos++;
        return Value(listValues);
    }
    else {
        size_t startPos = pos;
        while (isdigit(line[pos])) {
            pos++;
        }
        return Value(std::stoi(line.substr(startPos, pos - startPos)));
    }
}

input_type get_input_day_13(const string &file_path){
    ifstream file(file_path);
    input_type out;

    string line;
    pair<Value, Value> p_pack;
    bool which = 1;
    while(getline(file, line)){
        if(line.empty()){
            out.push_back(p_pack);
            continue;
        }
        int i = 0;
        auto v = get_input_util(line, i);

        if(which){
            p_pack.first = v;
            which = !which;
        }else{
            p_pack.second = v;
            which = !which;
        }
    }
    out.push_back(p_pack);

    file.close();

    return out;
}