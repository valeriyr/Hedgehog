
-- Orc's Ai

local aiSequence = { WaitGoal( 2 ), WaitGoal( 3 ) }

function OrcAi()

	if #aiSequence == 0 then
		return
	end

	if aiSequence[1]:process() == true then
		table.remove(aiSequence, 1)
	end
end

AiManager:regAi( QString("OrcAi"), QString("Orc") )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Orc's Ai has been initialized."))