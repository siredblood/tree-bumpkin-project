#ifndef IMPORT_CODEC_BMP_HPP
#define IMPORT_CODEC_BMP_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "worldeditor/import/import_codec.hpp"


/**
 *  This codec reads/writes BMP data.
 */
class ImportCodecBMP : public ImportCodec
{
public:
    /*virtual*/ bool canHandleFile(std::string const &filename);

    /*virtual*/ LoadResult load
    (
        std::string         const &filename, 
        ImportImage			&image,
        float               *left           = NULL,
        float               *top            = NULL,
        float               *right          = NULL,
        float               *bottom         = NULL,
		bool				*absolute		= NULL,
        bool                loadConfigDlg   = false
    );

    /*virtual*/ bool save
    (
        std::string         const &filename, 
        ImportImage			const &image,
        float               *left           = NULL,
        float               *top            = NULL,
        float               *right          = NULL,
        float               *bottom         = NULL,
		bool				*absolute		= NULL,
		float				*minVal			= NULL,
		float				*maxVal			= NULL
    );

    /*virtual*/ bool canLoad() const;

    /*virtual*/ bool canSave() const;
};


#endif // IMPORT_CODEC_BMP_HPP