cmake_minimum_required(VERSION 3.29)
project(cmps2131)

set(CMAKE_CXX_STANDARD 20)

# Function to add executables for all cpp files with main functions
function(add_subdir_executables base_dir)
    file(GLOB_RECURSE MAIN_SOURCES "${base_dir}/**/*.cpp")
    foreach(SOURCE_FILE ${MAIN_SOURCES})
        file(STRINGS ${SOURCE_FILE} CONTAINS_MAIN REGEX "^int main")
        if(CONTAINS_MAIN)
            # Generate a unique name based on the file path
            file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${SOURCE_FILE})
            string(REPLACE "/" "_" TARGET_NAME ${REL_PATH})
            string(REPLACE ".cpp" "" TARGET_NAME ${TARGET_NAME})

            add_executable(${TARGET_NAME} ${SOURCE_FILE})

            # Add any additional .cpp files in the same directory (excluding files with main)
            get_filename_component(SOURCE_DIR ${SOURCE_FILE} DIRECTORY)
            file(GLOB ADDITIONAL_SOURCES "${SOURCE_DIR}/*.cpp")
            foreach(ADDITIONAL_SOURCE ${ADDITIONAL_SOURCES})
                file(STRINGS ${ADDITIONAL_SOURCE} OTHER_CONTAINS_MAIN REGEX "^int main")
                if(NOT OTHER_CONTAINS_MAIN)
                    target_sources(${TARGET_NAME} PRIVATE ${ADDITIONAL_SOURCE})
                endif()
            endforeach()

            # Add the directory to include directories for this target
            target_include_directories(${TARGET_NAME} PRIVATE ${SOURCE_DIR})
        endif()
    endforeach()
endfunction()

# Add all executables in top-level directories
add_subdir_executables(${CMAKE_SOURCE_DIR}/practice)

# add_subdir_executables(${CMAKE_SOURCE_DIR}/other_directory)