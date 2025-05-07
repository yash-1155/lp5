#include <bits/stdc++.h>
using namespace std;

void MultiplySeq(const vector<vector<int>> &mat, const vector<int> &vec, vector<int> &result)
{
    int n = mat.size();
    for (int i = 0; i < n; i++)
    {
        result[i] = 0;
        for (int j = 0; j < vec.size(); j++)
        {
            result[i] += mat[i][j] * vec[j];
        }
    }
}

void MultiplyPar(vector<vector<int>> &mat, vector<int> &vec, vector<int> &result)
{
    int n = mat.size();
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        result[i] = 0;
        for (int j = 0; j < vec.size(); j++)
        {
            result[i] += mat[i][j] * vec[j];
        }
    }
}

void print(const vector<int> &A)
{
    for (int x : A)
    {
        cout << x << " ";
    }
}

int main()
{
    int n, m;
    cout << "\nEnter no of rows : ";
    cin >> n;
    cout << "\nEnter no of cols : ";
    cin >> m;

    vector<vector<int>> mat(n, vector<int>(m));
    vector<int> vec(m);
    vector<int> res_seq(n), res_par(n);

    cout << "\nEnter elements : ";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << "\nElement [" << i << "][" << j << "] :";
            cin >> mat[i][j];
        }
    }
    cout << "\nElements for Vector : " << endl;
    for (int i = 0; i < m; i++)
    {
        cout << "\nElement " << i << " : ";
        cin >> vec[i];
    }

    auto start = chrono::high_resolution_clock::now();
    MultiplySeq(mat, vec, res_seq);
    auto end = chrono::high_resolution_clock::now();
    print(res_seq);
    cout << "\nTime taken by Sequential : " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    start = chrono::high_resolution_clock::now();
    MultiplyPar(mat, vec, res_par);
    end = chrono::high_resolution_clock::now();
    print(res_par);
    cout << "\nTime taken by Parallel : " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
    return 0;
}