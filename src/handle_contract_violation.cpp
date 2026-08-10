#include <contracts>
#include <print>

void handle_contract_violation(const std::contracts::contract_violation &cv)
{
  std::println("Found contract violation {}", cv.comment());  
}
