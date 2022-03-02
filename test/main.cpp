#include "skl/version/config.hpp"
#include "util.hpp"
#include <unistd.h>

GTEST_API_ int main(int argc, char** argv)
{
  fmt::print("Running main() from {}\n", __FILE__);
  fmt::print("Running skl versio {}.{}.{}\n", skl::version::MAJOR, skl::version::MINOR, skl::version::PATCH);

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
