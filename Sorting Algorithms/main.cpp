#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#include "SortingAlgorithms.h"
#include "DataGenerator.h"

void showHelp() {
    cout << "----------------------------------------\n\n";
    cout << "INSTRUCTION:\n";
    cout << "Command 1: main.exe -a [algorithm] [given input] [output parameter]\n";
    cout << "Command 2: main.exe -a [algorithm] [input size] [input order] [output parameter]\n";
    cout << "Command 3: main.exe -a [algorithm] [input size] [output parameter]\n";
    cout << "Command 4: main.exe -c [algorithm 1] [algorithm 2] [given input]\n";
    cout << "Command 5: main.exe -c [algorithm 1] [algorithm 2] [input size] [input order]\n";
    cout << "----------------------------------------\n\n";
    cout << "PARAMETERS MEANINGS:\n";
    cout << "-a: algorithm mode\n";
    cout << "-c: comparison mode\n";
    cout << "[algorithm]: name of algorithm, lowercase, words are linked by character '-'. Examples: selection-sort...\n";
    cout << "[input size]: number of elements, an integer less then or equal to 1,000,000.\n";
    cout << "[input order]:\n";
    cout << "\t -rand: randomized data\n";
    cout << "\t -nsorted: nearly sorted data\n";
    cout << "\t -sorted: sorted data\n";
    cout << "\t -rev: reverse sorted data\n";
    cout << "[given input]: path to input file. File format:\n";
    cout << "\t - 1st line: an integer n, number of element of input data\n";
    cout << "\t - 2nd line: n integers, seperated by a single space\n";
    cout << "[output parameter]:\n";
    cout << "\t -time: algorithm's running time\n";
    cout << "\t -comp: number of comparisons\n";
    cout << "\t -both: both time and number of comparisons\n";
    cout << "----------------------------------------\n\n";
}

const char* algorithms[] = {
    "selection-sort", "insertion-sort", "bubble-sort", "shaker-sort", "shell-sort",
    "heap-sort", "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"
};
const char* inputOrders[] = {"-rand", "-sorted", "-rev", "-nsorted"};
const char* inputOrderNames[] = {"randomize", "sorted", "reverse sorted", "nearly sorted"};
const char* outputParams[] = {"-time", "-comp", "-both"};

int isAlgorithm(char *flag) {
    for (int i = 0; i < 11; i++) {
        if (strcmp(algorithms[i], flag) == 0)
            return i;
    }
    return -1;
}

int isInputOrder(char *flag) {
    for (int i = 0; i < 4; i++) {
        if (strcmp(inputOrders[i], flag) == 0)
            return i;
    }
    return -1;
}

int isOutputParam(char *flag) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(outputParams[i], flag) == 0)
            return i;
        
    }
    return -1;
}

void copyArray(int *src, int *&dest, int n) {
    if (src != nullptr) {
        if (dest != nullptr)
            delete[] dest;
        dest = new int[n];
        for (int i = 0; i < n; i++)
            dest[i] = src[i];
    }
}

void writeArray(int *a, int n, FILE *pFile) {
    if (a != nullptr) {
        fprintf(pFile, "%d\n", n);
        for (int i = 0; i < n - 1; i++)
            fprintf(pFile, "%d ", a[i]);
        fprintf(pFile, "%d", a[n-1]);
    }
}

void readArray(int *&a, int &n, FILE *pFile) {
    if (pFile) {
        fscanf(pFile, "%d", &n);
        if (a == nullptr)
            delete[] a;
        a = new int[n];
        for (int i = 0; i < n; i++)
            fscanf(pFile, "%d", &a[i]);
    }
}

long long sortGetRunTime(int *a, int n, int algoCode) {
    long long result;
    switch (algoCode) {
        case 0: {
            result = SelectionSort(a, n);
            break;
        }
        case 1: {
            result = BinaryInsertionSort(a, n);
            break;
        }
        case 2: {
            result = BubbleSort(a, n);
            break;
        }
        case 3: {
            result = ShakerSort(a, n);
            break;
        }
        case 4: {
            result = ShellSort(a, n);
            break;
        }
        case 5: {
            result = HeapSort(a, n);
            break;
        }
        case 6: {
            result = MergeSortCalcTime(a, n);
            break;
        }
        case 7: {
            result = QuickSortCalcTime(a, n);
            break;
        }
        case 8: {
            result = CountingSortCalcTime(a, n);
            break;
        }
        case 9: {
            result = LSDRadixSortCalcTime(a, n);
            break;
        }
        case 10: {
            result = FlashSortCalcTime(a, n);
            break;
        }
        default: {
            result = -1;
            break;
        }
    }
    return result;
}

