/*
 * cmock_expectcall.h
 *
 *  Created on: 2016/6/14
 *      Author: emit.yanfeng@gmail.com
 */

#ifndef INCLUDE_CMOCK_EXPECTCALL_H_
#define INCLUDE_CMOCK_EXPECTCALL_H_

#include "cmock_dag.h"
#include "cmock_utility.h"
#include "cmock_testcase_ctx.h"


#define CMOCK_EXPECTCALL_RESULT_INIT        (0x00)
#define CMOCK_EXPECTCALL_RESULT_PENDING     (0x01)
#define CMOCK_EXPECTCALL_RESULT_MATCHED     (0x02)
#define CMOCK_EXPECTCALL_RESULT_FAILED      (0x03)
#define CMOCK_EXPECTCALL_RESULT_RETIRED     (0x04)



typedef struct __s_cmock_expect_call__ {
    char *funcSignature;
    char *expectVarName;
    int expectCalls;
    int called;
    int (*judgeExpectCalls)(int, int);
    int expectCallStatus;
    int sequenceNo;
    unsigned char ignore:1;
    unsigned char retireWhenMatched:1;
    unsigned char missmatch:1;
    void *mock;
} CMOCK_S_EXPECT_CALL;


/* configure a CMOCK_S_EXPECT_CALL structure */

/* expect calls */
static inline int cmock_expectcalls_eq(int expectCalls, int called) {
    if (called < expectCalls) {
        return CMOCK_EXPECTCALL_RESULT_PENDING;
    }else if (called == expectCalls) {
        return CMOCK_EXPECTCALL_RESULT_MATCHED;
    }else {
        return CMOCK_EXPECTCALL_RESULT_FAILED;
    }
}

#if 0
static inline int cmock_expectcalls_lt(int expectCalls, int called) {
    if (called < expectCalls) {
        return CMOCK_EXPECTCALL_RESULT_MATCHED;
    }else {
        return CMOCK_EXPECTCALL_RESULT_FAILED;
    }
}

static inline int cmock_expectcalls_gt(int expectCalls, int called) {
    if (called > expectCalls) {
        return CMOCK_EXPECTCALL_RESULT_MATCHED;
    }else {
        return CMOCK_EXPECTCALL_RESULT_FAILED;
    }
}
#endif

static inline int cmock_expectcalls_infinite(int expectCalls, int called) {
    return CMOCK_EXPECTCALL_RESULT_MATCHED;
}

static inline int cmock_expectcalls_never(int expectCalls, int called) {
    return CMOCK_EXPECTCALL_RESULT_FAILED;
}

#define CMOCK_EXPECTCALL_TIMES(funcname, var, func, expectCallTimes) \
    var.expectCalls = (expectCallTimes);\
    var.judgeExpectCalls = (func);\
    var.expectCallStatus = CMOCK_EXPECTCALL_RESULT_INIT;

#define CMOCK_EXPECTCALL_NEVER(funcname, var) \
    var.judgeExpectCalls = cmock_expectcalls_never;\
    var.expectCallStatus = CMOCK_EXPECTCALL_RESULT_MATCHED;

#define CMOCK_EXPECTCALL_INFINITE(funcname, var) \
    var.judgeExpectCalls = cmock_expectcalls_infinite;\
    var.expectCallStatus = CMOCK_EXPECTCALL_RESULT_MATCHED;


/* retire when matched */
#define CMOCK_EXPECTCALL_RETIRE_WHEN_MATCHED(funcname, var) \
    do { \
        var.retireWhenMatched = 1;\
    } while(0);


/* return value */
#define CMOCK_EXPECTCALL_RET(funcname, var, func) \
    do { \
        CMOCK_INTERNAL_MOCK_TYPE(funcname) *mock = var.mock;\
        mock->mockAction = (func);\
    } while(0);

#define CMOCK_EXPECTCALL_RET_VAL(funcname, var, val) \
    do { \
        CMOCK_INTERNAL_MOCK_TYPE(funcname) *mock = var.mock;\
        mock->defaultRetVal = (val);\
    } while(0);


