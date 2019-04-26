
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local mask = class("mask", PopupLayer)

function mask:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function mask:dtor()

end

function mask:init()

	self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/Mask/Mask.ccreator")


end




return mask
