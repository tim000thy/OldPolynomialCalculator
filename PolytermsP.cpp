#include "PolytermsP.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
//default constructor
Poly:: Poly()
{
	head = NULL;
	current = NULL;
	numTerms = 0;
}

Poly::Poly(const Poly& original)
{
	if (original.head == NULL)
		head = NULL; //original list empty
	else
	{//copy first node

		head = new polyTerm;
		head-> coef = original.head -> coef;
		head-> exponent = original.head -> exponent;
		numTerms++;

		//copy rest of list
		current = head; //new list pointer
		//current points to last node in new list
		//origPtr points to node in original list
		for (polyTerm *origPtr = original.head->next;
			origPtr != NULL;
			origPtr = origPtr->next)
		{//loop through original list and copy all nodes in new list
			//creates new list node for the "next" pointer of the current node to point to
			current->next = new polyTerm;

			//makes current point to the next node
			current = current -> next;
			//copies the values
			current-> coef = origPtr -> coef;
			current-> exponent = origPtr -> exponent;
			numTerms++;
		}//end for loop

		current ->next = NULL;
	}//end if

}//end of copy constructor

//destructor
Poly::~Poly()
{
	//deletes head if there is only one item
	if (head == NULL)
	{
		return;
	}
	else if( head -> next == NULL)
	{
		current = head;
		current -> next = NULL;
		delete current;
		current = NULL;
		head = NULL;
		numTerms = NULL;

	}
	else
	{
		while (head -> next !=NULL)//destroy the rest of the linked list noeds
		{
			polyTerm *temp = head;
			current = head->next;
			head = head -> next;
			delete temp;
			numTerms--;
		}
		delete head;
		head = NULL;// deallocate memory
		current = NULL;
		numTerms = NULL;
	}

}
//gets corresponding coefficoent


coefType Poly::getCoef( exponentType exponent )
{
	findTerm(exponent);// use findterm function to find coressponding node
	return current -> coef;// return coefficient
}

void Poly:: newTerm( exponentType exponent, coefType coef )
{

	if ( head == NULL )//if list is empty newterm becomes head of list
	{
		polyTerm *newPtr = new polyTerm;

		newPtr -> exponent = exponent;
		newPtr -> coef = coef;
		newPtr -> next = NULL;
		head = newPtr;
		current = newPtr;
		newPtr = NULL;
		numTerms++;

	}
	else
	{
		findTerm(exponent);//if there is no term with that exponent makes newterm
		current -> coef = current -> coef + coef;//with zero in the coef and adds the new coeff
		numTerms++;
	}


}

void Poly:: findTerm( exponentType exponent )
{
	bool found = false;
	polyTerm *temp = head;
	//traverse list to find node with that exponent
	while (temp != NULL && !found)
	{
		if ( temp -> exponent == exponent)
		{
			current = temp;
			found = true;
		}
		else
		{
			temp = temp -> next;
		}
	}
	//if node with corresponding exponent cannot be found a new one is made
	if (temp == NULL && !found)
	{
		temp = new polyTerm;
		temp -> coef = 0;
		temp -> exponent = exponent;
		temp -> next = NULL;
		current -> next = temp;
		current = temp;
	}
	temp = NULL;
}
//finds highest exponent in list
exponentType Poly:: findDegree()
{
	exponentType highestDegree;
	polyTerm *temp = head;//pointer to head
	highestDegree = temp -> exponent;//highest degree assigned to exponent of first term
	while (temp != NULL)// travesrse list to find highesdegree
	{
		if ( temp-> exponent > highestDegree)
		{
			highestDegree = temp -> exponent;
		}
		temp = temp-> next;
	}
	temp = NULL;
	return highestDegree;
}

//uses findterm function to set a term in the polynomial
void Poly::setCoef( exponentType exponent, coefType coef )
{
	findTerm(exponent);
	current -> coef = coef;
}



//adds two polynomials
Poly Poly:: operator+( const Poly& p)
{
	//make a new empty instance of the polynomial
	Poly result = Poly();


	//pointers to polynomials on left and right hand
	//side of the operator
	polyTerm *leftPtr;
	polyTerm *rightPtr;
	leftPtr = head;
	rightPtr = p.head;
	//add all the terms from the left hand poly
	while ( leftPtr != NULL)
	{
		result.newTerm(leftPtr->exponent, leftPtr->coef);
		leftPtr = leftPtr ->next;
	}
	//add all the terms from the right hand poly
	while (rightPtr != NULL)
	{
		result.newTerm(rightPtr->exponent, rightPtr-> coef);
		rightPtr = rightPtr -> next;
	}


	//return the result
	return result;
}

//overloaded multiplication operator
Poly Poly:: operator*(const Poly& p)
{
	//make a new empty instance of the polynomial
	Poly result = Poly();
	//copy left polynomial
	Poly leftPoly = Poly(*this);
	//copy right polynomial
	Poly rightPoly = Poly(p);

	// new_coef and new_expo store the coefficient and exponent of the next term to
	// be added to result
	coefType new_coef; 
	exponentType new_expo; 
	//The loops below take each term in the Left Hand polynomial, multiply it with
	//all the terms of the right hand polynomial, and store term into n
	for(polyTerm * left = leftPoly.head; left != NULL; left= left->next)
	{
		for(polyTerm * right = rightPoly.head; right != NULL; right = right->next)
		{
			new_coef = left->coef * right->coef;
			new_expo = left->exponent + right->exponent;
			result.newTerm(new_expo, new_coef);
		}
	} 
	//returns the result of multiplication
	return result;

}



//overloaded assignment operator
Poly& Poly:: operator = (const Poly& p)
{
	//checks if copying the same instance
	if (this != &p)
	{
		polyTerm *leftPtr;
		polyTerm *rightPtr;
		leftPtr = this-> head;
		rightPtr = p.head;

		//delete instance
		while ( leftPtr!= NULL)
		{
			leftPtr = leftPtr ->next;
			delete leftPtr;
			this->numTerms--;
		}
		this-> head = NULL;
		this-> current = NULL;
		this->numTerms = 0;
		while (rightPtr!= NULL)
		{
			(*this).newTerm(rightPtr->exponent, rightPtr->coef);
			rightPtr = rightPtr -> next;
			this->numTerms++;
		}

	}
	return *this;
}