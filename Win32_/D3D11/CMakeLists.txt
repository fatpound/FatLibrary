fatlib_add_component(Win32_D3D11)

add_subdirectory(Pipeline)

target_link_libraries(Win32 PUBLIC Win32_D3D11)
