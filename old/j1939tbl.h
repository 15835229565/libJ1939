// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          J1939TBL Console Transmit Task (j1939tbl) Header
//****************************************************************
/*
 * Program
 *				Separate j1939tbl (j1939tbl)
 * Purpose
 *				This object provides a standardized way of handling
 *              a separate j1939tbl to run things without complications
 *              of interfering with the main j1939tbl. A j1939tbl may be 
 *              called a j1939tbl on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal j1939tbl. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	05/20/2015 Generated
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






#include        <j1939_defs.h>


#ifndef         J1939TBL_H
#define         J1939TBL_H  1


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939tbl_data_s	J1939TBL_DATA;


    typedef struct j1939tbl_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939tbl_object.c.
        // Properties:
        // Methods:
    } J1939TBL_VTBL;

    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    J1939TBL_DATA * j1939tbl_Alloc(
    );
    
    
    /*!
     Create an 8-bit mask given the number of bits and position.
     @param:    this    J1939TBL object pointer
     @param:    numBits number of bits in the mask (0 < numBits < 9)
     @param:    pos     number of bits to shift left
     @return:   If successful, the byte mask otherwise 0
     */
    uint8_t         j1939tbl_CreateBitMask(
        uint16_t        numBits,
        uint16_t        pos
    );
    
    
    int32_t         j1939tbl_SpnToS32(
        J1939_SPN_TYPE  *pType,
        uint16_t        data
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            j1939tbl_setFileOut(
        J1939TBL_DATA   *this,
        FILE            *pValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    bool            j1939tbl_DumpMessage(
        J1939TBL_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    
    J1939TBL_DATA *     j1939tbl_Init(
        J1939TBL_DATA       *this
    );


    
    //---------------------------------------------------------------
    //                      *** SPN Types Table ***
    //---------------------------------------------------------------
    
    extern
    const
    J1939_SPN_TYPE      SAEfg01;
    extern
    const
    J1939_SPN_TYPE      SAEgv01;
    extern
    const
    J1939_SPN_TYPE      SAEpc03;
    extern
    const
    J1939_SPN_TYPE      SAEpc05;
    extern
    const
    J1939_SPN_TYPE      SAEpr02;
    extern
    const
    J1939_SPN_TYPE      SAEpr05;
    extern
    const
    J1939_SPN_TYPE      SAEpr07;
    extern
    const
    J1939_SPN_TYPE      SAEpr10;
    extern
    const
    J1939_SPN_TYPE      SAEtm09;
    extern
    const
    J1939_SPN_TYPE      SAEtp01;
    extern
    const
    J1939_SPN_TYPE      SAEvl02;
    extern
    const
    J1939_SPN_TYPE      SAEvl04;
    extern
    const
    J1939_SPN_TYPE      SAEvl05;
    extern
    const
    J1939_SPN_TYPE      SAEvr01;
    
    
    
    //---------------------------------------------------------------
    //                      *** PGN Table ***
    //---------------------------------------------------------------
    
    extern
    const
    J1939_PGN_ENTRY     pgn0_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn256_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn51456_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn57344_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn59392_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn59904_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn60160_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn60416_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn60928_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61184_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61440_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61442_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61443_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61444_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61445_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65098_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65129_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65184_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65217_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65226_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65242_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65247_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65249_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65252_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65261_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65262_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65265_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65269_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65271_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65272_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65279_entry;
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* J1939TBL_H */

