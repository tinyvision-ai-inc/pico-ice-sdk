//
// Created by MrJake222 on 30/10/24.
//

#pragma once

#include <tusb_config.h>
// #define RB_BUFSIZE CFG_TUD_CDC_TX_BUFSIZE

struct rb {
    char* buf;
    int size;

    int read_index;
    unsigned long long read_total;

    int write_index;
    unsigned long long written_total;

    // additionally to indexes (which will roll over) we defined read_total and written_total
    // to mitigate ambiguity (when read_index==write_index is the buffer full or empty?)
    // this variables will get large so we define them as 64bit (rolls over after 645 years at 10Gbit/s)
};

void rb_init(struct rb* rb, char* buf, int bufsize);
int rb_data_left(struct rb* rb);
int rb_data_left_continuous(struct rb* rb);
int rb_space_left(struct rb* rb);
int rb_space_left_continuous(struct rb* rb);
char* rb_read_ptr(struct rb* rb);
char* rb_write_ptr(struct rb* rb);
char* rb_write_ptr_next_ack(struct rb* rb, unsigned int bytes);
void rb_read_ack(struct rb* rb, unsigned int bytes);
void rb_write_ack(struct rb* rb, unsigned int bytes);