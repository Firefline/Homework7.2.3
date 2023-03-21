// Homework7.2.3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

class Data
{
public:
    std::mutex m1, m2;

    int number_1 = 42;
    int number_2 = 0451;
    char letter_1 = 'y';
    char letter_2 = 'n';
    std::string word_1 = "hello";
    std::string word_2 = "world";
public:
    Data()
    {

    }

    template <typename T>
    T swap_lock(T& parameter_1, T& parameter_2) noexcept
    {
        lock(m1, m2);
        T temp = std::move(parameter_1);
        std::lock_guard <std::mutex> la{ m1, std::adopt_lock };
        parameter_1 = std::move(parameter_2);
        std::lock_guard <std::mutex> lb{m2, std::adopt_lock};
        parameter_2 = std::move(temp);
        return parameter_1, parameter_2;
    }

    template <typename T>
    T swap_scoped(T& parameter_1, T& parameter_2) noexcept
    {
        std::scoped_lock lock{ m1, m2 };
        T temp = std::move(parameter_1);
        parameter_1 = std::move(parameter_2);
        parameter_2 = std::move(temp);
        return parameter_1, parameter_2;
    }

    template <typename T>
    T swap_unique(T& parameter_1, T& parameter_2) noexcept
    {
        T temp = std::move(parameter_1);
        std::unique_lock <std::mutex> grd_1(m1);
        parameter_1 = std::move(parameter_2);
        std::unique_lock <std::mutex> grd_2(m2);
        parameter_2 = std::move(temp);
        return parameter_1, parameter_2;
    }

    template <typename T>
    T print(T& parameter_1, T& parameter_2) noexcept
    {
        std::cout << "Значение 1: " << parameter_1 << std::endl;
        std::cout << "Значение 2: " << parameter_2 << std::endl;

        return parameter_1, parameter_2;
    }
};



int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    Data data;

    std::cout << "До обмена: " << std::endl;
    data.print(data.number_1, data.number_2);

    data.swap_lock(data.number_1, data.number_2);

    std::cout << "После обмена (lock): " << std::endl;
    data.print(data.number_1, data.number_2);

    data.swap_scoped(data.number_1, data.number_2);

    std::cout << "После обмена (scoped_lock): " << std::endl;
    data.print(data.number_1, data.number_2);

    data.swap_unique(data.number_1, data.number_2);

    std::cout << "После обмена (unique_lock): " << std::endl;
    data.print(data.number_1, data.number_2);
}