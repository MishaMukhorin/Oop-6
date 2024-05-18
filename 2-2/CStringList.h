//
// Created by Misha on 16.05.2024.
//

#ifndef OOP_6_CSTRINGLIST_H
#define OOP_6_CSTRINGLIST_H

#include <iostream>
#include <memory>
#include <utility>
#include <iostream>
#include <memory>
#include <string>
#include <iterator>

struct Node {
    std::string data;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;

    //move
    explicit Node(std::string str): data(std::move(str)), next(nullptr), prev(nullptr) {}
};

class CStringList {
public:

    CStringList() : head(nullptr), tail(nullptr), size(0) {}
    CStringList(const CStringList& other);
    CStringList(CStringList&& other) noexcept;

    CStringList& operator=(const CStringList& other);
    CStringList& operator=(CStringList&& other) noexcept;

    ~CStringList() noexcept;

    void AddToBeginning(const std::string& str);
    void AddToEnd(const std::string& str);
    [[nodiscard]] size_t GetSize() const noexcept;
    [[nodiscard]] bool IsEmpty() const noexcept;
    void Clear() noexcept;

    class Iterator;
    class ReverseIterator;
    class ConstIterator;
    class ConstReverceIterator;

    Iterator begin();
    Iterator end();
    [[nodiscard]] ConstIterator begin() const;
    [[nodiscard]] ConstIterator end() const;
    [[nodiscard]] ConstIterator cbegin() const;
    [[nodiscard]] ConstIterator cend() const;
    ReverseIterator rbegin();
    ReverseIterator rend();
    [[nodiscard]] ConstReverceIterator rbegin() const;
    [[nodiscard]] ConstReverceIterator rend() const;
    [[nodiscard]] ConstReverceIterator crbegin() const;
    [[nodiscard]] ConstReverceIterator crend() const;
    Iterator Insert(Iterator pos, const std::string& str);
    Iterator Erase(Iterator pos);

private:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    size_t size;

};


class CStringList::Iterator {
public:
    explicit Iterator(Node* node) : m_node(node) {}

    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::string;
    using difference_type = std::ptrdiff_t;
    using pointer = std::string*;
    using reference = std::string&;

    reference operator*() const;
    pointer operator->() const;

    Iterator operator++();
    Iterator operator++(int);
    Iterator operator--();
    Iterator operator--(int);

    Iterator& operator+=(difference_type n);
    Iterator operator+(difference_type n) const;
    Iterator& operator-=(difference_type n);

    Iterator operator-(difference_type n) const;
    difference_type operator-(const Iterator& other) const;

    reference operator[](difference_type n) const;

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

    bool operator<(const Iterator& other) const ;
    bool operator<=(const Iterator& other) const;
    bool operator>(const Iterator& other) const;
    bool operator>=(const Iterator& other) const;



    Node* m_node;
};

class CStringList::ReverseIterator {
public:
    explicit ReverseIterator(Node* node) : m_node(node) {}

    std::string& operator*() const;
    std::string* operator->() const;

    ReverseIterator operator--();
    ReverseIterator operator--(int);
    ReverseIterator operator++();
    ReverseIterator operator++(int);

    bool operator==(const ReverseIterator& other) const;
    bool operator!=(const ReverseIterator& other) const;

    Node* m_node;
};

class CStringList::ConstIterator {
public:
    explicit ConstIterator(const Node* node) : m_node(node) {}

    const std::string& operator*() const;
    const std::string* operator->() const;

    ConstIterator& operator++();
    ConstIterator operator++(int);
    ConstIterator& operator--();
    ConstIterator operator--(int);

    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;

private:
    const Node* m_node;
};

class CStringList::ConstReverceIterator {
public:
    explicit ConstReverceIterator(const Node* node) : m_node(node) {}

    const std::string& operator*() const;
    const std::string* operator->() const;

    ConstReverceIterator& operator++();
    ConstReverceIterator operator++(int);
    ConstReverceIterator& operator--();
    ConstReverceIterator operator--(int);

    bool operator==(const ConstReverceIterator& other) const;
    bool operator!=(const ConstReverceIterator& other) const;

private:
    const Node* m_node;
};

#endif //OOP_6_CSTRINGLIST_H
