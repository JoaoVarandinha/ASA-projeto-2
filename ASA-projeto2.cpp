#include <iostream>
#include <vector>

using namespace std;

void readInput(int& N, int& M, int& m1, int& m2, int& K, vector<pair<int, int>>& paths) {
    //Read number of intersections, number of trucks, range of truck numbers and number of paths
    cin >> N >> M >> m1 >> m2 >> K;

    //Read guided paths between intersections
    for(int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;
        paths.push_back({a, b});
    }

}

vector<vector<int>> buildGraph(int N, const vector<pair<int, int>>& paths) {
   vector<vector<int>> graph(N+1);

   for(const auto& path : paths) {
        int origin = path.first;
        int destination = path.second;

        graph[origin].push_back(destination);
   }

   return graph;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /*
    N: number of intersections
    M: number of trucks
    m1, m2: range of truck numbers
    K: number of paths
    paths: vector of guided paths between intersections
    */
    int N, M, m1, m2, K;
    vector<pair<int, int>> paths;

    readInput(N, M, m1, m2, K, paths);

}