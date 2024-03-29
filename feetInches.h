#ifndef FEETINCHES_H
#define FEETINCHES_H
#include <iostream>
using namespace std;

// (Friend step 1) Forward Declaration 
class FeetInches;	

// (Friend step 2) Forward Declaration of Friend Function
ostream &operator << (ostream &, const FeetInches &);
istream &operator >> (istream &, FeetInches &);

class FeetInches {
	int feet;		// To hold a number of feet
	int inches;		 // To hold a number of inches
	void simplify();// header only Definition below
public:
	// argument constructor
	FeetInches(int f = 0, int i = 0) 
		{ feet = f; inches = i; simplify(); }
	FeetInches(string s);
	// copy constructor - must 1. pass ref var.
	FeetInches (const FeetInches &fi) 
		{ feet = fi.feet; inches = fi.inches; simplify(); }
	// assignment operator
	FeetInches operator= (const FeetInches &right)
		{ feet = right.feet; inches = right.inches; simplify(); }
	// Mutator
	void setFeet(int f) { feet = f; }
	void setInches(int i) { inches = i; simplify(); }
	// Accessor 
	int getFeet() const { return feet; }
	int getInches() const { return inches; }

	// Overloaded operator functions      
	FeetInches operator + (const FeetInches &);	// Overloaded + 
	FeetInches operator - (const FeetInches &);	// Overloaded -
	FeetInches operator ++ ();					// Prefix ++      
	FeetInches operator ++ (int);				// Postfix ++  
	bool operator > (const FeetInches &);		// Overloaded >  
	bool operator < (const FeetInches &);		// Overloaded <
	bool operator == (const FeetInches &);		// Overloaded ==

	// Object Type Converter declaration
	operator int() { return feet; } 
	operator double() {
		double temp = feet; temp += (inches / 12.0); return temp; } 
		
    // (Friends Step 3) Friend Function Declaration
	friend ostream &operator << (ostream &, const FeetInches &);
	friend istream &operator >> (istream &, FeetInches &);
};
	
void FeetInches::simplify(){
	if (inches >= 12) {
		feet += (inches / 12);
		inches = inches % 12; }
	else if (inches < 0) {
		feet -= ((abs(inches) / 12) + 1);	// quotion for feets
		inches = 12 - (abs(inches) % 12); }	// remainder for inches
	if( feet < 0 && inches >0 ) { feet += 1; inches -= 12; }
}

//*********************************************************
// Overloaded binary + and - operator.	int	result = a + b;
//*********************************************************

FeetInches FeetInches::operator + (const FeetInches &right) { 
	FeetInches temp;
	temp.inches = inches + right.inches; 
	temp.feet = feet + right.feet;
	temp.simplify();
	return temp; 
}

FeetInches FeetInches::operator - (const FeetInches &right) {
	FeetInches temp;
	temp.inches = inches - right.inches;
	temp.feet = feet - right.feet;
	temp.simplify();  
	return temp;
} 

//**********************************************************
// Overloaded unary pre and postfix ++ operator.		
//**********************************************************
FeetInches FeetInches::operator++() { // prefix increment
	++inches;
	simplify();
	return *this;
} 

FeetInches FeetInches::operator++(int) { 
	FeetInches temp(feet, inches);   // keep my old value
	inches+=1;                       // increase myself
	simplify();
	return temp;                     // return my old value
}          

//************************************************************
// Overloaded comparator operator.  
//************************************************************

bool FeetInches::operator > (const FeetInches &right) {
	if (feet > right.feet)  return true;
	if (feet == right.feet && inches > right.inches)
		return true;
	return false;
}

bool FeetInches::operator < (const FeetInches &right) {
	if (feet < right.feet) return true;
	if (feet == right.feet && inches < right.inches)
		return true;
	return false;
}

bool FeetInches::operator == (const FeetInches &right) {
	if (feet == right.feet && inches == right.inches)
		return true;
	return false;
}

//************************************************************
// (Friend step 4) Friend Function Definition
// Overloaded stream operator << and >>
//************************************************************
ostream &operator << (ostream &strm, const FeetInches &rhs) {
    strm << rhs.feet << "\' " << rhs.inches << "\" "; 
    return strm;
}

istream &operator >> (istream &strm, FeetInches &rhs) {
    char c; // 3'5"
    strm >> rhs.feet;
    strm >> c;
    strm >> rhs.inches;
    rhs.simplify();
    return strm;
}
#endif
