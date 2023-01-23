cmake_minimum_required(VERSION 3.7.2)

add_executable(rtimplot
	main.cpp
)

target_link_libraries(rtimplot
	glad

	imgui
	imgui_impl_opengl3
	imgui_impl_sdl

	implot
)


