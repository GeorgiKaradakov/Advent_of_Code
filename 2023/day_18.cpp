#include "../headers/day_18.h"
using namespace std;
typedef pair<int, vector<vector<char>>> input_type;

input_type get_input_day_18();

string day_18::part1(){
    auto input = get_input_day_18();
    auto map = input.second;
    auto cnt = input.first;

    size_t top = map.size(), bottom = 0, left = map[0].size(), right = 0;

    for (size_t i = 0; i < map.size(); ++i) {
        string line;
        for(int x = 0; x < map[i].size(); x++)
            line += map[i][x];

        size_t hashPos = line.find('#');
        if (hashPos != std::string::npos) {
            top = std::min(top, i);
            bottom = std::max(bottom, i);
            left = std::min(left, hashPos);
            right = std::max(right, line.rfind('#'));
        }
    }

    auto floodFill = [&](int startX, int startY) {
        std::queue<pair<int ,int>> points;
        points.push({startX, startY});

        while (!points.empty()) {
            auto current = points.front();
            points.pop();

            int x = current.first;
            int y = current.second;

            if (x >= 0 && x < map[0].size() && y >= 0 && y < map.size() && map[y][x] == '.') {
                map[y][x] = 'x';  // Mark visited points

                // Add neighboring points to the queue
                points.push({x + 1, y});
                points.push({x - 1, y});
                points.push({x, y + 1});
                points.push({x, y - 1});
            }
        }
    };
    floodFill(75, 19);//for sample input

    for(auto vec : map){
        cnt += count_if(vec.begin(), vec.end(), [](auto ch){return ch == 'x' || ch == '#';});
    }

    return to_string(cnt);
}

string day_18::part2(){
    return "2";
}

//------------------------------------------------------------------------------User Defined Functions-----------------------------------------------------------------------------------

input_type get_input_day_18(){
    int t = 1;
    ifstream file(t == 0 ? "inputs/sample_input18.txt" : "inputs/input18.txt");
    vector<vector<char>> map(2000, vector<char>(2000, '.'));

    int x = 50, y = 50, c = 0;
    int cnt_hash = 0;
    string line;
    while(getline(file, line)){
        std::istringstream iss(line);
        char direction;
        int count;
        std::string color;
        iss >> direction >> count >> color;

        color = color.substr(1, color.size() - 2);

        for (int i = 0; i < count; ++i) {
            if (direction == 'R') {
                x += 1;
            } else if (direction == 'L') {
                x -= 1;
            } else if (direction == 'U') {
                y -= 1;
            } else if (direction == 'D') {
                y += 1;
            }

            if (x >= 0 && x < map[0].size() && y >= 0 && y < map.size()) {
                map[y][x] = '#';
            }
        }
    }

    return {cnt_hash, map};
}
