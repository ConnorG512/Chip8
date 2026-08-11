#include <contracts>
#include <print>
#include <source_location>

void handle_contract_violation(const std::contracts::contract_violation &cv)
{
  const std::source_location location {cv.location()};

  std::println("Found contract violation! Assert: [{}].", cv.comment());  
  std::println("File: [{}] at line [{}]\nFunction: {}.", location.file_name(), location.line(), location.function_name());
}
