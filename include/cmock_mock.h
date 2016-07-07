/*
 * cmock_mock.h
 *
 *  Created on: 2016/6/14
 *      Author: emit.yanfeng@gmail.com
 */

#ifndef INCLUDE_CMOCK_MOCK_H_
#define INCLUDE_CMOCK_MOCK_H_

#include "cmock_testcase_ctx.h"
#include "cmock_expectcall.h"




#define CMOCK_NORET_FUNC0(_functionName, void)  \
    \
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
         \
        \
        void  (*mockAction)();\
         \
    }; \
    void _functionName() { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        \
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction();\
    }





#define CMOCK_FUNC0(_functionName, _retType)  \
    \
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
         \
        \
        _retType (*mockAction)();\
        _retType defaultRetVal; \
    }; \
    _retType _functionName() { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        \
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction();\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC1(_functionName, void, argType1)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1;  \
        char (*argValueMatcherCb1)(argType1, argType1); \
        void  (*mockAction)(argType1);\
         \
    }; \
    void _functionName(argType1 arg1) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1);\
    }





#define CMOCK_FUNC1(_functionName, _retType, argType1)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1;  \
        char (*argValueMatcherCb1)(argType1, argType1); \
        _retType (*mockAction)(argType1);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC2(_functionName, void, argType1, argType2)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); \
        void  (*mockAction)(argType1,argType2);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2);\
    }





#define CMOCK_FUNC2(_functionName, _retType, argType1, argType2)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); \
        _retType (*mockAction)(argType1,argType2);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC3(_functionName, void, argType1, argType2, argType3)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); \
        void  (*mockAction)(argType1,argType2,argType3);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3);\
    }





#define CMOCK_FUNC3(_functionName, _retType, argType1, argType2, argType3)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); \
        _retType (*mockAction)(argType1,argType2,argType3);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC4(_functionName, void, argType1, argType2, argType3, argType4)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); \
        void  (*mockAction)(argType1,argType2,argType3,argType4);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4);\
    }





#define CMOCK_FUNC4(_functionName, _retType, argType1, argType2, argType3, argType4)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC5(_functionName, void, argType1, argType2, argType3, argType4, argType5)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5);\
    }





#define CMOCK_FUNC5(_functionName, _retType, argType1, argType2, argType3, argType4, argType5)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC6(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6);\
    }





#define CMOCK_FUNC6(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC7(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7);\
    }





#define CMOCK_FUNC7(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC8(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8);\
    }





#define CMOCK_FUNC8(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC9(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9);\
    }





#define CMOCK_FUNC9(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC10(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10);\
    }





#define CMOCK_FUNC10(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC11(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11);\
    }





#define CMOCK_FUNC11(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC12(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12);\
    }





#define CMOCK_FUNC12(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC13(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13);\
    }





#define CMOCK_FUNC13(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC14(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14);\
    }





#define CMOCK_FUNC14(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC15(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14, argType15)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg15(argType15 arg, argType15 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14; argType15 inArgValue15;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); char (*argValueMatcherCb15)(argType15, argType15); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14,argType15);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14,argType15 arg15) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb15) {\
                            if(!pMock->argValueMatcherCb15(arg15, pMock->inArgValue15)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15);\
    }





