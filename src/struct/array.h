#pragma once
#include <stddef.h>


struct xshell_array
{
    void  *data;

    size_t size;
    size_t capacity;
    size_t type_size;
};


/**
 * @brief Initializes an @ref xshell_array with an initial capacity.
 *
 * @param n    The amount of items the array should contain.
 * @param size The size of each item, i.e. `sizeof(T)`.
 *
 * @memberof xshell_array
 */
bool xshell_array_init_with_capacity(struct xshell_array *self, size_t n, size_t size);

/**
 * @brief Initializes an @ref xshell_array .
 *
 * @param size The size of the contained item.
 *
 * @memberof xshell_array
 */
bool xshell_array_init(struct xshell_array *self, size_t size);

void xshell_array_deinit(struct xshell_array *self);


/**
 * @brief Reserves anough space to at least hold N items.
 *
 * @note Will do nothing if @p n is less or equals than the current capacity.
 */
bool xshell_array_reserve(struct xshell_array *self, size_t n);

/**
 * @brief Resizes the array to be able to insert until the (N - 1)th index.
 *
 * @note Will do nothing if @p n is less or equals than the current size.
 */
bool xshell_array_resize(struct xshell_array *self, size_t n);


/** @brief Returns a pointer at an index inside the array. */
void *xshell_array_at(struct xshell_array *self, size_t index);

/** @brief Returns a const pointer at an index inside the array. */
const void *xshell_array_at_const(const struct xshell_array *self, size_t index);


bool xshell_array_insert(struct xshell_array *self, void *data, size_t at);
bool xshell_array_push(struct xshell_array *self, void *data);

void xshell_array_erase(struct xshell_array *self, size_t at);
void xshell_array_pop(struct xshell_array *self);
