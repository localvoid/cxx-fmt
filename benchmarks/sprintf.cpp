#include <cstdint>
#include <iostream>
#include <string.h>
#include <vector>
#include <sched.h>

namespace {

class Value {
public:
  Value(std::string &f, int64_t v)
      : format(f), value(v) {}

  std::string format;
  int64_t value;
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
  char buf[2048];
  uint64_t time;

  for (int x = 0; x < loop_count; ++x) {
    time = measure([=, &buf, &values]() {
        for (auto &v : values) {
          sprintf(buf, v.format.c_str(), v.value);
        }
      });
  }

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
  std::string format_str;

  while (std::cin) {
    if (!std::getline(std::cin, format_str))
      break;
    if (!std::getline(std::cin, line))
      break;

    uint32_t n = atoi(line.c_str());
    int64_t value = 0;

    for (uint32_t i = 0; i < n; i++) {
      std::getline(std::cin, line);
      const char *c = line.c_str();
      if (!strncmp("i32:", c, 4)) {
      } else if (!strncmp("i64:", c, 4)) {
        value = atoll(c+4);
      } else if (!strncmp("f64:", c, 4)) {
      } else if (!strncmp("str:", c, 4)) {
      }
    }
    values.emplace_back(format_str, value);
  }

  run(loop_count, values);

  return 0;
}
