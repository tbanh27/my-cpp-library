#include <iostream>
#include <chrono>
using namespace std;

#include "DataGenerator.h"

void printArray(int *a, int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << "  ";
    cout << endl;
}

void BinaryInsertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int valueToInsert = a[i];

        // Dùng tìm kiếm nhị phân để tìm posToInsert
        int posToInsert;
        int left = 0, right = i - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (a[mid] < valueToInsert)
                left = mid + 1;
            else
                right = mid - 1;
        }
        posToInsert = left;

        // Chuyển dời dữ liệu từ a[posToInsert] sang phải
        for (int j = i; j > posToInsert; j--)
            a[j] = a[j - 1];

        // Chèn valueToInsert vào a[posToInsert]
        a[posToInsert] = valueToInsert;
    }
}

void BubbleSort(int a[], int n) {
    int left = 0, right = n - 1;
    while (left <= right) {
        bool isSwapped = false;
        int lastSwapPos = right;
        for (int j = left; j < right; ++j) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                isSwapped = true;
                lastSwapPos = j + 1;
            }
        }
        if (isSwapped == false)
            break;
        right = lastSwapPos;
    }
}

long long ShakerSort(int *a, int n) {
    int cmp = 0;
    auto start = chrono::high_resolution_clock::now();
    int left = 0, right = n - 1;
    int lastSwapPos = n - 1;
    do {
        for (int j = left; ++cmp && j < right; j++) {
            if (++cmp && a[j] > a[j+1]) {
                swap(a[j], a[j + 1]);
                lastSwapPos = j + 1;
            }
        }
        right = lastSwapPos - 1;
        for (int j = right; ++cmp && j > left; --j) {
            if (++cmp && a[j-1] > a[j]) {
                swap(a[j - 1], a[j]);
                lastSwapPos = j - 1;
            }
        }
        left = lastSwapPos + 1;
    } while (++cmp && left <= right);
    auto end = chrono::high_resolution_clock::now();
    auto runtime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Compare: " << cmp << endl;
    return runtime;
}


