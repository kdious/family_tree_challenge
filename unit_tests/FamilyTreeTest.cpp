/* 
 * File:   FamilyTreeTest.cpp
 * Author: builduser
 *
 * Created on Jun 12, 2015, 11:30:05 PM
 */

#include <gtest/gtest.h>

#include "FamilyTreeClass.h"
#include "FamilyTreeOpResultCode.h"

using namespace FamilyTree;

class FamilyTreeTestSuite : public testing::Test {
protected:
};

TEST_F(FamilyTreeTestSuite, invalidInputFileName) {
    FamilyTreeClass testTree;
    
    EXPECT_EQ(INPUT_FILE_OPEN_ERROR, testTree.initialize("invalidFileName.txt"));
    
}

TEST_F(FamilyTreeTestSuite, validInputFile) {
    FamilyTreeClass testTree;

    string validInputFilePath =
    		"/home/builduser/git/family_tree_challenge/input_files/sample_family_tree_input_file.txt";


    EXPECT_EQ(SUCCESS, testTree.initialize(validInputFilePath));
}

TEST_F(FamilyTreeTestSuite, siblingCount) {
    FamilyTreeClass testTree;

    string validInputFilePath =
    		"/home/builduser/git/family_tree_challenge/input_files/sample_family_tree_input_file.txt";

    // Initialize the tree
    testTree.initialize(validInputFilePath);

    uint32_t siblingCount = 0;

    // INVALID FAMILY MEMBER
    EXPECT_EQ(FAMILY_MEMBER_NOT_FOUND, testTree.countSiblings("Invalid_Family_Member_Name", siblingCount));

    // NO SIBLINGS

    // Nancy
	EXPECT_EQ(SUCCESS, testTree.countSiblings("Nancy", siblingCount));
	EXPECT_EQ(0, siblingCount);

	// Kevin
	EXPECT_EQ(SUCCESS, testTree.countSiblings("Kevin", siblingCount));
	EXPECT_EQ(0, siblingCount);

	// Mary
	EXPECT_EQ(SUCCESS, testTree.countSiblings("Mary", siblingCount));
	EXPECT_EQ(0, siblingCount);


    // ONE SIBLING

	// Catherine
	EXPECT_EQ(SUCCESS, testTree.countSiblings("Catherine", siblingCount));
	EXPECT_EQ(1, siblingCount);

	// Joseph
	EXPECT_EQ(SUCCESS, testTree.countSiblings("Joseph", siblingCount));
	EXPECT_EQ(1, siblingCount);

	// Patrick
	EXPECT_EQ(SUCCESS, testTree.countSiblings("Patrick", siblingCount));
	EXPECT_EQ(1, siblingCount);

	// Robert
	EXPECT_EQ(SUCCESS, testTree.countSiblings("Robert", siblingCount));
	EXPECT_EQ(1, siblingCount);

	// TWO SIBLINGS

	// Carl
    EXPECT_EQ(SUCCESS, testTree.countSiblings("Carl", siblingCount));
    EXPECT_EQ(2, siblingCount);

    // Jill
	EXPECT_EQ(SUCCESS, testTree.countSiblings("Jill", siblingCount));
	EXPECT_EQ(2, siblingCount);

	// Adam
	EXPECT_EQ(SUCCESS, testTree.countSiblings("Adam", siblingCount));
	EXPECT_EQ(2, siblingCount);

	// THREE SIBLINGS

	// Aaron
	EXPECT_EQ(SUCCESS, testTree.countSiblings("Aaron", siblingCount));
	EXPECT_EQ(3, siblingCount);

	// James
	EXPECT_EQ(SUCCESS, testTree.countSiblings("James", siblingCount));
	EXPECT_EQ(3, siblingCount);

	// George
	EXPECT_EQ(SUCCESS, testTree.countSiblings("George", siblingCount));
	EXPECT_EQ(3, siblingCount);

	// Samuel
	EXPECT_EQ(SUCCESS, testTree.countSiblings("Samuel", siblingCount));
	EXPECT_EQ(3, siblingCount);
}


int main(int argc, char **argv) {
  printf("Running main() from sample1\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

