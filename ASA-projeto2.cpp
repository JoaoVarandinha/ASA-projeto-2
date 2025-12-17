#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct {
    int num_inter;              //N
    int total_trucks;           //M
    int truck_min, truck_max;   //m1 e m2
    int num_paths;              //K
    vector<vector<int>> paths;  //caminhos
} input_data;


const input_data readInput() {
    input_data info;

    //Read number of intersections, number of trucks, range of truck numbers and number of paths
    cin >> info.num_inter >> info.total_trucks >> info.truck_min >> info.truck_max >> info.num_paths;

    info.paths.resize(info.num_inter + 1);

    //Read the paths between intersections and turn them into a graph
    for (int i = 0; i < info.num_paths; i++) {
        int origin, destination;
        cin >> origin >> destination;
        info.paths[origin].push_back(destination);
    }

    return info;
}

int calculateTruckToPath(int total_trucks, int total_paths) {
    return 1 + (total_paths % total_trucks);
}

vector<int> getTopologicalOrder(const input_data info) {
    vector<int> top_order;
    vector<int> degrees(info.num_inter + 1, 0);

    for (int i = 1; i <= info.num_inter; i++) {
        for (int j : info.paths[i])
            degrees[j]++;
    }

    queue<int> q;
    for (int j = 1; j <= info.num_inter; j++) {
            if (degrees[j] == 0) q.push(j);
    }

    while (!q.empty()) {
        int inter = q.front();
        q.pop();
        top_order.push_back(inter);

        for (int k : info.paths[inter]) {
            degrees[k]--;
            if (degrees[k] == 0) q.push(k);
        }
    }

    return top_order;
}

vector<vector<pair<int,int>>> solve(const input_data info) {
    vector<vector<int>> total_paths(info.num_inter + 1, vector<int>(info.num_inter + 1, 0));
    vector<vector<pair<int,int>>> truck_routes(info.truck_max - info.truck_min + 1);
    vector<int> top_order = getTopologicalOrder(info);
    // Para cada origem i, fazemos uma DP iterativa ao longo da ordem topológica
    vector<int> paths_a_To_b(info.num_inter + 1, 0);

    for (int i = 1; i <= info.num_inter; i++) {
        // Inicializar DP
        fill(paths_a_To_b.begin(), paths_a_To_b.end(), 0);
        paths_a_To_b[i] = 1;  // um caminho trivial que começa em i

        // Propagar contagens em ordem topológica
        for (int j : top_order) {
            if (paths_a_To_b[j] == 0) continue;  // nada para propagar
            for (int k : info.paths[j]) {
                paths_a_To_b[k] += paths_a_To_b[j];
                if (paths_a_To_b[k] > info.total_trucks)
                    paths_a_To_b[k] -= info.total_trucks;
            }
        }

        // Guardar resultados: nº de caminhos de i para t
        for (int t = 1; t <= info.num_inter; t++) {
            if (i == t || paths_a_To_b[t] == 0) continue;      // ignorar pares A == B

            total_paths[i][t] = paths_a_To_b[t];

            int truck_num = calculateTruckToPath(info.total_trucks, paths_a_To_b[t]);
            if (truck_num >= info.truck_min && truck_num <= info.truck_max) {
                truck_routes[truck_num - info.truck_min].emplace_back(i,t);
            }
        }
    }
    return truck_routes;
}

void printData(input_data info, vector<vector<pair<int,int>>> truck_routes) {
    for (int i = info.truck_min; i <= info.truck_max; i++) {
        cout << "C" << i;
        for (pair<int,int> path : truck_routes[i - info.truck_min]) {
            cout << " " << path.first << "," << path.second;
        }
        cout << "\n";
    }
    return;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    const input_data info = readInput();

    vector<vector<pair<int,int>>> truck_routes = solve(info);    

    printData(info, truck_routes);

    return 0;
}