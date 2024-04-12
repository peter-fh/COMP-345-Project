#include <filesystem>
#include <iostream>

int main() {
  std::filesystem::path p = std::filesystem::current_path();
  std::cout << p << std::endl;
  return 0;
}
