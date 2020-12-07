#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

struct _link_node_t {
    void *data;
    struct _link_node_t *next, *prev;
};

typedef struct _link_node_t link_node_t;


struct _link_list_t {
    link_node_t *head, *tail;
};

typedef struct _link_list_t link_list_t;


void link_node_init(link_node_t *node);
link_node_t *link_node_create(void *data);
void list_node_init(link_list_t *lst);
link_list_t *list_create();



int  list_push_node_head(link_list_t *lst, link_node_t *node);
int  list_push_node(link_list_t *lst, link_node_t *node);
void list_remove_node(link_list_t *lst, link_node_t *node);


#endif // LIST_H
