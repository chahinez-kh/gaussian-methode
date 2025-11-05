/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cout << "Enter number of equations (n): ";
    if(!(cin >> n) || n <= 0){
        cerr << "Invalid n\n";
        return 1;
    }

    // Augmented matrix of size n x (n+1)
    vector<vector<double>> A(n, vector<double>(n+1));
    cout << "Enter each row: coefficients (n values) then constant B (total n+1 numbers per row)\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            if(!(cin >> A[i][j])){
                cerr << "Invalid input at row " << i << " col " << j << "\n";
                return 1;
            }
        }
    }

    // Forward elimination with partial pivoting
    for(int k = 0; k < n; ++k){
        // find pivot row (max absolute in column k from rows k..n-1)
        int pivot_row = k;
        double maxval = fabs(A[k][k]);
        for(int i = k+1; i < n; ++i){
            double v = fabs(A[i][k]);
            if(v > maxval){
                maxval = v;
                pivot_row = i;
            }
        }

        // if pivot is (close to) zero => singular or near singular
        const double EPS = 1e-12;
        if(maxval < EPS){
            cerr << "Zero (or near-zero) pivot encountered at column " << k << ".\n";
            cerr << "Matrix may be singular or require a different pivot strategy.\n";
            return 1;
        }

        // swap rows k and pivot_row if needed
        if(pivot_row != k){
            swap(A[k], A[pivot_row]);
        }

        // eliminate rows below
        for(int i = k+1; i < n; ++i){
            double factor = A[i][k] / A[k][k];
            // subtract factor * row k from row i (columns k..n)
            for(int j = k; j < n+1; ++j){
                A[i][j] -= factor * A[k][j];
            }
        }
    }

    // Back substitution
    vector<double> X(n, 0.0);
    for(int i = n-1; i >= 0; --i){
        double sum = 0.0;
        for(int j = i+1; j < n; ++j) sum += A[i][j] * X[j];
        double denom = A[i][i];
        if(fabs(denom) < 1e-12){
            cerr << "Zero diagonal element at row " << i << ". Cannot divide.\n";
            return 1;
        }
        X[i] = (A[i][n] - sum) / denom;
    }

    // Output
    cout << fixed << setprecision(6);
    cout << "Solution:\n";
    for(int i=0;i<n;i++){
        cout << "X[" << i << "] = " << X[i] << "\n";
    }
    return 0;
}
