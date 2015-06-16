/**
 *  @file    FamilyMemberClass.cpp
 *  @author  Kevin Dious
 *  @date    6/15/2015
 *
 *  @brief Implementation of the FamilyMemberClass
 *
 *  @section DESCRIPTION
 *
 *  Implements the FamilyMemberClass
 *
 */

#include "FamilyMemberClass.h"
#include "FamilyTreeClass.h"

namespace FamilyTree {

	FamilyMemberClass::FamilyMemberClass() {
	}

	FamilyMemberClass::~FamilyMemberClass() {
	}

	uint32_t FamilyMemberClass::getNumberOfSiblings() {
		uint32_t numberOfSiblings = 0;

		// Retrieve the set of from edges connected to this vertex
		// where "from" edge means the edge is directed from the vertex
		EdgeSet adjacentEdges = CollectIncidentEdges(false, true, false);

		// If the edge has a "sibling relationship"
		// then increment the sibling count.
		for (unsigned int i = 0; i < adjacentEdges.size(); i++) {
			Edge * const currentEdge = adjacentEdges[i];
			IntAttribute * pRelationshipAttr = (IntAttribute *)currentEdge->GetAttribute("Relationship");
			if(pRelationshipAttr->Value == FamilyTreeClass::Sibling) {
				numberOfSiblings++;
			}
		}

		return numberOfSiblings;
	}

	uint32_t FamilyMemberClass::getNumberOfChildren() {
			uint32_t numberOfChildren = 0;

			// Retrieve the set of from edges connected to this vertex
			// where "from" edge means the edge is directed from the vertex
			EdgeSet adjacentEdges = CollectIncidentEdges(false, true, false);

			// If the edge has a "sibling relationship"
			// then increment the sibling count.
			for (unsigned int i = 0; i < adjacentEdges.size(); i++) {
				Edge * const currentEdge = adjacentEdges[i];
				IntAttribute * pRelationshipAttr = (IntAttribute *)currentEdge->GetAttribute("Relationship");
				if(pRelationshipAttr->Value == FamilyTreeClass::Parent_Child) {
					numberOfChildren++;
				}
			}

			return numberOfChildren;
		}

}


