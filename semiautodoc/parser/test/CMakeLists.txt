cmake_minimum_required(VERSION 2.6)
project(basic_test)



##################################
# Download and install GoogleTest
##################################

include(ExternalProject)
ExternalProject_Add(gtest
  #URL https://github.com/google/googletest/archive/release-1.8.0.zip
  URL https://github.com/google/googletest/archive/release-1.10.0.zip
  #URL https://github.com/google/googletest/archive/master.zip
  # Comment above line, and uncomment line below to use subversion.
  # SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/ 
  # Uncomment line below to freeze a revision (here the one for 1.7.0)
  # SVN_REVISION -r700

  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  INSTALL_COMMAND ""
)
ExternalProject_Get_Property(gtest source_dir binary_dir)

#message(FATAL_ERROR ${source_dir})# /home/aleksandra/Documents/semiautodoc/semiautodoc/parser/test/build/gtest/src/gtest
message(${binary_dir}) #/home/aleksandra/Documents/semiautodoc/semiautodoc/parser/test/build/gtest/src/gtest-build


include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")


################################
# Unit Tests
################################
# Add test cpp file
add_executable( runUnitTests test-class-declaration.cpp test-function-declaration.cpp
 test-class-getcontent.cpp test-function-getcontent.cpp)



######################################
# Configure the test to use GoogleTest
######################################

#target_include_directories(runUnitTests PUBLIC ../include)

target_link_libraries(runUnitTests 
    ${binary_dir}/lib/libgmock.a 
    ${binary_dir}/lib/libgtest.a 
    pthread
    parser)

add_test(NAME runUnitTests COMMAND $<TARGET_FILE:runUnitTests>)