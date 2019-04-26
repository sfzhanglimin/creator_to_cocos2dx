
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local video = class("video", PopupLayer)

function video:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function video:dtor()

end

function video:init()
end




return video
