
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local dragonbones = class("dragonbones", PopupLayer)

function dragonbones:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function dragonbones:dtor()

end

function dragonbones:init()

--	self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/dragon_bones/DragonBones.ccreator")
end




return dragonbones
