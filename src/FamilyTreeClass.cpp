/**
 *  @file    FamilyTreeClass.cpp
 *  @author  Kevin Dious
 *  @date    6/15/2015
 *
 *  @brief Implementation of the FamilyTreeClass
 *
 *  @section DESCRIPTION
 *
 *  Implements the FamilyTreeClass
 *
 */

#include <fstream>
#include "libs/boost/algorithm/string.hpp"	// local boost libs
//#include <boost/algorithm/string.hpp>		// Use installed boost libs

#include "libs/opengt/opengt.h"

#include "FamilyTreeClass.h"
#include "FamilyTreeDebug.h"

namespace FamilyTree {
    
    FamilyTreeClass::FamilyTreeClass() {
    }

    FamilyTreeClass::FamilyTreeClass(const FamilyTreeClass& orig) {
    }
    
    FamilyTreeClass::FamilyTreeClass(string const & inputFileName) {
    	m_inputFileName = inputFileName;
    }

    FamilyTreeClass::~FamilyTreeClass() {
    }


    FamilyTreeOpResultCode FamilyTreeClass::initialize(string const & inputFileName) {
        return constructTreeFromFile(inputFileName);
    }

    FamilyMemberClass * FamilyTreeClass::findFamilyMember(string const & memberName) {

        FamilyMemberClass * pFamilyMember = NULL;

        // Search the list of vertices to see
        // if the label of a vertex matches memberName
        // If so, return that vertex.
        // Otherwise, return NULL
        for(VertexIterator it = m_Graph.BeginVertices(); it != m_Graph.EndVertices(); it++) {
            if((*it)->GetLabel("Member_Name").compare(memberName) == 0) {
                pFamilyMember = (FamilyMemberClass *)(*it);
                break;
            }
        }

        return pFamilyMember;
    }

    FamilyTreeOpResultCode FamilyTreeClass::getGrandparentsList
	(
		string const & memberName,
		vector<FamilyMemberClass *> & list
    ) {
    	// Retrieve the FamilyMemberClass objects for
		// the specified family member.  Return error
		// if one of them is not present in the tree.
    	FamilyMemberClass * pFamilyMember = findFamilyMember(memberName);
    	if(pFamilyMember == NULL) {
			FamilyTreeErrorMsg(LOG_ERROR, "%s is not in the family tree.", memberName.c_str())
			return FAMILY_MEMBER_NOT_FOUND;
		}

    	// Clear the vector
    	list.clear();

    	// Retrieve the set of from edges connected to this vertex
		// where "from" edge means the edge is directed from the vertex
		EdgeSet childAdjacentEdges = pFamilyMember->CollectIncidentEdges(false, true, false);

		// Find the parent of each parent of pFamilyMember.  Store
		// pointers to each of these FamilyMemberClass objects in
		// grandParentList.  These are the pointers to each grandparent
		// of pFamilyMember
		for (unsigned int i = 0; i < childAdjacentEdges.size(); i++) {
			Edge * const childParentEdge = childAdjacentEdges[i];
			IntAttribute * pRelationshipAttr = (IntAttribute *)childParentEdge->GetAttribute("Relationship");

			// If this edge has a child->parent relationship
			// then the "to" vertex is the parent of pFamilyMember
			if(pRelationshipAttr->Value == Child_Parent) {
				FamilyMemberClass * pParent = (FamilyMemberClass *)childParentEdge->To();

				// Retrieve the set of from edges connected to this vertex
				// where "from" edge means the edge is directed from the vertex
				EdgeSet childAdjacentEdges = pParent->CollectIncidentEdges(false, true, false);

				// Find the grandparent of pFamilyMember
				// (the parent of pParent)
				for (unsigned int j = 0; j < childAdjacentEdges.size(); j++) {
					Edge * const parentGrandparentEdge = childAdjacentEdges[j];
					IntAttribute * pRelationshipAttr = (IntAttribute *)parentGrandparentEdge->GetAttribute("Relationship");

					// If this is a child->parent edge,
					// get the parent vertex.  This is the
					// grandparent of memberName
					if(pRelationshipAttr->Value == Child_Parent) {
						list.push_back((FamilyMemberClass *)parentGrandparentEdge->To());
					}
				}
			}
		}

		// If we reach here, everything is fine.
		// Return SUCCESS.
    	return SUCCESS;

    }

