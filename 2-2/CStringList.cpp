//
// Created by Misha on 16.05.2024.
//

#include "CStringList.h"


CStringList::CStringList(const CStringList& other) : CStringList()
{
    for (const auto& str : other)
    {
        AddToEnd(str);
    }
}
CStringList::CStringList(CStringList&& other) noexcept : head(std::move(other.head)), tail(std::move(other.tail)), size(other.size)
{
    other.tail = nullptr;
    other.size = 0;
}

CStringList& CStringList::operator=(const CStringList& other)
{
    if (this != &other)
    {
        CStringList temp(other);
        std::swap(*this, temp);
    }
    return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
    if (this != &other)
    {
        Clear();
        head = std::move(other.head);
        tail = other.tail;
        size = other.size;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}

CStringList::~CStringList() noexcept
{
    Clear();
}

void CStringList::AddToBeginning(const std::string& str)
{
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

void CStringList::AddToEnd(const std::string& str)
{
    auto newNode = std::make_shared<Node>(str);
    newNode->prev = tail;
    if (tail)
    {
        tail->next = std::move(newNode);
        tail = tail->next;
    } else
    {
        head = std::move(newNode);
        tail = head;
    }
    ++size;
}

[[nodiscard]] size_t CStringList::GetSize() const noexcept
{
    return size;
}

[[nodiscard]] bool CStringList::IsEmpty() const noexcept
{
    return size == 0;
}

void CStringList::Clear() noexcept
{
    while (head)
    {
        head = std::move(head->next);
    }
    tail = nullptr;
    size = 0;
}

CStringList::Iterator CStringList::begin()
{
    return Iterator(head.get());
}

CStringList::Iterator CStringList::end()
{
    return Iterator(nullptr);
}

[[nodiscard]] CStringList::ConstIterator CStringList::begin() const
{
    return ConstIterator(head.get());
}

[[nodiscard]] CStringList::ConstIterator CStringList::end() const
{
    return ConstIterator(nullptr);
}

[[nodiscard]] CStringList::ConstIterator CStringList::cbegin() const
{
    return ConstIterator(head.get());
}

[[nodiscard]] CStringList::ConstIterator CStringList::cend() const
{
    return ConstIterator(nullptr);
}

CStringList::ReverseIterator CStringList::rbegin()
{
    return ReverseIterator(tail.get());
}

CStringList::ReverseIterator CStringList::rend()
{
    return ReverseIterator(nullptr);
}

[[nodiscard]] CStringList::ConstReverceIterator CStringList::rbegin() const
{
    return ConstReverceIterator(tail.get());
}

[[nodiscard]] CStringList::ConstReverceIterator CStringList::rend() const
{
    return ConstReverceIterator(nullptr);
}

[[nodiscard]] CStringList::ConstReverceIterator CStringList::crbegin() const
{
    return ConstReverceIterator(tail.get());
}

[[nodiscard]] CStringList::ConstReverceIterator CStringList::crend() const
{
    return ConstReverceIterator(nullptr);
}

CStringList::Iterator CStringList::Insert(Iterator pos, const std::string& str)
{
    if (pos == begin())
    {
        AddToBeginning(str);
        return begin();
    }
    else if (pos == end())
    {
        AddToEnd(str);
        return Iterator(tail.get());
    }
    else
    {
        auto newNode = std::make_shared<Node>(str);
        Node* current = pos.m_node;
        newNode->prev = current->prev;
        newNode->next = std::move(current->prev->next);
        current->prev->next = std::move(newNode);
        current->prev = current->prev->next;
        ++size;
        return Iterator(current->prev.get());
    }
}

CStringList::Iterator CStringList::Erase(Iterator pos)
{
    if (pos == end()) {
        return end();
    }
    Node* current = pos.m_node;
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

//

CStringList::Iterator& CStringList::Iterator::operator+=(std::ptrdiff_t n)
{
    if (n > 0) {
        for (std::ptrdiff_t i = 0; i < n; ++i) {
            ++(*this);
        }
    } else {
        for (std::ptrdiff_t i = 0; i < -n; ++i) {
            --(*this);
        }
    }
    return *this;
}

CStringList::Iterator CStringList::Iterator::operator+(std::ptrdiff_t n) const
{
    Iterator temp = *this;
    return temp += n;
}

CStringList::Iterator& CStringList::Iterator::operator-=(std::ptrdiff_t n)
{
    for (std::ptrdiff_t i = 0; i < n; ++i) {
        --(*this);
    }
    return *this;
}

CStringList::Iterator CStringList::Iterator::operator-(std::ptrdiff_t n) const
{
    Iterator temp = *this;
    return temp -= n;
}

std::ptrdiff_t CStringList::Iterator::operator-(const Iterator& other) const {
    std::ptrdiff_t dist = 0;
    Iterator temp = *this;
    if (temp > other) {
        while (temp != other) {
            --temp;
            ++dist;
        }
    } else {
        while (temp != other) {
            ++temp;
            --dist;
        }
    }
    return dist;
}

std::string& CStringList::Iterator::operator[](std::ptrdiff_t n) const
{
    Iterator temp = *this;
    return *(temp += n);
}

std::string& CStringList::Iterator::operator*() const
{
    return m_node->data;
}

std::string* CStringList::Iterator::operator->() const
{
    return &m_node->data;
}

CStringList::Iterator CStringList::Iterator::operator++()
{
    m_node = m_node->next.get();
    return *this;
}

CStringList::Iterator CStringList::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

CStringList::Iterator CStringList::Iterator::operator--()
{
    m_node = m_node->prev.get();
    return *this;
}

CStringList::Iterator CStringList::Iterator::operator--(int)
{
    Iterator temp = *this;
    --(*this);
    return temp;
}

bool CStringList::Iterator::operator==(const Iterator& other) const
{
    return m_node == other.m_node;
}

bool CStringList::Iterator::operator!=(const Iterator& other) const
{
    return m_node != other.m_node;
}

bool CStringList::Iterator::operator<(const Iterator& other) const
{
    Node* temp = m_node;
    while (temp != nullptr) {
        if (temp == other.m_node) return true;
        temp = temp->next.get();
    }
    return false;
}

bool CStringList::Iterator::operator<=(const Iterator& other) const {
    return (*this < other) || (*this == other);
}

bool CStringList::Iterator::operator>(const Iterator& other) const {
    return !(*this <= other);
}

bool CStringList::Iterator::operator>=(const Iterator& other) const {
    return !(*this < other);
}




std::string& CStringList::ReverseIterator::operator*() const
{
    return m_node->data;
}

std::string* CStringList::ReverseIterator::operator->() const
{
    return &m_node->data;
}

CStringList::ReverseIterator CStringList::ReverseIterator::operator--()
{
    m_node = m_node->next.get();
    return *this;
}

CStringList::ReverseIterator CStringList::ReverseIterator::operator--(int)
{
    ReverseIterator temp = *this;
    ++(*this);
    return temp;
}

CStringList::ReverseIterator CStringList::ReverseIterator::operator++()
{
    m_node = m_node->prev.get();
    return *this;
}

CStringList::ReverseIterator CStringList::ReverseIterator::operator++(int)
{
    ReverseIterator temp = *this;
    --(*this);
    return temp;
}

bool CStringList::ReverseIterator::operator==(const ReverseIterator& other) const
{
    return m_node == other.m_node;
}

bool CStringList::ReverseIterator::operator!=(const ReverseIterator& other) const
{
    return m_node != other.m_node;
}

const std::string& CStringList::ConstIterator::operator*() const
{
    return m_node->data;
}

const std::string* CStringList::ConstIterator::operator->() const
{
    return &m_node->data;
}

CStringList::ConstIterator& CStringList::ConstIterator::operator++()
{
    m_node = m_node->next.get();
    return *this;
}

CStringList::ConstIterator CStringList::ConstIterator::operator++(int)
{
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

CStringList::ConstIterator& CStringList::ConstIterator::operator--()
{
    m_node = m_node->prev.get();
    return *this;
}

CStringList::ConstIterator CStringList::ConstIterator::operator--(int)
{
    ConstIterator temp = *this;
    --(*this);
    return temp;
}

bool CStringList::ConstIterator::operator==(const ConstIterator& other) const
{
    return m_node == other.m_node;
}

bool CStringList::ConstIterator::operator!=(const ConstIterator& other) const
{
    return m_node != other.m_node;
}


const std::string& CStringList::ConstReverceIterator::operator*() const
{
    return m_node->data;
}

const std::string* CStringList::ConstReverceIterator::operator->() const
{
    return &m_node->data;
}

CStringList::ConstReverceIterator& CStringList::ConstReverceIterator::operator++()
{
    m_node = m_node->prev.get();
    return *this;
}

CStringList::ConstReverceIterator CStringList::ConstReverceIterator::operator++(int)
{
    ConstReverceIterator temp = *this;
    ++(*this);
    return temp;
}

CStringList::ConstReverceIterator& CStringList::ConstReverceIterator::operator--()
{
    m_node = m_node->next.get();
    return *this;
}

CStringList::ConstReverceIterator CStringList::ConstReverceIterator::operator--(int)
{
    ConstReverceIterator temp = *this;
    --(*this);
    return temp;
}

bool CStringList::ConstReverceIterator::operator==(const ConstReverceIterator& other) const
{
    return m_node == other.m_node;
}

bool CStringList::ConstReverceIterator::operator!=(const ConstReverceIterator& other) const
{
    return m_node != other.m_node;
}