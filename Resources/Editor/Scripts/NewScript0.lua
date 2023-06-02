local NewScript0 = 
 { 
 } 
 
 function NewScript0:Start() 
 
 end 
 
 function NewScript0:Update(deltaTime) 
    self.owner:GetTransform():AddRotation(Vector3.new(0,300,0) * deltaTime)
 end 
 
 return NewScript0