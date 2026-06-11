#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

static constexpr float XSHELL_ARRAY_GROWTH_FACTOR = 1.5;


bool
xshell_array_init_with_capacity(struct xshell_array *self, size_t n, size_t size)
{
    assert(self != nullptr && "passed instance is null");

    if (n > 0)
    {
        self->data = malloc(n * size);
        if (self->data == nullptr) return false;
    }

    self->type_size = size;
    self->capacity  = n;
    self->size      = 0;

    return true;
}


bool
xshell_array_init(struct xshell_array *self, size_t size)
{ return xshell_array_init_with_capacity(self, 0, size); }


void
xshell_array_deinit(struct xshell_array *self)
{
    assert(self != nullptr && "passed instance is null");

    free(self->data);
    self->capacity  = 0;
    self->type_size = 0;
    self->size      = 0;
}


bool
xshell_array_reserve(struct xshell_array *self, size_t n)
{
    assert(self != nullptr && "passed instance is null");

    if (self->capacity >= n) return true;

    void *ptr = realloc(self->data, n * self->type_size);
    if (ptr == nullptr) return false;

    self->data     = ptr;
    self->capacity = n;

    return true;
}


bool
xshell_array_resize(struct xshell_array *self, size_t n)
{
    if (!xshell_array_reserve(self, n)) return false;
    if (self->size >= n) return true;

    self->size = n;
    return true;
}


void *
xshell_array_at(struct xshell_array *self, size_t index)
{
    assert(self != nullptr && "passed instance is null");
    if (self->size <= index) return nullptr;

    return (char *)self->data + index;
}


const void *
xshell_array_at_const(const struct xshell_array *self, size_t index)
{ return xshell_array_at((struct xshell_array *)self, index); }


bool
xshell_array_insert(struct xshell_array *self, void *data, size_t at)
{
    assert(self != nullptr && "passed instance is null");
    if (at > self->size) return false;

    if (self->size >= self->capacity)
    {
        size_t size = self->capacity == 0 ? 15 : self->capacity * XSHELL_ARRAY_GROWTH_FACTOR;

        if (!xshell_array_reserve(self, size)) return false;
    }

    if (at == self->size)
    {
        self->size++;

        void *elem = xshell_array_at(self, self->capacity - 1);
        memcpy(elem, data, self->type_size);

        return elem;
    }

    if (at < self->size)
    {
        char  *base          = (char *)self->data;
        size_t bytes_to_move = (self->size - at) * self->type_size;

        void *dest = base + ((at + 1) * self->type_size);
        void *src  = base + (at * self->type_size);

        memmove(dest, src, bytes_to_move);
    }

    void *elem_ptr = xshell_array_at(self, at);
    memcpy(elem_ptr, data, self->type_size);

    self->size++;
    return elem_ptr;
}


bool
xshell_array_push(struct xshell_array *self, void *data)
{ return xshell_array_insert(self, data, self->size); }


void
xshell_array_erase(struct xshell_array *self, size_t at)
{
    assert(self != nullptr && "passed instance is null");
    if (at > self->size || self->size == 0) return;
    if (self->data == NULL) return;

    if (at == self->size - 1)
    {
        self->size--;
        return;
    }

    if (at < self->size - 1)
    {
        char  *base          = (char *)self->data;
        size_t bytes_to_move = (self->size - at) * self->type_size;

        void *dest = base + (at * self->type_size);
        void *src  = base + ((at + 1) * self->type_size);

        memmove(dest, src, bytes_to_move);
        self->size--;
    }
}


void
xshell_array_pop(struct xshell_array *self)
{ xshell_array_erase(self, self->size - 1); }
