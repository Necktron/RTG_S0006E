# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build"

# Include any dependencies generated for this target.
include projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/depend.make

# Include the progress variables for this target.
include projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/progress.make

# Include the compile flags for this target's objects.
include projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/flags.make

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.o: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/flags.make
projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.o: ../projects/NackensGrafik/code/GraphicsNode.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.o"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.o -c "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/GraphicsNode.cc"

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.i"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/GraphicsNode.cc" > CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.i

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.s"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/GraphicsNode.cc" -o CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.s

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/LightResource.cc.o: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/flags.make
projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/LightResource.cc.o: ../projects/NackensGrafik/code/LightResource.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/LightResource.cc.o"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NackensGrafik.dir/code/LightResource.cc.o -c "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/LightResource.cc"

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/LightResource.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NackensGrafik.dir/code/LightResource.cc.i"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/LightResource.cc" > CMakeFiles/NackensGrafik.dir/code/LightResource.cc.i

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/LightResource.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NackensGrafik.dir/code/LightResource.cc.s"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/LightResource.cc" -o CMakeFiles/NackensGrafik.dir/code/LightResource.cc.s

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.o: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/flags.make
projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.o: ../projects/NackensGrafik/code/MeshResource.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.o"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.o -c "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/MeshResource.cc"

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.i"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/MeshResource.cc" > CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.i

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.s"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/MeshResource.cc" -o CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.s

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.o: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/flags.make
projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.o: ../projects/NackensGrafik/code/Rasterizer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.o"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.o -c "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/Rasterizer.cc"

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.i"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/Rasterizer.cc" > CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.i

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.s"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/Rasterizer.cc" -o CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.s

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.o: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/flags.make
projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.o: ../projects/NackensGrafik/code/ShaderObject.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.o"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.o -c "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/ShaderObject.cc"

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.i"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/ShaderObject.cc" > CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.i

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.s"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/ShaderObject.cc" -o CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.s

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.o: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/flags.make
projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.o: ../projects/NackensGrafik/code/TextureResource.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.o"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.o -c "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/TextureResource.cc"

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.i"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/TextureResource.cc" > CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.i

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.s"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/TextureResource.cc" -o CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.s

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.o: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/flags.make
projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.o: ../projects/NackensGrafik/code/exampleapp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.o"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.o -c "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/exampleapp.cc"

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.i"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/exampleapp.cc" > CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.i

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.s"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/exampleapp.cc" -o CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.s

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/main.cc.o: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/flags.make
projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/main.cc.o: ../projects/NackensGrafik/code/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/main.cc.o"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NackensGrafik.dir/code/main.cc.o -c "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/main.cc"

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NackensGrafik.dir/code/main.cc.i"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/main.cc" > CMakeFiles/NackensGrafik.dir/code/main.cc.i

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NackensGrafik.dir/code/main.cc.s"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && /usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik/code/main.cc" -o CMakeFiles/NackensGrafik.dir/code/main.cc.s

# Object files for target NackensGrafik
NackensGrafik_OBJECTS = \
"CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.o" \
"CMakeFiles/NackensGrafik.dir/code/LightResource.cc.o" \
"CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.o" \
"CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.o" \
"CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.o" \
"CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.o" \
"CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.o" \
"CMakeFiles/NackensGrafik.dir/code/main.cc.o"

# External object files for target NackensGrafik
NackensGrafik_EXTERNAL_OBJECTS =

../bin/NackensGrafik: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/GraphicsNode.cc.o
../bin/NackensGrafik: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/LightResource.cc.o
../bin/NackensGrafik: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/MeshResource.cc.o
../bin/NackensGrafik: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/Rasterizer.cc.o
../bin/NackensGrafik: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/ShaderObject.cc.o
../bin/NackensGrafik: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/TextureResource.cc.o
../bin/NackensGrafik: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/exampleapp.cc.o
../bin/NackensGrafik: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/code/main.cc.o
../bin/NackensGrafik: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/build.make
../bin/NackensGrafik: engine/core/libcore.a
../bin/NackensGrafik: engine/render/librender.a
../bin/NackensGrafik: exts/glew/libglew.a
../bin/NackensGrafik: exts/glfw-3.1.1/src/libglfw3.a
../bin/NackensGrafik: exts/libimgui.a
../bin/NackensGrafik: exts/libnanovg.a
../bin/NackensGrafik: exts/libimgui.a
../bin/NackensGrafik: exts/libnanovg.a
../bin/NackensGrafik: projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable ../../../bin/NackensGrafik"
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NackensGrafik.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/build: ../bin/NackensGrafik

.PHONY : projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/build

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/clean:
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" && $(CMAKE_COMMAND) -P CMakeFiles/NackensGrafik.dir/cmake_clean.cmake
.PHONY : projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/clean

projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/depend:
	cd "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master" "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/projects/NackensGrafik" "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build" "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik" "/home/nacken/ojaaho-6/S0006E - RTG Prog/lab-env-master/build/projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : projects/NackensGrafik/CMakeFiles/NackensGrafik.dir/depend