long long sortGetComparison(int *a, int n, int algoCode) {
    long long result;
    switch (algoCode) {
        case 0: {
            result = SelectionSortCountCompare(a, n);
            break;
        }
        case 1: {
            result = BinaryInsertionSortCountCompare(a, n);
            break;
        }
        case 2: {
            result = BubbleSortCountCompare(a, n);
            break;
        }
        case 3: {
            result = ShakerSortCountCompare(a, n);
            break;
        }
        case 4: {
            result = ShellSortCountCompare(a, n);
            break;
        }
        case 5: {
            result = HeapSortCountCompare(a, n);
            break;
        }
        case 6: {
            result = MergeSortCalcCompare(a, n);
            break;
        }
        case 7: {
            result = QuickSortCalcCompare(a, n);
            break;
        }
        case 8: {
            result = CountingSortCalcCompare(a, n);
            break;
        }
        case 9: {
            result = LSDRadixSortCalcCompare(a, n);
            break;
        }
        case 10: {
            result = FlashSortCalcCompare(a, n);
            break;
        }
        default: {
            result = -1;
            break;
        }
    }
    return result;
}

void runCommand1(int algoCode, char* inputFile, int outputParamCode) {
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: ";
    puts(algorithms[algoCode]);
    cout << "Input file: ";
    puts(inputFile);
    
    FILE *pInput = fopen(inputFile, "r");
    
    // check file exist
    if (pInput == NULL)
        return;

    // read input array
    int n;
    int *a = nullptr;
    readArray(a, n, pInput);
    cout << "Input size: " << n << endl;
    cout << "----------------------------\n";

    FILE *pOutput = fopen("output.txt", "w");

    if (outputParamCode == 0) {
        cout << "Running time: " << sortGetRunTime(a, n, algoCode) << " milisecs\n";
    }
    else if (outputParamCode == 1) {
        cout << "Comparisons: " << sortGetComparison(a, n, algoCode) << endl;
    }
    else if (outputParamCode == 2) {
        int *temp = nullptr;
        copyArray(a, temp, n);

        cout << "Running time: " << sortGetRunTime(a, n, algoCode) << " milisecs\n";
        cout << "Comparisons: " << sortGetComparison(temp, n, algoCode) << endl;

        delete[] temp;
    }

    writeArray(a, n, pOutput);

    // free memory
    if (a != nullptr)
        delete[] a;
    
    fclose(pInput);
    fclose(pOutput);
}

void runCommand2(int algoCode, int inputSize, int inputOrderCode, int outputParamCode) {
    cout << "ALGORITHM MODE\n";
    printf("Algorithm: %s\n", algorithms[algoCode]);
    printf("Input size: %d\n", inputSize);
    printf("Input order: ");
    puts(inputOrderNames[inputOrderCode]);
    cout << "---------------------------\n";

    int n = inputSize;
    int *a = new int[n];
    GenerateData(a, n, inputOrderCode);
    FILE *pIn = fopen("input.txt", "w");
    writeArray(a, n, pIn);
    fclose(pIn);

    if (outputParamCode == 0) {
        cout << "Running time: " << sortGetRunTime(a, n, algoCode) << " milisecs\n";
    }
    else if (outputParamCode == 1) {
        cout << "Comparisons: " << sortGetComparison(a, n, algoCode) << endl;
    }
    else if (outputParamCode == 2) {
        int *temp = nullptr;
        copyArray(a, temp, n);

        cout << "Running time: " << sortGetRunTime(a, n, algoCode) << " milisecs\n";
        cout << "Comparisons: " << sortGetComparison(temp, n, algoCode) << endl;

        delete[] temp;
    }

    FILE *pOutput = fopen("output.txt", "w");
    writeArray(a, n, pOutput);
    fclose(pOutput);

    delete[] a;

}

void runCommand3(int algoCode, int inputSize, int outputParamCode) {
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: ";
    puts(algorithms[algoCode]);
    cout << "Input size: " << inputSize << endl;

    int *a = new int[inputSize];
    int n = inputSize;

    FILE *pOutput = fopen("output.txt", "w");

    int order[] = {0, 3, 1, 2};
    char inputName[] = "input_";
    char outputName[] = "output_";

    char *buff = new char[10];

    for (int i = 0; i < 4; i++) {
        int realOrder = order[i];
        cout << "\nInput order: ";
        puts(inputOrderNames[realOrder]);
        cout << "----------------------------\n";
        GenerateData(a, n, realOrder);

        char inputFileName[20] = {'\0'};
        strcpy(inputFileName, inputName);
        strcat(inputFileName, itoa(i+1, buff, 10));
        strcat(inputFileName, ".txt");
        FILE * input = fopen(inputFileName, "w");
        writeArray(a, n, input);
        fclose(input);

        if (outputParamCode == 0) {
        cout << "Running time: " << sortGetRunTime(a, n, algoCode) << " milisecs\n";
        }
        else if (outputParamCode == 1) {
            cout << "Comparisons: " << sortGetComparison(a, n, algoCode) << endl;
        }
        else if (outputParamCode == 2) {
            int *temp = nullptr;
            copyArray(a, temp, n);

            cout << "Running time: " << sortGetRunTime(a, n, algoCode) << " milisecs\n";
            cout << "Comparisons: " << sortGetComparison(temp, n, algoCode) << endl;

            delete[] temp;
        }

        char outputFileName[20] = {'\0'};
        strcpy(outputFileName, outputName);
        strcat(outputFileName, itoa(i+1, buff, 10));
        strcat(outputFileName, ".txt");
        FILE *out = fopen(outputFileName, "w");
        writeArray(a, n, out);
        fclose(out);
    }

    delete[] a;
    delete[] buff;
    fclose(pOutput);
}

