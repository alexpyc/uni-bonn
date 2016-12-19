#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

int max(int *a, int n) {
    int max = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }

    return max;
};

int sum(int *a, int n) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += a[i];
    }

    return sum;
};

void eInsertionSort(double *e, int *p, int *w, int n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && e[j] > e[j-1]) {
            double temp = e[j];
            e[j] = e[j-1];
            e[j-1] = temp;
            int tempI = p[j];
            p[j] = p[j-1];
            p[j-1] = tempI;
            tempI = w[j];
            w[j] = w[j-1];
            w[j-1] = tempI;
            j--;
        }
    }
};

int intGreedyKP(int *p, int *w, int t, int n) {
    double *e = new double[n];
    for (int i = 0; i < n; i++) {
        e[i] = p[i]*1.0 / w[i]*1.0;
    }
    eInsertionSort(e, p, w, n);
    int nutzenwerte = 0;
    int i = 0;
    while (t - w[i] >= 0) {
        nutzenwerte += p[i];
        t -= w[i];
        i++;
    }

    delete []e;

    return nutzenwerte;
};

int approxKP(int *p, int *w, int t, int n) {
    int greedy = intGreedyKP(p, w, t, n);
    int max_nutze = max(p, n);
    if (greedy > max_nutze) return greedy;
    else return max_nutze;
};

int dynKP(int *p, int *w, int t, int n) {
    int **tabelle = new int*[n];
    int W = max(w, n);
    for (int i = 0; i < n; i++) {
        tabelle[i] = new int[n*W];
    }
    for (int i = 0; i < n*W-1; i++) {
        if (i < w[0]-1) {
            tabelle[0][i] = 0;
        } else {
            tabelle[0][i] = p[0];
        }
    }
    for (int i = 1; i <= n-1; i++) {
        for (int j = 0; j < n*W-1; j++) {
            int without = tabelle[i-1][j];
            int with = 0;
            if (j - w[i]+1> 0) with = tabelle[i-1][j-w[i]+1] + p[i];
            else if (j - w[i]+1 == 0) with = p[i];

            if (without > with) {
                tabelle[i][j] = without;
            } else {
                tabelle[i][j] = with;
            }
        }
    }
    return tabelle[n-1][t-1];
};

int main(int argc, const char * argv[]) {

    std::srand((int)std::time(0));

    double minimal[99], maximal[99], durchschnittlich[99];

    for (int n = 2; n <= 100; n++) {
        if (n % 10 == 0) std::cout << "Step: " << n << std::endl;
        minimal[n-2] = 1;
        maximal[n-2] = 0;
        double durchschnitt = 0;
        for (int i = 0; i < 100; i++) {
            int *p = new int[n];
            int *w = new int[n];
            for (int j = 0; j < n; j++) {
                p[j] = std::rand() % 100 + 1;
                w[j] = std::rand() % 100 + 1;
            }
            int W = max(w, n);
            int summe = sum(w, n);
            int t = std::rand() % (summe-W) + W;
            int dp = dynKP(p, w, t, n);
            int ap = approxKP(p, w, t, n);
            double guete = dp*1.0/ap*1.0;
            if (guete < minimal[n-2]) minimal[n-2] = guete;
            if (guete > maximal[n-2]) maximal[n-2] = guete;
            durchschnitt += guete;
        }
        durchschnittlich[n-2] = durchschnitt / 100;
    }

    std::ofstream fout;
    fout.open("data.txt");

    if (fout.fail()) exit(1);

    fout << 'n' << '\t' << "minimal" << '\t' << "maximal" << '\t' << "durchschnittlich" << std::endl;

    for (int i = 0; i < 99; i++) {
        fout << i + 2 << '\t' << minimal[i] << '\t' << maximal[i] << '\t' << durchschnittlich[i] << std::endl;
    }

    fout.close();

    return 0;
}
