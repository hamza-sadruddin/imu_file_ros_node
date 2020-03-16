cmake_minimum_required(VERSION 2.8.3)
project(imu_file)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rosconsole
  sensor_msgs
)



catkin_package()

include_directories(

  ${catkin_INCLUDE_DIRS}
)

add_executable(imu_file_node src/imu_file.cpp)

target_link_libraries(imu_file_node ${catkin_LIBRARIES})

install(TARGETS imu_file_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
