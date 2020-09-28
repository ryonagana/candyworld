#ifndef THREAD_H
#define THREAD_H
#include <allegro5/allegro.h>
#include <stdio.h>
#include <string.h>


typedef void *(*thread_func)(ALLEGRO_THREAD *thread, void* data);

typedef struct thread_t {
    ALLEGRO_THREAD *thread;
    ALLEGRO_MUTEX  *mutex;
    thread_func  callback;
}thread_t;

struct thread_data_t {
    ALLEGRO_MUTEX *mutex;
    void *data;
};


void thread_init(thread_t *th, thread_func func, void *data);
void thread_destroy(thread_t *th);
void thread_start(thread_t *th);
void* thread_join(thread_t *th);


#endif // THREAD_H
