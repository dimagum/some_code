#pragma once
#include <cmath>
#include <iomanip>
#include "Complex.h"

namespace linalg {
    template<class T = double>
    class Matrix {
        T *m_ptr;
        unsigned m_rows;
        unsigned m_columns;
    public:
        Matrix(unsigned r = 0, unsigned c = 1) {
            m_rows = r;
            m_columns = c;

            m_ptr = new T[r * c];

            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    m_ptr[i * m_columns + j] = 0;
                }
            }
        }

        Matrix(const Matrix<T> &other) {
            m_rows = other.m_rows;
            m_columns = other.m_columns;

            m_ptr = new T[other.m_rows * other.m_columns];

            for (int i = 0; i < other.m_rows; ++i) {
                for (int j = 0; j < other.m_columns; ++j) {
                    m_ptr[i * m_columns + j] = other.m_ptr[i * m_columns + j];
                }
            }
        }

        Matrix(Matrix<T> &&other) { // && - r-value ссылка;
            m_rows = other.m_rows;
            m_columns = other.m_columns;
            m_ptr = other.m_ptr;

            other.m_ptr = nullptr;
            other.m_rows = 0;
            other.m_columns = 0;
        }

        Matrix(const std::initializer_list<T> &lst) {
            m_rows = lst.size();
            m_columns = 1;
            m_ptr = new T[m_rows * m_columns];
            for (int i = 0; i < m_rows; ++i) {
                m_ptr[i * m_columns + 0] = *(lst.begin() + i);
            }
        }

        Matrix(const std::initializer_list<std::initializer_list<T>> &lst) {
            m_rows = lst.size();
            m_columns = lst.begin()->size();

            m_ptr = new T[m_rows * m_columns];
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_columns; ++j) {
                    m_ptr[i * m_columns + j] = *((lst.begin() + i)->begin() + j);
                }
            }

        }

        ~Matrix() {
            delete[] m_ptr;
        }

        unsigned rows() {
            return m_rows;
        }

        unsigned rows() const {
            return m_rows;
        }

        unsigned columns() {
            return m_columns;
        }

        unsigned columns() const {
            return m_columns;
        }

        // m(1, 1);
        T &operator()(int i, int j) {
            if (i >= m_rows || j >= m_columns) {
                throw std::logic_error("index out of range\n");
            }
            return m_ptr[i * m_columns + j];
        }

        const T &operator()(int i, int j) const {
            if (i >= m_rows || j >= m_columns) {
                throw std::logic_error("index out of range\n");
            }
            return m_ptr[i * m_columns + j];
        }

        Matrix<T> &operator=(const Matrix<T> &rhs) {
            if (this == &rhs) {
                return *this;
            }

            delete[] m_ptr;

            m_rows = rhs.m_rows;
            m_columns = rhs.m_columns;

            m_ptr = new T[m_rows * m_columns];
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_columns; ++j) {
                    m_ptr[i * m_columns + j] = rhs.m_ptr[i * m_columns + j];
                }
            }

            return *this;
        }

        Matrix<T> &operator=(Matrix<T> &&rhs) noexcept {
            if (this == &rhs) {
                return *this;
            }

            delete[] m_ptr;

            m_rows = rhs.m_rows;
            m_columns = rhs.m_columns;

            m_ptr = rhs.m_ptr;

            rhs.m_ptr = nullptr;
            rhs.m_rows = 0;
            rhs.m_columns = 0;

            return *this;
        }


        Matrix<T> &operator+=(const Matrix<T> &rhs) {
            if (m_rows != rhs.m_rows || m_columns != rhs.m_columns) {
                throw std::logic_error("dimensions are not equal\n");
            }
            for (int i = 0; i < rhs.m_rows; ++i) {
                for (int j = 0; j < rhs.m_columns; ++j) {
                    this->m_ptr[i * m_columns + j] += rhs.m_ptr[i * m_columns + j];
                }
            }
            return *this;
        }

        friend Matrix<T> operator+(Matrix<T> lhs, const Matrix<T> &rhs) {
            lhs += rhs;
            return lhs;
        }
        // m = m1 + m2;

        Matrix<T> &operator-=(const Matrix<T> &rhs) {
            if (m_rows != rhs.m_rows || m_columns != rhs.m_columns) {
                throw std::logic_error("dimensions are not equal\n");
            }
            for (int i = 0; i < rhs.m_rows; ++i) {
                for (int j = 0; j < rhs.m_columns; ++j) {
                    this->m_ptr[i * m_columns + j] -= rhs.m_ptr[i * m_columns + j];
                }
            }
            return *this;
        }

        friend Matrix<T> operator-(Matrix<T> lhs, const Matrix<T> &rhs) {
            lhs -= rhs;
            return lhs;
        }

        Matrix<T> &operator*=(T rhs) {
            for (int i = 0; i < rhs.m_rows; ++i) {
                for (int j = 0; j < rhs.m_columns; ++j) {
                    this->m_ptr[i * m_columns + j] *= rhs;
                }
            }
            return *this;
        }

        friend Matrix<T> operator*(Matrix<T> lhs, T rhs) {
            lhs *= rhs;
            return lhs;
        }

        friend Matrix<T> operator*(T lhs, Matrix<T> rhs) {
            rhs *= lhs;
            return rhs;
        }

        friend Matrix<T> operator*(Matrix<T> lhs, const Matrix<T> &rhs) {
            if (lhs.m_columns != rhs.m_rows) {
                throw std::logic_error("dimensions are not equal\n");
            }
            Matrix<T> tmp(lhs.m_rows, rhs.m_columns);
            for (int i = 0; i < lhs.m_rows; ++i) {
                for (int j = 0; j < rhs.m_columns; ++j) {
                    for (int k = 0; k < lhs.m_columns; ++k) {
                        tmp(i, j) += lhs.m_ptr[i * lhs.m_columns + k] * rhs.m_ptr[k * rhs.m_columns + j];
                    }
                }
            }
            return tmp;
        }

        friend std::ostream &operator<<(std::ostream &out, const Matrix<T> &m) {
            for (int i = 0; i < m.m_rows; ++i) {
                out << '|';
                for (int j = 0; j < m.m_columns; ++j) {
                    out << std::scientific << std::setprecision(4) << " " << std::right << std::setw(7) << m(i, j)
                        << " ";
                }
                out << "|\n";
            }
            return out;
        }

        friend void getMat(const Matrix<T> &m, Matrix<T> &t, int p, int q) {
            unsigned n = m.m_rows;
            int i = 0, j = 0;

            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    if (row != p && col != q) {
                        t(i, j++) = m(row, col);
                        if (j == n - 1) {
                            j = 0;
                            i++;
                        }
                    }
                }
            }
        }

        T det() const {
            if (m_rows != m_columns) {
                throw std::logic_error("not a square matrix\n");
            }

            if (m_rows == 1) {
                return (*this)(0, 0);
            }

            T d = 0;
            int sgn = 1;
            Matrix<T> t(m_rows - 1, m_rows - 1);
            for (int i = 0; i < m_rows; ++i) {
                getMat(*this, t, 0, i);
                d += sgn * (*this)(0, i) * t.det();
                sgn *= -1;
            }

            return d;
        }

        double norm() {
            double n = 0;
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_columns; ++j) {
                    n += (*this)(i, j) * (*this)(i, j);
                }
            }

            return sqrt(n);
        }

        double trace() {
            double t = 0;

            for (int i = 0; i < std::min(m_rows, m_columns); ++i) {
                t += m_ptr[i * m_columns + i];
            }

            return t;
        }

        friend Matrix<T> transpose(Matrix<T> other) {
            Matrix<T> tmp(other.m_columns, other.m_rows);
            for (int i = 0; i < other.m_columns; ++i) {
                for (int j = 0; j < other.m_rows; ++j) {
                    tmp(i, j) = other(j, i);
                }
            }

            return tmp;
        }

        friend Matrix<T> pow(const Matrix<T> &m, unsigned p) {
            Matrix<T> tmp(m);

            for (int i = 0; i < p - 1; ++i) {
                tmp = tmp * m;
            }

            return tmp;
        }

        // friend void row_swap(Matrix<> & to_swap, int r1, int r2, int c) {
        //     for (int i = 0; i < c; ++i) {
        //         std::swap(to_swap(r1, i), to_swap(r2, i));
        //     }
        // }

        int rank() {
            Matrix<> tmp(m_rows, m_columns);

            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_columns; ++j) {
                    tmp(i, j) = (double) (*this)(i, j);
                }
            }

            int r = std::min(m_rows, m_columns);

            for (int row = 0; row < r; ++row) {
                if (tmp(row, row)) {
                    for (int col = 0; col < m_rows; ++col) {
                        if (col != row) {
                            double m = (double) tmp(col, row) / tmp(row, row);
                            for (int i = 0; i < r; ++i) {
                                tmp(col, i) -= m * tmp(row, i);
                            }
                        }
                    }
                } else {
                    bool to_reduce = true;
                    for (int i = row + 1; i < m_rows; ++i) {
                        if (tmp(i, row)) {
                            // row_swap(tmp, row, i, r);
                            for (int k = 0; i < r; ++i) {
                                std::swap(tmp(row, k), tmp(i, k));
                            }
                            to_reduce = false;
                            break;
                        }
                    }

                    if (to_reduce) {
                        r--;
                        for (int i = 0; i < m_rows; ++i) {
                            tmp(i, row) = tmp(i, r);
                        }
                    }
                    row--;
                }
            }

            return r;
        }

        friend void get_adj(const Matrix<T> &mat, Matrix<> &res) {
            if (mat.m_rows != res.m_rows || mat.m_columns != res.m_columns) {
                throw std::logic_error("matrix dimensions are not matching\n");
            }
            if (mat.m_rows != res.m_columns) {
                throw std::logic_error("not a square matrix\n");
            }
            T mat_det = mat.det();
            for (int i = 0; i < res.m_rows; ++i) {
                for (int j = 0; j < res.m_columns; ++j) {
                    Matrix<T> tmp(mat.m_rows - 1, mat.m_rows - 1);
                    getMat(mat, tmp, i, j);
                    int sgn = (i + j) % 2 == 0 ? 1 : -1;
                    res(j, i) = (double) sgn * tmp.det() / mat_det;
                }
            }
        }

        friend Matrix<> inv(const Matrix<T> &m) {
            if (m.det() == 0) {
                throw std::logic_error("matrix is singular\n");
            }

            Matrix<> res(m.m_rows, m.m_columns);

            get_adj(m, res);

            return res;
        }
    };
}