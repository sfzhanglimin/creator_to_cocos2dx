
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local webview = class("webview", PopupLayer)

function webview:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function webview:dtor()

end

function webview:init()

end




return webview
