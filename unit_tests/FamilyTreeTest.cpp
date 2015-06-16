/**
 *  @file    FamilyTreeTest.cpp
 *  @author  Kevin Dious
 *  @date    6/15/2015
 *
 *  @brief Unit tests to test the FamilyTreeClass class.
 *
 *  @section DESCRIPTION
 *
 *  This is a program that runs a variety of units tests to
 *  test the FamilyTreeClass.
 *
 *  The unit tests call the public member methods of the
 *  FamilyTreeClass.
 *
 */

//#include <gtest/gtest.h>		// gtest libs installed on machine
#include "libs/gtest/gtest.h"	// local gtest libs

#include "FamilyTreeClass.h"
#include "FamilyTreeOpResultCode.h"

using namespace FamilyTree;

string g_validInputFilePath;

class FamilyTreeTest : public testing::Test {
protected:
};

// Test the FamilyTreeClass::initialize method
TEST_F(FamilyTreeTest, initialize) {

	FamilyTreeClass testTree;

    EXPECT_EQ(INPUT_FILE_OPEN_ERROR, testTree.initialize("invalidFileName.txt"));

    EXPECT_EQ(SUCCESS, testTree.initialize(g_validInputFilePath));
}

// Test the FamilyTreeClass::getSiblingNameList method
TEST_F(FamilyTreeTest, getSiblingNameList) {
    FamilyTreeClass testTree;

    // Initialize the tree
    testTree.initialize(g_validInputFilePath);

    vector<string> nameList;
    vector<string>::iterator nameIterator;

    // INVALID FAMILY MEMBER
    EXPECT_EQ(FAMILY_MEMBER_NOT_FOUND, testTree.getSiblingNameList("Invalid_Family_Member_Name", nameList));

    // NO SIBLINGS

    // Nancy
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Nancy", nameList));
	EXPECT_EQ(0, nameList.size());

	// Kevin
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Kevin", nameList));
	EXPECT_EQ(0, nameList.size());

	// Mary
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Mary", nameList));
	EXPECT_EQ(0, nameList.size());

    // ONE SIBLING

	// Catherine
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Catherine", nameList));
	EXPECT_EQ(1, nameList.size());
    nameIterator = find(nameList.begin(), nameList.end(), "Joseph");
    EXPECT_EQ(true, nameIterator != nameList.end());

	// Joseph
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Joseph", nameList));
	EXPECT_EQ(1, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Catherine");
	EXPECT_EQ(true, nameIterator != nameList.end());


	// Patrick
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Patrick", nameList));
	EXPECT_EQ(1, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Robert");
	EXPECT_EQ(true, nameIterator != nameList.end());

	// Robert
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Robert", nameList));
	EXPECT_EQ(1, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Patrick");
	EXPECT_EQ(true, nameIterator != nameList.end());


	// TWO SIBLINGS

	// Carl
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Carl", nameList));
	EXPECT_EQ(2, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Jill");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Adam");
	EXPECT_EQ(true, nameIterator != nameList.end());

    // Jill
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Jill", nameList));
	EXPECT_EQ(2, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Carl");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Adam");
	EXPECT_EQ(true, nameIterator != nameList.end());

	// Adam
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Adam", nameList));
	EXPECT_EQ(2, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Jill");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Carl");
	EXPECT_EQ(true, nameIterator != nameList.end());


	// THREE SIBLINGS

	// Aaron
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Aaron", nameList));
	EXPECT_EQ(3, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "James");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "George");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Samuel");
	EXPECT_EQ(true, nameIterator != nameList.end());

	// James
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("James", nameList));
	EXPECT_EQ(3, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Aaron");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "George");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Samuel");
	EXPECT_EQ(true, nameIterator != nameList.end());

	// George
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("George", nameList));
	EXPECT_EQ(3, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Aaron");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "James");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Samuel");
	EXPECT_EQ(true, nameIterator != nameList.end());

	// Samuel
	EXPECT_EQ(SUCCESS, testTree.getSiblingNameList("Samuel", nameList));
	EXPECT_EQ(3, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Aaron");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "George");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "James");
	EXPECT_EQ(true, nameIterator != nameList.end());



}

// Test the FamilyTreeClass::getChildrenNameList method
TEST_F(FamilyTreeTest, getChildrenNameList) {

	FamilyTreeClass testTree;

    // Initialize the tree
    testTree.initialize(g_validInputFilePath);

    vector<string> nameList;
    vector<string>::iterator nameIterator;

    // INVALID FAMILY MEMBER
    EXPECT_EQ(FAMILY_MEMBER_NOT_FOUND, testTree.getChildrenNameList("Invalid_Family_Member_Name", nameList));

    // NO CHILDREN

    // Adam
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("Adam", nameList));
	EXPECT_EQ(0, nameList.size());

	// Catherine
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("Catherine", nameList));
	EXPECT_EQ(0, nameList.size());

	// Joseph
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("Joseph", nameList));
	EXPECT_EQ(0, nameList.size());

	// Mary
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("Mary", nameList));
	EXPECT_EQ(0, nameList.size());

	// Patrick
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("Patrick", nameList));
	EXPECT_EQ(0, nameList.size());

	// Robert
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("Robert", nameList));
	EXPECT_EQ(0, nameList.size());

    // ONE CHILD

	// Jill
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("Jill", nameList));
	EXPECT_EQ(1, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Kevin");
	EXPECT_EQ(true, nameIterator != nameList.end());

	// James
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("James", nameList));
	EXPECT_EQ(1, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Mary");
	EXPECT_EQ(true, nameIterator != nameList.end());

	// TWO CHILDREN

	// Carl
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("Carl", nameList));
	EXPECT_EQ(2, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Catherine");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Joseph");
	EXPECT_EQ(true, nameIterator != nameList.end());

    // George
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("George", nameList));
	EXPECT_EQ(2, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Robert");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Patrick");
	EXPECT_EQ(true, nameIterator != nameList.end());

	// THREE CHILDREN

	// Nancy
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("Nancy", nameList));
	EXPECT_EQ(3, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Carl");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Jill");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Adam");
	EXPECT_EQ(true, nameIterator != nameList.end());

	// FOUR CHILDREN

	// Kevin
	EXPECT_EQ(SUCCESS, testTree.getChildrenNameList("Kevin", nameList));
	EXPECT_EQ(4, nameList.size());
	nameIterator = find(nameList.begin(), nameList.end(), "Aaron");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "James");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "George");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Samuel");
	EXPECT_EQ(true, nameIterator != nameList.end());

}

