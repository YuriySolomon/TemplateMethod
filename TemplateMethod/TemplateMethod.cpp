#include <iostream>
using namespace std;

/* Абстрактный Класс определяет шаблонный метод, содержащий скелет некоторого
 * алгоритма, состоящего из вызовов (обычно) абстрактных примитивных операций.
 *
 * Конкретные подклассы должны реализовать эти операции, но оставить сам шаблонный метод без изменений.*/

/* An Abstract Class defines a template method that contains the skeleton of some algorithm,
 * consisting of calls to (usually) abstract primitive operations.
 * 
 * Concrete subclasses must implement these operations, but leave the template method itself unchanged.*/
class AbstractClass {
    // Шаблонный метод определяет скелет алгоритма.   
    // The template method defines the skeleton of the algorithm.
public:
    void TemplateMethod() const {
        this->BaseOperation1();
        this->RequiredOperations1();
        this->BaseOperation2();
        this->Hook1();
        this->RequiredOperation2();
        this->BaseOperation3();
        this->Hook2();
    }
    // Эти операции уже имеют реализации.
    // These operations already have implementations.
protected:
    void BaseOperation1() const {
        cout << "AbstractClass says: I am doing the bulk of the work\n";
    }
    void BaseOperation2() const {
        cout << "AbstractClass says: But I let subclasses override some operations\n";
    }
    void BaseOperation3() const {
        cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
    }
    // А эти операции должны быть реализованы в подклассах.
    // And these operations must be implemented in subclasses.
    virtual void RequiredOperations1() const = 0;
    virtual void RequiredOperation2() const = 0;
    /* Это «хуки».Подклассы могут переопределять их, но это не обязательно,
     * поскольку у хуков уже есть стандартная (но пустая) реализация.
     * Хуки предоставляют дополнительные точки расширения в некоторых критических местах алгоритма.*/

    /* These are "hooks".Subclasses can override them, but they don't have to
     * because hooks already have a standard (but empty) implementation. 
     * Hooks provide additional extension points at some critical places in the algorithm.*/
    virtual void Hook1() const {}
    virtual void Hook2() const {}
};

/* Конкретные классы должны реализовать все абстрактные операции базового класса.
 * Они также могут переопределить некоторые операции с реализацией по умолчанию.*/

/* Concrete classes must implement all the abstract operations of the base class.
 * They can also override some operations with the default implementation.*/
class ConcreteClass1 : public AbstractClass {
protected:
    void RequiredOperations1() const override {
        cout << "ConcreteClass1 says: Implemented Operation1\n";
    }
    void RequiredOperation2() const override {
        cout << "ConcreteClass1 says: Implemented Operation2\n";
    }
};
// Обычно конкретные классы переопределяют только часть операций базового класса.
// Usually concrete classes override only part of the operations of the base class.
class ConcreteClass2 : public AbstractClass {
protected:
    void RequiredOperations1() const override {
        cout << "ConcreteClass2 says: Implemented Operation1\n";
    }
    void RequiredOperation2() const override {
        cout << "ConcreteClass2 says: Implemented Operation2\n";
    }
    void Hook1() const override {
        cout << "ConcreteClass2 says: Overridden Hook1\n";
    }
};
/* Клиентский код вызывает шаблонный метод для выполнения алгоритма.
 * Клиентский код не должен знать конкретный класс объекта, с которым работает, 
 * при условии, что он работает с объектами через интерфейс их базового класса.*/

/* The client code calls the template method to execute the algorithm.
 * Client code does not need to know the specific class of the object it is working on,
 * provided that it works with objects through their base class interface*/
void ClientCode(AbstractClass* class_) {
    // ...
    class_->TemplateMethod();
    // ...
}
int main() {
    cout << "Same client code can work with different subclasses:\n";
    ConcreteClass1* concreteClass1 = new ConcreteClass1;
    ClientCode(concreteClass1);
    cout << "\n";
    cout << "Same client code can work with different subclasses:\n";
    ConcreteClass2* concreteClass2 = new ConcreteClass2;
    ClientCode(concreteClass2);
    delete concreteClass1;
    delete concreteClass2;
    return 0;
}
