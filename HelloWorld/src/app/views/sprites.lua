
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local sprites = class("sprites", PopupLayer)

function sprites:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function sprites:dtor()

end

function sprites:init()

	self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/sprites/CreatorSprites.ccreator")

	local animation = UIUtils:seekNodeByName(self.m_root,"grossini_dance_08_1")
	self.m_aniManager:playAnimationClip(animation,"Animation1")
	
	


end




return sprites
