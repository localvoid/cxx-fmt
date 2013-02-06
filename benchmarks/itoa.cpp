#include <cstdint>
#include <iostream>
#include <string.h>
#include <vector>
#include <sched.h>

#include <fmt/itoa.hpp>

namespace {

class Value {
public:
  Value(int32_t n, uint32_t w, uint32_t f)
      : number(n), width(w), flags(f) {}

  int32_t number;
  uint32_t width;
  uint32_t flags;
};

#if defined(__i386__)
uint64_t rdtsc() {
  uint64_t x;
  __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
  return x;
}
#elif defined(__x86_64__)
uint64_t rdtsc() {
  uint32_t hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)lo)|(((uint64_t)hi)<<32 );
}
#endif

template<typename T>
uint64_t measure(T code) {
  uint64_t a = rdtsc();

  code();

  uint64_t b = rdtsc();

  return (b - a);
}

void run(int loop_count, std::vector<Value> &values) {
  char buf[64];

  uint64_t time = measure([=, &buf]() {
      for (int x = 0; x < loop_count; ++x) {
        for (auto &v : values) {
          fmt::itoa(v.number, v.width, v.flags, buf);
        }
      }
    });

  std::cout << time << std::endl;
}


}


int main(int argc, char *argv[]) {
  cpu_set_t  mask;
  CPU_ZERO(&mask);
  CPU_SET(0, &mask);
  if (sched_setaffinity(0, sizeof(mask), &mask) < 0) {
    perror("sched_setaffinity");
  }

  int loop_count = 1;


  if (argc > 1) {
    loop_count = atoi(argv[1]);
    if (loop_count < 1) {
      std::cerr << "Invalid argument: loop counter" << std::endl;
      return 1;
    }
  }

  std::vector<Value> values;
  std::string line;

  while (std::cin) {
    std::getline(std::cin, line);
    int32_t n = atoi(line.c_str());
    std::getline(std::cin, line);
    uint32_t w = atoi(line.c_str());
    std::getline(std::cin, line);
    uint32_t f = atoi(line.c_str());
    values.emplace_back(n, w, f);
  }

  run(loop_count, values);

  return 0;
}