// Test the FamilyTreeClass::getGrandparentNameList method
TEST_F(FamilyTreeTest, getGrandparentNameList) {

	FamilyTreeClass testTree;

    // Initialize the tree
    testTree.initialize(g_validInputFilePath);

    vector<string> nameList;

    // INVALID FAMILY MEMBER
	EXPECT_EQ(FAMILY_MEMBER_NOT_FOUND, testTree.getGrandparentNameList("Invalid_Family_Member_Name", nameList));

    // NO GRANDPARENTS

    // Nancy
    EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Nancy", nameList));
    EXPECT_EQ(0, nameList.size());

    // Jill
    EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Jill", nameList));
    EXPECT_EQ(0, nameList.size());

    // Carl
    EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Carl", nameList));
    EXPECT_EQ(0, nameList.size());

    // Adam
    EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Adam", nameList));
    EXPECT_EQ(0, nameList.size());

    // ONE GRANDPARENT

    // A. Grandparent: Nancy

    // Nancy
	EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Catherine", nameList));
	EXPECT_EQ(1, nameList.size());
	EXPECT_EQ("Nancy", nameList[0]);

	// Joseph
	EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Joseph", nameList));
	EXPECT_EQ(1, nameList.size());
	EXPECT_EQ("Nancy", nameList[0]);

	// Kevin
	EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Kevin", nameList));
	EXPECT_EQ(1, nameList.size());
	EXPECT_EQ("Nancy", nameList[0]);

	// B. Grandparent: Jill
	// Aaron
	EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Aaron", nameList));
	EXPECT_EQ(1, nameList.size());
	EXPECT_EQ("Jill", nameList[0]);

	// James
	EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("James", nameList));
	EXPECT_EQ(1, nameList.size());
	EXPECT_EQ("Jill", nameList[0]);

	// George
	EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("George", nameList));
	EXPECT_EQ(1, nameList.size());
	EXPECT_EQ("Jill", nameList[0]);

	// Samuel
	EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Samuel", nameList));
	EXPECT_EQ(1, nameList.size());
	EXPECT_EQ("Jill", nameList[0]);

	// C. Grandparent: Kevin

	// Mary
	EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Mary", nameList));
	EXPECT_EQ(1, nameList.size());
	EXPECT_EQ("Kevin", nameList[0]);

	// Mary
	EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Mary", nameList));
	EXPECT_EQ(1, nameList.size());
	EXPECT_EQ("Kevin", nameList[0]);

	// Robert
	EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Robert", nameList));
	EXPECT_EQ(1, nameList.size());
	EXPECT_EQ("Kevin", nameList[0]);

	// Patrick
	EXPECT_EQ(SUCCESS, testTree.getGrandparentNameList("Patrick", nameList));
	EXPECT_EQ(1, nameList.size());
	EXPECT_EQ("Kevin", nameList[0]);
}

