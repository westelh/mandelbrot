option(GUI "Enable option for displaying on monitor")
if(GUI)
    message("Display option is enabled")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTKMM gtkmm-3.0>=3.24.3 REQUIRED)

    set(CMAKE_CXX_STANDARD 20)
    add_executable(show
            ${CMAKE_SOURCE_DIR}/mandelbrot.cpp
            ${CMAKE_SOURCE_DIR}/bmp.cpp
            show-main.cpp
            bmp_canvas.h bmp_canvas.cpp
            anti_aliasing.cpp anti_aliasing.h
            utils.h utils.cpp)
    target_include_directories(show PRIVATE ${CMAKE_SOURCE_DIR} ${GTKMM_INCLUDE_DIRS})
    message(${GTKMM_INCLUDE_DIRS})
    target_link_directories(show PRIVATE ${GTKMM_LIBRARY_DIRS})
    target_link_libraries(show ${GTKMM_LIBRARIES} Threads::Threads)

    add_subdirectory(test)
endif()