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
        // Defauly value for age
        uint8_t INVALID_AGE = UINT8_MAX;
        
        // Gender value
        typedef enum {
            Male,
            Female,
            Other,
            Invalid
        } gender_t;
        
        // Relationships between family members
        typedef enum {
            Parent,
            Child,
            Sibling
        } relationship_t;
    
    // Member variables
    private:


    public:
        
};

} /* namespace FamilyTree */

#endif	/* FAMILYMEMBERCLASS_H */

