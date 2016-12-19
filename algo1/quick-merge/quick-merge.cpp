//
//  main.cpp
//  quickSortAndMergeSort
//
//  Created by Chan Pui Yiu on 27.11.16.
//  Copyright © 2016 Chan Pui Yiu. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <chrono>

int partition(std::vector<int> &a, int l, int r) {
    int x = a[r];
    int i = l-1;
    for (int j = l; j < r; j++) {
        if (a[j] <= x) {
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    int temp = a[i+1];
    a[i+1] = a[r];
    a[r] = temp;
    return i+1;
};

void quickSort(std::vector<int> &a, int l, int r) {
    if (l < r) {
        int q = partition(a, l, r);
        quickSort(a, l, q-1);
        quickSort(a, q+1, r);
    }
};

void merge(std::vector<int> &vec, int head, int mid, int last) {
    unsigned int l_len = mid - head, r_len = last - mid;
    unsigned int *l = new unsigned int[l_len], *r = new unsigned int[r_len];
    
    for(int i = 0; i < l_len; i++) {
        l[i] = vec[head + i];
    }
    for(int i = 0; i < r_len; i++) {
        r[i] = vec[mid + i];
    }
    
    int l_index = 0, r_index = 0, counter = 0;
    
    for(int i = head; i < last; i++) {
        if(r_index == r_len || (l_index < l_len && l[l_index] < r[r_index])) {
            vec[i] = l[l_index];
            l_index++;
        } else {
            if(l_index < l_len) counter += l_len - l_index;
            vec[i] = r[r_index];
            r_index++;
        }
    }
    
    delete [] l;
    delete [] r;
}

void mergeSort(std::vector<int> &vec, int head, int last) {
    if(last - head > 1) {
        int mid = (head + last) / 2;
        mergeSort(vec, head, mid);
        mergeSort(vec, mid, last);
        merge(vec, head, mid, last);
    }
}

int main(int argc, const char * argv[]) {
    
    std::srand((int)std::time(0));
    
    unsigned long long quickAverage[500], mergeAverage[500];
    for (int i = 0; i < 500; i++) {
        quickAverage[i] = 0;
        mergeAverage[i] = 0;
    }
    std::vector<int> *quickVec, *mergeVec;
    
    for (int i = 1; i < 501; i++) {
        if (i % 20 == 0) std::cout << "Step: " << i << std::endl;
        
        for (int j = 0; j < i; j++) {
            quickVec = new std::vector<int>(i);
            mergeVec = new std::vector<int>(i);
            for (int k = 0; k < i; k++) {
                (*quickVec)[k] = std::rand() % 5000;
                (*mergeVec)[k] = (*quickVec)[k];
            }
            
            auto t1 = std::chrono::high_resolution_clock::now();
            quickSort((*quickVec), 0, i-1);
            auto t2 = std::chrono::high_resolution_clock::now();
            quickAverage[i - 1] += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            std::vector<int>().swap(*quickVec);
            
            t1 = std::chrono::high_resolution_clock::now();
            mergeSort((*mergeVec), 0, i);
            t2 = std::chrono::high_resolution_clock::now();
            std::vector<int>().swap(*mergeVec);
            mergeAverage[i - 1] += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            
        }
        quickAverage[i - 1] /= i;
        mergeAverage[i - 1] /= i;
    }
    
    std::ofstream fout;
    fout.open("data.dat");
    
    if (fout.fail()) exit(1);
    
    fout << 'n' << '\t' << "quickSort" << '\t' << "mergeSort" << std::endl;
    
    for (int i = 0; i < 500; i++) {
        fout << i + 1 << '\t' << quickAverage[i] << '\t' << mergeAverage[i] << std::endl;
    }
    
    return 0;
}

