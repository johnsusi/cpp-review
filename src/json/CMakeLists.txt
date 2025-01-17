add_library(json)

target_compile_features(json
    PUBLIC
        cxx_std_20
)

target_sources(json
    PRIVATE
        json.cpp
    PUBLIC 
        FILE_SET HEADERS
        BASE_DIRS ..
        FILES
            json.h
)

install(TARGETS json
    EXPORT RockSolidJsonTargets
    FILE_SET HEADERS
    COMPONENT json
)