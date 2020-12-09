#include "list.h"




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

    if(node->prev){
        node->prev->next = node->next;
        return;
    }
    else {
        lst->head = node->next;
    }
    if(node->next){
        node->next->prev = node->prev;
    }
    else {
        lst->tail = node->prev;
    }
    free(node);
}
