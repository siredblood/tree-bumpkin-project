#ifndef EDITOR_CHUNK_SUBSTANCE
#define EDITOR_CHUNK_SUBSTANCE

#include "math/boundbox.hpp"

class   Chunk;
class   Model;
typedef SmartPointer<Model> ModelPtr;

/**
 *	This template class gives substance in the editor to items that
 *	are ordinarily without it.
 */
template <class CI> class EditorChunkSubstance : public CI
{
public:
	EditorChunkSubstance() { }
	~EditorChunkSubstance() { }

	bool load( DataSectionPtr pSection );
	bool load( DataSectionPtr pSection, Chunk * pChunk );

	virtual void toss( Chunk * pChunk );

	virtual bool edShouldDraw();
	virtual void draw();

	virtual void edBounds( BoundingBox& bbRet ) const;

	virtual const char * sectName() const = 0;
	virtual const char * drawFlag() const = 0;
	virtual ModelPtr reprModel() const = 0;

	virtual void addAsObstacle();	// usually don't override

	virtual DataSectionPtr pOwnSect()	{ return pOwnSect_; }
	virtual const DataSectionPtr pOwnSect()	const { return pOwnSect_; }

	bool reload();

	virtual bool addYBounds( BoundingBox& bb ) const;

protected:
	DataSectionPtr	pOwnSect_;

	static uint32	s_settingsMark_;
	static bool		s_drawAlways_;
};




#endif // EDITOR_CHUNK_SUBSTANCE