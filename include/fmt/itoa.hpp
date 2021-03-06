#ifndef _FMT_ITOA_HPP_
#define _FMT_ITOA_HPP_

#include <fmt/flag.hpp>

namespace fmt {

uint32_t itoa(int64_t n, uint32_t width, uint32_t flags, char *b);
uint32_t itoa(uint64_t n, uint32_t width, uint32_t flags, char *b);
uint32_t itoa(int32_t n, uint32_t width, uint32_t flags, char *b);
uint32_t itoa(uint32_t n, uint32_t width, uint32_t flags, char *b);

uint32_t itoa_hex(uint64_t n, uint32_t width, uint32_t flags, char *b);
uint32_t itoa_hex(uint32_t n, uint32_t width, uint32_t flags, char *b);

uint32_t dtoa(double v, uint32_t width, uint32_t precision, uint32_t flags, char *b);

}

#endif
