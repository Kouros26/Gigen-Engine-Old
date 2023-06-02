local KillerBox =
{
    rigidBody = nil,
    transform = nil,
}

function KillerBox:Awake()

    -- self.owner:SetModel("Engine/Models/Basics/Cube.FBX")
    self.owner:SetName("KillerBox")

    self.transform = self.owner:GetTransform()
    -- self.transform:SetPosition(Vector3.new(-10, 10, -10))
    -- self.transform:SetRotation(Vector3.new(0))
    -- self.transform:SetScale(Vector3.new(1))
        
    self.owner:CreateBoxRigidBody(Vector3.new(1), Vector3.new(1), 1)
    self.rigidBody = self.owner:GetRigidBody()
    self.rigidBody:SetGravity(Vector3.new(0,0,0))
end


function KillerBox:Start()

    if (self.transform == nil) then
        self.transform = self.owner:GetTransform()
    end

    if (self.rigidBody == nil) then
        self.rigidBody = self.owner:GetRigidBody()
    end
    
    
end

function KillerBox:Update()
    
    self.rigidBody:SetAngularVelocity(Vector3.new(0.1,0.75,0.5))

end

return KillerBox

