
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local Label = class("Label", PopupLayer)

function Label:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function Label:dtor()

end

function Label:init()

	self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/Label/CreatorLabels.ccreator")

end




return Label
