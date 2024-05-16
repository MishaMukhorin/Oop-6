//
// Created by mrLogic on 5/15/2024.
//

#ifndef OOP_6_CURLPARSINGERROR_H
#define OOP_6_CURLPARSINGERROR_H

#include <stdexcept>

class CUrlParsingError : public std::invalid_argument
{
public:
    CUrlParsingError() : std::invalid_argument("") {};

};

class CUrlDocumentParsingError : public std::invalid_argument
{
public:
    CUrlDocumentParsingError() : std::invalid_argument("") {};

};

class CUrlDomainParsingError : public std::invalid_argument
{
public:
    CUrlDomainParsingError() : std::invalid_argument("") {};

};

class CUrlPortParsingError : public std::invalid_argument
{
public:
    CUrlPortParsingError() : std::invalid_argument("") {};

};

class CUrlProtocolParsingError : public std::invalid_argument
{
public:
    CUrlProtocolParsingError() : std::invalid_argument("") {};

};

class NoNumberAfterMinusError : public std::invalid_argument {
public:
    explicit NoNumberAfterMinusError(int position) : std::invalid_argument(""), _position(position) {}

    [[nodiscard]] int getPosition() const {
        return _position;
    }

private:
    int _position;
};


#endif //OOP_6_CURLPARSINGERROR_H
