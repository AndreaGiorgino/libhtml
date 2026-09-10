cmake_minimum_required(VERSION 3.24)

#
# Target executables
#

set(
    SOURCE_FILES

    # HtmlNode
    ## indirectly testing get/set methods
    Test_HtmlNode_Ctor.cxx
    Test_HtmlNode_Copy.cxx
    Test_HtmlNode_Move.cxx

    Test_HtmlNode_Clear.cxx

    Test_HtmlNode_Decode.cxx
    Test_HtmlNode_Encode.cxx

    # HtmlNode
    ## indirectly testing get/set methods
    Test_HtmlDoc_Ctor.cxx
    Test_HtmlDoc_Copy.cxx
    Test_HtmlDoc_Move.cxx

    Test_HtmlDoc_Decode.cxx
    Test_HtmlDoc_Encode.cxx
)

create_test_sourcelist(
    TEST_SOURCELIST
    CommonCxxTests.cxx
    ${SOURCE_FILES}
)

#
# Target
#

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    CommonCxxTests
    ${TEST_SOURCELIST}
)

set_target_properties(
    CommonCxxTests
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_compile_options(
    CommonCxxTests
    PRIVATE -Wextra -Wall -pedantic
)

target_include_directories(
    CommonCxxTests
    PRIVATE $<TARGET_FILE_DIR:${PROJECT_NAME}>/include
)

target_link_libraries(
    CommonCxxTests
    PRIVATE ${PROJECT_NAME}
)

foreach(TEST_FILE ${SOURCE_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_test(
        NAME ${TEST_NAME}
        COMMAND CommonCxxTests ${TEST_NAME}
    )
endforeach()

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/PostBuild.cmake)
