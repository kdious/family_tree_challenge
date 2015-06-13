/* 
 * File:   FamilyTree.cpp
 * Author: builduser
 * 
 * Created on June 10, 2015, 12:45 PM
 */

#include <fstream>
#include <boost/algorithm/string.hpp>

#include "FamilyTreeClass.h"

namespace FamilyTree {
    
    // Default constructor
    FamilyTreeClass::FamilyTreeClass() {

    }

    // Copy constructor
    FamilyTreeClass::FamilyTreeClass(const FamilyTreeClass& orig) {
    }
    
    // Constructor
    FamilyTreeClass::FamilyTreeClass(string inputFileName) {
        // TODO
    }

    // Destructor
    FamilyTreeClass::~FamilyTreeClass() {
    }

    FamilyMemberClass * FamilyTreeClass::findFamilyMember(string const & memberName) {

        FamilyMemberClass * pFamilyMember = NULL;

        for(VertexIterator v = m_Graph.BeginVertices(); v != m_Graph.EndVertices(); v++) {
            if((*v)->GetLabel("Member_Name").compare(memberName) == 0) {
                pFamilyMember = (FamilyMemberClass *)(*v);
                break;
            }
        }

        return pFamilyMember;
    }

    FamilyTreeOpResultCode FamilyTreeClass::initialize(string inputFileName) {
        return constructTreeFromFile(inputFileName);
    }

    FamilyTreeOpResultCode FamilyTreeClass::countSiblings(string memberName, uint32_t & count) {

    	// Initialize count variable
    	count = 0;

    	// Search for the FamilyMemberClass object in the tree
    	// with the name memberName
    	FamilyMemberClass * pFamilyMember = findFamilyMember(memberName);

    	// If the family member is not present, return error
    	if(pFamilyMember == NULL) {
    		return FAMILY_MEMBER_NOT_FOUND;
    	}

    	// Set the count variable
    	count = pFamilyMember->getSiblingCount();

    	// Return success
        return SUCCESS;
    }