// Test the FamilyTreeClass::getFamilyMembersNameList method
TEST_F(FamilyTreeTest, getFamilyMembersNameList) {

	FamilyTreeClass testTree;

    // Initialize the tree
    testTree.initialize(g_validInputFilePath);

    vector<string> nameList;
    vector<string>::iterator nameIterator;

    // Make sure the correct number is returned
    EXPECT_EQ(SUCCESS, testTree.getFamilyMembersNameList(nameList));
    EXPECT_EQ(14, nameList.size());

    // Make sure the name returned are correct.
    nameIterator = find(nameList.begin(), nameList.end(), "Nancy");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "Carl");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "Jill");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "Adam");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "Joseph");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "Catherine");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "Kevin");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "Aaron");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "James");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "George");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "Samuel");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "Mary");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "Patrick");
    EXPECT_EQ(true, nameIterator != nameList.end());

    nameIterator = find(nameList.begin(), nameList.end(), "Robert");
    EXPECT_EQ(true, nameIterator != nameList.end());
}


// Test the FamilyTreeClass::getMembersWithChildCount method
TEST_F(FamilyTreeTest, getMembersWithChildCount) {

	FamilyTreeClass testTree;

    // Initialize the tree
    testTree.initialize(g_validInputFilePath);

    vector<string> nameList;
    vector<string>::iterator nameIterator;

    // NO CHILDREN

    EXPECT_EQ(SUCCESS, testTree.getMembersWithChildCount(0, nameList));
    EXPECT_EQ(8, nameList.size());
    nameIterator = find(nameList.begin(), nameList.end(), "Adam");
    EXPECT_EQ(true, nameIterator != nameList.end());
    nameIterator = find(nameList.begin(), nameList.end(), "Catherine");
    EXPECT_EQ(true, nameIterator != nameList.end());
    nameIterator = find(nameList.begin(), nameList.end(), "Joseph");
    EXPECT_EQ(true, nameIterator != nameList.end());
    nameIterator = find(nameList.begin(), nameList.end(), "Aaron");
    EXPECT_EQ(true, nameIterator != nameList.end());
    nameIterator = find(nameList.begin(), nameList.end(), "Samuel");
    EXPECT_EQ(true, nameIterator != nameList.end());
    nameIterator = find(nameList.begin(), nameList.end(), "Mary");
    EXPECT_EQ(true, nameIterator != nameList.end());
    nameIterator = find(nameList.begin(), nameList.end(), "Patrick");
    EXPECT_EQ(true, nameIterator != nameList.end());
    nameIterator = find(nameList.begin(), nameList.end(), "Robert");
    EXPECT_EQ(true, nameIterator != nameList.end());

    // ONE CHILD

    EXPECT_EQ(SUCCESS, testTree.getMembersWithChildCount(1, nameList));
    EXPECT_EQ(2, nameList.size());
    nameIterator = find(nameList.begin(), nameList.end(), "Jill");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "James");
	EXPECT_EQ(true, nameIterator != nameList.end());

    // TWO CHILDREN

    EXPECT_EQ(SUCCESS, testTree.getMembersWithChildCount(2, nameList));
    EXPECT_EQ(2, nameList.size());
    nameIterator = find(nameList.begin(), nameList.end(), "Carl");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "George");
	EXPECT_EQ(true, nameIterator != nameList.end());

    // THREE CHILDREN

    EXPECT_EQ(SUCCESS, testTree.getMembersWithChildCount(3, nameList));
    EXPECT_EQ(1, nameList.size());
    nameIterator = find(nameList.begin(), nameList.end(), "Nancy");
	EXPECT_EQ(true, nameIterator != nameList.end());

    // FOUR CHILDREN

    EXPECT_EQ(SUCCESS, testTree.getMembersWithChildCount(4, nameList));
    EXPECT_EQ(1, nameList.size());
    nameIterator = find(nameList.begin(), nameList.end(), "Kevin");
	EXPECT_EQ(true, nameIterator != nameList.end());

    // FIVE CHILDREN

    EXPECT_EQ(SUCCESS, testTree.getMembersWithChildCount(5, nameList));
    EXPECT_EQ(0, nameList.size());
}