    FamilyTreeOpResultCode FamilyTreeClass::getChildrenList
	(
		string const & memberName,
		vector<FamilyMemberClass *> & list
    ) {
    	// Retrieve the FamilyMemberClass objects for
		// the specified family member.  Return error
		// if one of them is not present in the tree.
    	FamilyMemberClass * pFamilyMember = findFamilyMember(memberName);
    	if(pFamilyMember == NULL) {
			FamilyTreeErrorMsg(LOG_ERROR, "%s is not in the family tree.", memberName.c_str())
			return FAMILY_MEMBER_NOT_FOUND;
		}

    	// Clear the vector
    	list.clear();

    	// Retrieve the set of from edges connected to this vertex
		// where "from" edge means the edge is directed from the vertex
		EdgeSet memberAdjacentEdges = pFamilyMember->CollectIncidentEdges(false, true, false);

		// Find the parent of each parent of pFamilyMember.  Store
		// pointers to each of these FamilyMemberClass objects in
		// grandParentList.  These are the pointers to each grandparent
		// of pFamilyMember
		for (unsigned int i = 0; i < memberAdjacentEdges.size(); i++) {
			Edge * const currentMemberEdge = memberAdjacentEdges[i];
			IntAttribute * pRelationshipAttr = (IntAttribute *)currentMemberEdge->GetAttribute("Relationship");

			// If this is a parent->child edge,
			// get the child vertex.  This is a
			// child of memberName
			if(pRelationshipAttr->Value == Parent_Child) {
				list.push_back((FamilyMemberClass *)currentMemberEdge->To());
			}
		}

    	return SUCCESS;
    }

    FamilyTreeOpResultCode FamilyTreeClass::getSiblingList
	(
		string const & memberName,
		vector<FamilyMemberClass *> & list
    ) {
    	// Retrieve the FamilyMemberClass objects for
		// the specified family member.  Return error
		// if the family member is not present in the tree.
    	FamilyMemberClass * pFamilyMember = findFamilyMember(memberName);
    	if(pFamilyMember == NULL) {
			FamilyTreeErrorMsg(LOG_ERROR, "%s is not in the family tree.", memberName.c_str())
			return FAMILY_MEMBER_NOT_FOUND;
		}

    	// Clear the vector
    	list.clear();

    	// Retrieve the set of from edges connected to this vertex
		// where "from" edge means the edge is directed from the vertex
		EdgeSet memberAdjacentEdges = pFamilyMember->CollectIncidentEdges(false, true, false);

		// Find the parent of each parent of pFamilyMember.  Store
		// pointers to each of these FamilyMemberClass objects in
		// grandParentList.  These are the pointers to each grandparent
		// of pFamilyMember
		for (unsigned int i = 0; i < memberAdjacentEdges.size(); i++) {
			Edge * const currentMemberEdge = memberAdjacentEdges[i];
			IntAttribute * pRelationshipAttr = (IntAttribute *)currentMemberEdge->GetAttribute("Relationship");

			// If this is a parent->child edge,
			// get the child vertex.  This is a
			// child of memberName
			if(pRelationshipAttr->Value == Sibling) {
				list.push_back((FamilyMemberClass *)currentMemberEdge->To());
			}
		}

    	return SUCCESS;
    }

