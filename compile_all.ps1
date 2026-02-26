$modules = @(
    "01_references",
    "02_function_overloading",
    "03_classes_basics",
    "04_constructors_destructors",
    "05_operator_overloading",
    "10_smart_pointers",
    "12_lambda_expressions"
)

# Detect available compiler
$compiler = $null
$compilerName = ""

if (Get-Command cl -ErrorAction SilentlyContinue) {
    $compiler = "cl"
    $compilerName = "MSVC (cl)"
} elseif (Get-Command g++ -ErrorAction SilentlyContinue) {
    $compiler = "g++"
    $compilerName = "GCC (g++)"
} else {
    Write-Host "ERROR: No C++ compiler found!" -ForegroundColor Red
    Write-Host "Please install one of the following:" -ForegroundColor Yellow
    Write-Host "  - Visual Studio with C++ support (provides cl)" -ForegroundColor White
    Write-Host "  - MinGW-w64 (provides g++)" -ForegroundColor White
    exit 1
}

Write-Host "=====================================" -ForegroundColor Cyan
Write-Host "  C++ Learning Modules Compiler" -ForegroundColor Cyan
Write-Host "=====================================" -ForegroundColor Cyan
Write-Host "Compiler: $compilerName" -ForegroundColor Green
Write-Host ""

$totalCompiled = 0
$totalFailed = 0

foreach ($module in $modules) {
    Write-Host "Module: $module" -ForegroundColor Green
    
    if (Test-Path "$module\example.cpp") {
        Write-Host "   Compiling example.cpp... " -NoNewline
        
        if ($compiler -eq "cl") {
            cl /EHsc /std:c++17 /W4 /Fe:"$module\example.exe" "$module\example.cpp" 2>$null >$null
        } else {
            g++ -std=c++17 -Wall -Wextra -o "$module\example.exe" "$module\example.cpp" 2>$null
        }
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host "OK" -ForegroundColor Green
            $totalCompiled++
            # Clean up MSVC intermediate files
            if ($compiler -eq "cl") {
                Remove-Item "$module\*.obj" -ErrorAction SilentlyContinue
            }
        } else {
            Write-Host "FAILED" -ForegroundColor Red
            $totalFailed++
        }
    }
    
    if (Test-Path "$module\exercise.cpp") {
        Write-Host "   Compiling exercise.cpp... " -NoNewline
        
        if ($compiler -eq "cl") {
            cl /EHsc /std:c++17 /W4 /Fe:"$module\exercise.exe" "$module\exercise.cpp" 2>$null >$null
        } else {
            g++ -std=c++17 -Wall -Wextra -o "$module\exercise.exe" "$module\exercise.cpp" 2>$null
        }
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host "OK" -ForegroundColor Green
            $totalCompiled++
            if ($compiler -eq "cl") {
                Remove-Item "$module\*.obj" -ErrorAction SilentlyContinue
            }
        } else {
            Write-Host "SKIPPED (might have TODOs)" -ForegroundColor Yellow
        }
    }
    
    if (Test-Path "$module\solution.cpp") {
        Write-Host "   Compiling solution.cpp... " -NoNewline
        
        if ($compiler -eq "cl") {
            cl /EHsc /std:c++17 /W4 /Fe:"$module\solution.exe" "$module\solution.cpp" 2>$null >$null
        } else {
            g++ -std=c++17 -Wall -Wextra -o "$module\solution.exe" "$module\solution.cpp" 2>$null
        }
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host "OK" -ForegroundColor Green
            $totalCompiled++
            if ($compiler -eq "cl") {
                Remove-Item "$module\*.obj" -ErrorAction SilentlyContinue
            }
        } else {
            Write-Host "FAILED" -ForegroundColor Red
            $totalFailed++
        }
    }
    
    Write-Host ""
}

Write-Host "=====================================" -ForegroundColor Cyan
Write-Host "  Summary" -ForegroundColor Cyan
Write-Host "=====================================" -ForegroundColor Cyan
Write-Host "Successfully compiled: $totalCompiled" -ForegroundColor Green
if ($totalFailed -gt 0) {
    Write-Host "Failed: $totalFailed" -ForegroundColor Red
}
Write-Host ""
Write-Host "To run an example:" -ForegroundColor Yellow
Write-Host "  .\01_references\example.exe" -ForegroundColor White
Write-Host ""
