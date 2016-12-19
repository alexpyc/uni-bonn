#include <iostream>
#include <fstream>

int ordnung;

struct Node {
    int n;
    bool leaf;
    int* key;
    Node* parent;
    Node** child;
};

void test(Node* v) {
    std::cout << v->n;
    if (!v->leaf) {
        for (int i = 0; i <= v->n; i++) {
            if (v->child[i] != NULL) {
                test(v->child[i]);
            }
        }
    }
}

void print(Node* v) {
    std::cout << "( ";
    for (int i = 0; i < v->n; i++) {
        std::cout << v->key[i] << ' ';
    }
    std::cout << ')';
    for (int i = 0; i <= v->n; i++) {
        if (v->child[i] != NULL) {
            print(v->child[i]);
        }
    }
}

Node* createNode() {
    Node* v = new Node;
    v->n = 0;
    v->leaf = false;
    v->key = new int[2*ordnung-1];
    for (int i = 0; i < 2*ordnung-1; i++) v->key[i] = 0;
    v->parent = NULL;
    v->child = new Node*[2*ordnung];
    for (int i = 0; i < 2*ordnung; i++) v->child[i] = NULL;
    return v;
}

//NULL = found
Node* search(Node* v, int k) {
    if (v->leaf) return v;
    int i = 0;
    while (i < v->n && k > v->key[i]) i++;
    if (i < v->n && k == v->key[i]) return NULL;
    else return search(v->child[i], k);
};

Node* search2(Node* v, int k) {
    if (v == NULL) return NULL;
    int i = 0;
    while (i < v->n && k > v->key[i]) i++;
    if (i < v->n && k == v->key[i]) return v;
    else return search2(v->child[i], k);
};

int insertNonfull(Node* v, int k) {
    int i = v->n - 1;
    while (i >= 0 && k < v->key[i]) {
        v->key[i+1] = v->key[i];
        v->child[i+2] = v->child[i+1];
        i--;
    }
    v->key[i+1] = k;
    v->n++;
    return i+2;
};

void splitChild(Node* v) {
    Node* parent = v->parent;
    Node* w = createNode();
    if (parent == NULL) {
        parent = createNode();
        parent->child[0] = v;
        v->parent = parent;
    }
    if (parent->n == 2*ordnung-1) {
        splitChild(parent);
        parent = v->parent;
    }
    w->n = ordnung-1;
    w->leaf = v->leaf;
    w->parent = parent;
    for (int i = 0; i < ordnung-1; i++) {
        w->key[i] = v->key[i+ordnung];
        if (!v->leaf) {
            w->child[i] = v->child[i+ordnung];
            w->child[i]->parent = w;
        }
    }
    if (!v->leaf) {
        w->child[ordnung-1] = v->child[2*ordnung-1];
        w->child[ordnung-1]->parent = w;
    }
    v->n = ordnung-1;
    int j = insertNonfull(parent, v->key[ordnung-1]);
    parent->child[j] = w;
};

Node* insert(Node* v, int k) {
    if (v->n < 2*ordnung-1) {
        insertNonfull(v, k);
        while (v->parent != NULL) {
            v = v->parent;
        }
        return v;
    } else {
        splitChild(v);
        while (v->parent != NULL) {
            v = v->parent;
        }
        v = search(v, k);
        return insert(v, k);
    }
};

