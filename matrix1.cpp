#include <bits/stdc++.h>
using namespace std;

void seqMat(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C)
{
    int n = A.size();
    int m = B[0].size();
    int p = A[0].size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < p; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void parMat(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C)
{
    int n = A.size();
    int m = B[0].size();
    int p = A[0].size();

#pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < p; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void print(vector<vector<int>> &mat)
{
    for (auto row : mat)
    {
        for (auto val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n, p, m;
    cout << "\nEnter number of rows : (n) ";
    cin >> n;
    cout << "\nEnter p : ";
    cin >> p;
    cout << "\nEnter m : ";
    cin >> m;

    vector<vector<int>> A(n, vector<int>(p));
    vector<vector<int>> B(p, vector<int>(m));
    vector<vector<int>> C_seq(n, vector<int>(m, 0));
    vector<vector<int>> C_par(n, vector<int>(m, 0));

    cout << "\nEnter Elements of Mat A : ";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p; j++)
        {
            cout << "A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }
    }
    cout << "\nEnter Elements of Mat B : ";
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << "A[" << i << "][" << j << "]: ";
            cin >> B[i][j];
        }
    }
}