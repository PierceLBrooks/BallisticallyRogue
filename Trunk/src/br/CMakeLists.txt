link_directories(${PROJECT_SOURCE_DIR}/../Oublietteer/Trunk/bin)

include_directories(${PROJECT_SOURCE_DIR}/../Oublietteer/Trunk/extlibs/SFML/include)
link_libraries(sfml-system-2 sfml-window-2 sfml-graphics-2 sfml-audio-2 sfml-network-2)

set(INC ${PROJECT_SOURCE_DIR}/include/br)
set(SRC ${PROJECT_SOURCE_DIR}/src/br)
set(DUNG_INC ${PROJECT_SOURCE_DIR}/../Oublietteer/Trunk/include/oublietteer)
set(DUNG_SRC ${PROJECT_SOURCE_DIR}/../Oublietteer/Trunk/src/oublietteer)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/../Oublietteer/Trunk/include)

set(PROJECT_FILES
	${SRC}/main.cpp
	${INC}/Ownable.hpp
	${SRC}/BallisticallyRogue.cpp
	${INC}/BallisticallyRogue.hpp
	${SRC}/Game.cpp
	${INC}/Game.hpp
	${SRC}/Grid.cpp
	${INC}/Grid.hpp
	${SRC}/Player.cpp
	${INC}/Player.hpp
	${SRC}/Bullet.cpp
	${INC}/Bullet.hpp
	${SRC}/Enemy.cpp
	${INC}/Enemy.hpp
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