void rotation(Node* v) {
    int i = 0;
    bool flag = true;
    while (i < v->parent->n && v->parent->child[i] != v) {
        i++;
    }
    if (i > 0) {
        if (v->parent->child[i-1]->n > ordnung-1) {
            insertNonfull(v, v->parent->key[i-1]);
            v->parent->key[i-1] = v->parent->child[i-1]->key[v->parent->child[i-1]->n-1];
            v->child[0] = v->parent->child[i-1]->child[v->parent->child[i-1]->n];
            v->parent->child[i-1]->n--;
            flag = false;
        }
    }
    if (flag && i <= v->parent->n-1) {
        if (v->parent->child[i+1]->n > ordnung-1) {
            v->key[v->n] = v->parent->key[i];
            v->n++;
            v->child[v->n] = v->parent->child[i+1]->child[0];
            v->parent->key[i] = v->parent->child[i+1]->key[0];
            for (int j = 1; j < v->parent->child[i+1]->n; j++) {
                v->parent->child[i+1]->key[j-1] = v->parent->child[i+1]->key[j];
                v->parent->child[i+1]->child[j-1] = v->parent->child[i+1]->child[j];
            }
            v->parent->child[i+1]->child[v->parent->child[i+1]->n-1] = v->parent->child[i+1]->child[v->parent->child[i+1]->n];
            v->parent->child[i+1]->n--;
            flag = false;
        }
    }
    if (flag) {
        if (i > 0) {
            v->parent->child[i-1]->key[v->parent->child[i-1]->n] = v->parent->key[i-1];
            v->parent->child[i-1]->n++;
            for (int j = 0; j < v->n; j++) {
                v->parent->child[i-1]->key[v->parent->child[i-1]->n+j+1] = v->key[j];
                v->parent->child[i-1]->n++;
            }
            v->parent->child[i-1]->child[v->parent->child[i-1]->n] = v->child[v->n];
            for (int j = i-1; j < v->parent->n; j++) {
                v->parent->key[i-1] = v->parent->key[i];
                v->parent->child[i] = v->parent->child[i+1];
            }
            v->parent->n--;
            if (v->parent->n == 0  && v->parent->parent == NULL) {
                v->parent->child[i-1]->parent = NULL;
            }
        } else {
            v->key[v->n] = v->parent->key[i];
            v->n++;
            for (int j = 0; j < v->parent->child[i+1]->n; j++) {
                v->key[v->n] = v->parent->child[i+1]->key[j];
                v->n++;
            }
            for (int j = i; j < v->parent->n; j++) {
                v->parent->key[j] = v->parent->key[j+1];
                v->parent->child[j+1] = v->parent->child[j+2];
            }
            v->parent->n--;
            if (v->parent->n == 0 && v->parent->parent == NULL) {
                v->parent = NULL;
            }
        }
    }
};

Node* remove(Node* v, int k) {
    Node* temp;
    if (v->leaf) {
        for (int i = 0; i < v->n; i++) {
            if (v->key[i] > k) {
                v->key[i-1] = v->key[i];
            }
        }
        v->n--;
        temp = v;
    } else {
        int i = 0;
        while (i < v->n && k != v->key[i]) i++;
        temp = v->child[i];
        while (!temp->leaf) {
            temp = temp->child[temp->n];
        }
        v->key[i] = temp->key[temp->n-1];
        temp->n--;
    }
    while (temp->parent != NULL && temp->n < ordnung-1) {
        rotation(temp);
        if (temp->parent != NULL) {
            if (temp->parent->n == 0 && temp->parent->parent == NULL) {
                temp = temp->parent->child[0];
            } else {
                temp = temp->parent;
            }
        }
    }
    while (temp->parent != NULL) temp = temp->parent;
    return temp;
};

int main(int argc, const char * argv[]) {

    std::ifstream fin;

    std::string filename;
    std::cin >> filename;

    fin.open(filename);
    if (fin.fail()) exit(1);

    fin >> ordnung;

    Node* root = createNode();
    root->leaf = true;
    Node* result;
    char symbol;
    int input;

    while (!fin.eof()) {
        fin >> symbol >> input;
        if (symbol == '+') {
            result = search(root, input);
            if (result) {
                root = insert(result, input);
            }
        } else {
            result = search2(root, input);
            if (result) {
                root = remove(result, input);
            }
        }

        print(root);
        std::cout << std::endl;
    }

    test(root);
    std::cout << std::endl;

    fin.close();

    return 0;
}
