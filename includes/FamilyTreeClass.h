/**
 *  @file    FamilyTreeClass.h.cpp
 *  @author  Kevin Dious
 *  @date    6/15/2015
 *
 *  @brief Class definition for FamilyMemberClass object
 *
 *  @section DESCRIPTION
 *
 *  This file details the definition of the
 *  FamilyTreeClass class.
 *
 *  This class contains the members and methods to store
 *  and perform operations on the family tree.  The family
 *  tree is implemented as a graph leveraging the
 *  OpenGraphTheory library.  Family members are represented
 *  as Vertex objects in the graph while relationships are
 *  represented as edges.
 *
 *  The public member methods can be used to retrieve information
 *  from the family tree.  THe public methods are defined in a
 *  way that hides the implementation details and graph specific
 *  data structures from the caller.  In this way, if there is
 *  a desire to change the way the family tree is implemented
 *  (such as use a tree instead of a graph) this can be done
 *  easily without changing the public method definitions.
 *
 */

#ifndef FAMILYTREECLASS_H
#define	FAMILYTREECLASS_H


#include <stdint.h>
#include <string>

#include "libs/opengt/opengt.h"

#include "FamilyTreeOpResultCode.h"
#include "FamilyMemberClass.h"

#include "libs/gtest/gtest_prod.h" // For testing

using namespace std;
using namespace OpenGraphtheory;

namespace FamilyTree {

class FamilyTreeClass {
    // Constants and enums
	public:
		// Relationships between family members
		typedef enum {
			Parent_Child,
			Child_Parent,
			Sibling
		} relationship_t;

	// Member variables
    private:
        // Graph that will represent the family tree
        Graph m_Graph;
        
        // Name of the input file containing the data for the tree
        string m_inputFileName;

    public:
        // Default Constructor

        //! @brief Default constructor
        FamilyTreeClass();
        
        //! @brief Copy constructor
        FamilyTreeClass(const FamilyTreeClass& orig);

        //! @brief Constructor
        //! @param [in] Name of the input file
        FamilyTreeClass(string const & inputFileName);

        //! @brief Destructor
        ~FamilyTreeClass();
    
    // Member functions
    private:
        //! @brief Create the family tree based on the input file
        //! @param[in] inputFileName File name of the input file
        //! @return SUCCESS or error
        FamilyTreeOpResultCode constructTreeFromFile(string const & inputFileName);
        
        //! @brief Create the relationship between the from and to family members
        //! @return SUCCESS or error
        FamilyTreeOpResultCode addRelationship
        (
            string const & from,
            string const & to,
            relationship_t relationship
        );
        
        //! @brief Find a family member
        //! @param[in] name Name of the family member to find
        //! @return FamilyMemberClass object for name or NULL
        FamilyMemberClass * findFamilyMember(string const & name);

        //! @brief Retrieves the list of grandparents for memberName
        //! @param[in] memberName Name of the family member whose grandparents list to retrieve
        //! @param[in/out] list A vector containing pointers to the
        //!					   FamilyMemberClass objects that are grandparents of the specified member
        //! @return SUCCESS or error
        FamilyTreeOpResultCode getGrandparentsList
		(
			string const & memberName,
			vector<FamilyMemberClass *> & list
		);

        //! @brief Retrieves the list of children for memberName
		//! @param[in] memberName Name of the family member whose children list to retrieve
		//! @param[in/out] list A vector containing pointers to the
		//!					   FamilyMemberClass objects that are children of the specified member
		//! @return SUCCESS or error
        FamilyTreeOpResultCode getChildrenList
		(
			string const & memberName,
			vector<FamilyMemberClass *> & list
		);

        //! @brief Retrieves the list of children for memberName
		//! @param[in] memberName Name of the family member whose sibling list to retrieve
		//! @param[in/out] list A vector containing pointers to the
		//!					   FamilyMemberClass objects that are siblings of the specified member
		//! @return SUCCESS or error
        FamilyTreeOpResultCode getSiblingList
		(
			string const & memberName,
			vector<FamilyMemberClass *> & list
		);

    public:
        //! @brief Initialize the family tree
		//! @param[in] inputFileName Name of the input file that has the family tree data
		//! @return SUCCESS or error
        FamilyTreeOpResultCode initialize(string const & inputFileName);

        //! @brief Retrieves the list of names of the grandparents for the specified family member
		//! @param[in] memberName Name of the family member whose grandparent list to retrieve
		//! @param[in/out] nameList A vector containing the names of the grandparents of the specified member
		//! @return SUCCESS or error
		FamilyTreeOpResultCode getGrandparentNameList(string const & memberName, vector<string> & nameList);

        //! @brief Retrieves the list of names of the children for the specified family member
		//! @param[in] memberName Name of the family member whose children list to retrieve
		//! @param[in/out] nameList A vector containing the names of the children of the specified member
		//! @return SUCCESS or error
		FamilyTreeOpResultCode getChildrenNameList(string const & memberName, vector<string> & nameList);

        //! @brief Retrieves the list of names of the siblings for the specified family member
		//! @param[in] memberName Name of the family member whose siblings list to retrieve
		//! @param[in/out] nameList A vector containing the names of the siblings of the specified member
		//! @return SUCCESS or error
		FamilyTreeOpResultCode getSiblingNameList(string const & memberName, vector<string> & nameList);

		//! @brief Retrieves the list of names of all members of the family tree
		//! @param[in/out] nameList A vector containing the names of the family members
		//!				   in the family tree
		//! @return SUCCESS or error
		FamilyTreeOpResultCode getFamilyMembersNameList(vector<string> & nameList);

        //! @brief Retrieves the list of names of the family members who
		//!		  have the specified number of children
		//! @param[in] count Specified number of children
		//! @param[in/out] nameList A vector containing the names of the members who
		//!						   have the specified number of children
		//! @return SUCCESS or error
		FamilyTreeOpResultCode getMembersWithChildCount(uint32_t count, vector<string> & nameList);

        //! @brief Retrieves the list of names of the family members who
		//!		  have the specified number of siblings
		//! @param[in] count Specified number of siblings
		//! @param[in/out] nameList A vector containing the names of the members who
		//!						   have the specified number of siblings
		//! @return SUCCESS or error
		FamilyTreeOpResultCode getMembersWithSiblingCount(uint32_t count, vector<string> & nameList);

        //! @brief Retrieves the list of names of the family members who
		//!		  have the most grandchildren
		//! @param[in/out] nameList A vector containing the names of the members who
		//!						   have the most grandchildren
		//! @return SUCCESS or error
		FamilyTreeOpResultCode getMembersWithMostGrandchildren(vector<string> & nameList);

};

} /* namespace FamilyTree */

#endif	/* FAMILYTREECLASS_H */

