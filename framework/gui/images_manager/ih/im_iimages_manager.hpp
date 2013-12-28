
#ifndef __IM_IIMAGES_MANAGER_HPP__
#define __IM_IIMAGES_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace ImagesManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_IMAGES_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IImagesManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct TransformationData
	{
		explicit TransformationData( const QRect& _rect )
			:	m_rect( _rect )
			,	m_mirroredByVertical( false )
			,	m_mirroredByHorizontal( false )
		{}

		TransformationData(
				const QRect& _rect
			,	const bool _mirroredByVertical
			,	const bool _mirroredByHorizontal
			)
			:	m_rect( _rect )
			,	m_mirroredByVertical( _mirroredByVertical )
			,	m_mirroredByHorizontal( _mirroredByHorizontal )
		{}

		const QRect m_rect;

		const bool m_mirroredByVertical;
		const bool m_mirroredByHorizontal;
	};

/*---------------------------------------------------------------------------*/

	virtual const QPixmap& getPixmap( const QString& _resourcePath ) = 0;

	virtual const QPixmap& getPixmap(
			const QString& _resourcePath
		,	const TransformationData& _transformationData ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ImagesManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __IM_IIMAGES_MANAGER_HPP__
