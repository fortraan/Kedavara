#ifndef DEFINES_H
#define DEFINES_H

// this file contains the macros used in the software.

#include <stdint.h>

// macro for generating the internal name of a callback
#define __PATTERN_CALLBACK_NAME(pattern_name) pattern_callback_ ## pattern_name
// macro for generating the internal name of the global pointer to a callback function
#define __PATTERN_POINTER_NAME(pattern_name) pattern_pointer_ ## pattern_name

// struct to contain a pattern
// pointer points to the pattern's code
// pin is the physical pin the pattern is mapped to.
struct __struct_pattern {
  void (*pointer)();
  uint8_t pin;
};

// macro for pattern registration. it doesn't actually execute any code;
// instead, it expands its arguments into a __struct_pattern. since
// the registry is inside of an array literal, the registry is compiled
// to an array of __struct_pattern, with one for each pattern.
#define REGISTER_PATTERN(pattern_name, pattern_button)\
(struct __struct_pattern){__PATTERN_POINTER_NAME(pattern_name), pattern_button},

// macro for pattern callbacks. a pattern callback is the code run by the pattern
// while it is active. the macro expands it into a global void function, and
// creates a global pointer to the function. when REGISTER_PATTERN is called, it
// finds the name of the global function pointer from the pattern's name, and uses
// it to build a __struct_pattern.
#define ON_RUN_PATTERN(pattern_name, pattern_code) \
void __PATTERN_CALLBACK_NAME(pattern_name)() {\
  pattern_code\
};\
auto __PATTERN_POINTER_NAME(pattern_name) = __PATTERN_CALLBACK_NAME(pattern_name);

#endif
