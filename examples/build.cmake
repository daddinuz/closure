add_library(adder ${CMAKE_CURRENT_LIST_DIR}/adder.h ${CMAKE_CURRENT_LIST_DIR}/adder.c)
target_link_libraries(adder PUBLIC closure)

add_executable(adder-main ${CMAKE_CURRENT_LIST_DIR}/adder-main.c)
target_link_libraries(adder-main PRIVATE adder)
