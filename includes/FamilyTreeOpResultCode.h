/**
 *  @file    FamilyTreeOpResultCode.h.cpp
 *  @author  Kevin Dious
 *  @date    6/15/2015
 *
 *  @brief Defines various result codes that are used to convey information
 *
 *  @section DESCRIPTION
 *
 *  Operation result codes that are used to identify
 *  whether a method succeeds or the actual reason why
 *  the method failed.
 *
 */

#ifndef FAMILYTREEOPRESULTCODE_H_
#define FAMILYTREEOPRESULTCODE_H_

#include <limits.h>

namespace FamilyTree {

    //! @brief Error codes that functions and methods will return
    typedef enum {
        UNDEFINED_ERROR = INT_MIN,
        INVALID_ARG,        
        TREE_CONSTRUCTION_ERROR,
        OBJECT_INSTANTIATION_ERROR,
        ADD_VERTEX_ERROR,
        ADD_EDGE_ERROR,
        INPUT_FILE_OPEN_ERROR,
        INPUT_FILE_FORMAT_ERROR,
        FAMILY_MEMBER_NOT_FOUND,
		SUCCESS = 0
    } FamilyTreeOpResultCode;

} /* namespace FamilyTree */

#endif /* FAMILYTREEOPRESULTCODE_H_ */
