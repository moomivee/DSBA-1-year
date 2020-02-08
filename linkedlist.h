#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <algorithm>
#include <stdexcept>

template<typename T>
class LinkedList
{
public:

    class Node
    {
        friend class LinkedList;

    public:
        Node( const T& val = T(), Node* next = nullptr, Node* prev = nullptr) : _value{val}, _next(next) 
        {
        }
        static void Swap(Node* lhs, Node* rhs)
        {
            std::swap(lhs->_value, rhs->_value);
        }

    public:
        const T& getValue() const { return _value; }

        void setValue(const T& val) { _value = val; }

        Node* getNext()  { return _next; }
        const Node* getNext() const { return _next; }

        Node* getPrev()  { return _prev; }
        const Node* getPrev() const { return _prev; }

    protected:
        T _value;
        Node* _next;
        Node* _prev;
    };

public:
    LinkedList(): _preHead(new Node()), _size(0)
    {
        _preHead->_next = _preHead;
        _preHead->_prev = _preHead;
    }

    ~LinkedList() //деструктор
    {
        Node* cur = _preHead->_next;
        while(cur != _preHead)
        {
            Node* foll = cur->_next;
            delete cur;
            cur = foll;
        }
        delete _preHead;
    }

public:
    Node* insertNode(Node* newNode, Node* prev = nullptr) //вставка нового нода
    {
        if(!newNode)
            throw std::invalid_argument("Inserted node must not be null.");
        if(!prev)
            prev = _preHead;

        newNode->_next = prev->_next;
        prev->_next = newNode;
        newNode->_prev = prev;
        newNode->_next->_prev = newNode;

        ++_size;
        return newNode;
    }

    Node* insertValue(const T& val, Node* prev = nullptr) //вставка нового значения
    {
        Node* newNd = new Node(val);
        return insertNode(newNd, prev);
    }

    Node* prependNode(Node* newNode)
    {
        return insertNode(newNode);
    }

    Node* prependValue(const T& val)
    {
        return insertValue(val);
    }

    Node* getLastNode() const
    {
        return _preHead->_prev;
    }

    Node* appendNode(Node* newNode)
    {
        Node* last = getLastNode();
        return insertNode(newNode, last);
    }

    Node* appendValue(const T& val)
    {
        Node* newNd = new Node(val);
        return appendNode(newNd);
    }

    void removeNodeAfter(Node* prev)
    {
        if(!prev)
            throw std::invalid_argument("Can't remove a node after the null predecessor.");
        if(!prev->_next)
            return;      
        if (_size == 0)
        {
            throw std::runtime_error("It's empty");
        }
        if (prev->_next == _preHead) 
        {
            return;
        }

        Node* next = prev->_next->_next;
        prev->_next->_next = nullptr;

        delete prev->_next; 

        prev->_next = next;
        next->_prev = prev;

        --_size;
    }
public:
    Node* getPreHead() const { return _preHead; }
    size_t getSize() const { return _size; }
protected:
    Node* _preHead;
    size_t _size;
};

template<typename T>
std::ostream& operator<<(std::ostream& s, const LinkedList<T>& l)
{
    const typename LinkedList<T>::Node* cur = l.getPreHead()->getNext();
    while(cur != l.getPreHead())
    {
        s << cur->getValue();
        cur = cur->getNext();
        if(cur != l.getPreHead())
            s << std::string(" <-> ");
    }

    return s;
}

#endif // LINKED_LIST_H_