/* expect input args */
#define CMOCK_EXPECTCALL_ARG_MATCHER(funcname, var, argNo, func) \
    do { \
        CMOCK_INTERNAL_MOCK_TYPE(funcname) *mock = var.mock;\
        mock->argValueMatcherCb##argNo = (func);\
    } while(0);

#define CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(funcname, var, argNo, val) \
    do { \
        CMOCK_INTERNAL_MOCK_TYPE(funcname) *mock = var.mock;\
        mock->inArgValue##argNo = (val);\
        mock->argValueMatcherCb##argNo = cmock_internal_matcher_##funcname##_val_eq_arg##argNo;\
    } while(0);

#if 0
#define CMOCK_EXPECTCALL_ARG_MATCHER_REF_EQ(funcname, var, argNo, ref) \
    char __cmock_internal_matcher_##funcname##_ref_eq_arg##argNo( \
        typeof(((CMOCK_INTERNAL_MOCK_TYPE(funcname) *)0)->inArgValue##argNo) arg, \
        typeof(((CMOCK_INTERNAL_MOCK_TYPE(funcname) *)0)->inArgValue##argNo) __unused__) {\
            return (arg==(*ref));\
    };\
    do { \
        CMOCK_INTERNAL_MOCK_TYPE(funcname) *mock = var.mock;\
        mock->argValueMatcherCb##argNo = __cmock_internal_matcher_##funcname##_val_eq_arg##argNo;\
    } while(0);
#endif


/* create a new CMOCK_S_EXPECT_CALL structure and add to default dag */
#define CMOCK_EXPECTCALL_FUNCTION(funcname, var) \
    CMOCK_S_EXPECT_CALL var; \
    cmock_memset(&(var), 0, sizeof(CMOCK_S_EXPECT_CALL));\
    var.mock = (void *)CMOCK_ALLOC_MOCK_TYPE_STACK(funcname);\
    cmock_memset(var.mock, 0, sizeof(CMOCK_INTERNAL_MOCK_TYPE(funcname)));\
    var.funcSignature = #funcname;\
    var.expectVarName = #var;\
    var.sequenceNo = 0;\
    var.ignore = 0;\
    var.missmatch = 0;\
    do { \
        CMOCK_S_DAG_VERTEX *vertex;\
        CMOCK_S_EXPECT_CALL *missmatchedCallBuffer = CMOCK_ALLOC_STACK(CMOCK_S_EXPECT_CALL);\
        cmock_memcpy(missmatchedCallBuffer, &(var), sizeof(CMOCK_S_EXPECT_CALL));\
        vertex = CMOCK_ALLOC_STACK(CMOCK_S_DAG_VERTEX);\
        cmock_dag_path_add(g_cmock_ctx->missmatch_expect_head, vertex, (void *)(missmatchedCallBuffer));\
        vertex = CMOCK_ALLOC_STACK(CMOCK_S_DAG_VERTEX);\
        cmock_dag_path_add(g_cmock_ctx->defaulCMOCK_S_DAG_PATH_head, vertex, (void *)(&var));\
        CMOCK_EXPECTCALL_INFINITE(funcname, var);\
    } while(0);

/* create a new call sequence */
#define CMOCK_EXPECTCALL_SEQUENCE(var) \
    CMOCK_S_DAG_VERTEX var;\
    cmock_dag_path_init(&(var));\
    (var).data = (void *)#var;\
    do { \
        CMOCK_S_DAG_PATH *path = CMOCK_ALLOC_STACK(CMOCK_S_DAG_PATH);\
        cmock_dag_add(&g_cmock_ctx->seq_dag, path, &(var));\
    } while(0);\

/* add a CMOCK_S_EXPECT_CALL structure to a call sequence */
#define CMOCK_EXPECTCALL_ADD(sequnce, expection) \
    do { \
        CMOCK_S_DAG_VERTEX *vertex = CMOCK_ALLOC_STACK(CMOCK_S_DAG_VERTEX);\
        cmock_dag_path_add(&sequnce, vertex, (void *)(&expection));\
        expection.ignore = 1;\
    } while(0);


#endif /* INCLUDE_CMOCK_EXPECTCALL_H_ */
