/*
 * FamilyMemberClass.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: builduser
 */

#include "FamilyMemberClass.h"

namespace FamilyTree {
	// Default constructor
	FamilyMemberClass::FamilyMemberClass() {
	}

    // Destructor
	FamilyMemberClass::~FamilyMemberClass() {
	}

	uint32_t FamilyMemberClass::getSiblingCount() {
		uint32_t siblingCount = 0;

		// Retrieve the set of from edges connected to this vertex
		// where "from" edge means the edge is directed from the vertex
		EdgeSet adjacentEdges = CollectIncidentEdges(false, true, false);

		// If the edge has a "sibling relationship"
		// then increment the sibling count.
		for (unsigned int i = 0; i < adjacentEdges.size(); i++) {
			Edge * const currentEdge = adjacentEdges[i];
			IntAttribute * pRelationshipAttr = (IntAttribute *)currentEdge->GetAttribute("Relationship");
			if(pRelationshipAttr->Value == Sibling) {
				siblingCount++;
			}
		}

		return siblingCount;
	}

}


