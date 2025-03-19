cmake_minimum_required(VERSION 3.30)
project(Ping_Pong)

set(CMAKE_CXX_STANDARD 20)

# Đặt đường dẫn đến thư viện SDL
set(SDL2_DIR "D:/SDL2/x86_64-w64-mingw32")
set(SDL2_IMAGE_DIR "D:/SDL2_image/x86_64-w64-mingw32")
set(SDL2_MIXER_DIR "D:/SDL2_mixer/x86_64-w64-mingw32")
set(SDL2_TTF_DIR "D:/SDL2_ttf/x86_64-w64-mingw32")

# Include directories
include_directories(
        "${SDL2_DIR}/include/SDL2"
        "${SDL2_IMAGE_DIR}/include/SDL2"
        "${SDL2_MIXER_DIR}/include/SDL2"
        "${SDL2_TTF_DIR}/include/SDL2"
)

# Link directories
link_directories(
        "${SDL2_DIR}/lib"
        "${SDL2_IMAGE_DIR}/lib"
        "${SDL2_MIXER_DIR}/lib"
        "${SDL2_TTF_DIR}/lib"
)

# Thêm định nghĩa để tắt warning SDL_main
add_compile_definitions(SDL_MAIN_HANDLED)

# Thêm các file nguồn của bạn
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/**/*.cpp")

# Tạo executable
add_executable(Ping_Pong ${SOURCES} Scripts/main.cpp
        Scripts/DEFS.cpp
        Scripts/BaseObject.cpp
        Scripts/Player.cpp
        Scripts/Entity.cpp
        Scripts/lib/Entity.h
        Scripts/lib/DEFS.h
        Scripts/lib/Player.h
        Scripts/lib/BaseObject.h
)

# Liên kết các thư viện SDL
target_link_libraries(Ping_Pong SDL2main SDL2 SDL2_image SDL2_mixer SDL2_ttf)
