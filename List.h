//**************************************************************
// Programmer: Ayana Tran
// Date: 03/05/2024
// Purpose: header file - Node class, List class.
// Input: none
// Output: none
//**************************************************************

#include <iostream>
using namespace std;

#ifndef LIST_H
#define LIST_H

/// @brief Features a node with a forward and previous pointer
template <class T>
class Node
{
   private:
    T m_key;
    Node<T>* m_next;
    Node<T>* m_prev;

   public:
    /// @brief Construct an empty node
    Node();
    /// @brief Returns the `key` of type `T`
    T& key();
    /// @brief Returns a modifiable next node of type `T`
    Node<T>*& next();
    /// @brief Returns a modifiable previous node of type `T`
    Node<T>*& prev();
    /// @brief Returns a const `key` of type `T`
    const T& key() const;
    /// @brief Returns a const next node of type `T`
    const Node<T>* next() const;
    /// @brief Returns a const previous node of type `T`
    const Node<T>* prev() const;
};

/// @brief Features a linked list with basic search, delete, and insert
/// functions
template <class T>
class List
{
   private:
    Node<T>* m_head;
    Node<T>* m_tail;
    int m_length;

   public:
    /// @brief Construct an empty list
    List();
    /// @brief Deletes all items in list
    ~List();
    /// @brief Makes a deep copy and writes it to the calling object
    List(const List<T>& other);
    /// @brief Construct a list with preset values (extra)
    List(initializer_list<T> list);
    /// @brief Overloads the assignment operator to make a deep copy of the
    /// list and writes it to the calling object
    const List<T>& operator=(const List<T>& rhs);
    /// @brief Deletes all items in a list and nullifies unused pointers
    void cleanUp();
    /// @brief Copys all items in a list and write it to the calling object
    void copyList(const List<T>& other);
    /// @brief Searches the list for an item and returns the const node,
    /// otherwise returns null
    const Node<T>* searchList(T item) const;
    /// @brief Inserts an item in front of the list
    void insertFront(T item);
    /// @brief  Inserts an item to the back of the list
    void insertBack(T item);
    /// @brief Prints the items in the list from front to back
    void printList();
    void printNoSpc();
    /// @brief Prints the item in the list from back to front
    void printBackward();
    /// @brief Returns true after deleting an item, otherwise returns false
    bool deleteItem(T item);
    void deleteFront();
    void deleteBack();
    /// @brief Returns true if list contains no nodes, otherwise returns false
    bool isEmpty() const;
    /// @brief Returns the number of nodes in the list
    int length() const;

    /// @brief Iterates forward; uses standard iterator
    class iterator
    {
       private:
        Node<T>* m_node;

       public:
        iterator(Node<T>* node) : m_node(node)
        {
        }
        iterator& operator++()
        {
            if (m_node != NULL) m_node = m_node->next();
            return *this;
        }
        const iterator& operator++() const
        {
            if (m_node != NULL) m_node = m_node->next();
            return *this;
        }
        iterator operator++(int)
        {
            iterator retval = *this;
            ++(*this);
            return retval;
        }
        bool operator==(iterator other) const
        {
            return m_node == other.m_node;
        }
        bool operator!=(iterator other) const
        {
            return !(*this == other);
        }
        Node<T>* operator*()
        {
            return m_node;
        }
        const Node<T>* operator*() const
        {
            return m_node;
        }

        using difference_type = int;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = forward_iterator_tag;
    };

    /// @brief Returns beginning of iterator
    iterator begin()
    {
        return List::iterator(m_head);
    }
    const iterator begin() const
    {
        return List::iterator(m_head);
    }
    /// @brief Returns end of iterator
    iterator end()
    {
        return NULL;
    }
    const iterator end() const
    {
        return NULL;
    }

    /// @brief Iterates backwards; uses standard iterator
    class iteratorR
    {
       private:
        Node<T>* m_node;

