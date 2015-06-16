/**
 *  @file    FamilyTreeDebug.h.cpp
 *  @author  Kevin Dious
 *  @date    6/15/2015
 *
 *  @brief File that implements various logging and debugging mechanisms
 *
 *  @section DESCRIPTION
 *
 *  This file details the definition of the
 *  FamilyTreeClass class.
 *
 *  Defines various C/C++ logging macros and methods
 *  that can be used for logging.
 *
 */

#ifndef FAMILYTREEDEBUG_H_
#define FAMILYTREEDEBUG_H_

#include "FamilyMemberClass.h"
#include "FamilyTreeClass.h"

// Inclusion of stdio functions
#ifdef __cplusplus
#include <cstdio>
#else
#include <stdio.h>
#endif

#define DEBUG               // Note: Want to define this in the makefile or elsewhere

#ifdef DEBUG

#define __METHOD_NAME__     FamilyTree::FamilyTreeDebug::methodName(__PRETTY_FUNCTION__).c_str()

#define LOG_OFF             0
#define LOG_FATAL           1
#define LOG_ERROR           2
#define LOG_WARN            4
#define LOG_INFO            8
#define LOG_DEBUG           16
#define LOG_ENTRY           32

#define LOG_LEVEL_FATAL		LOG_FATAL
#define LOG_LEVEL_ERROR		(LOG_FATAL | LOG_ERROR)
#define LOG_LEVEL_WARN		(LOG_FATAL | LOG_ERROR | LOG_WARN)
#define LOG_LEVEL_INFO		(LOG_FATAL | LOG_ERROR | LOG_WARN | LOG_INFO)
#define LOG_LEVEL_DEBUG		(LOG_FATAL | LOG_ERROR | LOG_WARN | LOG_INFO | LOG_DEBUG)
#define LOG_ALL             (LOG_FATAL | LOG_ERROR | LOG_WARN | LOG_INFO | LOG_DEBUG | LOG_ENTRY)

#define LOG_MASK            LOG_LEVEL_DEBUG

// Note: The Logging MACROS need to be refined so
// that they completely disable all logging
// When the log level is not set in the LOG_MASK
// For now it is better to use LOG_LEVEL_DEBUG or
// LOG_LEVEL_ALL.

#ifdef __cplusplus  // C++ Debug Macros

#define FamilyTreeLogMsg(level, ...) ((level & LOG_MASK) == 0) ? 0 : printf("%s (%d): ", __METHOD_NAME__, __LINE__); printf(__VA_ARGS__); printf("\n");
#define FamilyTreeErrorMsg(level, ...) ((level & LOG_MASK) == 0) ? 0 : printf("Error - %s (%d): ", __METHOD_NAME__, __LINE__); printf(__VA_ARGS__); printf("\n");

#define FamilyTreeLogMsgMain(level, ...) ((level & LOG_MASK) == 0) ? 0 : printf("%s (%d): ", __func__, __LINE__); printf(__VA_ARGS__); printf("\n");
#define FamilyTreeErrorMsgMain(level, ...) ((level & LOG_MASK) == 0) ? 0 : printf("Error - %s (%d): ", __func__, __LINE__); printf(__VA_ARGS__); printf("\n");

#else               // C Debug Macros
#define FamilyTreeLogMsg(level, ...) ((level & LOG_MASK) == 0) ? 0 : printf("%s (%d): ", __func__, __LINE__); printf(__VA_ARGS__); printf("\n");
#define FamilyTreeErrorMsg(level, ...) ((level & LOG_MASK) == 0) ? 0 : printf("Error - %s (%d): ", __func__, __LINE__); printf(__VA_ARGS__); printf("\n");
#endif

#endif  // DEBUG

#ifdef __cplusplus  /* C++ Debug methods */
#include <string>

namespace FamilyTree
{
	class FamilyTreeDebug {
		// Member function
		private:
		public:
	        static std::string methodName(const std::string & prettyFunction) {
	        	size_t space = prettyFunction.find(" ");
	        	string classString = prettyFunction.substr(space + 1);

	        	size_t colons = classString.find("::");
				size_t begin = classString.substr(0, colons).rfind(" ") + 1;
				size_t end = classString.rfind("(") - begin;

				return classString.substr(begin, end);
	        }
	};
}
#endif /* C++ Debug Methods */

#ifdef __cplusplus  /* C++ namespace declaration */
using namespace FamilyTree;
#endif

/* Convert constants to C-Strings */
#define TO_C_STR(constant) #constant

static char * familyTreeDebugRelationshipToCStr(FamilyTreeClass::relationship_t relationship) {
    switch(relationship) {
        case FamilyTreeClass::Parent_Child:	return TO_C_STR(Parent_Child);
        case FamilyTreeClass::Child_Parent:	return TO_C_STR(Child_Parent);
        case FamilyTreeClass::Sibling:   	return TO_C_STR(Sibling);
        default:            return TO_C_STR(Unknown);
    }
}

static char * familyTreeDebugGenderToCStr(FamilyMemberClass::gender_t gender) {
    switch(gender) {
        case FamilyMemberClass::Male:		return TO_C_STR(Male);
        case FamilyMemberClass::Female: 	return TO_C_STR(Female);
        case FamilyMemberClass::Other:   	return TO_C_STR(Other);
        default:        return TO_C_STR(Unknown);
    }
}

#endif /* FAMILYTREEDEBUG_H_ */
