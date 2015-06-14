/* 
 * File:   FamilyMember.h
 * Author: builduser
 *
 * Created on June 9, 2015, 9:51 PM
 */

#ifndef FAMILYTREECLASS_H
#define	FAMILYTREECLASS_H


#include <stdint.h>
#include <string>

#include "libs/opengt/opengt.h"

#include "FamilyTreeOpResultCode.h"
#include "FamilyMemberClass.h"

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
        string inputFileName;

    public:
        // Default Constructor
        FamilyTreeClass();
        
        // Copy Constructor
        FamilyTreeClass(const FamilyTreeClass& orig);

        // Constructor
        FamilyTreeClass(string inputFileName);

        // Destructor
        ~FamilyTreeClass();
    
    // Member functions
    private:
        // Create the family tree based on the input file
        FamilyTreeOpResultCode constructTreeFromFile(string inputFileName);
        
        // Create the relationship between the from and to family members
        FamilyTreeOpResultCode addRelationship
        (
            string & from,
            string & to,
            relationship_t relationship
        );
        
        // Count the grandchildren for family member
        FamilyTreeOpResultCode countGrandChildren(FamilyMemberClass const & familyMember, uint32_t & count);
        
        // Find the grandparent for family member
        //FamilyTreeOpResultCode getGrandparent(string & memberName, FamilyMemberClass * grandParent);
        
        // Find Family Member
        FamilyMemberClass * findFamilyMember(string const & name);


        FamilyTreeOpResultCode getGrandparentsList
		(
			string & memberName,
			vector<FamilyMemberClass *> & grandParentList
		);
                
    public:
        // Initialize the family tree
        FamilyTreeOpResultCode initialize(string inputFileName);

        // Count the siblings for familyMember
		FamilyTreeOpResultCode countSiblings(string memberName, uint32_t & count);

		// Count the siblings for familyMember
		FamilyTreeOpResultCode getGrandparentNameList(string memberName, vector<string> & grandparentList);
};

} /* namespace FamilyTree */

#endif	/* FAMILYTREECLASS_H */

