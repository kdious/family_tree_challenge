# Family Tree Challenge
Family Tree Coding Challenge

## Synopsis

This is a program that reads a family structure from an input file, constructs a family tree, and allows the user to perform predefined query operations on the family tree.

## Motivation

An assigned coding challenge.

## Libraries

GoogleTest

https://code.google.com/p/googletest/

OpenGraphTheory

http://www.open-graphtheory.org/

Boost

http://www.boost.org/

Pthread

- Usually included with the OS

## APIs

The OpenGraphTheory API is documented here:
http://www.open-graphtheory.org/documentation/html/annotated.html


## Installation

Provide code examples and explanations of how to get the project.

The project has been uploaded as an Eclipse project.  The projet has two configurations: Debug and GTest

The Debug configuration is for running the user program which has a command line interface.
The GTest configuration is used to run the unit tests of the FamilyTreeClass public methods.

You will need to have the following libraries installed on your machine.

libgtest.a
libopengt.so
lpthread

libgtest.a and libopengt.so are included in the "libs" folder

## Input File

A sample input file is provided in the input_files folder.  See:
https://github.com/kdious/family_tree_challenge/blob/master/input_files/sample_family_tree_input_file.txt

The input file MUST adhere to the following formatting rules in order for it to be read and processed properly by the program:

1. All fields are delimed with a ":".

2. The first non-comment and non-white space line MUST start with the list of family members.

The line MUST start with "MEMBERS" and is then followed a list of family members (in no particular order).
Each name in the members list MUST be unique.

Example:
MEMBERS:Nancy:Carl:Jill:Adam:Joseph:Catherine:Kevin:Aaron:James:George:Samuel:Mary:Patrick:Robert

3. Other subsequent lines can define either PARENT or SIBLING relationships

3a. PARENT relationships

The format of a parent relationship is as follows: PARENT:<parent name>:CHILDREN:<child1>:<child2>:<child3>...
This means that <parent name> is the parent of each of the family members listed after CHILDREN
 
3b. SIBLING relationships
 
The format of a sibling relationship line is as follows: SIBLINGS:<sibling1>:<sibling2>:<sibling33>...
This means that all of the siblings listed after SIBLINGS are in fact siblings.
For each group of siblings, there should also be a PARENT relationship line in the file indicating that all of the siblings have the same parent. 

Example:

PARENT:Nancy:CHILDREN:Carl:Jill:Adam
SIBLINGS:Carl:Jill:Adam

4. Comments

The following characters are acceptable for indicating comments:
#
/

These characters MUST start the line for the lien to be a valid comment line.  Comment lines will be skipped when the file is being read by the program.

## Runing Program

In the eclipse project, jsut select either the "Debug" or "GTest" configuration depending on which
scenario you want to run.

If you want to run the executable directly, you will want to do the following (linux example):

$ LD_LIBARY_PATH=<path to library files> ./<executable name> <path to input file>

example: LD_LIBRARY_PATH=../libs ./family_tree_challenge ../input_files/sample_family_tree_input_file.txt

## Tests

See FamilyTreeTests.cpp for examples on how to write and test.

Also, to test private member functions, see https://code.google.com/p/googletest/wiki/AdvancedGuide#Testing_Private_Code

Info on configuring Eclipse so that your GoogleTest unit test main file can also reside in the same project without the multiple definitions of main compilation issue:

http://pezad-games.googlecode.com/svn/trunk/GTestTest/HOWTO
