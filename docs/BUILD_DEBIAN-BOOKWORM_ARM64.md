# Building Starship
These build instructions are based on the upstream repository via their [GitHub Actions Workflow](https://github.com/HarbourMasters/Starship/blob/main/.github/workflows/linux.yml) and [build instructions](https://github.com/HarbourMasters/Starship/blob/main/docs/BUILDING.md).

## Build Starship
```
git clone --recursive https://github.com/HarbourMasters/starship.git && cd starship
git checkout tags/vx.x.x
cmake -H. -Bbuild-cmake -GNinja -DUSE_OPENGLES=1 -DBUILD_CROWD_CONTROL=0 -DCMAKE_BUILD_TYPE=Release
cmake --build build-cmake --config Release --target GeneratePortOTR
cmake --build build-cmake
```
