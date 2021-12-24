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

#pragma once
#include <chrono>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

//============================================================================================================
// SELECTION SORT
// Ý tưởng: Với mỗi giá trị i nằm trong đoạn [0, n-2], tìm amin = min{a[j]} với j trong đoạn
// [i, n-1], sau đó swap amin với a[i] 
// Tài liệu tham khảo: https://www.geeksforgeeks.org/selection-sort/

// Trả về thời gian chạy hàm
long long SelectionSort(int *a, int n);
// Trả về số phép so sánh
long long SelectionSortCountCompare(int *a, int n);

//============================================================================================================
// INSERTION SORT
// Ý tưởng: với mỗi giá trị i nằm trong đoạn [1, n-1], ta xem như đoạn từ a[0] đến a[i-1] đã
// được sắp, ta sẽ tìm vị trí đúng cho a[i] trong đoạn từ a[0] đến a[i-1]
// Cải tiến: do đoạn từ a[0] đến a[i-1] đã được sắp, ta có thể tìm vị trí để chèn a[i] vào
// bằng tìm kiếm nhị phân
// Tài liệu tham khảo: video record bài giảng của thầy Nguyễn Thanh Phương, ngày 8-10-2021 phần 1
// Link: https://courses.fit.hcmus.edu.vn/mod/page/view.php?id=86001

// Hàm trả về thời gian thực thi hàm
long long BinaryInsertionSort(int a[], int n);
// Hàm trả về số phép so sánh
long long BinaryInsertionSortCountCompare(int a[], int n);

//============================================================================================================
// BUBBLE SORT
// Ý tưởng: ta làm cho phần tử lớn nhất trong đoạn từ a[left] đến a[right] "nổi" lên vị trí a[right]
// sau đó giảm right đi 1 và tiếp tục cho đến khi left > right
// Cải tiến: nếu trong một lần duyệt không tìm ra phần tử a[j] > a[j+1] thì đã sắp xếp xong
// Cải tiến: ghi nhớ vị trí cuối cùng xảy ra phép hoán vị để thu hẹp khoản cần duyệt nhanh hơn
// Tài liệu tham khảo: video record bài giảng của thầy Nguyễn Thanh Phương, ngày 8-10-2021 phần 1
// Link: https://courses.fit.hcmus.edu.vn/mod/page/view.php?id=86001

// Hàm trả về thời gian thực thi hàm
long long BubbleSort(int a[], int n);

// Hàm trả về số phép so sánh
long long BubbleSortCountCompare(int a[], int n);

//============================================================================================================
// SHAKER SORT
// Ý tưởng: là một bản cải tiến của Bubble Sort, sau khi duyệt từ left -> right, tiếp tục duyệt từ right
// -> left, giảm đáng kể số phép so sánh trong trường hợp phần tử lớn nhất nằm ở đầu mảng hoặc phần tử
// nhỏ nhất nằm ở cuối mảng
// Tài liệu tham khảo: video record bài giảng của thầy Nguyễn Thanh Phương, ngày 8-10-2021 phần 1
// Link: https://courses.fit.hcmus.edu.vn/mod/page/view.php?id=86001

// Hàm trả về thời gian thực thi hàm
long long ShakerSort(int *a, int n);

// Hàm trả về số phép so sánh
long long ShakerSortCountCompare(int *a, int n);

//============================================================================================================
// SHELL SORT
// Ý tưởng: với mỗi giá trị interval từ lớn đến nhỏ, chia mảng thành interval mảng con (mảng
// mà các phần tử cách nhau interval vị trí), rồi insertion sort mỗi mảng con. Dừng lại
// khi interval = 1
// Tài liệu tham khảo: https://www.geeksforgeeks.org/shellsort/

// Hàm trả về thời gian thực thi hàm
long long ShellSort(int arr[], int n);

// Hàm trả về số phép so sánh
long long ShellSortCountCompare(int arr[], int n);

//============================================================================================================
// HEAP SORT
// Ý tưởng: xây dựng cây max-heap từ mảng, sau đó rút phần tử root ra (chính là max của heap)
// rồi đặt vào cuối mảng, đổi phần tử cuối mảng lên làm root rồi cho nó trượt xuống cây heap
// lần lượt làm với heap nhỏ dần cho đến khi mảng được sắp
// Tài liệu tham khảo: video record bài giảng của thầy Nguyễn Thanh Phương, ngày 15-10-2021 phần 1
// Link: https://courses.fit.hcmus.edu.vn/mod/page/view.php?id=86288

// Hàm trượt phần tử a[left] xuống đúng vị trí trong cây max-heap
void sift(int *a, int left, int right);

// Hàm trượt phần tử a[left] xuống đúng vị trí trong cây max-heap (trả về số phép so sánh)
long long siftCountCompare(int *a, int left, int right);

// Hàm trả về thời gian thực thi hàm
long long HeapSort(int *a, int n);

// Hàm trả về số phép so sánh
long long HeapSortCountCompare(int *a, int n);

