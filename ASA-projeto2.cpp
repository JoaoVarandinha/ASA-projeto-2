#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int num_inter;
    int num_trucks;
    int truck_min, truck_max;
    int num_paths;
    vector<vector<int>> paths;
} input_data;


input_data readInput() {
    input_data info;

    //Read number of intersections, number of trucks, range of truck numbers and number of paths
    cin >> info.num_inter >> info.num_trucks >> info.truck_min >> info.truck_max >> info.num_paths;

    //Read guided paths between intersections
    for(int i = 0; i < info.num_paths; i++) {
        int a, b;
        cin >> a >> b;
        info.paths[a].push_back(b);
    }

    return info;
}

vector<vector<string>> solve(input_data info) {
    vector<vector<string>> truck_paths;

    
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    input_data info = readInput();

    vector<vector<string>> truck_paths = solve(info);    

    for (int i = info.truck_min; i < info.truck_max; i++) {
        cout << "C" << i;
        for (string path : truck_paths[i]) {
            cout << " " << path;
        }
        cout << "\n";
    }

    return 0;
}