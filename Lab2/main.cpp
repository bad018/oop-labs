#include <iostream>

using namespace std;

class Vector
{
public:
    Vector()
    {
        flag = true;
        size = 0;
        array = nullptr;
        
        cout << "Вызван конструктор по умолчанию " << this << endl;
    }
    
    Vector(int size)
    {
        flag = true;
        this->size = size;
        array = new int[size] {};
        
        cout << "Вызван конструктор с параметром размера " << this << endl;
    }
    
    Vector(int size, int value)
    {
        flag = true;
        this->size = size;
        array = new int[size] {};
        for (int i = 0; i < size; i++)
        {
            array[i] = value;
        }
        cout << "Вызван конструктор с параметром размера и значения " << this << endl;
    }
    
    Vector(int *external, int size)
    {
        flag = false;
        this->size = size;
        array = external;
        cout << "Вызван конструктор, принимающий внешний массив и его размер " << this << endl;
    }
    
    Vector(const Vector &other)
    {
        this->size = other.size;
        this->flag = other.flag;
        
        if (other.flag)
        {
            this->array = new int[other.size];
            for (int i = 0; i < other.size; i++)
            {
                this->array[i] = other.array[i];
            }
            cout << "Вызван конструктор копирования владеющего вектора " << this << endl;
        }
        else
        {
            this->array = other.array;
            cout << "Вызван конструктор копирования невладеющего вектора " << this << endl;
        }
    }
    
    ~Vector()
    {
        if (flag && array != nullptr)
        {
            delete[] array;
        }
        cout << "Вызван деструктор " << this << endl;
    }
    
    int Size()
    {
        return size;
    }
    
    bool OwnsMemory()
    {
        return flag;
    }
    
    void SetElement(int index, int value)
    {
        if (index < 0 || index >= size)
        {
            cout << "Индекс выходит за пределы вектора" << endl;
        }
        else
        {
            array[index] = value;
        }
    }
    
    int GetElement(int index)
    {
        if (index < 0 || index >= size)
        {
            cout << "Индекс выходит за пределы вектора" << endl;
            return 0;
        }
        else
        {
            return array[index];
        }
    }
    
    int Dot(const Vector& other) const
    {
        int res = 0;
        
        if (this->size == other.size)
        {
            for (int i = 0; i < other.size; i++)
            {
                res += array[i] * other.array[i];
            }
            return res;
        }
        else
        {
            cout << "Векторы разного размера" << endl;
            return 0;
        }
    }
    
    void Link(int *external_ptr, int size)
    {
        if (flag && array != nullptr)
        {
            delete[] array;
        }
        flag = false;
        this->size = size;
        array = external_ptr;
    }
    
    void Unlink()
    {
        if (!flag)
        {
            int *new_array = new int[size];
            for (int i = 0; i < size; i++)
            {
                new_array[i] = array[i];
            }
            array = new_array;
            flag = true;
        }
    }
    
    void print() {
        cout << "Размер массива: " << size
             << "\t Значение флага: " << flag
             << "\t Значения массива: [ ";
        
        for (int i = 0; i < size; i++) {
            cout << array[i] << " ";
        }
        cout << "]" << endl;
    }
    
private:
    bool flag;
    int size;
    int *array;
};