//============================================================================================================
// MERGE SORT
// Ý tưởng: lần lượt chia mảng ra làm 2 mảng con bằng nhau, sau đó tiếp tục gọi đệ quy sắp xếp trộn 
// 2 mảng con, sau đó trộn 2 mảng con lại với nhau
// Tài liệu tham khảo: video record bài giảng của thầy Nguyễn Minh Huy (môn Kỹ thuật lập trình), ngày
// 17-06-2021
// Link: https://drive.google.com/file/d/1epx3KsjlvXBvj3lETn_dHN2PighwaciP/view
// Hàm trộn hai mảng a, b vào mảng c theo thứ tự không giảm
void MergeArray(int *a, int *b, int sizea, int sizeb, int *c);

// Hàm copy mảng src từ src[from] đến src[to] vào mảng dest
void CopyArray(int *src, int *dest, int from, int to);

// Hàm sắp xếp trộn
// mảng temp phải được cấp phát n phần tử trước
void MergeSort(int *arr, int n, int *temp);

// Hàm sắp xếp trộn trả về thời gian chạy
long long MergeSortCalcTime(int *a, int n);

// Hàm trộn 2 mảng trả về số phép so sánh
long long MergeArrayCountCompare(int *a, int *b, int sizea, int sizeb, int *c);

// Hàm copy mảng trả về số phép so sánh
long long CopyArrayCountCompare(int *src, int *dest, int from, int to);

// Hàm sắp xếp trộn có đếm số phép so sánh
void MergeSortCountCompare(int *arr, int n, int *temp, long long &cmp);

// Hàm sắp xếp trộn trả về số phép so sánh
long long MergeSortCalcCompare(int *a, int n);

//============================================================================================================
// QUICK SORT
// Ý tưởng: chọn phần tử pivot, sau đó phân hoạch mảng theo phần tử pivot đã chọn, khi đó phần tử pivot đã 
// nằm ở đúng vị trí trong mảng sau khi được sắp, tiếp tục gọi đệ quy quick sort với mỗi mảng con sau khi phân hoạch
// Tài liệu tham khảo: video record thầy Phương, ngày 8-10-2021 phần 2
// Link: https://drive.google.com/file/d/1MmJcIQSi24xjkbpAkR8cI91371xFNoFL/view

// Hàm phân hoạch mảng từ vị trí left đến right, phần tử pivot là a[left]
// trả về vị trí cuối của pivot
int Partition(int *a, int left, int right);

// Hàm quick sort chia để trị
void QuickSort(int *a, int left, int right);

// Hàm quick sort trả về thời gian thực thi thuật toán
long long QuickSortCalcTime(int *a, int n);

// Hàm phân hoạch có đếm số phép so sánh
int PartitionCountCompare(int *a, int left, int right, long long &cmp);

// Hàm quick sort chia để trị có đến số phép so sánh
void QuickSortCountCompare(int *a, int left, int right, long long &cmp);

// Hàm quick sort trả về số phép so sánh
long long QuickSortCalcCompare(int *a, int n);

//==========================================================================================================
// COUNTING SORT
// Ý tưởng: không rõ
// Tài liệu tham khảo: video record thầy Phương, ngày 15-10-2021 phần 2
// Link: https://drive.google.com/file/d/1wHClVvwTVIGSiQqDsFm2koYLm9n6inHF/view

// Hàm tìm giá trị lớn nhất của mảng số nguyên
int FindMax(int *a, int n);

// Hàm sắp xếp đếm
void CountingSort(int *a, int n, int max);

// Hàm sắp xếp đếm trả về số phép so sánh
long long CountingSortCountCompare(int *a, int n, int max);

// Hàm sắp xếp đếm trả về thời gian thực thi
long long CountingSortCalcTime(int *a, int n);

// Hàm sắp xếp đếm trả về số phép so sánh
long long CountingSortCalcCompare(int *a, int n);

//==========================================================================================================
// RADIX SORT

// Hàm trả về chữ số cơ số k của num
int Digit(int num, int k);

// Hàm trả về số chữ số của số lớn nhất trong mảng
int CalcDRadixSort(int *a, int n);

// Hàm sắp xếp theo cơ số k
void RadixSort(int *a, int n, int k);

// Hàm sắp xếp theo cơ số (bắt đầu từ Least Significant Digit)
// d là số chữ số của số lớn nhất trong mảng
void LSDRadixSort(int *a, int n, int d);

// Hàm sắp xếp theo cơ số k
void RadixSortCountCmp(int *a, int n, int k, long long &cmp);

// Hàm sắp xếp theo cơ số (bắt đầu từ Least Significant Digit)
// d là số chữ số của số lớn nhất trong mảng
void LSDRadixSortCountCmp(int *a, int n, int d, long long &cmp);

// Hàm sắp xếp theo cơ số trả về thời gian thực thi giải thuật
long long LSDRadixSortCalcTime(int *a, int n);

// Hàm sắp xếp theo cơ số trả về số phép so sánh
long long LSDRadixSortCalcCompare(int *a, int n);

//==========================================================================================================
// FLASH SORT

// Hàm trả về giá trị nhỏ nhất trong mảng
int FindMin(int *a, int n);

long long CalcKFlashSort(long long m, long long a, long long max, long long min);

void FlashSort(int *a, int n, int min, int max);

void FlashSortCountCompare(int *a, int n, int min, int max, long long &cmp);

long long FlashSortCalcTime(int *a, int n);

long long FlashSortCalcCompare(int *a, int n);