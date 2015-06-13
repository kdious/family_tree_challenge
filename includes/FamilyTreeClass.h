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
            FamilyMemberClass const * from, 
            FamilyMemberClass const * to, 
            FamilyMemberClass::relationship_t relationship
        );
        
        // Count the grandchildren for familyMember
        FamilyTreeOpResultCode countGrandChildren(FamilyMemberClass const & familyMember, uint32_t & count);
        
        // Count the siblings for familyMember
        FamilyTreeOpResultCode countSiblings(FamilyMemberClass const & familyMember, uint32_t & count);
        
        // Find the grandparent for familyMember
        FamilyTreeOpResultCode findGrandParent(FamilyMemberClass const & familyMember, FamilyMemberClass * grandParent);
        
        // Find Family Member
        FamilyMemberClass * findFamilyMember(string const & name);
                
    public:
        // Initialize the family tree
        FamilyTreeOpResultCode initialize(string inputFileName);
};

} /* namespace FamilyTree */

#endif	/* FAMILYTREECLASS_H */

