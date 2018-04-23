#include <iostream> 
#include <fstream>
#include <string> 
#include <sstream>

#include "PolytermsP.h"
int main(int argc, char* argv[])
{
	ifstream inFile;
	ofstream outFile;
	string line;
	try
	{
		if (argc == 3)//neeeded number of arguments
		{
			inFile.open(argv[1]);//first argument opens input file
			outFile.open(argv[2]);//second argument opens output file
			if (inFile.is_open() && outFile.is_open())
			{
				Poly p1 = Poly();//creates new instancs of poly class
				Poly p2 = Poly();
				Poly multiply = Poly();//will contain the two polynomials multiplied
				Poly add = Poly();// will contain the sum of polynomials
				exponentType ex;
				coefType co;
				bool separator = false;
				try
				{
					while(!inFile.eof())//loop until end of input
					{

						getline(inFile, line);//get first line
						istringstream iss (line);
						iss >> co;
						iss >> ex;

						//check for negative or zero coefficient
						if ( ex < 0) throw(4);
						if( co == 0) throw(5);
						if(line == "XXX")//checks for "XXX"
						{
							separator = true;
							getline(inFile, line);
							istringstream iss (line);
							iss >> co;
							iss >> ex;

						}



						//if after the separator terms from input file go into p2
						if( separator == true)
						{
							p2.newTerm( ex, co);
						}
						else//if before separator terms from input file go into p1
							p1.newTerm( ex, co);


					}

					multiply = p1 * p2;
					add = p1 + p2;
					int sumLength = add.findDegree();
					int multLength = multiply.findDegree();

					//writes sumofpolynomials to file
					for ( int i = sumLength; i >= 0; i--)
					{
						if ( add.getCoef(i) != 0)
						{
							if ( i >= 1)
							{
								outFile << add.getCoef(i)  << " " <<i << endl ;
							}
							else
							{
								outFile << add.getCoef(i)  <<" " << i << endl ;
								outFile << "YYY" << endl;
							}
						}
					}
					//writes multiplied polynomials to file
					for ( int i = multLength; i >= 0; i--)
					{
						if ( multiply.getCoef(i) != 0)
						{
							if ( i >= 1)
							{
								outFile << multiply.getCoef(i)  << " " <<i << endl ;
							}
							else
							{
								outFile << multiply.getCoef(i)  <<" " << i << endl ;
							}
						}
					}

					//exception handling
					if (separator == false)
					{
						throw 1;
					}
				}
			
			catch(int x)
			{
				if (x == 1)
					outFile << "bad input file: did not have 'XXX' to separate polynomials" << endl;
			}
			inFile.close();//close files
			outFile.close();
		}
		else
		{
			throw 2;
		}
	}
			else
			{
				throw 3;
			}
} 
catch(int x)
{
	if (x == 3)
		outFile << "input or output file not provided on command line"
		<< endl;
	else if (x == 2)
		outFile << "input file does not exist" << endl;
	else if (x == 4)
		outFile << "ERROR: Input exponent is negative!" << endl;
	else if (x == 5)
		outFile << "ERROR: Input coefficient is zero!" << endl;

}

return 0;
	} 