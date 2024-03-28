
file(GLOB_RECURSE FMS_SRC
    src/*.cpp
    src/*.h
    *.cpp
)

add_library(FMS
    ${FMS_SRC}
)
