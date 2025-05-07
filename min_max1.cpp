#include <bits/stdc++.h>
using namespace std;

int minval(int arr[], int n)
{
    int min = arr[0];
#pragma omp parallel for reduction(min : minval)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

int maxval(int arr[], int n)
{
    int max = arr[0];
#pragma omp parallel for reduction(max : maxval)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int sum(int arr[], int n)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int average(int arr[], int n)
{
    return (double)sum(arr, n) / n;
}

int main()
{
    int n;
    cout << "\nEnter the number of elements : ";
    cin >> n;

    int arr[n];
    cout << "\nEnter the elements : ";
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
        // cin >> arr[i];
    }

    cout << "\nArray is : ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\nMinimum value is : " << minval(arr, n) << endl;
    cout << "\nMaximum value is : " << maxval(arr, n) << endl;
    cout << "\nSum of all elemets is : " << sum(arr, n) << endl;
    cout << "\nAverage is : " << average(arr, n) << endl;

    return 0;
}