    // Add a relationship to the Family Tree
    FamilyTreeOpResultCode FamilyTreeClass::addRelationship
    (
        FamilyMemberClass const * from, 
        FamilyMemberClass const * to, 
        FamilyMemberClass::relationship_t relationship
    ) {
        if(from == NULL || to == NULL) {
            // Log error
            cout << "INVALID_ARG: One or both of the family member pointers are NULL" << endl;
            
            // Return error code
            return INVALID_ARG;
        }
        
        // Create new arc
        EdgeIterator newEdgeIterator = m_Graph.AddArc((Vertex *)from, (Vertex *)to);
        
        // Get pointer to edge and make sure it is valid
        Edge * newEdge = *newEdgeIterator;
        if(newEdge == NULL) {
            // Print error Message
            cout << "Failed to add directed edge to graph" << endl;

            // Remove the edge from the graph
            m_Graph.RemoveEdge(newEdgeIterator);
            
            // Return error code
            return ADD_EDGE_ERROR;
        }
        
        if(newEdge->IsDirected() == false) {
            // Print error Message
            cout << "Edge not created properly" << endl;

            // Remove the edge from the graph
            m_Graph.RemoveEdge(newEdgeIterator);
            
            // Return error code
            return ADD_EDGE_ERROR;
        }
        
        // Add relationship attribute to the edge
        IntAttribute * relationshipAttribute = (IntAttribute *)newEdge->AddAttribute("Relationship", "int");
        if(relationshipAttribute == NULL) {
            // Print error Message
            cout << "Edge attribute not added properly" << endl;

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
    
    FamilyTreeOpResultCode FamilyTreeClass::constructTreeFromFile(string fileName) {
    
        // Try and open the input file
        ifstream infile(fileName.c_str());
  
        if(infile.is_open() == false) {
            // Print error Message
            cout << "Could not open the file: " << fileName << endl;

            // Close input file
            infile.close();

            // Return error code
            return INPUT_FILE_OPEN_ERROR;
        }
        
        // Read form input file line by line and construct the tree
        string currentLine;
        while(getline(infile, currentLine)) {
            
            // Split the current line into tokens based on the delimeter
            vector<string> currentLineTokens;
            boost::split(currentLineTokens, currentLine, boost::is_any_of(":"));
            
            // Create the member objects and add them as vertices to the graph
            if(currentLineTokens[0].compare("MEMBERS") == 0) {
            	cout << "Adding " << currentLineTokens.size() - 1 << " family members to the family tree" << endl;
                for(unsigned int i = 1; i < currentLineTokens.size(); i++) {
                    // Add the vertex to the graph
                    VertexIterator currentVertexIterator = m_Graph.AddVertex();
                    
                    // Get pointer to vertex within the iterator and make sure it is valid
                    Vertex * currentVertex = *currentVertexIterator;
                    if(currentVertex == NULL) {
                        // Print error Message
                        cout << "Failed to add directed vertex to graph" << endl;

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

                    cout << "Added family member " << currentVertex->GetLabel("Member_Name") << " to the family tree" << endl;
                }
            }
            else if (currentLineTokens[0].compare("CHILDREN") == 0) {
            	cout << "Adding the parent->children relationships to the family tree" << endl;
            	// Find the parent vertex
                string parentName = currentLineTokens[1];
                FamilyMemberClass * pParent = findFamilyMember(parentName);
                if(pParent == NULL) {
                    // Log error message
                    cout << "Failed to find family member " << parentName << " in the graph" << endl;
                    
                    // Close input file
                    infile.close();
                    
                    // return error
                    return TREE_CONSTRUCTION_ERROR;
                }
                
                cout << "Adding the parent->child relationships for parent " << pParent->GetLabel("Member_Name") << " to the family tree" << endl;

                // For each child, add a parent->child edge to the graph
                for(unsigned int i = 2; i < currentLineTokens.size(); i++) {
                    // Find the child vertex
                    string currentChildName = currentLineTokens[i];
                    FamilyMemberClass * pCurrentChild = findFamilyMember(currentChildName);
                    if(pCurrentChild == NULL) {
                        // Log error message
                        cout << "Failed to find family member " << currentChildName << " to the tree" << endl;
                        
                        // Close input file
                        infile.close();

                        // return error
                        return TREE_CONSTRUCTION_ERROR;
                    }
                    
                    // Add the parent-child relationship to the graph
                    if(addRelationship(pParent, pCurrentChild, FamilyMemberClass::Child) != SUCCESS) {
                        // Log error message
                        cout << "Failed to add the parent->child relationship " << parentName
                             << "->" << currentChildName << 
                                " relationship to the tree" << endl;
                        
                        // Close input file
                        infile.close();

                        // return error
                        return TREE_CONSTRUCTION_ERROR;
                    }

                    cout << "Successfully Added the parent->child relationship " << parentName
						 << "->" << currentChildName <<
							" relationship to the family tree" << endl;
                }
            }
            else if (currentLineTokens[0].compare("SIBLINGS") == 0) {
            	cout << "Adding the sibling relationships to the family tree" << endl;

                for(unsigned int i = 1; i < currentLineTokens.size(); i++) {
                	// Find the mainSibling vertex
                	string mainSiblingName = currentLineTokens[i];
					FamilyMemberClass * pMainSibling = findFamilyMember(mainSiblingName);
					if(pMainSibling == NULL) {
						// Log error message
						cout << "Failed to find family member " << mainSiblingName << " in the tree" << endl;

						// Close input file
						infile.close();

						// return error
						return TREE_CONSTRUCTION_ERROR;
					}

                	for(unsigned int j = 1; j < currentLineTokens.size(); j++) {
                		if(i == j) {
                			continue;
                		}

                		// Find the other sibling vertex
						string currentSiblingName = currentLineTokens[j];
						FamilyMemberClass * pCurrentSibling = findFamilyMember(currentSiblingName);
						if(pCurrentSibling == NULL) {
							// Log error message
							cout << "Failed to find family member " << currentSiblingName << " in the tree" << endl;

							// Close input file
							infile.close();

							// return error
							return TREE_CONSTRUCTION_ERROR;
						}

						cout << "Adding the " << pMainSibling->GetLabel("Member_Name")
						     << "->" << pCurrentSibling->GetLabel("Member_Name")
							 << " sibling relationships to the family tree" << endl;

						// Add the sibling->sibling relationship to the graph
						if(addRelationship(pMainSibling, pCurrentSibling, FamilyMemberClass::Sibling) != SUCCESS) {
							// Log error message
							cout << "Failed to add the " << mainSiblingName
								 << "->" << currentSiblingName
								 << " sibling relationship to the family tree" << endl;

							// Close input file
							infile.close();

							// return error
							return TREE_CONSTRUCTION_ERROR;
						}

						// Log error message
						cout << "Successfully added the mainSibling->sibling relationship " << mainSiblingName
							 << "->" << currentSiblingName <<
								" to the family tree" << endl;
                	}
                }
            }
            else {
                // Print error Message
                cout << "Input file formatted incorrectly" << endl;
                
                // Close input file
                infile.close();
                
                // Return false
                return INPUT_FILE_FORMAT_ERROR;
            }
        }

        return SUCCESS;
    }
    
} /* namespace FamilyTree */
