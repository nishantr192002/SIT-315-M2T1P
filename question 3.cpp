#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <pthread.h>

using namespace std::chrono;

const int MATRIX_SIZE = 500;
#define MAX_THREADS 16

int matrixA[MATRIX_SIZE][MATRIX_SIZE];
int matrixB[MATRIX_SIZE][MATRIX_SIZE];
int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];
int threadCounter = 0;
int partitionSize = MATRIX_SIZE / MAX_THREADS;

void fillMatrixWithRandomValues(int matrix[][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void *multiplyMatrices(void *args) {
    int threadID = threadCounter++;

    for (int i = threadID * partitionSize; i < (threadID + 1) * partitionSize; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return NULL;
}

int main() {
    srand(time(nullptr));

    fillMatrixWithRandomValues(matrixA);
    fillMatrixWithRandomValues(matrixB);

    auto start = high_resolution_clock::now();

    pthread_t threadArray[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_create(&threadArray[i], NULL, &multiplyMatrices, NULL);
    }

    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_join(threadArray[i], NULL);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    printf("Execution time: %d microseconds", duration.count());

    std::ofstream outputFile("Modified_PThread_Results.txt");
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            outputFile << resultMatrix[i][j] << "\t";
        }
        outputFile << std::endl;
    }
    outputFile << "Execution time: " << duration.count() << " microseconds";
    outputFile.close();

    return 0;
}
