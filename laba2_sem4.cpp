#include <iostream>
#include <random>

class Matrix {
private:
    int** data; // двумерный массив для хранения данных матрицы
    unsigned int m; // количество строк в матрице
    unsigned int n; // количество столбцов в матрице

public:
    Matrix(unsigned int m, unsigned int n) : m(m), n(n) {
        // Конструктор создаёт двумерный массив для хранения данных матрицы
        data = new int* [m];
        for (unsigned int i = 0; i < m; ++i) {
            data[i] = new int[n];
        }
    }

    ~Matrix() {
        // Деструктор освобождает память, занятую двумерным массивом
        for (unsigned int i = 0; i < m; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    int& operator[](const unsigned int& i) {
        // Перегрузка оператора [] обеспечивает доступ к элементам матрицы с возможностью их изменения
        return data[i][0];
    }

    void fillRandom() {
        // Метод заполняет матрицу случайными значениями от 0 до 9
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, 9);
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] = dist(gen);
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        // Перегрузка оператора << обеспечивает вывод матрицы в виде таблицы
        for (unsigned int i = 0; i < matrix.m; ++i) {
            for (unsigned int j = 0; j < matrix.n; ++j) {
                os << matrix.data[i][j] << ' ';
            }
            os << std::endl;
        }
        return os;
    }

    Matrix& operator+=(const Matrix& other) {
        // Перегрузка оператора += для сложения матриц
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix& other) const {
        // Перегрузка оператора + для сложения матриц
        Matrix result(m, n);
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix& operator-=(const Matrix& other) {
        // Перегрузка оператора -= для вычитания матриц
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }

    Matrix operator-(const Matrix& other) const {
        // Перегрузка оператора - для вычитания матриц
        Matrix result(m, n);
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix& operator*=(const Matrix& other) {
        // Перегрузка оператора *= для умножения матриц
        if (n != other.m) {
            throw std::invalid_argument("Matrix dimensions are not compatible for multiplication");
        }
        Matrix result(m, other.n);
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < other.n; ++j) {
                for (unsigned int k = 0; k < n; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return *this;
    }

    Matrix operator*(const Matrix& other) const {
        // Перегрузка оператора * для умножения матриц
        if (n != other.m) {
            throw std::invalid_argument("Matrix dimensions are not compatible for multiplication");
        }
        Matrix result(m, other.n);
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < other.n; ++j) {
                for (unsigned int k = 0; k < n; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    bool operator!=(const Matrix& other) const {
        // Перегрузка оператора != для проверки неравенства матриц
        if (m != other.m || n != other.n) {
            return true;
        }
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                if (data[i][j] != other.data[i][j]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool operator==(const Matrix& other) const {
        // Перегрузка оператора == для проверки равенства матриц
        return !(*this != other);
    }
};

int main() {
    // Создание двух матриц размером 3x3 и заполнение их случайными значениями
    Matrix m1(3, 3);
    m1.fillRandom();
    std::cout << "Matrix 1:" << std::endl;
    std::cout << m1 << std::endl;

    Matrix m2(3, 3);
    m2.fillRandom();
    std::cout << "Matrix 2:" << std::endl;
    std::cout << m2 << std::endl;

    // Сложение матриц
    Matrix m3 = m1 + m2;
    std::cout << "Matrix 1 + Matrix 2:" << std::endl;
    std::cout << m3 << std::endl;

    // Вычитание матриц
    Matrix m4 = m1 - m2;
    std::cout << "Matrix 1 - Matrix 2:" << std::endl;
    std::cout << m4 << std::endl;

    // Умножение матриц
    Matrix m5 = m1 * m2;
    std::cout << "Matrix 1 * Matrix 2:" << std::endl;
    std::cout << m5 << std::endl;

    // Проверка равенства матриц
    bool isEqual = m1 == m2;
    std::cout << "Matrix 1 == Matrix 2: " << (isEqual ? "true" : "false") << std::endl;

    return 0;
}
