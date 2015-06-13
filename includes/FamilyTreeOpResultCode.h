/*
 * UbiResultCode.h
 *
 *  Created on: Dec 9, 2014
 *      Author: builduser
 */

#ifndef FAMILYTREEOPRESULTCODE_H_
#define FAMILYTREEOPRESULTCODE_H_

#include <limits.h>

namespace FamilyTree {

    // Error codes that functions and methods will return
    typedef enum {
        UNDEFINED_ERROR = INT_MIN,
        INVALID_ARG,        
        TREE_CONSTRUCTION_ERROR,
        OBJECT_INSTANTIATION_ERROR,
        ADD_VERTEX_ERROR,
        ADD_EDGE_ERROR,
        INPUT_FILE_OPEN_ERROR,
        INPUT_FILE_FORMAT_ERROR,
        SUCCESS = 0
    } FamilyTreeOpResultCode;

} /* namespace FamilyTree */

#endif /* FAMILYTREEOPRESULTCODE_H_ */
