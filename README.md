Generate the solution:
```
& 'C:\Program Files\CMake\bin\cmake' -S . -B "build/x64" -G "Visual Studio 17 2022" -T v143 -A x64
```

make sure you have the uncompressed rom on root (baserom.us.rev1.uncompressed.z64)

# Generate sf64.otr
& 'C:\Program Files\CMake\bin\cmake.exe' --build .\build\x64 --target ExtractAssets

Open the sln file and build.