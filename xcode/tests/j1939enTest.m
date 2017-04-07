
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


#import <XCTest/XCTest.h>


// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      XCTAssert(expression, failure_description, ...)
//      XCTFail(failure_description, ...)
//      XCTAssertEqualObjects(object_1, object_2, failure_description, ...) uses isEqualTo:
//      XCTAssertEquals(value_1, value_2, failure_description, ...)
//      XCTAssertEqualsWithAccuracy(value_1, value_2, accuracy, failure_description, ...)
//      XCTAssertNil(expression, failure_description, ...)
//      XCTAssertNotNil(expression, failure_description, ...)
//      XCTAssertTrue(expression, failure_description, ...)
//      XCTAssertFalse(expression, failure_description, ...)
//      XCTAssertThrows(expression, failure_description, ...)
//      XCTAssertThrowsSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertThrowsSpecificNamed(expression, exception_class, exception_name,
//                                  failure_description, ...)
//      XCTAssertNoThrow(expression, failure_description, ...)
//      XCTAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertNoThrowSpecificNamed(expression, exception_class, exception_name,
//                                  failure_description, ...)


#include    <j1939.h>
#include    "j1939en_internal.h"



#include	"common.h"
#include    "j1939Can.h"
#include    "j1939Sys.h"




static
int         shiftsT = 0;
static
int         shiftsF = 0;


void        shiftExit(void *ptr,bool fShifting)
{
    if (fShifting) {
        fprintf(stderr, "NOW SHIFTING    ======================================\n");
        ++shiftsT;
    }
    else {
        fprintf(stderr, "END OF SHIFTING ======================================\n");
        ++shiftsF;
    }
}




@interface j1939enTests : XCTestCase

@end

@implementation j1939enTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    mem_Init( );
    
}


- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
    
    mem_Dump( );
}



- (void)testOpenClose_1_0
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939EN_DATA    *pEN = NULL;

    j1939Sys_TimeReset(pSYS, 0);
    
    pEN = j1939en_Alloc();
    XCTAssertFalse( (NULL == pEN), @"Could not alloc pEN" );
    pEN = j1939en_Init( pEN, NULL, xmtHandler, NULL, 0, 0, 0 );
    XCTAssertFalse( (NULL == pEN), @"Could not init pEN" );
    if (pEN) {

        //pBase = j1939_getBase( pJ1939 );
        //STAssertFalse( (NULL == pBase), @"Could not open canbase" );
        //STAssertTrue( (OBJ_IDENT_CANBASE == obj_getIdent(pBase)), @"??" );
        //STAssertTrue( (canbase_getBaud(pBase) == CANBASE_BAUD_250000_10), @"??" );

        obj_Release(pEN);
        pEN = NULL;
    }

    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    j1939_SharedReset( );

}



- (void)testTimedMessages
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939EN_DATA    *pEN = NULL;
    J1939_PDU       pdu;
    bool            fRc;
        
    j1939Sys_TimeReset(pSYS, 0);

    pEN = j1939en_Alloc();
    XCTAssertFalse( (NULL == pEN), @"Could not alloc pEN" );
    pEN = j1939en_Init( pEN, NULL, xmtHandler, NULL, 0, 0, 0 );
    XCTAssertFalse( (NULL == pEN), @"Could not init pEN" );
    if (pEN) {
        
        for (int i=0; i<1000; ++i) {
            fRc = (*j1939ca_getHandler((J1939CA_DATA *)pEN))( (J1939CA_DATA *)pEN, 0, NULL );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (61 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x0CF00300 == pdu.eid), @"Result was false!" );
        
        obj_Release(pEN);
        pEN = NULL;
    }
    
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    j1939_SharedReset( );
    
}



- (void)testCheck_TSC1_Direct_Clean
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939EN_DATA    *pJ1939er = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    j1939Sys_TimeReset(pSYS, 0);

    pJ1939er = j1939en_Alloc();
    XCTAssertFalse( (OBJ_NIL == pJ1939er) );
    pJ1939er = j1939en_Init( pJ1939er, OBJ_NIL, xmtHandler, NULL, 0, 0, 0 );
    XCTAssertFalse( (OBJ_NIL == pJ1939er) );
    cCurMsg = 0;
    if (pJ1939er) {
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939er, 0, NULL);
        j1939Sys_BumpMS(pSYS, 250);
        // Send "Timed Out".
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939er, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pJ1939er->super.cs), @"" );
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 0;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 1;                // Engine
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939er, pdu.eid, &msg );
        XCTAssertTrue( (true == pJ1939er->fActive), @"" );
        XCTAssertTrue( (3 == pJ1939er->spn1480), @"" );
        
        for (int i=0; i<500; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939er, 0, NULL );
        }
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 0;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // Disable Brake
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939er, pdu.eid, &msg );
        XCTAssertTrue( (false == pJ1939er->fActive), @"" );
        XCTAssertTrue( (255 == pJ1939er->spn1480), @"" );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (29 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-2]);
        XCTAssertTrue( (0x0CF00300 == pdu.eid), @"Result was false!" );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x0C000003 == pdu.eid), @"Result was false!" );
        
        obj_Release(pJ1939er);
        pJ1939er = OBJ_NIL;
    }
    
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    j1939_SharedReset( );

}