       public:
        iteratorR(Node<T>* node) : m_node(node)
        {
        }
        iteratorR& operator++()
        {
            if (m_node != NULL) m_node = m_node->prev();
            return *this;
        }
        const iteratorR& operator++() const
        {
            if (m_node != NULL) m_node = m_node->prev();
            return *this;
        }
        iteratorR operator++(int)
        {
            iteratorR retval = *this;
            ++(*this);
            return retval;
        }
        bool operator==(iteratorR other) const
        {
            return m_node == other.m_node;
        }
        bool operator!=(iteratorR other) const
        {
            return !(*this == other);
        }
        Node<T>* operator*()
        {
            return m_node;
        }
        const Node<T>* operator*() const
        {
            return m_node;
        }

        using difference_type = int;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = forward_iterator_tag;
    };

    /// @brief Returns beginning of reverse iterator
    iteratorR rbegin()
    {
        return m_tail;
    }
    const iteratorR rbegin() const
    {
        return m_tail;
    }
    /// @brief Returns end of reverse iterator
    iteratorR rend()
    {
        return NULL;
    }
    const iteratorR rend() const
    {
        return NULL;
    }
};

template <class T>
inline Node<T>::Node()
{
    m_next = NULL;
    m_prev = NULL;
}

template <class T>
inline T& Node<T>::key()
{
    return m_key;
}

template <class T>
inline Node<T>*& Node<T>::next()
{
    return m_next;
}

template <class T>
inline Node<T>*& Node<T>::prev()
{
    return m_prev;
}

template <class T>
inline const T& Node<T>::key() const
{
    return m_key;
}

template <class T>
inline const Node<T>* Node<T>::next() const
{
    return m_next;
}

template <class T>
inline const Node<T>* Node<T>::prev() const
{
    return m_prev;
}

template <class T>
inline List<T>::List()
{
    m_head = NULL;
    m_tail = NULL;
    m_length = 0;
}

template <class T>
inline List<T>::~List()
{
    cleanUp();
}

template <class T>
inline void List<T>::cleanUp()
{
    // Exits function if list is empty
    if (m_head == NULL)
    {
        return;
    }
    Node<T>* current = m_head;

    while (current->next() != NULL)
    {
        current = current->next();
        delete current->prev();
        current->prev() = NULL;
    }

    delete current;
    current = NULL;
    m_head = NULL;
    m_tail = NULL;
    m_length = 0;
}

template <class T>
inline List<T>::List(const List<T>& other)
{
    copyList(other);
}

// Overloading the assignment operator
template <class T>
inline const List<T>& List<T>::operator=(const List<T>& rhs)
{
    // When using assignment operator with list on left-hand side and right-hand
    // side
    if (this != &rhs)
    {
        cleanUp();
        copyList(rhs);
    }
    return *this;
}

template <class T>
inline void List<T>::copyList(const List<T>& other)
{
    // Exits function is calling object is empty
    if (other.isEmpty())
    {
        return;
    }

    m_length = 0;

    Node<T> dummy;

    Node<T>* copyNode;
    Node<T>* copyPrev = &dummy;
    const Node<T>* origNode = other.m_head;

    while (origNode != NULL)
    {
        copyNode = new Node<T>();
        copyPrev->next() = copyNode;
        copyNode->prev() = copyPrev;
        copyNode->key() = origNode->key();

        origNode = origNode->next();
        copyPrev = copyPrev->next();
        ++m_length;
    }

    m_head = dummy.next();
    m_head->prev() = NULL;
    m_tail = copyNode;
    dummy.next() = NULL;
}

template <class T>
inline List<T>::List(initializer_list<T> list)  // insert at head, then at tail
{
    Node<T> dummy;
    Node<T>* current;

    current = &dummy;

    for (auto value : list)
    {
        current->next() = new Node<T>();
        current->next()->prev() = current;
        current = current->next();

        current->key() = value;
        ++m_length;
    }

    m_tail = current;
    m_head = dummy.next();
    m_head->prev() = NULL;
}

