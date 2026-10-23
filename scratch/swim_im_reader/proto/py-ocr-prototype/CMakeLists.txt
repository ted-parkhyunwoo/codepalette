cmake_minimum_required(VERSION 3.16)
project(swim_ocr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs)
find_package(PkgConfig REQUIRED)
pkg_check_modules(TESSERACT REQUIRED IMPORTED_TARGET tesseract)

add_executable(swim_ocr_cpp swim_ocr.cpp)
target_include_directories(swim_ocr_cpp PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(swim_ocr_cpp PRIVATE ${OpenCV_LIBS} PkgConfig::TESSERACT)
target_compile_definitions(
    swim_ocr_cpp
    PRIVATE SWIM_OCR_TESSDATA_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/tessdata_for_samsung_health\"
)
