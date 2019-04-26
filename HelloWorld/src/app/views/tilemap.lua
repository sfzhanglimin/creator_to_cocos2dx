
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local tilemap = class("tilemap", PopupLayer)

function tilemap:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function tilemap:dtor()

end

function tilemap:init()

	self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/tilemap/CreatorTilemap.ccreator")

end




return tilemap
