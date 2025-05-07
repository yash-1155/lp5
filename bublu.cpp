#include <bits/stdc++.h>
using namespace std;

void seqBublu(vector<int> &arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parBublu(vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
#pragma omp parallel for
        for (int j = i % 2; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void print(vector<int> &arr)
{
    for (auto x : arr)
    {
        cout << x << " ";
    }
}

int main()
{
    int n;
    cout << "\nEnter no of elements : ";
    cin >> n;
    vector<int>
        arr(n),
        arr_copy(n);

    for (int i = 0; i < n; i++)
    {
        // cin >> arr[i];
        arr[i] = rand() % 1000;
        arr_copy[i] = arr[i];
    }

    cout << "\nUnsorted Array is : ";
    print(arr);
    cout << endl;

    auto start = chrono::high_resolution_clock::now();
    seqBublu(arr, n);
    print(arr);
    auto end = chrono::high_resolution_clock::now();

    cout << "\nTime takne by serial : " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds " << endl;

    start = chrono::high_resolution_clock::now();
    seqBublu(arr_copy, n);
    print(arr_copy);
    end = chrono::high_resolution_clock::now();

    cout << "\nTime takne by Parallel : " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds " << endl;

    return 0;
}