template <class T>
inline const Node<T>* List<T>::searchList(T item) const
{
    Node<T>* node = m_head;

    while (node != NULL && node->key() != item)
    {
        node = node->next();
    }

    return node;
}

template <class T>
inline void List<T>::insertFront(T item)
{
    Node<T>* newNode = new Node<T>();
    // Inserts new node, and points head and tail to it when list is empty
    if (isEmpty())
    {
        m_head = newNode;
        m_head->key() = item;
        m_tail = m_head;
    }
    else
    {
        newNode->key() = item;
        newNode->next() = m_head;
        m_head->prev() = newNode;
        m_head = newNode;
    }
    ++m_length;
}

template <class T>
inline void List<T>::insertBack(T item)
{
    Node<T>* newNode = new Node<T>();
    // Inserts new node, and points head and tail to it if list is empty
    if (isEmpty())
    {
        m_tail = newNode;
        m_tail->key() = item;
        m_head = m_tail;
    }
    else
    {
        newNode->key() = item;
        newNode->prev() = m_tail;
        m_tail->next() = newNode;
        m_tail = newNode;
    }
    ++m_length;
}

template <class T>
inline void List<T>::printList()
{
    if (m_head == NULL)
    {
        cout << "\nList is empty\n";
    }
    else
    {
        Node<T>* node = m_head;
        while (node != NULL)
        {
            cout << node->key() << " ";
            node = node->next();
        }
    }
}

template <class T>
inline void List<T>::printNoSpc()
{
    if (m_head == NULL)
    {
        cout << "\nList is empty\n";
    }
    else
    {
        Node<T>* node = m_head;
        while (node != NULL)
        {
            cout << node->key();
            node = node->next();
        }
    }
}

template <class T>
inline void List<T>::printBackward()
{
    if (m_tail == NULL)
    {
        cout << "\nList is empty\n";
    }
    else
    {
        Node<T>* node = m_tail;
        while (node != NULL)
        {
            cout << node->key() << " ";
            node = node->prev();
        }
    }
}

template <class T>
inline bool List<T>::deleteItem(T item)
{
    if (isEmpty())
    {
        return false;
    }

    Node<T>* currentNode = m_head;

    while (currentNode != NULL)
    {
        if (currentNode->key() == item)
        {
            // Edge case for head node. If not at head, point prev node to next
            // node
            if (currentNode->prev() != NULL)
            {
                currentNode->prev()->next() = currentNode->next();
            }
            // When deletion target is at head, move head pointer to next node
            else
            {
                m_head = currentNode->next();
            }
            // Edge case for last node. If not at tail, point next node to prev
            // node
            if (currentNode->next() != NULL)
            {
                currentNode->next()->prev() = currentNode->prev();
            }
            // When deletion target is at tail, move tail pointer to prev node
            else
            {
                m_tail = currentNode->prev();
            }

            delete currentNode;
            currentNode = NULL;
            --m_length;
            return true;
        }
        currentNode = currentNode->next();
    }

    return false;
}

template <class T>
inline void List<T>::deleteFront()
{
    if (isEmpty())
    {
        return;
    }

    Node<T>* dummy = m_head;

    m_head = m_head->next();
    m_head->prev() = NULL;
    delete dummy;
    dummy = NULL;
    --m_length;
}

template <class T>
inline void List<T>::deleteBack()
{
    if (isEmpty())
    {
        return;
    }

    Node<T>* dummy = m_tail;

    m_tail = m_tail->prev();
    m_tail->next() = NULL;
    delete dummy;
    dummy = NULL;
    --m_length;
}

template <class T>
inline bool List<T>::isEmpty() const
{
    return m_head == NULL;
}

template <class T>
inline int List<T>::length() const
{
    return m_length;
}

#endif
