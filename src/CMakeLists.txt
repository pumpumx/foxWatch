

# Collect all cpp files recursively under src/app/*
file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/app/*.cpp"
)

# If you later want to split libraries (db, engine, net, util), I can generate that too.

# Create the executable
add_executable(foxwatch ${SOURCE_FILES})

# Include dirs for this target
target_include_directories(foxwatch
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Enable warnings (modern recommended)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(foxwatch PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(foxwatch PRIVATE /W4 /permissive-)
endif()

