
file(GLOB_RECURSE FMS_SRC
    lib/*.cpp
    lib/*.h
    *.cpp
)

add_library(FMS
    ${FMS_SRC}
)