// Test the FamilyTreeClass::getMembersWithSiblingCount method
TEST_F(FamilyTreeTest, getMembersWithSiblingCount) {

	FamilyTreeClass testTree;

    // Initialize the tree
    testTree.initialize(g_validInputFilePath);

    vector<string> nameList;
    vector<string>::iterator nameIterator;

    // NO SIBLINGS

    EXPECT_EQ(SUCCESS, testTree.getMembersWithSiblingCount(0, nameList));
    EXPECT_EQ(3, nameList.size());
    nameIterator = find(nameList.begin(), nameList.end(), "Nancy");
    EXPECT_EQ(true, nameIterator != nameList.end());
    nameIterator = find(nameList.begin(), nameList.end(), "Kevin");
    EXPECT_EQ(true, nameIterator != nameList.end());
    nameIterator = find(nameList.begin(), nameList.end(), "Mary");

    // ONE SIBLING

    EXPECT_EQ(SUCCESS, testTree.getMembersWithSiblingCount(1, nameList));
    EXPECT_EQ(4, nameList.size());
    nameIterator = find(nameList.begin(), nameList.end(), "Catherine");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Joseph");
	EXPECT_EQ(true, nameIterator != nameList.end());
    nameIterator = find(nameList.begin(), nameList.end(), "Patrick");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Robert");
	EXPECT_EQ(true, nameIterator != nameList.end());


    // TWO SIBLINGS

    EXPECT_EQ(SUCCESS, testTree.getMembersWithSiblingCount(2, nameList));
    EXPECT_EQ(3, nameList.size());
    nameIterator = find(nameList.begin(), nameList.end(), "Carl");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Jill");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Adam");
	EXPECT_EQ(true, nameIterator != nameList.end());


    // THREE SIBLINGS

    EXPECT_EQ(SUCCESS, testTree.getMembersWithSiblingCount(3, nameList));
    EXPECT_EQ(4, nameList.size());
    nameIterator = find(nameList.begin(), nameList.end(), "Aaron");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "James");
	EXPECT_EQ(true, nameIterator != nameList.end());
    nameIterator = find(nameList.begin(), nameList.end(), "George");
	EXPECT_EQ(true, nameIterator != nameList.end());
	nameIterator = find(nameList.begin(), nameList.end(), "Samuel");
	EXPECT_EQ(true, nameIterator != nameList.end());

    // FOUR SIBLINGS

    EXPECT_EQ(SUCCESS, testTree.getMembersWithSiblingCount(5, nameList));
    EXPECT_EQ(0, nameList.size());
}

// Test the FamilyTreeClass::getMembersWithMostGrandchildren method
TEST_F(FamilyTreeTest, getMembersWithMostGrandchildren) {
    FamilyTreeClass testTree;

    // Initialize the tree
    testTree.initialize(g_validInputFilePath);

    vector<string> nameList;
    vector<string>::iterator nameIterator;

    // Jill has the most grand children for sample_family_tree_input_file.txt

    EXPECT_EQ(SUCCESS, testTree.getMembersWithMostGrandchildren(nameList));
    EXPECT_EQ(1, nameList.size());
    EXPECT_EQ("Jill", nameList[0]);
}

// Main method for running all of the tests

int main(int argc, char **argv) {
	printf("Running main() from FamilyTreeTest.cpp\n");
	testing::InitGoogleTest(&argc, argv);
/*
	// Get the family member name from the user
	cout << "Please type the full file path of the input file (ex: /home/builduser/log_file.txt)" << endl;
	cout << "File path: ";
	cin >> g_validInputFilePath;

	// Ensure that the user inputs something
	while(g_validInputFilePath.empty()) {
		cout << "You did not input a file path.  Please input the full file path for the input file." << endl;
		cout << "File path: ";
		cin >> g_validInputFilePath;
	}
*/

	if(argc < 2) {
		cout << "Log file not passed in as an argument" << endl;
		exit(-1);
	}

	g_validInputFilePath = string(argv[1]);

	return RUN_ALL_TESTS();
}


