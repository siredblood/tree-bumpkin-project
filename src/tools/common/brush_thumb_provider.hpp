#ifndef BRUSH_THUMB_PROVIDER_HPP
#define BRUSH_THUMB_PROVIDER_HPP


#include "ual/image_thumb_prov.hpp"


/**
 *	This class helps generate thumbnails for .brush files.
 */
class BrushThumbProvider : public ThumbnailProvider
{
public:
	virtual bool isValid( const ThumbnailManager& manager, const std::string& file );
	virtual bool prepare( const ThumbnailManager& manager, const std::string& file );
	virtual bool render( const ThumbnailManager& manager, const std::string& file, Moo::RenderTarget* rt );

protected:
	std::string getTextureFileForBrush( const std::string & file ) const;

private:
	DECLARE_THUMBNAIL_PROVIDER()

	ImageThumbProv		imageProvider_;
};


#endif // BRUSH_THUMB_PROVIDER_HPP
