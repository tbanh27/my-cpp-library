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

    fstream out;
    out.open("result.txt", ios::out);

    cout << "STARTED...\n";

    for (int order = 0; order < 4; order++) {
        out << "##################################################################\n";
        /*for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "Selection Sort:\n";
            out << "Order: " << dataOrder << "\n";
            out << "Size: " << dataSize << endl;
            out << "Used Time: " << SelectionSort(array, dataSize) << " milisecs\n";
            GenerateData(array, dataSize, order);
            out << "Comparisons: " << SelectionSortCountCompare(array, dataSize) << "\n";
            cout << "Selection Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "\n\nInsertion Sort:\n";
            out << "Order: " << dataOrder << "\n";
            out << "Size: " << dataSize << endl;
            out << "Used Time: " << BinaryInsertionSort(array, dataSize) << " milisecs\n";
            GenerateData(array, dataSize, order);
            out << "Comparisons: " << BinaryInsertionSortCountCompare(array, dataSize) << "\n";
            cout << "Insertion Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "\n\nBubble Sort:\n";
            out << "Order: " << dataOrder << "\n";
            out << "Size: " << dataSize << endl;
            out << "Used Time: " << BubbleSort(array, dataSize) << " milisecs\n";
            GenerateData(array, dataSize, order);
            out << "Comparisons: " << BubbleSortCountCompare(array, dataSize) << "\n";
            cout << "Bubble Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "\n\nShaker Sort:\n";
            out << "Order: " << dataOrder << "\n";
            out << "Size: " << dataSize << endl;
            out << "Used Time: " << ShakerSort(array, dataSize) << " milisecs\n";
            GenerateData(array, dataSize, order);
            out << "Comparisons: " << ShakerSortCountCompare(array, dataSize) << "\n";
            cout << "Shaker Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }*/
        /*for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "\n\nShell Sort:\n";
            out << "Order: " << dataOrder << "\n";
            out << "Size: " << dataSize << endl;
            out << "Used Time: " << ShellSort(array, dataSize) << " milisecs\n";
            //GenerateData(array, dataSize, order);
            //out << "Comparisons: " << ShakerSortCountCompare(array, dataSize) << "\n";
            cout << "Shell Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }*/
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "\n\nHeap Sort:\n";
            out << "Order: " << dataOrder << "\n";
            out << "Size: " << dataSize << endl;
            out << "Used Time: " << HeapSort(array, dataSize) << " milisecs\n";
            GenerateData(array, dataSize, order);
            out << "Comparisons: " << HeapSortCountCompare(array, dataSize) << "\n";
            cout << "Heap Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "\n\nMerge Sort:\n";
            out << "Order: " << dataOrder << "\n";
            out << "Size: " << dataSize << endl;
            out << "Used Time: " << MergeSortCalcTime(array, dataSize) << " milisecs\n";
            GenerateData(array, dataSize, order);
            out << "Comparisons: " << MergeSortCalcCompare(array, dataSize) << "\n";
            cout << "Merge Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "\n\nQuick Sort:\n";
            out << "Order: " << dataOrder << "\n";
            out << "Size: " << dataSize << endl;
            out << "Used Time: " << QuickSortCalcTime(array, dataSize) << " milisecs\n";
            GenerateData(array, dataSize, order);
            out << "Comparisons: " << QuickSortCalcCompare(array, dataSize) << "\n";
            cout << "Quick Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "\n\nCounting Sort:\n";
            out << "Order: " << dataOrder << "\n";
            out << "Size: " << dataSize << endl;
            out << "Used Time: " << CountingSortCalcTime(array, dataSize) << " milisecs\n";
            GenerateData(array, dataSize, order);
            out << "Comparisons: " << CountingSortCalcCompare(array, dataSize) << "\n";
            cout << "Counting Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
        for (int size = 0; size < 6; size++) {
            int dataSize = dataSizes[size];
            string dataOrder = getOrder(order);
            GenerateData(array, dataSize, order);
            out << "\n\nRadix Sort:\n";
            out << "Order: " << dataOrder << "\n";
            out << "Size: " << dataSize << endl;
            out << "Used Time: " << LSDRadixSortCalcTime(array, dataSize) << " milisecs\n";
            GenerateData(array, dataSize, order);
            out << "Comparisons: " << LSDRadixSortCalcCompare(array, dataSize) << "\n";
            cout << "LSD Radix Sort | Size: " << dataSize << " | Order: " << dataOrder << " COMPLETED!" << endl;
        }
    }

    out.close();

    return 0;
}