long long ShellSort(int arr[], int n) {
    auto start = chrono::high_resolution_clock::now();
    // Sử dụng cách chọn khoảng interval là n/2, n/4, n/8, ..., 1
    for (int interval = n/2; interval > 0; interval /= 2) {
        // Với mỗi khoảng interval, sắp xếp chèn các mảng con mà các phần tử
        // cách nhau một khoảng interval
        // VD: interval = 5 thì insertion sort các phần tử a[0], a[5], a[10],...
        // Rồi a[1], a[6], a[11],...
        // Chỉ số i bắt đầu từ interval, do a[0], a[1], ..., a[interval - 1] đều
        // được xem là các mảng có 1 phần tử dĩ nhiên được sắp
        for (int i = interval; i < n; i += 1) {
            // Lưu giá trị a[i] vào temp, vì khi chuyển dời các giá trị bên trái sang
            // thì a[i] sẽ bị lấp mất
            int temp = arr[i];

            // Bắt đầu chuyển dời dữ liệu từ mảng được sắp bên trái (các phần tử cách 
            // nhau interval) sang phải đến khi tìm ra vị trí thích hợp để chèn temp vào
            int j;           
            for (j = i; j >= interval && arr[j - interval] > temp; j -= interval)
                arr[j] = arr[j - interval];

            // Vòng lặp trên dừng khi a[j-interval] <= temp hoặc hết các giá trị j cần xét
            // Khi đó j là vị trí thích hợp để chèn temp vào
            arr[j] = temp;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// Hàm trượt phần tử a[left] xuống đúng vị trí trong cây max-heap
void sift(int *a, int left, int right) {
    int i = left;
    // right luôn bằng n-1
    int x = a[i];           // Phần tử cần trượt xuống trong max-heap
    int j = 2 * i + 1;          // a[j] và a[j+1] là hai node con của a[i]
    while (j <= right) {    
        if (j < right) {        // Đảm bảo có tồn tại a[j] và a[j+1]
            if (a[j] < a[j+1])  
                j = j + 1;      // Đảo bảo a[j] là phần tử Lớn hơn giữa a[2*i+1] và a[2*i+2]
        }
        if (a[j] < x)   // Nếu a[i] lớn hơn cả a[2*i+1] và a[2*i+2]
            break;      // thì a[i] đã ở đúng vị trí trong max-heap -> break
        a[i] = a[j];    // Nếu không, cho a[j] trượt lên vị trí của a[i]
        i = j;          // Coi như a[i] đã trượt xuống vị trí a[j], nhưng chưa thực sự swap
        j = 2 * i + 1;      // Tiếp tục xét
    }
    // Khi đã tìm ra vị trí đúng cho x, cho x trượt xuống đến vị trí đó
    a[i] = x; 
}

long long HeapSort(int *a, int n) {
    auto start = chrono::high_resolution_clock::now();

    // Xây dựng max-heap
    int left = (n-1) / 2;
    while (left >= 0) {
        sift(a, left, n - 1);
        left--;
    }

    // Sắp xếp
    int right = n - 1;
    while (right > 0) {
        swap(a[0], a[right]);
        right--;
        sift(a, 0, right);
    }

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

void MergeArray(int *a, int *b, int sizea, int sizeb, int *c) {
    int ia = 0, ib = 0, i = 0;
    while (ia < sizea && ib < sizeb) {
        c[i++] = (a[ia] < b[ib]) ? a[ia++] : b[ib++];
    }
    while (ia < sizea) {
        c[i++] = a[ia++];
    }
    while (ib < sizeb) {
        c[i++] = b[ib++];
    }
}

void CopyArray(int *src, int *dest, int from, int to) {
    int j = 0;
    for (int i = from; i <= to; i++) {
        dest[j++] = src[i];
    }
}

// must allocate memory for temp before using the function
// size of temp is same as size of arr
void MergeSort(int *arr, int n, int *temp) {
    if (n == 1)
        return;
    int size1 = n / 2;
    int size2 = n - size1;
    int *a1 = arr;
    int *a2 = arr + size1;
    MergeSort(a1, size1, temp);
    MergeSort(a2, size2, temp);
    MergeArray(a1, a2, size1, size2, temp);
    CopyArray(temp, arr, 0, n - 1);
}

long long MergeSortCalcTime(int *a, int n) {
    int *temp = new int[n];
    auto start = chrono::high_resolution_clock::now();
    MergeSort(a, n, temp);
    auto end = chrono::high_resolution_clock::now();
    delete[] temp;
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

long long MergeArrayCountCompare(int *a, int *b, int sizea, int sizeb, int *c) {
    int ia = 0, ib = 0, i = 0;
    long long cmp = 0;
    while (++cmp && ia < sizea && ++cmp && ib < sizeb) {
        c[i++] = (++cmp && a[ia] < b[ib]) ? a[ia++] : b[ib++];
    }
    while (++cmp && ia < sizea) {
        c[i++] = a[ia++];
    }
    while (++cmp && ib < sizeb) {
        c[i++] = b[ib++];
    }
    return cmp;
}

long long CopyArrayCountCompare(int *src, int *dest, int from, int to) {
    int j = 0;
    long long cmp = 0;
    for (int i = from; ++cmp && i <= to; i++) {
        dest[j++] = src[i];
    }
    return cmp;
}

// must allocate memory for temp before using the function
// size of temp is same as size of arr
void MergeSortCountCompare(int *arr, int n, int *temp, long long &cmp) {
    if (++cmp && n == 1)
        return;
    int size1 = n / 2;
    int size2 = n - size1;
    int *a1 = arr;
    int *a2 = arr + size1;
    MergeSortCountCompare(a1, size1, temp, cmp);
    MergeSortCountCompare(a2, size2, temp, cmp);
    cmp += MergeArrayCountCompare(a1, a2, size1, size2, temp);
    cmp += CopyArrayCountCompare(temp, arr, 0, n - 1);
}

// Hàm trả về số phép so sánh
long long MergeSortCalcCompare(int *a, int n) {
    int *temp = new int[n];
    long long cmp = 0;
    MergeSortCountCompare(a, n, temp, cmp);
    delete[] temp;
    return cmp;
}

int Partition(int *a, int left, int right) {
    int pivot = right;
    int i = left;
    int j = right - 1;
    while (i < j) {
        while (a[i] < a[pivot])
            i++;
        while (a[j] > a[pivot])
            j--;
        swap(a[i], a[j]);
    }
    // Lúc này j <= i
    swap(a[i], a[j]);   // trả lại một lần swap cuối khi i >= j vì ta chỉ swap khi i < j
    swap(a[j], a[pivot]);
    return j;
}

void QuickSort(int *a, int left, int right) {
    if (left < right) {
        int splitPos = Partition(a, left, right);
        QuickSort(a, left, splitPos - 1);
        QuickSort(a, splitPos + 1, right);
    }
}


int main() {
    int n = 10;

    int *a = new int[n];
    int *b = new int[n];

    GenerateRandomData(a, n);
    //GenerateRandomData(b, n);
    //GenerateReverseData(b, n);
    //GenerateReverseData(a, n);
    //GenerateSortedData(b, n);
    //GenerateNearlySortedData(b, n);

    printArray(a, n);
    //printArray(b, n);

    //cout << HeapSort(a, n) << endl;
    //cout << MergeSortCalcTime(b, n) << " milisecs\n";
    QuickSort(a, 0, n - 1);

    printArray(a, n);
    //printArray(b, n);

    delete[] a;
    delete[] b;

    return 0;
}