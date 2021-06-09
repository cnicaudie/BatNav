cmake_minimum_required(VERSION 3.17)
project(BatNav)

set(CMAKE_CXX_STANDARD 14)

add_executable(BatNavProject main.cpp Engine/Game.cpp Engine/Game.h Engine/EngineIncludes.h Gameplay/GameManager.cpp Gameplay/GameManager.h Gameplay/Board/Board.cpp Gameplay/Board/Board.h Gameplay/GameplayIncludes.h Engine/Log/Log.h Engine/Input/InputManager.cpp Engine/Input/InputManager.h Engine/Event/EventManager.cpp Engine/Event/EventManager.h Engine/Event/Listener/IEventListener.cpp Engine/Event/Listener/IEventListener.h Engine/Event/Listener/EventListener.cpp Engine/Event/Listener/EventListener.h Engine/Event/EventTypes/Event.cpp Engine/Event/EventTypes/Event.h Engine/Event/EventTypes/EventType.h Engine/Event/EventTypes/ClickEvent.cpp Engine/Event/EventTypes/ClickEvent.h Gameplay/Boats/Boat.cpp Gameplay/Boats/Boat.h Engine/Maths/Maths.h UI/UIManager.cpp UI/UIManager.h UI/Button.cpp UI/Button.h UI/UIViewModel.cpp UI/UIViewModel.h Gameplay/Events/BoatEvent.cpp Gameplay/Events/BoatEvent.h)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(BatNavProject sfml-system sfml-window sfml-graphics sfml-audio sfml-network)