    FamilyTreeOpResultCode FamilyTreeClass::getGrandparentNameList
	(
		string const & memberName,
		vector<string> & grandparentStringList
	) {
    	// Retrieve the list of grandparents for memberName
    	// If there is an error, return the error
    	vector<FamilyMemberClass *> grandParentList;
    	FamilyTreeOpResultCode result = getGrandparentsList(memberName, grandParentList);
    	if(result != SUCCESS) {
    		FamilyTreeErrorMsg(LOG_ERROR, "Failed to retrieve grandparent name list for %s.", memberName.c_str());
    		return result;
    	}

    	// Clear the input list
    	grandparentStringList.clear();

    	// Create the list of grandparent name strings
    	for(vector<FamilyMemberClass *>::iterator it = grandParentList.begin() ; it != grandParentList.end(); ++it) {
    		FamilyMemberClass * pGrandParent = (*it);
    		grandparentStringList.push_back(pGrandParent->GetLabel("Member_Name"));
    	}

    	return SUCCESS;
    }


    FamilyTreeOpResultCode FamilyTreeClass::getChildrenNameList
	(
		string const & memberName,
		vector<string> & nameList
	) {
    	vector<FamilyMemberClass *> childrenList;
    	FamilyTreeOpResultCode result = getChildrenList(memberName, childrenList);
    	if(result != SUCCESS) {
    		FamilyTreeErrorMsg(LOG_ERROR, "Failed to retrieve children name list for %s.", memberName.c_str());
    		return result;
    	}

    	// Clear the input list
    	nameList.clear();

    	// Create the list of children name strings
    	for(vector<FamilyMemberClass *>::iterator it = childrenList.begin() ; it != childrenList.end(); ++it) {
    		FamilyMemberClass * pChild = (*it);
    		nameList.push_back(pChild->GetLabel("Member_Name"));
    	}

    	return SUCCESS;
    }

    FamilyTreeOpResultCode FamilyTreeClass::getSiblingNameList
	(
		string const & memberName,
		vector<string> & nameList
	) {
    	vector<FamilyMemberClass *> siblingList;
    	FamilyTreeOpResultCode result = getSiblingList(memberName, siblingList);
    	if(result != SUCCESS) {
    		FamilyTreeErrorMsg(LOG_ERROR, "Failed to retrieve sibling name list for %s.", memberName.c_str());
    		return result;
    	}

    	// Clear the input list
    	nameList.clear();

    	// Create the list of sibling name strings
    	for(vector<FamilyMemberClass *>::iterator it = siblingList.begin() ; it != siblingList.end(); ++it) {
    		FamilyMemberClass * pSibling = (*it);
    		nameList.push_back(pSibling->GetLabel("Member_Name"));
    	}

    	return SUCCESS;
    }

    FamilyTreeOpResultCode FamilyTreeClass::getFamilyMembersNameList(vector<string> & nameList) {

    	// CLear the list
    	nameList.clear();

    	// Search the list of vertices and add
    	// the label to the nameList.
    	// For now, the label of each vertex
    	// stores the name of that family member
		for(VertexIterator it = m_Graph.BeginVertices(); it != m_Graph.EndVertices(); it++) {
			nameList.push_back((*it)->GetLabel("Member_Name"));
		}

		return SUCCESS;
	}

    FamilyTreeOpResultCode FamilyTreeClass::getMembersWithChildCount
	(
		uint32_t count,
		vector<string> & nameList
	) {
    	// Clear the nameList
    	nameList.clear();

    	// Find the names of the members that have children count == count
		for(ConstVertexIterator it = m_Graph.BeginVertices(); it != m_Graph.EndVertices(); ++it) {
			FamilyMemberClass * pCurrentMember = (FamilyMemberClass *)(*it);
			if(pCurrentMember->getNumberOfChildren() == count) {
				nameList.push_back(pCurrentMember->GetLabel("Member_Name"));
			}
		}

		return SUCCESS;
    }

    FamilyTreeOpResultCode FamilyTreeClass::getMembersWithSiblingCount
	(
		uint32_t count,
		vector<string> & nameList
	) {
		// Clear the nameList
		nameList.clear();

		// Find the names of the members that have children count == count
		for(ConstVertexIterator it = m_Graph.BeginVertices(); it != m_Graph.EndVertices(); ++it) {
			FamilyMemberClass * pCurrentMember = (FamilyMemberClass *)(*it);
			if(pCurrentMember->getNumberOfSiblings() == count) {
				nameList.push_back(pCurrentMember->GetLabel("Member_Name"));
			}
		}

		return SUCCESS;
	}

