XmlLib::IRule rule

	=
		XmlLib::Tag( "plugins" )
		[
			*XmlLib::Tag( "plugin" )
			[
				// Some tags
			]
			[
					XmlLib::Attribute( "id" )
				&&
					XmlLib::Attribute( "name" )
			]
			.handle()
			.postHandle()
		]