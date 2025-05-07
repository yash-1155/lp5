#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &arr, int left, int mid, int right)
{
    vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }
    while (i <= mid)
        temp.push_back(arr[i++]);
    while (j <= right)
        temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++)
    {
        arr[left + k] = temp[k];
    }
}

void seqSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        seqSort(arr, left, mid);
        seqSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void parallelSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            parallelSort(arr, left, mid);

#pragma omp section
            parallelSort(arr, mid + 1, right);
        }
        merge(arr, left, mid, right);
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
        // cin >> arr[i];
        arr[i] = rand() % 1000;
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