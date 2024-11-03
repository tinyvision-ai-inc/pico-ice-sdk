//
// Created by MrJake222 on 30/10/24.
//

#include "rb.h"

// MIN/MAX
#include <pico/platform.h>

void rb_init(struct rb* rb) {
    rb->read_index = 0;
    rb->write_index = 0;
    rb->read_total = 0;
    rb->written_total = 0;
}

int rb_data_left(struct rb* rb) {
    return (int) (rb->written_total - rb->read_total);
}

int rb_data_left_continuous(struct rb* rb) {
    return MIN(rb_data_left(rb), RB_BUFSIZE - rb->read_index);
}

int rb_space_left(struct rb* rb) {
    return RB_BUFSIZE - rb_data_left(rb);
}

int rb_space_left_continuous(struct rb* rb) {
    return MIN(rb_space_left(rb), RB_BUFSIZE - rb->write_index);
}

char* rb_read_ptr(struct rb* rb) {
    return rb->buf + rb->read_index;
}

char* rb_write_ptr(struct rb* rb) {
    return rb->buf + rb->write_index;
}

char* rb_write_ptr_next_ack(struct rb* rb, unsigned int bytes) {
    int wi = rb->write_index + (int)bytes;
    while (wi >= RB_BUFSIZE) wi -= RB_BUFSIZE;
    return rb->buf + wi;
}

void rb_read_ack(struct rb* rb, unsigned int bytes) {
    rb->read_index += (int)bytes;
    while (rb->read_index >= RB_BUFSIZE) rb->read_index -= RB_BUFSIZE; // faster than modulo (%)
    rb->read_total += bytes;
}

void rb_write_ack(struct rb* rb, unsigned int bytes) {
    rb->write_index += (int)bytes;
    while (rb->write_index >= RB_BUFSIZE) rb->write_index -= RB_BUFSIZE;
    rb->written_total += bytes;
}

