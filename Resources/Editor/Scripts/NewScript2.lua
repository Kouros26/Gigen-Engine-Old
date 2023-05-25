local NewScript2 = 
 { 

 } 
 
 function NewScript2:Start() 
    Debug.Log("NewScript2:Start")
    Physics.Delegate("OnCollisionEnter")
    Physics.Delegate("OnCollisionExit")
 end 

 function OnCollisionEnter(OtherActor)
    Debug.Log("Collision From Lua")
    Debug.Log(OtherActor:GetName())
 end

function OnCollisionExit(OtherActor)
    Debug.Log("Exiting Collision")
    Debug.Log(OtherActor:GetName()) 
end


 function NewScript2:Update(deltaTime) 
 
 end 
 
 return NewScript2