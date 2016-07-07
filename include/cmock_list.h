/*
 * cmock_list.h
 *
 *  Created on: 2016/6/14
 *      Author: emit.yanfeng@gmail.com
 */

#ifndef INCLUDE_CMOCK_LIST_H_
#define INCLUDE_CMOCK_LIST_H_


typedef struct _CMOCK_S_LIST_NODE{
    struct _CMOCK_S_LIST_NODE *prev;
    struct _CMOCK_S_LIST_NODE *next;
} CMOCK_S_LIST_NODE;


static inline void cmock_list_init(CMOCK_S_LIST_NODE* head) {
    head->next = head;
    head->prev = head;
}


static inline int cmock_list_empty(CMOCK_S_LIST_NODE* head) {
    return (head->next == head);
}


static inline void cmock_list_insert(CMOCK_S_LIST_NODE* node, CMOCK_S_LIST_NODE* p, CMOCK_S_LIST_NODE* n) {
    node->next = n;
    node->prev = p;
    p->next = node;
    n->prev = node;
}


static inline CMOCK_S_LIST_NODE* cmock_list_delete(CMOCK_S_LIST_NODE* node, CMOCK_S_LIST_NODE* p, CMOCK_S_LIST_NODE* n) {
    p->next = node->next;
    n->prev = node->prev;
    return node;
}


static inline void cmock_list_insert_tail(CMOCK_S_LIST_NODE* node, CMOCK_S_LIST_NODE* head) {
    cmock_list_insert(node, head->prev, head);
}


static inline void cmock_list_insert_head(CMOCK_S_LIST_NODE* node, CMOCK_S_LIST_NODE* head) {
    cmock_list_insert(node, head, head->next);
}


static inline CMOCK_S_LIST_NODE* cmock_list_delete_tail(CMOCK_S_LIST_NODE* head) {
    return cmock_list_delete(head->prev, head->prev->prev, head);
}


static inline CMOCK_S_LIST_NODE* cmock_list_delete_head(CMOCK_S_LIST_NODE* head) {
    return cmock_list_delete(head->next, head, head->next->next);
}


#define cmock_list_for_each(head, pNode, pTmp) \
    for((pNode)=(head)->next, (pTmp)=(pNode)->next; (pNode)!=(head); (pNode)=(pTmp), (pTmp)=(pTmp)->next)

#define cmock_list_for_each_ext(head, pNode, pTmp, ext) \
    for((pNode)=(head)->next, (pTmp)=(pNode)->next, ext; (pNode)!=(head); (pNode)=(pTmp), (pTmp)=(pTmp)->next, ext)

#endif /* INCLUDE_CMOCK_LIST_H_ */
