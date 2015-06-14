/* 
 * File:   FamilyMember.h
 * Author: builduser
 *
 * Created on June 9, 2015, 9:51 PM
 */

#ifndef FAMILYMEMBERCLASS_H
#define	FAMILYMEMBERCLASS_H

#include <stdint.h>
#include <string>

#include "libs/opengt/opengt.h"

namespace FamilyTree {

using namespace OpenGraphtheory;
    
class FamilyMemberClass : public Vertex {
    // Constants and enums
    public:
        // Default value for age
        uint8_t INVALID_AGE = UINT8_MAX;
        
        // Gender value
        typedef enum {
            Male,
            Female,
            Other,
            Invalid
        } gender_t;
    
    // Member variables
    private:

    // Constructors/Destructors
    public:
        // Default constructor
        FamilyMemberClass();

        // Destructor
        ~FamilyMemberClass();

    // Class methods
    public:
        uint32_t getSiblingCount();
        
};

} /* namespace FamilyTree */

#endif	/* FAMILYMEMBERCLASS_H */

