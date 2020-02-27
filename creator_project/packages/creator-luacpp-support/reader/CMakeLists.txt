# reader lib for creator to cocos2d-x plugin
set(LIB_NAME creator_to_cocos2dx)

include_directories(
    collider
    animation
    dragonbones/cocos2dx
    dragonbones/armature
    dragonbones/animation
    dragonbones/events
    dragonbones/factories
    dragonbones/core
    dragonbones/geom
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${COCOS2DX_ROOT_PATH}/cocos/editor-support
)

set(CREATOR_TO_COCOS2DX_HEAD
    CreatorReader_generated.h
    CreatorReader.h
    animation/Easing.h
    animation/AnimateClip.h
    animation/Bezier.h
    animation/AnimationClipProperties.h
    animation/AnimationManager.h
    animation/AnimationClip.h
    collider/Collider.h
    collider/Intersection.h
    collider/ColliderManager.h
    collider/Contract.h
    Macros.h
    ui/RichtextStringVisitor.h
    ui/PageView.h
    ui/WidgetExport.h
)

set(CREATOR_TO_COCOS2DX_HEAD
    animation/AnimateClip.cpp
    animation/AnimationClip.cpp
    animation/AnimationManager.cpp
    animation/Easing.cpp
    animation/Bezier.cpp
    collider/Collider.cpp
    collider/ColliderManager.cpp
    collider/Contract.cpp
    collider/Intersection.cpp
    CreatorReader.cpp
    ui/PageView.cpp
    ui/RichtextStringVisitor.cpp
    ui/WidgetExport.cpp
)

if(BUILD_LUA_LIBS)
    list(APPEND CREATOR_TO_COCOS2DX
        lua-bindings/reader/lua_creator_reader_auto.hpp
        lua-bindings/reader/lua_creator_reader_manual.hpp
        lua-bindings/dragonbones/lua_dragonbones_auto.hpp
        lua-bindings/dragonbones/lua_dragonbones_manual.hpp
        lua-bindings/creator_reader_bindings.hpp
    )
    list(APPEND CREATOR_TO_COCOS2DX_HEAD
        lua-bindings/creator_reader_bindings.cpp
        lua-bindings/reader/lua_creator_reader_auto.cpp
        lua-bindings/reader/lua_creator_reader_manual.cpp
        lua-bindings/dragonbones/lua_dragonbones_manual.cpp
        lua-bindings/dragonbones/lua_dragonbones_auto.cpp
    )
endif()


add_library(${LIB_NAME} ${CREATOR_TO_COCOS2DX_HEAD} ${CREATOR_TO_COCOS2DX})

set_target_properties(${LIB_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    FOLDER "Internal"
)

add_subdirectory(dragonbones)
target_link_libraries(${LIB_NAME} dragonbones)

if(XCODE OR VS)
    cocos_mark_code_files(${LIB_NAME})
endif()
