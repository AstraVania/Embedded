#include <RingBuffer.h>
#include <main.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern UART_HandleTypeDef huart2;

#define RING_BUFFER_SIZE 100

static int _head = 0;
static int _tail = 0;
static uint8_t _buffer[RING_BUFFER_SIZE];

// Initializes the ring buffer internal data structures
void RingBuffer_Init()
{
	_head = 0;
	_tail = 0;
}

// returns 1 if it’s empty and 0 if it has at least one byte
int RingBuffer_IsEmpty()
{
	return _head == _tail;
}

// returns 1 if no more bytes can be added to the ring buffer
int RingBuffer_IsFull()
{
	return _tail == (_head + 1) % RING_BUFFER_SIZE;
}

// returns the amount of free space in the buffer
int RingBuffer_FreeSpace()
{
	if (_head >= _tail) {
		return RING_BUFFER_SIZE - _head + _tail;
	}
	else {
		return _tail - _head - 1;
	}
}

// Writes the data from the input array to the ring buffer.
// If it does not have enough space returns 0 and does not write any bytes,
// otherwise writes the bytes to the ring buffer and returns 1
int RingBuffer_Write(uint8_t * data, size_t dataSize)
{
	if (dataSize > RingBuffer_FreeSpace()) {
		return 0;
	}

	for (size_t i = 0; i < dataSize; i++) {
		_buffer[_head] = *data++;
		_head = (_head + 1) % RING_BUFFER_SIZE;
	}
	return 1;
}

// Reads the amount of bytes specified in dataSize from the ring buffer to the data array
int RingBuffer_Read(uint8_t * data, size_t dataSize)
{
	int readCount = 0;
	for (size_t i = 0; i < dataSize; i++) {
		if (_tail == _head) {
			break;
		}

		*data++ = _buffer[_tail];
		_tail = (_tail + 1) % RING_BUFFER_SIZE;
		readCount++;
	}

	return readCount;
}


