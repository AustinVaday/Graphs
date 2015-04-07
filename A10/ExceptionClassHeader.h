/**************************************************************************
* AUTHOR        : Austin Vaday
**************************************************************************/
#ifndef EXCEPTIONCLASSHEADER_H_
#define EXCEPTIONCLASSHEADER_H_

#include <string>
#include <iostream>
#include <sstream>
using namespace std;


/**
 * Exceptions that indicate functionality as described in their names!
 */


class OutOfRange{};
class NotFound{};
class Full{};
class Empty{};

// the following are additions for the tree ADT.
class NoParent{};
class ExternalNode{};
class RootAlreadyExists{};
class TreeError{};

// the following are additions for the hash map
class BadHash{};

// the following are additions for the graph ADT
class IndexNotSet{};
#endif /* EXCEPTIONCLASSHEADER_H_ */
