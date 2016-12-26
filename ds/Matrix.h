/*
 * @Author: Igor Tymchyshyn
 *			Taras Shevchenko National University of Kyiv
 *          Kyiv, Ukraine
 */


#pragma once

#ifndef _DS_MATRIX_
#define _DS_MATRIX_


#if !defined(_MSC_VER) && !defined(__GNUC__)
#error You need to compile with MSVC or GNU compiler
#endif  // !defined(_MSC_VER) && !defined(__GNUC__)

#include "../typedefs/typedefgeneral.h"

#define _DS_MATRIX_SUPPORT_ERASE 0


#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR
#include <vector>
#endif

namespace ds {

#ifndef _DS_MATRIX_NOT_USE_STANDART_VALUES_DEF

#define ZERO static_cast<T>(0)
#define ONE static_cast<T>(1)
#define DEFAULT_EPS static_cast<T>(0.00001)

#endif // #ifndef _DS_MATRIX_NOT_USE_STANDART_VALUES_DEF

#if _DS_MATRIX_SUPPORT_ERASE
#define DEFAULT_AREA_KOEF_FOR_RESIZE 0.75
#endif

    enum ROW_COL {
        ROW, COLUMN
    };

    template <class T>
    class Matrix
    {
    protected:
        size_t rows;
        size_t cols;
        T ** data;

    private:
#if _DS_MATRIX_SUPPORT_ERASE
        double areaKoefForResize;
#endif
        T eps;

    protected:
        T** copyData() const;
        void destroy();

        static T ** create_array_by_size(size_t n, size_t m);
        static T ** create_array_with_val(size_t n, size_t m, const T& val);
        static T ** create_array_by_two_dim_array(size_t n, size_t m, const T* const * matrix);
        static T ** create_array_by_array(size_t n, const T* array_in, ROW_COL row_col = COLUMN);

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR
        static T ** create_array_by_std_vector_vector(const std::vector< std::vector<T> >& matrix);
        static T ** create_array_by_std_vector(const std::vector<T>& vector_in, ROW_COL row_col = COLUMN);
#endif // _DS_MATRIX_SUPPORT_STL_VECTOR

        template <size_t n, size_t m>
        static T ** create_array_by_two_dim_array(const T (&matrix)[n][m]);

        struct MatrixData {
            size_t rows;
            size_t cols;
            T ** data;
        };

    public:

        class iterator {
            size_t row;
            size_t col;
            Matrix<T> * matrix;

        public:
            iterator();
            iterator(const iterator& iter);
            iterator(Matrix * matr, size_t n, size_t m);
            ~iterator();

#if !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))
            explicit operator T*();
            explicit operator const T*() const;
#endif // !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))

            T* cast_to_ptr();
            const T* cast_to_ptr() const;

            iterator& operator=(const iterator& iter);
            bool operator==(const iterator& iter) const;
            bool operator!=(const iterator& iter) const;
            iterator& operator++();
            iterator operator++(int);
            iterator& operator--();
            iterator operator--(int);
            iterator operator+(size_t i) const;
            iterator operator-(size_t i) const;
            iterator& operator+=(size_t i);
            iterator& operator-=(size_t i);
            T& operator*();
            const T& operator*() const;
            T& operator->();
            const T& operator->() const;
        };

        class const_iterator {
            size_t row;
            size_t col;
            const Matrix<T> * matrix;

        public:
            const_iterator();
            const_iterator(const iterator& iter);
            const_iterator(const const_iterator& iter);
            const_iterator(const Matrix * matr, size_t n, size_t m);
            ~const_iterator();

#if !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))
            explicit operator const T*() const;
#endif // !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))

            const T* cast_to_ptr() const;

#if defined(_MSC_VER) || defined(__GNUC__)
            operator const iterator() const;
#endif // _MSC_VER

            const_iterator& operator=(const const_iterator& iter);
            bool operator==(const const_iterator& iter) const;
            bool operator!=(const const_iterator& iter) const;
            const_iterator& operator++();
            const_iterator operator++(int);
            const_iterator& operator--();
            const_iterator operator--(int);
            const_iterator operator+(size_t i) const;
            const_iterator operator-(size_t i) const;
            const_iterator& operator+=(size_t i);
            const_iterator& operator-=(size_t i);
            const T& operator*() const;
            const T& operator->() const;
        };


        Matrix();
        Matrix(size_t n, size_t m);
        Matrix(size_t n);
        Matrix(const Matrix<T>& matrix);
#if _MSC_VER >= 1700
        Matrix(Matrix<T>&& matrix);
#endif  // #if _MSC_VER >= 1700
        Matrix(const MatrixData& matrixData);

        template <class S>
        friend void swap(Matrix<S>& matrix1, Matrix<S>& matrix2);

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR
        explicit Matrix(const std::vector<T>& vector_);
        explicit Matrix(const std::vector< std::vector<T> >& vector_);
#endif // _DS_MATRIX_SUPPORT_STL_VECTOR

        virtual ~Matrix();

        static MatrixData matrixWithValue(size_t n, size_t m, const T& val);
        static MatrixData vectorWithValue(size_t n, const T& val);
        static MatrixData matrixByArray(const T* const * matrix, size_t n, size_t m);
        static MatrixData vectorByArray(const T* matrix, size_t n, ROW_COL row_col = COLUMN);

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR
        static MatrixData matrixByStdVector(const std::vector<T>& vector_, ROW_COL row_col = COLUMN);
        static MatrixData matrixByStdVectorVector(const std::vector< std::vector<T> >& vector_);
#endif // _DS_MATRIX_SUPPORT_STL_VECTOR

        template <size_t n, size_t m>
        static MatrixData matrixByArray(const T (&matrix)[n][m]);

        void resize(size_t n, size_t m);
        void resize(size_t n, size_t m, const T& val);

        static Matrix<T> createZeroMatrix(size_t n, size_t m);
        static Matrix<T> createIdMatrix(size_t n);

        size_t size() const;
        size_t rowsCount() const;
        size_t colsCount() const;
        Matrix<T> submatrix(size_t n_from, size_t n_to, size_t m_from, size_t m_to) const;

        Matrix<T>& concatRowsRight(const Matrix<T>& rightMatrix);
        Matrix<T>& concatRowsLeft(const Matrix<T>& leftMatrix);
        Matrix<T>& concatColsDown(const Matrix<T>& downMatrix);
        Matrix<T>& concatColsUp(const Matrix<T>& upperMatrix);

        template <class S>
        friend Matrix<S> concatRows(const Matrix<S>& leftMatrix, const Matrix<S>& rightMatrix);

        template <class S>
        friend Matrix<S> concatCols(const Matrix<S>& upperMatrix, const Matrix<S>& downMatrix);

        Matrix<T>& setVal(const T& val);
        Matrix<T>& transpose();
        Matrix<T>& swap_rows(size_t i1, size_t i2);
        Matrix<T>& swap_cols(size_t j1, size_t j2);
        Matrix<T>& to_zero();

        //Will be implemented in future;
        /*Matrix<T>& removeRows(size_t from, size_t to = from + 1);
        Matrix<T>& removeCols(size_t from, size_t to = from + 1);*/

        Matrix<T>& setRow(size_t i, const T* row_);
        Matrix<T>& setColumn(size_t i, const T* column_);
        Matrix<T>& setEps(const T& val);

#if _DS_MATRIX_SUPPORT_ERASE
        Matrix<T>& setKoefForResize(const T& val);
#endif // _DS_MATRIX_SUPPORT_ERASE

        Matrix<T>& to_upper_triangle();
        Matrix<T>& to_lower_triangle();
        Matrix<T>& inverse();

        template <class S>
        friend Matrix<S> to_upper_triangle(const Matrix<S>& matrix);

        template <class S>
        friend Matrix<S> to_lower_triangle(const Matrix<S>& matrix);

        template <class S>
        friend Matrix<S> inverse(const Matrix<S>& matrix);

        template <class S>
        friend Matrix<S> solveSystem_GaussMethod(Matrix<S> matrix, const Matrix<S>& freeColumn);

