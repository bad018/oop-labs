#include <iostream>
#include <utility>
#include <cmath>

using namespace std;

class Polynomial
{
public:
    Polynomial()
    {
        this->degree = 0;
        coeffs = new double[1] {};
        cout << "Вызван конструктор по умолчанию " << this << endl;
    };
    
    Polynomial(int degree)
    {
        this->degree = degree;
        coeffs = new double[degree + 1]{};
        
        cout << "Вызван конструктор по степени " << this << endl;
    };
    
    Polynomial(int degree, double* coeffs)
    {
        this->degree = degree;
        this->coeffs = new double[degree + 1]{};
        for (int i = 0; i <= degree; i++) {
            this->coeffs[i] = coeffs[i];
        }
        
        cout << "Вызван конструктор от массива коэффициентов " << this << endl;
    };
    
    Polynomial(const Polynomial& other)
    {
        this->degree = other.degree;
        this->coeffs = new double[degree + 1];
        for (int i = 0; i <= degree; i++) {
            this->coeffs[i] = other.coeffs[i];
        }
        
        cout << "Вызван конструктор копирования " << this << endl;
    };
    
    Polynomial& operator=(const Polynomial& other)
    {
        if (this != &other){
            this->degree = other.degree;
            delete[] coeffs;
            this->coeffs = new double[degree + 1];
            
            for (int i = 0; i <= degree; i++) {
                this->coeffs[i] = other.coeffs[i];
            }
        }
        
        cout << "Вызван оператор присваивания копированием " << this << endl;
        
        return *this;
    };
    
    Polynomial(Polynomial&& other) noexcept
    {
        this->degree = other.degree;
        this->coeffs = other.coeffs;
        other.coeffs = nullptr;
        other.degree = 0;
        
        cout << "Вызван конструктор перемещения " << this << endl;
    };
    
    Polynomial& operator=(Polynomial&& other) noexcept
    {
        if (this != &other){
            this->degree = other.degree;
            delete[] coeffs;
            this->coeffs = other.coeffs;
            other.coeffs = nullptr;
            other.degree = 0;
        }
        
        cout << "Вызван оператор присваивания перемещением " << this << endl;
        
        return *this;
    };
    
    ~Polynomial()
    {
        delete[] this->coeffs;
        cout << "Вызван деструктор "<< this << endl;
    };
    
    void Print() const {
        cout << "Степень полинома (degree = " << degree << "): [ ";
        if (coeffs != nullptr) {
            for (int i = 0; i <= degree; i++)
                cout << coeffs[i] << " ";
        } else {
            cout << "nullptr (перемещённый объект)";
        }
        cout << "]" << endl;
    };
    
    Polynomial operator+(const Polynomial& other) const
    {
        int max_degree;
        if (this->degree >= other.degree){
            max_degree = this->degree;
        }
        else {
            max_degree = other.degree;
        };
        Polynomial result(max_degree);
        
        for (int i = 0; i <= max_degree; i++){
            double a = (i <= this->degree) ? this->coeffs[i] : 0.0;
            double b = (i <= other.degree) ? other.coeffs[i] : 0.0;
            result.coeffs[i] = a + b;
        };
        
        cout << "Вызван оператор сложения полиномов" << endl;
        
        return result;
    };
    
    Polynomial operator-(const Polynomial& other) const
    {
        int max_degree;
        if (this->degree >= other.degree){
            max_degree = this->degree;
        }
        else {
            max_degree = other.degree;
        };
        Polynomial result(max_degree);
        
        for (int i = 0; i <= max_degree; i++){
            double a = (i <= this->degree) ? this->coeffs[i] : 0.0;
            double b = (i <= other.degree) ? other.coeffs[i] : 0.0;
            result.coeffs[i] = a - b;
        };
        
        cout << "Вызван оператор вычитания полиномов" << endl;
        
        return result;
    };
    
    Polynomial operator*(const Polynomial& other) const
    {
        Polynomial result(this->degree + other.degree);
        for (int i = 0; i <= this->degree; i++){
            for (int j = 0; j <= other.degree; j++){
                result.coeffs[i + j] += this->coeffs[i] * other.coeffs[j];
            }
        }
            
        cout << "Вызван оператор умножения полиномов" << endl;
            
        return result;
    };
    
