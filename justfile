configure buildType="Debug" compileCommands="ON":
  @printf "Running configure...\n"
  cmake -B build -S . -G Ninja \
    -DCMAKE_BUILD_TYPE={{buildType}} \
    -DCMAKE_EXPORT_COMPILE_COMMANDS={{compileCommands}}

build:
  @printf "Running build...\n"
  cmake --build ./build
