
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local collider = class("collider", PopupLayer)

function collider:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function collider:dtor()

end

function collider:init()

end




return collider
