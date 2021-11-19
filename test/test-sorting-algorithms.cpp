#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <chrono>
using namespace std;

#include "DataGenerator.h"

void printArray(int *a, int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << "  ";
    cout << endl;
}

void MySwapFunction(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int FindMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (max < a[i])
            max = a[i];
    return max;
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
                MySwapFunction(a[j], a[j + 1]);
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
                MySwapFunction(a[j], a[j + 1]);
                lastSwapPos = j + 1;
            }
        }
        right = lastSwapPos - 1;
        for (int j = right; ++cmp && j > left; --j) {
            if (++cmp && a[j-1] > a[j]) {
                MySwapFunction(a[j - 1], a[j]);
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
        MySwapFunction(a[0], a[right]);
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
    // Chọn pivot là phần tử ngoài cùng bên trái
    int mid = left + (right - left) / 2;
    if (a[left] > a[mid])
        swap(a[left], a[mid]);
    if (a[left] > a[right])
        swap(a[left], a[right]);
    if (a[mid] < a[right])
        swap(a[mid], a[right]);
    int pivot = a[right];
    
    // Các biến chạy i chạy từ trái sang phải, j chạy từ phải sang trái
    int i = left - 1;
    int j = right;
    do {
        // Tăng i đến khi a[i] >= pivot
        do
            i++;
        while (a[i] < pivot);

        // Giảm j đến khi a[j] <= pivot
        do
            j--;
        while (a[j] > pivot);

        // Hoán vị a[i], a[j]
        MySwapFunction(a[i], a[j]);

        // Nếu i >= j thì thoát khỏi vòng lặp
    } while (i < j);

    // Hoán vị lại lần hoán vị cuối do ta chỉ hoán vị khi i < j
    MySwapFunction(a[i], a[j]);

    // Đưa pivot vào vị trí đúng của nó trong mảng được sắp
    MySwapFunction(a[i], a[right]);
    return i;
}

void QuickSort(int *a, int left, int right) {
    if (left < right) {
        int splitPos = Partition(a, left, right);
        QuickSort(a, left, splitPos - 1);
        QuickSort(a, splitPos + 1, right);
    }
}

//==========================================================================================================
// Hàm sắp xếp đếm
void CountingSort(int *a, int n, int max) { 
    // Giá trị count[i] là số lần xuất hiện của số i trong mảng a
    int *count = new int[max+1]{0};   
    for (int i=0; i<n; i++)                                  
        count[a[i]]++;

    // Xử lý lại mảng count
    for (int i=1; i<=n; i++)       
        count[i] += count[i-1];   

    // Mảng temp để chứa kết quả sắp xếp 
    int *temp = new int[n]{0};                    
    for (int i = n-1; i >= 0; --i) {              
        temp[--count[a[i]]] = a[i];  
    }

    // Sao chép mảng temp vào lại mảng a
    for (int i = 0; i < n; i++)
        a[i] = temp[i];

    // Kết thúc thuật toán, trả lại bộ nhớ
    delete[] count;
    delete[] temp;
}

// Hàm sắp xếp đếm trả về số phép so sánh
long long CountingSortCountCompare(int *a, int n, int max) {
    long long cmp = 0;

    // Giá trị count[i] là số lần xuất hiện của số i trong mảng a
    int *count = new int[max+1]{0};    
    for (int i=0; ++cmp && i<n; i++)                                  
        count[a[i]]++;

    // Xử lý lại mảng count
    for (int i=1; ++cmp && i<=n; i++)       
        count[i] += count[i-1];   

    // Mảng temp để chứa kết quả sắp xếp 
    int *temp = new int[n]{0};                    
    for (int i = n-1; ++cmp && i >= 0; --i) {              
        temp[--count[a[i]]] = a[i];  
    }

    // Sao chép mảng temp vào lại mảng a
    for (int i = 0; ++cmp && i < n; i++)
        a[i] = temp[i];

    // Kết thúc thuật toán, trả lại bộ nhớ
    delete[] count;
    delete[] temp;

    return cmp;
}

// Hàm sắp xếp đếm trả về thời gian thực thi
long long CountingSortCalcTime(int *a, int n) {
    int max = FindMax(a, n);
    auto start = chrono::high_resolution_clock::now();
    CountingSort(a, n, max);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// Hàm sắp xếp đếm trả về số phép so sánh
long long CountingSortCalcCompare(int *a, int n) {
    int max = FindMax(a, n);
    long long cmp = CountingSortCountCompare(a, n, max);
    return cmp;
}

// RADIX SORT

// Hàm trả về chữ số cơ số k của num
int Digit(int num, int k) {
    int digitk = (num / int(pow(10, k))) % 10;
    return digitk;
}

// Hàm trả về số chữ số của số lớn nhất trong mảng
int CalcDRadixSort(int *a, int n) {
    stringstream ss;
    ss << FindMax(a, n);
    return ss.str().length();
}

// Hàm sắp xếp theo cơ số k
void RadixSort(int *a, int n, int k) {
    // count[i] là số lần xuất hiện số i trong các chữ số hàng k
    // của các phần tử của mảng
    int *count = new int[10]{0};

    for (int i=0; i<n; i++) {
        count[Digit(a[i], k)]++;
    }

    // Xử lý lại mảng count để counting sort
    for (int i=1; i<10; i++) {
        count[i] += count[i-1];
    }

    // Mảng temp để chứa tạm kết quả sắp xếp
    int *temp = new int[n]{0};
    for (int i=n-1; i>=0; --i) {
        temp[--count[Digit(a[i], k)]] = a[i];
    }

    // Sao chép kết quả tạm sang mảng chính
    for (int i=0; i<n; i++)
        a[i] = temp[i];

    // Trả lại bộ nhớ
    delete[] count;
    delete[] temp;
}

// Hàm sắp xếp theo cơ số (bắt đầu từ Least Significant Digit)
// d là số chữ số của số lớn nhất trong mảng
void LSDRadixSort(int *a, int n, int d) {
    for (int k=0; k<d; k++)
        RadixSort(a, n, k);
}

// Hàm sắp xếp theo cơ số trả về thời gian thực thi giải thuật
long long LSDRadixSortCalcTime(int *a, int n) {
    int d = CalcDRadixSort(a, n);
    auto start = chrono::high_resolution_clock::now();
    LSDRadixSort(a, n, d);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// Hàm sắp xếp theo cơ số k
void RadixSortCountCmp(int *a, int n, int k, long long &cmp) {
    // count[i] là số lần xuất hiện số i trong các chữ số hàng k
    // của các phần tử của mảng
    int *count = new int[10]{0};

    for (int i=0; ++cmp && i<n; i++) {
        count[Digit(a[i], k)]++;
    }

    // Xử lý lại mảng count để counting sort
    for (int i=1; ++cmp && i<10; i++) {
        count[i] += count[i-1];
    }

    // Mảng temp để chứa tạm kết quả sắp xếp
    int *temp = new int[n]{0};
    for (int i=n-1; ++cmp && i>=0; --i) {
        temp[--count[Digit(a[i], k)]] = a[i];
    }

    // Sao chép kết quả tạm sang mảng chính
    for (int i=0; ++cmp && i<n; i++)
        a[i] = temp[i];

    // Trả lại bộ nhớ
    delete[] count;
    delete[] temp;
}

// Hàm sắp xếp theo cơ số (bắt đầu từ Least Significant Digit)
// d là số chữ số của số lớn nhất trong mảng
void LSDRadixSortCountCmp(int *a, int n, int d, long long &cmp) {
    for (int k=0; ++cmp && k<d; k++)
        RadixSortCountCmp(a, n, k, cmp);
}

// Hàm sắp xếp theo cơ số trả về số phép so sánh
long long LSDRadixSortCalcCompare(int *a, int n) {
    long long cmp = 0;
    int d = CalcDRadixSort(a, n);
    LSDRadixSortCountCmp(a, n, d, cmp);
    return cmp;
}

int main() {
    int n = 500000;

    int *a = new int[n];
    //int *b = new int[n];

    GenerateData(a, n, 0);

    //printArray(a, n);
    //printArray(b, n);

    int d = CalcDRadixSort(a, n);
    cout << "d = " << d << endl;
    LSDRadixSort(a, n, d);

    printArray(a, n);

    delete[] a;
    //delete[] b;

    return 0;
}