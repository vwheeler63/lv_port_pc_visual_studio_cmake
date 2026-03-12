# LVGL for Visual Studio (CMake)

This is the LVGL simulator designed to run under Microsoft Visual Studio using CMake.

![Screenshot](Screenshot.png)



## The Problem this Project Solves

The LVGL library has files that frequently:

- move,
- change names,
- new files are added, and
- old files are removed.

This type of directory-structure change typically happens a few times per month.

Given this behavior, the legacy Visual Studio `.vcxproj` file is not particularly appropriate for projects like this because it forces users of the project to have to "jump through hoops" to re-generate the `.vcxproj` file every time the directory structure of LVGL changes.  While this can be done programmatically, this is neither predictable nor intuitive, and thus such a requirement is deemed as not being very user friendly.

This project solves that problem by incorporating Visual Studio's new-ish support for CMake.

If you ever get into trouble compiling, simply `Project > Configure lv_port_pc_visual_studio_cmake` or re-save the `LvglWindowsSimulator\CMakeLists.txt` file.  By default, Visual Studio initiates updating the CMake files automatically simply from the `CMakeLists.txt` file having a new timestamp.  If this is ever not enough, delete the entire contents of the project's `out/` directory (where CMake stores its files), forcing CMake to regenerate them from scratch, and the project will compile again.  Note:  you can do this from within Visual Studio by right-clicking the `out/` folder and selecting `Delete`.



## Cloning this Repository

To use this project, you will need to not only clone this repository, but also its submodules.  Do so in one step by:

```bash
git clone  --recurse-submodules  URL
```

Example:

```bash
git clone  --recurse-submodules  git@github.com:lvgl/lv_port_pc_visual_studio_cmake.git
```

### IMPORTANT!

Visual Studio `*.sln` and `*.vcxproj` files need to be deleted from the `lv_port_pc_visual_studio_cmake\freetype\` directory or else Visual Studio gravitates to them and thinks it is a traditional `*.vcxproj`-type project instead of a CMake project.  Do this before opening the folder in Visual Studio for the first time.  Files that must be deleted are:

- `lv_port_pc_visual_studio_cmake\freetype\MSBuild.sln`
- `lv_port_pc_visual_studio_cmake\freetype\builds\windows\` (all files except the 2 `*.c` files)





 ## Opening Project for the First Time

It is strongly recommended to use Visual Studio 2026 or newer due to its improved integration with CMake.

After carrying out the above steps above under **Cloning this Repository** (including deleting the files specified under the **IMPORTANT!** step), open it from Visual Studio by:

- `File > Open > Folder...`
- Select `path\to\lv_port_pc_visual_studio_cmake\`
  - Recognizing it as a CMake project and taking initial set-up actions can take 20-30 seconds depending on your system.
  - You can ignore messages like `[CMake] -- Could NOT find ZLIB (missing: ZLIB_LIBRARY ZLIB_INCLUDE_DIR)`.  A similar message will be generated for ZLIB, PNG, BZip2 and BrotliDec.
- If Visual Studio does not automatically generate the needed CMake files, get it to do so by:
  - `Project > Configure lv_port_pc_visual_studio_cmake`

Once this last step is completed, it is ready to build and run.

- `Build > Build All`
- `Debug > Start Debugging`



## Project Structure

The entry point for the program in this project is the `main()` function in `LvglWindowsSimulator.cpp`.

This project utilizes the LVGL library in the `lvgl/` directory, as well as the FreeType library in the `freetype/` directory used to generate fonts at run time for some examples.  Each has its own `CMakeLists.txt` file which takes part in the generation of the Ninja build files, which Visual Studio then utilizes to build the project, instead of using the traditional `.vcxproj` file.



## Changing the LVGL Example Demonstrated

By default, `LvglWindowsSimulator.cpp` runs the `lv_demo_widgets` example.  It does this by calling `lv_demo_widgets()`.  You will find the line which makes this call just above the `while(1)` loop at the end of the file.  To change which example is being run, simply comment out that line in `LvglWindowsSimulator.cpp` and add your own.  Example:

```cpp
lv_example_roller_1();
// lv_demo_widgets();
```

You can find the entire set of examples that LVGL ships with under `lvgl\examples\`.  You can easily navigate to the example code to see how it works by placing your cursor on the example call (e.g. `lv_example_roller_()`) and pressing `[F12]` or right-click and select `Go To Definition`.



## Updating LVGL

Periodically you may need or want to update the LVGL Git submodule to the current version or to a particular point in LVGL's version history.  Do so in the usual way.  If LVGL's directory structure has changed (likely), you will need to `Project > Configure lv_port_pc_visual_studio_cmake` or re-save the `LvglWindowsSimulator\CMakeLists.txt` file, or delete the entire contents of the project's `out/` directory (where CMake stores its files), forcing CMake to regenerate them from scratch, and the project will compile again.

**Note:**  Visual Studio *does not* automatically detect file updates in the `lvgl\` directory structure.  You will need to tell Visual Studio to re-generate the CMake files by `Project > Configure lv_port_pc_visual_studio_cmake`, and to rebuild the application by `Build > Build All` or `Build > Rebuild` before running the application again with the updated content.



## Modifying Project Structure

**Caution:**  In this project you do not modify this Visual Studio project in the traditional way.  Instead you modify the project by modifying the appropriate `CMakeLists.txt` file(s).  If you need to add experimental files to the LVGL file structure, for instance, simply `Project > Configure lv_port_pc_visual_studio_cmake` or re-save the `LvglWindowsSimulator\CMakeLists.txt` file, and CMake will update its internal file list to include the `.c/.cpp` file(s) you added.  If this is not enough for any reason, delete the entire contents of the project's `out/` directory (where CMake stores its files), forcing CMake to regenerate them from scratch, and the project will compile:  CMake takes care of adding the appropriate `*.c` and/or `*.cpp` file(s) that you added so that the project will thereafter use them.

If you need to add a top-level source file in the `LvglWindowsSimulator\` directory for any reason, you will need to also add it manually to the list of source files in the CMake `add_executable` command in the `LvglWindowsSimulator\CMakeLists.txt` file.  Visual Studio will respond according to its contents.

### Example:

Let's say you want to experiment with the example in `lv_example_roller_1.c`  without modifying the original file.

- From Visual Studio (or any editor), save that file to (for example) `my_roller_experiment.c` in the same directory as `lv_example_roller_1.c`.
- Rename the function from `lv_example_roller_1()` to `my_roller_experiment()`.
- In `lvgl\examples\widgets\lv_example_widgets.h`, add a prototype for your new function.
- `Project > Configure lv_port_pc_visual_studio_cmake` or re-save `LvglWindowsSimulator\CMakeLists.txt` to get CMake to update the generated CMake files.
- Build and run.

This works because `lvgl\env_support\cmake\os_desktop.cmake` (included by `lvgl\CMakeLists.txt`) contains several

```cmake
file(GLOB_RECURSE ...)
```

commands which automatically include:

- all `*.c` and `*.cpp` files contained in `lvgl\src\`,
- all `*.c` files contained in `lvgl\examples\`,
- etc.



## Further Reading

### CMake References

https://cmake.org/cmake/help/latest/

https://cmake.org/cmake/help/latest/manual/cmake.1.html

https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html



### LVGL References

https://github.com/lvgl/lvgl

https://docs.lvgl.io/master/

