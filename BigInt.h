#include <memory>

#include "List.h"
#ifndef BIGINT_H
#define BIGINT_H

//**************************************************************
// Programmer: Ayana Tran
// Date: 05/21/2024
// Purpose: header file - BigInt class
// Input: none
// Output: none
//**************************************************************

/// @brief uses a linked list to contain integers larger than the maximum size
/// of 64 bits for integers
class BigInt
{
   private:
    List<int> m_list;

   public:
    /// @brief converts from string to calling object (BigInt)
    void fromString(const string& stringToConvert);
    friend istream& operator>>(istream& in, BigInt& bigInt);

    /// @brief converts BigInt to string
    string toString() const;
    friend ostream& operator<<(ostream& out, const BigInt& bigInt);

    bool operator!=(const BigInt& rhs) const;
    bool operator==(const BigInt& rhs) const;

    BigInt& operator=(const BigInt& rhs);
    // copy constructor created for rule of three
    BigInt(const BigInt& other);
    // default constructor created for rule of three
    BigInt(){};
    /// @brief constructor that inserts an integer into BigInt
    BigInt(const int someInt);

    bool operator>(const BigInt& rhs) const;
    bool operator>=(const BigInt& rhs) const;
    bool operator<(const BigInt& rhs) const;
    bool operator<=(const BigInt& rhs) const;

    /// @brief inserts from an integer into calling object (BigInt)
    void fromInt(int intToConvert);
    BigInt operator+(const BigInt& rhs) const;
    BigInt operator-(const BigInt& rhs) const;
    BigInt operator*(const BigInt& rhs) const;

    BigInt operator/(const BigInt& bottom) const;
    BigInt operator%(const BigInt& bottom) const;
};

#endif
