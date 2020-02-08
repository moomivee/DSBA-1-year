#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono>
#include <ctime>
#include "linkedlist.h"



//-------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------Quick--Sort---------------------------------------------------------------------------------------//

template <class iter>
void Partition(iter it1, iter it2, iter& pivot) // Quick-Sort for vectors of string/int
{
    std::iter_swap(pivot, std::prev(it2));
    pivot =std::prev(it2);
    iter left = it1;
    while (pivot != left)
    {
        if (*left <= *pivot) 
        {
            ++left;
        } 
        else
        {
            std::iter_swap(left, pivot);
            --pivot;
            std::iter_swap(left, pivot);
        }
    }
}

template <class iter>
void QuickSortRandom(iter it1, iter it2, std::mt19937& gen) // Quick-Sort for vectors of string/int
{
    if (it2 - it1 < 2)
    {
        return;
    }
    std::uniform_int_distribution<int> distr(0, it2 - it1 - 1);
    iter pivot = it1 + distr(gen);
    Partition(it1, it2, pivot);
    QuickSortRandom(it1, pivot, gen);
    QuickSortRandom(pivot, it2, gen);
}

template <class iter>
void QuickSort(iter it1, iter it2) // Quick-Sort for vectors of string/int
{
    std::mt19937 gen(time(0));
    QuickSortRandom(it1, it2, gen);
}

template<class T>
void ListPartition(typename LinkedList<T>::Node* it1, typename LinkedList<T>::Node* it2,
typename LinkedList<T>::Node*& pivot) // Quick-Sort for linked-list of string/int
{
    LinkedList<T>::Node::Swap(pivot, it2->getPrev());
    pivot = it2->getPrev();
    typename LinkedList<T>::Node* left = it1;
    while (pivot != left)
    {
        if (left->getValue() <= pivot->getValue())
        {
            left = left->getNext();
        }
        else
        {
            LinkedList<T>::Node::Swap(left, pivot);
            pivot = pivot->getPrev();
            LinkedList<T>::Node::Swap(left, pivot);
        }
    }
}

template<class T>
void ListQuickSortRandom(typename LinkedList<T>::Node* it1, 
typename LinkedList<T>::Node* it2, std::mt19937& gen) // Quick-Sort for linked-list of string/int
{
    int bound = 0;
    typename LinkedList<T>::Node* tmp = it1;
    while (tmp != it2) 
    {
        tmp = tmp->getNext();
        ++bound;
    }
    if (bound < 2)
    {
        return;
    }
    std::uniform_int_distribution<int> distr(0, bound - 1);
    int steps = distr(gen);
    typename LinkedList<T>::Node* pivot = it1;
    for (int step = 0; step < steps; ++step)
    {
        pivot = pivot->getNext();
    }
    ListPartition<T>(it1, it2, pivot);
    ListQuickSortRandom<T>(it1, pivot, gen);
    ListQuickSortRandom<T>(pivot, it2, gen);
}

template<class T>
void QuickSort(typename LinkedList<T>::Node* it1, 
typename LinkedList<T>::Node* it2) // Quick-Sort for linked-list of string/int
{
    std::mt19937 gen(time(0));
    ListQuickSortRandom<T>(it1, it2, gen);
}


//-------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------Megre--Sort-----------------------------------------------------------------------------------//

template <typename iter, class T>
void Megre(iter it1, iter it2, iter it3) 
{
    iter first = it1;
    iter second = it2;

    std::vector<T> tmp;

    tmp.reserve(it3 - it1);

    while (first != it2 || second != it3)
    {
        if (second == it3 || (first != it2 && *first <= *second))
        {
            tmp.push_back(*first);
            ++first;
        }
        else
        {
            tmp.push_back(*second);
            ++second;
        }
    }
    iter curr = it1; 
    for (T elem : tmp)
    {
        *curr = elem;
        ++curr;
    }
}

