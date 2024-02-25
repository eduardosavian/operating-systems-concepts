// C11 header for cleaner type names and definitions

#ifndef INCLUDE_TYPES_H_
#define INCLUDE_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdalign.h>

// Aligment of max_align_t
#define MAX_ALIGN alignof(max_align_t)

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float    f32;
typedef double   f64;

typedef unsigned int  uint;
typedef unsigned char byte;
typedef uint32_t      rune;
typedef uintptr_t     uintptr;

typedef size_t        usize;
#ifndef NO_SIGNED_SIZE
	_Static_assert(sizeof(ptrdiff_t) == sizeof(size_t) ,"could not create a valid ssize type, #define NO_SIGNED_SIZE to disable it.");
	typedef ptrdiff_t     ssize;
#endif

#endif /* include guard */
