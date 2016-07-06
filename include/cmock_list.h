/*
 * cmock_list.h
 *
 *  Created on: 2016/6/14
 *      Author: emit.yanfeng@gmail.com
 */

#ifndef INCLUDE_CMOCK_LIST_H_
#define INCLUDE_CMOCK_LIST_H_


typedef struct S_LIST_NODE {
    struct S_LIST_NODE *prev;
    struct S_LIST_NODE *next;
} T_LIST_NODE;


static inline void list_init(T_LIST_NODE* head) {
    head->next = head;
    head->prev = head;
}


static inline int list_empty(T_LIST_NODE* head) {
    return (head->next == head);
}


static inline void list_insert(T_LIST_NODE* node, T_LIST_NODE* p, T_LIST_NODE* n) {
    node->next = n;
    node->prev = p;
    p->next = node;
    n->prev = node;
}


static inline T_LIST_NODE* list_delete(T_LIST_NODE* node, T_LIST_NODE* p, T_LIST_NODE* n) {
    p->next = node->next;
    n->prev = node->prev;
    return node;
}


static inline void list_insert_tail(T_LIST_NODE* node, T_LIST_NODE* head) {
    list_insert(node, head->prev, head);
}


static inline void list_insert_head(T_LIST_NODE* node, T_LIST_NODE* head) {
    list_insert(node, head, head->next);
}


static inline T_LIST_NODE* list_delete_tail(T_LIST_NODE* head) {
    return list_delete(head->prev, head->prev->prev, head);
}


static inline T_LIST_NODE* list_delete_head(T_LIST_NODE* head) {
    return list_delete(head->next, head, head->next->next);
}


#define list_for_each(head, pNode, pTmp) \
    for((pNode)=(head)->next, (pTmp)=(pNode)->next; (pNode)!=(head); (pNode)=(pTmp), (pTmp)=(pTmp)->next)

#define list_for_each_ext(head, pNode, pTmp, ext) \
    for((pNode)=(head)->next, (pTmp)=(pNode)->next, ext; (pNode)!=(head); (pNode)=(pTmp), (pTmp)=(pTmp)->next, ext)

#endif /* INCLUDE_CMOCK_LIST_H_ */
