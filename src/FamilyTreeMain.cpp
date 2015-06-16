/**
 *  @file    FamilyTreeMain.cpp
 *  @author  Kevin Dious
 *  @date    6/15/2015
 *
 *  @brief Program that interacts with a family tree.
 *
 *  @section DESCRIPTION
 *
 *  This is a program that reads a a family tree structure
 *  from an input file, constructs the tree, and preforms
 *  query operations on the tree specified by the user.
 *
 *  The program provides a command line interface that allows
 *  the user to interact with the tree.
 *
 */

#include <cstdlib>
#include <limits>

#include "FamilyTreeClass.h"
#include "FamilyTreeOpResultCode.h"

using namespace std;
using namespace FamilyTree;

// Global variable to hold the family tree
FamilyTreeClass g_FamilyTree;

void printFamilyMembersList() {
	vector<string> familyMemberNameList;
	if(g_FamilyTree.getFamilyMembersNameList(familyMemberNameList) != SUCCESS) {
		cout << "Unable to retrieve the list of family member names" << endl;
		return;
	}

	cout << "The list of family members are: " << endl;
	for(unsigned int i = 0; i < familyMemberNameList.size(); i++) {
		cout << i + 1 << ".\t" << familyMemberNameList[i] << endl;
	}
}

void findGrandparentForSpecifiedMember() {
	// Get the family member name from the user
	cout << "Please Type the name of the family member: ";

	string familyMemberName;
	cin >> familyMemberName;

	// Ensure that the user inputs something
	while(familyMemberName.empty()) {
		cout << "You did not input a name.  Please input the name of a family member: ";
		cin >> familyMemberName;
	}

	// Retrieve the grandparent name list
	// If there is an error, log the error and return
	vector<string> grandparentNameList;
	if(g_FamilyTree.getGrandparentNameList(familyMemberName, grandparentNameList) != SUCCESS) {
		cout << "Unable to retrieve grandparent info for " << familyMemberName << endl;
		return;
	}

	// If grandparentNameList is empty, then the
	// specified family member has no grandparents.
	// Otherwise, print the list of grandparents
	//
	// Note: In the given family tree specified in the problem,
	// there should be at most one grandparent.  However, the
	// family tree implementation can handle multiple
	// grandparents for a family member.
	if(grandparentNameList.empty()) {
		cout << "Family member " << familyMemberName
			 << "does not have any grandparents in the family tree" << endl;
	}
	else {
		cout << "The grandparent(s) for " << familyMemberName << " in the family tree is/are:" << endl;
		for(vector<string>::iterator it = grandparentNameList.begin(); it != grandparentNameList.end(); ++it) {
			cout << *it << endl;
		}
	}
}