#define CMOCK_FUNC15(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14, argType15)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg15(argType15 arg, argType15 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14; argType15 inArgValue15;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); char (*argValueMatcherCb15)(argType15, argType15); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14,argType15);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14,argType15 arg15) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb15) {\
                            if(!pMock->argValueMatcherCb15(arg15, pMock->inArgValue15)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC16(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14, argType15, argType16)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg15(argType15 arg, argType15 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg16(argType16 arg, argType16 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14; argType15 inArgValue15; argType16 inArgValue16;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); char (*argValueMatcherCb15)(argType15, argType15); char (*argValueMatcherCb16)(argType16, argType16); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14,argType15,argType16);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14,argType15 arg15,argType16 arg16) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb15) {\
                            if(!pMock->argValueMatcherCb15(arg15, pMock->inArgValue15)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb16) {\
                            if(!pMock->argValueMatcherCb16(arg16, pMock->inArgValue16)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16);\
    }





#define CMOCK_FUNC16(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14, argType15, argType16)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg15(argType15 arg, argType15 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg16(argType16 arg, argType16 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14; argType15 inArgValue15; argType16 inArgValue16;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); char (*argValueMatcherCb15)(argType15, argType15); char (*argValueMatcherCb16)(argType16, argType16); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14,argType15,argType16);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14,argType15 arg15,argType16 arg16) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb15) {\
                            if(!pMock->argValueMatcherCb15(arg15, pMock->inArgValue15)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb16) {\
                            if(!pMock->argValueMatcherCb16(arg16, pMock->inArgValue16)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC17(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14, argType15, argType16, argType17)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg15(argType15 arg, argType15 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg16(argType16 arg, argType16 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg17(argType17 arg, argType17 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14; argType15 inArgValue15; argType16 inArgValue16; argType17 inArgValue17;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); char (*argValueMatcherCb15)(argType15, argType15); char (*argValueMatcherCb16)(argType16, argType16); char (*argValueMatcherCb17)(argType17, argType17); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14,argType15,argType16,argType17);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14,argType15 arg15,argType16 arg16,argType17 arg17) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb15) {\
                            if(!pMock->argValueMatcherCb15(arg15, pMock->inArgValue15)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb16) {\
                            if(!pMock->argValueMatcherCb16(arg16, pMock->inArgValue16)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb17) {\
                            if(!pMock->argValueMatcherCb17(arg17, pMock->inArgValue17)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16,arg17);\
    }





#define CMOCK_FUNC17(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14, argType15, argType16, argType17)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg15(argType15 arg, argType15 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg16(argType16 arg, argType16 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg17(argType17 arg, argType17 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14; argType15 inArgValue15; argType16 inArgValue16; argType17 inArgValue17;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); char (*argValueMatcherCb15)(argType15, argType15); char (*argValueMatcherCb16)(argType16, argType16); char (*argValueMatcherCb17)(argType17, argType17); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14,argType15,argType16,argType17);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14,argType15 arg15,argType16 arg16,argType17 arg17) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb15) {\
                            if(!pMock->argValueMatcherCb15(arg15, pMock->inArgValue15)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb16) {\
                            if(!pMock->argValueMatcherCb16(arg16, pMock->inArgValue16)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb17) {\
                            if(!pMock->argValueMatcherCb17(arg17, pMock->inArgValue17)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16,arg17);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC18(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14, argType15, argType16, argType17, argType18)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg15(argType15 arg, argType15 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg16(argType16 arg, argType16 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg17(argType17 arg, argType17 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg18(argType18 arg, argType18 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14; argType15 inArgValue15; argType16 inArgValue16; argType17 inArgValue17; argType18 inArgValue18;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); char (*argValueMatcherCb15)(argType15, argType15); char (*argValueMatcherCb16)(argType16, argType16); char (*argValueMatcherCb17)(argType17, argType17); char (*argValueMatcherCb18)(argType18, argType18); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14,argType15,argType16,argType17,argType18);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14,argType15 arg15,argType16 arg16,argType17 arg17,argType18 arg18) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb15) {\
                            if(!pMock->argValueMatcherCb15(arg15, pMock->inArgValue15)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb16) {\
                            if(!pMock->argValueMatcherCb16(arg16, pMock->inArgValue16)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb17) {\
                            if(!pMock->argValueMatcherCb17(arg17, pMock->inArgValue17)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb18) {\
                            if(!pMock->argValueMatcherCb18(arg18, pMock->inArgValue18)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16,arg17,arg18);\
    }





#define CMOCK_FUNC18(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14, argType15, argType16, argType17, argType18)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg15(argType15 arg, argType15 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg16(argType16 arg, argType16 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg17(argType17 arg, argType17 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg18(argType18 arg, argType18 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14; argType15 inArgValue15; argType16 inArgValue16; argType17 inArgValue17; argType18 inArgValue18;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); char (*argValueMatcherCb15)(argType15, argType15); char (*argValueMatcherCb16)(argType16, argType16); char (*argValueMatcherCb17)(argType17, argType17); char (*argValueMatcherCb18)(argType18, argType18); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14,argType15,argType16,argType17,argType18);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14,argType15 arg15,argType16 arg16,argType17 arg17,argType18 arg18) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb15) {\
                            if(!pMock->argValueMatcherCb15(arg15, pMock->inArgValue15)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb16) {\
                            if(!pMock->argValueMatcherCb16(arg16, pMock->inArgValue16)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb17) {\
                            if(!pMock->argValueMatcherCb17(arg17, pMock->inArgValue17)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb18) {\
                            if(!pMock->argValueMatcherCb18(arg18, pMock->inArgValue18)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16,arg17,arg18);\
        else return pMock->defaultRetVal;\
    }





#define CMOCK_NORET_FUNC19(_functionName, void, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14, argType15, argType16, argType17, argType18, argType19)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg15(argType15 arg, argType15 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg16(argType16 arg, argType16 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg17(argType17 arg, argType17 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg18(argType18 arg, argType18 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg19(argType19 arg, argType19 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14; argType15 inArgValue15; argType16 inArgValue16; argType17 inArgValue17; argType18 inArgValue18; argType19 inArgValue19;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); char (*argValueMatcherCb15)(argType15, argType15); char (*argValueMatcherCb16)(argType16, argType16); char (*argValueMatcherCb17)(argType17, argType17); char (*argValueMatcherCb18)(argType18, argType18); char (*argValueMatcherCb19)(argType19, argType19); \
        void  (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14,argType15,argType16,argType17,argType18,argType19);\
         \
    }; \
    void _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14,argType15 arg15,argType16 arg16,argType17 arg17,argType18 arg18,argType19 arg19) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb15) {\
                            if(!pMock->argValueMatcherCb15(arg15, pMock->inArgValue15)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb16) {\
                            if(!pMock->argValueMatcherCb16(arg16, pMock->inArgValue16)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb17) {\
                            if(!pMock->argValueMatcherCb17(arg17, pMock->inArgValue17)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb18) {\
                            if(!pMock->argValueMatcherCb18(arg18, pMock->inArgValue18)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb19) {\
                            if(!pMock->argValueMatcherCb19(arg19, pMock->inArgValue19)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return ;\
        lable_matched:\
        if(pMock->mockAction) pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16,arg17,arg18,arg19);\
    }





#define CMOCK_FUNC19(_functionName, _retType, argType1, argType2, argType3, argType4, argType5, argType6, argType7, argType8, argType9, argType10, argType11, argType12, argType13, argType14, argType15, argType16, argType17, argType18, argType19)  \
    char cmock_internal_matcher_##_functionName##_val_eq_arg1(argType1 arg, argType1 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg2(argType2 arg, argType2 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg3(argType3 arg, argType3 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg4(argType4 arg, argType4 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg5(argType5 arg, argType5 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg6(argType6 arg, argType6 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg7(argType7 arg, argType7 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg8(argType8 arg, argType8 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg9(argType9 arg, argType9 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg10(argType10 arg, argType10 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg11(argType11 arg, argType11 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg12(argType12 arg, argType12 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg13(argType13 arg, argType13 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg14(argType14 arg, argType14 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg15(argType15 arg, argType15 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg16(argType16 arg, argType16 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg17(argType17 arg, argType17 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg18(argType18 arg, argType18 expect) {\
        return (arg==expect);\
    }char cmock_internal_matcher_##_functionName##_val_eq_arg19(argType19 arg, argType19 expect) {\
        return (arg==expect);\
    }\
    typedef struct _T_CMOCK_INTERNAL_##_functionName CMOCK_INTERNAL_MOCK_TYPE(_functionName);\
    struct _T_CMOCK_INTERNAL_##_functionName{ \
        argType1 inArgValue1; argType2 inArgValue2; argType3 inArgValue3; argType4 inArgValue4; argType5 inArgValue5; argType6 inArgValue6; argType7 inArgValue7; argType8 inArgValue8; argType9 inArgValue9; argType10 inArgValue10; argType11 inArgValue11; argType12 inArgValue12; argType13 inArgValue13; argType14 inArgValue14; argType15 inArgValue15; argType16 inArgValue16; argType17 inArgValue17; argType18 inArgValue18; argType19 inArgValue19;  \
        char (*argValueMatcherCb1)(argType1, argType1); char (*argValueMatcherCb2)(argType2, argType2); char (*argValueMatcherCb3)(argType3, argType3); char (*argValueMatcherCb4)(argType4, argType4); char (*argValueMatcherCb5)(argType5, argType5); char (*argValueMatcherCb6)(argType6, argType6); char (*argValueMatcherCb7)(argType7, argType7); char (*argValueMatcherCb8)(argType8, argType8); char (*argValueMatcherCb9)(argType9, argType9); char (*argValueMatcherCb10)(argType10, argType10); char (*argValueMatcherCb11)(argType11, argType11); char (*argValueMatcherCb12)(argType12, argType12); char (*argValueMatcherCb13)(argType13, argType13); char (*argValueMatcherCb14)(argType14, argType14); char (*argValueMatcherCb15)(argType15, argType15); char (*argValueMatcherCb16)(argType16, argType16); char (*argValueMatcherCb17)(argType17, argType17); char (*argValueMatcherCb18)(argType18, argType18); char (*argValueMatcherCb19)(argType19, argType19); \
        _retType (*mockAction)(argType1,argType2,argType3,argType4,argType5,argType6,argType7,argType8,argType9,argType10,argType11,argType12,argType13,argType14,argType15,argType16,argType17,argType18,argType19);\
        _retType defaultRetVal; \
    }; \
    _retType _functionName(argType1 arg1,argType2 arg2,argType3 arg3,argType4 arg4,argType5 arg5,argType6 arg6,argType7 arg7,argType8 arg8,argType9 arg9,argType10 arg10,argType11 arg11,argType12 arg12,argType13 arg13,argType14 arg14,argType15 arg15,argType16 arg16,argType17 arg17,argType18 arg18,argType19 arg19) { \
        const char *funcSignature = __func__;\
        char *sequenceVarName;\
        CMOCK_S_DAG_VERTEX *pPathHead;\
        CMOCK_S_EXPECT_CALL *pExpectCall;\
        CMOCK_INTERNAL_MOCK_TYPE(_functionName) *pMock;\
        CMOCK_S_DAG_PATH *dag_heads[] = {&g_cmock_ctx->seq_dag, &g_cmock_ctx->default_dag};\
        int i;\
        for(i=0; i<sizeof(dag_heads)/sizeof(dag_heads[0]); i++) {\
            DAG_FOREACH(dag_heads[i], pPathHead) {\
	            if(dag_heads[i] == &g_cmock_ctx->default_dag) sequenceVarName = "None";\
	            else sequenceVarName = (char *)pPathHead->data;\
                DAG_PATH_FOREACH(pPathHead, pExpectCall){\
                    pMock = (CMOCK_INTERNAL_MOCK_TYPE(_functionName) *)(pExpectCall->mock);\
                    if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                        if(pExpectCall->expectCallStatus == CMOCK_EXPECTCALL_RESULT_RETIRED) goto lable_continue;\
                        if(pMock->argValueMatcherCb1) {\
                            if(!pMock->argValueMatcherCb1(arg1, pMock->inArgValue1)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb2) {\
                            if(!pMock->argValueMatcherCb2(arg2, pMock->inArgValue2)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb3) {\
                            if(!pMock->argValueMatcherCb3(arg3, pMock->inArgValue3)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb4) {\
                            if(!pMock->argValueMatcherCb4(arg4, pMock->inArgValue4)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb5) {\
                            if(!pMock->argValueMatcherCb5(arg5, pMock->inArgValue5)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb6) {\
                            if(!pMock->argValueMatcherCb6(arg6, pMock->inArgValue6)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb7) {\
                            if(!pMock->argValueMatcherCb7(arg7, pMock->inArgValue7)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb8) {\
                            if(!pMock->argValueMatcherCb8(arg8, pMock->inArgValue8)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb9) {\
                            if(!pMock->argValueMatcherCb9(arg9, pMock->inArgValue9)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb10) {\
                            if(!pMock->argValueMatcherCb10(arg10, pMock->inArgValue10)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb11) {\
                            if(!pMock->argValueMatcherCb11(arg11, pMock->inArgValue11)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb12) {\
                            if(!pMock->argValueMatcherCb12(arg12, pMock->inArgValue12)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb13) {\
                            if(!pMock->argValueMatcherCb13(arg13, pMock->inArgValue13)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb14) {\
                            if(!pMock->argValueMatcherCb14(arg14, pMock->inArgValue14)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb15) {\
                            if(!pMock->argValueMatcherCb15(arg15, pMock->inArgValue15)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb16) {\
                            if(!pMock->argValueMatcherCb16(arg16, pMock->inArgValue16)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb17) {\
                            if(!pMock->argValueMatcherCb17(arg17, pMock->inArgValue17)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb18) {\
                            if(!pMock->argValueMatcherCb18(arg18, pMock->inArgValue18)) goto lable_continue;\
                        }if(pMock->argValueMatcherCb19) {\
                            if(!pMock->argValueMatcherCb19(arg19, pMock->inArgValue19)) goto lable_continue;\
                        }\
                        if(dag_heads[i] == &g_cmock_ctx->seq_dag) \
                            if(!pExpectCall->sequenceNo) \
                                pExpectCall->sequenceNo = ++g_cmock_ctx->curSequenceNo;\
                        pExpectCall->expectCallStatus = pExpectCall->judgeExpectCalls(pExpectCall->expectCalls, ++pExpectCall->called);\
                        switch(pExpectCall->expectCallStatus) {\
                        case CMOCK_EXPECTCALL_RESULT_MATCHED:\
                        if(pExpectCall->retireWhenMatched) pExpectCall->expectCallStatus = CMOCK_EXPECTCALL_RESULT_RETIRED;\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_PENDING:\
                        case CMOCK_EXPECTCALL_RESULT_FAILED:\
                        goto lable_matched;\
                        break;\
                        case CMOCK_EXPECTCALL_RESULT_RETIRED:\
                        goto lable_continue;\
                        break;\
                        default:\
                        cmock_ctx_fprintf(stderr, "<FATAL ERROR> Expect(%s) call of function(%s) in sequence(%s) fatal error, called times matcher callback should not return %d, abort!\n", \
                                pExpectCall->expectVarName, pExpectCall->funcSignature, sequenceVarName, pExpectCall->expectCallStatus);\
                        cmock_exit(1);\
                        break;\
                        }\
                    }\
                    lable_continue:\
                    continue;\
                }\
            }\
        }\
        do{\
            DAG_PATH_FOREACH(g_cmock_ctx->missmatch_expect_head, pExpectCall){\
                if(cmock_strcmp(funcSignature, pExpectCall->funcSignature) == 0) {\
                    pExpectCall->missmatch = 1;\
                }\
            }\
        } while(0);\
        return *(CMOCK_ALLOC_STACK(_retType));\
        lable_matched:\
        if(pMock->mockAction) return pMock->mockAction(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16,arg17,arg18,arg19);\
        else return pMock->defaultRetVal;\
    }




#endif /* INCLUDE_CMOCK_MOCK_H_ */