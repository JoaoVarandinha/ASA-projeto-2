#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
 * Structure that stores all input data.
 */
typedef struct {
    int num_inter;              // N: number of intersections
    int total_trucks;           // M: total trucks
    int truck_min, truck_max;   // m1 and m2: truck interval
    int num_paths;              // K: number of paths
    vector<vector<int>> paths;  // adjacency list
} input_data;

/*
 * Reads input from stdin and stores the data.
 * Returns the filled structure.
 */
const input_data readInput() {
    input_data info;

    // Read basic parameters
    cin >> info.num_inter >> info.total_trucks
        >> info.truck_min >> info.truck_max
        >> info.num_paths;

    // Resize adjacency list (1-based indexing)
    info.paths.resize(info.num_inter + 1);

    // Read unidirectional paths
    for (int i = 0; i < info.num_paths; i++) {
        int origin, destination;
        cin >> origin >> destination;
        info.paths[origin].push_back(destination);
    }

    return info;
}

/*
 * Computes which truck number is assigned to a path count.
 */
int calculateTruckToPath(int total_trucks, int total_paths) {
    return 1 + (total_paths % total_trucks);
}

/*
 * Computes a topological ordering of the graph using Kahn's algorithm.
 * Assumes DAG.
 */
vector<int> getTopologicalOrder(const input_data info) {
    vector<int> top_order;
    vector<int> degrees(info.num_inter + 1, 0);

    // Compute degree of each intersection
    for (int i = 1; i <= info.num_inter; i++) {
        for (int j : info.paths[i])
            degrees[j]++;
    }

    // Push nodes with zero degrees for processing
    queue<int> q;
    for (int j = 1; j <= info.num_inter; j++) {
        if (degrees[j] == 0) q.push(j);
    }

    // Process nodes
    while (!q.empty()) {
        int inter = q.front();
        q.pop();
        top_order.push_back(inter);

        for (int k : info.paths[inter]) {
            degrees[k]--;
            // Push new 0 degreee nodes for processing
            if (degrees[k] == 0) q.push(k);
        }
    }

    return top_order;
}

/*
 * - Counts number of paths between all pairs (i, t)
 * - Maps each valid pair to a truck number
 * - Groups pairs by truck number
 */
vector<vector<pair<int,int>>> solve(const input_data info) {
    // Matrix to store number of total paths from each intersection to all others
    vector<vector<int>> total_paths(info.num_inter + 1, vector<int>(info.num_inter + 1, 0));

    // Result: routes grouped by truck number
    vector<vector<pair<int,int>>> truck_routes(info.truck_max - info.truck_min + 1);

    // Topological order of the graph
    vector<int> top_order = getTopologicalOrder(info);

    // Auxiliary vector to count paths from a fixed intersection
    vector<int> paths_a_To_b(info.num_inter + 1, 0);

    // For each starting intersection i
    for (int i = 1; i <= info.num_inter; i++) {
        fill(paths_a_To_b.begin(), paths_a_To_b.end(), 0);
        paths_a_To_b[i] = 1;  // One path from i to itself

        // Dynamic programming over topological order
        for (int j : top_order) {
            if (paths_a_To_b[j] == 0) continue;
            for (int k : info.paths[j]) {
                paths_a_To_b[k] += paths_a_To_b[j];
                // Modulo to limit values
                if (paths_a_To_b[k] > info.total_trucks)
                    paths_a_To_b[k] -= info.total_trucks;
            }
        }

        // Store valid paths and assign trucks
        for (int t = 1; t <= info.num_inter; t++) {
            if (i == t || paths_a_To_b[t] == 0) continue;

            total_paths[i][t] = paths_a_To_b[t];

            int truck_num = calculateTruckToPath(info.total_trucks, paths_a_To_b[t]);

            // Only consider trucks in valid range
            if (truck_num >= info.truck_min && truck_num <= info.truck_max) {
                truck_routes[truck_num - info.truck_min].emplace_back(i, t);
            }
        }
    }
    return truck_routes;
}

/*
 * Prints the result grouped by truck number.
 */
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

/*
 * Reads input, solves problem, prints results.
 */
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    const input_data info = readInput();

    vector<vector<pair<int,int>>> truck_routes = solve(info);

    printData(info, truck_routes);

    return 0;
}
