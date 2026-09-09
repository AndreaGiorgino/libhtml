# libhtml

lib brief description

> [!IMPORTANT]
> Since this library is still in development, it may not work correctly or some
> functionalities might be missing

## Build

### Requirements

- [CMake](https://cmake.org/)

### Compilation

```bash
git clone https://github.com/AndreaGiorgino/libhtml
cd libhtml

./build.sh
```

### Debug

```bash
cmake -B build -DDEBUG=ON && \
    cmake --build build --parallel $(($(nproc) - 1))
```

### Testing

```bash
cmake -B build -DLIBHTML_BUILD_TESTING=ON && \
    cmake --build build --parallel $(($(nproc) - 1)) && \
    ctest --test-dir build 
```

### Example

```bash
cmake -B build -DLIBHTML_BUILD_EXAMPLE=ON && \
    cmake --build build --parallel $(($(nproc) - 1)) && \
    ./build/example/example
```

## Usage

Look at [example](example) for an example usage

### Quick reference

Name | Brief
:--- | :----
