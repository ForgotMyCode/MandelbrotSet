cmake_minimum_required (VERSION 3.9)

SET(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

set (CMAKE_CXX_STANDARD 20)

project ("Mandelbrot")

add_executable (Mandelbrot "Mandelbrot.cpp" "Mandelbrot.h"
"imgui_demo.cpp" "imgui_draw.cpp" "imgui_impl_glfw.cpp" "imgui_impl_opengl3.cpp" "imgui_tables.cpp" "imgui_widgets.cpp" "imgui.cpp"
"imconfig.h" "imgui_impl_glfw.h" "imgui_impl_opengl3_loader.h" "imgui_impl_opengl3.h" "imgui_internal.h" "imgui.h" "imstb_rectpack.h" "imstb_textedit.h" "imstb_truetype.h"
   "opengl_image_wrapper.h" "check_util.h" "complex.h" "math_utils.h" "mandelbrot_gui.cpp" "mandelbrot_gui.h"  "mandelbrot_calculator.h" "mandelbrot_calculator.cpp" "opengl_image_wrapper.cpp" "color_palette.h")

find_package(glfw3 CONFIG REQUIRED)      
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(OpenGL REQUIRED)
link_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

find_package(OpenMP REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
