cmake_minimum_required(VERSION 3.14)
project(GameStars)
set(CMAKE_CXX_STANDARD 17)
add_executable(GameStars main.cpp GameScene.cpp Character.cpp Enemy.h ExplosionImage.cpp ExplosionImage.h FastGame.cpp EndlessGame.cpp TargetEnemy.cpp Star.h Star.cpp WalkingEnemy.cpp ShootingEnemy.cpp ShootingEnemy.h Bullet.cpp)
set(SFML_ROOT C:/SFML-2.5.1)
set(SFML_STATIC_LIBRARIES FALSE)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED COMPONENTS system window graphics network audio)
if(SFML_FOUND)
    include_directories(C:/SFML-2.5.1/include)
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()