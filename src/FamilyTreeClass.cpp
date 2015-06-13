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

    // Add a relationship to the Family Tree
    FamilyTreeOpResultCode FamilyTreeClass::addRelationship
    (
        FamilyMemberClass const * from, 
        FamilyMemberClass const * to, 
        FamilyMemberClass::relationship_t relationship
    ) {
        if(from == NULL || to == NULL) {
            // Log error
            cout << "INVALID_ARG: One or both of the family  member pointers are NULL" << endl;
            
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
        IntAttribute * relationshipAttribute = (IntAttribute *)newEdge->AddAttribute("Relationship", "IntAttribute");
        if(relationshipAttribute == NULL) {
            // Print error Message
            cout << "Edge relationship not added properly" << endl;

            // Remove the edge from the graph
            m_Graph.RemoveEdge(newEdgeIterator);
            
            // Return error code
            return ADD_EDGE_ERROR;
        }
        
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
            cout << "Input file formatted incorrectly" << endl;

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
            if(currentLineTokens[0].compare("MEMBERS")) {
                for(int i = 1; i < currentLineTokens.size(); i++) {
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
                    
                    // Add a StringAttribute to the new member object
                    StringAttribute * memberName = 
                            (StringAttribute *)currentVertex->AddAttribute("Member_Name", "StringAttribute");
                    
                    // Set the name of the family member
                    memberName->Value = currentLineTokens[i];              
                }
            }
            else if (currentLineTokens[0].compare("CHILDREN")) {
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
                
                // For each child, add a parent->child edge to the graph
                for(int i = 2; i < currentLineTokens.size(); i++) {
                    // Find the child vertex
                    string currentChildName = currentLineTokens[i];
                    FamilyMemberClass * pCurrentChild = findFamilyMember(currentChildName);
                    if(pCurrentChild == NULL) {
                        // Log error message
                        cout << "Failed to find family member " << currentChildName << " in the graph" << endl;
                        
                        // Close input file
                        infile.close();

                        // return error
                        return TREE_CONSTRUCTION_ERROR;
                    }
                    
                    // Add the parent-child relationship to the graph
                    if(addRelationship(pParent, pCurrentChild, FamilyMemberClass::Child) != SUCCESS) {
                        // Log error message
                        // Log error message
                        cout << "Failed to add " << parentName 
                             << "->" << currentChildName << 
                                " relationship in the graph" << endl;
                        
                        // Close input file
                        infile.close();

                        // return error
                        return TREE_CONSTRUCTION_ERROR;
                    }
                }
            }
            else if (currentLineTokens[0].compare("SIBLINGS")) {
                // Find the parent vertex
                string mainSiblingName = currentLineTokens[1];
                FamilyMemberClass * pMainSibling = findFamilyMember(mainSiblingName);
                if(pMainSibling == NULL) {
                    // Log error message
                    cout << "Failed to find family member " << mainSiblingName << " in the graph" << endl;
                    
                    // Close input file
                    infile.close();
                    
                    // return error
                    return TREE_CONSTRUCTION_ERROR;
                }
                
                // For each child, add a sibling->sibling edge to the graph
                for(int i = 2; i < currentLineTokens.size(); i++) {
                    // Find the sibling vertex
                    string currentSiblingName = currentLineTokens[i];
                    FamilyMemberClass * pCurrentSibling = findFamilyMember(currentSiblingName);
                    if(pCurrentSibling == NULL) {
                        // Log error message
                        cout << "Failed to find family member " << currentSiblingName << " in the graph" << endl;
                        
                        // Close input file
                        infile.close();

                        // return error
                        return TREE_CONSTRUCTION_ERROR;
                    }
                    
                    // Add the sibling->sibling relationship to the graph
                    if(addRelationship(pMainSibling, pCurrentSibling, FamilyMemberClass::Sibling) != SUCCESS) {
                        // Log error message
                        cout << "Failed to add " << mainSiblingName 
                             << "->" << currentSiblingName << 
                                " relationship in the graph" << endl;
                        
                        // Close input file
                        infile.close();

                        // return error
                        return TREE_CONSTRUCTION_ERROR;
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
    }
    
    FamilyMemberClass * FamilyTreeClass::findFamilyMember(string const & memberName) {
        
        FamilyMemberClass * pFamilyMember = NULL;
        
        for(VertexIterator v = m_Graph.BeginVertices(); v != m_Graph.EndVertices(); v++) {
            if((*v)->GetLabel().compare(memberName) == 0) {
                pFamilyMember = (FamilyMemberClass *)(*v);
                break;
            }
        }
        
        return pFamilyMember;
    }
    
    FamilyTreeOpResultCode FamilyTreeClass::initialize(string inputFileName) {
        return constructTreeFromFile(inputFileName);
    }

} /* namespace FamilyTree */