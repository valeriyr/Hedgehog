
-- Human's Ai

local humanAISequence = {  }

function HumanAIThink( playerId )

	SystemMessenger:printMessage(IMessenger.Info, QString("Human's AI think function called for player " .. playerId))

	if #humanAISequence == 0 then
		return
	end

	if humanAISequence[1]:process() == true then
		table.remove(humanAISequence, 1)
	end
end

function HumanAIEventCallback( event )
end

AIManager:regAI( QString("SampleHumanAI"), QString("Human"), QString("HumanAIThink"), QString("HumanAIEventCallback") )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Human's AI has been initialized."))