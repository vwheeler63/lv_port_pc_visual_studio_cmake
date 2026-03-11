# CMakeList.txt : CMake project for lv_port_pc_visual_studio_cmake, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (LvglWindowsSimulator "LvglWindowsSimulator.cpp" "LvglWindowsSimulator.h" "LvglWindowsSimulator.rc")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LvglWindowsSimulator PROPERTY CXX_STANDARD 20)
endif()

# Link with libraries.
target_link_libraries(LvglWindowsSimulator lvgl lvgl_thorvg lvgl_examples lvgl_demos)
