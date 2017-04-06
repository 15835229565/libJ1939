
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
#include    "j1939tc_internal.h"

#include	"common.h"




@interface j1939tcTests : XCTestCase

@end

@implementation j1939tcTests


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
    J1939TC_DATA    *pER = NULL;

    tn_time_reset();
    pER = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pER), @"Could not alloc pER" );
    pER = j1939tc_Init(
                       pER,
                       NULL,            // pJ1939 - 
                       xmtHandler,      // pXmtMsg
                       NULL             // pXmtData
            );
    XCTAssertFalse( (NULL == pER), @"Could not init pER" );
    cCurMsg = 0;
    if (pER) {

        obj_Release(pER);
        pER = NULL;
    }

    j1939_SharedReset( );
    canbase_SharedReset( );
    
}



#ifdef XYZZY
- (void)testCheck_RequestNameDirect
{
    J1939TC_DATA    *pJ1939tc = NULL;
    bool            fRc;
    CAN_MSG         msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    tn_time_reset();

    pJ1939tc = j1939tc_Alloc();
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not alloc J1939CA" );
    pJ1939tc = j1939tc_Init( pJ1939tc, OBJ_NIL, xmtHandler, NULL );
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not init J1939CA" );
    cCurMsg = 0;
    if (pJ1939tc) {

        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        tn_time_bump(250);
        // Send "Timed Out".
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        STAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pJ1939tc->super.cs), @"" );

        // Setup up msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0xEE;
        data[2] = 0x00;
        canmsg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939tc, pdu.eid, &msg );
        STAssertTrue( (4 == cCurMsg), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-2]);
        STAssertTrue( (0x18EEFF29 == pdu.eid), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        STAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );

        obj_Release(pJ1939tc);
        pJ1939tc = OBJ_NIL;
    }
    
    j1939_SharedReset( );
    canbase_SharedReset( );
}



- (void)testCheck_RequestBadNameDirect
{
    J1939TC_DATA    *pJ1939tc = NULL;
    bool            fRc;
    CAN_MSG         msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    tn_time_reset();

    cCurMsg = 0;
    pJ1939tc = j1939tc_Alloc();
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not alloc J1939CA" );
    pJ1939tc = j1939tc_Init( pJ1939tc, OBJ_NIL, xmtHandler, NULL );
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not init J1939CA" );
    if (pJ1939tc) {
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        tn_time_bump(250);
        // Send "Timed Out".
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        STAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pJ1939tc->super.cs), @"" );
        
        // Setup up msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0x23;         // Not Sure what this is! lol
        data[2] = 0x00;
        canmsg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939tc, pdu.eid, &msg );
        STAssertTrue( (4 == cCurMsg), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-2]);
        STAssertTrue( (0x18E80329 == pdu.eid), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        STAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pJ1939tc);
        pJ1939tc = OBJ_NIL;
    }
    
    j1939_SharedReset( );
    canbase_SharedReset( );
}



- (void)testCheck_RequestBadNameGlobal
{
    J1939TC_DATA    *pJ1939tc = NULL;
    bool            fRc;
    CAN_MSG         msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    tn_time_reset();

    cCurMsg = 0;
    pJ1939tc = j1939tc_Alloc();
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not alloc J1939CA" );
    pJ1939tc = j1939tc_Init( pJ1939tc, OBJ_NIL, xmtHandler, NULL );
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not init J1939CA" );
    if (pJ1939tc) {
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        tn_time_bump(250);
        // Send "Timed Out".
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        STAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pJ1939tc->super.cs), @"" );
        
        // Setup up msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;
        pdu.PS = 255;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0x23;         // Not Sure what this is! lol
        data[2] = 0x00;
        canmsg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939tc, pdu.eid, &msg );
        // It will not nak since we asked globablly.
        STAssertTrue( (3 == cCurMsg), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        STAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pJ1939tc);
        pJ1939tc = OBJ_NIL;
    }
    
    j1939_SharedReset( );
    canbase_SharedReset( );
}



- (void)testCheck_RequestIRC1Direct
{
    J1939TC_DATA    *pJ1939tc = NULL;
    bool            fRc;
    CAN_MSG         msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    tn_time_reset();
    cCurMsg = 0;

    pJ1939tc = j1939tc_Alloc();
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not alloc J1939CA" );
    pJ1939tc = j1939tc_Init( pJ1939tc, OBJ_NIL, xmtHandler, NULL );
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not init J1939CA" );
    if (pJ1939tc) {
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        tn_time_bump(250);
        // Send "Timed Out".
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        STAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pJ1939tc->super.cs), @"" );
        
        // Setup up msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // IRC1 PGN
        data[1] = 240;
        data[2] = 0x00;
        canmsg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939tc, pdu.eid, &msg );
        STAssertTrue( (4 == cCurMsg), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-2]);
        STAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        STAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pJ1939tc);
        pJ1939tc = OBJ_NIL;
    }
    
    j1939_SharedReset( );
    canbase_SharedReset( );
}



