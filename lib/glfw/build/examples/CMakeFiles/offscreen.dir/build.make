# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build

# Include any dependencies generated for this target.
include examples/CMakeFiles/offscreen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/offscreen.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/offscreen.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/offscreen.dir/flags.make

examples/CMakeFiles/offscreen.dir/offscreen.c.obj: examples/CMakeFiles/offscreen.dir/flags.make
examples/CMakeFiles/offscreen.dir/offscreen.c.obj: examples/CMakeFiles/offscreen.dir/includes_C.rsp
examples/CMakeFiles/offscreen.dir/offscreen.c.obj: ../examples/offscreen.c
examples/CMakeFiles/offscreen.dir/offscreen.c.obj: examples/CMakeFiles/offscreen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/offscreen.dir/offscreen.c.obj"
	cd /d C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build\examples && C:\PROGRA~2\MINGW-~1\I686-8~2.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT examples/CMakeFiles/offscreen.dir/offscreen.c.obj -MF CMakeFiles\offscreen.dir\offscreen.c.obj.d -o CMakeFiles\offscreen.dir\offscreen.c.obj -c C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\examples\offscreen.c

examples/CMakeFiles/offscreen.dir/offscreen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/offscreen.dir/offscreen.c.i"
	cd /d C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build\examples && C:\PROGRA~2\MINGW-~1\I686-8~2.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\examples\offscreen.c > CMakeFiles\offscreen.dir\offscreen.c.i

examples/CMakeFiles/offscreen.dir/offscreen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/offscreen.dir/offscreen.c.s"
	cd /d C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build\examples && C:\PROGRA~2\MINGW-~1\I686-8~2.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\examples\offscreen.c -o CMakeFiles\offscreen.dir\offscreen.c.s

examples/CMakeFiles/offscreen.dir/glfw.rc.obj: examples/CMakeFiles/offscreen.dir/flags.make
examples/CMakeFiles/offscreen.dir/glfw.rc.obj: ../examples/glfw.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building RC object examples/CMakeFiles/offscreen.dir/glfw.rc.obj"
	cd /d C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build\examples && C:\PROGRA~2\MINGW-~1\I686-8~2.0-P\mingw32\bin\windres.exe -O coff $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\examples\glfw.rc CMakeFiles\offscreen.dir\glfw.rc.obj

# Object files for target offscreen
offscreen_OBJECTS = \
"CMakeFiles/offscreen.dir/offscreen.c.obj" \
"CMakeFiles/offscreen.dir/glfw.rc.obj"

# External object files for target offscreen
offscreen_EXTERNAL_OBJECTS =

examples/offscreen.exe: examples/CMakeFiles/offscreen.dir/offscreen.c.obj
examples/offscreen.exe: examples/CMakeFiles/offscreen.dir/glfw.rc.obj
examples/offscreen.exe: examples/CMakeFiles/offscreen.dir/build.make
examples/offscreen.exe: src/libglfw3.a
examples/offscreen.exe: examples/CMakeFiles/offscreen.dir/linklibs.rsp
examples/offscreen.exe: examples/CMakeFiles/offscreen.dir/objects1.rsp
examples/offscreen.exe: examples/CMakeFiles/offscreen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable offscreen.exe"
	cd /d C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\offscreen.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/offscreen.dir/build: examples/offscreen.exe
.PHONY : examples/CMakeFiles/offscreen.dir/build

examples/CMakeFiles/offscreen.dir/clean:
	cd /d C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build\examples && $(CMAKE_COMMAND) -P CMakeFiles\offscreen.dir\cmake_clean.cmake
.PHONY : examples/CMakeFiles/offscreen.dir/clean

examples/CMakeFiles/offscreen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\examples C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build\examples C:\Users\mater\OneDrive\Documents\3DGameInCUsingOpenGL\lib\glfw\build\examples\CMakeFiles\offscreen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/offscreen.dir/depend

