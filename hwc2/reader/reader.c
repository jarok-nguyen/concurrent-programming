//
// Created by Alessandro Iori on 16/12/2017.
//

#include "reader.h"

reader_t* reader_init(int velocity)
{
    reader_t* reader = (reader_t*) malloc(sizeof(reader_t));
    int* v = (int*) malloc(sizeof(int));
    buffer_concurrent_t* c_buffer = (buffer_concurrent_t*) malloc(sizeof(buffer_concurrent_t));

    *v = velocity;
    c_buffer = buffer_concurrent_init(READER_BUFFER_SIZE);

    reader->velocity = v;
    reader->c_buffer = c_buffer;
    reader->reader_destroy = reader_destroy;

    return reader;
}

void reader_destroy(reader_t* r)
{
    buffer_concurrent_t* b = r->c_buffer;
    b->buffer_concurrent_destroy(b);
    free(r->velocity);
}

void* reader_thread_function(void* args)
{
    reader_t* reader = (reader_t*) args;
    msg_t* m;

    int exit = 0;
    while(!exit)
    {

        READER_LAST_MSG = (msg_t*) NULL;
        READER_LAST_MSG = buffer_concurrent_get_msg(reader->c_buffer);
        if(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content))
        {
            exit = 1;
        } else {
            //READER_LAST_MSG->msg_destroy(READER_LAST_MSG);
        }
        sleep(*reader->velocity);
    }
    return (void*) NULL;
}

void reader_start_thread(reader_t* r)
{
    pthread_t      tid;  // thread ID
    pthread_attr_t attr; // thread attribute

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if(pthread_create(&tid, &attr, reader_thread_function, r))
    {
        printf("error creating reader thread\t\n");
        exit(1);
    }
}