- (void)testCheck_TimedIRC1
{
    J1939TC_DATA    *pJ1939tc = NULL;
    bool            fRc;
    J1939_PDU       pdu;
    
    tn_time_reset();
    cCurMsg = 0;

    pJ1939tc = j1939tc_Alloc();
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not alloc J1939CA" );
    pJ1939tc = j1939tc_Init( pJ1939tc, OBJ_NIL, xmtHandler, NULL );
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not init J1939CA" );
    if (pJ1939tc) {
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        tn_time_bump(250);
        // Send "Timed Out".
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        STAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pJ1939tc->super.cs), @"" );
        
        for (int i=0; i<200; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939tc, 0, NULL );
        }        

        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        STAssertTrue( (3 == cCurMsg), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        STAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pJ1939tc);
        pJ1939tc = OBJ_NIL;
    }
    
    j1939_SharedReset( );
    canbase_SharedReset( );
}



- (void)testCheck_TSC1_Direct_Clean
{
    J1939TC_DATA    *pJ1939tc = NULL;
    bool            fRc;
    CAN_MSG         msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    tn_time_reset();
    cCurMsg = 0;

    pJ1939tc = j1939tc_Alloc();
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not alloc J1939CA" );
    pJ1939tc = j1939tc_Init( pJ1939tc, OBJ_NIL, xmtHandler, NULL );
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not init J1939CA" );
    if (pJ1939tc) {
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        tn_time_bump(250);
        // Send "Timed Out".
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        STAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pJ1939tc->super.cs), @"" );
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 2;                // Brake
        //data[1] = 240;
        //data[2] = 0x00;
        canmsg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939tc, pdu.eid, &msg );
        STAssertTrue( (true == pJ1939tc->fActive), @"" );
        STAssertTrue( (3 == pJ1939tc->spn1482), @"" );

        for (int i=0; i<100; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939tc, 0, NULL );
        }
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // Disable Brake
        //data[1] = 240;
        //data[2] = 0x00;
        canmsg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939tc, pdu.eid, &msg );
        STAssertTrue( (false == pJ1939tc->fActive), @"" );
        STAssertTrue( (255 == pJ1939tc->spn1482), @"" );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        STAssertTrue( (5 == cCurMsg), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-2]);
        STAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        STAssertTrue( (0x0C002903 == pdu.eid), @"Result was false!" );
        
        obj_Release(pJ1939tc);
        pJ1939tc = OBJ_NIL;
    }
    
    j1939_SharedReset( );
    canbase_SharedReset( );
}



- (void)testCheck_TSC1_Direct_Timeout
{
    J1939TC_DATA    *pJ1939tc = NULL;
    bool            fRc;
    CAN_MSG         msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    tn_time_reset();
    cCurMsg = 0;
    
    pJ1939tc = j1939tc_Alloc();
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not alloc J1939CA" );
    pJ1939tc = j1939tc_Init( pJ1939tc, OBJ_NIL, xmtHandler, NULL );
    STAssertFalse( (OBJ_NIL == pJ1939tc), @"Could not init J1939CA" );
    if (pJ1939tc) {
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        tn_time_bump(250);
        // Send "Timed Out".
        fRc = j1939ca_HandlePgn60928((J1939CA_DATA *)pJ1939tc, 0, NULL);
        STAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pJ1939tc->super.cs), @"" );
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 2;                // Brake
        //data[1] = 240;
        //data[2] = 0x00;
        canmsg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939tc, pdu.eid, &msg );
        STAssertTrue( (true == pJ1939tc->fActive), @"" );
        STAssertTrue( (3 == pJ1939tc->spn1482), @"" );
        
        for (int i=0; i<200; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939tc, 0, NULL );
        }
        
#ifdef XYZZY
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // Disable Brake
        //data[1] = 240;
        //data[2] = 0x00;
        canmsg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pJ1939tc, pdu.eid, &msg );
#endif
        STAssertTrue( (false == pJ1939tc->fActive), @"" );
        STAssertTrue( (255 == pJ1939tc->spn1482), @"" );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        STAssertTrue( (5 == cCurMsg), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-2]);
        STAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        pdu = canmsg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        STAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pJ1939tc);
        pJ1939tc = OBJ_NIL;
    }
    
    j1939_SharedReset( );
    canbase_SharedReset( );
}
#endif



@end



