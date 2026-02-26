/*
C++ Object-Oriented Programming Concepts - Comprehensive Guide
==============================================================
This file demonstrates all major object-oriented programming concepts
in C++ including encapsulation, inheritance, polymorphism, abstraction,
and advanced OOP features.
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <typeinfo>

using namespace std;

// =========================================================================
// 1. Encapsulation - Data Hiding and Access Control
// =========================================================================

class Employee {
private:
    // Private members - only accessible within the class
    string name;
    int age;
    double salary;
    
    void validateData() {
        if (age < 18 || age > 65) {
            throw invalid_argument("Age must be between 18 and 65");
        }
        if (salary < 0) {
            throw invalid_argument("Salary cannot be negative");
        }
    }
    
protected:
    // Protected members - accessible to derived classes
    string department;
    
public:
    // Constructors
    Employee() : name(""), age(0), salary(0.0), department("") {}
    
    Employee(string name, int age, double salary, string department)
        : name(name), age(age), salary(salary), department(department) {
        validateData();
    }
    
    // Destructor
    virtual ~Employee() {
        cout << "Employee " << name << " destructed" << endl;
    }
    
    // Getter methods (accessors)
    string getName() const {
        return name;
    }
    
    int getAge() const {
        return age;
    }
    
    double getSalary() const {
        return salary;
    }
    
    string getDepartment() const {
        return department;
    }
    
    // Setter methods (mutators) with validation
    void setName(string name) {
        if (name.empty()) {
            throw invalid_argument("Name cannot be empty");
        }
        this->name = name;
    }
    
    void setAge(int age) {
        if (age < 18 || age > 65) {
            throw invalid_argument("Age must be between 18 and 65");
        }
        this->age = age;
    }
    
    void setSalary(double salary) {
        if (salary < 0) {
            throw invalid_argument("Salary cannot be negative");
        }
        this->salary = salary;
    }
    
    void setDepartment(string department) {
        this->department = department;
    }
    
    // Public member functions
    virtual void work() const {
        cout << name << " is working in the " << department << " department" << endl;
    }
    
    virtual double calculateBonus() const {
        return salary * 0.1; // 10% bonus
    }
    
    void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Salary: $" << salary << endl;
        cout << "Department: " << department << endl;
    }
};

// =========================================================================
// 2. Inheritance - Base and Derived Classes
// =========================================================================

class Manager : public Employee {
private:
    int teamSize;
    double bonusMultiplier;
    
public:
    Manager() : Employee(), teamSize(0), bonusMultiplier(1.2) {}
    
    Manager(string name, int age, double salary, string department, int teamSize)
        : Employee(name, age, salary, department), 
          teamSize(teamSize), bonusMultiplier(1.2) {}
    
    int getTeamSize() const {
        return teamSize;
    }
    
    void setTeamSize(int teamSize) {
        if (teamSize < 0) {
            throw invalid_argument("Team size cannot be negative");
        }
        this->teamSize = teamSize;
    }
    
    // Override base class methods
    void work() const override {
        cout << getName() << " is managing a team of " << teamSize 
             << " in the " << getDepartment() << " department" << endl;
    }
    
    double calculateBonus() const override {
        return getSalary() * 0.15 * bonusMultiplier; // 15% bonus with multiplier
    }
    
    void displayInfo() const {
        Employee::displayInfo();
        cout << "Team Size: " << teamSize << endl;
        cout << "Bonus Multiplier: " << bonusMultiplier << "x" << endl;
    }
};

class Developer : public Employee {
private:
    string programmingLanguage;
    int linesOfCode;
    
public:
    Developer() : Employee(), programmingLanguage(""), linesOfCode(0) {}
    
    Developer(string name, int age, double salary, string department, 
              string language, int loc)
        : Employee(name, age, salary, department),
          programmingLanguage(language), linesOfCode(loc) {}
    
    string getProgrammingLanguage() const {
        return programmingLanguage;
    }
    
    int getLinesOfCode() const {
        return linesOfCode;
    }
    
    void setProgrammingLanguage(string language) {
        if (language.empty()) {
            throw invalid_argument("Programming language cannot be empty");
        }
        programmingLanguage = language;
    }
    
    void setLinesOfCode(int loc) {
        if (loc < 0) {
            throw invalid_argument("Lines of code cannot be negative");
        }
        linesOfCode = loc;
    }
    
    void work() const override {
        cout << getName() << " is coding in " << programmingLanguage 
             << " (Lines of code: " << linesOfCode << ")" << endl;
    }
    
    double calculateBonus() const override {
        double baseBonus = getSalary() * 0.12;
        double locBonus = (linesOfCode / 10000.0) * 500; // $500 per 10k LOC
        return baseBonus + locBonus;
    }
    
    void displayInfo() const {
        Employee::displayInfo();
        cout << "Programming Language: " << programmingLanguage << endl;
        cout << "Lines of Code: " << linesOfCode << endl;
    }
};

class Intern : public Employee {
private:
    string university;
    int monthsRemaining;
    
public:
    Intern() : Employee(), university(""), monthsRemaining(6) {}
    
    Intern(string name, int age, double salary, string department, 
           string university, int months)
        : Employee(name, age, salary, department),
          university(university), monthsRemaining(months) {}
    
    string getUniversity() const {
        return university;
    }
    
    int getMonthsRemaining() const {
        return monthsRemaining;
    }
    
    void setUniversity(string university) {
        if (university.empty()) {
            throw invalid_argument("University name cannot be empty");
        }
        this->university = university;
    }
    
    void setMonthsRemaining(int months) {
        if (months < 0 || months > 24) {
            throw invalid_argument("Months remaining must be between 0 and 24");
        }
        monthsRemaining = months;
    }
    
    void work() const override {
        cout << getName() << " is interning at " << getDepartment() 
             << " from " << university << " (" << monthsRemaining << " months left)" << endl;
    }
    
    double calculateBonus() const override {
        return getSalary() * 0.05; // 5% bonus
    }
    
    void displayInfo() const {
        Employee::displayInfo();
        cout << "University: " << university << endl;
        cout << "Months Remaining: " << monthsRemaining << endl;
    }
};

// =========================================================================
// 3. Polymorphism - Runtime and Compile-time
// =========================================================================

void demonstratePolymorphism() {
    cout << "\n=== Polymorphism Demonstration ===\n";
    
    // Base class pointers to derived class objects
    Employee* emp1 = new Manager("John Doe", 45, 90000, "Management", 8);
    Employee* emp2 = new Developer("Jane Smith", 30, 80000, "Engineering", "C++", 25000);
    Employee* emp3 = new Intern("Bob Johnson", 22, 25000, "Marketing", "University of Tech", 3);
    
    // Runtime polymorphism - virtual function call
    cout << "\nRuntime Polymorphism (Virtual Function Calls):\n";
    emp1->work();
    emp2->work();
    emp3->work();
    
    // Polymorphic behavior with calculations
    cout << "\nBonus Calculations:\n";
    cout << emp1->getName() << " bonus: $" << emp1->calculateBonus() << endl;
    cout << emp2->getName() << " bonus: $" << emp2->calculateBonus() << endl;
    cout << emp3->getName() << " bonus: $" << emp3->calculateBonus() << endl;
    
    // Display information
    cout << "\nEmployee Information:\n";
    emp1->displayInfo();
    cout << endl;
    emp2->displayInfo();
    cout << endl;
    emp3->displayInfo();
    cout << endl;
    
    // Clean up
    delete emp1;
    delete emp2;
    delete emp3;
}

// =========================================================================
// 4. Abstraction - Interfaces and Abstract Classes
// =========================================================================

// Abstract base class (interface) with pure virtual functions
class Shape {
public:
    virtual double getArea() const = 0; // Pure virtual function
    virtual double getPerimeter() const = 0; // Pure virtual function
    virtual void display() const = 0; // Pure virtual function
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;
    const double PI = 3.14159;
    
public:
    Circle(double radius) : radius(radius) {}
    
    double getArea() const override {
        return PI * radius * radius;
    }
    
    double getPerimeter() const override {
        return 2 * PI * radius;
    }
    
    void display() const override {
        cout << "Circle - Radius: " << radius << ", ";
        cout << "Area: " << getArea() << ", Perimeter: " << getPerimeter() << endl;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;
    
public:
    Rectangle(double width, double height) : width(width), height(height) {}
    
    double getArea() const override {
        return width * height;
    }
    
    double getPerimeter() const override {
        return 2 * (width + height);
    }
    
    void display() const override {
        cout << "Rectangle - Width: " << width << ", Height: " << height << ", ";
        cout << "Area: " << getArea() << ", Perimeter: " << getPerimeter() << endl;
    }
};

class Triangle : public Shape {
private:
    double sideA;
    double sideB;
    double sideC;
    
public:
    Triangle(double a, double b, double c) : sideA(a), sideB(b), sideC(c) {
        if (!isValid()) {
            throw invalid_argument("Invalid triangle sides");
        }
    }
    
    bool isValid() const {
        return (sideA + sideB > sideC) && (sideA + sideC > sideB) && (sideB + sideC > sideA);
    }
    
    double getArea() const override {
        double s = (sideA + sideB + sideC) / 2;
        return sqrt(s * (s - sideA) * (s - sideB) * (s - sideC)); // Heron's formula
    }
    
    double getPerimeter() const override {
        return sideA + sideB + sideC;
    }
    
    void display() const override {
        cout << "Triangle - Sides: " << sideA << ", " << sideB << ", " << sideC << ", ";
        cout << "Area: " << getArea() << ", Perimeter: " << getPerimeter() << endl;
    }
};

// =========================================================================
// 5. Operator Overloading
// =========================================================================

class Complex {
private:
    double real;
    double imaginary;
    
public:
    Complex(double real = 0, double imaginary = 0) : real(real), imaginary(imaginary) {}
    
    // Overload + operator
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }
    
    // Overload - operator
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }
    
    // Overload * operator
    Complex operator*(const Complex& other) const {
        double r = real * other.real - imaginary * other.imaginary;
        double i = real * other.imaginary + imaginary * other.real;
        return Complex(r, i);
    }
    
    // Overload << operator for output
    friend ostream& operator<<(ostream& os, const Complex& complex) {
        os << complex.real;
        if (complex.imaginary >= 0) {
            os << " + " << complex.imaginary << "i";
        } else {
            os << " - " << abs(complex.imaginary) << "i";
        }
        return os;
    }
    
    // Overload >> operator for input
    friend istream& operator>>(istream& is, Complex& complex) {
        cout << "Enter real part: ";
        is >> complex.real;
        cout << "Enter imaginary part: ";
        is >> complex.imaginary;
        return is;
    }
    
    void display() const {
        cout << real << (imaginary >= 0 ? " + " : " - ") << abs(imaginary) << "i";
    }
};

// =========================================================================
// 6. Templates and Generics
// =========================================================================

// Function template
template <typename T>
T findMax(const T& a, const T& b) {
    return (a > b) ? a : b;
}

// Class template
template <typename T>
class Stack {
private:
    vector<T> elements;
    
public:
    void push(const T& element) {
        elements.push_back(element);
    }
    
    void pop() {
        if (elements.empty()) {
            throw out_of_range("Stack is empty");
        }
        elements.pop_back();
    }
    
    T top() const {
        if (elements.empty()) {
            throw out_of_range("Stack is empty");
        }
        return elements.back();
    }
    
    bool isEmpty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
    
    void display() const {
        cout << "Stack elements: ";
        for (const T& element : elements) {
            cout << element << " ";
        }
        cout << endl;
    }
};

// =========================================================================
// 7. Smart Pointers (Modern C++)
// =========================================================================

void demonstrateSmartPointers() {
    cout << "\n=== Smart Pointers Demonstration ===\n";
    
    // Unique pointer - sole ownership
    cout << "\n1. Unique Pointer:\n";
    unique_ptr<Employee> emp1 = make_unique<Manager>("Alice Brown", 38, 95000, "Operations", 6);
    emp1->displayInfo();
    cout << "Bonus: $" << emp1->calculateBonus() << endl;
    
    // Shared pointer - shared ownership
    cout << "\n2. Shared Pointer:\n";
    shared_ptr<Employee> emp2 = make_shared<Developer>("Charlie Davis", 28, 85000, "R&D", "Python", 30000);
    shared_ptr<Employee> emp2Copy = emp2; // Reference count becomes 2
    
    cout << "Original pointer: ";
    emp2->displayInfo();
    cout << "Copy pointer: ";
    emp2Copy->displayInfo();
    
    cout << "Reference count: " << emp2.use_count() << endl;
    
    // Weak pointer - does not affect reference count
    cout << "\n3. Weak Pointer:\n";
    weak_ptr<Employee> emp2Weak = emp2;
    cout << "Reference count after weak pointer: " << emp2.use_count() << endl;
    
    if (auto locked = emp2Weak.lock()) {
        cout << "Weak pointer is valid: ";
        locked->displayInfo();
    }
}

// =========================================================================
// 8. Exception Handling
// =========================================================================

void demonstrateExceptionHandling() {
    cout << "\n=== Exception Handling Demonstration ===\n";
    
    try {
        // Test age validation
        cout << "\n1. Trying to create employee with invalid age:\n";
        Employee invalidEmp("Invalid Age", 17, 50000, "Testing");
    } catch (const invalid_argument& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    try {
        // Test salary validation
        cout << "\n2. Trying to set negative salary:\n";
        Employee validEmp("Valid Emp", 30, 60000, "Finance");
        validEmp.setSalary(-1000);
    } catch (const invalid_argument& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    try {
        // Test stack underflow
        cout << "\n3. Trying to pop from empty stack:\n";
        Stack<int> emptyStack;
        emptyStack.pop();
    } catch (const out_of_range& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
}

// =========================================================================
// 9. Static Members and Singleton Pattern
// =========================================================================

class Counter {
private:
    static int count; // Static data member (class-wide)
    
public:
    Counter() {
        count++;
    }
    
    ~Counter() {
        count--;
    }
    
    static int getCount() { // Static member function
        return count;
    }
};

int Counter::count = 0; // Initialize static data member

// Singleton design pattern
class Singleton {
private:
    static Singleton* instance;
    string data;
    
    // Private constructor - cannot be instantiated directly
    Singleton(string value) : data(value) {}
    
    // Disable copy operations
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
public:
    static Singleton* getInstance(string value) {
        if (instance == nullptr) {
            instance = new Singleton(value);
        }
        return instance;
    }
    
    void displayData() const {
        cout << "Singleton data: " << data << endl;
    }
    
    void setData(string value) {
        data = value;
    }
};

Singleton* Singleton::instance = nullptr;

// =========================================================================
// 10. Virtual Inheritance and Diamond Problem
// =========================================================================

class Base {
protected:
    int value;
    
public:
    Base(int v) : value(v) {
        cout << "Base constructor - value: " << value << endl;
    }
    
    virtual void display() const {
        cout << "Base - Value: " << value << endl;
    }
};

class Derived1 : virtual public Base { // Virtual inheritance
public:
    Derived1(int v) : Base(v) {
        cout << "Derived1 constructor" << endl;
    }
    
    void display() const override {
        cout << "Derived1 - Value: " << value << endl;
    }
};

class Derived2 : virtual public Base { // Virtual inheritance
public:
    Derived2(int v) : Base(v) {
        cout << "Derived2 constructor" << endl;
    }
    
    void display() const override {
        cout << "Derived2 - Value: " << value << endl;
    }
};

class FinalDerived : public Derived1, public Derived2 { // No diamond problem
public:
    FinalDerived(int v) : Base(v), Derived1(v), Derived2(v) {
        cout << "FinalDerived constructor" << endl;
    }
    
    void display() const override {
        cout << "FinalDerived - Value: " << value << endl;
    }
};

// =========================================================================
// Main Function for Testing
// =========================================================================
int main() {
    cout << "=== C++ Object-Oriented Programming Concepts ===\n";
    
    // 1. Encapsulation
    cout << "\n1. Encapsulation (Employee Class):\n";
    Employee emp("John Smith", 35, 75000, "Engineering");
    emp.displayInfo();
    cout << "Bonus: $" << emp.calculateBonus() << endl;
    
    emp.setSalary(80000);
    cout << "New salary: $" << emp.getSalary() << endl;
    cout << "New bonus: $" << emp.calculateBonus() << endl;
    
    // 2. Inheritance and Polymorphism
    demonstratePolymorphism();
    
    // 3. Abstraction
    cout << "\n=== Abstraction Demonstration ===\n";
    vector<Shape*> shapes;
    shapes.push_back(new Circle(5));
    shapes.push_back(new Rectangle(4, 6));
    shapes.push_back(new Triangle(3, 4, 5));
    
    for (Shape* shape : shapes) {
        shape->display();
    }
    
    for (Shape* shape : shapes) {
        delete shape;
    }
    
    // 4. Operator Overloading
    cout << "\n=== Operator Overloading Demonstration ===\n";
    Complex c1(3, 4), c2(1, -2);
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c1 + c2 = " << c1 + c2 << endl;
    cout << "c1 - c2 = " << c1 - c2 << endl;
    cout << "c1 * c2 = " << c1 * c2 << endl;
    
    // 5. Templates and Generics
    cout << "\n=== Templates and Generics Demonstration ===\n";
    cout << "Max of 5 and 10: " << findMax(5, 10) << endl;
    cout << "Max of 'a' and 'z': " << findMax('a', 'z') << endl;
    cout << "Max of 3.14 and 2.71: " << findMax(3.14, 2.71) << endl;
    
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    intStack.display();
    cout << "Top: " << intStack.top() << endl;
    intStack.pop();
    cout << "After pop: ";
    intStack.display();
    
    Stack<string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.display();
    cout << "Top: " << stringStack.top() << endl;
    
    // 6. Smart Pointers
    demonstrateSmartPointers();
    
    // 7. Exception Handling
    demonstrateExceptionHandling();
    
    // 8. Static Members and Singleton
    cout << "\n=== Static Members and Singleton Demonstration ===\n";
    cout << "Initial count: " << Counter::getCount() << endl;
    
    Counter c1_counter;
    Counter c2_counter;
    cout << "After creating 2 counters: " << Counter::getCount() << endl;
    
    {
        Counter c3_counter;
        cout << "Inside scope: " << Counter::getCount() << endl;
    }
    cout << "Outside scope: " << Counter::getCount() << endl;
    
    // Singleton
    Singleton* singleton1 = Singleton::getInstance("First singleton");
    Singleton* singleton2 = Singleton::getInstance("Second singleton");
    cout << "Singleton 1: ";
    singleton1->displayData();
    cout << "Singleton 2: ";
    singleton2->displayData();
    cout << "Same instance? " << (singleton1 == singleton2 ? "Yes" : "No") << endl;
    
    // 9. Virtual Inheritance (Diamond Problem Solution)
    cout << "\n=== Virtual Inheritance Demonstration ===\n";
    FinalDerived finalDerived(42);
    finalDerived.display();
    
    return 0;
}

/*
Key Takeaways:

1. Encapsulation:
   - Data hiding through access modifiers (private, protected, public)
   - Encapsulates data and methods that operate on that data
   - Provides controlled access through getters and setters
   - Prevents direct manipulation of internal state

2. Inheritance:
   - Creates new classes from existing ones
   - Promotes code reuse
   - Base class provides common functionality
   - Derived classes inherit and extend functionality
   - Single inheritance (one base class), multiple inheritance (multiple base classes)
   - Virtual inheritance solves diamond problem

3. Polymorphism:
   - Runtime polymorphism (virtual functions, overrides)
   - Compile-time polymorphism (function overloading, operator overloading)
   - Same interface, different implementations
   - Enables generic programming

4. Abstraction:
   - Hides complex implementation details, exposes only necessary interfaces
   - Abstract classes with pure virtual functions
   - Interfaces define contracts for derived classes
   - Concrete implementations provide specific functionality

5. Operator Overloading:
   - Allows user-defined types to behave like built-in types
   - Overload operators to support natural syntax
   - Friend functions for global operator overloads
   - Overload << and >> for I/O operations

6. Templates and Generics:
   - Function templates: Generic functions that work with any type
   - Class templates: Generic classes that work with any type
   - Enable type-safe, reusable code
   - Compile-time type checking

7. Smart Pointers (C++11 and later):
   - Unique pointer: Sole ownership, automatic destruction
   - Shared pointer: Shared ownership, reference counting
   - Weak pointer: Non-owning reference, doesn't affect lifetime
   - Prevents memory leaks

8. Exception Handling:
   - Try-catch blocks for error handling
   - Throw exceptions to indicate errors
   - Custom exception classes
   - RAII (Resource Acquisition Is Initialization)

9. Static Members and Singleton Pattern:
   - Static data members: Shared by all instances
   - Static member functions: Can be called without instance
   - Singleton pattern: Ensures only one instance exists

10. Virtual Inheritance (Diamond Problem):
    - Occurs in multiple inheritance when base class is inherited twice
    - Solved using virtual inheritance
    - Ensures only one copy of base class is inherited

11. Advanced OOP Features:
    - RTTI (Run-Time Type Information): typeid and dynamic_cast
    - Const correctness: const member functions, const objects
    - Copy and move semantics: copy constructor, copy assignment, move constructor
    - Initialization lists: Efficient initialization of base and member objects

These concepts form the foundation of object-oriented programming in C++.
*/
