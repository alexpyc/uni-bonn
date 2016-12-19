#include <iostream>
#include <fstream>
#include <cstdlib>

enum Color { WHITE, GREY, BLACK };
enum EdgeType { TREE, BACK, FORWARD, CROSS };
int t, n;

struct Vertex {
    bool* edge;
    EdgeType* type;
    Color color;
    Vertex* predecessor;
    int id, d, f;
};

void printEinfacherKrei(Vertex* v, Vertex* u) {
    do {
        std::cout << u->id << ' ';
        u = u->predecessor;
    } while (u != v);
    std::cout << std::endl;
};

void dfsVisit(Vertex* vertices, Vertex* curr) {
    t++;
    curr->d = t;
    curr->color = GREY;
    for(int i = 0; i < n; i++) {
        if(curr->edge[i]) {
            switch(vertices[i].color) {
                case WHITE:
                    curr->type[i] = TREE;
                    vertices[i].predecessor = curr;
                    dfsVisit(vertices, &vertices[i]);
                    break;
                case GREY:
                    curr->type[i] = BACK;
                    printEinfacherKrei(&vertices[i], curr);
                    break;
                default:
                    if(curr->d < vertices[i].d) {
                        curr->type[i] = FORWARD;
                    } else {
                        curr->type[i] = CROSS;
                    }
            }
        }
    }
    curr->color = BLACK;
    t++;
    curr->f = t;
};

void dfs(Vertex* vertices) {
    t = 0;
    for (int i = 0; i < n; i++) {
        if(vertices[i].color == WHITE) {
            dfsVisit(vertices, &vertices[i]);
        }
    }
};

int main() {
    std::string filename;
    std::cout << "Bitte geben Sie den Name der Datei: ";
    std::cin >> filename;
    
    std::ifstream fin;
    fin.open(filename);
    if(fin.fail()) {
        exit(1);
    }
    
    fin >> n;
    Vertex* vertices = new Vertex[n];
    for (int i = 0; i < n; i++) {
        vertices[i].edge = new bool[n];
        for (int j = 0; j < n; j++) {
            vertices[i].edge[j] = false;
        }
        vertices[i].type = new EdgeType[n];
        vertices[i].color = WHITE;
        vertices[i].predecessor = NULL;
        vertices[i].id = i;
        vertices[i].d = -1;
        vertices[i].f = -1;
    }
    
    int u, v;
    while(!fin.eof()) {
        fin >> u >> v;
        vertices[u].edge[v] = true;
    }
    
    fin.close();
    
    dfs(vertices);
    
    return 0;
}