    FamilyTreeOpResultCode FamilyTreeClass::getMembersWithMostGrandchildren(vector<string> & nameList) {
		// Clear the nameList
		nameList.clear();

		FamilyTreeOpResultCode resultCode;
		uint32_t largestGrandChildrenCount = 0;

		// Iterate through each family member and get the list of grandchildren.
		// 1. If the list of grandchildren for the current member > largestGrandChildrenCount,
		//    then clear the list, add the current member to the nameList, and
		//    update the largestGrandChildrenCount value.
		//
		// 2. If the list of grandchildren for current member == largestGrandChildrenCount,
		//    then current member has the same number of grandchildren as the
		//    largestGrandChildrenCount.  Add current member to the list.
		//
		// 3. Otherwise, do nothing.

		for(ConstVertexIterator itParent = m_Graph.BeginVertices(); itParent != m_Graph.EndVertices(); ++itParent) {
			// Current vertex is the parent
			FamilyMemberClass * pParent = (FamilyMemberClass *)(*itParent);

			// Get the list of children of the parent
			// If this is not possible, print log message
			// and return the error code
			vector<FamilyMemberClass *> childrenList;
			resultCode = getChildrenList(pParent->GetLabel("Member_Name"), childrenList);
			if(resultCode != SUCCESS) {
				FamilyTreeErrorMsg
				(
					LOG_ERROR, "Unable to retrieve children name list for %s.",
					pParent->GetLabel("Member_Name").c_str()
				);
				return resultCode;
			}
			// Iterate through the children of pParent
			for(vector<FamilyMemberClass *>::iterator itChild = childrenList.begin(); itChild != childrenList.end(); ++itChild) {
				// Current vertex is a child of pParent.
				FamilyMemberClass * pChild = (*itChild);

				if(pChild->getNumberOfChildren() > largestGrandChildrenCount) {
					// If the current child has more children than largestGrandChildrenCount
					// then pParent has more grandchildren than the previous family members
					// in mameList.  Clear the list, add pParent to the list and update
					// largestGrandChildrenCount with the count of pChild children count.
					nameList.clear();
					nameList.push_back(pParent->GetLabel("Member_Name"));
					largestGrandChildrenCount = pChild->getNumberOfChildren();
				}
				else if(pChild->getNumberOfChildren() == largestGrandChildrenCount) {
					// If the current child has the same number of children as largestGrandChildrenCount
					// then pParent has the same number of grandchildren than the current members
					// in mameList. Just add pParent to the list.
					nameList.push_back(pParent->GetLabel("Member_Name"));
				}
				else {
					// Do nothing
				}
			}
		}

		return SUCCESS;
	}

