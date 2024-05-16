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

class CStringList {
private:
    struct Node {
        std::string data;
        std::shared_ptr<Node> next;
        std::shared_ptr<Node> prev;

        //move
        explicit Node(std::string str): data(std::move(str)), next(nullptr), prev(nullptr) {}
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    size_t size;

    void Clear() noexcept {
        while (head) {
            head = std::move(head->next);
        }
        tail = nullptr;
        size = 0;
    }

public:
    // Default constructor
    CStringList() : head(nullptr), tail(nullptr), size(0) {}

    // Copy constructor
    CStringList(const CStringList& other) : CStringList() {
        for (const auto& str : other) {
            AddToEnd(str);
        }
    }

    // Move constructor
    CStringList(CStringList&& other) noexcept : head(std::move(other.head)), tail(other.tail), size(other.size) {
        other.tail = nullptr;
        other.size = 0;
    }

    // Copy assignment operator
    CStringList& operator=(const CStringList& other) {
        if (this != &other) {
            CStringList temp(other);
            std::swap(*this, temp);
        }
        return *this;
    }

    // Move assignment operator
    CStringList& operator=(CStringList&& other) noexcept {
        if (this != &other) {
            Clear();
            head = std::move(other.head);
            tail = other.tail;
            size = other.size;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Destructor
    ~CStringList() noexcept {
        Clear();
    }

    // Add a string to the beginning of the list
    void AddToBeginning(const std::string& str) {
        auto newNode = std::make_shared<Node>(str);
        newNode->next = std::move(head);
        if (newNode->next) {
            newNode->next->prev = newNode;
        }
        head = std::move(newNode);
        if (!tail) {
            tail = head;
        }
        ++size;
    }

    // Add a string to the end of the list
    void AddToEnd(const std::string& str) {
        auto newNode = std::make_shared<Node>(str);
        newNode->prev = tail;
        if (tail) {
            tail->next = std::move(newNode);
            tail = tail->next;
        } else {
            head = std::move(newNode);
            tail = head;
        }
        ++size;
    }

    // Get the number of elements
    [[nodiscard]] size_t GetSize() const noexcept {
        return size;
    }

    // Check if the list is empty
    [[nodiscard]] bool IsEmpty() const noexcept {
        return size == 0;
    }

    // Remove all elements from the list
    void ClearList() noexcept {
        Clear();
    }

    // Iterator class
    class Iterator {

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::string;
        using difference_type = std::ptrdiff_t;
        using pointer = std::string*;
        using reference = std::string&;

        explicit Iterator(Node* node) : node(node) {}

        reference operator*() const {
            return node->data;
        }

        pointer operator->() const {
            return &node->data;
        }

        Iterator operator++() {
            node = node->next.get();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator operator--() {
            node = node->prev.get();
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return node == other.node;
        }

        bool operator!=(const Iterator& other) const {
            return node != other.node;
        }

        Node* node;
    };
 // Iterator class
    class ReverseIterator {

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::string;
        using difference_type = std::ptrdiff_t;
        using pointer = std::string*;
        using reference = std::string&;

        explicit ReverseIterator(Node* node) : node(node) {}

        reference operator*() const {
            return node->data;
        }

        pointer operator->() const {
            return &node->data;
        }

        ReverseIterator operator--() {
            node = node->next.get();
            return *this;
        }

        ReverseIterator operator--(int) {
            ReverseIterator temp = *this;
            ++(*this);
            return temp;
        }

        ReverseIterator operator++() {
            node = node->prev.get();
            return *this;
        }

        ReverseIterator operator++(int) {
            ReverseIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ReverseIterator& other) const {
            return node == other.node;
        }

        bool operator!=(const ReverseIterator& other) const {
            return node != other.node;
        }

        Node* node;
    };

    // Const iterator class
    class ConstIterator {
    private:
        const Node* node;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const std::string;
        using difference_type = std::ptrdiff_t;
        using pointer = const std::string*;
        using reference = const std::string&;

        explicit ConstIterator(const Node* node) : node(node) {}

        reference operator*() const {
            return node->data;
        }

        pointer operator->() const {
            return &node->data;
        }

        ConstIterator& operator++() {
            node = node->next.get();
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }

        ConstIterator& operator--() {
            node = node->prev.get();
            return *this;
        }

        ConstIterator operator--(int) {
            ConstIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ConstIterator& other) const {
            return node == other.node;
        }

        bool operator!=(const ConstIterator& other) const {
            return node != other.node;
        }
    };

    // Get iterator to the beginning
    Iterator begin() {
        return Iterator(head.get());
    }

    // Get iterator to the end
    Iterator end() {
        return Iterator(nullptr);
    }

    // Get const iterator to the beginning
    [[nodiscard]] ConstIterator begin() const {
        return ConstIterator(head.get());
    }

    // Get const iterator to the end
    [[nodiscard]] ConstIterator end() const {
        return ConstIterator(nullptr);
    }

    // Get reverse iterator to the beginning
    ReverseIterator rbegin() {
        return ReverseIterator(tail.get());
    }

    // Get reverse iterator to the end            //todo вынести реализацию в cpp
    ReverseIterator rend() {
        return ReverseIterator(nullptr);
    }

    // Get const reverse iterator to the beginning
    [[nodiscard]] std::reverse_iterator<ConstIterator> rbegin() const {
        return std::reverse_iterator<ConstIterator>(end());
    }

    // Get const reverse iterator to the end
    [[nodiscard]] std::reverse_iterator<ConstIterator> rend() const {
        return std::reverse_iterator<ConstIterator>(begin());
    }

    // Insert an element at a position specified by an iterator
    Iterator Insert(Iterator pos, const std::string& str) {
        if (pos == begin()) {
            AddToBeginning(str);
            return begin();
        } else if (pos == end()) {
            AddToEnd(str);
            return Iterator(tail.get());
        } else {
            auto newNode = std::make_shared<Node>(str);
            Node* current = pos.node;
            newNode->prev = current->prev;
            newNode->next = std::move(current->prev->next);
            current->prev->next = std::move(newNode);
            current->prev = current->prev->next;
            ++size;
            return Iterator(current->prev.get());
        }
    }

    // Remove an element at a position specified by an iterator
    Iterator Erase(Iterator pos) {
        if (pos == end()) {
            return end();
        }
        Node* current = pos.node;
        if (current->prev) {
            current->prev->next = std::move(current->next);
            if (current->prev->next) {
                current->prev->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
        } else {
            head = std::move(current->next);
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        }
        --size;
        return Iterator(current->next.get());
    }
};


#endif //OOP_6_CSTRINGLIST_H
