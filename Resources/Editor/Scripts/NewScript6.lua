local NewScript6 = 
 { 
 } 
 
 function NewScript6:Start() 
    Physics.Delegate("OnTriggerEnter")
    Physics.Delegate("OnTriggerExit")

 end 
 
 function NewScript6:Update(deltaTime) 
 
 end 


    function OnTriggerEnter(other)
        Debug.Log("OnTriggerEnter")
    end

    function OnTriggerExit(other)
        Debug.Log("OnTriggerExit")
    end


 
 return NewScript6