    FamilyTreeOpResultCode FamilyTreeClass::addRelationship
    (
        string const & from,
        string const & to,
        relationship_t relationship
    ) {
    	// Retrieve the FamilyMemberClass objects for
    	// the from and to family members.  Return
    	// error if one of them is not present in the tree.
        FamilyMemberClass * fromMember = findFamilyMember(from);
        if(fromMember == NULL) {
			FamilyTreeErrorMsg(LOG_ERROR, "%s is not in the family tree.", from.c_str());
        	return FAMILY_MEMBER_NOT_FOUND;
        }

        FamilyMemberClass * toMember = findFamilyMember(to);
        if(fromMember == NULL) {
			FamilyTreeErrorMsg(LOG_ERROR, "%s is not in the family tree.", to.c_str());
			return FAMILY_MEMBER_NOT_FOUND;
		}

        // Create new directed edge where fromMemer is the
        // out vertex (start) and toMember is the in vertex (the endpoint)
        EdgeIterator newEdgeIterator = m_Graph.AddArc((Vertex *)fromMember, (Vertex *)toMember);
        
        // Get pointer to edge and make sure it is
        // a valid directed edge valid
        Edge * newEdge = *newEdgeIterator;
        if(newEdge == NULL) {
            // Print error Message
            FamilyTreeErrorMsg(LOG_ERROR, "Failed to add directed edge %s->%s to the graph.",
            	from.c_str(),
				to.c_str()
			);

            // Remove the edge from the graph
            m_Graph.RemoveEdge(newEdgeIterator);
            
            // Return error code
            return ADD_EDGE_ERROR;
        }
        
        if(newEdge->IsDirected() == false) {
            // Print error Message
            FamilyTreeErrorMsg(LOG_ERROR, "Directed edge %s->%s was not created as a proper directed edge.",
				from.c_str(),
				to.c_str()
			);
            // Remove the edge from the graph
            m_Graph.RemoveEdge(newEdgeIterator);
            
            // Return error code
            return ADD_EDGE_ERROR;
        }
        
        // Add relationship attribute to the edge
        // If this fails, remove the ege and
        // return error
        IntAttribute * relationshipAttribute = (IntAttribute *)newEdge->AddAttribute("Relationship", "int");
        if(relationshipAttribute == NULL) {
            // Print error Message
            FamilyTreeErrorMsg(LOG_ERROR, "Relationship attribute %s for directed edge %s->%s was not added properly.",
            	from.c_str(),
				to.c_str()
			);

            // Remove the edge from the graph
            m_Graph.RemoveEdge(newEdgeIterator);
            
            // Return error code
            return ADD_EDGE_ERROR;
        }
        
        // Set the value of the edge attribute to the specified relationship
        relationshipAttribute->Value = relationship;
   
        // If we have reached here, everything is correct
        // Return SUCCESS
        return SUCCESS;
    }
    
