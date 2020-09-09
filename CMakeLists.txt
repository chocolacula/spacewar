cmake_minimum_required(VERSION 3.10)
project(spacewar)

set(CMAKE_CXX_STANDARD 17)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")

    if (NOT CMAKE_BUILD_TYPE MATCHES "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -s")
    endif ()
endif()

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

if (UNIX)
    find_package(glfw3 REQUIRED)
endif()

if (WIN32)
    set(GLFW_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
endif()

include_directories(${GLFW_INCLUDE_DIRS})

if (WIN32)
    add_compile_definitions(_USE_MATH_DEFINES)
endif()

include_directories(Engine)
include_directories(Engine/ECS)
include_directories(Engine/ECS/Component)
include_directories(Engine/ECS/Component/Embedded)
include_directories(Engine/ECS/Entity)
include_directories(Engine/ECS/System)
include_directories(Engine/ECS/System/Embedded)
include_directories(Engine/ECS/System/SystemQueue)
include_directories(Engine/Types)
include_directories(Engine/Utils)
include_directories(Game)
include_directories(Game/Components)
include_directories(Game/Components/Collider)
include_directories(Game/Systems)
include_directories(Game/Systems/UnitSystems)

add_executable(${PROJECT_NAME}
        Engine/ECS/Component/Embedded/Mesh.cpp
        Engine/ECS/Component/Embedded/Mesh.h
        Engine/ECS/Component/Embedded/Text.h
        Engine/ECS/Component/Embedded/Velocity.cpp
        Engine/ECS/Component/Embedded/Velocity.h
        Engine/ECS/Component/Component.cpp
        Engine/ECS/Component/Component.h
        Engine/ECS/Component/ComponentCollection.h
        Engine/ECS/Component/ComponentManager.h
        Engine/ECS/Entity/Entity.h
        Engine/ECS/Entity/EntityDef.h
        Engine/ECS/Entity/EntityManager.cpp
        Engine/ECS/Entity/EntityManager.h
        Engine/ECS/System/Embedded/InertiaSystem.cpp
        Engine/ECS/System/Embedded/InertiaSystem.h
        Engine/ECS/System/Embedded/MeshRenderSystem.cpp
        Engine/ECS/System/Embedded/MeshRenderSystem.h
        Engine/ECS/System/Embedded/MoveSystem.cpp
        Engine/ECS/System/Embedded/MoveSystem.h
        Engine/ECS/System/Embedded/TextRenderSystem.cpp
        Engine/ECS/System/Embedded/TextRenderSystem.h
        Engine/ECS/System/SystemQueue/SystemQueue.cpp
        Engine/ECS/System/SystemQueue/SystemQueue.h
        Engine/ECS/System/ISystem.h
        Engine/ECS/System/SystemManager.h
        Engine/ECS/ECS.h
        Engine/Types/Color.cpp
        Engine/Types/Color.h
        Engine/Types/Polar.cpp
        Engine/Types/Polar.h
        Engine/Types/Transform.cpp
        Engine/Types/Transform.h
        Engine/Types/Vector2.cpp
        Engine/Types/Vector2.h
        Engine/Utils/MathUtils.cpp
        Engine/Utils/MathUtils.h
        Engine/Utils/Random.cpp
        Engine/Utils/Random.h
        Engine/Utils/StringUtils.cpp
        Engine/Utils/StringUtils.h
        Engine/Engine.cpp
        Engine/Engine.h
        Engine/Input/Input.cpp
        Engine/Input/Input.h
        Engine/Scene.cpp
        Engine/Scene.h
        Game/Components/Collider/Collider.h
        Game/Components/Collider/ColliderLethal.h
        Game/Components/Collider/ColliderTarget.h
        Game/Components/Blast.cpp
        Game/Components/Blast.h
        Game/Components/Enemy.h
        Game/Components/GravityBigObject.h
        Game/Components/GravitySmallObject.h
        Game/Components/JetStreamParticles.cpp
        Game/Components/JetStreamParticles.h
        Game/Components/LifeTime.h
        Game/Components/Projectile.h
        Game/Components/ProjectileLauncher.h
        Game/Components/Rotor.h
        Game/Components/User.h
        Game/Systems/UnitSystems/EnemySystem.cpp
        Game/Systems/UnitSystems/EnemySystem.h
        Game/Systems/UnitSystems/ProjectileSubSystem.cpp
        Game/Systems/UnitSystems/ProjectileSubSystem.h
        Game/Systems/UnitSystems/UserInputSystem.cpp
        Game/Systems/UnitSystems/UserInputSystem.h
        Game/Systems/BlastSystem.cpp
        Game/Systems/BlastSystem.h
        Game/Systems/CollisionSystem.cpp
        Game/Systems/CollisionSystem.h
        Game/Systems/EndOfGameSystem.cpp
        Game/Systems/EndOfGameSystem.h
        Game/Systems/GravitySystem.cpp
        Game/Systems/GravitySystem.h
        Game/Systems/JetStreamSystem.cpp
        Game/Systems/JetStreamSystem.h
        Game/Systems/LifeTimeSystem.cpp
        Game/Systems/LifeTimeSystem.h
        Game/Systems/RotorSystem.cpp
        Game/Systems/RotorSystem.h
        Game/Systems/StarRenderSystem.cpp
        Game/Systems/StarRenderSystem.h
        Game/Game.cpp
        Game/Game.h
        Engine/main.cpp Engine/Input/Keyboard.h Engine/Input/Mouse.h)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY})

if (UNIX)
    target_link_libraries(${PROJECT_NAME} glfw)
else()
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/glfw3.lib)
endif()
