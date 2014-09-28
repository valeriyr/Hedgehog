
-- Orc's Ai

local orcAISequence = {  }

function OrcAIThink( playerId )

	SystemMessenger:printMessage(IMessenger.Info, QString("Orc's AI think function called for player " .. playerId))

	if #orcAISequence == 0 then
		return
	end

	if orcAISequence[1]:process() == true then
		table.remove(orcAISequence, 1)
	end
end

function OrcAIEventCallback( event )
end

AIManager:regAI( QString("SampleOrcAI"), QString("Orc"), QString("OrcAIThink"), QString("OrcAIEventCallback") )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Orc's AI has been initialized."))