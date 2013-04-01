#ifndef CHUNK_ITEM_PLACER_HPP
#define CHUNK_ITEM_PLACER_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "chunk/chunk_item.hpp"
#include "gizmo/undoredo.hpp"

//change 2010-3-5
//将类声明放到hpp文件来
//添加static ChunkItemGroupPtr createDBChunkItem()用于动态添加物体
class ChunkItemPlacer
{
	typedef ChunkItemPlacer This;
public:
	PY_MODULE_STATIC_METHOD_DECLARE( py_createChunkItem )
	PY_MODULE_STATIC_METHOD_DECLARE( py_deleteChunkItems )
	PY_MODULE_STATIC_METHOD_DECLARE( py_cloneChunkItems )

	//change 添加指定的模型
	static ChunkItemPtr createDBChunkItem(
		const char * namePath,
		const std::string &modelGUID,
		const float & posX,
		const float & posY,
		const float & posZ,
		const float & rotX,
		const float & rotY,
		const float & rotZ,
		const float & scaleX,
		const float & scaleY,
		const float & scaleZ,
		bool selected = true );
	
	//static ChunkItemPtr createDBChunkItem(
	//	const char * namePath,
	//	const std::string &modelGUID,
	//	const Vector3 &pos,
	//	const Vector3 &dir,
	//	const Vector3 &scale);

	//change 重载模型创建，增加是否创建后对象存于选中状态
	static ChunkItemPtr createDBChunkItem(
		const char * namePath,
		const std::string &modelGUID,
		const Vector3 &pos,
		const Vector3 &dir,
		const Vector3 &scale,
		bool selected = true );

	static ChunkItemPtr createDBChunkParticularItem(
		const char * namePath,
		const std::string &particularGUID,
		const float & posX,
		const float & posY,
		const float & posZ,
		const float & rotX,
		const float & rotY,
		const float & rotZ,
		const float & scaleX,
		const float & scaleY,
		const float & scaleZ,
		bool selected = true );
	
	// UserDataObject
	static ChunkItemPtr createUDOChunkItem(
		const Matrix& transform_,
		const std::string& guid_ = "",
		const std::string& chunkID_ = "",
		const std::string& nextGUID_ = "",
		const std::string& nextChunkID_ = "",
		const std::string& backGUID_ = "",
		const std::string& backChunkID_ = "",
		bool selected = true
	);
private:
	static void removeFromSelected( ChunkItemPtr pItem );
};

class ChunkItemExistenceOperation : public UndoRedo::Operation
{
public:
	ChunkItemExistenceOperation( ChunkItemPtr pItem, Chunk * pOldChunk ) :
		UndoRedo::Operation( 0 ),
		pItem_( pItem ),
		pOldChunk_( pOldChunk )
	{
		addChunk( pOldChunk_ );
		if( pItem_ )
			addChunk( pItem_->chunk() );
	}

protected:

	virtual void undo();

	virtual bool iseq( const UndoRedo::Operation & oth ) const
	{
		// these operations never replace each other
		return false;
	}

	ChunkItemPtr	pItem_;
	Chunk			* pOldChunk_;
};


class LinkerExistenceOperation : public ChunkItemExistenceOperation
{
public:
	LinkerExistenceOperation( ChunkItemPtr pItem, Chunk * pOldChunk ) :
		ChunkItemExistenceOperation( pItem, pOldChunk )	{}

protected:
	/*virtual*/ void undo();
};


class CloneNotifier
{
	static std::set<CloneNotifier*>* notifiers_;
public:
	CloneNotifier()
	{
		if( !notifiers_ )
			notifiers_ = new std::set<CloneNotifier*>;
		notifiers_->insert( this );
	}
	~CloneNotifier()
	{
		notifiers_->erase( this );
		if( notifiers_->empty() )
		{
			delete notifiers_;
			notifiers_ = NULL;
		}
	}
	virtual void begin() = 0;
	virtual void end() = 0;

	static void beginClone()
	{
		if( notifiers_ )
		{
			for( std::set<CloneNotifier*>::iterator iter = notifiers_->begin();
				iter != notifiers_->end(); ++iter )
			{
				(*iter)->begin();
			}
		}
	}
	static void endClone()
	{
		if( notifiers_ )
		{
			for( std::set<CloneNotifier*>::iterator iter = notifiers_->begin();
				iter != notifiers_->end(); ++iter )
			{
				(*iter)->end();
			}
		}
	}
	class Guard
	{
	public:
		Guard()
		{
			CloneNotifier::beginClone();
		}
		~Guard()
		{
			CloneNotifier::endClone();
		}
	};
};


#endif // CHUNK_ITEM_PLACER_HPP
