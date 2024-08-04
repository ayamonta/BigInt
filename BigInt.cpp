#include "BigInt.h"

#include <string>

//**************************************************************
// Programmer: Ayana Tran
// Date: 05/21/2024
// Purpose: implementation file - BigInt class
// Input: cin for BigInt
// Output: cout for BigInt
//**************************************************************

// converts string to int and insert each digit into calling object's m_list
void BigInt::fromString(const string& stringToConvert)
{
    for (const auto& val : stringToConvert)
    {
        m_list.insertBack(val - '0');
    }
}

// inputs string to stream, (using fromString)
// converts string to int and inserts each digit into calling object's m_list
istream& operator>>(istream& in, BigInt& bigInt)
{
    // read obj from stream
    string newString;

    in >> newString;

    // wipes leading zeros from input string
    for (size_t i = 0; i < newString.length(); i++)
    {
        if (newString[i] != '0')
        {
            newString = newString.substr(i);
            break;
        }
    }

    bigInt.fromString(newString);

    return in;
}

// converts BigInt's int m_list to a string
string BigInt::toString() const
{
    string newString;

    for (const auto& val : m_list)
    {
        newString = newString + (char)((val->key()) + '0');
    }

    return newString;
}

// outputs bigInt's int m_list to stream,
// (using fromInt) converts BigInt's int m_list to a string,
// then returns string to stream
ostream& operator<<(ostream& out, const BigInt& bigInt)
{
    // write obj to stream
    if (bigInt.m_list.isEmpty())
    {
        out << "NULL";
    }
    else
    {
        out << bigInt.toString();
    }

    return out;
}

bool BigInt::operator!=(const BigInt& rhs) const
{
    return !((*this) == rhs);
}

bool BigInt::operator==(const BigInt& rhs) const
{
    auto& rt = rhs.m_list;

    if (m_list.length() != rt.length())
    {
        return false;
    }

    for (auto i = m_list.begin(), j = rt.begin();
         i != m_list.end() && j != rt.end(); i++, j++)
    {
        if ((*i)->key() != (*j)->key())
        {
            return false;
        }
    }

    return true;
}

BigInt& BigInt::operator=(const BigInt& rhs)
{
    if (this != &rhs)
    {
        m_list = rhs.m_list;
    }

    return *this;
}

BigInt::BigInt(const BigInt& other)
{
    m_list.copyList(other.m_list);
}

bool BigInt::operator>(const BigInt& rhs) const
{
    auto i = m_list.begin();
    auto j = rhs.m_list.begin();

    if (m_list.length() > rhs.m_list.length())
    {
        return true;
    }
    if (m_list.length() < rhs.m_list.length())
    {
        return false;
    }

    for (; i != m_list.end() && j != rhs.m_list.end(); i++, j++)
    {
        if ((*i)->key() > (*j)->key())
        {
            return true;
        }
        else if ((*i)->key() < (*j)->key())
        {
            return false;
        }
    }

    return false;
}

bool BigInt::operator>=(const BigInt& rhs) const
{
    auto i = m_list.begin();
    auto j = rhs.m_list.begin();

    if (m_list.length() > rhs.m_list.length())
    {
        return true;
    }
    if (m_list.length() < rhs.m_list.length())
    {
        return false;
    }

    for (; i != m_list.end() && j != rhs.m_list.end(); i++, j++)
    {
        if ((*i)->key() > (*j)->key())
        {
            return true;
        }
        else if ((*i)->key() < (*j)->key())
        {
            return false;
        }
    }

    return true;
}

bool BigInt::operator<(const BigInt& rhs) const
{
    auto i = m_list.begin();
    auto j = rhs.m_list.begin();

    if (m_list.length() < rhs.m_list.length())
    {
        return true;
    }
    if (m_list.length() > rhs.m_list.length())
    {
        return false;
    }

    for (; i != m_list.end() && j != rhs.m_list.end(); i++, j++)
    {
        if ((*i)->key() < (*j)->key())
        {
            return true;
        }
        else if ((*i)->key() > (*j)->key())
        {
            return false;
        }
    }

    return false;
}

