//
// Created by Alessandro Iori on 16/12/2017.
//

#ifndef UNTITLED_TEST_READER_H
#define UNTITLED_TEST_READER_H

#include <unistd.h>
#include "CUnit/Basic.h"
#include "../reader.h"
#include "../poison_pill.h"

int reader_before(void);
int reader_after(void);
void test_reader_init(void);
void test_reader_destroy(void);

void test_reader_1_msg_letto_buffer_dim_5(void);

#endif //UNTITLED_TEST_READER_H
