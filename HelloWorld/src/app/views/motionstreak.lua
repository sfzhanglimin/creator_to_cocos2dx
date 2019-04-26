
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local motionstreak = class("motionstreak", PopupLayer)

function motionstreak:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function motionstreak:dtor()

end

function motionstreak:init()
	local creatorReader = creator.CreatorReader:createWithFilename("creator/scenes/motionstreak/motionstreak.ccreator")
	creatorReader:setup()
	local node = creatorReader:getNodeGraph()
	self:addChild(node)
end




return motionstreak
