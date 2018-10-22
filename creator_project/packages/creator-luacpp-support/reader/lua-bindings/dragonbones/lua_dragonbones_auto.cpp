#include "lua-bindings/dragonbones/lua_dragonbones_auto.hpp"
#include "Slot.h"
#include "Animation.h"
#include "AnimationState.h"
#include "WorldClock.h"
#include "Slot.h"
#include "Transform.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"


TOLUA_API int register_all_creator_dragonbones(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccdb",0);
	tolua_beginmodule(tolua_S,"ccdb");

	/*lua_register_creator_dragonbones_Slot(tolua_S);
	lua_register_creator_dragonbones_CCArmatureDisplay(tolua_S);
	lua_register_creator_dragonbones_Transform(tolua_S);
	lua_register_creator_dragonbones_EventObject(tolua_S);
	lua_register_creator_dragonbones_AnimationState(tolua_S);
	lua_register_creator_dragonbones_BaseFactory(tolua_S);
	lua_register_creator_dragonbones_Animation(tolua_S);
	lua_register_creator_dragonbones_CCFactory(tolua_S);
	lua_register_creator_dragonbones_Armature(tolua_S);
	lua_register_creator_dragonbones_WorldClock(tolua_S);
	lua_register_creator_dragonbones_Bone(tolua_S);*/

	tolua_endmodule(tolua_S);
	return 1;
}

