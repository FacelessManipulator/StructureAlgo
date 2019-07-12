#include <chrono>
#include <iostream>
#include <functional>

namespace Faceless {
namespace Timing {
void run(std::function<void()> fn , int loops = 1) {
  auto start = std::chrono::steady_clock::now();
  for (int loop = 1; loop <= loops; ++loop) {
    fn();
  }
  auto end = std::chrono::steady_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution " << loops << " loop cost ";
  if (duration.count() > 10000) {
    std::cout << duration.count()/1000 << " ms" << std::endl;
  } else {
    std::cout << duration.count() << " us" << std::endl;
  }
}
};  // namespace Timing
};  // namespace Faceless