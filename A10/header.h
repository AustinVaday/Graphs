/**************************************************************************
* AUTHOR        : Austin Vaday
**************************************************************************/

#ifndef HEADER_H_
#define HEADER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <sstream>
#include <limits>
#include <ios>
#include <fstream>
#include "ExceptionClassHeader.h"
#include "UndirectedGraphHeader.h"


using namespace std;

/**************************************************************************
 * PrintHeader
 * 	This function receives an assignment (or lab) name, type and number
 * 	then outputs the appropriate header
 * 	- returns nothing -> this will output the class heading.
 *************************************************************************/
 string PrintHeader (string asName,    	// IN - Assignment Name
				    char   asType,    	// IN - Assignment type
				  	  	  	  	    	//    -(LAB or ASSIGNMENT)
				    int    asNum);		// IN - Assignment number

#endif /* HEADER_H_ */
