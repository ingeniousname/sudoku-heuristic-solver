# CMakeList.txt : CMake project for sudoku, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (sudoku
	${CMAKE_CURRENT_SOURCE_DIR}/sudoku.c
	${CMAKE_CURRENT_SOURCE_DIR}/sudoku-grid/sudoku_grid.c
	${CMAKE_CURRENT_SOURCE_DIR}/solver/sudoku_solver_simple.c
	${CMAKE_CURRENT_SOURCE_DIR}/utils/utils.c
	${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.c
    )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sudoku PROPERTY C_STANDARD 11)
endif()

# TODO: Add tests and install targets if needed.
