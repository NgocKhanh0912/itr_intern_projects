/**
 * @file       cbuffer.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    1.0.0
 * @date       2024-06-26
 * @author     Giang Phan
 *             Viet Hoang Xuan
 *             Khanh Nguyen Ngoc
 *
 * @brief      Circular Buffer
 *             This Circular Buffer is safe to use in IRQ with single reader,
 *             single writer. No need to disable any IRQ.
 *
 *             Capacity = <size> - 1
 * @note       none
 * @example    cbuffer_t cb;
 *             uint8_t cb_buff[6];
 *             uint8_t a;
 *             void main(void)
 *             {
 *                 cb_init(&cb, cb_buff, 100);
 *                 cb_clear(&cb);
 *                 char a[] = {0, 1, 2, 3, 4};
 *
 *                 int c = 5;
 *                 cb_write(&cb, a, 5);
 *                 char b[5];
 *                 cb_read(&cb, a, 5);
 *             }
 */

/* Includes ----------------------------------------------------------- */
#include "cbuffer.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */
typedef enum
{
	CBUFFER_COUNT_SPACE_FAIL = -4,
	CBUFFER_COUNT_DATA_FAIL = -3,
	CBUFFER_WRITE_FAIL = -2,
	CBUFFER_READ_FAIL = -1,
	CBUFFER_OK = 0
} cbuffer_status_t;

/* Private macros ----------------------------------------------------- */
#define CHECK(_EXPR_, _RET_VAL_) \
	do                             \
	{                              \
		if (!(_EXPR_))               \
			return _RET_VAL_;          \
	} while (0)

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void cb_init(cbuffer_t *cb, void *buf, uint32_t size)
{
	CHECK(cb != NULL, );
	CHECK((size < CB_MAX_SIZE) && (size > 0), );
	CHECK(buf != NULL, );

	cb->data = buf;
	cb->size = size;
	cb->writer = 0;
	cb->reader = 0;
	cb->overflow = 0;
	cb->active = 1;
}

void cb_clear(cbuffer_t *cb)
{
	// Return if cb is not active
	CHECK(cb->active == 1, );

	// Return if cb is NULL
	CHECK(cb != NULL, );

	cb->reader = 0;
	cb->writer = 0;
	cb->overflow = 0;
}

uint32_t cb_data_count(cbuffer_t *cb)
{
	// Return if cb is NULL
	CHECK(cb != NULL, CBUFFER_COUNT_DATA_FAIL);

	// Return if cb is not active
	CHECK(cb->active, CBUFFER_COUNT_DATA_FAIL);

	if (cb->writer >= cb->reader)
		return (cb->writer - cb->reader);

	return (cb->size + cb->writer - cb->reader);
}

uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
	// Return if cb is NULL
	CHECK(cb != NULL, CBUFFER_READ_FAIL);

	// Return if buf is NULL
	CHECK(buf != NULL, CBUFFER_READ_FAIL);

	// Return if cb is not active
	CHECK(cb->active, CBUFFER_READ_FAIL);

	// Return if nbytes < 0 or nbytes = 0 (invalid)
	CHECK(nbytes > 0, CBUFFER_READ_FAIL);

	// Return if (cb->reader = cb->writer) from the beginning, buffer is empty
	CHECK(cb->reader != cb->writer, CBUFFER_READ_FAIL);

	uint32_t count_bytes = 0;
	for (uint32_t i = 0; i < nbytes; i++)
	{
		*((uint8_t *)buf + i) = cb->data[cb->reader];
		cb->reader = (cb->reader + 1) % cb->size;
		count_bytes++;
		if (cb->reader == cb->writer)
		{
			return count_bytes; // End the function when all nbytes have not been read and the buffer is empty
		}
	}
	return nbytes; // Returns the number of nbytes that have been read
}

uint32_t cb_space_count(cbuffer_t *cb)
{
	uint32_t size, in, out;
	// Return if cb is NULL
	CHECK(cb != NULL, CBUFFER_COUNT_SPACE_FAIL);

	// Return if cb is not active
	CHECK(cb->active, CBUFFER_COUNT_SPACE_FAIL);

	// Save values
	in = cb->writer;
	out = cb->reader;

	// Case 1: CBuffer empty
	if (in == out)
	{
		size = cb->size;
	}

	// Case 2: Normal mode (Writer is ahead of Reader)
	if (in > out)
	{
		size = cb->size - (in - out);
	}

	// Case 3: Overflow mode (Writer is behind of Reader)
	if (in < out)
	{
		size = out - in;
	}

	// Maximum in-use size is Size - 1 to distinguish empty versus full cases
	return size - 1;
}

uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
	// Return if cb is NULL
	CHECK(cb != NULL, CBUFFER_WRITE_FAIL);

	// Return if cb is not active
	CHECK(cb->active, CBUFFER_WRITE_FAIL);

	// Return if buf is NULL
	CHECK(buf != NULL, CBUFFER_WRITE_FAIL);

	uint32_t count_bytes = 0;
	uint32_t free;
	uint8_t *data = (uint8_t *)buf;

	// Get space left
	free = cb_space_count(cb);

	// Check whether enough space left or not
	if (free < nbytes)
	{
		// Count the number of bytes would be overwrite
		cb->overflow = nbytes - free;
	}

	// Write operation
	while (nbytes--)
	{
		// Write to buffer
		cb->data[cb->writer++] = *data++;

		// Increase bytes counter
		count_bytes++;

		// Overflow
		if (cb->writer >= (cb->size - 1))
		{
			cb->writer = 0;
		}
	}

	// Return the number of bytes wrote
	return count_bytes;
}

/* Private definitions ------------------------------------------------ */

/* End of file -------------------------------------------------------- */
