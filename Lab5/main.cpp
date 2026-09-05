#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Element
{
protected:
    string name;
    
public:
    Element(const string& n) : name(n) {}
    
    virtual ~Element() = default;
    
    string getName() const { return name; }
    
    virtual string getType() const = 0;
};


class Air : public Element
{
public:
    Air() : Element("Воздух") {}
    string getType() const override { return "Air"; }
};


class Water : public Element
{
public:
    Water() : Element("Вода") {}
    string getType() const override { return "Water"; }
};


class Earth : public Element
{
public:
    Earth() : Element("Земля") {}
    string getType() const override { return "Earth"; }
};


class Fire : public Element
{
public:
    Fire() : Element("Огонь") {}
    string getType() const override { return "Fire"; }
};


// Классы производных элементов
class Steam : public Element
{
public:
    Steam() : Element("Пар") {}
    string getType() const override { return "Steam"; }
};

class Mud : public Element
{
public:
    Mud() : Element("Грязь") {}
    string getType() const override { return "Mud"; }
};

class Lava : public Element
{
public:
    Lava() : Element("Лава") {}
    string getType() const override { return "Lava"; }
};

class Energy : public Element
{
public:
    Energy() : Element("Энергия") {}
    string getType() const override { return "Energy"; }
};

// Оператор сложения для элементов
Element* operator+(const Element& a, const Element& b)
{
    string typeA = a.getType();
    string typeB = b.getType();

    if ((typeA == "Fire" && typeB == "Water") ||
        (typeA == "Water" && typeB == "Fire")) {
        return new Steam();
    }

    else if ((typeA == "Earth" && typeB == "Water") ||
             (typeA == "Water" && typeB == "Earth")) {
        return new Mud();
    }

    else if ((typeA == "Fire" && typeB == "Earth") ||
             (typeA == "Earth" && typeB == "Fire")) {
        return new Lava();
    }

    else if ((typeA == "Air" && typeB == "Fire") ||
             (typeA == "Fire" && typeB == "Air")) {
        return new Energy();
    }
    
    return nullptr;
}

int main() {
    vector<Element*> elements;
    
    // Начальные элементы
    elements.push_back(new Fire());
    elements.push_back(new Water());
    elements.push_back(new Earth());
    elements.push_back(new Air());
    
    
    while (true) {
        cout << "Доступные элементы:" << endl;
        for (size_t i = 0; i < elements.size(); i++) {
            cout << i << ": " << elements[i]->getName() << endl;
        }
        
        int index1, index2;
        cout << "\nВведите индекс первого элемента: ";
        cin >> index1;
        
        if (index1 == -1) break;
        
        cout << "Введите индекс второго элемента: ";
        cin >> index2;
        
        if (index2 == -1) break;
   
        if (index1 < 0 || index1 >= (int)elements.size() ||
            index2 < 0 || index2 >= (int)elements.size()) {
            cout << "Ошибка: неверные индексы элементов" << endl;
            continue;
        }
  
        Element* result = *elements[index1] + *elements[index2];
        
        if (result != nullptr) {
            cout << "Получен новый элемент: "<< result->getName() << endl;
            elements.push_back(result);
        } else {
            cout << "Эти элементы не взаимодействуют!" << endl;
        }
        
    }

    for (Element* elem : elements) {
        delete elem;
    }
    
    return 0;
}

