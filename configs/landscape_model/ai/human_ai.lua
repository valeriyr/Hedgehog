
-- Human's Ai

local aiSequence = { WaitGoal( 2 ), WaitGoal( 3 ) }

function HumanAi()

	if #aiSequence == 0 then
		return
	end

	if aiSequence[1]:process() == true then
		table.remove(aiSequence, 1)
	end
end

AiManager:regAi( QString("HumanAi"), QString("Human") )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Human's Ai has been initialized."))