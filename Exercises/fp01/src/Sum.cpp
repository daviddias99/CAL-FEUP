/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <cstring>
#include <fstream>


void showArray(int* array, int size){


    cout << "[";

    for(int i = 0; i < size;i++){

        cout << array[i];

        if( i != size - 1)
            cout << ",";

    }

    cout << "]" << endl;
}


string calcSum(int* sequence, int size)
{

	int bestSum = -1;
	int bestIndex = 0;
	int* currSum =(int*) malloc(size* sizeof(int));
	string result;

	memset(currSum,0,sizeof(int) * size);

	for(int m = 0; m < size; m++) {

        for (int i = 0; i < size - m; i++) {

            currSum[i] += sequence[i + m];

            if (currSum[i] < bestSum || i == 0) {

                bestSum = currSum[i];
                bestIndex = i;
            }
        }
        result += to_string(bestSum) + ',' + to_string(bestIndex) + ';';
    }

	free(currSum);
    return result;

}



auto calculateTime1k(int* sequence, int size){


    int result = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for(int j = 0; j < 1000;j++){

        auto startGen = std::chrono::high_resolution_clock::now();

        for(int i = 0; i < size; i++)
            sequence[i] = random()%(size*10)+1;

        auto finishGen = std::chrono::high_resolution_clock::now();
        auto miliGen = chrono::duration_cast<chrono::milliseconds>(finishGen - startGen).count();
        result -= miliGen;

        calcSum(sequence,size);

    }


    auto finish = std::chrono::high_resolution_clock::now();
    auto miliTotal = chrono::duration_cast<chrono::milliseconds>(finish - start).count();

    result += miliTotal;

    return result;
}


void testSum(){

    srand(time(NULL));

    ofstream destFile;
    destFile.open("sum_statistics.csv");


    for(size_t n = 10; n <= 500; n += 10){


        int* sequence = (int*) malloc(n * sizeof(int));

        auto timeSpent = calculateTime1k(sequence,n);

        destFile << n << "," << timeSpent << endl;

        free(sequence);
    }

    destFile.close();
}