        template <class S>
        friend Matrix<S> transpose(const Matrix<S>& matrix);

        template <class S>
        friend S diag_sum(const Matrix<S>& matrix);

        template <class S>
        friend S diag_prod(const Matrix<S>& matrix);

        template <class S>
        friend S det(const Matrix<S>& matrix);

        Matrix<T> row(size_t i) const;
        Matrix<T> column(size_t j) const;
        T* row_array(size_t i) const;
        const T* crow_array(size_t i) const;
        T* column_array(size_t j) const;

#if !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))

        explicit operator T**() const;
        explicit operator T*() const;

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR
        explicit operator std::vector<T>() const;
        explicit operator std::vector< std::vector<T> >() const;
#endif	// _DS_MATRIX_SUPPORT_STL_VECTOR

#endif // !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))

        T** cast_to_two_dim_array() const;
        T* cast_to_one_dim_array() const;

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR
        std::vector<T> cast_to_std_vector() const;
        std::vector< std::vector<T> > cast_to_std_vector_vector() const;
#endif // _DS_MATRIX_SUPPORT_STL_VECTOR

        Matrix<T>& operator=(const Matrix<T>& matrix);
#if _MSC_VER >= 1700
        Matrix<T>& operator=(Matrix<T>&& matrix);
#endif  // _MSC_VER >= 1700
        Matrix<T>& operator=(
#if defined(__GNUC__)
							const Matrix<T>::MatrixData& matrixData
#else
							typename const Matrix<T>::MatrixData& matrixData
#endif
							);
        bool operator==(const Matrix<T>& matrix) const;
        bool operator!=(const Matrix<T>& matrix) const;
        T*& operator[](size_t i);
        const T* operator[](size_t i) const;
        Matrix<T> operator+(const T& val) const;
        Matrix<T> operator-(const T& val) const;
        Matrix<T>& operator+=(const Matrix& matrix);
        Matrix<T>& operator-=(const Matrix& matrix);
        Matrix<T>& operator+=(const T& val);
        Matrix<T>& operator-=(const T& val);
        Matrix<T> operator*(const T& val) const;
        Matrix<T> operator/(const T& val) const;
        Matrix<T> operator%(const T& val) const;
        Matrix<T>& operator*=(const T& val);
        Matrix<T>& operator/=(const T& val);
        Matrix<T>& operator%=(const T& val);
        Matrix<T>& operator*=(const Matrix<T>& matrix);
        Matrix<T>& operator++();
        Matrix<T> operator++(int);
        Matrix<T>& operator--();
        Matrix<T> operator--(int);
        Matrix<T> operator-() const;

        template <class S>
        friend std::ostream& operator<<(std::ostream& stream, const Matrix<S>& matrix);

        template <class S>
        friend Matrix<S> operator+(const Matrix<S>& matrix1, const Matrix<S>& matrix2);

        template <class S>
        friend Matrix<S> operator-(const Matrix<S>& matrix1, const Matrix<S>& matrix2);

        template <class S>
        friend Matrix<S> operator*(const Matrix<S>& matrix1, const Matrix<S>& matrix2);

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR

        template <class S>
        friend Matrix<S> operator+(const Matrix<S>& matrix, const std::vector<S>& vector_);

        template <class S>
        friend Matrix<S> operator-(const Matrix<S>& matrix, const std::vector<S>& vector_);

        template <class S>
        friend Matrix<S> operator*(const Matrix<S>& matrix, const std::vector<S>& vector_);

        template <class S>
        friend Matrix<S> operator+(const std::vector<S>& vector_, const Matrix<S>& matrix);

        template <class S>
        friend Matrix<S> operator-(const std::vector<S>& vector_, const Matrix<S>& matrix);

        template <class S>
        friend Matrix<S> operator*(const std::vector<S>& vector_, const Matrix<S>& matrix);

#endif // _DS_MATRIX_SUPPORT_STL_VECTOR

        template <class S>
        friend Matrix<S> operator*(const S& val, const Matrix<S>& matrix);

        template <class S>
        friend Matrix<S> operator+(const S& val, const Matrix<S>& matrix);

        template <class S>
        friend Matrix<S> operator-(const S& val, const Matrix<S>& matrix);

        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;
        iterator end();
        const_iterator end() const;
        const_iterator cend() const;
    };

    template<class T>
    inline Matrix<T>::Matrix() : rows(0)
                               , cols(0)
                               , eps(DEFAULT_EPS)
#if _DS_MATRIX_SUPPORT_ERASE
                               , areaKoefForResize(DEFAULT_AREA_KOEF_FOR_RESIZE)
#endif // _DS_MATRIX_SUPPORT_ERASE
    {
        data = 0;
    }

    template<class T>
    inline Matrix<T>::Matrix(size_t n, size_t m) : rows(n)
                                                 , cols(m)
                                                 , eps(DEFAULT_EPS)
#if _DS_MATRIX_SUPPORT_ERASE
                                                 , areaKoefForResize(DEFAULT_AREA_KOEF_FOR_RESIZE)
#endif // _DS_MATRIX_SUPPORT_ERASE
    {
        data = create_array_by_size(n, m);
    }

    template<class T>
    inline Matrix<T>::Matrix(size_t n) : rows(n)
                                       , cols(n)
                                       , eps(DEFAULT_EPS)
#if _DS_MATRIX_SUPPORT_ERASE
                                       , areaKoefForResize(DEFAULT_AREA_KOEF_FOR_RESIZE)
#endif // _DS_MATRIX_SUPPORT_ERASE
    {
        data = create_array_by_size(n, n);
    }

    template<class T>
    Matrix<T>::Matrix(const Matrix<T> & matrix)
    {
        rows = matrix.rows;
        cols = matrix.cols;
        eps = matrix.eps;
#if _DS_MATRIX_SUPPORT_ERASE
        areaKoefForResize = matrix.areaKoefForResize;
#endif // _DS_MATRIX_SUPPORT_ERASE
        data = matrix.copyData();
    }

#if _MSC_VER >= 1700
    template<class T>
    Matrix<T>::Matrix(Matrix<T>&& matrix) : data(0)
    {
        swap(*this, matrix);
    }
#endif  // _MSC_VER >= 1700

    template<class T>
    Matrix<T>::Matrix(const typename Matrix<T>::MatrixData & matrix_) :
                                                              eps(DEFAULT_EPS)
#if _DS_MATRIX_SUPPORT_ERASE
                                                            , areaKoefForResize(DEFAULT_AREA_KOEF_FOR_RESIZE)
#endif // _DS_MATRIX_SUPPORT_ERASE
    {
        rows = matrix_.rows;
        cols = matrix_.cols;
        data = matrix_.data;
    }

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR

    template<class T>
    Matrix<T>::Matrix(const std::vector<T>& vector_) : eps(DEFAULT_EPS)
#if _DS_MATRIX_SUPPORT_ERASE
                                                    , areaKoefForResize(DEFAULT_AREA_KOEF_FOR_RESIZE)
#endif // _DS_MATRIX_SUPPORT_ERASE
    {
        data = 0;
        *this = matrixByStdVector(vector_);
    }

    template<class T>
    Matrix<T>::Matrix(const std::vector< std::vector<T> >& vector_) : eps(DEFAULT_EPS)
#if _DS_MATRIX_SUPPORT_ERASE
                                                    , areaKoefForResize(DEFAULT_AREA_KOEF_FOR_RESIZE)
#endif // _DS_MATRIX_SUPPORT_ERASE
    {
        *this = matrixByStdVectorVector(vector_);
    }

#endif // _DS_MATRIX_SUPPORT_STL_VECTOR

    template<class T>
    Matrix<T>::~Matrix()
    {
        destroy();
    }

    template <class S>
    void swap(Matrix<S>& matrix1, Matrix<S>& matrix2)
    {
        size_t t = matrix1.rows;
        matrix1.rows = matrix2.rows;
        matrix2.rows = t;

        t = matrix1.cols;
        matrix1.cols = matrix2.cols;
        matrix2.cols = t;

        S ** _data = matrix1.data;
        matrix1.data = matrix2.data;
        matrix2.data = _data;

#if _DS_MATRIX_SUPPORT_ERASE
        double _areaKoefForResize = matrix1.areaKoefForResize;
        matrix1.areaKoefForResize = matrix2.areaKoefForResize;
        matrix2.areaKoefForResize = _areaKoefForResize;
#endif
        S _eps = matrix1.eps;
        matrix1.eps = matrix2.eps;
        matrix2.eps = _eps;
    }

