Tools::Core::XmlLibrary::Tag rule
		=
			Tools::Core::XmlLibrary::Tag( "plugins" )
			[
				*Tools::Core::XmlLibrary::Tag( "plugin" )
				[
						Tools::Core::XmlLibrary::Attribute( "name", Tools::Core::XmlLibrary::AttributeType::String )
					&&
						Tools::Core::XmlLibrary::Attribute( "file", Tools::Core::XmlLibrary::AttributeType::String )
					&&
						Tools::Core::XmlLibrary::Attribute( "id", Tools::Core::XmlLibrary::AttributeType::Integer )
					&&
						Tools::Core::XmlLibrary::Attribute( "loadatstartup", Tools::Core::XmlLibrary::AttributeType::Integer )
				]
				.postHandle(
						boost::bind( &PluginsSerializer::onPluginElement, this, _1, _2, _3, _4 )
					,	Tools::Core::XmlLibrary::UIntAttributeExtructor( "id" )
					,	Tools::Core::XmlLibrary::BoolAttributeExtructor( "loadatstartup" )
					,	Tools::Core::XmlLibrary::StringAttributeExtructor( "name" )
					,	Tools::Core::XmlLibrary::StringAttributeExtructor( "file" )
					)
			];