- (void)testCheck_TSC1_Direct_Timeout
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939EN_DATA    *pJ1939er = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    j1939Sys_TimeReset(pSYS, 0);

    pJ1939er = j1939en_Alloc();
    XCTAssertFalse( (OBJ_NIL == pJ1939er), @"Could not alloc J1939CA" );
    pJ1939er = j1939en_Init( pJ1939er, OBJ_NIL, xmtHandler, NULL, 0, 0, 0 );
    XCTAssertFalse( (OBJ_NIL == pJ1939er), @"Could not init J1939CA" );
    cCurMsg = 0;
    if (pJ1939er) {
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939er, 0, NULL);
        j1939Sys_BumpMS(pSYS, 250);
        // Send "Timed Out".
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939er, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pJ1939er->super.cs), @"" );
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 1;                // Engine
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939er, pdu.eid, &msg );
        XCTAssertTrue( (true == pJ1939er->fActive), @"" );
        XCTAssertTrue( (3 == pJ1939er->spn1480), @"" );
        
        for (int i=0; i<200; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939er, 0, NULL );
        }
        
#ifdef XYZZY
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 0;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // Disable Brake
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939er, pdu.eid, &msg );
#endif
        XCTAssertTrue( (false == pJ1939er->fActive), @"" );
        XCTAssertTrue( (255 == pJ1939er->spn1480), @"" );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (15 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-2]);
        XCTAssertTrue( (0x18FEDF00 == pdu.eid), @"Result was false!" );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x0CF00300 == pdu.eid), @"Result was false!" );
        
        obj_Release(pJ1939er);
        pJ1939er = OBJ_NIL;
    }
    
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    j1939_SharedReset( );
    
}



- (void)testCheck_MSG02_Clean
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939EN_DATA    *pEng = NULL;
    bool            fRc;
    J1939_MSG       msg;
    uint32_t        i;
    int             count = 0;
    
    j1939Sys_TimeReset(pSYS, 0);
    
    shiftsT = 0;
    shiftsF = 0;
    
    pEng = j1939en_Alloc();
    XCTAssertFalse( (OBJ_NIL == pEng), @"Could not alloc J1939CA" );
    pEng = j1939en_Init( pEng, OBJ_NIL, xmtHandler, NULL, 0, 0, 0 );
    XCTAssertFalse( (OBJ_NIL == pEng), @"Could not init J1939CA" );
    cCurMsg = 0;
    if (pEng) {
        
        fRc = j1939en_setShiftExit(pEng, shiftExit, NULL);
        XCTAssertTrue( (fRc), @"" );
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pEng, 0, NULL);
        j1939Sys_BumpMS(pSYS, 250);
        // Send "Timed Out".
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pEng, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs), @"" );
        
        // Send all msg02 msgs.
        for (i=0; i<cMsgs02; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs02[i].pdu, Msgs02[i].len, Msgs02[i].data);
            msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
            printCanMsg(&msg);
            //fRc = xmtHandler(NULL, 0, &msg);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, Msgs02[i].pdu, &msg );
            XCTAssertTrue( (true == pEng->fActive), @"" );
            if (pEng->fShifting) {
                fprintf(stderr, "\tShifting with detorque!\n");
                ++count;
            }
        }
        fprintf(stderr, "Number of messages in shift mode: %d\n",count);
        fprintf(stderr, "Number of true shifts: %d\n",shiftsT);
        fprintf(stderr, "Number of false shifts: %d\n",shiftsF);
        XCTAssertTrue( (shiftsT == shiftsF), @"" );
        XCTAssertTrue( (shiftsT == 15), @"" );
        
        obj_Release(pEng);
        pEng = OBJ_NIL;
    }
    
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    j1939_SharedReset( );

}



- (void)testCheck_MSG03_Clean
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939EN_DATA    *pEng = NULL;
    bool            fRc;
    J1939_MSG       msg;
    uint32_t        i;
    int             count = 0;
    
    j1939Sys_TimeReset(pSYS, 0);
    
    shiftsT = 0;
    shiftsF = 0;
    
    pEng = j1939en_Alloc();
    XCTAssertFalse( (OBJ_NIL == pEng), @"Could not alloc J1939CA" );
    pEng = j1939en_Init( pEng, OBJ_NIL, xmtHandler, NULL, 0, 0, 0 );
    XCTAssertFalse( (OBJ_NIL == pEng), @"Could not init J1939CA" );
    cCurMsg = 0;
    if (pEng) {
        
        fRc = j1939en_setShiftExit(pEng, shiftExit, NULL);
        XCTAssertTrue( (fRc), @"" );
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pEng, 0, NULL);
        j1939Sys_BumpMS(pSYS, 250);
        // Send "Timed Out".
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pEng, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs), @"" );
        
        // Send all msg03 msgs.
        for (i=0; i<cMsgs03; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs03[i].pdu, Msgs03[i].len, Msgs03[i].data);
            msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
            printCanMsg(&msg);
            //fRc = xmtHandler(NULL, 0, &msg);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, Msgs03[i].pdu, &msg );
            //STAssertTrue( (true == pEng->fActive), @"" );
            if (pEng->fShifting) {
                fprintf(stderr, "\tShifting with detorque!\n");
                ++count;
            }
        }
        fprintf(stderr, "Number of messages in shift mode: %d\n",count);
        fprintf(stderr, "Number of true shifts: %d\n",shiftsT);
        fprintf(stderr, "Number of false shifts: %d\n",shiftsF);
        XCTAssertTrue( (shiftsT == shiftsF), @"" );
        
        obj_Release(pEng);
        pEng = OBJ_NIL;
    }
    
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    j1939_SharedReset( );

}



@end



