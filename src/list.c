#include "list.h"


#define  LIST_DELETE_NODE(l,n) \
                if(n->prev){ n->prev->next = n->next;}\
                else { l->head = n->next; }\
                if(n->next){ n->next->prev = n->prev;}\
                else { l->tail = n->prev ; }

void link_node_init(link_node_t *node)
{
    node->data = NULL;
    node->next = NULL;
    node->prev = NULL;
}

link_node_t *link_node_create(void *data)
{
    link_node_t *self =  malloc(sizeof(link_node_t));

    if(!self){
        return NULL;
    }

    link_node_init(self);
    self->data = data;
    return self;

}

void list_node_init(link_list_t *lst)
{
    lst->head = NULL;
    lst->tail = NULL;
    lst->frame_count = 0;
}

link_list_t *list_create()
{
    link_list_t *tmp = NULL;

    tmp = malloc(sizeof(link_list_t));
    list_node_init(tmp);
    return tmp;
}

int list_push_node_head(link_list_t *lst, link_node_t *node)
{
    if(lst->head == NULL){
        lst->head = node;
        lst->tail = node;
        return 0;
    }

    node->next = lst->head;
    lst->head->prev = node;
    lst->head = node;
    return 1;
}

int list_push_node(link_list_t *lst, link_node_t *node)
{
    if(lst->head == NULL){
        lst->head = node;
        lst->tail = node;
        return 0;
    }


    lst->tail->next = node;
    node->prev = lst->tail;
    lst->tail = node;
    return 1;

}

void list_remove_node(link_list_t *lst, link_node_t *node)
{
    LIST_DELETE_NODE(lst,node);
}
