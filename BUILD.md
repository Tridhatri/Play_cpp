# Building and Running C++ Examples

This guide shows you how to compile and run the C++ examples in this learning repository.

## Prerequisites

You need a C++ compiler that supports C++17 or later:
- **Windows**: 
  - Microsoft Visual C++ (cl) - Recommended, comes with Visual Studio
  - MinGW-w64 (g++) - Alternative option
- **Linux**: g++ or clang++
- **macOS**: Xcode Command Line Tools (includes clang++)

## Basic Compilation

### Single File Compilation

#### Using MSVC (cl) - Windows

```powershell
cl /EHsc /std:c++17 /W4 /Fe:output_name.exe source_file.cpp
```

**Example:**
```powershell
cl /EHsc /std:c++17 /W4 /Fe:example.exe 01_references/example.cpp
.\example.exe
```

#### Using g++ (MinGW/Linux/macOS)

```bash
g++ -std=c++17 -Wall -Wextra -o output_name source_file.cpp
```

**Example:**
```bash
g++ -std=c++17 -Wall -Wextra -o example 01_references/example.cpp
./example
```

### Flag Explanation

**MSVC (cl):**
- `/EHsc`: Enable C++ exception handling
- `/std:c++17`: Use C++17 standard (also supports /std:c++20)
- `/W4`: Warning level 4 (highest useful level)
- `/Fe:name`: Specify output executable name

**GCC (g++):**
- `-std=c++17`: Use C++17 standard (minimum required; C++20 works too)
- `-Wall`: Enable all common warnings
- `-Wextra`: Enable extra warnings
- `-o output_name`: Specify output executable name

## Module-by-Module Guide

### Module 01: References

**Using cl (MSVC):**
```powershell
cd 01_references
cl /EHsc /std:c++17 /W4 /Fe:example.exe example.cpp
.\example.exe

cl /EHsc /std:c++17 /W4 /Fe:exercise.exe exercise.cpp
.\exercise.exe
```

**Using g++:**
```bash
cd 01_references
g++ -std=c++17 -Wall -Wextra -o example example.cpp
./example

g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
./exercise
```

### Module 02: Function Overloading

**Using cl (MSVC):**
```powershell
cd 02_function_overloading
cl /EHsc /std:c++17 /W4 /Fe:example.exe example.cpp
.\example.exe
```

**Using g++:**
```bash
cd 02_function_overloading
g++ -std=c++17 -Wall -Wextra -o example example.cpp
./example
```

### Module 03: Classes Basics
```bash
cd 03_classes_basics
g++ -std=c++17 -Wall -Wextra -o example example.cpp
./example
```

### Module 04: Constructors & Destructors
```bash
cd 04_constructors_destructors
g++ -std=c++17 -Wall -Wextra -o example example.cpp
./example
```

### Module 05: Operator Overloading
```bash
cd 05_operator_overloading
g++ -std=c++17 -Wall -Wextra -o example example.cpp
./example
```

### Module 10: Smart Pointers
```bash
cd 10_smart_pointers
g++ -std=c++17 -Wall -Wextra -o example example.cpp
./example
```

### Module 12: Lambda Expressions
```bash
cd 12_lambda_expressions
g++ -std=c++17 -Wall -Wextra -o example example.cpp
./example
```

## Quick Compile All Script

### Windows (PowerShell)
A `compile_all.ps1` script is already included in the cpp folder. It automatically detects whether you have cl (MSVC) or g++ installed and uses the appropriate compiler.

Simply run:
```powershell
.\compile_all.ps1
```

The script content for reference:

```powershell
$modules = @(
    "01_references",
    "02_function_overloading",
    "03_classes_basics",
    "04_constructors_destructors",
    "05_operator_overloading",
    "10_smart_pointers",
    "12_lambda_expressions"
)

foreach ($module in $modules) {
    Write-Host "Compiling $module..." -ForegroundColor Green
    
    if (Test-Path "$module\example.cpp") {
        g++ -std=c++17 -Wall -Wextra -o "$module\example.exe" "$module\example.cpp"
        if ($LASTEXITCODE -eq 0) {
            Write-Host "  ✓ example.cpp compiled successfully" -ForegroundColor Cyan
        }
    }
    
    if (Test-Path "$module\exercise.cpp") {
        g++ -std=c++17 -Wall -Wextra -o "$module\exercise.exe" "$module\exercise.cpp"
        if ($LASTEXITCODE -eq 0) {
            Write-Host "  ✓ exercise.cpp compiled successfully" -ForegroundColor Cyan
        }
    }
    
    if (Test-Path "$module\solution.cpp") {
        g++ -std=c++17 -Wall -Wextra -o "$module\solution.exe" "$module\solution.cpp"
        if ($LASTEXITCODE -eq 0) {
            Write-Host "  ✓ solution.cpp compiled successfully" -ForegroundColor Cyan
        }
    }
}

Write-Host "`nAll compilations complete!" -ForegroundColor Green
```

Run with: `.\compile_all.ps1`

### Linux/macOS (Bash)
Create a file `compile_all.sh`:

```bash
#!/bin/bash

