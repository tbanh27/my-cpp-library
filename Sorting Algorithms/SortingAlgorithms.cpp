/*
Các giải thuật sắp xếP được cài đặt trong file này:
    - Selection Sort
    - Insertion Sort
    - Bubble Sort
    - Shaker Sort
    - Shell Sort
    - Heap Sort
    - Merge Sort
    - Quick Sort
    - Counting Sort
    - Radix Sort
    - Flash Sort
*/


#include "SortingAlgorithms.h"

void MySwapFunction(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// SELECTION SORT
// Ý tưởng: Với mỗi giá trị i nằm trong đoạn [0, n-2], tìm amin = min{a[j]} với j trong đoạn
// [i, n-1], sau đó swap amin với a[i] 
// Tài liệu tham khảo: https://www.geeksforgeeks.org/selection-sort/

// Trả về thời gian chạy hàm
long long SelectionSort(int *a, int n) {
    auto start = chrono::high_resolution_clock::now();
    int minIdx;
    for (int i = 0; i < n - 1; i++) {
        minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIdx]) {
                minIdx = j;
            }
        }
        MySwapFunction(a[i], a[minIdx]);
    }
    auto end = chrono::high_resolution_clock::now();
    auto runtime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    return runtime;
}

// Trả về số phép so sánh
long long SelectionSortCountCompare(int *a, int n) {
    long long compare = 0;
    int minIdx;
    for (int i = 0; ++compare && i < n - 1; i++) {
        minIdx = i;
        for (int j = i + 1; ++compare && j < n; j++) {
            if (++compare && a[j] < a[minIdx]) {
                minIdx = j;
            }
        }
        MySwapFunction(a[i], a[minIdx]);
    }
    return compare;
}

// INSERTION SORT
// Ý tưởng: với mỗi giá trị i nằm trong đoạn [1, n-1], ta xem như đoạn từ a[0] đến a[i-1] đã
// được sắp, ta sẽ tìm vị trí đúng cho a[i] trong đoạn từ a[0] đến a[i-1]
// Cải tiến: do đoạn từ a[0] đến a[i-1] đã được sắp, ta có thể tìm vị trí để chèn a[i] vào
// bằng tìm kiếm nhị phân
// Tài liệu tham khảo: video record bài giảng của thầy Nguyễn Thanh Phương, ngày 8-11-2021 phần 1
// Link: https://courses.fit.hcmus.edu.vn/mod/page/view.php?id=86001

// Hàm trả về thời gian thực thi hàm
long long BinaryInsertionSort(int a[], int n) {
    auto start = chrono::high_resolution_clock::now();
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
    auto end = chrono::high_resolution_clock::now();
    long long runtime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    return runtime;
}

// Hàm trả về số phép so sánh
long long BinaryInsertionSortCountCompare(int a[], int n) {
    long long compare = 0;
    for (int i = 1; ++compare && i < n; i++) {
        int valueToInsert = a[i];

        // Dùng tìm kiếm nhị phân để tìm posToInsert
        int posToInsert;
        int left = 0, right = i - 1;
        while (++compare && left <= right) {
            int mid = left + (right - left) / 2;
            if (++compare && a[mid] < valueToInsert)
                left = mid + 1;
            else
                right = mid - 1;
        }
        posToInsert = left;

        // Chuyển dời dữ liệu từ a[posToInsert] sang phải
        for (int j = i; ++compare && j > posToInsert; j--)
            a[j] = a[j - 1];

        // Chèn valueToInsert vào a[posToInsert]
        a[posToInsert] = valueToInsert;
    }
    return compare;
}

// BUBBLE SORT
// Ý tưởng: ta làm cho phần tử lớn nhất trong đoạn từ a[left] đến a[right] "nổi" lên vị trí a[right]
// sau đó giảm right đi 1 và tiếp tục cho đến khi left > right
// Cải tiến: nếu trong một lần duyệt không tìm ra phần tử a[j] > a[j+1] thì đã sắp xếp xong
// Cải tiến: ghi nhớ vị trí cuối cùng xảy ra phép hoán vị để thu hẹp khoản cần duyệt nhanh hơn
// Tài liệu tham khảo: video record bài giảng của thầy Nguyễn Thanh Phương, ngày 8-11-2021 phần 1
// Link: https://courses.fit.hcmus.edu.vn/mod/page/view.php?id=86001