template<class iter, typename T>
void MegreSort(iter it1, iter it2)
{
    if (it2 - it1 == 1)
    {
        return;
    }
    iter medium = it1 + (it2 - it1)/2;
    MegreSort<iter, T>(it1, medium);
    MegreSort<iter, T>(medium, it2);
    Megre<iter, T>(it1, medium, it2);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------Insertion--Sort-----------------------------------------------------------------------------------//

template<class T>
void insertionSortV(std::vector<T> &vec) // Insertion-Sort for vectors of string/int
{
    if (vec.size() < 2)
    {
        return;
    }
    for(int i = 1; i<vec.size(); ++i)
    {
        auto cur = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j]>cur)
        {
            vec[j+1] = vec[j];
            --j;
        }
        vec[j+1]=cur;
    }
}

template<class T>
void insertionSort( LinkedList<T> &list) // Insertion-Sort for linked-list of string/int
{
    if (list.getSize() < 2)
    {
        return;
    }
    for (auto node = list.getPreHead()->getNext()->getNext(); 
         node != list.getPreHead(); node = node->getNext())
    {
        auto current = node->getValue();
        auto previos_node = node->getPrev();
        while (previos_node != list.getPreHead() && previos_node->getValue() > current)
        {
            previos_node->getNext()->setValue(previos_node->getValue());
            previos_node = previos_node->getPrev();
        }
        previos_node->getNext()->setValue(current);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------Counting--Sort------------------------------------------------------------------------------------//

void CountingSort(std::vector<int>& vec) // Counting-Sort for vectors of int
{
    int maximum = *std::max_element(vec.begin(), vec.end());
    int minimum = *std::min_element(vec.begin(), vec.end());
    std::vector<int> counting(maximum - minimum + 1, 0);
    for (int num : vec)
    {
        ++counting[num - minimum];
    }
    int current = 0;
    for (int step = 0; step < vec.size(); ++step)
    {
        while(counting[current] == 0)
        {
            ++current;
        }
        vec[step] = current + minimum;
        --counting[current];
    }
}


//-------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------Radix--Sort---------------------------------------------------------------------------------------//

int GetDigit(int num, int digit, int base)
{
    for (int step = 0; step < digit; ++step) {
        num /= base;
    }
    return num % base;
}

int DigitNum(int num, int base)
{
    int answer = 0;
    while (num != 0)
    {
        num /= base;
        ++answer;
    }
    return answer;
}


void RadixSort(std::vector<int>& vec, int base)
{
    int digits = DigitNum(*std::max_element(vec.begin(), vec.end()), base);
    std::vector<int> counting_digit(base);
    std::vector<int> counting_less(base);
    std::vector<int> vec_copy(vec.size());
    for (int digit = 0; digit < digits; ++digit)
    {
        counting_digit.assign(base, 0);
        counting_less.assign(base, 0);
        for (int num : vec)
        {
            ++counting_digit[GetDigit(num, digit, base)];
        }
        for (int dig = 1; dig < base; ++ dig)
        {
            counting_less[dig] = counting_less[dig - 1] + counting_digit[dig - 1];
        }
        for (size_t step = 0; step < vec.size(); ++step)
        {
            int dig = GetDigit(vec[step], digit, base);
            vec_copy[counting_less[dig]] = vec[step];
            ++counting_less[dig];
        }
        vec = vec_copy;
    }
}


//-------------------------------------------------------------------------------------------------------------------------------------------------//

template<typename T>
std::ostream& operator<<(std::ostream& s, std::vector<T> vec) // output for vectors 
{
    for (auto elem : vec)
    {
        s << elem << ' ';
    }
    s << '\n';
    return s;
}

void createVector(std::vector <int> &vector_i)
{
    while(vector_i.size() < 500)
    {
        int des = 0 + rand()%10;
        int cto = 0 + rand()%100;
        int tys = 0 + rand()%1000;

        vector_i.push_back(des);
        vector_i.push_back(cto);
        vector_i.push_back(tys);
    }
}

void createVectorOfint(std::vector <int> &vector_i)
{
    while(vector_i.size() < 500)
    {
        int des = 0 + rand()%10;
        int x = - ( rand() % 10 );
        int cto = 0 + rand()%100;
        int r = - ( rand() % 100 );
        int tys = 0 + rand()%1000;
        int p = - ( rand() % 1000 );
        
        vector_i.push_back(des);
        vector_i.push_back(x);
        vector_i.push_back(r);
        vector_i.push_back(cto);
        vector_i.push_back(p);
        vector_i.push_back(tys);
    }
}


void createVectorOfstrings(int size, std::vector<std::string> &vec) 
{
    srand(time(NULL));
    std::string text;

    for ( int i = 0, j = 0; i < size; i++ ) 
    {
        j = rand() % 10 + 1;
        
        if ( j > size - i ) j = size - i;
        i += j;
        
        for ( int k = 0; k < j; k++ ) 
        {
            text += (char)(rand() % 26 + 97);
        }
        text += ' ';
    }
    vec.push_back(text);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------Testing-------------------------------------------------------------------------------------------//

int main()
{
    std::vector<int> vector_i;
    createVectorOfint(vector_i);

    std::vector<std::string> vector_s;
    createVectorOfstrings(500, vector_s);

    std::vector<int> vector_r; //for radix only
    createVector(vector_r);

    LinkedList<int> linked_l_i;
    LinkedList<std::string> linked_l_s;

    for (int elem : vector_i)
    {
        linked_l_i.appendValue(elem);
    }
    for (std::string elem : vector_s)
    {
        linked_l_s.appendValue(elem);
    }
    
//-----Quick

    auto z1 = std::chrono::steady_clock::now();   
    QuickSort(vector_i.begin(), vector_i.end());
    auto z2 = std::chrono::steady_clock::now();
    auto z3 = std::chrono::duration_cast<std::chrono::nanoseconds>(z2 - z1);
    std::cout << "Time: "<< z3.count()<< "\n";
    std::cout <<"Quick-sort for vector of integers:"<< " "<< vector_i;
    std::cout << "\n";

//-----Quick

    auto f1 = std::chrono::steady_clock::now();
    QuickSort(vector_s.begin(), vector_s.end());
    auto f2 = std::chrono::steady_clock::now();
    auto f3 = std::chrono::duration_cast<std::chrono::nanoseconds>(f2 - f1);
    std::cout << "Time: "<< f3.count()<< "\n";
    std::cout <<"Quick-sort for vector of strings:"<< " "<< vector_s;
    std::cout << "\n";
    
//-----Quick
    
    auto s1 = std::chrono::steady_clock::now();
    QuickSort<int>(linked_l_i.getPreHead()->getNext(), linked_l_i.getPreHead());
    auto s2 = std::chrono::steady_clock::now();
    auto s3 = std::chrono::duration_cast<std::chrono::nanoseconds>(s2 - s1);
    std::cout << "Time: "<< s3.count()<< "\n";
    std::cout <<"Quick-sort for linked-list of integers:"<< " "<< linked_l_i << '\n';
    std::cout << "\n";
//-----Quick

    auto b1 = std::chrono::steady_clock::now();
    QuickSort<std::string>(linked_l_s.getPreHead()->getNext(), linked_l_s.getPreHead());
    auto b2 = std::chrono::steady_clock::now();
    auto b3 = std::chrono::duration_cast<std::chrono::nanoseconds>(b2 - b1);
    std::cout << "Time: "<< b3.count()<< "\n";
    std::cout <<"Quick-sort for linked-list of strings:"<< " "<< linked_l_s << '\n';
    std::cout << "\n";  

//-----Megre  

    auto l1 = std::chrono::steady_clock::now();
    MegreSort<std::vector<std::string>::iterator, std::string>(vector_s.begin(), vector_s.end());
    auto l2 = std::chrono::steady_clock::now();
    auto l3 = std::chrono::duration_cast<std::chrono::nanoseconds>(l2 - l1);
    std::cout << "Time: "<< l3.count()<< "\n";
    std::cout <<"Megre-sort for vector of strings:"<< " "<< vector_s;
    std::cout << "\n";

//-----Megre
    auto h1 = std::chrono::steady_clock::now();
    MegreSort<std::vector<int>::iterator, int>(vector_i.begin(), vector_i.end());
    auto h2 = std::chrono::steady_clock::now();
    auto h3 = std::chrono::duration_cast<std::chrono::nanoseconds>(h2 - h1);
    std::cout << "Time: "<< h3.count()<< "\n";
    std::cout <<"Megre-sort for vector of integers:"<< " "<< vector_i;
    std::cout << "\n";

//-----Insertion
    auto u1 = std::chrono::steady_clock::now();
    insertionSortV(vector_i);
    auto u2 = std::chrono::steady_clock::now();
    auto u3 = std::chrono::duration_cast<std::chrono::nanoseconds>(u2 - u1);
    std::cout << "Time: "<< u3.count()<< "\n";
    std::cout <<"Insertion-sort for vector of integers:"<< " "<< vector_i;
    std::cout << "\n";

//-----Insertion
    auto p1 = std::chrono::steady_clock::now();
    insertionSortV(vector_s);
    auto p2 = std::chrono::steady_clock::now();
    auto p3 = std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1);
    std::cout << "Time: "<< p3.count()<< "\n";
    std::cout <<"Insertion-sort for vector of strings:"<< " "<< vector_s;
    std::cout << "\n";

//-----Insertion
    auto g1 = std::chrono::steady_clock::now();
    insertionSort(linked_l_i);
    auto g2 = std::chrono::steady_clock::now();
    auto g3 = std::chrono::duration_cast<std::chrono::nanoseconds>(g2 - g1);
    std::cout << "Time: "<< g3.count()<< "\n";
    std::cout <<"Insertion-sort for linked-list of integers:"<< " "<< linked_l_i << '\n';
    std::cout << "\n";

//-----Insertion
    auto o1 = std::chrono::steady_clock::now();
    insertionSort(linked_l_s);
    auto o2 = std::chrono::steady_clock::now();
    auto o3 = std::chrono::duration_cast<std::chrono::nanoseconds>(o2 - o1);
    std::cout << "Time: "<< o3.count()<< "\n";
    std::cout <<"Insertion-sort for linked-list of strings:"<< " "<< linked_l_s << '\n';
    std::cout << "\n";

//-----Counting
    auto a1 = std::chrono::steady_clock::now();
    CountingSort(vector_i);
    auto a2 = std::chrono::steady_clock::now();
    auto a3 = std::chrono::duration_cast<std::chrono::nanoseconds>(a2 - a1);
    std::cout << "Time: "<< a3.count()<< "\n";
    std::cout <<"Counting-sort for vector of integers:"<< " "<< vector_i;
    std::cout << "\n";

//-----Radix
    auto t1 = std::chrono::steady_clock::now();
    RadixSort(vector_r, 10); 
    auto t2 = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "Time: "<< elapsed.count()<< "\n";
    std::cout <<"Radix-sort (base = 10) for vector of integers:"<< " "<< vector_r;
    std::cout << "\n";

//-----Radix
    auto q1 = std::chrono::steady_clock::now();
    RadixSort(vector_r, 2); 
    auto q2 = std::chrono::steady_clock::now();
    auto q3 = std::chrono::duration_cast<std::chrono::nanoseconds>(q2 - q1);
    std::cout << "Time: "<< q3.count()<< "\n";
    std::cout <<"Radix-sort (base = 2) for vector of integers:"<< " "<< vector_r;
    std::cout << "\n";

return 0;

}