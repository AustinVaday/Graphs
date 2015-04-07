/**************************************************************************
* AUTHOR        : Austin Vaday
**************************************************************************/
#include "header.h"
/**************************************************************************
 *
 * FUNCTION PrintHeader
 *_________________________________________________________________________
 * This function receives an assignment name, type and number
 *      outputs the appropriate header - returns the heading variable.
 *_________________________________________________________________________
 * PRE-CONDITIONS
 *   asName: Assignment Name has to be previously defined
 *   asType: Assignment Type has to be previously defined
 *   asNum : Assignment Number has to be previously defined
 *
 * POST-CONDITIONS
 *   This function will return the heading variable.
 *************************************************************************/
string PrintHeader (string asName,   // IN - Assignment Name
					char   asType,   // IN - Assignment type
									 //    -(LAB or ASSIGNMENT)
					int    asNum)    // IN - Assignment number
{
	// Declaration
	ostringstream headingOSS;

	// OUTPUT - Will output the class header
	headingOSS << left;
	headingOSS << "*******************************************************";
	headingOSS << "\n* PROGRAMMED BY : Austin Vaday";
	headingOSS << "\n* " << setw(14) << "STUDENT ID" << ": 354687";
	headingOSS << "\n* " << setw(14) << "CLASS" << ": CS1D : TTH-5:30-7:20 pm";
	headingOSS << "\n* ";

	// IF-STATEMENT - This will determine whether the header will display
	// "Assignment" or "Lab"
	if(toupper(asType) == 'L')
	{
		headingOSS << "LAB #" << setw(9);
	}
	else
	{
		headingOSS << "ASSIGNMENT #" << setw(2);
	}

	headingOSS << asNum << ": " << asName;
	headingOSS << "\n***************************************************";
	headingOSS << "****\n\n";
	headingOSS << right;

	return headingOSS.str();
}

