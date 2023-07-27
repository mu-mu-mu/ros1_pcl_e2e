cmake_minimum_required(VERSION 3.0.2)
project(ros1_pcl_e2e)

set(DEFAULT_BUILD_TYPE "Release")

find_package(catkin REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  pcl_ros
  tf
  eigen_conversions
  pcl_conversions
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARY_DIRS})

add_executable(st   src/st.cpp)
include_directories(st include)
target_link_libraries(st
  ${catkin_LIBRARIES}
)
install(TARGETS st
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(intm   src/intm.cpp)
include_directories(intm include)
target_link_libraries(intm
  ${catkin_LIBRARIES}
)
install(TARGETS intm
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(end   src/end.cpp)
include_directories(end include)
target_link_libraries(end
  ${catkin_LIBRARIES}
)
install(TARGETS end
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
