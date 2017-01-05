#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int n;
bool **graph, *besucht;

int rekursion(int index) {
  if(besucht[index]) {
    return 0;
  } else {
    besucht[index] = true;
    int summe = 1;
    for(int i = 0; i < n; i++) {
      if(graph[index][i]) {
        summe += rekursion(i);
      }
    }
    return summe;
  }
};

int main() {
  cout << "Der Name der Datei: ";
  string filename;
  cin >> filename;

  ifstream fin;
  fin.open(filename);
  if(fin.fail()) {
    exit(1);
  }

  fin >> n;

  graph = new bool* [n];
  besucht = new bool [n];
  for(int i = 0; i < n; i++) {
    graph[i] = new bool [n];
    besucht[i] = false;
    for(int j = 0; j < n; j++) {
      graph[i][j] = false;
    }
  }

  while(!fin.eof()) {
    int u, v;
    fin >> u >> v;
    graph[v][u] = graph[u][v] = true;
  }

  int zaehler = 0;
  for(int i = 0; i < n; i++) {
    if(!besucht[i]) {
      zaehler++;
      cout << rekursion(i) << endl;
    }
  }
  cout << zaehler << endl;

  return 0;
}
