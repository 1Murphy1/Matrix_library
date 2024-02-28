#include<iostream>
#include <stdexcept>
#include <vector>

using namespace std;


class Matrix{
    private:
    int rows_, cols_;
    double **matrix_;
    
    public:
    Matrix();
    Matrix(int rows,int cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();
    
    void PrintMatrix()const;
    
    bool EqMatrix(const Matrix& other) const;
    void SumMatrix(const Matrix& other);
    void SubMatrix(const Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const Matrix& other);
    
    Matrix Transpose()const;
    Matrix CalcComplements();
    double Determinant();
    Matrix InverseMatrix();
    bool isInvertible();
    Matrix GetSubmatrix(int row, int col)const;
    
    
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other)const;
    Matrix operator*(int s) const;
    bool operator==(const Matrix& other);
    Matrix &operator=(const Matrix& other);
    Matrix operator+=(const Matrix& other);
    Matrix operator-=(const Matrix& other);
    Matrix operator*=(const Matrix& other);
    double* operator[](int index) const;
    
    
    int GetRows() const;
    void SetRows(int rows);
    
    int GetCols() const;
    void SetCols(int cols);
    
};
