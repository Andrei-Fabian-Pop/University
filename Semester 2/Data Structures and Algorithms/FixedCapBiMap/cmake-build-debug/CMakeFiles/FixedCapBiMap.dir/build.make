﻿# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\FixedCapBiMap.dir\depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles\FixedCapBiMap.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\FixedCapBiMap.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\FixedCapBiMap.dir\flags.make

CMakeFiles\FixedCapBiMap.dir\App.cpp.obj: CMakeFiles\FixedCapBiMap.dir\flags.make
CMakeFiles\FixedCapBiMap.dir\App.cpp.obj: ..\App.cpp
CMakeFiles\FixedCapBiMap.dir\App.cpp.obj: CMakeFiles\FixedCapBiMap.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FixedCapBiMap.dir/App.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\FixedCapBiMap.dir\App.cpp.obj.d --working-dir="C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug" --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\FixedCapBiMap.dir\App.cpp.obj /FdCMakeFiles\FixedCapBiMap.dir\ /FS -c "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\App.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\App.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FixedCapBiMap.dir/App.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe > CMakeFiles\FixedCapBiMap.dir\App.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\App.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\App.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FixedCapBiMap.dir/App.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\FixedCapBiMap.dir\App.cpp.s /c "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\App.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\ExtendedTest.cpp.obj: CMakeFiles\FixedCapBiMap.dir\flags.make
CMakeFiles\FixedCapBiMap.dir\ExtendedTest.cpp.obj: ..\ExtendedTest.cpp
CMakeFiles\FixedCapBiMap.dir\ExtendedTest.cpp.obj: CMakeFiles\FixedCapBiMap.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/FixedCapBiMap.dir/ExtendedTest.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\FixedCapBiMap.dir\ExtendedTest.cpp.obj.d --working-dir="C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug" --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\FixedCapBiMap.dir\ExtendedTest.cpp.obj /FdCMakeFiles\FixedCapBiMap.dir\ /FS -c "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\ExtendedTest.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\ExtendedTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FixedCapBiMap.dir/ExtendedTest.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe > CMakeFiles\FixedCapBiMap.dir\ExtendedTest.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\ExtendedTest.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\ExtendedTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FixedCapBiMap.dir/ExtendedTest.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\FixedCapBiMap.dir\ExtendedTest.cpp.s /c "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\ExtendedTest.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\FixedCapBiMap.cpp.obj: CMakeFiles\FixedCapBiMap.dir\flags.make
CMakeFiles\FixedCapBiMap.dir\FixedCapBiMap.cpp.obj: ..\FixedCapBiMap.cpp
CMakeFiles\FixedCapBiMap.dir\FixedCapBiMap.cpp.obj: CMakeFiles\FixedCapBiMap.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/FixedCapBiMap.dir/FixedCapBiMap.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\FixedCapBiMap.dir\FixedCapBiMap.cpp.obj.d --working-dir="C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug" --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\FixedCapBiMap.dir\FixedCapBiMap.cpp.obj /FdCMakeFiles\FixedCapBiMap.dir\ /FS -c "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\FixedCapBiMap.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\FixedCapBiMap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FixedCapBiMap.dir/FixedCapBiMap.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe > CMakeFiles\FixedCapBiMap.dir\FixedCapBiMap.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\FixedCapBiMap.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\FixedCapBiMap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FixedCapBiMap.dir/FixedCapBiMap.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\FixedCapBiMap.dir\FixedCapBiMap.cpp.s /c "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\FixedCapBiMap.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\FixedCapBiMapIterator.cpp.obj: CMakeFiles\FixedCapBiMap.dir\flags.make
CMakeFiles\FixedCapBiMap.dir\FixedCapBiMapIterator.cpp.obj: ..\FixedCapBiMapIterator.cpp
CMakeFiles\FixedCapBiMap.dir\FixedCapBiMapIterator.cpp.obj: CMakeFiles\FixedCapBiMap.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/FixedCapBiMap.dir/FixedCapBiMapIterator.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\FixedCapBiMap.dir\FixedCapBiMapIterator.cpp.obj.d --working-dir="C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug" --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\FixedCapBiMap.dir\FixedCapBiMapIterator.cpp.obj /FdCMakeFiles\FixedCapBiMap.dir\ /FS -c "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\FixedCapBiMapIterator.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\FixedCapBiMapIterator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FixedCapBiMap.dir/FixedCapBiMapIterator.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe > CMakeFiles\FixedCapBiMap.dir\FixedCapBiMapIterator.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\FixedCapBiMapIterator.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\FixedCapBiMapIterator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FixedCapBiMap.dir/FixedCapBiMapIterator.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\FixedCapBiMap.dir\FixedCapBiMapIterator.cpp.s /c "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\FixedCapBiMapIterator.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\ShortTest.cpp.obj: CMakeFiles\FixedCapBiMap.dir\flags.make
CMakeFiles\FixedCapBiMap.dir\ShortTest.cpp.obj: ..\ShortTest.cpp
CMakeFiles\FixedCapBiMap.dir\ShortTest.cpp.obj: CMakeFiles\FixedCapBiMap.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/FixedCapBiMap.dir/ShortTest.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\FixedCapBiMap.dir\ShortTest.cpp.obj.d --working-dir="C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug" --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\FixedCapBiMap.dir\ShortTest.cpp.obj /FdCMakeFiles\FixedCapBiMap.dir\ /FS -c "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\ShortTest.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\ShortTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FixedCapBiMap.dir/ShortTest.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe > CMakeFiles\FixedCapBiMap.dir\ShortTest.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\ShortTest.cpp"
<<

