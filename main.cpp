#include <iostream>
#include <concepts>
#include <string>
#include <type_traits>

template<typename T>
concept ComplexConcept =
    requires(T t) {
        { t.hash() } -> std::convertible_to<long>;
        { t.toString() } -> std::same_as<std::string>;
} &&
!std::has_virtual_destructor_v<T>;

// Пример класса, удовлетворяющего концепту
struct MyType {
    long hash() const { return 42; }
    std::string toString() const { return "MyType"; }
};

// Пример класса, НЕ удовлетворяющего концепту
struct MyVirtualType {
    virtual ~MyVirtualType() = default;
    long hash() const { return 123; }
    std::string toString() const { return "MyVirtualType"; }
};

// Функция, удовлетворящая ComplexConcept
template<ComplexConcept T>
void process(const T& obj) {
    std::cout << "Hash: " << obj.hash() << "\n";
    std::cout << "String: " << obj.toString() << "\n";
}

int main() {
    MyType obj;
    process(obj);
    return 0;
}