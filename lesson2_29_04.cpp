
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <string_view>


class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::string m_name;
    std::chrono::time_point<clock_t> m_beg;
    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }

public:
    Timer() : m_beg(clock_t::now()) { }
    Timer(std::string name) : m_name(name), m_beg(clock_t::now()) { }

    void start(std::string name) {
        m_name = name;
        m_beg = clock_t::now();
    }
    void print() const {
        std::cout << m_name << ":\t" << elapsed() * 1000 << " ms";
    }
};


// Задание 1. 
template <typename T>
void Swap(T*& first, T*& second)
{
    T* tmp = nullptr;
    tmp = first;
    first = second;
    second = tmp;
}

// Задание 2.
template <typename T>
void SortPointer(std::vector<T*>& pointers)
{
    std::sort(begin(pointers), end(pointers), [](T* left, T* right)
        {
            return *left < *right;
        });
}


int main()
{
    setlocale(LC_ALL, "Russian");
    // Задание 1.
    std::cout << "Task 1." << std::endl;
    int var1 = 1;
    int var2 = 5;
    int* first = &var1;
    int* second = &var2;
    std::cout << "Befor swap first " << *first << ", second " << *second << std::endl;
    Swap(first, second);
    std::cout << "After swap first " << *first << ", second " << *second << std::endl;


    // Задание 2. 
    std::cout << "Task 2." << std::endl;
    std::vector<int> numbers = { 4, 1, 7, 5, 3, 6, 2 };
    std::vector<int*> pointers;
    std::cout << "Befor SortPointers " << std::endl;
    for (auto& x : numbers)
    {
        pointers.push_back(&x);
        std::cout << pointers[pointers.size() - 1] << " : " << *pointers[pointers.size() - 1] << std::endl;
    };
    SortPointer(pointers);
    std::cout << "After SortPointers " << std::endl;
    for (auto& x : pointers)
    {
        std::cout << x << " : " << *x << std::endl;
    };



    // Задание 3.
    std::cout << "Task 3." << std::endl;
    std::ifstream file("War and peace.txt");
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0);
    std::string s(size, ' ');
    file.read(&s[0], size);
    std::string vowelLetters = "аАеЕёЁиИоОуУыЫэЭюЮяЯ";

    int count = 0;
    Timer timer("1. count_if and find");
    count = std::count_if(s.begin(), s.end(), [&vowelLetters](char& c)
        {
            return vowelLetters.find(c) != std::string::npos;
        });
    timer.print();
    std::cout << '\t' << "Count of vowel letters " << count << std::endl;

    count = 0;
    timer.start("2. count_if and for");
    count = std::count_if(s.begin(), s.end(), [&vowelLetters](char& c)
        {
            for (size_t i = 0; i < vowelLetters.size(); ++i)
            {
                if (vowelLetters[i] == c)
                    return true;

            }
            return false;
        });
    timer.print();
    std::cout << '\t' << "Count of vowel letters " << count << std::endl;


    count = 0;
    timer.start("3. for and find   ");
    for (size_t j = 0; j < s.size(); ++j)
    {
        if (vowelLetters.find(s[j]) != std::string::npos)
            ++count;
    };
    timer.print();
    std::cout << '\t' << "Count of vowel letters " << count << std::endl;

    count = 0;
    timer.start("4. for and for    ");
    for (size_t j = 0; j < s.size(); ++j)
    {
        for (size_t i = 0; i < vowelLetters.size(); ++i)
        {
            if (s[j] == vowelLetters[i])
            {
                ++count;
                break;
            }
        }
    }

    timer.print();
    std::cout << '\t' << "Count of vowel letters " << count << std::endl;



}
