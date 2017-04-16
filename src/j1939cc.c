// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939cc.c
 *	Generated 04/15/2017 08:51:40
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include <j1939cc_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn57344_entry = {
        // PGN 57344  0x00F003 - Electronic Engine Controller 2 - EEC2
        &pgn57344_entry,
        (P_SRVCMSG_RTN)j1939cc_HandlePgn57344,
        (P_MSGDATA_RTN)j1939cc_SetupPgn57344,
        offsetof(J1939CC_DATA, startTime57344),
        0,
        0,
        1000
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61443_entry = {
        // PGN 61443  0x00F003 - Electronic Engine Controller 2 - EEC2
        &pgn61443_entry,
        (P_SRVCMSG_RTN)j1939cc_HandlePgn61443,
        (P_MSGDATA_RTN)j1939cc_SetupPgn61443,
        offsetof(J1939CC_DATA, startTime61443),
        0,
        0,
        50
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65217_entry = {
        &pgn65217_entry,
        (P_SRVCMSG_RTN)j1939cc_HandlePgn65217,
        (P_MSGDATA_RTN)j1939cc_SetupPgn65217,
        offsetof(J1939CC_DATA, startTime65217),
        0,
        0,
        1000
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65226_entry = {
        // PGN 65226  0x00FEF1 - Cruise Control/Vehicle Speed - CCVS
        &pgn65226_entry,
        (P_SRVCMSG_RTN)j1939cc_HandlePgn65226,
        (P_MSGDATA_RTN)j1939cc_SetupPgn65226,
        offsetof(J1939CC_DATA, startTime65226),
        0,
        0,
        1000
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65261_entry = {
        &pgn65261_entry,
        NULL, //FIXME: ??? (P_SRVCMSG_RTN)j1939cc_HandlePgn65261,
        NULL, //FIXME: ??? (P_MSGDATA_RTN)j1939cc_SetupPgn65261,
        0,
        0,
        0,
        0                       // On Request
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65265_entry = {
        // PGN 65265  0x00FEF1 - Cruise Control/Vehicle Speed - CCVS
        &pgn65265_entry,
        (P_SRVCMSG_RTN)j1939cc_HandlePgn65265,
        (P_MSGDATA_RTN)j1939cc_SetupPgn65265,
        offsetof(J1939CC_DATA, startTime65265),
        0,
        0,
        100
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65269_entry = {
        // PGN 65269  0x00FEF5 - Ambient Conditions - AMB
        &pgn65269_entry,
        (P_SRVCMSG_RTN)j1939cc_HandlePgn65269,
        (P_MSGDATA_RTN)j1939cc_SetupPgn65269,
        offsetof(J1939CC_DATA, startTime65269),
        0,
        0,
        1000
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65271_entry = {
        // PGN 65269  0x00FEF5 - Ambient Conditions - AMB
        &pgn65271_entry,
        (P_SRVCMSG_RTN)j1939cc_HandlePgn65271,
        (P_MSGDATA_RTN)j1939cc_SetupPgn65271,
        offsetof(J1939CC_DATA, startTime65271),
        0,
        0,
        1000
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     *rcvPgnIndex[] = {
        //&ca_pgn0_entry,
        //&ca_pgn61442_entry,
        //&ca_pgn61445_entry,
        //&ca_pgn65252_entry,
        NULL
    };
    
    static
    const
    J1939CA_PGN_TABLE   rcvPgnTbl = {
        (sizeof(rcvPgnIndex)/sizeof(J1939CA_PGN_ENTRY *))-1,
        0,              // Reserved
        &rcvPgnIndex
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY   *xmtPgnIndex[] = {
        &ca_pgn61443_entry,
        &ca_pgn65217_entry,
        &ca_pgn65265_entry,
        &ca_pgn65261_entry,
        &ca_pgn65269_entry,
        &ca_pgn65271_entry,
        NULL
    };
    
    static
    const
    J1939CA_PGN_TABLE   xmtPgnTbl = {
        (sizeof(xmtPgnIndex)/sizeof(J1939CA_PGN_ENTRY *))-1,
        0,              // Reserved
        &xmtPgnIndex
    };
    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            j1939cc_task_body(
        void            *pData
    )
    {
        //J1939CC_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939CC_DATA *     j1939cc_Alloc(
    )
    {
        J1939CC_DATA       *this;
        uint32_t        cbSize = sizeof(J1939CC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939CC_DATA *     j1939cc_New(
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        J1939CC_DATA       *this;
        
        this = j1939cc_Alloc( );
        if (this) {
            this = j1939cc_Init(this, pCAN, pSYS, spn2837, spn2838, spn2846);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         j1939cc_getLastError(
        J1939CC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939cc_setLastError(
        J1939CC_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        j1939cc_getPriority(
        J1939CC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939cc_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            j1939cc_setPriority(
        J1939CC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        j1939cc_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        j1939cc_getSize(
        J1939CC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939cc_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code:
        ERESULT eRc = j1939cc__Assign(this,pOther);
     @endcode:
     @param:    this    J1939CC object pointer
     @param:    pOther  a pointer to another J1939CC object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         j1939cc_Assign(
        J1939CC_DATA		*this,
        J1939CC_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return j1939cc_getLastError(this);
        }
        if( !j1939cc_Validate(pOther) ) {
            DEBUG_BREAK();
            return j1939cc_getLastError(pOther);
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        j1939cc_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939cc_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939cc_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        j1939cc      *pCopy = j1939cc_Copy(this);
     @endcode:
     @param:    this    J1939CC object pointer
     @return:   If successful, a J1939CC object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the J1939CC object.
     */
    J1939CC_DATA *     j1939cc_Copy(
        J1939CC_DATA       *this
    )
    {
        J1939CC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //FIXME: pOther = j1939cc_New(obj_getSize(this));
        if (pOther) {
            eRc = j1939cc_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939cc_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939cc_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939CC_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((J1939CC_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        j1939ca_Dealloc(this);          // Needed for inheritance
        //obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939cc_Disable(
        J1939CC_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939cc_setLastError(this, ERESULT_INVALID_OBJECT);
            return j1939cc_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return j1939cc_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939cc_setLastError(this, ERESULT_SUCCESS);
        return j1939cc_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939cc_Enable(
        J1939CC_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return j1939cc_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939cc_setLastError(this, ERESULT_SUCCESS);
        return j1939cc_getLastError(this);
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 6 5
    //---------------------------------------------------------------
    
    bool            j1939cc_HandlePgn65265(
       J1939CC_DATA     *this,
       uint32_t         eid,
       J1939_MSG        *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);

        
        
        
        
        
        
        
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939CC_DATA *  j1939cc_Init(
        J1939CC_DATA    *this,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint32_t        cbSize = sizeof(J1939CC_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this = (OBJ_ID)j1939ca_Init(                        // Needed for Inheritance
                                  (J1939CA_DATA *)this,
                                    pCAN,
                                    pSYS,
                                    spn2837,
                                    spn2838,
                                    spn2846
                    );
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939CC);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                        // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_J1939CC);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939cc_Vtbl);
        
        j1939cc_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

        this->super.ca = J1939_CAB_CONTROLLER;
        //this->super.name.ECU = 0;
        this->super.name.FU = 3;
        this->super.name.FUI = 0;
        //FIXME: this->super.pRcvPgnTbl = &rcvPgntbl;
        //FIXME: this->super.pXmtPgnTbl = &xmtPgntbl;
        //FIXME: this->super.pTimedTransmit = (P_HANDLE_TIMED_TRANSMITS)&j1939cc_HandleTimedTransmits;
        
    #ifdef NDEBUG
    #else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         j1939cc_IsEnabled(
        J1939CC_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return j1939cc_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939cc_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939cc_getLastError(this);
        }
        
        // Return to caller.
        j1939cc_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939cc_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939cc_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939CC object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939cc_ToDebugString(
        J1939CC_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cc_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(j1939cc)\n",
                     this
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(j1939cc)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939cc_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 1 4 4 3   0xF003       EEC2
    //---------------------------------------------------------------
    
    // Electronic Engine Controller 2 - EEC2 -
    // Unused bits are set to 1.
    
    int             j1939cc_SetupPgn61443(
        J1939CC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn61443_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn61443_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn61443_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = 0xC0;
            *pData |= this->spn558 & 0x3;
            *pData |= (this->spn559 & 0x3) << 2;
            *pData |= (this->spn1437 & 0x3) << 4;
            ++pData;    // 1
            *pData  = this->spn91;                   // Accelerator Pedal Position 1
            ++pData;    // 2
            *pData  = this->spn92;
            ++pData;    // 3
            *pData  = this->spn974;
            ++pData;    // 4
            *pData  = 0xFF;
            ++pData;    // 5
            *pData  = 0xFF;
            ++pData;    // 6
            *pData  = 0xFF;
            ++pData;    // 7
            *pData  = 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939cc_TransmitPgn61443(
        J1939CC_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;

        iRc = j1939cc_SetupPgn61443(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, 0, pdu, dlc, &data);
        this->startTime61443 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 1 7   0xFEC1      VDHR
    //---------------------------------------------------------------
    
    /* High Resolution Vehicle Distance - VDHR -
     * Freq: 1000 ms
     * Priority: 6
     */
    int             j1939cc_SetupPgn65217(
        J1939CC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65217_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65217_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65217_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn917 & 0xFF;
            ++pData;    // 1
            *pData  = (this->spn917 >> 8) & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn917 >> 16) & 0xFF;
            ++pData;    // 3
            *pData  = (this->spn917 >> 24) & 0xFF;
            ++pData;    // 4
            *pData  = this->spn918 & 0xFF;
            ++pData;    // 5
            *pData  = (this->spn918 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = (this->spn918 >> 16) & 0xFF;
            ++pData;    // 7
            *pData  = (this->spn918 >> 24) & 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939cc_TransmitPgn65217(
        J1939CC_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cc_SetupPgn65217(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, 0, pdu, dlc, &data);
        this->startTime65217 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        // Return to caller.
        return fRc;
    }
    
    

    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 6 1   0xFEED      CCSS
    //---------------------------------------------------------------
    
    /* CruiseControl/VehicleSpeedSetup - CCSS -
     * Freq: 0 ms
     * Priority: 6
     */
    int             j1939cc_SetupPgn65261(
        J1939CC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65261_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65261_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65261_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn74;
            ++pData;    // 1
            *pData  = this->spn87;
            ++pData;    // 2
            *pData  = this->spn88;
            ++pData;    // 3
            *pData  = 0xFF;
            ++pData;    // 4
            *pData  = 0xFF;
            ++pData;    // 5
            *pData  = 0xFF;
            ++pData;    // 6
            *pData  = 0xFF;
            ++pData;    // 7
            *pData  = 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939cc_TransmitPgn65261(
        J1939CC_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cc_SetupPgn65261(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, 0, pdu, dlc, &data);
        this->startTime65261 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        // Return to caller.
        return fRc;
    }
    
    

    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 6 5   0xFEF1      CCVS
    //---------------------------------------------------------------
    
    /* Cruise Control/Vehicle Speed - CCVS -
     * Freq: 100 ms
     * Priority: 6
     */
    int             j1939cc_SetupPgn65265(
        J1939CC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65265_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65265_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65265_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = 0xC0;
            *pData |= (this->spn69 & 0x3);
            *pData |= (this->spn70 & 0x3) << 2;
            *pData |= (this->spn1633 & 0x3) << 4;
            ++pData;    // 1
            *pData  = this->spn84 & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn84 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = 0;
            *pData |= (this->spn595 & 0x3);
            *pData |= (this->spn596 & 0x3) << 2;
            *pData |= (this->spn597 & 0x3) << 4;
            *pData |= (this->spn598 & 0x3) << 6;
            ++pData;    // 4
            *pData  = 0;
            *pData |= (this->spn599 & 0x3);
            *pData |= (this->spn600 & 0x3) << 2;
            *pData |= (this->spn601 & 0x3) << 4;
            *pData |= (this->spn602 & 0x3) << 6;
            ++pData;    // 5
            *pData  = (this->spn86 & 0xFF);
            ++pData;    // 6
            *pData  = 0;
            *pData |= (this->spn976 & 0x1F);
            *pData |= (this->spn527 & 0x7) << 5;
            ++pData;    // 7
            *pData  = 0;
            *pData |= (this->spn968 & 0x3);
            *pData |= (this->spn967 & 0x3) << 2;
            *pData |= (this->spn966 & 0x3) << 4;
            *pData |= (this->spn1237 & 0x3) << 6;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939cc_TransmitPgn65265(
        J1939CC_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cc_SetupPgn65265(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, 0, pdu, dlc, &data);
        this->startTime65265 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        // Return to caller.
        return fRc;
    }
    
    

    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 6 9   0xFEF5        AMB
    //---------------------------------------------------------------
    
    /* Ambient Conditions - AMB -
     * Freq: 0 ms
     * Priority: 6
     */
    int             j1939cc_SetupPgn65269(
        J1939CC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65269_entry.pgn >> 8) & 0xFF ;
            pPDU->PS = pgn65269_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65269_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn108;
            ++pData;    // 1
            *pData  = this->spn170 & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn170 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = this->spn171 & 0xFF;
            ++pData;    // 4
            *pData  = (this->spn171 >> 8) & 0xFF;
            ++pData;    // 5
            *pData  = this->spn172;
            ++pData;    // 6
            *pData  = this->spn79 & 0xFF;
            ++pData;    // 7
            *pData  = (this->spn79 >> 8) & 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939cc_TransmitPgn65269(
        J1939CC_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cc_SetupPgn65269(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, 0, pdu, dlc, &data);
        this->startTime65269 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        // Return to caller.
        return fRc;
    }

    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 7 1   0xFEF7       VEP1
    //---------------------------------------------------------------
    
    /* VehicleElectricalPower#1 - VEP1 -
     * Freq: 1000 ms
     * Priority: 6
     */
    int             j1939cc_SetupPgn65271(
        J1939CC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = 254;
            pPDU->PS = 247;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65271_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            //          // 0
            *pData  = this->spn114;
            ++pData;    // 1
            *pData  = this->spn115;
            ++pData;    // 2
            *pData  = this->spn167 & 0xFF;
            ++pData;    // 3
            *pData  = (this->spn167 >> 8) & 0xFF;
            ++pData;    // 4
            *pData  = this->spn168 & 0xFF;
            ++pData;    // 5
            *pData  = (this->spn168 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = this->spn158 & 0xFF;
            ++pData;    // 7
            *pData  = (this->spn158 >> 8) & 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939cc_TransmitPgn65271(
        J1939CC_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cc_SetupPgn65271(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, 0, pdu, dlc, &data);
        this->startTime65271 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939cc_Validate(
        J1939CC_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_J1939CC) )
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if( !(obj_getSize(this) >= sizeof(J1939CC_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


