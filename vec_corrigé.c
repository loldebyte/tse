#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct _vec {
    /// Heap pointer to the vector
    int32_t * array;
    /// Used space of the vec_t
    size_t len;
    /// Really allocated space
    size_t capacity;
} vec_t;

/** Allocate a growable array in heap.
 * default size is 16 words.
 */
vec_t vec_new(void);

/** Deallocate the vector. */
void vec_free(vec_t *vec);

/** Add an `element` in vector `vec`.
 * Allocation occurs if `len` == `capacity`.
 * exemple:
 * ```c
 *  vec_t v = vec_new(2);
 *  vec_push(v, 5);
 *  vec_push(v, 3);
 *  // Contain [ 5, 3]
 * ```
 */
vec_t * vec_push(vec_t *vec, int32_t element);

size_t vec_capacity(const vec_t * v);
size_t vec_len(const vec_t * v);

/** Get access to element at index i.
 * Debug build:
 *  Crash execion if access is out of bound.
 * Optimized build:
 *  Undefined behaviour if acces is out of bound.
 */
int32_t vec_get(const vec_t * vec, const size_t i);

/** Allocate with initial capacity */
void vec_new_with_capacity(size_t capacity);

/** Becareful raw access to the underling pointer! */
int32_t * vec_unsafe_as_ptr(vec_t * v);

vec_t vec_new(void) {
    vec_t vec;
    vec.capacity = 8;
    vec.len = 0;
    vec.array = (int32_t *) malloc(sizeof(int32_t) * vec.capacity);
    return vec;
}

vec_t * vec_push(vec_t * vec, int32_t element) {
    // On realloue
    if (vec->capacity == vec->len) {
        size_t new_capacity = vec->capacity * 2;
        int32_t * new_array = realloc(vec->array, sizeof(int32_t) * new_capacity);
        vec->array = new_array;
        vec->capacity = new_capacity;
    }
    const size_t index = vec->len;
    vec->array[index] = element;
    vec->len += 1;
    return vec;
}

void vec_free(vec_t * v) {
    free(v->array);
    v->capacity = 0;
    v->len = 0;
    v->array = NULL;
}

size_t vec_len(const vec_t * v) { return v->len; }
size_t vec_capacity(const vec_t * v) { return v->capacity; }
int32_t * vec_unsafe_as_ptr(vec_t * v) { return v->array; }

int32_t vec_get(const vec_t * vec, const size_t index) {
    assert(index < vec->len);
    return vec->array[index];
}

/** Remove an element by index, shift to left element after
 * the removed element.
 */
int32_t vec_remove(vec_t * vec, size_t index) {
    assert(vec->len >= index);
    const int32_t removed = vec->array[index];
    for (size_t i = index + 1; i < vec->len; i += 1) {
        vec->array[i - 1] = vec->array[i];
    }
    vec->len -= 1;
    return removed;
}

int main(void) {
    vec_t v = vec_new();
    vec_t * p = &v;
    { // Test push
        vec_push(p, 5); vec_push(p, 6); 
        vec_push(p, 6); vec_push(p, 1);
        vec_push(p, 42); vec_push(p, 32); 
        vec_push(p, 6); vec_push(p, 1);
        assert(vec_get(p, 0) == 5);
        assert(vec_get(p, 1) == 6);
        vec_push(p, 54);
        assert(vec_get(p, 8) == 54);
        assert(vec_remove(p, 8) == 54);
        assert(vec_len(p) == 8);
        
        assert(vec_remove(p, 0) == 5);
        assert(vec_len(p) == 7);
        assert(vec_get(p, 1) == 6);
    }
    
    vec_free(p);
    assert(vec_capacity(p) == 0);
    assert(vec_len(p) == 0);
}

// vec_iter_t * vec_into_iter(vec_t * v);

// struct _vec_iter {
    
// } vec_iter_t;

// vec_iter_t * vec_first(vec_t * v);
// bool vec_done(vec_t *v);
// vec_iter_t * vec_next(vec_iter_t * v);