CMakeFiles\FixedCapBiMap.dir\ShortTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FixedCapBiMap.dir/ShortTest.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\FixedCapBiMap.dir\ShortTest.cpp.s /c "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\ShortTest.cpp"
<<

# Object files for target FixedCapBiMap
FixedCapBiMap_OBJECTS = \
"CMakeFiles\FixedCapBiMap.dir\App.cpp.obj" \
"CMakeFiles\FixedCapBiMap.dir\ExtendedTest.cpp.obj" \
"CMakeFiles\FixedCapBiMap.dir\FixedCapBiMap.cpp.obj" \
"CMakeFiles\FixedCapBiMap.dir\FixedCapBiMapIterator.cpp.obj" \
"CMakeFiles\FixedCapBiMap.dir\ShortTest.cpp.obj"

# External object files for target FixedCapBiMap
FixedCapBiMap_EXTERNAL_OBJECTS =

FixedCapBiMap.exe: CMakeFiles\FixedCapBiMap.dir\App.cpp.obj
FixedCapBiMap.exe: CMakeFiles\FixedCapBiMap.dir\ExtendedTest.cpp.obj
FixedCapBiMap.exe: CMakeFiles\FixedCapBiMap.dir\FixedCapBiMap.cpp.obj
FixedCapBiMap.exe: CMakeFiles\FixedCapBiMap.dir\FixedCapBiMapIterator.cpp.obj
FixedCapBiMap.exe: CMakeFiles\FixedCapBiMap.dir\ShortTest.cpp.obj
FixedCapBiMap.exe: CMakeFiles\FixedCapBiMap.dir\build.make
FixedCapBiMap.exe: CMakeFiles\FixedCapBiMap.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable FixedCapBiMap.exe"
	"C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\FixedCapBiMap.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\FixedCapBiMap.dir\objects1.rsp @<<
 /out:FixedCapBiMap.exe /implib:FixedCapBiMap.lib /pdb:"C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug\FixedCapBiMap.pdb" /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\FixedCapBiMap.dir\build: FixedCapBiMap.exe
.PHONY : CMakeFiles\FixedCapBiMap.dir\build

CMakeFiles\FixedCapBiMap.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\FixedCapBiMap.dir\cmake_clean.cmake
.PHONY : CMakeFiles\FixedCapBiMap.dir\clean

CMakeFiles\FixedCapBiMap.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap" "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap" "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug" "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug" "C:\Users\andre\OneDrive\Desktop\UBB stuff\DSA\FixedCapBiMap\cmake-build-debug\CMakeFiles\FixedCapBiMap.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\FixedCapBiMap.dir\depend
