local NewScript3 = 
 { 
 } 
 
 function NewScript3:Start() 
    self.owner:AddAudioSource()
    Audio = self.owner:GetAudioSource(0)
    Audio:SetAudio("Audio/japanese_girl_sing_erika.mp3")

 end 
 
 function NewScript3:Update(deltaTime) 
    if(Inputs.GetKey(Keys.Space)) then
        Audio:Pause()
    elseif (Inputs.GetKey(Keys.P)) then
        Audio:UnPause()
    end
end
 
 return NewScript3