    FamilyTreeOpResultCode FamilyTreeClass::constructTreeFromFile(string const & inputFileName) {
    
        // Try and open the input file
        ifstream infile(inputFileName.c_str());
  
        if(infile.is_open() == false) {
            // Print error Message
            FamilyTreeErrorMsg(LOG_ERROR, "Could not open the file: %s", inputFileName.c_str());

            // Close input file
            infile.close();

            // Return error code
            return INPUT_FILE_OPEN_ERROR;
        }
        
        // Read from input file line by line and construct the tree
        string currentLine;
        while(getline(infile, currentLine)) {
            // Skip comment lines or white space lines
        	if(currentLine[0] == '#' || currentLine[0] == '/' || currentLine == "") {
            	continue;
            }

        	// Split the current line into tokens based on the delimeter
            vector<string> currentLineTokens;
            boost::split(currentLineTokens, currentLine, boost::is_any_of(":"));
            
            // Create the member objects and add them as vertices to the graph
            if(currentLineTokens[0].compare("MEMBERS") == 0) {
            	FamilyTreeLogMsg(LOG_DEBUG, "Adding %d family members to the family tree", currentLineTokens.size() - 1);
                for(unsigned int i = 1; i < currentLineTokens.size(); i++) {
                    // Add the vertex to the graph
                    VertexIterator currentVertexIterator = m_Graph.AddVertex();
                    
                    // Get pointer to vertex within the iterator and make sure it is valid
                    Vertex * currentVertex = *currentVertexIterator;
                    if(currentVertex == NULL) {
                        // Print error Message
                        FamilyTreeErrorMsg(LOG_ERROR, "Failed to add directed vertex to graph");

                        // Remove the edge from the graph
                        m_Graph.RemoveVertex(currentVertex, true);

                        // Return error code
                        return ADD_VERTEX_ERROR;
                    }
                    
                    // Add a label to the Vertex
                    currentVertex->SetLabel(currentLineTokens[i], "Member_Name");

                    // Add a StringAttribute to the new member object
                    StringAttribute * memberName =
                            (StringAttribute *)currentVertex->AddAttribute("Member_FirstName", "string");
                    
                    // Set the name of the family member
                    memberName->Value = currentLineTokens[i];

                    FamilyTreeLogMsg(LOG_DEBUG, "Added family member %s to the family tree",
                    	currentVertex->GetLabel("Member_Name").c_str());
                }
            }
            else if (currentLineTokens[0].compare("PARENT") == 0) {
            	FamilyTreeLogMsg(LOG_DEBUG, "Adding the parent-child relationships to the family tree");
            	// Find the parent vertex
                string parentName = currentLineTokens[1];

                FamilyTreeLogMsg
				(
					LOG_DEBUG,
					"Adding the parent->child and child->parent relationships for parent %s to the family tree.",
					parentName.c_str()
                );

                // For each child, add a parent->child edge to the graph
                for(unsigned int i = 3; i < currentLineTokens.size(); i++) {
                    // Find the child vertex
                    string currentChildName = currentLineTokens[i];
                    
                    // Add the parent->child relationship to the graph
                    if(addRelationship(parentName, currentChildName, Parent_Child) != SUCCESS) {
                        // Log error message
                        FamilyTreeErrorMsg(
                        	LOG_ERROR,
							"Failed to add the parent->child relationship %s->%s to the family tree",
							parentName.c_str(),
							currentChildName.c_str()
                        );
                        
                        // Close input file
                        infile.close();

                        // return error
                        return TREE_CONSTRUCTION_ERROR;
                    }
                    else {
						FamilyTreeLogMsg(
							LOG_DEBUG,
							"Successfully added the parent->child relationship %s->%s to the family tree",
							parentName.c_str(),
							currentChildName.c_str()
						);
                    }

                    // Add the child->parent relationship to the graph
                    if(addRelationship(currentChildName, parentName, Child_Parent) != SUCCESS) {
						// Log error message
						FamilyTreeErrorMsg(
							LOG_ERROR,
							"Failed to add the child->parent relationship %s->%s to the family tree",
							currentChildName.c_str(),
							parentName.c_str()
						);
						// Close input file
						infile.close();

						// return error
						return TREE_CONSTRUCTION_ERROR;
					}
					else {
						FamilyTreeLogMsg(
							LOG_DEBUG,
							"Successfully added the child->parent relationship %s->%s to the family tree",
							currentChildName.c_str(),
							parentName.c_str()
						);
					}
                }
            }
            else if (currentLineTokens[0].compare("SIBLINGS") == 0) {
            	FamilyTreeLogMsg(LOG_DEBUG, "Adding the sibling relationships to the family tree");
            	// Loop through the sibling entries and add
            	// link them together.  Siblings should have
            	// directed edges to and from one another
                for(unsigned int i = 1; i < currentLineTokens.size(); i++) {
                	// Find the mainSibling vertex
                	string mainSiblingName = currentLineTokens[i];

                	for(unsigned int j = 1; j < currentLineTokens.size(); j++) {
                		// Do not add a relationship for sibling to itself
                		if(i == j) {
                			continue;
                		}

                		// Find the other sibling vertex
						string currentSiblingName = currentLineTokens[j];
						FamilyTreeLogMsg
						(
							LOG_DEBUG,
							"Adding the %s->%s sibling relationships to the family tree.",
							mainSiblingName.c_str(),
							currentSiblingName.c_str()
						);

						// Add the sibling->sibling relationship to the graph
						if(addRelationship(mainSiblingName, currentSiblingName, Sibling) != SUCCESS) {
							// Log error message
							FamilyTreeErrorMsg(
								LOG_ERROR,
								"Failed to add the %s->%s sibling relationship to the family tree",
								mainSiblingName.c_str(),
								currentSiblingName.c_str()
							);
							// Close input file
							infile.close();

							// return error
							return TREE_CONSTRUCTION_ERROR;
						}
						else {
							// Log error message
							FamilyTreeLogMsg(
								LOG_DEBUG,
								"Successfully added the %s->%s sibling to the family tree",
								mainSiblingName.c_str(),
								currentSiblingName.c_str()
							);
						}
                	}
                }
            }
            else {
                // Print error Message
                FamilyTreeErrorMsg(LOG_ERROR, "Input file formatted incorrectly");
                
                // Close input file
                infile.close();
                
                // Return false
                return INPUT_FILE_FORMAT_ERROR;
            }
        }

        // Close input file
		infile.close();

        return SUCCESS;
    }
    
} /* namespace FamilyTree */
