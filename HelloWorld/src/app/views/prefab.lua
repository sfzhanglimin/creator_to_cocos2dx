
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local prefab = class("prefab", PopupLayer)

function prefab:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function prefab:dtor()

end

function prefab:init()

	--self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/prefab/prefab-test.ccreator")

	
	local creatorReader = creator.CreatorReader:createWithFilename("creator/Landlord/tx_lingqu_lihe.prefab.ccreator")
	creatorReader:setup()
	local node = creatorReader:getNodeGraph()
	self:addChild(node)
	node:setPosition(display.width/2,display.height/2)
	 
	self.m_aniManager  = UIUtils:getAniManager(creatorReader,self)
	self.m_aniManager:playAnimationClip(node,"tx_lingqu_lihe")

end




return prefab
