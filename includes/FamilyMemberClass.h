/**
 *  @file    FamilyMemberClass.h.cpp
 *  @author  Kevin Dious
 *  @date    6/15/2015
 *
 *  @brief Class definition for FamilyMemberClass object
 *
 *  @section DESCRIPTION
 *
 *  This file details the definition of the
 *  FamilyMemberClass class.
 *
 *  FamilyMemberClass inherits from the Vertex class
 *  in the OpenGraphTheory library.
 *
 *  The class is very basic for now but can easily
 *  be expanded to accomodate the gender and age of
 *  family members as well as other attributes that
 *  can be defined.
 *
 *  Since this class inherits from the Vertex class
 *  many attributes can be stored as Attributes
 *  associated with the Vertex.
 *
 */

#ifndef FAMILYMEMBERCLASS_H
#define	FAMILYMEMBERCLASS_H

#include <stdint.h>
#include <string>

#include "libs/opengt/opengt.h"

#include "gtest/gtest_prod.h" // For testing

namespace FamilyTree {

using namespace OpenGraphtheory;
    
class FamilyMemberClass : public Vertex {
    // Constants and enums
    public:
        //! @brief Default value for age
        uint8_t INVALID_AGE = UINT8_MAX;
        
        //! @brief Gender value
        typedef enum {
            Male,
            Female,
            Other
        } gender_t;
    
    // Member variables
    private:

    // Constructors/Destructors
    public:
        //! @brief Default constructor
        FamilyMemberClass();

        //! @brief Destructor
        ~FamilyMemberClass();

    // Class methods
    public:
        //! @brief Retrieves the number of siblings for this family member
		//! @return Number of siblings
        uint32_t getNumberOfSiblings();

        //! @brief Retrieves the number of children for this family member
		//! @return Number of children
        uint32_t getNumberOfChildren();
        
};

} /* namespace FamilyTree */

#endif	/* FAMILYMEMBERCLASS_H */

