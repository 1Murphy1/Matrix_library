#include "matrix_oop.h"
#include <cmath>
#include <stdexcept>

using namespace std;

Matrix::Matrix(): rows_(0),cols_(0), matrix_(nullptr){}

Matrix::Matrix(int rows,int cols): rows_(rows), cols_(cols){
    if(rows<=0 || cols<=0){
        throw invalid_argument("Invalid matrix dimentions");
    }
    
    matrix_= new double *[rows_];
    
    for(int i=0; i<rows_; ++i){
        matrix_[i]= new double[cols_];
    }
}

Matrix::Matrix(const Matrix& other):rows_(other.rows_), cols_(other.cols_){
    matrix_= new double *[rows_];
    
    for(int i=0; i<rows_; ++i){
        matrix_= new double *[cols_];
        
        for(int j=0; j<cols_; j++){
            matrix_[i][j]=other.matrix_[i][j];
        }
    }
}


Matrix::Matrix(Matrix&& other):rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_){
    other.rows_=0;
    other.cols_=0;
    other.matrix_=nullptr;
}

Matrix::~Matrix(){
    if(matrix_ != nullptr){
        for(int i=0; i<rows_;i++){
            delete[] matrix_[i];
        }
        
        delete matrix_;
    }
} 



bool Matrix::EqMatrix(const Matrix& other) const {
    if(rows_ != other.rows_ || cols_ != other.cols_){
        return false;
    }
    
    for(int i=0; i<rows_; i++){
        for(int j=0; j<cols_; j++){
            if(matrix_[i][j] != other.matrix_[i][j]){
                return  false;
            }
        }
    }
    return true;
}

