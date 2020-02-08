
#include <iostream>
#include <vector>


template <typename T, typename TPred>
void heapsort(T& a, size_t size, TPred pred)
{
    buildHeap(a, size, pred);

    for (size_t i = size - 1; i >= 1; i--)
    {
        std::swap(a[i], a[0]);
        size--;
        heapify(a, size, 0, pred);
    }
}

template <typename T, typename TPred>
void heapify(T& a, size_t size, size_t i, TPred pred)
{
    size_t parent = i;
    size_t left = (size_t)2*i + (size_t)1;
    size_t right = (size_t)2*i + (size_t)2;
    if ((left < size) && (a[left] > a[parent]))
        parent = left;
    if ((right < size) && (a[right] > a[parent])) 
        parent = right;
    if (parent != i)
    {
        std::swap(a[i], a[parent]);
        heapify(a, size, parent, pred);
    }
}

template <typename T, typename TPred>
void buildHeap(T& a, size_t size, TPred pred)
{
    size_t i = size/(size_t)2 + (size_t)1;
    while(i > 0)
    {
        heapify(a, size, i, pred);
        i--;
    }
    heapify(a, size, i, pred);
}

template<typename T>
std::ostream& operator<<(std::ostream& s, std::vector<T> vec) 
{
    for (auto elem : vec)
    {
        s << elem << ' ';
    }
    s << '\n';
    return s;
}

int main()
{
    std::vector<int> randVec{7,8,1,9,5,6};
    heapsort(randVec, randVec.size(), 0);
    std::cout << randVec; //но чет он не работает с моим тестом

    return 0;
}


