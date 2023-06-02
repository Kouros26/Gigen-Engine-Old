local Player = 
 { 
    camera = nil,
    transform = nil,
    rigidBody = nil,
    moveSpeed = 5,
    sensitivity = 400,
    jumpForce = 10,
    isGrounded = false,
    jumpTimer = 0,
    life = 3,
    spwanPoint = Vector3.new(0,10,0),
    toRespawn = false,
    ShootSound = nil,
    isSoundPlaying = false,
 } 
 
 function Player:Awake() 
    self.ShootSound = self.owner:AddAudioSource()
    self.ShootSound:SetAudio("Engine/Audio/shot.mp3")
    self.ShootSound:SetLoop(false)
    self.ShootSound:SetVolume(0.5)
    self.ShootSound:PlayOnStart(false)
    self.ShootSound:Set3D(true)
 end
 
 
 function Player:Start() 
    Physics.Delegate("OnCollisionEnter")
    Physics.Delegate("OnCollisionExit")

    if (self.transform == nil) then
        self.transform = self.owner:GetTransform()
    end

    if (self.rigidBody == nil) then
        self.rigidBody = self.owner:GetRigidBody()
        self.rigidBody:SetAngularFactor(Vector3.new(0,0,0))
        self.rigidBody:SetGravity(Vector3.new(0,-0.25,0))
    end
    
    if (self.camera == nil) then
        self.camera = GameObjectManager.CreateCamera()
        self.owner:AddChild(self.camera)
        self.camera:GetTransform():SetPosition(Vector3.new(0, 0, 0))

    end

    if (self.ShootSound == nil) then
        self.ShootSound = self.owner:GetAudioSource(0)
        self.ShootSound:SetAudio("Engine/Audio/shot.mp3")
        self.ShootSound:SetLoop(false)
        self.ShootSound:SetVolume(0.5)
        self.ShootSound:PlayOnStart(false)
        self.ShootSound:Set3D(true)
    end


 end 
 
 function Player:Update(deltaTime) 
    local hit = HitResult.new()
    Physics.RayCast(self.transform:GetPosition(), -self.transform:GetUp() * 20, hit)
    if(Vector3.Distance(self.transform:GetPosition(),hit.hitPoint) < 7) then
        self.isGrounded = true
    else
        self.isGrounded = false
    end

    Move(deltaTime, self)
   
    Look(deltaTime, self)

    Jump(deltaTime, self)

    Descend(deltaTime, self)

    Shoot(deltaTime, self)

    if (self.toRespawn == true) then
        self.transform:SetPosition(self.spwanPoint)
        self.toRespawn = false
    end

    if (self.isSoundPlaying == true) then
        self.ShootSound:Play()
        self.isSoundPlaying = false
    end
  
 end
 

 function Look(deltaTime, this)
    local mouseDelta = Inputs.GetMousePos()
    local rotation = this.camera:GetTransform():GetRotation()
    if (mouseDelta.x == 0 and mouseDelta.y == 0 ) then
        return
    end
    if(mouseDelta.x > 0) then
        mouseDelta.x = 1
    elseif(mouseDelta.x < 0) then
        mouseDelta.x = -1
    end

    if(mouseDelta.y > 0) then
        mouseDelta.y = 1
    elseif(mouseDelta.y < 0) then
        mouseDelta.y = -1
    end
    
    rotation.y = rotation.y + mouseDelta.x * this.sensitivity * deltaTime
    rotation.x = rotation.x - mouseDelta.y * this.sensitivity * deltaTime


    this.camera:GetTransform():SetRotation(rotation)
 end

function CalculateFront(camera)
    local matrix = camera:GetTransform():GetMatrix()
   
    local inverse = Matrix4.Inverse(matrix)
    local front = Vector3.new(inverse[2].x, inverse[2].y, inverse[2].z)
    return front:Normalize()

end

function CalculateUp(camera)
    local matrix = camera:GetTransform():GetMatrix()
   
    local inverse = Matrix4.Inverse(matrix)
    local up = Vector3.new(inverse[1].x , inverse[1].y, inverse[1].z)
    return up:Normalize()
    
end

function CalculateRight(camera)
    local matrix = camera:GetTransform():GetMatrix()
   
    local inverse = Matrix4.Inverse(matrix)
    local right = Vector3.new(inverse[0].x, inverse[0].y, inverse[0].z)
    return right:Normalize()    
end


function Shoot(deltaTime, this)
    if Inputs.GetKey(Keys.F) then
       
        local hit = HitResult.new()
        
        Physics.RayCast(this.camera:GetTransform():GetWorldPosition(), this.camera:GetTransform():GetWorldPosition() + CalculateFront(this.camera) * 100, hit, RayCastDebug.OneFrame, 15)
        Debug.Log("Raycast")

        if(hit.hitObject ~= nil) then
            hit.hitObject:GetRigidBody():AddForce(CalculateFront(this.camera) * 20)
            Debug.Log(hit.hitObject:GetName())
        end
            this.isSoundPlaying = true
     
    end
    
end


 function Move(deltaTime, this)

    local moveDir = Vector3.new(0)
    if Inputs.GetKey(Keys.W) then
        moveDir = moveDir + CalculateFront(this.camera)
    elseif Inputs.GetKey(Keys.S) then
        moveDir = moveDir - CalculateFront(this.camera)
    end
    if Inputs.GetKey(Keys.A) then
        moveDir = moveDir + CalculateRight(this.camera)
    elseif Inputs.GetKey(Keys.D) then
        moveDir = moveDir - CalculateRight(this.camera)
    end
    moveDir = moveDir:Normalize()
    moveDir = moveDir * this.moveSpeed * deltaTime

    moveDir.y = 0
    

    this.transform:AddPosition(moveDir)

end

function Jump(deltaTime, this)
    
    if (this.isGrounded == false and this.jumpTimer > 2) then
        return
    end

    if (isGrounded == true) then
        this.jumpTimer = this.jumpTimer + deltaTime
 

    else
        this.jumpTimer = 0
    end


    local jumpDir = Vector3.new(0)
    if Inputs.GetKey(Keys.Space) then

        jumpDir = jumpDir + this.transform:GetUp()
    end
    jumpDir = jumpDir:Normalize()
    jumpDir = jumpDir * this.jumpForce * deltaTime

    local position = this.transform:GetPosition()
    position = position + jumpDir

    this.transform:SetPosition(position)
    
end

function Descend(deltaTime, this)
    local descendDir = Vector3.new(0)
    if Inputs.GetKey(Keys.LeftShift) then
        descendDir = descendDir - this.transform:GetUp()
    end
    descendDir = descendDir:Normalize()
    descendDir = descendDir * this.moveSpeed * deltaTime

    local position = this.transform:GetPosition()
    position = position + descendDir

    this.transform:SetPosition(position)

end



function OnCollisionEnter(otherActor)
    if(otherActor:GetName() == "KillerBox") then
        Player.life = Player.life - 1
        Player.toRespawn = true
        
    end
end

function OnCollisionExit(otherActor)

end
 
 return Player