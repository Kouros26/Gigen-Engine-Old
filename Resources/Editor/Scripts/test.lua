-- Holds data that are shared between functions of this usertype
local test =
{
    elapsedTime = 0,
    
}



function test:Start()
    rigidBody = self.owner:GetRigidBody()
    if(rigidBody) then
        rigidBody:SetGravityEnabled(false)
    end
    
    transform = self.owner:GetTransform()
    transform:SetPosition(Vector3.new(0, 4, 0))
    self.owner:SetModel("Engine/Models/MinecraftVillage.fbx")

    transform:SetScale(Vector3.new(0.1))
   
end


-- Update function
function test:Update(dt)  
    transform = self.owner:GetTransform()
    move = Vector3.new()
    move.x = Tools.BoolToInt(Inputs.GetKey(Keys.J)) - Tools.BoolToInt(Inputs.GetKey(Keys.L))
    move.z = Tools.BoolToInt(Inputs.GetKey(Keys.I)) - Tools.BoolToInt(Inputs.GetKey(Keys.K))
    move = move * 10 * dt

    if(move ~= Vector3.Zero()) then
        transform:SetPosition(transform:GetPosition() + move)
        transform:LookAt(move, Vector3.Up())
    end
end

-- Returns the usertype so the engine has a reference to it
return test