#ifndef USER_DATA_OBJECT_LINK_PROXY_HPP
#define USER_DATA_OBJECT_LINK_PROXY_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "gizmo/link_proxy.hpp"
#include <string>


/**
 *  This is a proxy that implements linking and testing of linking between two
 *  EditorUserDataObjects
 */
class UserDataObjectLinkProxy : public LinkProxy
{
public:
    explicit UserDataObjectLinkProxy
    (
	    const std::string&		linkName,
		EditorChunkItemLinkable*	linker
    );

    /*virtual*/ ~UserDataObjectLinkProxy();

    /*virtual*/ LinkType EDCALL linkType() const;

    /*virtual*/ MatrixProxyPtr EDCALL createCopyForLink();

    /*virtual*/ TargetState EDCALL canLinkAtPos(ToolLocatorPtr locator) const;

    /*virtual*/ void EDCALL createLinkAtPos(ToolLocatorPtr locator);

    /*virtual*/ ToolLocatorPtr EDCALL createLocator() const;
	

private:
    UserDataObjectLinkProxy( UserDataObjectLinkProxy const & );
    UserDataObjectLinkProxy &operator=( UserDataObjectLinkProxy const & );

private:
    EditorChunkItemLinkable*		linker_;
	std::string					linkName_;
};


#endif // USER_DATA_OBJECT_LINK_PROXY_HPP
