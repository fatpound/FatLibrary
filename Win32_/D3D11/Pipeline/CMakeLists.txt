fatlib_add_component(Win32_D3D11_Pipeline)

target_link_libraries(Win32_D3D11 INTERFACE Win32_D3D11_Pipeline)

add_subdirectory(Core)
add_subdirectory(Element)
add_subdirectory(Resource)
