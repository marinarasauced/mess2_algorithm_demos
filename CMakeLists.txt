cmake_minimum_required(VERSION 3.8)
project(mess2_algorithm_demos)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(mess2_algorithm_threat_static REQUIRED)
find_package(mess2_algorithm_plugins REQUIRED)

include_directories(
  include
  ${mess2_algorithm_threat_static_INCLUDE_DIRS}
  ${mess2_algorithm_plugins_INCLUDE_DIRS}
)

# add_executable(demo_graph src/demo_graph.cpp)
# add_executable(demo_low_level_static src/demo_low_level_static.cpp)
# add_executable(demo_high_level_static src/demo_high_level_static.cpp)

add_executable(generate_graph src/generate_graph.cpp)
add_executable(generate_threat src/generate_threat.cpp)
add_executable(simulate_actors_2x src/simulate_actors_2x.cpp)
add_executable(simulate_actors_10x src/simulate_actors_10x.cpp)

# ament_target_dependencies(
#   demo_graph
#   "rclcpp"
#   "mess2_algorithm_threat_static"
#   "mess2_algorithm_plugins"
# )

# ament_target_dependencies(
#   demo_low_level_static
#   "rclcpp"
#   "mess2_algorithm_threat_static"
#   "mess2_algorithm_plugins"
# )

# ament_target_dependencies(
#   demo_high_level_static
#   "rclcpp"
#   "mess2_algorithm_threat_static"
#   "mess2_algorithm_plugins"
# )

ament_target_dependencies(
  generate_graph
  "rclcpp"
  "mess2_algorithm_threat_static"
  "mess2_algorithm_plugins"
)

ament_target_dependencies(
  generate_threat
  "rclcpp"
  "mess2_algorithm_threat_static"
  "mess2_algorithm_plugins"
)

ament_target_dependencies(
  simulate_actors_2x
  "rclcpp"
  "mess2_algorithm_threat_static"
  "mess2_algorithm_plugins"
)

ament_target_dependencies(
  simulate_actors_10x
  "rclcpp"
  "mess2_algorithm_threat_static"
  "mess2_algorithm_plugins"
)

install(
  TARGETS generate_graph generate_threat simulate_actors_2x simulate_actors_10x
  DESTINATION lib/${PROJECT_NAME}
)

# install(
#   DIRECTORY launch
#   DESTINATION share/${PROJECT_NAME}
# )

# ament_export_include_directories(include)
ament_package()