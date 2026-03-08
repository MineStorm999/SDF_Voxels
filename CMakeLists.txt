cmake_minimum_required(VERSION 3.16)

project(SDF_Voxels LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# vk_bootstrap
FetchContent_Declare(
    fetch_vk_bootstrap
    GIT_REPOSITORY https://github.com/charles-lunarg/vk-bootstrap
    GIT_TAG         v1.4.344  #suggest using a tag so the library doesn't update whenever new commits are pushed to a branch
)
FetchContent_MakeAvailable(fetch_vk_bootstrap)

# glfw
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG        3.3.8
)
FetchContent_MakeAvailable(glfw)

# vulkan memory allocator
FetchContent_Declare(
    fetch_vma
    GIT_REPOSITORY https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator
    GIT_TAG         v3.3.0  #suggest using a tag so the library doesn't update whenever new commits are pushed to a branch
)
FetchContent_MakeAvailable(fetch_vma)

# glm
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

file(GLOB_RECURSE SHADER_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/*.hlsl
    ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/*.hlsli
)
message("${SHADER_SRC}")

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ShaderCompiler/bin/slangc
    COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/Shader.sh
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/.shaders.timestamp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DEPENDS "${SHADER_SRC}"
    COMMENT "Compiling Shaders..."
)

add_custom_target(ShaderCompiling ALL 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/.shaders.timestamp
)

add_executable(SDF_Voxels main.cpp App.cpp)

target_include_directories(SDF_Voxels PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/ShaderCompiler/lib")
target_link_libraries(SDF_Voxels vk-bootstrap::vk-bootstrap GPUOpen::VulkanMemoryAllocator glfw glm::glm slang)


include(GNUInstallDirs)
install(TARGETS SDF_Voxels
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
