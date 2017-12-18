#!/usr/bin/env bash

echo "building"
#gcc -lcunit ./*.c ./hwc1/*.c ./hwc2list/*.c ./test/*.c -o test_runner
gcc -lcunit ./test_driver.c \
            ./accepter/*.c ./accepter/test/*.c \
            ./dispatcher/*.c ./dispatcher/test/*.c \
            ./provider/*.c ./provider/test/*.c \
            ./reader/*.c ./reader/test/*.c \
            ./lib/buffer/*.c ./lib/buffer/test/*.c \
            ./lib/buffer_concorrent/*.c ./lib/buffer_concorrent/test/*.c \
            ./lib/hwc2list/*.c ./lib/list_concorrent/*.c \
            ./lib/monitor_buffer/*.c ./lib/msg/*.c ./lib/poison_pill/*.c \
            -o test_runner

echo "running"
./test_runner