void Matrix::SumMatrix(const Matrix &other){
    if(rows_ != other.rows_ || cols_ != other.cols_){
        throw invalid_argument("Matrix dimensions dont match");
    }
    for(int i=0; i<rows_; i++){
        for(int j=0;j<cols_;j++){
            matrix_[i][j] +=other.matrix_[i][j];
        }
    }
}

 void Matrix::SubMatrix(const Matrix &other){
    if(rows_ != other.rows_ || cols_ != other.cols_){
        throw invalid_argument("Matrix dimensions dont match");
    }
    for(int i=0; i<rows_; i++){
        for(int j=0;j<cols_; j++){
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void Matrix::MulNumber(const double num){
    for(int i=0; i< rows_;i++){
        for(int j=0;j<cols_; j++){
            matrix_[i][j] *= num;
        }
    }
}

void Matrix::MulMatrix(const Matrix &other){
    if(cols_ != other.rows_){
        throw invalid_argument("Matrix dimensions are not compatible for multiplication");
    }
    Matrix result(rows_, other.cols_);
    
    for(int i=0; i < rows_; ++i){
        for(int j=0; j< other.cols_; ++j){
            for(int k = 0; k< cols_; ++k){
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
            
        }
    }
    *this = result;
}

void Matrix::PrintMatrix() const {
  for (int i = 0; i <rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      cout << matrix_[i][j] << " ";
    }
    cout << endl;
  }
}



Matrix Matrix::Transpose() const{
    Matrix result(cols_, rows_);
    
    for(int i = 0; i < rows_; ++i){
        for(int j = 0; j < cols_; ++j){
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result;
}

Matrix Matrix::CalcComplements(){
    Matrix result(rows_,cols_);
    
    for(int i=0; i< rows_ ;++i){
        for(int j=0; j<cols_; ++j){
            Matrix temp = this->GetSubmatrix(i,j);
            result.matrix_[i][j] = pow(-1.0,i+j)* temp.Determinant();
        }
    }
    return result;
}

double Matrix::Determinant(){
    if(rows_ != cols_){
        throw invalid_argument("Matrix must be a square matrix to calculate determinant");
    }
    if(rows_ == 1){
        return matrix_[0][0];
    }
    double det = 0;
    for(int i=0; i<cols_; ++i){
        Matrix temp = this->GetSubmatrix(0,i);
        det += matrix_[0][i] * pow(-1.0,i)*temp.Determinant();
    }
    return det;
}

Matrix Matrix::InverseMatrix(){
    double det = this->Determinant();
    if(det == 0.0){
        throw invalid_argument("Matrix isnt invertible");
    }
    
    Matrix result = this->CalcComplements();
    result.Transpose();
    result.MulNumber(1.0/det);
    
    return result;
    
}

bool Matrix::isInvertible() {
  double det = this->Determinant();
  return det != 0.0;
}


Matrix Matrix::GetSubmatrix(int row, int col) const{
    Matrix result(rows_ - 1, cols_ - 1);
    int k=0;
    int l=0;
    
    for(int i = 0; i < rows_; i++){
        int j;
        if(j==col){
            continue;
        }
        
        for(int j = 0; j<cols_; j++){
            if(j==col){
                continue;
            }
            result.matrix_[k][l++] = matrix_[i][j];
        }
        l =0;
        k++;
    }
    return result;
}


Matrix Matrix::operator+(const Matrix &other) const {
    Matrix result=*this;
    result.SumMatrix(other);
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
    Matrix result = *this;
    result.SubMatrix(other);
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
    Matrix result= *this;
    result.MulMatrix(other);
    return result;
}

Matrix Matrix::operator*(int s) const {
    Matrix result= *this;
    result.MulNumber(s);
    return result;
}

bool Matrix::operator==(const Matrix &other){
    return EqMatrix(other);
}

Matrix& Matrix::operator=(const Matrix &other){
    if (this != &other) {
        for(int i = 0; i< rows_; ++i){
            delete[] matrix_[i];
        }
        delete[] matrix_;
        
        rows_ = other.rows_;
        cols_ = other.cols_;
        
        matrix_= new double*[rows_];
        
        for(int i = 0 ; i< rows_ ; ++i){
            matrix_[i] = new double[cols_];
        
            for(int j = 0; j<cols_; ++j){
                matrix_[i][j] = other.matrix_[i][j];
            }
        }
    }
    return *this;
}

Matrix Matrix::operator+=(const Matrix &other){
    Matrix result = *this;
    result.SumMatrix(other);
    return result;
}

Matrix Matrix::operator-=(const Matrix &other){
    Matrix result = *this;
    result.SubMatrix(other);
    return result;
}

Matrix Matrix::operator*=(const Matrix &other){
    Matrix result = *this;
    result.MulMatrix(other);
    return result;
}

double* Matrix::operator[](int i_) const{
    if( i_< 0 || i_>=rows_ ){
        throw out_of_range("Index out of bounds");
    }
    return matrix_[i_];
}

int Matrix::GetRows()const{
    return rows_;
}

void Matrix::SetRows(int rows){
    if(rows<=0){
        throw invalid_argument("");
    }
    
    double** new_Matrix= new double*[rows];
    for(int i = 0; i<rows; ++i){
        new_Matrix[i] = new double[cols_];
        for(int j =0; j<cols_; ++j){
            new_Matrix[i][j]=0.0;
        }
    }
    
    int min_R = min(rows, rows_);
    for(int i =0; i<min_R; ++i){
        for(int j =0; j< cols_ ; ++j){
            new_Matrix[i][j] = matrix_[i][j];
        }
    }
    
    for(int i =0; i<rows_; ++i){
        delete[] matrix_[i];
    }
    delete[] matrix_;
    
    
    rows_= rows;
    matrix_=new_Matrix;
    
}


int Matrix::GetCols()const{
    return cols_;
}


void Matrix:: SetCols(int cols){
    if(cols<=0){
        throw invalid_argument("");
    }
    
    double** new_Matrix= new double*[rows_];
    for(int i = 0; i<rows_; ++i){
        new_Matrix[i] = new double[cols];
        for(int j =0; j<cols; ++j){
            new_Matrix[i][j]=0.0;
        }
    }
    
    int min_C = min(cols, cols_);
    for(int i =0; i<rows_; ++i){
        for(int j =0; j< min_C; ++j){
            new_Matrix[i][j] = matrix_[i][j];
        }
    }
    
    for(int i =0; i<rows_; ++i){
        delete[] matrix_[i];
    }
    delete[] matrix_;
    
    
    cols_= cols;
    matrix_=new_Matrix;
    
}
