// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'j1939Can'
//	Generated 04/06/2017 16:09:16


/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */


#define			J1939CAN_OBJECT_C	    1
#include        "j1939Can_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct j1939Can_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct j1939Can_class_data_s J1939CAN_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        j1939Can_Info;            // Forward Reference



OBJ_ID          j1939Can_Class(
    OBJ_ID          objId
);



static
bool            j1939Can_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939CAN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		obj_ClassWhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_J1939CAN_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&j1939Can_Info,
    j1939Can_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
J1939CAN_CLASS_DATA  j1939Can_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_J1939CAN_CLASS, 0, 1},
	//0
};



static
bool            j1939Can_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939CAN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            j1939Can_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          j1939Can_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&j1939Can_ClassObj;
}


static
uint16_t		j1939Can_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_J1939CAN;
}


const
J1939CAN_VTBL     j1939Can_Vtbl = {
    {
        &j1939Can_Info,
        j1939Can_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        j1939Can_Dealloc,
        j1939Can_Class,
        j1939Can_WhoAmI,
        NULL,			// j1939Can_Enable,
        NULL,			// j1939Can_Disable,
        (P_OBJ_TOSTRING)j1939Can_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)j1939Can_Assign,
        NULL,			// (P_OBJ_COMPARE)j1939Can_Compare,
        NULL, 			// (P_OBJ_PTR)j1939Can_Copy,
        NULL 			// (P_OBJ_HASH)j1939Can_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    j1939Can_XmtMsg
 
};



static
const
OBJ_INFO        j1939Can_Info = {
    "j1939Can",
    "j1939 CAN Test Object",
    (OBJ_DATA *)&j1939Can_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&j1939Can_Vtbl
};