bool BigInt::operator<=(const BigInt& rhs) const
{
    auto i = m_list.begin();
    auto j = rhs.m_list.begin();

    if (m_list.length() < rhs.m_list.length())
    {
        return true;
    }
    if (m_list.length() > rhs.m_list.length())
    {
        return false;
    }

    for (; i != m_list.end() && j != rhs.m_list.end(); i++, j++)
    {
        if ((*i)->key() < (*j)->key())
        {
            return true;
        }
        else if ((*i)->key() > (*j)->key())
        {
            return false;
        }
    }

    return true;
}

void BigInt::fromInt(int intToConvert)
{
    for (; intToConvert != 0; intToConvert /= 10)
    {
        m_list.insertFront(intToConvert % 10);
    }
}

BigInt BigInt::operator+(const BigInt& rhs) const
{
    auto i = m_list.rbegin();
    auto j = rhs.m_list.rbegin();

    BigInt finalResult;
    int carry = 0;

    for (; i != m_list.rend() && j != rhs.m_list.rend(); i++, j++)
    {
        int digit = (*i)->key() + (*j)->key() + carry;
        carry = digit / 10;
        digit %= 10;
        finalResult.m_list.insertFront(digit);
    }

    for (; i != m_list.rend(); i++)
    {
        int digit = (*i)->key() + carry;
        carry = digit / 10;
        digit %= 10;
        finalResult.m_list.insertFront(digit);
    }

    for (; j != rhs.m_list.rend(); j++)
    {
        int digit = (*j)->key() + carry;
        carry = digit / 10;
        digit %= 10;
        finalResult.m_list.insertFront(digit);
    }

    if (carry != 0)
    {
        finalResult.m_list.insertFront(carry);
    }

    return finalResult;
}

BigInt BigInt::operator-(const BigInt& rhs) const
{
    auto i = m_list.rbegin();
    auto j = rhs.m_list.rbegin();

    BigInt finalResult;
    int carry = 0;
    int digit;

    if (m_list.length() >= rhs.m_list.length())
    {
        for (; i != m_list.rend() && j != rhs.m_list.rend(); i++, j++)
        {
            digit = (*i)->key() - (*j)->key() + carry;

            carry = 0;

            if (digit < 0)
            {
                digit += 10;
                carry = -1;
            }

            finalResult.m_list.insertFront(digit);
        }

        // catch the rest of the first number
        for (; i != m_list.rend(); i++)
        {
            digit = (*i)->key() + carry;

            carry = 0;

            if (digit < 0)
            {
                digit += 10;
                carry = -1;
            }

            finalResult.m_list.insertFront(digit);
        }

        // shave off leading zeros
        while ((*finalResult.m_list.begin())->key() == 0 &&
               finalResult.m_list.length() != 1)
        {
            finalResult.m_list.deleteFront();
        }
    }

    return finalResult;
}

BigInt BigInt::operator*(const BigInt& rhs) const
{
    bool isThisBigger = *this > rhs;
    const auto& bigger = isThisBigger ? *this : rhs;
    const auto& smaller = isThisBigger ? rhs : *this;

    const auto& v = bigger.m_list;
    const auto& w = smaller.m_list;

    // multiplying
    List<BigInt> prodsBigInt;

    int placement = 0;
    int digit = 0;
    int carry = 0;

    for (auto j = w.rbegin(); j != w.rend(); j++, placement++)
    {
        BigInt newBigInt;

        for (int temp = 0; temp < placement; temp++)
        {
            newBigInt.m_list.insertFront(0);
        }

        for (auto i = v.rbegin(); i != v.rend(); i++)
        {
            digit = ((*j)->key() * (*i)->key()) + carry;
            carry = digit / 10;
            digit %= 10;
            newBigInt.m_list.insertFront(digit);
        }

        if (carry != 0)
        {
            // (*b)->key().m_list.insertFront(carry);
            newBigInt.m_list.insertFront(carry);
            carry = 0;
        }

        prodsBigInt.insertFront(newBigInt);
    }

    BigInt finalResult;
    // adding
    for (auto r = prodsBigInt.begin(); r != prodsBigInt.end(); r++)
    {
        finalResult = finalResult + (*r)->key();
    }

    return finalResult;
}

BigInt::BigInt(const int someInt)
{
    fromInt(someInt);
}

// --------------------------------------------------

