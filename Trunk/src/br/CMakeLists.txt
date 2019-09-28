link_directories(${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/extlibs/SFML/include)
link_libraries(sfml-system-2 sfml-window-2 sfml-graphics-2 sfml-audio-2 sfml-network-2)

set(INC ${PROJECT_SOURCE_DIR}/include/br)
set(SRC ${PROJECT_SOURCE_DIR}/src/br)
set(DUNG_INC ${PROJECT_SOURCE_DIR}/../Oublietteer/Trunk/include/oublietteer)
set(DUNG_SRC ${PROJECT_SOURCE_DIR}/../Oublietteer/Trunk/src/oublietteer)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(PROJECT_FILES
	${SRC}/main.cpp
	${SRC}/BallisticallyRogue.cpp
	${INC}/BallisticallyRogue.hpp
	${DUNG_SRC}/Oubliette.cpp
	${DUNG_INC}/Oubliette.hpp
	${DUNG_SRC}/Room.cpp
	${DUNG_INC}/Room.hpp
	${DUNG_SRC}/Floor.cpp
	${DUNG_INC}/Floor.hpp
	${DUNG_SRC}/Random.cpp
	${DUNG_INC}/Random.hpp
)

add_executable(BallisticallyRogue ${PROJECT_FILES})

set_property(TARGET BallisticallyRogue PROPERTY CXX_STANDARD 14)
set_property(TARGET BallisticallyRogue PROPERTY CXX_STANDARD_REQUIRED ON)