// Hàm trả về thời gian thực thi hàm
long long BubbleSort(int a[], int n) {
    auto start = chrono::high_resolution_clock::now();
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
    auto end = chrono::high_resolution_clock::now();
    auto runtime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    return runtime;
}

// Hàm trả về số phép so sánh
long long BubbleSortCountCompare(int a[], int n) {
    long long compare = 0;
    int left = 0, right = n - 1;
    while (++compare && left <= right) {
        bool isSwapped = false;
        int lastSwapPos = right;
        for (int j = left; ++compare && j < right; ++j) {
            if (++compare && a[j] > a[j + 1]) {
                MySwapFunction(a[j], a[j + 1]);
                isSwapped = true;
                lastSwapPos = j + 1;
            }
        }
        if (++compare && isSwapped == false)
            break;
        right = lastSwapPos;
    }
    return compare;
}

// SHAKER SORT

// Hàm trả về thời gian thực thi hàm
long long ShakerSort(int *a, int n) {
    auto start = chrono::high_resolution_clock::now();
    int left = 0, right = n - 1;
    int lastSwapPos = n - 1;
    do {
        for (int j = left; j < right; j++) {
            if (a[j] > a[j+1]) {
                MySwapFunction(a[j], a[j + 1]);
                lastSwapPos = j + 1;
            }
        }
        right = lastSwapPos - 1;
        for (int j = right; j > left; --j) {
            if (a[j-1] > a[j]) {
                MySwapFunction(a[j - 1], a[j]);
                lastSwapPos = j - 1;
            }
        }
        left = lastSwapPos + 1;
    } while (left <= right);
    auto end = chrono::high_resolution_clock::now();
    auto runtime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    return runtime;
}

// Hàm trả về số phép so sánh
long long ShakerSortCountCompare(int *a, int n) {
    long long cmp = 0;
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
    return cmp;
}

// SHELL SORT
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

// Hàm trả về số phép so sánh
long long ShellSortCountCompare(int arr[], int n) {
    long long cmp = 0;
    // Sử dụng cách chọn khoảng interval là n/2, n/4, n/8, ..., 1
    for (int interval = n/2; ++cmp && interval > 0; interval /= 2) {
        // Với mỗi khoảng interval, sắp xếp chèn các mảng con mà các phần tử
        // cách nhau một khoảng interval
        // VD: interval = 5 thì insertion sort các phần tử a[0], a[5], a[10],...
        // Rồi a[1], a[6], a[11],...
        // Chỉ số i bắt đầu từ interval, do a[0], a[1], ..., a[interval - 1] đều
        // được xem là các mảng có 1 phần tử dĩ nhiên được sắp
        for (int i = interval; ++cmp && i < n; i += 1) {
            // Lưu giá trị a[i] vào temp, vì khi chuyển dời các giá trị bên trái sang
            // thì a[i] sẽ bị lấp mất
            int temp = arr[i];

            // Bắt đầu chuyển dời dữ liệu từ mảng được sắp bên trái (các phần tử cách 
            // nhau interval) sang phải đến khi tìm ra vị trí thích hợp để chèn temp vào
            int j;           
            for (j = i; ++cmp && j >= interval && ++cmp && arr[j - interval] > temp; j -= interval)
                arr[j] = arr[j - interval];

            // Vòng lặp trên dừng khi a[j-interval] <= temp hoặc hết các giá trị j cần xét
            // Khi đó j là vị trí thích hợp để chèn temp vào
            arr[j] = temp;
        }
    }
    return cmp;
}