    template<class T>
    typename Matrix<T>::MatrixData Matrix<T>::matrixWithValue(size_t n, size_t m, const T& val) {
        MatrixData matrix_;

        matrix_.rows = n;
        matrix_.cols = m;
        matrix_.data = create_array_with_val(n, m, val);

        return matrix_;
    }

    template<class T>
    typename Matrix<T>::MatrixData Matrix<T>::vectorWithValue(size_t n, const T& val) {
        Matrix<T>::MatrixData matrix_;

        matrix_.rows = n;
        matrix_.cols = 1;
        matrix_.data = create_array_with_val(n, 1, val);

        return matrix_;
    }

    template<class T>
    typename Matrix<T>::MatrixData Matrix<T>::matrixByArray(const T* const * matrix, size_t n, size_t m) {
        Matrix<T>::MatrixData matrix_;

        matrix_.rows = n;
        matrix_.cols = m;
        matrix_.data = create_array_by_two_dim_array(n, m, matrix);

        return matrix_;
    }

    template<class T>
    typename Matrix<T>::MatrixData Matrix<T>::vectorByArray(const T* matrix, size_t n, ROW_COL row_col) {
        Matrix<T>::MatrixData matrix_;

        matrix_.rows = n;
        matrix_.cols = 1;
        matrix_.data = create_array_by_array(n, matrix, row_col);

        return matrix_;
    }

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR
    template<class T>
    typename Matrix<T>::MatrixData Matrix<T>::matrixByStdVector(const std::vector<T>& vector_, ROW_COL row_col) {
        Matrix<T>::MatrixData matrix_;

        if (row_col == COLUMN) {
            matrix_.rows = vector_.size();
            matrix_.cols = 1;
            matrix_.data = create_array_by_size(matrix_.rows, matrix_.cols);

            for (size_t i = 0; i < matrix_.rows; ++i) {
                matrix_.data[i][0] = vector_[i];
            }
        }
        else {
            matrix_.rows = 1;
            matrix_.cols = vector_.size();
            matrix_.data = create_array_by_size(matrix_.rows, matrix_.cols);

            T * data_0 = matrix_.data[0] - 1;
            for (size_t i = 0; i < matrix_.rows; ++i) {
                *(++data_0) = vector_[i];
            }
        }

        return matrix_;
    }

    template<class T>
    typename Matrix<T>::MatrixData Matrix<T>::matrixByStdVectorVector(const std::vector< std::vector<T> >& vector_) {
        Matrix<T>::MatrixData matrix_;

        matrix_.rows = vector_.size();
        matrix_.cols = vector_[0].size();
        matrix_.data = create_array_by_size(matrix_.rows, matrix_.cols);

        for (size_t i = 0; i < matrix_.rows; ++i) {
            for (size_t j = 0; j < matrix_.cols; ++j) {
                matrix_.data[i][j] = vector_[i][j];
            }
        }

        return matrix_;
    }
#endif // _DS_MATRIX_SUPPORT_STL_VECTOR

    template <class T>
    template <size_t n, size_t m>
    typename Matrix<T>::MatrixData Matrix<T>::matrixByArray(const T(&matrix)[n][m]) {
        Matrix<T>::MatrixData matrix_;

        matrix_.rows = n;
        matrix_.cols = m;
        matrix_.data = create_array_by_two_dim_array(matrix);

        return matrix_;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T> & matrix)
    {
        rows = matrix.rows;
        cols = matrix.cols;
        eps = matrix.eps;
#if _DS_MATRIX_SUPPORT_ERASE
        areaKoefForResize = matrix.areaKoefForResize;
#endif // _DS_MATRIX_SUPPORT_ERASE
        data = matrix.copyData();

        return *this;
    }

#if _MSC_VER >= 1700
    template<class T>
    Matrix<T>& Matrix<T>::operator=(Matrix<T>&& matrix)
    {
        swap(*this, matrix);

        return *this;
    }
#endif  // _MSC_VER >= 1700

	template<class T>
    Matrix<T>& Matrix<T>::operator=(
#if defined(__GNUC__)
									const Matrix<T>::MatrixData& matrixData
#else
									typename const Matrix<T>::MatrixData& matrixData
#endif
									) {

		destroy();

		rows = matrixData.rows;
		cols = matrixData.cols;
		data = matrixData.data;

		return *this;
	}

    template<class T>
    bool Matrix<T>::operator==(const Matrix<T>& matrix) const
    {
        if (rows != matrix.rows || cols != matrix.cols) {
            return false;
        }

        for (size_t i = 0; i < rows; ++i) {
            T * data_i = data[i] - 1;
            T * matr_data_i = matrix.data[i] - 1;
            for (size_t j = 0; j < cols; ++j) {
                if (*(--data) - *(--matrix) + eps < ZERO || *matrix - *data > eps) {
                    return false;
                }
            }
        }

        return true;
    }

    template<class T>
    inline bool Matrix<T>::operator!=(const Matrix<T>& matrix) const
    {
        return !(*this == matrix);
    }

    template<class T>
    inline T* & Matrix<T>::operator[](size_t i)
    {
        return data[i];
    }

    template<class T>
    inline const T* Matrix<T>::operator[](size_t i) const
    {
        return data[i];
    }