// TODO: logic needs to be cleaned
// top is dividend, bottom is divisor. like a fraction
BigInt BigInt::operator/(const BigInt& bottom) const
{
    // return nothing if dividing by zero
    if ((*bottom.m_list.begin())->key() == 0 && bottom.m_list.length() == 1)
    {
        return BigInt(0);
    }
    // return nothing if divisor is greater than dividend
    if (*this < bottom)
    {
        return BigInt(0);
    }

    auto top = m_list.begin();

    BigInt tempTop;
    // Retrieving dividend by length of divisor and
    // inserting it into tempTop.
    // Decrement iterator by one to be in the correct spot
    // to pull down a number in division process
    while (tempTop.m_list.length() != bottom.m_list.length() - 1)
    {
        if (tempTop.m_list.length() >= 1)
        {
            top++;
        }

        tempTop.m_list.insertBack((*top)->key());
    }

    // catch dividend with length 1 and insert into tempTop
    if (bottom.m_list.length() == 1)
    {
        tempTop.m_list.insertBack((*top)->key());

        // solves error: first top num less than first bot num
        // if (tempTop < bottom)
        // {
        //     top++;
        //     tempTop.m_list.insertBack((*top)->key());
        // }
    }

    BigInt quotient;
    // division process by minusing tempTop by divisor
    // and taking times minused as quotient
    while (top != m_list.end())
    {
        int multiple = 0;

        while (tempTop >= bottom)
        {
            tempTop = tempTop - bottom;
            ++multiple;
        }

        quotient.m_list.insertBack(multiple);

        if ((*top)->next() != NULL)
        {
            // solves error: tempTop becomes 0 for first quotient digit
            // if (((*tempTop.m_list.begin())->key() != 0))
            // {
            tempTop.m_list.insertBack((*top)->next()->key());
            // }
        }

        top++;
    }

    // shave off leading zeros
    while ((*quotient.m_list.begin())->key() == 0 &&
           quotient.m_list.length() != 1)
    {
        quotient.m_list.deleteFront();
    }

    return quotient;
}

// ------------------------------------------------------

// same as operator /
BigInt BigInt::operator%(const BigInt& bottom) const
{
    // return nothing if divisor is greater than dividend
    if (*this < bottom)
    {
        return bottom;
    }
    // return nothing if dividing by zero
    if ((*bottom.m_list.begin())->key() == 0 && bottom.m_list.length() == 1)
    {
        return bottom;
    }

    auto top = m_list.begin();

    BigInt tempTop;
    // retrieve dividend by length of divisor
    while (tempTop.m_list.length() != bottom.m_list.length() - 1)
    {
        if (tempTop.m_list.length() >= 1)
        {
            top++;
        }

        tempTop.m_list.insertBack((*top)->key());
    }

    // catch dividend with length 1
    if (bottom.m_list.length() == 1)
    {
        tempTop.m_list.insertBack((*top)->key());

        // if (tempTop < bottom)
        // {
        //     top++;
        //     tempTop.m_list.insertBack((*top)->key());
        // }
    }

    BigInt remainder;
    // division minusing top by bottom
    // and taking times minused as quotient
    while (top != m_list.end())
    {
        int multiple = 0;

        while (tempTop >= bottom)
        {
            tempTop = tempTop - bottom;
            ++multiple;
        }

        if ((*top)->next() != NULL)
        {
            // if (((*tempTop.m_list.begin())->key() != 0))
            // {
            tempTop.m_list.insertBack((*top)->next()->key());
            // }
        }

        top++;
    }

    remainder = tempTop;

    // shave off leading zeros
    while ((*remainder.m_list.begin())->key() == 0 &&
           remainder.m_list.length() != 1)
    {
        remainder.m_list.deleteFront();
    }

    return remainder;
}

// operator for bigInt == int
// bool BigInt::operator==(int rhs)
// {
//     auto j = m_list.rbegin();

//     for (; j != m_list.rend() && rhs != 0; j++, rhs /= 10)
//     {
//         if ((*j)->key() != rhs % 10)
//         {
//             return false;
//         }
//     }

//     if (j != m_list.rend() || rhs != 0)
//     {
//         return false;
//     }

//     return true;
// }
