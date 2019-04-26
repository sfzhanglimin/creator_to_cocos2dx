
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local pageview = class("pageview", PopupLayer)

function pageview:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function pageview:dtor()

end

function pageview:init()

	self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/pageview/pageview.ccreator")

end




return pageview
