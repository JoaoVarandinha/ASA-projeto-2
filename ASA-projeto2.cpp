#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int num_inter;              //N
    int total_trucks;           //M
    int truck_min, truck_max;   //m1 e m2
    int num_paths;              //K
    vector<vector<int>> paths;  //caminhos
} input_data;


input_data readInput() {
    input_data info;

    //Read number of intersections, number of trucks, range of truck numbers and number of paths
    cin >> info.num_inter >> info.total_trucks >> info.truck_min >> info.truck_max >> info.num_paths;

    info.paths.reserve(info.num_paths);

    //Read guided paths between intersections
    for (int i = 0; i < info.num_paths; i++) {
        int a, b;
        cin >> a >> b;
        info.paths[a].push_back(b);
    }

    return info;
}

int calculateTruckToPath(int total_trucks, int total_paths) {
    return 1 + (total_paths % total_trucks);
}

vector<vector<string>> solve(input_data info) {
    vector<vector<int>> total_paths(info.num_paths + 1, vector<int>(info.num_paths + 1, 0));
    vector<vector<string>> truck_paths(info.total_trucks);
    vector<int> top_order(info.num_inter + 1);

    for (int i = 1; i < info.num_paths + 1; i++) {
        if (info.paths[i].size() == 0) continue;

        for (int j = 1; j < info.num_paths + 1; j++) {
            if (i == j) continue;


            
        }
    }

    int truck_num = calculateTruckToPath(info.total_trucks, total_paths[i][j]);
    if (info.truck_min <= truck_num <= info.truck_max) {
        truck_paths[truck_num - info.total_trucks] = to_string(i) + "," + to_string(j);
    }
    

    return truck_paths;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    input_data info = readInput();

    vector<vector<string>> truck_paths = solve(info);    

    for (int i = info.truck_min; i < info.truck_max; i++) {
        cout << "C" << i;
        for (string path : truck_paths[i - info.total_trucks]) {
            cout << " " << path;
        }
        cout << "\n";
    }

    return 0;
}