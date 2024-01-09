#include "../headers/day_7.h"
using namespace std;

struct directory{
    directory* parent;
    string name;
    uint64_t size = 0;
    vector<directory*> sub_dirs;

    directory(){}
    directory(string name, directory* par){
        this->name = name;
        this->parent = par;
    }
};

typedef directory* input_type;

input_type get_input_day_7(const string &file_path);
uint64_t get_size(directory* root);
void get_all_sizes_part1(directory* root, uint64_t &size);
void get_smallest_dir_part2(directory *root, uint64_t &smallest, uint64_t at_least);

string day_7::part1(const string &file_path){
    auto root = get_input_day_7(file_path);

    uint64_t res = 0;
    get_all_sizes_part1(root, res);

    return to_string(res);
}

string day_7::part2(const string &file_path){
    auto root = get_input_day_7(file_path);

    uint64_t free_space = 30000000 - (70000000 - get_size(root)), res = INT_MAX;
    get_smallest_dir_part2(root, res, free_space);

    return to_string(res);
}

//--------------------------------------------------------------------------------- helper functions ---------------------------------------------------------------------------------

void get_smallest_dir_part2(directory *root, uint64_t &smallest, uint64_t at_least){
    auto size = get_size(root);

    if(size >= at_least){
        smallest = min(smallest, size);
    }

    for(auto next : root->sub_dirs){
        get_smallest_dir_part2(next, smallest, at_least);
    }
}

void get_all_sizes_part1(directory* root, uint64_t &size){
    auto t_size = get_size(root);
    size += t_size <= 100000 ? t_size : 0;

    for(auto next : root->sub_dirs){
        get_all_sizes_part1(next, size);
    }
}

uint64_t get_size(directory* root){
    if(root->sub_dirs.empty())return root->size;

    uint64_t size = root->size;
    for(auto n : root->sub_dirs){
        size += get_size(n);
    }

    return size;
}

input_type get_input_day_7(const string &file_path){
    ifstream file(file_path);

    directory *dir = new directory();
    dir->name = "/";
    directory *builder = dir;

    string line;
    while(getline(file, line)){
        istringstream iss(line); 
        string token;iss >> token;

        if(token == "$"){
            iss >> token;

            if(token == "cd"){
                iss >> token;

                if(token == ".."){
                    builder = !builder->parent ? dir : builder->parent;
                }else if(token == "/"){
                    builder = dir;
                }else{
                    auto it = find_if(builder->sub_dirs.begin(), builder->sub_dirs.end(), [&token](auto d){return d->name == token;});

                    if(it != builder->sub_dirs.end()){
                        builder = *it;
                    }else{
                        cout << "error: " << token << " not found!" << '\n';
                        return NULL;
                    }
                }
            }else if(token == "ls"){
                continue;
            }
        }else{
            if(token == "dir"){
                iss >> token;

                builder->sub_dirs.push_back(
                    new directory(token, builder)
                );
            }else{
                builder->size += atoi(token.c_str());
            }
        }
    }

    file.close();

    return dir;
}

    // auto dir = kv.second;
    // cout << kv.first << " from -> " << dir.parent << '\n';
    // cout << "has size: " << dir.size << '\n';
    // for(auto sub_dir : dir.sub_dirs){
    //     cout << "sub_dir: " << sub_dir << '\n';
    // }
    // cout << '\n';