void printMembersWithSpecificSiblingCount() {
	// Get the family member name from the user
	cout << "Please type the sibling count: ";

	uint32_t siblingCount;
	while(!(cin >> siblingCount) || (siblingCount == UINT_MAX)) {
		cout << "You did not input a valid value.  Please input a positive number: ";
		// Clear the cin error flag and reset the buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cout << endl;

	// Retrieve the list of family
	// member with no siblings.
	// If there is an error, log the error and return
	vector<string> membersWithSiblignCountSiblingsList;
	if(g_FamilyTree.getMembersWithSiblingCount(siblingCount, membersWithSiblignCountSiblingsList) != SUCCESS) {
		cout << "Unable to retrieve sibling count info" << endl;
		return;
	}

	// If membersWithSiblignCountSiblingsList is empty, then
	// there are no family members with the specified
	// number of siblings.  Otherwise, print the list of
	// family members with the specified number of siblings.
	if(membersWithSiblignCountSiblingsList.empty()) {
		cout << "There are no family members that have " << siblingCount << " siblings" << endl;
	}
	else {
		cout << "The family member(s) with " << siblingCount << " siblings in the family tree is/are:" << endl;
		for(vector<string>::iterator it = membersWithSiblignCountSiblingsList.begin();
				it != membersWithSiblignCountSiblingsList.end(); ++it) {
			cout << *it << endl;
		}
	}
}

void printMembersWithSpecificChildCount() {
	// Get the family member name from the user
	cout << "Please type the child count: ";

	uint32_t childCount;
	while(!(cin >> childCount) || (childCount == UINT_MAX)) {
		cout << "You did not input a valid value.  Please input a positive number: ";
		// Clear the cin error flag and reset the buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cout << endl;

	// Retrieve the list of family
	// members with the specified child count.
	// If there is an error, log the error and return
	vector<string> membersWithChildCountSiblingsList;
	if(g_FamilyTree.getMembersWithChildCount(childCount, membersWithChildCountSiblingsList) != SUCCESS) {
		cout << "Unable to retrieve child count info" << endl;
		return;
	}

	// If membersWithSiblignCountSiblingsList is empty, then
	// there are no family members with the specified
	// number of siblings.  Otherwise, print the list of
	// family members with the specified number of siblings.
	if(membersWithChildCountSiblingsList.empty()) {
		cout << "There are no family members that have " << childCount << " children" << endl;
	}
	else {
		cout << "The family member(s) with " << childCount << " children in the family tree is/are:" << endl;
		for(vector<string>::iterator it = membersWithChildCountSiblingsList.begin();
				it != membersWithChildCountSiblingsList.end(); ++it) {
			cout << *it << endl;
		}
	}
}

void printMemberWithMostGrandchildren() {
	vector<string> mostGrandChildrenList;
	if(g_FamilyTree.getMembersWithMostGrandchildren(mostGrandChildrenList) != SUCCESS) {
		cout << "Unable to determine what family member has the most grandchildren" << endl;
		return;
	}

	if(mostGrandChildrenList.size() == 0) {
		cout << "No family member has any grandchildren" << endl;
		return;
	}
	else {
		cout << "The family member(s) with the most grandchildren is/are: " << endl;
		for(vector<string>::iterator it = mostGrandChildrenList.begin();
				it != mostGrandChildrenList.end(); ++it) {
			cout << *it << endl;
		}
	}
}


int main(int argc, char** argv) {
    
    cout << "Welcome to the family tree program" << endl;

	if(argc < 2) {
		cout << "Log file not passed in as an argument" << endl;
		exit(-1);
	}

	string inputFileName(argv[1]);

	// Initialize the tree.  If the tree cannot
	// be initialized, exit the program.
	if(g_FamilyTree.initialize(inputFileName) != SUCCESS) {
		cout << "Unable to initialize family tree from file name: " << inputFileName << endl;
		cout << "Program exiting" << endl;
		exit(-2);
	}

	// While loop for the main thread.  Allow the user to select
	// an option.  If the option is invalid, prompt the user.
	while(true) {
		cout << endl;
		cout << "Please select from the following options:" << endl;
		cout << "1. Print the list of family members" << endl;
		cout << "2. Find the grandparent of a specific family member" << endl;
		cout << "3. Print the names of family members with a specified number of siblings" << endl;
		cout << "4. Print the names of family members with a specified number of children" << endl;
		cout << "5. Print the name of the person with largest number of grand children" << endl;
		cout << "6. Exit program" << endl << endl;
		cout << "Selection: ";

		int menuSelection;
		while(!(cin >> menuSelection) || (menuSelection < 1) || (menuSelection > 6)) {
			cout << "You did not input a valid value.  Please input a selection between 1-5: ";
			// Clear the cin error flag and reset the buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << endl;

		switch(menuSelection) {
		case 1:
			printFamilyMembersList();
			break;
		case 2:
			findGrandparentForSpecifiedMember();
			break;
		case 3:
			printMembersWithSpecificSiblingCount();
			break;
		case 4:
			printMembersWithSpecificChildCount();
			break;
		case 5:
			printMemberWithMostGrandchildren();
			break;
		case 6:
			exit(0);
		default:
			cout << "Invalid option.  Please select an option between 1-5:" << endl;
		}

		cout << endl;
	}

    return 0;
}




  

