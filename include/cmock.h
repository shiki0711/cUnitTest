/*
 * cmock.h
 *
 *  Created on: 2016/6/14
 *      Author: emit.yanfeng@gmail.com
 */

#ifndef INCLUDE_CMOCK_H_
#define INCLUDE_CMOCK_H_

#include "cmock_list.h"
#include "cmock_utility.h"


#define CMOCK_TESTCASE_FUNCTION_NAME(_testCaseName, _testName) \
    _##_testCaseName##_##_testName##_Test


/* test main */
#define CMOCK_TEST_MAIN \
CMOCK_S_TESTCASE_CTX *g_cmock_ctx = CMOCK_ALLOC_STACK(CMOCK_S_TESTCASE_CTX);\
void cmock_process_expext_call(void *expect, void *data) {\
    \
}\
int main(int argc, const char* argv[])



#define CMOCK_TESTCASE(_testCaseName, _testName) \
void CMOCK_TESTCASE_FUNCTION_NAME(_testCaseName, _testName)(void) { \
    CMOCK_TESTCASE_CTX_INIT(_testCaseName, _testName); \
    cmock_ctx_fprintf(stderr, "========Test start========\n");\
    do

#define CMOCK_TESTCASE_END \
    while(0);\
    int err = 0;\
    const char *sequenceVarName;\
    T_DAG_VERTEX *pPathHead;\
    CMOCK_S_EXPECT_CALL *pExpectCallPrev,*pExpectCall;\
    T_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
    int i;\
    for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
        DAG_FOREACH(dag_heads[i], pPathHead) {\
            sequenceVarName = (const char *)pPathHead->data;\
            pExpectCallPrev = NULL;\
            DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                if((dag_heads[i] == &g_cmock_ctx->default_dag) && pExpectCall->ignore) continue;\
                if((dag_heads[i] == &g_cmock_ctx->seq_dag) && pExpectCallPrev && pExpectCallPrev->sequenceNo > pExpectCall->sequenceNo) {\
                    cmock_ctx_fprintf(stderr, "<SEQUENCE ERROR> Expect sequence(%s) error, Expect(%s) call of function(%s) called After Expect(%s) call of function(%s)\n", \
                            sequenceVarName, pExpectCallPrev->expectVarName, pExpectCallPrev->funcSignature, \
                            pExpectCall->expectVarName, pExpectCall->funcSignature);\
                    err++;\
                }\
                switch(pExpectCall->expectCallStatus) {\
                case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                break;\
                case CMOCK_EXPECTCALL_RESULT_FAILED:\
                cmock_ctx_fprintf(stderr, "<CALL TIMES ERROR> Expect(%s) call of function(%s) in sequence(%s) error, called times(%d) not matched\n", \
                        pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->called);\
                err++;\
                break;\
                case CMOCK_EXPECTCALL_RESULT_INIT:\
                case CMOCK_EXPECTCALL_RESULT_PENDING:\
                cmock_ctx_fprintf(stderr, "<EXPECTATION ERROR> Expect(%s) call of function(%s) in sequence(%s) error, called times(%d) or argument matcher still not satisfied\n", \
                        pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->called);\
                err++;\
                break;\
                default:\
                cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) internal error(Times: %d)\n", \
                        pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->called);\
                err++;\
                break;\
                }\
                pExpectCallPrev = pExpectCall;\
            }\
        }\
    }\
    do{\
        DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
            if(pExpectCall->missmatch) {\
                cmock_ctx_fprintf(stderr, "<MISSMATCH ERROR> Unexpected function call: %s\n", pExpectCall->funcSignature);\
                err++;\
            }\
        }\
    } while(0);\
    if(!err) \
        cmock_ctx_fprintf(stderr, "<OK>, all expectations was satisfied!\n");\
    else \
        cmock_ctx_fprintf(stderr, "<FAIL>, Missmatched function call or sequence!\n");\
    cmock_ctx_fprintf(stderr, "========Test end========\n\n");\
}\


#define CMOCK_RUN_TESTCASE(_testCaseName, _testName) \
    CMOCK_TESTCASE_FUNCTION_NAME(_testCaseName, _testName)();


#endif /* INCLUDE_CMOCK_H_ */
