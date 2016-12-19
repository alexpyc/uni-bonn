#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

int insertionSort(int* array, int n) {

    int number_of_comparison = 0;

    for (int i = 1; i < n; i++) {
        int j = i;
        number_of_comparison += 1;
        while (j >= 1 && array[j] > array[j-1]) {
            int temp = array[j];
            array[j] = array[j-1];
            array[j-1] = temp;
            j--;
            number_of_comparison += 1;
        }
    }

    return number_of_comparison;
};

int main(int argc, const char * argv[]) {

    std::srand((int)std::time(0));

    int minimum[500], maximum[500], average[500];

    for (int i = 0; i < 500; i++) {
        minimum[i] = 100000;
        maximum[i] = 0;
        average[i] = 0;
    }

    int* array;

    for (int i = 1; i < 501; i++) {
        if (i % 100 == 0) std::cout << "Step: " << i << std::endl;
        int average_count = 0;
        for (int j = 0; j < i; j++) {
            array = new int[i];
            for (int k = 0; k < i; k++) {
                array[k] = std::rand() % 5000;
            }
            int number_of_comparison = insertionSort(array, i);
            if (number_of_comparison < minimum[i-1]) minimum[i-1] = number_of_comparison;
            if (number_of_comparison > maximum[i-1]) maximum[i-1] = number_of_comparison;
            average_count += number_of_comparison;
            delete [] array;
        }
        average[i-1] = average_count / i;
    }

    std::ofstream fout;
    fout.open("data.dat");

    if (fout.fail()) exit(1);

    fout << 'n' << '\t' << "minimum" << '\t' << "maximum" << '\t' << "average" << std::endl;

    for (int i = 0; i < 500; i++) {
        fout << i + 1 << '\t' << minimum[i] << '\t' << maximum[i] << '\t' << average[i] << std::endl;
    }

    return 0;
}
