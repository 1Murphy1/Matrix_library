#include <iostream>
#include "matrix_oop.h" 

using namespace std;

int main() {
   try {
        Matrix m1(2, 3);
        for(int i =0; i< m1.GetRows(); ++i){
            for(int j =0; j<m1.GetCols(); ++j){
                m1[i][j] = i * m1.GetCols()+j+1;
            }
        }
        cout<<"Matrix1: "<<endl;
        m1.PrintMatrix();
        cout << endl;
        

        Matrix m2(2, 3);
        for(int i=0; i<m2.GetRows(); ++i){
            for(int j=0; j<m2.GetCols(); ++j){
                m2[i][j] = i*m2.GetCols()+j+1;
            }
        }
        cout<<"Matrix2: "<<endl;
        m2.PrintMatrix();
        cout << endl;
        
        
        Matrix m3(3,2);
        m3[0][0]=11;
        m3[0][1]=12;
        m3[1][0]=13;
        m3[1][1]=14;
        m3[2][0]=15;
        m3[2][1]=16;
        
        cout<<"Matrix3: "<<endl;
        m3.PrintMatrix();
        cout<<endl;
        
        Matrix m4(2,3);
        m4[0][0]= 1;
        m4[0][1]= 2;
        m4[0][2]= 3;
        m4[1][0]= 4;
        m4[1][1]= 5;
        m4[1][2]= 6;
        
        cout<<"Matrix4: "<<endl;
        m4.PrintMatrix();
        cout<<endl;
        
        Matrix m5(3, 3);
        for(int i=0; i<m5.GetRows(); ++i){
            for(int j=0; j<m5.GetCols(); ++j){
                m5[i][j] = i*m5.GetCols()+j+1;
            }
        }
        cout<<"Matrix5: "<<endl;
        m5.PrintMatrix();
        cout << endl;
        
        int countPassedTests = 0;
        
        // Сложение матриц
        m1.SumMatrix(m2);
        cout << "Sum of matrices:" << endl;
        m1.PrintMatrix();
        cout << endl;
        
        if (m1 == m2) {
            std::cout << "\nPASSED matrix summation test." << std::endl;
            countPassedTests++;
        } else {
            std::cout << "\nFAILED matrix summation test." << std::endl;
        }
        cout<<endl;

        //Вычитание матриц
        m1.SubMatrix(m2);
        cout << "Subtraction of matrices:" << endl;
        m1.PrintMatrix();
        cout << endl;
        
         // Умножение на число
        double num = 4.0;
        m1.MulNumber(num);
        cout << "Multiplication by a number:" << endl;
        m1.PrintMatrix();
        cout << endl;
        
        //Умножение матриц
        m3.MulMatrix(m4);
        cout<<"Multiplication of matrices: "<< endl;
        m3.PrintMatrix();
        cout<<endl;
        
        
        Matrix t = m1.Transpose();
        cout<<"Transposed result: "<<endl;
        t.PrintMatrix();
        
        Matrix inv = m5.InverseMatrix();
        cout<<"Inverse: "<<endl;
        inv.PrintMatrix();

    } catch(const invalid_argument& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
