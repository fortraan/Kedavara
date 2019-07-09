#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>

#define __PATTERN_CALLBACK_NAME(pattern_name) pattern_callback_ ## pattern_name
#define __PATTERN_POINTER_NAME(pattern_name) pattern_pointer_ ## pattern_name

struct __struct_pattern {
  void (*pointer)();
  uint8_t pin;
};

#define REGISTER_PATTERN(pattern_name, pattern_button)\
(struct __struct_pattern){__PATTERN_POINTER_NAME(pattern_name), pattern_button},

#define ON_RUN_PATTERN(pattern_name, pattern_code) \
void __PATTERN_CALLBACK_NAME(pattern_name)() {\
  pattern_code\
};\
auto __PATTERN_POINTER_NAME(pattern_name) = __PATTERN_CALLBACK_NAME(pattern_name);

#endif
