#include "../headers/day_24.h"
using namespace std;
struct hail{
    double x, y, z;
    double dx, dy, dz;

    double get_a(){return this->dy;}
    double get_b(){return -this->dx;}
    double get_c(){return this->dy * this->x - this->dx * this->y;}
};

typedef vector<hail> input_type;

input_type get_input_day_24();

string day_24::part1(){
    auto hails = get_input_day_24();

    const double MIN = 200000000000000, MAX = 400000000000000;

    int res = 0;
    for(int i = 0; i < hails.size(); i++){
        for(int j = i + 1; j < hails.size(); j++){
            auto h1 = hails[i], h2 = hails[j];

            if(h1.get_a() * h2.get_b() == h1.get_b() * h2.get_a())
                continue;
            
            auto x = (h1.get_c() * h2.get_b() - h2.get_c() * h1.get_b()) / (h1.get_a() * h2.get_b() - h2.get_a() * h1.get_b());
            auto y = (h2.get_c() * h1.get_a() - h1.get_c() * h2.get_a()) / (h1.get_a() * h2.get_b() - h2.get_a() * h1.get_b());

            if(MIN <= x && x <= MAX && MIN <= y && y <= MAX){
                if((x - h1.x) * h1.dx >= 0 && (y - h1.y) * h1.dy >= 0 && 
                (x - h2.x) * h2.dx >= 0 && (y - h2.y) * h2.dy >= 0){
                        res++;
                }
            }
        }
    }

    return to_string(res);
}

string day_24::part2(){
    return "2";                                                     // part2 -> solved it using python and sympy 
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

input_type get_input_day_24(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input24.txt" : "inputs/input24.txt");

    input_type res;

    string line;
    while(getline(file, line)){
        istringstream iss(line);
        hail h;

        string splited;
        bool first = 1;
        while(getline(iss, splited, '@')){
            istringstream tokens(splited);
            string a, b, c;
            tokens >> a >> b >> c;

            a = a.substr(0, a.size() - 1);
            b = b.substr(0, b.size() - 1);

            if(first){
                h.x = stod(a);
                h.y = stod(b);
                h.z = stod(c);
                first = 0;
            }else{
                h.dx = stod(a);
                h.dy = stod(b);
                h.dz = stod(c);
            }
        }
        res.push_back(h);
    }

    return res;
}