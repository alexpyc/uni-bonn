//
//  main.cpp
//  sortAlgoRunningTime
//
//  Created by Chan Pui Yiu on 30.10.16.
//  Copyright © 2016 Chan Pui Yiu. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <chrono>

void insertionSort(std::vector<int> &array, int n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j >= 1 && array[j] < array[j-1]) {
            int temp = array[j];
            array[j] = array[j-1];
            array[j-1] = temp;
            j--;
        }
    }
};

void mergeInversionSplitCount(std::vector<int> &vec, int head, int mid, int last) {
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
        mergeInversionSplitCount(vec, head, mid, last);
    }
}

int main(int argc, const char * argv[]) {
    
    std::srand((int)std::time(0));
    
    unsigned long long insertionAverage[500], mergeAverage[500];
    for (int i = 0; i < 500; i++) {
        insertionAverage[i] = 0;
        mergeAverage[i] = 0;
    }
    std::vector<int> *insertionVec, *mergeVec;
    
    for (int i = 1; i < 501; i++) {
        if (i % 20 == 0) std::cout << "Step: " << i << std::endl;
        
        for (int j = 0; j < i; j++) {
            insertionVec = new std::vector<int>(i);
            mergeVec = new std::vector<int>(i);
            for (int k = 0; k < i; k++) {
                (*insertionVec)[k] = std::rand() % 5000;
                (*mergeVec)[k] = (*insertionVec)[k];
            }
            
            auto t1 = std::chrono::high_resolution_clock::now();
            insertionSort((*insertionVec), i);
            auto t2 = std::chrono::high_resolution_clock::now();
            insertionAverage[i - 1] += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            std::vector<int>().swap(*insertionVec);
            
            t1 = std::chrono::high_resolution_clock::now();
            mergeSort((*mergeVec), 0, i);
            t2 = std::chrono::high_resolution_clock::now();
            std::vector<int>().swap(*mergeVec);
            mergeAverage[i - 1] += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

        }
        insertionAverage[i - 1] /= i;
        mergeAverage[i - 1] /= i;
    }
    
    std::ofstream fout;
    fout.open("data.dat");
    
    if (fout.fail()) exit(1);
    
    fout << 'n' << '\t' << "insertionSort" << '\t' << "mergeSort" << std::endl;
    
    for (int i = 0; i < 500; i++) {
        fout << i + 1 << '\t' << insertionAverage[i] << '\t' << mergeAverage[i] << std::endl;
    }
    
    return 0;
}
