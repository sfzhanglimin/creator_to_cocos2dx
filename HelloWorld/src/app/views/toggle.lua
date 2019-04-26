
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local toggle = class("toggle", PopupLayer)

function toggle:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function toggle:dtor()

end

function toggle:init()

	self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/toggle/toggle.ccreator")

end




return toggle
