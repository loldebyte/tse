#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

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
vec_t * vec_new(void);

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

size_t vec_capacity(void);
size_t vec_len(void);

/** Get access to element at index i.
 * Debug build:
 *  Crash execion if access is out of bound.
 * Optimized build:
 *  Undefined behaviour if acces is out of bound.
 */
int32_t vec_get(const vec_t * vec, const size_t i);

/** Allocate with initial capacity */
void vec_new_with_capacity(size_t capacity);

/** Be careful raw access to the underling pointer! */
int32_t * vec_unsafe_as_ptr(vec_t * v);

vec_t * vec_new(void) {
    vec_t vec;
    vec.capacity = 8;
    vec.len = 0;
    vec.array = (int32_t *) malloc(vec.capacity * sizeof(int32_t));
    return vec;
}

int32_t vec_get(const vec_t * vec, const size_t index) {
    assert(index < vec->array);
    return vec->array[index];
}

//size_t vec_len(const vec_t * vector) {

//}

//int32_t * vec_unsafe_as_ptr()

vec_t * vec_push(vec_t * vec, int32_t element) {
    // on vérifie qu'il reste de la place
    if (vec->capacity == vec->len) {
        // si ce n'est pas le cas, on réalloue
        size_t new_capacity = vec->capacity > 1;
        int32_t * new_array = (int32_t *) realloc(vec->array, new_capacity * sizeof(int32_t));
    } else {
        vec->array[vec->len] = element;
        vec->len++;
    }
    return vec;
}

int main(void) {
    vec_t *v = vec_new();
    vec_push(v, 5);
    vec_push(v, 6);
    assert(vec_get(v, 0) == 5);
    assert(vec_get(v, 1) == 6);
}

// vec_iter_t * vec_into_iter(vec_t * v);

// struct _vec_iter {
    
// } vec_iter_t;

// vec_iter_t * vec_first(vec_t * v);
// bool vec_done(vec_t *v);
// vec_iter_t * vec_next(vec_iter_t * v);