int main()
{
    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССА VECTOR ===" << endl << endl;

    // 1. Тестирование различных конструкторов
    cout << "1. ТЕСТИРОВАНИЕ КОНСТРУКТОРОВ:" << endl;
    cout << "--------------------------------" << endl;
    
    cout << "а) Конструктор по умолчанию:" << endl;
    Vector v1;
    v1.print();
    cout << endl;

    cout << "б) Конструктор с параметром размера:" << endl;
    Vector v2(3);
    v2.print();
    cout << endl;

    cout << "в) Конструктор с размером и значением:" << endl;
    Vector v3(4, 7);
    v3.print();
    cout << endl;

    cout << "г) Конструктор с внешним массивом:" << endl;
    int external_array[] = {10, 20, 30, 40, 50};
    Vector v4(external_array, 5);
    v4.print();
    cout << "   Владеет памятью: " << v4.OwnsMemory() << endl;
    cout << endl;

    // 2. Тестирование конструктора копирования
    cout << "2. ТЕСТИРОВАНИЕ КОНСТРУКТОРА КОПИРОВАНИЯ:" << endl;
    cout << "-----------------------------------------" << endl;
    
    cout << "а) Копирование владеющего вектора:" << endl;
    Vector v5(3, 100);
    Vector v6(v5); // конструктор копирования
    cout << "Оригинал: ";
    v5.print();
    cout << "Копия:    ";
    v6.print();
    cout << "Изменяем копию..." << endl;
    v6.SetElement(1, 999);
    cout << "Оригинал после изменения копии: ";
    v5.print();
    cout << "Копия после изменения: ";
    v6.print();
    cout << endl;

    cout << "б) Копирование невладеющего вектора:" << endl;
    int external_array2[] = {1, 2, 3};
    Vector v7(external_array2, 3);
    Vector v8(v7); // конструктор копирования для невладеющего
    cout << "Оригинал: ";
    v7.print();
    cout << "Копия:    ";
    v8.print();
    cout << "Изменяем оригинал (внешний массив)..." << endl;
    external_array2[1] = 888;
    cout << "Оригинал после изменения: ";
    v7.print();
    cout << "Копия после изменения оригинала: ";
    v8.print();
    cout << endl;

    // 3. Тестирование методов доступа и модификации
    cout << "3. ТЕСТИРОВАНИЕ МЕТОДОВ ДОСТУПА:" << endl;
    cout << "--------------------------------" << endl;
    
    Vector v9(5);
    for (int i = 0; i < v9.Size(); i++) {
        v9.SetElement(i, i * 10);
    }
    cout << "Вектор после заполнения: ";
    v9.print();
    
    cout << "Чтение элементов: ";
    for (int i = 0; i < v9.Size(); i++) {
        cout << v9.GetElement(i) << " ";
    }
    cout << endl;
    
    // Тестирование обработки некорректных индексов
    cout << "Тестирование обработки ошибок индексации:" << endl;
    v9.SetElement(-1, 100);  // Ошибка: отрицательный индекс
    v9.SetElement(10, 100);  // Ошибка: индекс больше размера
    cout << "Попытка чтения с некорректным индексом: " << v9.GetElement(100) << endl;
    cout << endl;

    // 4. Тестирование скалярного произведения
    cout << "4. ТЕСТИРОВАНИЕ СКАЛЯРНОГО ПРОИЗВЕДЕНИЯ:" << endl;
    cout << "---------------------------------------" << endl;
    
    Vector v10(3);
    v10.SetElement(0, 1); v10.SetElement(1, 2); v10.SetElement(2, 3);
    
    Vector v11(3);
    v11.SetElement(0, 4); v11.SetElement(1, 5); v11.SetElement(2, 6);
    
    cout << "Вектор 1: "; v10.print();
    cout << "Вектор 2: "; v11.print();
    cout << "Скалярное произведение: " << v10.Dot(v11) << endl;
    
    // Тестирование с векторами разного размера
    Vector v12(2, 1);
    cout << "Вектор 3 (размер 2): "; v12.print();
    cout << "Попытка скалярного произведения векторов разного размера: " << v10.Dot(v12) << endl;
    cout << endl;

    // 5. Тестирование переходов между режимами владения
    cout << "5. ТЕСТИРОВАНИЕ ПЕРЕХОДОВ МЕЖДУ РЕЖИМАМИ ВЛАДЕНИЯ:" << endl;
    cout << "-------------------------------------------------" << endl;
    
    cout << "а) Link - переход к использованию внешнего массива:" << endl;
    Vector v13(3, 50);
    cout << "До Link: "; v13.print();
    
    int new_external[] = {100, 200, 300};
    v13.Link(new_external, 3);
    cout << "После Link: "; v13.print();
    cout << "Владеет памятью: " << v13.OwnsMemory() << endl;
    
    // Изменяем внешний массив
    new_external[1] = 999;
    cout << "После изменения внешнего массива: "; v13.print();
    cout << endl;

    cout << "б) Unlink - создание копии данных:" << endl;
    cout << "До Unlink: "; v13.print();
    v13.Unlink();
    cout << "После Unlink: "; v13.print();
    cout << "Владеет памятью: " << v13.OwnsMemory() << endl;
    
    // Теперь изменения внешнего массива не влияют на вектор
    new_external[1] = 111;
    cout << "После изменения внешнего массива: "; v13.print();
    cout << endl;


    // 6. Тестирование корректности работы деструкторов
    cout << "6. ТЕСТИРОВАНИЕ РАБОТЫ ДЕСТРУКТОРОВ:" << endl;
    cout << "-----------------------------------" << endl;
    
    cout << "Создание временных объектов в блоке..." << endl;
    {
        Vector temp1(2, 5);
        Vector temp2(temp1);
        int temp_array[] = {7, 8, 9};
        Vector temp3(temp_array, 3);
    }
    cout << "Выход из блока - все деструкторы должны были вызваться" << endl << endl;

    // 7. Дополнительные edge cases
    cout << "7. ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ (EDGE CASES):" << endl;
    cout << "------------------------------------" << endl;
    
    cout << "а) Вектор нулевого размера:" << endl;
    Vector v14(0);
    v14.print();
    cout << "Попытка установки элемента: ";
    v14.SetElement(0, 1);
    cout << endl;

    cout << "б) Unlink для уже владеющего вектора:" << endl;
    Vector v15(2, 10);
    cout << "До Unlink: "; v15.print();
    v15.Unlink(); // Не должен ничего менять
    cout << "После Unlink: "; v15.print();
    cout << endl;

    cout << "в) Link с нулевым указателем:" << endl;
    Vector v16(2, 20);
    v16.Link(nullptr, 0);
    v16.print();
    cout << endl;

    cout << "=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===" << endl;

    return 0;
}