    bool operator==(const Polynomial& other) const
    {
        constexpr double EPS = 1e-9;
        if (this->degree != other.degree){
            return false;
        };
        
        for (int i = 0; i <= this->degree; i++){
            if (fabs(this->coeffs[i] - other.coeffs[i]) > EPS){
                return false;
            }
        };
        
        cout << "Вызван оператор сравнения полиномов" << endl;
        
        return true;
    };
    
    bool operator!=(const Polynomial& other) const
    {
        constexpr double EPS = 1e-9;
        if (this->degree != other.degree){
            return true;
        };
        
        for (int i = 0; i <= this->degree; i++){
            if (fabs(this->coeffs[i] - other.coeffs[i]) > EPS){
                return true;
            }
        };
        
        cout << "Вызван оператор сравнения полиномов" << endl;
        
        return false;
    };
    
    Polynomial& operator++()
    {
        Polynomial result(degree + 1);
        result.coeffs[0] = 0.0;
        
        for (int i = 0; i <= degree + 1; i++)
        {
            result.coeffs[i + 1] = coeffs[i] / (i + 1);
        }
        
        *this = move(result);
        
        cout << "Вызван оператор взятия первообразной с нулевой константой" << endl;
        
        return *this;
    };
    
    Polynomial& operator++(int)
    {
        Polynomial result(degree + 1);
        result.coeffs[degree + 2] = 0.0;
        
        for (int i = 0; i <= degree; i++)
        {
            result.coeffs[i] = coeffs[i];
        }
        
        *this = move(result);
        
        cout << "Вызван оператор увеличения степени полинома на 1" << endl;
        
        return *this;
    };
    
    Polynomial& operator--()
    {
        Polynomial result(degree - 1);
        
        for (int i = 0; i < degree; i++)
        {
            result.coeffs[i] = coeffs[i + 1] * (i + 1);
        }
        
        *this = move(result);
        
        cout << "Вызван оператор взятия производной" << endl;
        
        return *this;
    };
    
    Polynomial& operator--(int)
    {
        Polynomial result(degree - 1);
        
        for (int i = 0; i < degree; i++)
        {
            result.coeffs[i] = coeffs[i];
        }
        
        *this = move(result);
        
        cout << "Вызван оператор уменьшения степени полинома на 1" << endl;
        
        return *this;
    };
    
    friend ostream& operator<<(ostream& os, const Polynomial& p)
    {
        for (int i = 0; i <= p.degree; i++) {
                os << p.coeffs[i];
                if (i > 0) os << "x^" << i;
                if (i < p.degree) os << " + ";
            }
            return os;
    };
    
    friend istream& operator>>(istream& is, Polynomial& p)
    {
        cout << "Введите степень полинома: ";
        int deg;
        is >> deg;

        delete[] p.coeffs;

        p.degree = deg;
        p.coeffs = new double[deg + 1];

        cout << "Введите " << deg + 1 << " коэффициентов: ";
        for (int i = 0; i <= deg; i++) {
            is >> p.coeffs[i];
        }

        cout << "Полином успешно введён!" << endl;
        return is;
    };

    double& operator[](int i)
    {
        return coeffs[i];
    };
    
    const double& operator[](int i) const
    {
        return coeffs[i];
    };
    
    double operator()(double x) const
    {
        double result = 0.0;
        for (int i = 0; i <= this->degree; i++){
            result += pow(x, i) * this->coeffs[i];
        };
        return result;
    };
    
    Polynomial operator^(int n) const
    {
        if (n == 0)
        {
            return Polynomial(0, new double[1]{1.0});
        };
        
        Polynomial result = *this;
        for (int i = 1; i < n; i++){
            result = result * *this;
        };
        
        return result;
    };
    
    Polynomial operator%(const Polynomial& other)
    {
        Polynomial result = *this;
        
        if (other.degree > this->degree){
            return result;
        };
        
        while (result.degree >= other.degree)
        {
            double factor = result.coeffs[result.degree] / other.coeffs[other.degree];
            int shift = result.degree - other.degree;
            Polynomial temp(shift);
            temp.coeffs[shift] = factor;
            result = result - other * temp;
        };
        
        return result;
    };
    
    int Degree()
    {
        return this->degree;
    };

private:
    int degree;
    double* coeffs;
    
};


int main() {

    
    return 0;
}