    template<class T>
    Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2)
    {
        Matrix<T> result(matrix1.rows, matrix1.cols);
        for (size_t i = 0; i < matrix1.rows; ++i) {
            for (size_t j = 0; j < matrix1.cols; ++j) {
                result.data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
            }
        }
        return result;
    }

    template<class T>
    Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2)
    {
        Matrix<T> result(matrix1.rows, matrix1.cols);

        for (size_t i = 0; i < matrix1.rows; ++i) {
            for (size_t j = 0; j < matrix1.cols; ++j) {
                result.data[i][j] = matrix1.data[i][j] - matrix2.data[i][j];
            }
        }

        return result;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator+(const T & val) const
    {
        Matrix<T> matrix(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                matrix.data[i][j] = data[i][j] + val;
            }
        }

        return matrix;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator-(const T & val) const
    {
        Matrix<T> matrix(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                matrix.data[i][j] = data[i][j] - val;
            }
        }

        return matrix;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::operator+=(const Matrix & matrix)
    {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] += matrix.data[i][j];
            }
        }
        return *this;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::operator-=(const Matrix & matrix)
    {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] -= matrix.data[i][j];
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator+=(const T & val)
    {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] += val;
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator-=(const T & val)
    {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] -= val;
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator*(const T & val) const
    {
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] * val;
            }
        }
        return result;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator/(const T & val) const
    {
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] / val;
            }
        }
        return result;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator%(const T & val) const
    {
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] % val;
            }
        }
        return result;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator*=(const T & val)
    {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] *= val;
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator/=(const T & val)
    {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] /= val;
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator%=(const T & val)
    {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] %= val;
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T> operator*(const Matrix<T>& matrix1, const Matrix<T>& matrix2)
    {
        Matrix<T> product(matrix1.rows, matrix2.cols);

        for (size_t i = 0; i < matrix1.rows; ++i) {
            for (size_t j = 0; j < matrix2.cols; ++j) {
                product.data[i][j] = 0;
                for (size_t k = 0; k < matrix1.cols; ++k) {
                    product.data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
                }
            }
        }

        return product;
    }

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR

    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix, const std::vector<T>& vector_) {
        Matrix<T> result(matrix.rows, matrix.cols);

        if (matrix.rows == 1) {
            T * data_0 = result.data[0] - 1;
            const T * matr_data_0 = matrix.data[0] - 1;
            for (size_t j = 0; j < matrix.cols; ++j) {
                *(++data_0) = *(++matr_data_0) + vector_[j];
            }
        }
        else {
            for (size_t i = 0; i < matrix.rows; ++i) {
                result.data[i][0] = matrix[i][0] + vector_[i];
            }
        }

        return result;
    }

    template <class T>
    Matrix<T> operator-(const Matrix<T>& matrix, const std::vector<T>& vector_) {
        Matrix<T> result(matrix.rows, matrix.cols);

        if (matrix.rows == 1) {
            T * data_0 = result.data[0] - 1;
            const T * matr_data_0 = matrix.data[0] - 1;
            for (size_t j = 0; j < matrix.cols; ++j) {
                *(++data_0) = *(++matr_data_0) + vector_[j];
            }
        }
        else {
            for (size_t i = 0; i < matrix.rows; ++i) {
                result.data[i][0] = matrix[i][0] - vector_[i];
            }
        }

        return result;
    }

    template <class T>
    Matrix<T> operator*(const Matrix<T>& matrix, const std::vector<T>& vector_) {
        if (matrix.cols > 1) {
            Matrix<T> result(matrix.rows, 1);

            for (size_t i = 0; i < matrix.rows; ++i) {
                T * data_i = result.data[i];
                *data_i = ZERO;
                const T * matr_data_i = matrix.data[i] - 1;
                for (size_t j = 0; j < matrix.cols; ++j) {
                    *data_i += *(++matr_data_i) * vector_[j];
                }
            }

            return result;
        }
        else {
            Matrix<T> result(matrix.rows, vector_.size());

            for (size_t i = 0; i < matrix.rows; ++i) {
                T * data_i = result.data[i] - 1;
                const T * matr_data_i = matrix.data[i];

                for (size_t j = 0; j < result.cols; ++j) {
                    *(++data_i) = (*matr_data_i) * vector_[j];
                }
            }

            return result;
        }
    }

    template <class T>
    inline Matrix<T> operator+(const std::vector<T>& vector_, const Matrix<T>& matrix) {
        return matrix + vector_;
    }

    template <class T>
    Matrix<T> operator-(const std::vector<T>& vector_, const Matrix<T>& matrix) {
        Matrix<T> result(matrix.rows, matrix.cols);

        if (matrix.rows == 1) {
            T * data_0 = result.data[0] - 1;
            const T * matr_data_0 = matrix.data[0] - 1;
            for (size_t j = 0; j < matrix.cols; ++j) {
                *(++data_0) = vector_[j] - *(++matr_data_0);
            }
        }
        else {
            for (size_t i = 0; i < matrix.rows; ++i) {
                result.data[i][0] = vector_[i] - matrix[i][0];
            }
        }

        return result;
    }

    template <class T>
    Matrix<T> operator*(const std::vector<T>& vector_, const Matrix<T>& matrix) {
        if (matrix.rows > 1) {
            Matrix<T> result(1, matrix.cols);

            T * data_0 = result.data[0];
            for (size_t j = 0; j < matrix.cols; ++j, ++data_0) {
                *data_0 = ZERO;
                for (size_t i = 0; i < matrix.rows; ++i) {
                    *data_0 += matrix[i][j] * vector_[i];
                }
            }

            return result;
        }
        else {
            Matrix<T> result(vector_.size(), matrix.cols);

            for (size_t i = 0; i < matrix.rows; ++i) {
                T * data_i = result.data[i] - 1;
                const T * matr_data_i = matrix.data[i];
                const T & vector_i = vector_[i];

                for (size_t j = 0; j < result.cols; ++j) {
                    *(++data_i) = *(++matr_data_i) * vector_i;
                }
            }

            return result;
        }
    }

#endif	// _DS_MATRIX_SUPPORT_STL_VECTOR

    template<class T>
    Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& matrix)
    {
        T * row_ = new T[matrix.cols];

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                row_[j] = 0;
                for (size_t k = 0; k < cols; ++k) {
                    row_[j] += data[i][k] * matrix.data[k][j];
                }
            }
            T * ptr = data[i];
            data[i] = row_;
            row_ = ptr;
        }

        delete[] row_;
        
        cols = matrix.cols;

        return *this;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::operator++()
    {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                ++data[i][j];
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator++(int)
    {
        Matrix matrix = *this;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                ++data[i][j];
            }
        }
        return matrix;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::operator--()
    {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                --data[i][j];
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator--(int)
    {
        Matrix matrix = *this;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                --data[i][j];
            }
        }
        return matrix;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator-() const
    {
        Matrix<T> matrix(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                matrix.data[i][j] = -data[i][j];
            }
        }

        return matrix;
    }

    template<class T>
    typename Matrix<T>::iterator Matrix<T>::begin()
    {
        return Matrix<T>::iterator(0, 0, this);
    }

    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::begin() const
    {
        return Matrix<T>::const_iterator(0, 0, this);
    }

    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::cbegin() const
    {
        return Matrix<T>::const_iterator(0, 0, this);
    }

    template<class T>
    typename Matrix<T>::iterator Matrix<T>::end()
    {
        return Matrix<T>::iterator(rows, 0, this);
    }

    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::end() const
    {
        return Matrix<T>::const_iterator(rows, 0, this);
    }

    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::cend() const
    {
        return Matrix<T>::const_iterator(rows, 0, this);
    }

    template<class T>
    T** Matrix<T>::copyData() const {
        T ** copy = new T*[rows];

        for (size_t i = 0; i < rows; ++i) {
            copy[i] = new T[cols];

            for (size_t j = 0; j < cols; ++j) {
                copy[i][j] = data[i][j];
            }
        }

        return copy;
    }

    template<class T>
    void Matrix<T>::destroy() {
        if (data != 0) {

            for (size_t i = 0; i < rows; ++i) {
                delete[] data[i];
            }

            delete[] data;
        }
    }

    template<class T>
    T ** Matrix<T>::create_array_by_size(size_t n, size_t m) {
        T ** array_ = new T*[n];

        for (size_t i = 0; i < n; ++i) {
            array_[i] = new T[m];
        }

        return array_;
    }

    template<class T>
    T ** Matrix<T>::create_array_with_val(size_t n, size_t m, const T& val) {
        T ** array_ = new T*[n];

        for (size_t i = 0; i < n; ++i) {
            array_[i] = new T[m];

            for (size_t j = 0; j < m; ++j) {
                array_[i][j] = val;
            }
        }

        return array_;
    }

    template<class T>
    T ** Matrix<T>::create_array_by_two_dim_array(size_t n, size_t m, const T * const * matrix)
    {
        T ** array_ = new T*[n];

        for (size_t i = 0; i < n; ++i) {
            array_[i] = new T[m];
            T* ptr = array_[i] - 1;

            for (size_t j = 0; j < m; ++j) {
                *(++ptr) = matrix[i][j];
            }
        }

        return array_;
    }

    template <class T>
    template <size_t n, size_t m>
    T ** Matrix<T>::create_array_by_two_dim_array(const T(&matrix)[n][m]) {
        T ** array_ = new T*[n];

        for (size_t i = 0; i < n; ++i) {
            array_[i] = new T[m];

            for (size_t j = 0; j < m; ++j) {
                array_[i][j] = matrix[i][j];
            }
        }

        return array_;
    }

    template<class T>
    T ** Matrix<T>::create_array_by_array(size_t n, const T * array_in, ROW_COL row_col)
    {
        if (row_col == COLUMN) {
            T ** array_ = new T*[n];

            for (size_t i = 0; i < n; ++i) {
                array_[i] = new T[1];
                array_[i][0] = array_in[i];
            }

            return array_;
        }
        if (row_col == ROW) {
            T ** array_ = new T*[1];
            *array_ = new T[n];
            T* ptr = *array_ - 1;

            for (size_t i = 0; i < n; ++i) {
                *(++ptr) = array_in[i];
            }

            return array_;
        }
        return 0;
    }

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR
    template<class T>
    T ** Matrix<T>::create_array_by_std_vector_vector(const std::vector< std::vector<T> >& matrix) {
        size_t n = matrix.size();
        size_t m = matrix[0].size();

        T ** array_ = new T*[n];

        for (size_t i = 0; i < n; ++i) {
            array_[i] = new T[m];

            for (size_t j = 0; j < m; ++j) {
                array_[i][j] = matrix[i][j];
            }
        }

        return array_;
    }

    template<class T>
    T ** Matrix<T>::create_array_by_std_vector(const std::vector<T>& vector_in, ROW_COL row_col) {
        size_t n = vector_in.size();

        if (row_col == COLUMN) {
            T ** array_ = new T*[n];

            for (size_t i = 0; i < n; ++i) {
                array_[i] = new T[1];
                array_[i][0] = vector_in[i];
            }

            return array_;
        }
        if (row_col == ROW) {
            T ** array_ = new T*[1];
            *array_ = new T[n];
            T* ptr = *array_ - 1;

            for (size_t i = 0; i < n; ++i) {
                *(++ptr) = vector_in[i];
            }

            return array_;
        }
        return 0;
    }