//============================================================================================================
// HEAP SORT
// Ý tưởng: xây dựng cây max-heap từ mảng, sau đó rút phần tử root ra (chính là max của heap)
// rồi đặt vào cuối mảng, đổi phần tử cuối mảng lên làm root rồi cho nó trượt xuống cây heap
// lần lượt làm với heap nhỏ dần cho đến khi mảng được sắp
// Tài liệu tham khảo: video record bài giảng của thầy Nguyễn Thanh Phương, ngày 15-10-2021 phần 1
// Link: https://courses.fit.hcmus.edu.vn/mod/page/view.php?id=86288

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

// Hàm trượt phần tử a[left] xuống đúng vị trí trong cây max-heap (trả về số phép so sánh)
long long siftCountCompare(int *a, int left, int right) {
    long long cmp = 0;
    int i = left;
    // right luôn bằng n-1
    int x = a[i];           // Phần tử cần trượt xuống trong max-heap
    int j = 2 * i + 1;          // a[j] và a[j+1] là hai node con của a[i]
    while (++cmp && j <= right) {    
        if (++cmp && j < right) {        // Đảm bảo có tồn tại a[j] và a[j+1]
            if (++cmp && a[j] < a[j+1])  
                j = j + 1;      // Đảo bảo a[j] là phần tử Lớn hơn giữa a[2*i+1] và a[2*i+2]
        }
        if (++cmp && a[j] < x)   // Nếu a[i] lớn hơn cả a[2*i+1] và a[2*i+2]
            break;      // thì a[i] đã ở đúng vị trí trong max-heap -> break
        a[i] = a[j];    // Nếu không, cho a[j] trượt lên vị trí của a[i]
        i = j;          // Coi như a[i] đã trượt xuống vị trí a[j], nhưng chưa thực sự swap
        j = 2 * i + 1;      // Tiếp tục xét
    }
    // Khi đã tìm ra vị trí đúng cho x, cho x trượt xuống đến vị trí đó
    a[i] = x;

    return cmp;
}

// Hàm trả về thời gian thực thi hàm
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

// Hàm trả về số phép so sánh
long long HeapSortCountCompare(int *a, int n) {
    long long cmp = 0;

    // Xây dựng max-heap
    int left = (n-1) / 2;
    while (++cmp && left >= 0) {
        cmp += siftCountCompare(a, left, n - 1);
        left--;
    }

    // Sắp xếp
    int right = n - 1;
    while (++cmp && right > 0) {
        MySwapFunction(a[0], a[right]);
        right--;
        cmp += siftCountCompare(a, 0, right);
    }
    return cmp;
}

//============================================================================================================
// MERGE SORT
// Hàm trộn hai mảng a, b vào mảng c theo thứ tự không giảm
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

// Hàm copy mảng src từ src[from] đến src[to] vào mảng dest
void CopyArray(int *src, int *dest, int from, int to) {
    int j = 0;
    for (int i = from; i <= to; i++) {
        dest[j++] = src[i];
    }
}

// Hàm sắp xếp trộn
// mảng temp phải được cấp phát n phần tử trước
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