void runCommand4(int algoCode1, int algoCode2, char *inputFile) {
    cout << "COMPARE MODE\n";
    printf("Algorithm: %s | %s\n", algorithms[algoCode1], algorithms[algoCode2]);
    printf("Input file: %s\n", inputFile);

    FILE *pFile = fopen(inputFile, "r");

    if (pFile == NULL)
        return;

    int n, *a = nullptr;
    readArray(a, n, pFile);
    printf("Input size: %d\n", n);
    cout << "--------------------------\n";

    int *temp = nullptr;
    copyArray(a, temp, n);

    int *temp1 = nullptr;
    copyArray(a, temp1, n);

    int *temp2 = nullptr;
    copyArray(a, temp2, n);

    printf("Running time: %lld milisecs | %lld milisecs\n", sortGetRunTime(a, n, algoCode1), sortGetRunTime(temp, n, algoCode2));
    printf("Comparisons: %lld | %lld\n", sortGetComparison(temp1, n, algoCode1), sortGetComparison(temp2, n, algoCode2));

    FILE *pOut = fopen("output.txt", "w");
    writeArray(a, n, pOut);
    fclose(pOut);

    delete[] a;
    delete[] temp;
    delete[] temp1;
    delete[] temp2;
    fclose(pFile);
}

void runCommand5(int algoCode1, int algoCode2, int inputSize, int inputOrderCode) {
    cout << "COMPARE MODE\n";
    printf("Algorithm: %s | %s\n", algorithms[algoCode1], algorithms[algoCode2]);
    printf("Input size: %d\n", inputSize);
    printf("Input order: %s\n", inputOrderNames[inputOrderCode]);
    cout << "-----------------------\n";

    int n = inputSize;
    int *a = new int[n];
    GenerateData(a, n, inputOrderCode);

    FILE *pIn = fopen("input.txt", "w");
    writeArray(a, n, pIn);
    fclose(pIn);

    int *temp = nullptr;
    copyArray(a, temp, n);

    int *temp1 = nullptr;
    copyArray(a, temp1, n);

    int *temp2 = nullptr;
    copyArray(a, temp2, n);

    printf("Running time: %lld milisecs | %lld milisecs\n", sortGetRunTime(a, n, algoCode1), sortGetRunTime(temp, n, algoCode2));
    printf("Comparisons: %lld | %lld\n", sortGetComparison(temp1, n, algoCode1), sortGetComparison(temp2, n, algoCode2));

    FILE *pOut = fopen("output.txt", "w");
    writeArray(a, n, pOut);
    fclose(pOut);

    delete[] a;
    delete[] temp;
    delete[] temp1;
    delete[] temp2;
}

int main(int argc, char** argv) {
    switch (argc) {
        case 2: {
            //  show help
            if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
                showHelp();
            break;
        }
        case 5: {
            // command 1, 3 and 4
            if (strcmp(argv[1], "-c") == 0)
                runCommand4(isAlgorithm(argv[2]), isAlgorithm(argv[3]), argv[4]);
            else if (atoi(argv[3]) == 0)
                runCommand1(isAlgorithm(argv[2]), argv[3], isOutputParam(argv[4]));
            else
                runCommand3(isAlgorithm(argv[2]), atoi(argv[3]), isOutputParam(argv[4]));
            break;
        }
        case 6: {
            // command 2 and 5
            if (strcmp(argv[1], "-a") == 0)
                runCommand2(isAlgorithm(argv[2]), atoi(argv[3]), isInputOrder(argv[4]), isOutputParam(argv[5]));
            else if (strcmp(argv[1], "-c") == 0)
                runCommand5(isAlgorithm(argv[2]), isAlgorithm(argv[3]), atoi(argv[4]), isInputOrder(argv[5]));
            break;
        }
        default:
            break;
    }
}