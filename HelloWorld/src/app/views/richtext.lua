
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local richtext = class("richtext", PopupLayer)

function richtext:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function richtext:dtor()

end

function richtext:init()

	self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/richtext/CreatorRichtext.ccreator")


end




return richtext
