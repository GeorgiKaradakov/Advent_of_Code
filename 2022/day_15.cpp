//                    Solution implemented through HyperNeutrino's video (https://www.youtube.com/watch?v=OG1QwJ2RKsU&list=PLnNm9syGLD3yf-YW-a5XNh1CJN07xr0Kz&index=15)  
#include "../headers/day_15.h"
using namespace std;
typedef vector<tuple<int, int, int, int>> input_type;
using ui64 = uint64_t;

const int Y = 2000000;
const int M = 4000000;

input_type get_input_day_15(const string &file_path);

string day_15::part1(const string &file_path){
    auto input = get_input_day_15(file_path);
    set<int> known, cannot;
    vector<pair<int, int>> intervals;

    for(auto t : input){
        int sx, sy, bx, by;tie(sx, sy, bx, by) = t;

        int d = abs(sx - bx) + abs(sy - by);
        int p = d - abs(sy - Y);

        if(p < 0)continue;
        int nx=sx-p, ny=sx+p;

        intervals.push_back({nx, ny});

        if(by == Y)
            known.insert(bx);
    }

    sort(intervals.begin(), intervals.end());

    vector<pair<int, int>> n;
    for(auto p : intervals){
        if(n.empty()){
            n.push_back(p);
            continue;
        }

        int lo, hi, nlo, nhi;tie(lo, hi) = p;tie(nlo, nhi) = n.back();

        if(lo > nhi + 1){
            n.push_back(p);
            continue;
        }

        n.back().second = max(nhi, hi);
    }

    for(auto p : n){
        for(int i = p.first; i <= p.second; i++)cannot.insert(i);
    }

    return to_string(cannot.size() - known.size());
}

string day_15::part2(const string &file_path){
    auto input = get_input_day_15(file_path);

    for(int i = 0; i <= M; i++){
        vector<pair<int, int>> intervals;
        for(auto t : input){
            int sx, sy, bx, by;tie(sx, sy, bx, by) = t;

            int d = abs(sx - bx) + abs(sy - by);
            int p = d - abs(sy - i);

            if(p < 0)continue;
            int nx=sx-p, ny=sx+p;

            intervals.push_back({nx, ny});
        }

        sort(intervals.begin(), intervals.end());

        vector<pair<int, int>> n;
        for(auto p : intervals){
            if(n.empty()){
                n.push_back(p);
                continue;
            }

            int lo, hi, nlo, nhi;tie(lo, hi) = p;tie(nlo, nhi) = n.back();

            if(lo > nhi + 1){
                n.push_back(p);
                continue;
            }

            n.back().second = max(nhi, hi);
        }

        int x = 0;
        for(auto p : n){
            if(x < p.first){
                stringstream ss;
                ss << x << ' ' << i;
                return ss.str(); //when you get the result calculate it using calculator
            }
            x = max(x, p.second + 1);
            if(x > M)break;
        }
    }

    return to_string(2);
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

input_type get_input_day_15(const string &file_path){
    ifstream file(file_path);
    input_type out;
    
    string s;
    regex pattern("[-]?\\d+");
    while(getline(file, s)){
        sregex_iterator it(s.begin(), s.end(), pattern);
        out.push_back({stoi((it++)->str()), stoi((it++)->str()), stoi((it++)->str()), stoi(it->str())});
    }
    
    file.close();
    return out;
}