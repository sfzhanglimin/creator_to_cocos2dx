
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local toggle_group = class("toggle_group", PopupLayer)

function toggle_group:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function toggle_group:dtor()

end

function toggle_group:init()

	self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/toggle_group/toggle_group.ccreator")
	
	


end




return toggle_group
