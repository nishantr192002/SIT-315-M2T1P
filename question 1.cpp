#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std::chrono;

const int SIZE_OF_MATRIX = 500;

// Function to initialize a matrix with random values
void initializeMatrixWithRandomValues(int matrix[][SIZE_OF_MATRIX])
{
    for (int i = 0; i < SIZE_OF_MATRIX; ++i)
        for (int j = 0; j < SIZE_OF_MATRIX; ++j)
            matrix[i][j] = rand() % 100;
}

// Function to perform matrix multiplication
void multiplyMatrices(const int matrix1[][SIZE_OF_MATRIX], const int matrix2[][SIZE_OF_MATRIX], int resultMatrix[][SIZE_OF_MATRIX])
{
    for (int i = 0; i < SIZE_OF_MATRIX; ++i)
    {
        for (int j = 0; j < SIZE_OF_MATRIX; ++j)
        {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < SIZE_OF_MATRIX; ++k)
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
        }
    }
}

int main()
{
    srand(time(nullptr));

    int matrix1[SIZE_OF_MATRIX][SIZE_OF_MATRIX];
    int matrix2[SIZE_OF_MATRIX][SIZE_OF_MATRIX];
    int resultMatrix[SIZE_OF_MATRIX][SIZE_OF_MATRIX];

    // Initialize matrices with random values
    initializeMatrixWithRandomValues(matrix1);
    initializeMatrixWithRandomValues(matrix2);

    auto startTime = high_resolution_clock::now();
    // Perform matrix multiplication
    multiplyMatrices(matrix1, matrix2, resultMatrix);
    auto stopTime = high_resolution_clock::now();

    // Calculate duration of multiplication
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    std::cout << "Matrix multiplication completed in: " << duration.count() << " microseconds" << std::endl;

    // Write result to file
    std::ofstream outputFile("Modified_Results.txt");
    for (int i = 0; i < SIZE_OF_MATRIX; ++i)
    {
        for (int j = 0; j < SIZE_OF_MATRIX; ++j)
            outputFile << resultMatrix[i][j] << "\t";
        outputFile << std::endl;
    }
    outputFile << "Execution time for multiplication: " << duration.count() << " microseconds";
    outputFile.close();

    return 0;
}
