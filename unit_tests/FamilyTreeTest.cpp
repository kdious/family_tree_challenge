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




int main(int argc, char **argv) {
  printf("Running main() from sample1\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

