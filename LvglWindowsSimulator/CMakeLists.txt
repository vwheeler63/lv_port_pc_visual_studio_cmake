# CMakeList.txt : CMake project for lv_port_pc_visual_studio_cmake, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(APP_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE SOURCES ${APP_ROOT_DIR}/*.c
                          ${APP_ROOT_DIR}/*.cpp
                          ${APP_ROOT_DIR}/*.h
                          ${APP_ROOT_DIR}/*.rc)

add_executable (LvglWindowsSimulator ${SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LvglWindowsSimulator PROPERTY CXX_STANDARD 20)
endif()

# Link with libraries.
target_link_libraries(LvglWindowsSimulator lvgl lvgl_thorvg lvgl_examples lvgl_demos)
