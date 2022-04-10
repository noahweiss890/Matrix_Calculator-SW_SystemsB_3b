#include <iostream>
#include <vector>

using namespace std;

namespace zich {
    class Matrix {
        vector<double> mat;
        int rows;
        int columns;
        
        public:
            Matrix(const vector<double> &vec, int row, int col);
            vector<double> getMat() const;
            int getRows() const;
            int getColumns() const;
            friend ostream& operator<<(ostream& os, const Matrix &mat);
            friend istream& operator>>(istream& is, Matrix &mat);
            Matrix operator-() const;
            Matrix operator+() const;
            Matrix operator++();
            Matrix operator++(int dummy_flag_for_postfix_increment);
            Matrix operator--();
            Matrix operator--(int dummy_flag_for_postfix_decrement);
            void operator*=(int n);
            void operator+=(int n);
            void operator-=(int n);
            void operator+=(const Matrix &mat);
            void operator-=(const Matrix &mat);
            void operator*=(const Matrix &mat);
            friend Matrix operator*(int n, const Matrix &mat);
            Matrix operator*(int n);
            Matrix operator+(const Matrix &mat);
            Matrix operator-(const Matrix &mat);
            Matrix operator*(const Matrix &mat);
            bool operator<(const Matrix &mat) const;
            bool operator>(const Matrix &mat) const;
            bool operator<=(const Matrix &mat) const;
            bool operator>=(const Matrix &mat) const;
            bool operator==(const Matrix &mat) const;
            bool operator!=(const Matrix &mat) const;
    };
}