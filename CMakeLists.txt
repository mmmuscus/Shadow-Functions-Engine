cmake_minimum_required(VERSION 3.8)

project(Shadow_Functions_Engine CXX)

set(INCLUDE_FILES
    ${PROJECT_SOURCE_DIR}/headers/input/input.h

    ${PROJECT_SOURCE_DIR}/headers/output/movement.h
    ${PROJECT_SOURCE_DIR}/headers/output/output.h

    ${PROJECT_SOURCE_DIR}/headers/rendering/animation.h
    ${PROJECT_SOURCE_DIR}/headers/rendering/render.h
    ${PROJECT_SOURCE_DIR}/headers/rendering/shadowFunctions.h

    ${PROJECT_SOURCE_DIR}/headers/system/system.h
)

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/headers/input/input.cpp

    ${PROJECT_SOURCE_DIR}/headers/output/movement.cpp
    ${PROJECT_SOURCE_DIR}/headers/output/output.cpp

    ${PROJECT_SOURCE_DIR}/headers/rendering/animation.cpp
    ${PROJECT_SOURCE_DIR}/headers/rendering/render.cpp
    ${PROJECT_SOURCE_DIR}/headers/rendering/shadowFunctions.cpp

    ${PROJECT_SOURCE_DIR}/ShadowFunctionsEngine.cpp
)

add_executable(${PROJECT_NAME} ${INCLUDE_FILES} ${SOURCE_FILES})

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)