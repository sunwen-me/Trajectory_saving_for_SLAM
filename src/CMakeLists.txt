cmake_minimum_required(VERSION 3.5)
project(test_pkg)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2_ros REQUIRED)

add_executable(save_traj_as_tum src/trajectorysave.cpp)
ament_target_dependencies(save_traj_as_tum rclcpp tf2_ros)

install(TARGETS save_traj_as_tum
  DESTINATION lib/${PROJECT_NAME})

ament_package()
