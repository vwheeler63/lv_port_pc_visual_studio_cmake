# LVGL for Visual Studio (CMake)

This Visual Studio project uses LVGL to provide an easy start with LVGL on Windows.  It uses the CMake build-system generator, and works out of the box.

<figure style="text-align: center;">
    <img src="Screenshot.png" alt="Screenshot 1: LVGL Widgets Demo" style="max-width: 90%; height: auto;"/>
    <figcaption>Screenshot 1: &nbsp;LVGL Widgets Demo</figcaption>
</figure>


Visual Studio uses CMake (and its "downstream" tools) to:

- allow the user to view and navigate the project files as they exist in the directory structure,
- keep track of dependencies and other information needed to build it, and
- partially automate the project's adapting to directory-structure changes in the LVGL library (or in directories and files you create) when they happen.



## Usage

### Download Visual Studio

If you have not already done so, download and install Visual Studio:  https://visualstudio.microsoft.com/downloads/ .  You will need Visual Studio 2026 or newer due to its improved integration with CMake.  Specifically, you will also need to have the Visual Studio Installer include the "**Desktop development with C++**" workload tools, which brings CMake + Ninja integration into Visual Studio

### Clone this Repository

To use this project, you will need to not only clone this repository, but also its submodules.  Click the green [Code] button and copy the appropriate URL or command line.  The following shows how to clone this repository using the SSH URL:

```bash
git clone --recurse-submodules git@github.com:lvgl/lv_port_pc_visual_studio_cmake.git
```

 ### Opening Project for the First Time

- `File > Open > Folder...` (Not `Open Project/Solution...`—this is important.)

- Select `path/to/lv_port_pc_visual_studio_cmake/`
  - Recognizing it as a CMake project and taking initial set-up actions can take a 10-20 seconds depending on your system.  If properly recognized as a CMake project, you will see a project "splash screen" similar to Screenshot 2 below.

  <figure style="text-align: center;">
      <img src="VS2026_CMake_Splash_Screen.png" alt="Screenshot 2: VS2026 CMake Splash Screen" style="max-width: 90%; height: auto;"/>
      <figcaption>Screenshot 2: &nbsp;VS2026 Splash Screen for CMake Projects</figcaption>
  </figure>
  
- If it is not already doing so, ensure Visual Studio is displaying the Solution Explorer in "Folder View".  If it isn't, right click any part of the Solution Explorer panel and select "Switch to Folder View".

### Build and Run

The first time you run the project, and any time there is a directory structure change thereafter (e.g. you checkout the LVGL submodule at a specific version, or update it from the upstream repository):

- `Project > Configure lv_port_pc_visual_studio_cmake`
  - Note:  Visual Studio *does not* automatically detect changes to the directory structure under the `lvgl/` directory.  This is the step you need to do to update the "build files" to know about directory-structure changes.  Once it knows what files to monitor, the Ninja build system detects changed files for building.

- `Build > Reuild All`

- `Debug > Start Debugging`



## Notes



### Changing the LVGL Example Demonstrated

By default, `LvglWindowsSimulator.c` runs the `lv_demo_widgets` example by calling `lv_demo_widgets()`.  You will find this call just above the `while(1)` loop at the end of the file.  To change which example is being run, simply comment out that line in `LvglWindowsSimulator.c` and add your own.  Example:

```cpp
// lv_demo_widgets();
lv_example_roller_1();
```

Use Visual Studio's Intellisense to make it easy:

- type "lv\_example\_" or "lv\_demo\_",
- hit `Ctrl-Space` if the pop-up list of the available functions has not already opened, and
- select the example or demo you want to try.

The entire set of examples and demos that LVGL ships with can be found under:

- `lvgl/examples/`, and
- `lvgl/demos/`.



### Adding New Directories and Files

This project is modified by:

- making the appropriate modifications in the directory structure (e.g. to experiment or develop a firmware UI),

- modifying the appropriate `CMakeLists.txt` file(s), and

- `Project > Configure lv_port_pc_visual_studio_cmake`

#### Example 1

Let us say you want to experiment with the example in `lv_example_roller_1.c`  without modifying the original file.

- From Visual Studio (or any editor), save that file to (for example) `my_roller_experiment.c` in the same directory as `lv_example_roller_1.c`.
- Rename the function from `lv_example_roller_1()` to `my_roller_experiment()`.
- In `lvgl/examples/widgets/lv_example_widgets.h`, add a prototype for your new function.
- `Project > Configure lv_port_pc_visual_studio_cmake` or re-save `LvglWindowsSimulator/CMakeLists.txt` to get CMake to update the generated CMake files in the `out/` directory.
- Rebuild and run.

This works because `lvgl/env_support/cmake/os_desktop.cmake` (included by `lvgl/CMakeLists.txt`) contains several

```cmake
file(GLOB_RECURSE ...)
```

commands which automatically include:

- all `*.c` and `*.cpp` files contained in `lvgl/src/`,
- all `*.c` files contained in `lvgl/examples/`,
- etc.

#### Example 2

Let us say you want to develop a firmware UI on a PC using this project, and you want your firmware source files to live in a new directory:   `lv_port_pc_visual_studio_cmake/my_ui/`.  You can do so by following these steps:

- Create the subdirectory (e.g. `lv_port_pc_visual_studio_cmake/my_ui/`).  *Do not create a CMakeLists.txt file in that directory.*

- Edit `LvglWindowsSimulator/CMakeLists.txt` and supplement the `file(GLOB_RECURSE ...)` command in  like this (add the last 2 lines):

  ```cmake
  file(GLOB_RECURSE SOURCES ${APP_ROOT_DIR}/*.c
                            ${APP_ROOT_DIR}/*.cpp
                            ${APP_ROOT_DIR}/*.h
                            ${APP_ROOT_DIR}/*.rc
                            ${APP_ROOT_DIR}/../my_ui/*.c
                            ${APP_ROOT_DIR}/../my_ui/*.h)
  ```
  
- Re-generate the CMake Cache:  `Project > Configure lv_port_pc_visual_studio_cmake`.

-  Rebuild and run.




### Troubleshooting

If you ever get into trouble compiling, simply `Project > Configure lv_port_pc_visual_studio_cmake` or re-save the `LvglWindowsSimulator/CMakeLists.txt` file.  By default, Visual Studio initiates updating the CMake files automatically simply from the `CMakeLists.txt` file having a new timestamp.  If this is ever not enough, perform a `Build > Clean All` and then delete the entire contents of the project's `out/` directory (where CMake stores its files, a.k.a. "CMake Cache"), forcing CMake to regenerate them from scratch, and the project will compile again.



## Further Reading

### CMake References

https://cmake.org/cmake/help/latest/

https://cmake.org/cmake/help/latest/guide/user-interaction/index.html

https://cmake.org/cmake/help/latest/manual/cmake.1.html

https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html



### LVGL References

https://github.com/lvgl/lvgl

https://docs.lvgl.io/master/

