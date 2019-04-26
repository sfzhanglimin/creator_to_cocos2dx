
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local slider = class("slider", PopupLayer)

function slider:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function slider:dtor()

end

function slider:init()

	self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/slider/slider.ccreator")
	
	


end




return slider
