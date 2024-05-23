#include <vector>
#include <iostream>
using namespace std;

class AdjacencyMatrix {
    private:
        vector<bool> adj;
        int n;
    public:
        AdjacencyMatrix(int _n) 
            : n {_n} 
            , adj {vector<bool>(_n*_n, 0)}
        {}
        void addEdge(int source, int target) {
            this->adj[this->n * source + target] = true;
        }
        void removeEdge(int source, int target) {
            this->adj[this->n * source + target] = false;
        }
        bool getEdge(int source, int target) {
            return this->adj[this->n * source + target];
        }
        // bool operator[][] (int x, int y){
        //     return this.ad
        // }
};