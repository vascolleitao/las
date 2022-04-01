#include "las/version/config.hpp"
#include "util.hpp"
#include <unistd.h>

GTEST_API_ int main(int argc, char** argv)
{
  // fmt::print("Running main() from {}\n", __FILE__);
  fmt::print("Running las version {}\n", las::version::to_string());
  fmt::print("Running las using {}\n", las::version::active_layers());

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
