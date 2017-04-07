// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          J1939 CAN Test Object (j1939Can) Header
//****************************************************************
/*
 * Program
 *			J1939 CAN Test Object (j1939Can)
 * Purpose
 *			This object provides a means of testing the operation
 *          of libJ1939 without actually having the library connected
 *          to a CAN Port. It requires j1939Sys as well.
 *
 * Remarks
 *	1.      J1939CAN_VTBL must be in sync with the J1939_CAN_VTBL in
 *          j1939_defs.h
 *  2.      This object is only used in a test environment and not
 *          needed in an operational environment.
 *
 * History
 *	04/06/2017 Generated
 */


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





#include        <cmn_defs.h>
#include        <AStr.h>
#include        <j1939_defs.h>


#ifndef         J1939CAN_H
#define         J1939CAN_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939Can_data_s	J1939CAN_DATA;    // Inherits from OBJ.

    typedef struct j1939Can_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939Can_object.c.
        // Properties:
        // Methods:
        P_SRVCMSG_RTN   *pSvc;
        P_XMTMSG_RTN    *pXmt;
        bool            (*pSetLoopBackMode)(OBJ_ID);
        bool            (*pSetNormalMode)(OBJ_ID);
    } J1939CAN_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return:   pointer to j1939Can object if successful, otherwise OBJ_NIL.
     */
    J1939CAN_DATA *     j1939Can_Alloc(
        uint16_t    stackSize           // Stack Size in Words
    );
    
    
    J1939CAN_DATA *     j1939Can_New(
        uint16_t    stackSize           // Stack Size in Words
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     j1939Can_getLastError(
        J1939CAN_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     j1939Can_Disable(
        J1939CAN_DATA		*this
    );


    ERESULT     j1939Can_Enable(
        J1939CAN_DATA		*this
    );

   
    J1939CAN_DATA *   j1939Can_Init(
        J1939CAN_DATA     *this
    );


    ERESULT     j1939Can_IsEnabled(
        J1939CAN_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939Can_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939CAN object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    j1939Can_ToDebugString(
        J1939CAN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* J1939CAN_H */

