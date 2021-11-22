#include <fstream>
using namespace std;

#include "SortingAlgorithms.h"
#include "DataGenerator.h"

/*
Data orders:
 - 0 means Randomize
 - 1 means Sorted
 - 2 means Reverse
 - 3 means Nearly Sorted
*/

static int dataOrders[4] = {0, 1, 2, 3};
static int dataSizes[6] = {10000, 30000, 50000, 100000, 300000, 500000};

string getOrder(int i) {
    switch(i) {
        case 0:
            return "Randomize";
        case 1:
            return "Sorted";
        case 2:
            return "Reverse";
        case 3:
            return "Nearly sorted";
        default:
            return "";
            break;
    }
}

int main() {
    int *array = new int[500000];

    ofstream out;
    out.open("result.csv");

    out << "algorithm,data order,data size,used time (milisecs),comparisons\n";

    for (int order = 0; order < 4; order++) {
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "selection sort" << "," << dataOrder << "," << dataSize << ",";
            out << SelectionSort(array, dataSize) << ",";
            GenerateData(array, dataSize, order);
            out << SelectionSortCountCompare(array, dataSize) << "\n"; 
            cout << "Selection Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "insertion sort" << "," << dataOrder << "," << dataSize << ",";
            out << BinaryInsertionSort(array, dataSize) << ",";
            GenerateData(array, dataSize, order);
            out << BinaryInsertionSortCountCompare(array, dataSize) << "\n"; 
            cout << "Insertion Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "bubble sort" << "," << dataOrder << "," << dataSize << ",";
            out << BubbleSort(array, dataSize) << ",";
            GenerateData(array, dataSize, order);
            out << BubbleSortCountCompare(array, dataSize) << "\n"; 
            cout << "Bubble Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "shaker sort" << "," << dataOrder << "," << dataSize << ",";
            out << ShakerSort(array, dataSize) << ",";
            GenerateData(array, dataSize, order);
            out << ShakerSortCountCompare(array, dataSize) << "\n"; 
            cout << "Shaker Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "shell sort" << "," << dataOrder << "," << dataSize << ",";
            out << ShellSort(array, dataSize) << ",";
            GenerateData(array, dataSize, order);
            out << ShellSortCountCompare(array, dataSize) << "\n"; 
            cout << "Shell Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "heap sort" << "," << dataOrder << "," << dataSize << ",";
            out << HeapSort(array, dataSize) << ",";
            GenerateData(array, dataSize, order);
            out << HeapSortCountCompare(array, dataSize) << "\n"; 
            cout << "Heap Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "merge sort" << "," << dataOrder << "," << dataSize << ",";
            out << MergeSortCalcTime(array, dataSize) << ",";
            GenerateData(array, dataSize, order);
            out << MergeSortCalcCompare(array, dataSize) << "\n"; 
            cout << "Merge Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "quick sort" << "," << dataOrder << "," << dataSize << ",";
            out << QuickSortCalcTime(array, dataSize) << ",";
            GenerateData(array, dataSize, order);
            out << QuickSortCalcCompare(array, dataSize) << "\n"; 
            cout << "Quick Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "counting sort" << "," << dataOrder << "," << dataSize << ",";
            out << CountingSortCalcTime(array, dataSize) << ",";
            GenerateData(array, dataSize, order);
            out << CountingSortCalcCompare(array, dataSize) << "\n"; 
            cout << "Counting Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "radix sort" << "," << dataOrder << "," << dataSize << ",";
            out << LSDRadixSortCalcTime(array, dataSize) << ",";
            GenerateData(array, dataSize, order);
            out << LSDRadixSortCalcCompare(array, dataSize) << "\n"; 
            cout << "Radix Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "flash sort" << "," << dataOrder << "," << dataSize << ",";
            out << FlashSortCalcTime(array, dataSize) << ",";
            GenerateData(array, dataSize, order);
            out << FlashSortCalcCompare(array, dataSize) << "\n"; 
            cout << "Flash Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
    }

    out.close();

    return 0;
}