#pragma once
#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#include <stdint.h>
#include <stdlib.h>

// Initializes the ring buffer internal data structures
void RingBuffer_Init();

// returns 1 if it’s empty and 0 if it has at least one byte
int RingBuffer_IsEmpty();

// returns 1 if no more bytes can be added to the ring buffer
int RingBuffer_IsFull();

// returns the amount of free space in the buffer
int RingBuffer_FreeSpace();

// Writes the data from the input array to the ring buffer.
// If it does not have enough space returns 0 and does not write any bytes,
// otherwise writes the bytes to the ring buffer and returns 1
int RingBuffer_Write(uint8_t * data, size_t dataSize);

// Reads the amount of bytes specified in dataSize from the ring buffer to the data array
int RingBuffer_Read(uint8_t * data, size_t dataSize);

#endif
