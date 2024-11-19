###################################################################################################
# CMake Build System for n2p2/libnnptrain
###################################################################################################

###################################################################################################
# Set Source Files
file(GLOB SRC_FILES "*.cpp")
file(GLOB HDR_FILES "*.h")
###################################################################################################

###################################################################################################
# Specify Build Targets
add_library(nnptrain ${SRC_FILES})   # Build libnnp.X library. (Shared, pass -D BUILD_SHARED_LIBS)
install(FILES ${HDR_FILES} DESTINATION ${PROJECT_INCLUDE})   # Headers copied at install time
###################################################################################################

###################################################################################################
# Find Required Package dependencies
find_package(MPI REQUIRED)
find_package(GSL REQUIRED)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)
include_directories(${MPI_INCLUDE_PATH} ${PROJECT_SOURCE_DIR}/libnnp ${GSL_INCLUDE_DIRS})
target_link_libraries(nnptrain MPI GSL Eigen3::Eigen)
###################################################################################################