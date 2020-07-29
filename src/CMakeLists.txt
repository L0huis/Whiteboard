
add_executable(
	Whiteboard WIN32
	App.hpp
	App.cpp
	Main.hpp
	Main.cpp
	Whiteboard.hpp
	Whiteboard.cpp
)

target_link_libraries(
	Whiteboard PRIVATE 
	project_options
	project_warnings
	CONAN_PKG::docopt.cpp
	CONAN_PKG::fmt
	CONAN_PKG::spdlog
	CONAN_PKG::wxwidgets
)


