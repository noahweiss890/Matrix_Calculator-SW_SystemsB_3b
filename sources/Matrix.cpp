#include <iostream>
#include <string.h>
#include <sstream>
#include "Matrix.hpp"

using namespace zich;

namespace zich {

    Matrix::Matrix(const vector<double> &vec, int rows, int cols) {
        if(vec.size() != rows * cols || rows < 0 || cols < 0) {
            throw invalid_argument("not a legal matrix!");
        }
        this->mat = vec;
        this->rows = rows;
        this->columns = cols;
    }

    vector<double> Matrix::getMat() const {
        return this->mat;
    }

    int Matrix::getRows() const {
        return this->rows;
    }

    int Matrix::getColumns() const {
        return this->columns;
    }

    ostream& operator<<(ostream& os, const Matrix &mat) {
        for(unsigned long i = 0; i < mat.rows; i++) {
            for(unsigned long k = 0; k < mat.columns; k++) {
                if(k == 0) {
                    os << "[" << mat.mat[i * (unsigned long)mat.columns + k];
                }
                else {
                    os << " " << mat.mat[i * (unsigned long)mat.columns + k];
                }
            }
            os << "]";
            if(i != mat.rows - 1) {
                os << endl;
            }
        }
        return os;
    }

    istream& operator>>(istream& is, Matrix &mat) {
        mat.mat.clear();
        int rows = 0;
        int columns = 0;
        string str;
        getline(is, str);
        if(str.back() == ',') {
            throw invalid_argument("bad input! 1");
        }
        stringstream ss1(str);
        string line;
        while(getline(ss1, line, ',')) {
            if(line.empty() || (rows > 0 && line[0] != ' ')) {
                throw invalid_argument("bad input! 2");
            }
            rows++;
            stringstream ss2;
            if(rows == 1) {
                ss2 << line;
            }
            else {
                ss2 << line.substr(1);
            }
            string word;
            string last;
            getline(ss2, word, ' ');
            if(word.front() != '[') {
                throw invalid_argument("bad input! 3");
            }
            try {
                mat.mat.push_back(stod(word.substr(1)));
            }
            catch(const std::exception& e) {
                throw invalid_argument("bad input! 4");
            }
            int row_cols = 1;
            while(getline(ss2, word, ' ')) {
                row_cols++;
                if(word.back() != ']') {
                    try {
                        mat.mat.push_back(stod(word));
                    }
                    catch(const std::exception& e) {
                        throw invalid_argument("bad input! 5");
                    }
                }
                last = word;
            }
            if(last.back() != ']') {
                throw invalid_argument("bad input! 6");
            }
            try {
                mat.mat.push_back(stod(last.substr(0, last.size()-1)));
            }
            catch(const std::exception& e) {
                throw invalid_argument("bad input! 7");
            }
            if(rows == 1) {
                    columns = row_cols;
            }
            else {
                if(row_cols != columns) {
                    throw invalid_argument("bad input! 8");
                }
            }
        }
        if(rows > 0 && columns > 0) {
            mat.rows = rows;
            mat.columns = columns;
        }
        return is;
    }
    
    Matrix Matrix::operator-() const {
        vector<double> vec;
        for(unsigned long i  = 0; i < mat.size(); i++) {
            if(mat[i] == 0) {
                vec.push_back(0);
            }
            else {
                vec.push_back(-mat[i]);
            }
        }
        return Matrix(vec, rows, columns);
    }

    Matrix Matrix::operator+() const {
        vector<double> vec;
        for(unsigned long i  = 0; i < mat.size(); i++) {
            vec.push_back(mat[i]);
        }
        return Matrix(vec, rows, columns);
    }

