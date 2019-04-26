-- local Layer = require("dev.demo.scenes.layers.Layer")
-- require("dev.demo.scenes.layers.LayerIds")

 local winSize = cc.Director:getInstance():getWinSize()
 cc.exports.PopupLayer = class("PopupLayer",cc.Layer)


function PopupLayer:ctor()
	self.m_zorder = 100
	self:setLocalZOrder(self.m_zorder)
	self:setContentSize(winSize)

    
    self.m_pListener = cc.EventListenerTouchOneByOne:create()
    self.m_pListener:setSwallowTouches(true)
    self.m_pListener:registerScriptHandler(self.onTouchesBegan,cc.Handler.EVENT_TOUCH_BEGAN )
    self.m_pListener:registerScriptHandler(self.onTouchesMoved,cc.Handler.EVENT_TOUCH_MOVED )
    self.m_pListener:registerScriptHandler(self.onTouchesEnded,cc.Handler.EVENT_TOUCH_ENDED )
    self.m_pListener:registerScriptHandler(self.onTouchesCancelled,cc.Handler.EVENT_TOUCH_CANCELLED )
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(self.m_pListener, self)

	self.m_colorLayer = cc.LayerColor:create(cc.c4b(0, 0, 0, 200), winSize.width, winSize.height)
    self.m_colorLayer:setCascadeColorEnabled(false)
	self:addChild(self.m_colorLayer,-1)
	


	local item = ccui.Button:create()
		item:setContentSize(cc.size(300,40))
		item:setTitleText("Exit")		
		item:setTitleColor(cc.WHITE)--cc.c3b(_r,_g,_b))
		item:setTitleFontSize(40)
		item:setAnchorPoint(cc.p(1,1))
		item:setPressedActionEnabled(true)
		item:addClickEventListener(function(sender)
			self:exitPopupLayer()
		  end)

		self:addChild(item,1000)
		item:setPosition(display.width,display.height)


end

function PopupLayer:dtor()
end

function PopupLayer:onTouchesBegan()

end

function PopupLayer:onTouchesMoved()
	
end

function PopupLayer:onTouchesEnded()
	
end

function PopupLayer:onTouchesCancelled()
	
end

function PopupLayer:doExitPopupLayer()
		self:dtor()
	    self:removeFromParent()
end

function PopupLayer:exitPopupLayer(style)
	self:doExitPopupLayer()

end




return PopupLayer