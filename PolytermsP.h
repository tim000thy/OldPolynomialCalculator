#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;
// Here the user can specify a different type;
// Your implementation should work for double, float, and int
typedef double coefType;
typedef int exponentType;
struct polyTerm;
class Poly {
	
public:
	// overloaded operator << to print poly to file
	//friend ostream& operator<<(ostream& out,Poly& p);

	// Constructor: create an empty polynomial linked list.
	Poly();
	// Copy constructor: create a deep copy
	Poly(const Poly& original);

	// Destructor: deallocate memory that was allocated dynamically
	~Poly();

	// Get corresponding coefficient for an exponent
	coefType getCoef( exponentType exponent ); 

	// Set the coefficient for an exponent
	void setCoef( exponentType exponent, coefType coef );
	// Find the term for an exponent, returns a pointer to the term.
	// If there is no term with that exponent, make a new term and set 
	//the coefficient to zero.
	void findTerm( exponentType exponent );
	// Insert a new term. This is placed directly after the current // item.
	void newTerm( exponentType exponent, coefType coef );

	// Find the highest exponent in the polynomial
	exponentType findDegree();


	//multiplies two polynomials
	Poly operator *(const Poly& p);

	//add two polynomials
	Poly operator +(const Poly& p);

	//subtracts two polynomials
	//Poly operator -(const Poly& p);

	//overloaded assignment operator
	Poly& operator = (const Poly& orig);



private:
	// List node, called polyTerm for Polynomial Term
	struct polyTerm
	{
		coefType coef;
		exponentType exponent;
		polyTerm *next;
	};
	// Points to the first term
	polyTerm *head;
	// Points to the current term – the tail end term of the linked list
	polyTerm *current;

	int numTerms;
};