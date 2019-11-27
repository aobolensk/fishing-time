file(GLOB_RECURSE headers "../include/*.h")
file(GLOB_RECURSE sources "./*.cpp")

add_library(${PROJECT_NAME}_lib ${sources} ${headers})
set_target_properties(${PROJECT_NAME}_lib PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
qt5_use_modules(${PROJECT_NAME}_lib Widgets)
