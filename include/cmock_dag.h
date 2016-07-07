/*
 * cmock_dag.h
 *
 *  Created on: 2016/6/14
 *      Author: emit.yanfeng@gmail.com
 */

#ifndef INCLUDE_CMOCK_DAG_H_
#define INCLUDE_CMOCK_DAG_H_

#include "cmock_list.h"
#include "cmock_utility.h"

#define container_of(type, member, p) \
    (type *)((char *)(p)-cmock_offsetof(type, member))

typedef struct {
    CMOCK_S_LIST_NODE edge;
    void *data;
} CMOCK_S_DAG_VERTEX;


typedef struct {
    CMOCK_S_LIST_NODE path_node;
    CMOCK_S_DAG_VERTEX *path_head;
} CMOCK_S_DAG_PATH;



static inline void cmock_dag_path_init(CMOCK_S_DAG_VERTEX *head) {
    cmock_list_init(&head->edge);
    head->data = NULL;
}

static inline void cmock_dag_path_add(CMOCK_S_DAG_VERTEX *head, CMOCK_S_DAG_VERTEX *vertex, void *data) {
    cmock_list_insert_tail(&vertex->edge, &head->edge);
    vertex->data = data;
}

static inline void cmock_dag_init(CMOCK_S_DAG_PATH *head) {
    cmock_list_init(&head->path_node);
    head->path_head = NULL;
}

static inline void cmock_dag_add(CMOCK_S_DAG_PATH *head, CMOCK_S_DAG_PATH *node, CMOCK_S_DAG_VERTEX *path_head) {
    cmock_list_insert_tail(&node->path_node, &head->path_node);
    node->path_head = path_head;
}


#define DAG_FOREACH(pHead, pPathHead) \
    CMOCK_S_LIST_NODE *$(pNode), *$(pTmp);\
    cmock_list_for_each_ext(&(pHead)->path_node, $(pNode), $(pTmp), pPathHead = (container_of(CMOCK_S_DAG_PATH, path_node, $(pNode)))->path_head)


#define DAG_PATH_FOREACH(pPathHead, pExpectCall) \
    CMOCK_S_LIST_NODE *$(pNode), *$(pTmp);\
    cmock_list_for_each_ext(&(pPathHead)->edge, $(pNode), $(pTmp), pExpectCall = (container_of(CMOCK_S_DAG_VERTEX, edge, $(pNode)))->data)


#define DAG_MAP(head, func, userdata) \
    do { \
        CMOCK_S_LIST_NODE *$(pNode1), *$(pNode2), *$(pTmp1), *$(pTmp2);\
        CMOCK_S_DAG_PATH *$(path);\
        CMOCK_S_DAG_VERTEX *$(path_head), *$(vertex);\
        void *$(data);\
        cmock_list_for_each(&(head)->path_node, $(pNode1), $(pTmp1)) { \
            $(path) = container_of(CMOCK_S_DAG_PATH, path_node, $(pNode1));\
            $(path_head) = $(path)->path_head; \
            printf("path_head=%p\n", $(path_head));\
            cmock_list_for_each(&($(path_head)->edge), $(pNode2), $(pTmp2)) { \
                $(vertex) = container_of(CMOCK_S_DAG_VERTEX, edge, $(pNode2));\
                $(data) = $(vertex)->data;\
                printf("data=%p\n", $(data));\
                func($(data), (userdata));\
            }\
        } \
    } while(0);

#endif /* INCLUDE_CMOCK_DAG_H_ */
