# Personal Finance Manager (C++)

A console-based personal finance manager with clean architecture and SQLite persistence.

## Features
- Add, view, filter, and delete expenses
- Add and view income
- Set and list budgets
- View summary totals and category spending breakdown
- Persist data in `finance.db` across restarts

## Requirements
- C++17 compiler (g++, clang, or MSVC)
- CMake 3.15+
- SQLite3 development library and headers

## Build
```powershell
cd c:\LearnAndCode\PersonalFinanceManagerCpp
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/Users/rucha.kukreti/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_PREFIX_PATH=C:/Users/rucha.kukreti/vcpkg/installed/x64-windows/share
cmake --build . --config Release
```

## Run
```powershell
cd c:\LearnAndCode\PersonalFinanceManagerCpp\build\Release
.\finance-manager.exe
```

## Tests
```powershell
cd c:\LearnAndCode\PersonalFinanceManagerCpp\build\Release
.\finance-manager-tests.exe
```

## Notes
- The project separates UI, business logic, persistence, and database schema initialization.
- Input validation and error handling are centralized in the service layer.
- The SQLite schema is automatically created at startup.
