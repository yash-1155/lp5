#include <bits/stdc++.h>
using namespace std;

int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void seqSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        seqSort(arr, low, pi - 1);
        seqSort(arr, pi + 1, high);
    }
}

void parallelSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
#pragma omp parallel sections
        {
#pragma omp section
            seqSort(arr, low, pi - 1);
#pragma omp section
            seqSort(arr, pi + 1, high);
        }
    }
}

void print(const vector<int> &arr)
{
    for (auto x : arr)
    {
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "\nEnter number of elements : ";
    cin >> n;

    vector<int> arr(n), arrCopy(n);
    cout << "\nEnter elemets : \n";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        arrCopy[i] = arr[i];
    }

    auto start = chrono::high_resolution_clock::now();
    cout << "\nSorted Array : ";
    seqSort(arr, 0, n - 1);
    print(arr);
    auto end = chrono::high_resolution_clock::now();
    cout << "\nTime taken Sequential : " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    start = chrono::high_resolution_clock::now();
    cout << "\nSorted Array : ";
    seqSort(arrCopy, 0, n - 1);
    print(arrCopy);
    end = chrono::high_resolution_clock::now();
    cout << "\nTime taken Parallel : " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    return 0;
}