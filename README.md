# hw\_btihot\_tuhna1

Homework for the course **"Btihot Tuhna"**.

## Project Structure

```
.
├── CMakeLists.txt
├── build/
└── src/
    ├── task1.cpp
    ├── task2.cpp
    ├── task3.cpp
    ├── task4.cpp
    ├── task5.cpp
    ├── service.cpp
    └── service.h
```

## How to Build

The recommended way to build the project is using CMake:

```bash
cd build
cmake ..
cmake --build .
```

Alternatively, you can compile individual programs manually using `g++`:

```bash
g++ src/task1.cpp src/service.cpp -o task1
g++ src/task2.cpp src/service.cpp -o task2
g++ src/task3.cpp src/service.cpp -o task3
g++ src/task4.cpp src/service.cpp -o task4
g++ src/task5.cpp src/service.cpp -o task5
```

## How to Run

After building, the binaries will be located in the `build` directory. Example:

```bash
./build/task1
```

If a program requires input parameters, it will prompt you in the terminal.

Each program corresponds to a specific task from Homework 1.

## Requirements

- `g++` compiler with C++14 support or higher
- CMake version 3.10 or later

## Testing

The project was built and tested on **Debian 12**.

## Feedback

For any questions, feel free to email: [romanva1@ac.sce.ac.il](mailto\:romanva1@ac.sce.ac.il)