#endif // _DS_MATRIX_SUPPORT_STL_VECTOR

    template<class T>
    void Matrix<T>::resize(size_t n, size_t m) {
        destroy();

        rows = n;
        cols = m;
        data = create_array_by_size(n, m);
    }

    template<class T>
    void Matrix<T>::resize(size_t n, size_t m, const T& val) {
        destroy();

        rows = n;
        cols = m;
        data = create_array_with_val(n, m, val);
    }

    template<class T>
    inline Matrix<T> Matrix<T>::createZeroMatrix(size_t n, size_t m)
    {
        return matrixWithValue(n, m, ZERO);
    }

    template<class T>
    Matrix<T> Matrix<T>::createIdMatrix(size_t n)
    {
        Matrix<T> matrix = matrixWithValue(n, n, ZERO);

        for (size_t i = 0; i < n; ++i) {
            matrix.data[i][i] = ONE;
        }

        return matrix;
    }

    template<class T>
    inline size_t Matrix<T>::size() const
    {
        return rows * cols;
    }

    template<class T>
    inline size_t Matrix<T>::rowsCount() const
    {
        return rows;
    }

    template<class T>
    inline size_t Matrix<T>::colsCount() const
    {
        return cols;
    }

    template<class T>
    Matrix<T>& Matrix<T>::setVal(const T & val)
    {
        T** ptr_ptr = data - 1;
        for (size_t i = 0; i < rows; ++i) {
            T* ptr = *(++ptr_ptr) - 1;

            for (size_t j = 0; j < cols; ++j) {
                *(++ptr) = val;
            }
        }

        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::transpose()
    {
        if (rows == cols) {
            for (size_t i = 0; i < rows - 1; ++i) {
                for (size_t j = i + 1; j < cols; ++j) {
                    T t = data[j][i];
                    data[j][i] = data[i][j];
                    data[i][j] = t;
                }
            }
        }
        else {
            T ** data_ = create_array_by_size(cols, rows);

            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    data_[j][i] = data[i][j];
                }
            }

            destroy();

            data = data_;
            size_t s = rows;
            rows = cols;
            cols = s;
        }

        return *this;
    }

    template<class T>
    Matrix<T> Matrix<T>::submatrix(size_t n_from, size_t n_to, size_t m_from, size_t m_to) const
    {
        Matrix<T> matrix(n_to - n_from, m_to - m_from);
        for (size_t i1 = 0, i2 = n_from; i2 < n_to; ++i1, ++i2) {
            for (size_t j1 = 0, j2 = m_from; j2 < m_to; ++j1, ++j2) {
                matrix.data[i1][j1] = data[i2][j2];
            }
        }
        return matrix;
    }

    template<class T>
    Matrix<T>& Matrix<T>::concatRowsRight(const Matrix<T>& rightMatrix) {
        size_t newCols = cols + rightMatrix.cols;

        T** ptr_row_this = data;
        T** ptr_row_rightMatrix = rightMatrix.data;

        for (size_t i = 0; i < rows; ++i, ++ptr_row_this, ++ptr_row_rightMatrix) {
            T* newRow = new T[cols];

            T* ptr_this = *ptr_row_this - 1;
            T* ptr_rightMatrix = *ptr_row_rightMatrix - 1;
            T* ptr_new_row = newRow - 1;

            for (size_t j = 0; j < cols; ++j) {
                *(++ptr_new_row) = *(++ptr_this);
            }

            for (size_t j = 0; j < rightMatrix.cols; ++j) {
                *(++ptr_new_row) = *(++ptr_rightMatrix);
            }

            delete[] *ptr_row_this;
            *ptr_row_this = newRow;
        }

        cols = newCols;

        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::concatRowsLeft(const Matrix<T>& leftMatrix) {
        size_t newCols = cols + leftMatrix.cols;

        T** ptr_row_this = data;
        T** ptr_row_leftMatrix = leftMatrix.data;

        for (size_t i = 0; i < rows; ++i, ++ptr_row_this, ++ptr_row_leftMatrix) {
            T* newRow = new T[cols];

            T* ptr_this = *ptr_row_this - 1;
            T* ptr_leftMatrix = *ptr_row_leftMatrix - 1;
            T* ptr_new_row = newRow - 1;

            for (size_t j = 0; j < leftMatrix.cols; ++j) {
                *(++ptr_new_row) = *(++ptr_leftMatrix);
            }

            for (size_t j = 0; j < cols; ++j) {
                *(++ptr_new_row) = *(++ptr_this);
            }

            delete[] * ptr_row_this;
            *ptr_row_this = newRow;
        }

        cols = newCols;

        return *this;
    }

    template <class T>
    Matrix<T>& Matrix<T>::concatColsDown(const Matrix<T>& downMatrix) {
        T ** downMatrixData = downMatrix.copyData();

        size_t newRows = rows + downMatrix.rows;

        T ** newData = new T*[newRows];

        T ** ptrRowThis = data - 1;
        T ** ptrRowNew = newData - 1;
        T ** ptrRowDownMatrix = downMatrix.data - 1;

        for (size_t i = 0; i < rows; ++i) {
            *(++ptrRowNew) = *(++ptrRowThis);
            delete[] * ptrRowThis;
        }

        for (size_t i = rows; i < newRows; ++i) {
            *(++ptrRowNew) = *(++ptrRowDownMatrix);
        }

        delete[] data;
        delete[] downMatrixData;

        data = newData;

        return *this;
    }

    template <class T>
    Matrix<T>& Matrix<T>::concatColsUp(const Matrix<T>& upperMatrix) {
        T ** upperMatrixData = upperMatrix.copyData();

        size_t newRows = rows + upperMatrix.rows;

        T ** newData = new T*[newRows];

        T ** ptrRowThis = data - 1;
        T ** ptrRowNew = newData - 1;
        T ** ptrRowUpperMatrix = upperMatrix.data - 1;

        for (size_t i = rows; i < newRows; ++i) {
            *(++ptrRowNew) = *(++ptrRowUpperMatrix);
        }

        for (size_t i = 0; i < rows; ++i) {
            *(++ptrRowNew) = *(++ptrRowThis);
            delete[] * ptrRowThis;
        }

        delete[] data;
        delete[] upperMatrixData;

        data = newData;

        return *this;
    }

    template<class T>
    Matrix<T> concatRows(const Matrix<T>& leftMatrix, const Matrix<T>& rightMatrix) {
        Matrix<T> matrix(leftMatrix.rows, leftMatrix.cols + rightMatrix.cols);

        T ** ptrData = matrix.data;
        T ** ptrLeftMatrixData = leftMatrix.data;
        T ** ptrRightMatrixData = rightMatrix.data;

        for (size_t i = 0; i < matrix.rows; ++i, ++ptrData, ++ptrLeftMatrixData, ++ptrRightMatrixData) {
            T * ptr = *ptrData - 1;
            T * ptrLeftMatrix = *ptrLeftMatrixData - 1;
            T * ptrRightMatrix = *ptrRightMatrixData - 1;

            for (size_t j = 0; j < leftMatrix.cols; ++j) {
                *(++ptr) = *(++ptrLeftMatrix);
            }

            for (size_t j = 0; j < rightMatrix.cols; ++j) {
                *(++ptr) = *(++ptrRightMatrix);
            }
        }

        return matrix;
    }

    template<class T>
    Matrix<T> concatCols(const Matrix<T>& upperMatrix, const Matrix<T>& downMatrix) {
        Matrix<T> matrix(upperMatrix.rows, upperMatrix.cols + downMatrix.cols);

        T ** ptrData = matrix.data;
        T ** ptrUpperMatrixData = upperMatrix.data;
        T ** ptrDownMatrixData = downMatrix.data;

        for (size_t i = 0; i < upperMatrix.rows; ++i, ++ptrData, ++ptrUpperMatrixData) {
            T * ptr = *ptrData - 1;
            T * ptrUpperMatrix = *ptrUpperMatrixData - 1;

            for (size_t j = 0; j < upperMatrix.cols; ++j) {
                *(++ptr) = *(++ptrUpperMatrix);
            }
        }

        for (size_t i = 0; i < downMatrix.rows; ++i, ++ptrData, ++ptrDownMatrixData) {
            T * ptr = *ptrData - 1;
            T * ptrDownMatrix = *ptrDownMatrixData - 1;

            for (size_t j = 0; j < downMatrix.cols; ++j) {
                *(++ptr) = *(++ptrDownMatrix);
            }
        }

        return matrix;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::swap_rows(size_t i1, size_t i2)
    {
        T * ptr = data[i1];
        data[i1] = data[i2];
        data[i2] = ptr;
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::swap_cols(size_t i1, size_t i2)
    {
        T t;
        for (size_t i = 0; i < rows; ++i) {
            t = data[i][i1];
            data[i][i1] = data[i][i2];
            data[i][i2] = t;
        }
        return *this;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::to_zero()
    {
        return setVal(ZERO);
    }

    template<class T>
    Matrix<T>& Matrix<T>::setRow(size_t i, const T * row_)
    {
        T* ptr = data[i] - 1;
        --row_;	//we want to use later ++row_ instead of row_++, because this operation is faster;

        for (size_t j = 0; j < cols; ++j) {
            *(++ptr) = *(++row_);
        }

        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::setColumn(size_t j, const T * column_)
    {
        T** ptr = data[0] - 1;	//we want to use later ++ptr_ instead of ptr_++, because this operation is faster;
        --column_;

        for (size_t i = 0; i < rows; ++i) {
            (++ptr)[j] = *(++column_);
        }

        return *this;
    }

    template<class T>
    inline Matrix<T>& Matrix<T>::setEps(const T & val)
    {
        eps = val;
        return *this;
    }

#if _DS_MATRIX_SUPPORT_ERASE
    template<class T>
    inline Matrix<T>& Matrix<T>::setKoefForResize(const T& val) {
        setKoefForResize = val;
        return *this;
    }
#endif // _DS_MATRIX_SUPPORT_ERASE

    template<class T>
    Matrix<T>& Matrix<T>::to_upper_triangle()
    {
        for (size_t i = 0; i < rows - 1; ++i) {
            if (data[i][i] == ZERO) {
                bool not_exist = true;

                for (size_t k = i; k < rows; ++k) {
                    if (data[k][i] != ZERO) {
                        swap_rows(i, k);
                        not_exist = false;
                        break;
                    }
                }

                if (not_exist) {
                    continue;
                }
            }

            T& data_ii = data[i][i];

            for (size_t k = i + 1; k < rows; ++k) {
                T data_ki = data[k][i];
                T* data_i = &data[i][i] - 1;

                for (size_t j = i; j < cols; ++j) {
                    data[k][j] -= data_ki * (*(++data_i)) / data_ii;
                }
            }
        }

        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::to_lower_triangle()
    {
        for (size_t i = rows - 1; i > 0; --i) {
            if (data[i][i] == ZERO) {
                bool not_exist = true;

                for (size_t k = i; k != SIZE_MAX; --k) {
                    if (data[k][i] != ZERO) {
                        swap_rows(i, k);
                        not_exist = false;
                        break;
                    }
                }

                if (not_exist) {
                    continue;
                }
            }

            T& data_ii = data[i][i];

            for (size_t k = i - 1; k != SIZE_MAX; --k) {
                T data_ki = data[k][i];
                T* data_i = &data[i][i] + 1;

                for (size_t j = i; j != SIZE_MAX; --j) {
                    data[k][j] -= data_ki * (*(--data_i)) / data_ii;
                }
            }
        }

        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::inverse()
    {
        Matrix<T>& inverse_ = createIdMatrix(rows);

        for (size_t i = 0; i < rows - 1; ++i) {
            if (data[i][i] == ZERO) {
                bool not_exist = true;

                for (size_t k = i; k < rows; ++k) {
                    if (data[k][i] != ZERO) {
                        swap_rows(i, k);
                        inverse_.swap_rows(i, k);
                        not_exist = false;
                        break;
                    }
                }

                if (not_exist) {
                    return *this;
                }
            }

            T& data_ii = data[i][i];

            for (size_t k = i + 1; k < rows; ++k) {
                T data_ki = data[k][i];
                T* data_i = &data[i][i] - 1;
                T* inv_data_i = &inverse_.data[i][0] - 1;

                for (size_t j = 0; j < i; ++j) {
                    inverse_[k][j] -= data_ki * (*(++inv_data_i)) / data_ii;
                }

                for (size_t j = i; j < cols; ++j) {
                    data[k][j] -= data_ki * (*(++data_i)) / data_ii;
                    inverse_[k][j] -= data_ki * (*(++inv_data_i)) / data_ii;
                }
            }
        }

        for (size_t i = rows - 1; i > 0; --i) {
            T& data_ii = data[i][i];

            for (size_t k = i - 1; k != SIZE_MAX; --k) {
                T data_ki = data[k][i];
                T* data_i = &data[i][i + 1];
                T* inv_data_i = &inverse_.data[i][cols];

                for (size_t j = cols - 1; j > i; --j) {
                    inverse_.data[k][j] -= data_ki * (*(--inv_data_i)) / data_ii;
                }

                for (size_t j = i; j != SIZE_MAX; --j) {
                    inverse_.data[k][j] -= data_ki * (*(--inv_data_i)) / data_ii;
                    data[k][j] -= data_ki * (*(--data_i)) / data_ii;
                }
            }
        }

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                inverse_.data[i][j] /= data[i][i];
            }
        }

        return (*this = inverse_);
    }

    template<class T>
    inline Matrix<T> Matrix<T>::row(size_t i) const
    {
        return Matrix<T>(crow_array, cols, ROW);
    }

    template<class T>
    Matrix<T> Matrix<T>::column(size_t j) const
    {
        Matrix<T> column_(rows, 1);
        for (size_t i = 0; i < rows; ++i) {
            column_.data[i][0] = data[i][j];
        }
        return column_;
    }

    template<class T>
    T * Matrix<T>::row_array(size_t i) const
    {
        T * row_ = new T[cols];
        for (size_t j = 0; j < cols; ++j) {
            row_[j] = data[i][j];
        }
        return row_;
    }

    template<class T>
    const T * Matrix<T>::crow_array(size_t i) const
    {
        return data[i];
    }

    template<class T>
    T * Matrix<T>::column_array(size_t j) const
    {
        T * col_ = new T[rows];
        for (size_t i = 0; i < rows; ++i) {
            col_[i] = data[i][j];
        }
        return col_;
    }

#if !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))

    template<class T>
    inline Matrix<T>::operator T**() const
    {
        return copyData();
    }

    template<class T>
    Matrix<T>::operator T*() const
    {
        T * arr = new T[rows];

        for (size_t i = 0; i < rows; ++i) {
            arr[i] = data[i][0];
        }

        return arr;
    }

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR

    template<class T>
    Matrix<T>::operator std::vector<T>() const
    {
        if (rows == 1) {
            std::vector<T> vect(rows);
            T * data_0 = data[0] - 1;

            for (size_t j = 0; j < cols; ++j) {
                vect[j] = *(++data_0);
            }

            return vect;
        }
        else {
            std::vector<T> vect(rows);

            for (size_t i = 0; i < rows; ++i) {
                vect[i] = data[i][0];
            }

            return vect;
        }
    }

    template<class T>
    Matrix<T>::operator std::vector< std::vector<T> >() const {
        std::vector< std::vector<T> > matrix(rows);

        T** ptr_ptr = data - 1;

        for (size_t i = 0; i < rows; ++i) {
            matrix[i].resize(cols);

            T* ptr = *(++data) - 1;

            for (size_t j = 0; j < cols; ++j) {
                matrix[i][j] = *(++ptr);
            }
        }

        return matrix;
    }

#endif // _DS_MATRIX_SUPPORT_STL_VECTOR

#endif // !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))

    template<class T>
    inline T** Matrix<T>::cast_to_two_dim_array() const {
        return copyData();
    }

    template<class T>
    T* Matrix<T>::cast_to_one_dim_array() const {
        T * arr = new T[rows];

        for (size_t i = 0; i < rows; ++i) {
            arr[i] = data[i][0];
        }

        return arr;
    }

#ifdef _DS_MATRIX_SUPPORT_STL_VECTOR

    template<class T>
    std::vector<T> Matrix<T>::cast_to_std_vector() const {
        if (rows == 1) {
            std::vector<T> vect(rows);
            T * data_0 = data[0] - 1;

            for (size_t j = 0; j < cols; ++j) {
                vect[j] = *(++data_0);
            }

            return vect;
        }
        else {
            std::vector<T> vect(rows);

            for (size_t i = 0; i < rows; ++i) {
                vect[i] = data[i][0];
//#include <QDebug>
//            qDebug() << "Vector[i]: " << (double)vect[i] << " ";
            }


            return vect;
        }
    }

    template<class T>
    std::vector< std::vector<T> > Matrix<T>::cast_to_std_vector_vector() const {
        std::vector< std::vector<T> > matrix(rows);

        T** ptr_ptr = data - 1;

        for (size_t i = 0; i < rows; ++i) {
            matrix[i].resize(cols);

            T* ptr = *(++ptr_ptr) - 1;

            for (size_t j = 0; j < cols; ++j) {
                matrix[i][j] = *(++ptr);
            }
        }

        return matrix;
    }

#endif // _DS_MATRIX_SUPPORT_STL_VECTOR

    template<class T>
    Matrix<T> to_upper_triangle(const Matrix<T>& matrix)
    {
        Matrix<T> matr = matrix;

        return matr.to_upper_triangle();
    }

    template<class T>
    Matrix<T> to_lower_triangle(const Matrix<T>& matrix)
    {
        Matrix<T> matr = matrix;
        return matr.inverse();
    }

    template<class T>
    Matrix<T> inverse(const Matrix<T>& matrix)
    {
        Matrix<T> matr = matrix;
        return matr.inverse();
    }

    template <class T>
    Matrix<T> solveSystem_GaussMethod(Matrix<T> matrix, const Matrix<T>& freeColumn) {
        Matrix<T> result = freeColumn;

        size_t &rows = matrix.rows;
        size_t &cols = matrix.cols;
        T **& data = matrix.data;

        for (size_t i = 0; i < rows - 1; ++i) {
            if (data[i][i] == ZERO) {
                bool not_exist = true;

                for (size_t k = i; k < rows; ++k) {
                    if (data[k][i] != ZERO) {
                        matrix.swap_rows(i, k);
                        result.swap_rows(i, k);
                        not_exist = false;
                        break;
                    }
                }

                if (not_exist) {
                    return result;
                }
            }

            T& data_ii = data[i][i];

            for (size_t k = i + 1; k < rows; ++k) {
                T data_ki = data[k][i];
                T* data_i = &data[i][i] - 1;

                for (size_t j = i; j < cols; ++j) {
                    data[k][j] -= data_ki * (*(++data_i)) / data_ii;
                }

                result.data[k][0] -= data_ki * result.data[i][0] / data_ii;
            }
        }

        for (size_t i = rows - 1; i > 0; --i) {
            T& data_ii = data[i][i];

            for (size_t k = i - 1; k != SIZE_MAX; --k) {
                T data_ki = data[k][i];
                T* data_i = &data[i][i + 1];

                for (size_t j = i; j != SIZE_MAX; --j) {
                    data[k][j] -= data_ki * (*(--data_i)) / data_ii;
                }

                result.data[k][0] -= data_ki * result.data[i][0] / data_ii;
            }
        }

        for (size_t i = 0; i < rows; ++i) {
            result.data[i][0] /= data[i][i];
        }

        return result;
    }

    template<class T>
    inline Matrix<T> transpose(const Matrix<T>& matrix)
    {
        Matrix<T> matr = matrix;
        return matr.transpose();
    }

    template<class T>
    T diag_sum(const Matrix<T>& matrix)
    {
        T t = matrix.data[0][0];

        for (size_t i = 1; i < matrix.rows; ++i) {
            t += matrix.data[i][i];
        }

        return t;
    }

    template<class T>
    T diag_prod(const Matrix<T>& matrix)
    {
        T t = matrix.data[0][0];

        for (size_t i = 1; i < matrix.rows; ++i) {
            t *= matrix.data[i][i];
        }

        return t;
    }

    template <class T>
    T det(const Matrix<T>& matrix) {
        Matrix<T> matr = matrix;

        matr.to_upper_triangle();

        return diag_prod(matr);
    }

    template <class T>
    std::ostream& operator<<(std::ostream& stream, const Matrix<T>& matrix) {
        for (size_t i = 0; i < matrix.rows; ++i) {
            stream << std::endl;
            stream << "| ";
            for (size_t j = 0; j < matrix.cols; ++j) {
                stream << matrix.data[i][j] << " ";
            }
            stream << "|";
        }
        return stream;
    }

    template<class T>
    Matrix<T> operator*(const T & val, const Matrix<T> & matrix)
    {
        return matrix * val;
    }

    template<class T>
    Matrix<T> operator+(const T & val, const Matrix<T> & matrix)
    {
        return matrix + val;
    }

    template<class T>
    Matrix<T> operator-(const T & val, const Matrix<T> & matrix)
    {
        return matrix - val;
    }

    template<class T>
    inline Matrix<T>::iterator::iterator() : row(0), col(0), matrix(0)
    {
    }

    template<class T>
    inline Matrix<T>::iterator::iterator(const iterator & iter)
    {
        row = iter.row;
        col = iter.col;
        matrix = iter.matrix;
    }

    template<class T>
    inline Matrix<T>::iterator::iterator(Matrix * matr, size_t n, size_t m)
    {
        row = n;
        col = m;
        matrix = matr;
    }

    template<class T>
    inline Matrix<T>::iterator::~iterator()
    {
    }


#if !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))

    template<class T>
    inline Matrix<T>::iterator::operator T*()
    {
        return &matrix[row][col];
    }

    template<class T>
    inline Matrix<T>::iterator::operator const T*() const
    {
        return &matrix->data[row][col];
    }

#endif // !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))

    template<class T>
    inline T* Matrix<T>::iterator::cast_to_ptr() {
        return &matrix[row][col];
    }

    template<class T>
    inline const T* Matrix<T>::iterator::cast_to_ptr() const {
        return &matrix[row][col];
    }

    template<class T>
    typename Matrix<T>::iterator & Matrix<T>::iterator::operator=(const iterator & iter)
    {
        row = iter.row;
        col = iter.col;
        matrix = iter.matrix;
    }

    template<class T>
    inline bool Matrix<T>::iterator::operator==(const iterator & iter) const
    {
        return &matrix[row][col] == &iter.matrix[iter.row][iter.col];
    }

    template<class T>
    inline bool Matrix<T>::iterator::operator!=(const iterator & iter) const
    {
        return &matrix[row][col] != &iter.matrix[iter.row][iter.col];
    }

    template<class T>
    typename Matrix<T>::iterator & Matrix<T>::iterator::operator++()
    {
        ++col;
        if (col == matrix->cols) {
            ++row;
            col = 0;
        }
        return *this;
    }

    template<class T>
    typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int)
    {
        Matrix<T>::iterator iter = *this;
        ++col;
        if (col == matrix->cols) {
            ++row;
            col = 0;
        }
        return iter;
    }

    template<class T>
    typename Matrix<T>::iterator & Matrix<T>::iterator::operator--()
    {
        if (col == 0) {
            col = matrix->cols - 1;
            --row;
        }
        else {
            --col;
        }
        return *this;
    }

    template<class T>
    typename Matrix<T>::iterator Matrix<T>::iterator::operator--(int)
    {
        Matrix<T>::iterator iter = *this;
        if (col == 0) {
            col = matrix->cols - 1;
            --row;
        }
        else {
            --col;
        }
        return iter;
    }

    template<class T>
    typename Matrix<T>::iterator Matrix<T>::iterator::operator+(size_t i) const
    {
        Matrix<T>::iterator iter(this->matrix, 0, 0);
        iter.col = col + i;
        iter.row = row + iter.col / matrix->cols;
        iter.col %= matrix->cols;
        return iter;
    }

    template<class T>
    typename Matrix<T>::iterator Matrix<T>::iterator::operator-(size_t i) const
    {
        Matrix<T>::iterator iter(this->matrix, 0, 0);
        long long col_ = static_cast<long long>(col) - static_cast<long long>(i);
        if (col_ < 0) {
            col_ = -col_;
            iter.row = row - static_cast<size_t>(col_ / matrix->cols) - 1;
            iter.col = matrix->cols - static_cast<size_t>(col_) % matrix->cols;
        }
        else {
            iter.col = static_cast<size_t>(col_);
            iter.row = row;
        }
        return iter;
    }

    template<class T>
    inline typename Matrix<T>::iterator & Matrix<T>::iterator::operator+=(size_t i)
    {
        col += i;
        row += col / matrix->cols;
        col %= matrix->cols;
        return *this;
    }

    template<class T>
    typename Matrix<T>::iterator & Matrix<T>::iterator::operator-=(size_t i)
    {
        long long col_ = static_cast<long long>(col) - static_cast<long long>(i);
        if (col_ < 0) {
            col_ = -col_;
            row -= static_cast<size_t>(col_ / matrix->cols) + 1;
            col = matrix->cols - static_cast<size_t>(col_) % matrix->cols;
        }
        else {
            col = static_cast<size_t>(col_);
        }
        return *this;
    }

    template<class T>
    inline T & Matrix<T>::iterator::operator*()
    {
        return matrix->data[row][col];
    }

    template<class T>
    inline const T & Matrix<T>::iterator::operator*() const
    {
        return matrix->data[row][col];
    }

    template<class T>
    inline T & Matrix<T>::iterator::operator->()
    {
        return matrix->data[row][col];
    }

    template<class T>
    inline const T & Matrix<T>::iterator::operator->() const
    {
        return matrix->data[row][col];
    }

    template<class T>
    inline Matrix<T>::const_iterator::const_iterator() : row(0), col(0), matrix(0)
    {
    }

    template<class T>
    inline Matrix<T>::const_iterator::const_iterator(const const_iterator & iter)
    {
        row = iter.row;
        col = iter.col;
        matrix = iter.matrix;
    }

    template<class T>
    inline Matrix<T>::const_iterator::const_iterator(const iterator & iter)
    {
        row = iter.row;
        col = iter.col;
        matrix = iter.matrix;
    }

    template<class T>
    inline Matrix<T>::const_iterator::const_iterator(const Matrix * matr, size_t n, size_t m)
    {
        row = n;
        col = m;
        matrix = matr;
    }

    template<class T>
    inline Matrix<T>::const_iterator::~const_iterator()
    {
        matrix = 0;
    }

#if !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))

    template<class T>
    inline Matrix<T>::const_iterator::operator const T*() const
    {
        return &matrix->data[row][col];
    }

#endif // !defined(_DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))

    template<class T>
    const T* Matrix<T>::const_iterator::cast_to_ptr() const {
        return &matrix->data[row][col];
    }

#if defined(_MSC_VER)

    template<class T>
    inline Matrix<T>::const_iterator::operator typename const Matrix<T>::iterator() const
    {
        return Matrix<T>::iterator(reinterpret_cast<Matrix<T> *>(matrix), row, col);
    }

#elif defined(__GNUC__)

    template<class T>
    inline Matrix<T>::const_iterator::operator const Matrix<T>::iterator() const
    {
        return Matrix<T>::iterator(reinterpret_cast<Matrix<T> *>(matrix), row, col);
    }

#endif // _MSC_VER

    template<class T>
    typename Matrix<T>::const_iterator & Matrix<T>::const_iterator::operator=(const const_iterator & iter)
    {
        row = iter.row;
        col = iter.col;
        matrix = iter.matrix;
    }

    template<class T>
    inline bool Matrix<T>::const_iterator::operator==(const const_iterator & iter) const
    {
        return &matrix[row][col] == &iter.matrix[iter.row][iter.col];
    }

    template<class T>
    inline bool Matrix<T>::const_iterator::operator!=(const const_iterator & iter) const
    {
        return &matrix[row][col] != &iter.matrix[iter.row][iter.col];
    }

    template<class T>
    typename Matrix<T>::const_iterator & Matrix<T>::const_iterator::operator++()
    {
        ++col;
        if (col == matrix->cols) {
            ++row;
            col = 0;
        }
        return *this;
    }

    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int)
    {
        Matrix<T>::const_iterator iter = *this;
        ++col;
        if (col == matrix->cols) {
            ++row;
            col = 0;
        }
        return iter;
    }

    template<class T>
    typename Matrix<T>::const_iterator & Matrix<T>::const_iterator::operator--()
    {
        if (col == 0) {
            col = matrix->cols - 1;
            --row;
        }
        else {
            --col;
        }
        return *this;
    }

    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator--(int)
    {
        Matrix<T>::const_iterator iter = *this;
        if (col == 0) {
            col = matrix->cols - 1;
            --row;
        }
        else {
            --col;
        }
        return iter;
    }

    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator+(size_t i) const
    {
        Matrix<T>::const_iterator iter(this->matrix, 0, 0);
        iter.col = col + i;
        iter.row = row + iter.col / matrix->cols;
        iter.col %= matrix->cols;
        return iter;
    }

    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator-(size_t i) const
    {
        Matrix<T>::const_iterator iter(this->matrix, 0, 0);
        long long col_ = static_cast<long long>(col) - static_cast<long long>(i);
        if (col_ < 0) {
            col_ = -col_;
            iter.row = row - static_cast<size_t>(col_ / matrix->cols) - 1;
            iter.col = matrix->cols - static_cast<size_t>(col_) % matrix->cols;
        }
        else {
            iter.col = static_cast<size_t>(col_);
            iter.row = row;
        }
        return iter;
    }

    template<class T>
    inline typename Matrix<T>::const_iterator & Matrix<T>::const_iterator::operator+=(size_t i)
    {
        col += i;
        row += col / matrix->cols;
        col %= matrix->cols;
        return *this;
    }

    template<class T>
    typename Matrix<T>::const_iterator & Matrix<T>::const_iterator::operator-=(size_t i)
    {
        long long col_ = static_cast<long long>(col) - static_cast<long long>(i);
        if (col_ < 0) {
            col_ = -col_;
            row -= static_cast<size_t>(col_ / matrix->cols) + 1;
            col = matrix->cols - static_cast<size_t>(col_) % matrix->cols;
        }
        else {
            col = static_cast<size_t>(col_);
        }
        return *this;
    }

    template<class T>
    inline const T & Matrix<T>::const_iterator::operator*() const
    {
        return matrix->data[row][col];
    }

    template<class T>
    inline const T & Matrix<T>::const_iterator::operator->() const
    {
        return matrix->data[row][col];
    }

};

#undef _DS_MATRIX_SUPPORT_ERASE

#ifndef _DS_MATRIX_NOT_USE_STANDART_VALUES_DEF

#undef ZERO
#undef ONE
#undef DEFAULT_EPS

#endif // #ifndef _DS_MATRIX_NOT_USE_STANDART_VALUES_DEF

#endif // !_DS_MATRIX_