// Hàm sắp xếp trộn trả về thời gian chạy
long long MergeSortCalcTime(int *a, int n) {
    int *temp = new int[n];
    auto start = chrono::high_resolution_clock::now();
    MergeSort(a, n, temp);
    auto end = chrono::high_resolution_clock::now();
    delete[] temp;
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// Hàm trộn 2 mảng trả về số phép so sánh
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

// Hàm copy mảng trả về số phép so sánh
long long CopyArrayCountCompare(int *src, int *dest, int from, int to) {
    int j = 0;
    long long cmp = 0;
    for (int i = from; ++cmp && i <= to; i++) {
        dest[j++] = src[i];
    }
    return cmp;
}

// Hàm sắp xếp trộn có đếm số phép so sánh
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

// Hàm sắp xếp trộn trả về số phép so sánh
long long MergeSortCalcCompare(int *a, int n) {
    int *temp = new int[n];
    long long cmp = 0;
    MergeSortCountCompare(a, n, temp, cmp);
    delete[] temp;
    return cmp;
}

//============================================================================================================
// QUICK SORT
// Ý tưởng: chọn phần tử pivot, sau đó phân hoạch mảng theo phần tử pivot đã chọn, khi đó phần tử pivot đã 
// nằm ở đúng vị trí trong mảng sau khi được sắp, tiếp tục gọi đệ quy quick sort với mỗi mảng con sau khi phân hoạch
// Tài liệu tham khảo: video record thầy Phương, ngày 8-10-2021 phần 2
// Link: https://drive.google.com/file/d/1MmJcIQSi24xjkbpAkR8cI91371xFNoFL/view
// Cai tien: chon pivot la median cua left, right va mid
// Link tham khao: https://en.wikipedia.org/wiki/Quicksort#Choice_of_pivot

// Hàm phân hoạch mảng từ vị trí left đến right, phần tử pivot là a[left]
// trả về vị trí cuối của pivot
int Partition(int *a, int left, int right) {
    // Chọn pivot là phần tử ngoài cùng bên trái
    int mid = left + (right - left) / 2;
    if (a[left] > a[mid])
        MySwapFunction(a[left], a[mid]);
    if (a[left] > a[right])
        MySwapFunction(a[left], a[right]);
    if (a[mid] < a[right])
        MySwapFunction(a[mid], a[right]);
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

// Hàm quick sort chia để trị
void QuickSort(int *a, int left, int right) {
    if (left < right) {
        int splitPos = Partition(a, left, right);
        QuickSort(a, left, splitPos - 1);
        QuickSort(a, splitPos + 1, right);
    }
}

// Hàm quick sort trả về thời gian thực thi thuật toán
long long QuickSortCalcTime(int *a, int n) {
    auto start = chrono::high_resolution_clock::now();
    QuickSort(a, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// Hàm phân hoạch có đếm số phép so sánh
int PartitionCountCompare(int *a, int left, int right, long long &cmp) {
    // Chọn pivot là phần tử ngoài cùng bên trái
    int mid = left + (right - left) / 2;
    if (++cmp && a[left] > a[mid])
        MySwapFunction(a[left], a[mid]);
    if (++cmp && a[left] > a[right])
        MySwapFunction(a[left], a[right]);
    if (++cmp && a[mid] < a[right])
        MySwapFunction(a[mid], a[right]);
    int pivot = a[right];
    
    // Các biến chạy i chạy từ trái sang phải, j chạy từ phải sang trái
    int i = left - 1;
    int j = right;
    do {
        // Tăng i đến khi a[i] >= pivot
        do
            i++;
        while (++cmp && a[i] < pivot);

        // Giảm j đến khi a[j] <= pivot
        do
            j--;
        while (++cmp && a[j] > pivot);

        // Hoán vị a[i], a[j]
        MySwapFunction(a[i], a[j]);

        // Nếu i >= j thì thoát khỏi vòng lặp
    } while (++cmp && i < j);

    // Hoán vị lại lần hoán vị cuối do ta chỉ hoán vị khi i < j
    MySwapFunction(a[i], a[j]);

    // Đưa pivot vào vị trí đúng của nó trong mảng được sắp
    MySwapFunction(a[i], a[right]);
    return i;
}

// Hàm quick sort chia để trị có đến số phép so sánh
void QuickSortCountCompare(int *a, int left, int right, long long &cmp) {
    if (++cmp && left < right) {
        int splitPos = PartitionCountCompare(a, left, right, cmp);
        QuickSortCountCompare(a, left, splitPos - 1, cmp);
        QuickSortCountCompare(a, splitPos + 1, right, cmp);
    }
}

// Hàm quick sort trả về số phép so sánh
long long QuickSortCalcCompare(int *a, int n) {
    long long cmp = 0;
    QuickSortCountCompare(a, 0, n - 1, cmp);
    return cmp;
}

//==========================================================================================================
// Hàm sắp xếp đếm

int FindMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (max < a[i])
            max = a[i];
    return max;
}

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
