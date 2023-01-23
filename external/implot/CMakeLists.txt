cmake_minimum_required(VERSION 3.7.2)

project(implot)

add_library(implot
	./implot/implot.h
	./implot/implot_internal.h

	./implot/implot.cpp
	./implot/implot_demo.cpp
	./implot/implot_items.cpp
)

target_include_directories(implot PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/implot"
)

target_link_libraries(implot PUBLIC
	imgui
)

