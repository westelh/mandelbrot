enable_testing()
find_package(GTest REQUIRED)
add_executable(gui_test
        anti_aliasing_test.cpp
        utils_test.cpp
        ${CMAKE_SOURCE_DIR}/gui/utils.cpp)
target_include_directories(gui_test PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/gui ${GTEST_INCLUDE_DIRS})
target_link_libraries(gui_test ${GTEST_BOTH_LIBRARIES})
add_test(gui_test gui_test)