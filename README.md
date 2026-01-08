# Ray Tracing Image Generator

## Sample

![Ray Tracing Result](sample.jpg)

## Structure

```
raytracing_one_weekend/
├── include/          
├── src/             
├── build/           # 빌드 결과물 (git 제외)
└── CMakeLists.txt   # CMake 빌드 설정
```

## Requirement
- C++17 이상
- CMake 3.10 이상
- 컴파일러: GCC, Clang, 또는 MSVC

## Build

### Windows
```bash
cmake -B build
cmake --build build --config Release
```

### Linux/macOS
```bash
mkdir build
cd build
cmake ..
make
```

## Excute

```bash
# Windows
build\Release\raytracing_one_weekend.exe > image.ppm

# Linux/macOS
./build/raytracing_one_weekend > image.ppm
```

## Reference

- [Ray Tracing in One Weekend](https://raytracing.github.io/)