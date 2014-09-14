
#ifndef __LM_IREPLAY_SERIALIZER_HPP__
#define __LM_IREPLAY_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "xml_library/sources/handle/xl_handle.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class CommandsQueue;

/*---------------------------------------------------------------------------*/

struct IReplaySerializer
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void load(
			const QString& _filePath
		,	QString& _landscapeName
		,	ILandscapeModel::PlayersCollection& _players
		,	CommandsQueue& _commands ) = 0;

	virtual void save(
			const QString& _filePath
		,	const QString& _landscapeName
		,	const ILandscapeModel::PlayersCollection& _players
		,	const CommandsQueue& _commands ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IREPLAY_SERIALIZER_HPP__
