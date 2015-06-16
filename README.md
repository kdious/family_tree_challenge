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

## Runing Program

In the eclipse project, jsut select either the "Debug" or "GTest" configuration depending on which
scenario you want to run.

If you want to run the executable directly, you will want to do the following (linux example):

$ LD_LIBARY_PATH=<path to library files> ./<executable name> <path to input file>

example: LD_LIBRARY_PATH=../libs ./family_tree_challenge ../input_files/sample_family_tree_input_file.txt

## Tests

See FamilyTreeTests.cpp for examples on how to write and test.

Also, to test private member functions, see https://code.google.com/p/googletest/wiki/AdvancedGuide#Testing_Private_Code