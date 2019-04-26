
local PopupLayer = require "app.views.PopupLayer"
local UIUtils = require "app.views.UIUtils"

local TestCreatorAni = class("TestCreatorAni", PopupLayer)

function TestCreatorAni:ctor()
	PopupLayer.ctor(self)
	self:init()
end

function TestCreatorAni:dtor()

end

function TestCreatorAni:init()

	self.m_root,self.m_aniManager = UIUtils:getRootNodeInCreatorEx(self,"creator/scenes/animation/CreatorAnim.ccreator")

	local animation = UIUtils:seekNodeByName(self.m_root,"grossini_dance_08_1")
	self.m_aniManager:playAnimationClip(animation,"Animation1")
	
	


end




return TestCreatorAni
