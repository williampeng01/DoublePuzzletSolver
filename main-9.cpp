#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <assert.h>
#include <queue>
using namespace std;

class Graph {
public:
    Graph() {};
    int n();
    void add_vertex();
    void add_edge(int a, int b);
    bool is_edge(int a, int b);
    list<int> shortest_path(int start, int end);
private:
    vector<list<int>> _v;
    void bfs(int start, vector<int> &parent);
};

int Graph::n() { return _v.size(); }

void Graph::add_vertex() { _v.push_back(list<int>()); }

void Graph::add_edge(int a, int b) {
    assert(a < n() && b < n());
    if (!is_edge(a, b)) {
        _v[a].push_front(b);
        _v[b].push_front(a);
    }
}

bool Graph::is_edge(int a, int b) {
    if (a >= n() || b >= n()) return false;
    for (auto e: _v[a]) if (e == b) return true;
    return false;
}

void Graph::bfs(int start, vector<int> &parent) {
    queue<int> vertex_num;
    vertex_num.push(start);
    parent[start] = start;
    while (!vertex_num.empty()) {
        int current = vertex_num.front();
        vertex_num.pop();
        for (auto e:_v[current]) {
            if(parent[e] == -1) {
                parent[e] = current; vertex_num.push(e);
            }
        }
    }
}

list<int> Graph::shortest_path(int start, int end) {
    vector<int> parent(n(),-1);
    bfs(start,parent);
    if (parent[end] == -1) {
        cout << "None";
        return list<int>();
    }
    list<int> ans;
    list<int>::iterator it;
    for(int v = end; v!=start; v=parent[v]) {ans.push_front(v);}
    ans.push_front(start); return ans;
}

class DoubletSolver {
public:
    DoubletSolver() {};
    void build_dict(string dict);
    void solve(string first_word, string last_word);
private:
    Graph graph;
    vector<string> dictionary;
    int intersections(string string1, string string2);
};

void DoubletSolver::build_dict(string d) {
    ifstream Input(d);
    string line;
    cout << "Building dictionary..." << "\n\n";
    while(getline(Input,line)){
        if(line.length() != 0){
            graph.add_vertex();
            dictionary.push_back(line);
        }
    }
    Input.close();
    string word1, word2;
    for( int i = 0; i < dictionary.size(); i++) {
        word1 = dictionary[i];
        for( int j = i; j < dictionary.size(); j++) {
            word2 = dictionary[j];
            if (intersections(word1, word2) == 4) {
                graph.add_edge(i,j);
            }
        }
    }
}

void DoubletSolver::solve(string first_word, string last_word) {
    int index1, index2;
    for (int i = 0; i < dictionary.size(); i++) {
        if (first_word == dictionary[i]) { index1 = i; }
    }
    for (int i = 0; i < dictionary.size(); i++) {
        if (last_word == dictionary[i]) { index2 = i; }
    }
    cout << first_word << " -> " << last_word << endl;
    list <int> answer = graph.shortest_path(index1, index2);
    list <int>::iterator it;
    for(it = answer.begin(); it!= answer.end(); it++) {
        cout << dictionary[*it] << " ";
    }
    cout << endl;
}

int DoubletSolver::intersections(string string1, string string2) {
    int matches = 0;
    for(int i=0; i < 5; i++) {
        if (string1[i] == string2[i]) { matches++; }
    }
    return matches;
}

int main() {
    DoubletSolver puzzle;
    puzzle.build_dict("dictionary.txt");
    puzzle.solve("black", "white");
    puzzle.solve("tears", "smile");
    puzzle.solve("small", "giant");
    puzzle.solve("stone", "money");
    puzzle.solve("angel", "devil");
    puzzle.solve("amino", "right");
    puzzle.solve("amigo", "signs");
    return 0;
}