    Matrix Matrix::operator++() {
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i]++;
        }
        return *this;
    }

    Matrix Matrix::operator++(int dummy_flag_for_postfix_increment) {
        Matrix copy = Matrix(this->mat, this->rows, this->columns);
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i]++;
        }
        return copy;
    }

    Matrix Matrix::operator--() {
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i]--;
        }
        return *this;
    }

    Matrix Matrix::operator--(int dummy_flag_for_postfix_decrement) {
        Matrix copy = Matrix(this->mat, this->rows, this->columns);
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i]--;
        }
        return copy;
    }

    void Matrix::operator*=(int n) {
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] *= n;
        }
    }

    void Matrix::operator+=(int n) {
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] += n;
        }
    }

    void Matrix::operator-=(int n) {
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] -= n;
        }
    }

    void Matrix::operator+=(const Matrix &mat) {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] += mat.mat[i];
        }
    }

    void Matrix::operator-=(const Matrix &mat) {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] -= mat.mat[i];
        }
    }

    void Matrix::operator*=(const Matrix &mat) {
        if(this->columns != mat.rows) {
            throw invalid_argument("illegal matrix multiplication!");
        }
        Matrix res = *this * mat;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            this->mat[i] = res.mat[i];
        }
    }

    Matrix operator*(int n, const Matrix &mat) {
        vector<double> vec;
        for(unsigned long i = 0; i < mat.mat.size(); i++) {
            vec.push_back(mat.mat[i]*n);
        }
        return Matrix(vec, mat.rows, mat.columns);
    }

    Matrix Matrix::operator*(int n) {
        vector<double> vec;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            vec.push_back(this->mat[i]*n);
        }
        return Matrix(vec, this->rows, this->columns);
    }

    Matrix Matrix::operator+(const Matrix &mat) {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        vector<double> vec;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            vec.push_back(this->mat[i] + mat.mat[i]);
        }
        return Matrix(vec, this->rows, this->columns);
    }

    Matrix Matrix::operator-(const Matrix &mat) {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        vector<double> vec;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            vec.push_back(this->mat[i] - mat.mat[i]);
        }
        return Matrix(vec, this->rows, this->columns);
    }

    Matrix Matrix::operator*(const Matrix &mat) {
        if(this->columns != mat.rows) {
            throw invalid_argument("illegal matrix multiplication!");
        }
        vector<double> vec;
        double sum = 0;
        for(unsigned long i = 0; i < this->rows; i++) {
            for(unsigned long j = 0; j < mat.columns; j++) {
                sum = 0;
                for(unsigned long k = 0; k < this->columns; k++) {
                    sum += this->mat[i * (unsigned long)this->columns + k] * mat.mat[k * (unsigned long)mat.columns + j];
                }
                vec.push_back(sum);
            }
        }
        return Matrix(vec, this->rows, mat.columns);
    }

    bool Matrix::operator<(const Matrix &mat) const {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        double sum1 = 0;
        double sum2 = 0;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            sum1 += this->mat[i];
        }
        for(unsigned long i = 0; i < mat.mat.size(); i++) {
            sum2 += mat.mat[i];
        }
        return sum1 < sum2;
    }

    bool Matrix::operator>(const Matrix &mat) const {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        double sum1 = 0;
        double sum2 = 0;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            sum1 += this->mat[i];
        }
        for(unsigned long i = 0; i < mat.mat.size(); i++) {
            sum2 += mat.mat[i];
        }
        return sum1 > sum2;
    }

    bool Matrix::operator<=(const Matrix &mat) const {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        double sum1 = 0;
        double sum2 = 0;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            sum1 += this->mat[i];
        }
        for(unsigned long i = 0; i < mat.mat.size(); i++) {
            sum2 += mat.mat[i];
        }
        return sum1 <= sum2;
    }

    bool Matrix::operator>=(const Matrix &mat) const {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        double sum1 = 0;
        double sum2 = 0;
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            sum1 += this->mat[i];
        }
        for(unsigned long i = 0; i < mat.mat.size(); i++) {
            sum2 += mat.mat[i];
        }
        return sum1 >= sum2;
    }

    bool Matrix::operator==(const Matrix &mat) const {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        for(unsigned long i = 0; i < this->mat.size(); i++) {
            if(this->mat[i] != mat.mat[i]) {
                return false;
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix &mat) const {
        if(mat.rows != this->rows || mat.columns != this->columns) {
            throw invalid_argument("matrices must be same dimentions!");
        }
        return !(*this == mat);
    }
}