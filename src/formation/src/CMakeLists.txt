
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/model
)

add_subdirectory(lib)
add_subdirectory(model)

set(SRC
    main.cpp
    uav_node.cpp
)   
add_executable(${PROJECT_NAME}_node ${SRC})
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES} 
  FMS geo
)