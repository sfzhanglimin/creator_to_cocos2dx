
local UIUtils =  {}


function UIUtils:seekNodeByName(node,name)
    
   -- print(node[".classname"])
    if node == nil then
    
        return 

    end

    if node:getName() == name then
        return node
    end
    local children = node:getChildren()


    if children ~= nil then
        for _,child in pairs(children) do
             local res = self:seekNodeByName(child,name)
            if (res ~= nil)  then
            
                return res
            end
             
        end

    end
    
end


function UIUtils:getRootNodeInCreator(creatorName)
    local creatorReader = creator.CreatorReader:createWithFilename(creatorName)
	creatorReader:setup()
	local scene = creatorReader:getNodeGraph()
	local root = UIUtils:seekNodeByName(scene,'root') 
	root:removeFromParent(false)
	return root,creatorReader
end

function UIUtils:getAniManager(creatorReader,root)
    local aniManager = creatorReader:getAnimationManager()
    aniManager:removeFromParent(false)
    root:addChild(aniManager)
	return aniManager
end

function UIUtils:getRootNodeInCreatorEx(parentNode,creatorName)

    local creatorReader = creator.CreatorReader:createWithFilename(creatorName)
	creatorReader:setup()
	local scene = creatorReader:getNodeGraph()
    local root = UIUtils:seekNodeByName(scene,'root') 
    root:retain()
    root:removeFromParent(false)
    parentNode:addChild(root)
    root:release()

    local aniManager = self:getAniManager(creatorReader,parentNode)

	return root,aniManager
end


local stringFind = string.find
function UIUtils:autoGenMember(table,node)

   if node == nil then
       return 
   end

   local children = node:getChildren()

   if children ~= nil then
       for _,child in pairs(children) do

           local cname = child:getName()
           if  stringFind(cname,"m_") then
               table[cname] = child
           end
           self:autoGenMember(table,child)
       end
   end 
end



return UIUtils