cmake_minimum_required(VERSION 3.7.2)

project(imgui)

add_library(imgui
	./imgui/imgui.h
	./imgui/imgui_internal.h
	./imgui/imconfig.h
	./imgui/imstb_rectpack.h
	./imgui/imstb_textedit.h
	./imgui/imstb_truetype.h

	./imgui/imgui.cpp
	./imgui/imgui_demo.cpp
	./imgui/imgui_draw.cpp
	./imgui/imgui_tables.cpp
	./imgui/imgui_widgets.cpp
)

target_include_directories(imgui PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/imgui"
)

########################

if(VCPKG_TARGET_TRIPLET)
	find_package(SDL2 CONFIG REQUIRED)
else() # HACK: fix sdl find module
	find_package(SDL2 REQUIRED)
endif()

add_library(imgui_impl_sdl
	./imgui/backends/imgui_impl_sdl.h
	./imgui/backends/imgui_impl_sdl.cpp
)

target_link_libraries(imgui_impl_sdl PUBLIC
	imgui
)

if(VCPKG_TARGET_TRIPLET)
	target_link_libraries(imgui_impl_sdl
		PUBLIC
			SDL2::SDL2
			SDL2::SDL2main
		#PRIVATE
			#SDL2::SDL2main
			#SDL2::SDL2-static
	)
else()
	target_include_directories(imgui_impl_sdl PUBLIC "${SDL2_INCLUDE_DIR}")
	target_link_libraries(imgui_impl_sdl PUBLIC ${SDL2_LIBRARY})
endif()


########################

add_library(imgui_impl_opengl3
	./imgui/backends/imgui_impl_opengl3.h
	./imgui/backends/imgui_impl_opengl3_loader.h
	./imgui/backends/imgui_impl_opengl3.cpp
)

#target_compile_definitions(imgui_impl_opengl3 PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_link_libraries(imgui_impl_opengl3 PUBLIC
	#glad
	imgui
)

if(UNIX)
	# imgui opengl now comes with its own loader
	target_link_libraries(imgui_impl_opengl3 PRIVATE dl)
endif()



