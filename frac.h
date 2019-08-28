#ifndef FRAC_H
#define FRAC_H
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;

class Frac;
ostream &operator << (ostream &, const Frac &);
istream &operator >> (istream &, Frac &);

class Frac {
	int num;
	int den;
    void simplify();
    
public:
	// Constructors
    Frac() {num = 0; den = 1;};
    Frac(int n) {num = n; den = 1; simplify();};
    Frac(int n, int d) {num=n; den=d; simplify();};
    Frac(float f) {float temp = roundf(f * 100)/100; num = temp*100; den=100; simplify();};
	
    Frac(const Frac &obj) {*this = obj;};
	void operator=(const Frac &rhs) {
		num = rhs.num;  den = rhs.den;
    };   // Frac a = b;
	
	// string constructor is challenging, worth 2 pts, try your best! 
	Frac(string);
	
	//Setters and Getters
    void setNum (int n) {num = n; simplify();};
    void setDen (int d) {den = d; simplify();};
    int getNum() {return num;};
    int getDen() {return den;};
        
    // math + - * must be minimum term, i.e. no 2/8
    Frac operator + (const Frac &);
    Frac operator - (const Frac &);
    Frac operator * (const Frac &);
    Frac operator / (const Frac &);
        
    // increment ++ decrement --
    Frac operator++();
    Frac operator++(int);
    Frac operator--();
    Frac operator--(int);
        
    // comparators
    bool operator == (const Frac &);
    bool operator != (const Frac &);
    bool operator < (const Frac &);
    bool operator > (const Frac &);
    bool operator <= (const Frac &);
    bool operator >= (const Frac &);
    
    //Object type converter declaration
    operator int() {int temp = num/den; return temp;};
    operator float() {float temp = (num+0.00)/den; return temp;}
	
	// overload ostream insertion operator<<
    friend ostream &operator << (ostream &, const Frac &);
    friend istream &operator >> (istream &, Frac &);
};
    
    void Frac::simplify() {
        if (den == 0) {
            cout << "Error, invalid denominator..." << endl;
        }
        else {
            vector <int> gcd1;
            vector <int> gcd2;
            
            int temp1 = 1;
            int temp2 = 1;
            
            while (temp1 <= num) {
                if (not(num % temp1))
                    gcd1.push_back(temp1);
                temp1++;    }
            
            while (temp2 <= den) {
                if (not(den % temp2))
                    gcd2.push_back(temp2);
                temp2++;}
            
            int gcd = 1;
            long size;
            
            if (gcd1.size() > gcd2.size()) {
                size = gcd1.size();
                gcd2.resize(size);}
            else if (gcd1.size() < gcd2.size()) {
                size = gcd2.size();
                gcd1.resize(size);}
            else {size = gcd1.size();}
            
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (gcd1.at(i) == gcd2.at(j)) {
                        int gcd_temp = gcd1.at(i);
                        if (gcd_temp > gcd) {gcd = gcd_temp;}}}
            }
            
            num = num/gcd;
            den = den/gcd;
        }
    }

    Frac::Frac(string s) {
        istringstream iss(s);
    
        char delim = 0;
    
        if (
            (iss >> num)
            && (iss >> delim)
            && (delim == '/')
            && (iss >> den))
        {
            assert(den != 0);
            simplify();
        } else
        {
            throw std::runtime_error("invalid conversion to Fraction");
        }
    }
    
    // math operators
    Frac Frac::operator + (const Frac &rhs) {
        Frac temp;
        temp.num = num*rhs.den + rhs.num*den;
        temp.den = den*rhs.den;
        temp.simplify();
        return temp;
    }
    
    Frac Frac::operator - (const Frac &rhs) {
        Frac temp;
        temp.num = num*rhs.den - rhs.num*den;
        temp.den = den*rhs.den;
        temp.simplify();
        return temp;
    }
    
    Frac Frac::operator * (const Frac &rhs) {
        Frac temp;
        temp.num = num*rhs.num;
        temp.den = den*rhs.den;
        temp.simplify();
        return temp;
    }
    
    Frac Frac::operator / (const Frac &rhs) {
        Frac temp;
        temp.num = num*rhs.den;
        temp.den = den*rhs.num;
        temp.simplify();
        return temp;
    }
    
    // prefix increment operator ++ --
    Frac Frac::operator ++() {
        num += den;
        simplify();
        // lowterms(*this);
        return *this; }
    
    Frac Frac::operator--() {
        num -= den;
        simplify();
        // lowterms(*this);
        return *this; }
    
    // postfix increment operator ++ --
    Frac Frac::operator ++(int) {
        Frac temp(num, den);
        num+= den;
        simplify();
        return temp; }
    
    Frac Frac::operator--(int) {
        Frac temp(num, den);
        num -= den;
        simplify();
        return temp; }
    
    bool Frac::operator == (const Frac &f2) {
        if (num == f2.num && den == f2.den) {
            return true;
        }
        else {return false;}
    }
    
    bool Frac::operator != (const Frac &f2) {
        if (num != f2.num && den != f2.den) {
            return true;
        }
        if (num != f2.num && den == f2.den) {
            return true;
        }
        if (num == f2.num && den != f2.den) {
            return true;
        }
        else {return false;}
    }
    
    bool Frac::operator > (const Frac &f2) {
        if (num > f2.num && den == f2.den) {
            return true;
        }
        if (num == f2.num && den < f2.den) {
            return true;
        }
        if (num > f2.num && den > f2.den) {
            return true;
        }
        else {return false;}
    }
    
    bool Frac::operator < (const Frac &f2) {
        if (num < f2.num && den == f2.den) {
            return true;
        }
        if (num == f2.num && den > f2.den) {
            return true;
        }
        if (num < f2.num && den < f2.den) {
            return true;
        }
        else {return false;}
    }
    
    bool Frac::operator >= (const Frac &f2) {
        if (num > f2.num && den == f2.den) {
            return true;
        }
        if (num == f2.num && den < f2.den) {
            return true;
        }
        if (num > f2.num && den > f2.den) {
            return true;
        }
        if (num == f2.num && den == f2.den) {
            return true;
        }
        else {return false;}
    }
    
    bool Frac::operator <= (const Frac &f2) {
        if (num < f2.num && den == f2.den) {
            return true;
        }
        if (num == f2.num && den > f2.den) {
            return true;
        }
        if (num < f2.num && den < f2.den) {
            return true;
        }
        if (num == f2.num && den == f2.den) {
            return true;
        }
        else {return false;}
    }
    
    ostream &operator << (ostream &strm, const Frac &rhs) {
        strm << rhs.num << "/" << rhs.den;
        return strm;
    }

    istream &operator >> (istream &strm, Frac &rhs) {
        char c;
        strm >> rhs.num;
        strm >> c;
        strm >> rhs.den;
        rhs.simplify();
        return strm;
    }
#endif
