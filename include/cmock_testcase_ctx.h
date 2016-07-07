/*
 * cmock_testcase_ctx.h
 *
 *  Created on: 2016/6/14
 *      Author: emit.yanfeng@gmail.com
 */

#ifndef INCLUDE_CMOCK_TESTCASE_CTX_H_
#define INCLUDE_CMOCK_TESTCASE_CTX_H_

#include "cmock_dag.h"
#include "cmock_utility.h"

typedef struct {
    CMOCK_S_DAG_PATH seq_dag;
    CMOCK_S_DAG_PATH default_dag;
    CMOCK_S_DAG_VERTEX *defaulCMOCK_S_DAG_PATH_head;
    CMOCK_S_DAG_VERTEX *missmatch_expect_head;
    int curSequenceNo;
    const char* testCaseName;
    const char* testName;
} CMOCK_S_TESTCASE_CTX;

#define CMOCK_TESTCASE_CTX_INIT(_testCaseName, _testName) \
    cmock_dag_init(&g_cmock_ctx->seq_dag);\
    cmock_dag_init(&g_cmock_ctx->default_dag);\
    do { \
        CMOCK_S_DAG_PATH *path = CMOCK_ALLOC_STACK(CMOCK_S_DAG_PATH);\
        CMOCK_S_DAG_VERTEX *edge_head = CMOCK_ALLOC_STACK(CMOCK_S_DAG_VERTEX);\
        cmock_dag_path_init(edge_head);\
        cmock_dag_add(&g_cmock_ctx->default_dag, path, edge_head);\
        g_cmock_ctx->defaulCMOCK_S_DAG_PATH_head = edge_head;\
    } while(0);\
    g_cmock_ctx->missmatch_expect_head = CMOCK_ALLOC_STACK(CMOCK_S_DAG_VERTEX);\
    cmock_dag_path_init(g_cmock_ctx->missmatch_expect_head);\
    g_cmock_ctx->curSequenceNo = 0;\
    g_cmock_ctx->testCaseName = #_testCaseName;\
    g_cmock_ctx->testName = #_testName;

extern CMOCK_S_TESTCASE_CTX *g_cmock_ctx;

#define cmock_ctx_fprintf(stream, fmt, ...) \
    cmock_fprintf(stream, "CMOCK [%s] [%s]: "fmt, g_cmock_ctx->testCaseName, g_cmock_ctx->testName, ## __VA_ARGS__)

#endif /* INCLUDE_CMOCK_TESTCASE_CTX_H_ */
