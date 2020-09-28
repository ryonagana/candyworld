#include  "thread.h"
#include "log.h"


void thread_init(thread_t *th, thread_func func, void *data)
{

    th->mutex  = al_create_mutex();
    struct thread_data_t data_thread;

    data_thread.data = data;
    data_thread.mutex = th->mutex;

    th->thread = al_create_thread(func, (void *)&data_thread);
}

void thread_destroy(thread_t *th)
{
    if(th->thread) al_destroy_thread(th->thread);
    if(th->mutex) al_destroy_mutex(th->mutex);

    th->thread = NULL;
    th->mutex  = NULL;
}


void thread_start(thread_t *th)
{
    if(th->thread == NULL) {
        return;
    }
    al_start_thread(th->thread);

    return;
}




void* thread_join(thread_t *th)
{
    if(th == NULL){
        DLOG("Thread Join Failed!");
        return NULL;
    }
    void *ret_val = NULL;
    al_join_thread(th->thread, &ret_val);
    return ret_val;
}
