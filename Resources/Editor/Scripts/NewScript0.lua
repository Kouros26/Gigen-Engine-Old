local NewScript0 = 
 { 
 } 
 
 
 function NewScript0:Start() 
    HitResult1 = HitResult.new()

    if(Physics.RayCast(self.owner:GetTransform():GetPosition(), Vector3.Down() * 1000, HitResult1, RayCastDebug.Timer, 15)) 
    then
        Debug.Log("Hit")
          Debug.Log(tostring(HitResult1.hitObject:GetName()))
          Debug.Log(tostring(HitResult1.hitPoint))
    else
        Debug.Log("No Hit")
    end
 end 
 
 function NewScript0:Update(deltaTime) 
 
 end 
 
 return NewScript0