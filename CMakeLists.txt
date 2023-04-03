cmake_minimum_required(VERSION 3.10)
project(ros2_r413d08)

# Compiler settings
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(ros2_modbus REQUIRED)
find_package(ros2_modbus_rtu REQUIRED)
find_package(remote_switch REQUIRED)

# Logic shared by all targets
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/ChangeLeafId.srv"
)
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

include_directories(
  include
  ${ros2_serial_INCLUDE_DIRS}
  ${ros2_modbus_INCLUDE_DIRS}
  ${ros2_modbus_rtu_INCLUDE_DIRS}
  ${remote_switch_INCLUDE_DIRS}
)

set(project_SOURCE_FILES
  src/node.cpp
  src/interface.cpp
)

set(project_LIBRARIES
  ${rclcpp_LIBRARIES}
  ${ros2_modbus_LIBRARIES}
  ${ros2_modbus_rtu_LIBRARIES}
  ${ros2_modbus_rtu_native_LIBRARIES}
  ${remote_switch_LIBRARIES}
  ${remote_switch_native_LIBRARIES}
)

set(project_DEPENDENCIES
  ament_index_cpp
  rclcpp
  ros2_modbus_rtu
  remote_switch
)

# Executable target
add_executable(${PROJECT_NAME}_standalone src/main.cpp ${project_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_standalone ${project_LIBRARIES} "${cpp_typesupport_target}")
ament_target_dependencies(${PROJECT_NAME}_standalone ${project_DEPENDENCIES})
install(TARGETS
  ${PROJECT_NAME}_standalone
  DESTINATION lib/${PROJECT_NAME}
)

# Library target
add_library(${PROJECT_NAME}_native ${project_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_native ${project_LIBRARIES} "${cpp_typesupport_target}")
ament_target_dependencies(${PROJECT_NAME}_native ${project_DEPENDENCIES})
ament_export_dependencies(${project_DEPENDENCIES} ${ros2_modbus_rtu_DEPENDENCIES} ${remote_switch_DEPENDENCIES})
install(TARGETS
  ${PROJECT_NAME}_native
  DESTINATION lib
)
install(
  DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
