cmake_minimum_required (VERSION 3.16)
project (dht11 CXX)

###################################################################################################
# SET ZONE
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-g")

set (CMAKE_CXX_STANDARD 17)
set (INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set (MODULES_DIR ${CMAKE_SOURCE_DIR}/modules)

###################################################################################################

###################################################################################################
# FILE ZONE
file (GLOB_RECURSE SRC
    ${MODULES_DIR}/*.cpp
    ${MODULES_DIR}/*.cc
    ${INCLUDE_DIR}/*.cpp
    ${INCLUDE_DIR}/*.cc
)

###################################################################################################

###################################################################################################
# ADD_EXECUTABLE ZONE
add_executable (${PROJECT_NAME}
    ${SRC}
    ${CMAKE_SOURCE_DIR}/main.cpp
)

###################################################################################################

###################################################################################################
# TARGET_INCLUDE_IDRECTORIES ZONE
target_include_directories (${PROJECT_NAME}
    PRIVATE
    ${INCLUDE_DIR}
    ${MODULES_DIR}

)

###################################################################################################

###################################################################################################
# TARGET_LINK_LIBRARIES ZONE
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    stdc++fs
    wiringPi
    pq
)

###################################################################################################

install (TARGETS ${PROJECT_NAME}
    DESTINATION
    /usr/local/bin
)
