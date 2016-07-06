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

typedef struct S_DAG_VERTEX {
    T_LIST_NODE edge;
    void *data;
} T_DAG_VERTEX;


typedef struct S_DAG_PATH {
    T_LIST_NODE path_node;
    T_DAG_VERTEX *path_head;
} T_DAG_PATH;



static inline void dag_path_init(T_DAG_VERTEX *head) {
    list_init(&head->edge);
    head->data = NULL;
}

static inline void dag_path_add(T_DAG_VERTEX *head, T_DAG_VERTEX *vertex, void *data) {
    list_insert_tail(&vertex->edge, &head->edge);
    vertex->data = data;
}

static inline void dag_init(T_DAG_PATH *head) {
    list_init(&head->path_node);
    head->path_head = NULL;
}

static inline void dag_add(T_DAG_PATH *head, T_DAG_PATH *node, T_DAG_VERTEX *path_head) {
    list_insert_tail(&node->path_node, &head->path_node);
    node->path_head = path_head;
}


#define DAG_FOREACH(pHead, pPathHead) \
    T_LIST_NODE *$(pNode), *$(pTmp);\
    list_for_each_ext(&(pHead)->path_node, $(pNode), $(pTmp), pPathHead = (container_of(T_DAG_PATH, path_node, $(pNode)))->path_head)


#define DAG_PATH_FOREACH(pPathHead, pExpectCall) \
    T_LIST_NODE *$(pNode), *$(pTmp);\
    list_for_each_ext(&(pPathHead)->edge, $(pNode), $(pTmp), pExpectCall = (container_of(T_DAG_VERTEX, edge, $(pNode)))->data)


#define DAG_MAP(head, func, userdata) \
    do { \
        T_LIST_NODE *$(pNode1), *$(pNode2), *$(pTmp1), *$(pTmp2);\
        T_DAG_PATH *$(path);\
        T_DAG_VERTEX *$(path_head), *$(vertex);\
        void *$(data);\
        list_for_each(&(head)->path_node, $(pNode1), $(pTmp1)) { \
            $(path) = container_of(T_DAG_PATH, path_node, $(pNode1));\
            $(path_head) = $(path)->path_head; \
            printf("path_head=%p\n", $(path_head));\
            list_for_each(&($(path_head)->edge), $(pNode2), $(pTmp2)) { \
                $(vertex) = container_of(T_DAG_VERTEX, edge, $(pNode2));\
                $(data) = $(vertex)->data;\
                printf("data=%p\n", $(data));\
                func($(data), (userdata));\
            }\
        } \
    } while(0);

#endif /* INCLUDE_CMOCK_DAG_H_ */