modules=(
    "01_references"
    "02_function_overloading"
    "03_classes_basics"
    "04_constructors_destructors"
    "05_operator_overloading"
    "10_smart_pointers"
    "12_lambda_expressions"
)

for module in "${modules[@]}"; do
    echo "Compiling $module..."
    
    if [ -f "$module/example.cpp" ]; then
        g++ -std=c++17 -Wall -Wextra -o "$module/example" "$module/example.cpp"
        [ $? -eq 0 ] && echo "  ✓ example.cpp compiled successfully"
    fi
    
    if [ -f "$module/exercise.cpp" ]; then
        g++ -std=c++17 -Wall -Wextra -o "$module/exercise" "$module/exercise.cpp"
        [ $? -eq 0 ] && echo "  ✓ exercise.cpp compiled successfully"
    fi
    
    if [ -f "$module/solution.cpp" ]; then
        g++ -std=c++17 -Wall -Wextra -o "$module/solution" "$module/solution.cpp"
        [ $? -eq 0 ] && echo "  ✓ solution.cpp compiled successfully"
    fi
done

echo ""
echo "All compilations complete!"
```

Make executable and run:
```bash
chmod +x compile_all.sh
./compile_all.sh
```

## Common Compilation Issues

### Issue: "cl not found" or "g++ not found"
**Solution**: Install a C++ compiler
- **Windows (Recommended)**: Install Visual Studio 2019 or later with "Desktop development with C++" workload
  - Or install "Build Tools for Visual Studio" (smaller download)
  - After installation, use "Developer Command Prompt for VS" or "Developer PowerShell for VS"
- **Windows (Alternative)**: Install MinGW-w64 from https://www.mingw-w64.org/
- **Linux**: `sudo apt install g++` (Ubuntu/Debian) or `sudo yum install gcc-c++` (RedHat/Fedora)
- **macOS**: `xcode-select --install`

### Issue: "error: 'make_unique' is not a member of 'std'"
**Solution**: Use C++14 or later: `-std=c++14` or `-std=c++17`

### Issue: Warnings about unused variables
**Solution**: This is normal during learning. You can:
- Fix the code to use all variables
- Remove `-Wextra` flag temporarily
- Add `(void)variable_name;` to suppress specific warnings

### Issue: "undefined reference to..."
**Solution**: Make sure you're compiling standalone example files, not incomplete exercise files with TODOs

## Debugging

To compile with debugging information:

**Using cl (MSVC):**
```powershell
cl /EHsc /std:c++17 /W4 /Zi /Fe:example.exe example.cpp
```
The `/Zi` flag adds debugging symbols for use with Visual Studio debugger.

**Using g++:**
```bash
g++ -std=c++17 -Wall -Wextra -g -o example example.cpp
```
The `-g` flag adds debugging symbols for use with gdb or lldb.

### Using gdb (Linux/Windows with MinGW)
```bash
gdb ./example
(gdb) run
(gdb) break main
(gdb) step
(gdb) print variable_name
(gdb) quit
```

### Using lldb (macOS)
```bash
lldb ./example
(lldb) run
(lldb) breakpoint set --name main
(lldb) step
(lldb) print variable_name
(lldb) quit
```

## Optimization Levels

**Using cl (MSVC):**

For learning, use no optimization or `/Od`:
```powershell
cl /EHsc /std:c++17 /W4 /Od /Zi /Fe:example.exe example.cpp
```

For performance testing:
- `/Od`: Disable optimization (default for debug)
- `/O1`: Minimize size
- `/O2`: Maximize speed (recommended for production)
- `/Ox`: Maximum optimization

**Example:**
```powershell
cl /EHsc /std:c++17 /O2 /Fe:example_optimized.exe example.cpp
```

**Using g++:**

For learning, use no optimization or `-O0`:
```bash
g++ -std=c++17 -O0 -g -o example example.cpp
```

For performance testing:
- `-O1`: Basic optimization
- `-O2`: Moderate optimization (recommended for production)
- `-O3`: Aggressive optimization

**Example:**
```bash
g++ -std=c++17 -O2 -Wall -Wextra -o example_optimized example.cpp
```

## Visual Studio Code Integration

If using VS Code, create `.vscode/tasks.json`:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build C++",
            "type": "shell",
            "command": "g++",
            "args": [
                "-std=c++17",
                "-Wall",
                "-Wextra",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"]
        }
    ]
}
```

Press `Ctrl+Shift+B` to build the currently open file.

## Tips

1. **Always compile with warnings enabled** (`-Wall -Wextra`) to catch common mistakes
2. **Start with examples**, understand them, then try exercises
3. **Compile frequently** - don't write too much code without testing
4. **Read compiler errors carefully** - they usually point to the exact problem
5. **Use version control** (git) to track your progress and experiments

## Next Steps

After setting up your build environment:

1. Start with Module 01 (References)
2. Compile and run the example
3. Read the code carefully
4. Try the exercises
5. Compare with solutions
6. Move to the next module

Happy coding! 🚀
