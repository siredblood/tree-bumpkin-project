#ifndef EDITOR_CHUNK_MODEL_HPP
#define EDITOR_CHUNK_MODEL_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "chunk/chunk_model.hpp"
#include "romp/static_light_fashion.hpp"
#include "moo/visual.hpp"
#include "common/dxenum.hpp"
#include <set>
#include <map>
#include <string>

//GUID
#include "cstdmf/unique_id.hpp"

/**
 *	This class is the editor version of a ChunkModel
 */
class EditorChunkModel : public ChunkModel
{
	static uint32 s_settingsMark_;
	DECLARE_EDITOR_CHUNK_ITEM( EditorChunkModel )
	DECLARE_CHUNK_ITEM_ALIAS( EditorChunkModel, shell )

	static std::map<std::string, std::set<EditorChunkModel*> > editorChunkModels_;
	static void add( EditorChunkModel*, const std::string& resourceName );
	static void remove( EditorChunkModel* );
	
	//change 20110816 用GUID关联场景模型
	//由于浏览器中不对场景现有模型进行删除添加操作，
	//所以这里选择vector进行存储
	static std::map< std::string, EditorChunkModel* > editorGUIDModels_;
	static void addGUIDModel( EditorChunkModel*, const std::string& guid );
	static void removeGUIDModel( EditorChunkModel* );

public:
	static void reload( const std::string& filename );
	void clean();

	EditorChunkModel();
	~EditorChunkModel();

	virtual bool edShouldDraw();
	virtual void draw();

	bool load( DataSectionPtr pSection, Chunk * pChunk );
	void loadModels( Chunk* chunk );
	/** Called once after loading from the main thread */
	void edPostLoad();

	virtual void toss( Chunk * pChunk );

	virtual bool edSave( DataSectionPtr pSection );
	virtual void edChunkSave();
	virtual void edChunkSaveCData(DataSectionPtr cData);

	virtual const Matrix & edTransform() { return transform_; }
	virtual bool edTransform( const Matrix & m, bool transient );
	virtual void edBounds( BoundingBox& bbRet ) const;

	virtual bool edAffectShadow() const;

	virtual bool edEdit( class ChunkItemEditor & editor );
	virtual Chunk * edDropChunk( const Vector3 & lpos );

	virtual std::string edDescription();

	virtual std::vector<std::string> edCommand( const std::string& path ) const;
	virtual bool edExecuteCommand( const std::string& path, std::vector<std::string>::size_type index );

	virtual DataSectionPtr pOwnSect()	{ return pOwnSect_; }
	virtual const DataSectionPtr pOwnSect()	const { return pOwnSect_; }

	virtual bool isShellModel();
	virtual const char* sectionName();

	/**
	 * Make sure we've got our own unique lighting data after being cloned
	 */
	void edPostClone( EditorChunkItem* srcItem );

	/** Ensure lighting on the chunk is marked as dirty */
	void edPostCreate();


	/** If we've got a .lighting file, delete it */
	void edPreDelete();

	/**
	 * Update the static lighting for the model
	 */
	bool edRecalculateLighting( StaticLighting::StaticLightContainer& lights );

	Vector3 edMovementDeltaSnaps();
	float edAngleSnaps();

	std::string getAnimation() const { return animName_; }
	bool setAnimation( const std::string & newAnimationName );

	std::string getDyeTints( const std::string& dye ) const;
	bool setDyeTints( const std::string& dye, const std::string& tint );

	float getAnimRateMultiplier() const { return animRateMultiplier_; }
	bool setAnimRateMultiplier( const float& f );

	bool getOutsideOnly() const { return outsideOnly_; }
	bool setOutsideOnly( const bool& outsideOnly );

	bool getCastsShadow() const { return castsShadow_; }
	bool setCastsShadow( const bool& castsShadow );

	struct MaterialProp
	{
		std::string matName_;
		ComObjectWrap<ID3DXEffect> effect_;
		D3DXHANDLE handle_;
		Moo::EffectPropertyPtr property_;
		std::string enumType_;
	};
	MaterialProp findMaterialByName( const std::string& name,
		D3DXPARAMETER_CLASS mcMin, D3DXPARAMETER_CLASS mcMax,
		D3DXPARAMETER_TYPE mtMin, D3DXPARAMETER_TYPE mtMax ) const;
	MaterialProp findOriginalMaterialByName( const std::string& name,
		D3DXPARAMETER_CLASS mcMin, D3DXPARAMETER_CLASS mcMax,
		D3DXPARAMETER_TYPE mtMin, D3DXPARAMETER_TYPE mtMax ) const;
	bool getMaterialBool( const std::string& name ) const;
	bool setMaterialBool( const std::string& name, const bool& value );
	std::string getMaterialString( const std::string& name ) const;
	bool setMaterialString( const std::string& name, const std::string& value );
	float getMaterialFloat( const std::string& name ) const;
	bool setMaterialFloat( const std::string& name, const float& value );
	bool getMaterialFloatRange( const std::string& name, float& min, float& max, int& digits );
	bool getMaterialFloatDefault( const std::string& name, float& def );
	void setMaterialFloatToDefault( const std::string& name );
	Vector4 getMaterialVector4( const std::string& name ) const;
	bool setMaterialVector4( const std::string& name, const Vector4& value );
	Matrix getMaterialMatrix( const std::string& name ) const;
	bool setMaterialMatrix( const std::string& name, const Matrix& value );
	uint32 getMaterialInt( const std::string& name ) const;
	bool setMaterialInt( const std::string& name, const uint32& value );
	bool getMaterialIntRange( const std::string& name, uint32& min, uint32& max, int& digits );

	Moo::EffectMaterialPtr findMaterialByName( const std::string& name ) const;
	std::string getMaterialCollision( const std::string& name ) const;
	bool setMaterialCollision( const std::string& name, const std::string& collisionType );
	std::string getMaterialKind( const std::string& name ) const;
	bool setMaterialKind( const std::string& name, const std::string& collisionType );
	std::string getMaterialEnum( const std::string& name ) const;
	bool setMaterialEnum( const std::string& name, const std::string& enumValue );
	DXEnum dxEnum_;

	virtual void edSetCastsShadow(const bool & b);		//change 2010-3-5 设置阴影
	virtual std::string edGUID();						//change 2010-3-4 返回已有GUID
	virtual void edSetGUID(const std::string & s);      //change 2010-3-4 设置GUID
	virtual std::string edCreateGUID();					//change 2010-3-6 设置第一次生成的GUID
	
	virtual void edSetShouldDraw(const bool & b) { shouldDraw_ = b; }       //change 2010-3-5 设置该模型是否显示
	virtual bool playAnimation( const std::string &newAnimationName );
	
	//change 获取已加载模型
	static std::map<std::string, std::set<EditorChunkModel*> > getModelMap() { return editorChunkModels_; }
	
	//change 获取模型动作列表
	const std::vector<std::string> getModelAnimations() const { return animationNames_; };

	//change 获取更改模型表面颜色状态
	void setDrawSpecialSurface( bool draw ) { drawSpecialSurface_ = draw; }

	//change 20110816 返回GUID关联模型
	static std::map< std::string, EditorChunkModel* > getGUIDModelsMap() { return editorGUIDModels_; }
	
protected:
	virtual void addStaticLighting( const std::string& resName, DataSectionPtr modelLightingSection = NULL );

private:
	EditorChunkModel( const EditorChunkModel& );
	EditorChunkModel& operator=( const EditorChunkModel& );

	bool			resourceIsOutsideOnly() const;

	bool								hasPostLoaded_;
	DataSectionPtr						pOwnSect_;
	std::string							animName_;
	std::map<std::string,std::string>	tintName_;
	std::set<std::string>				changedMaterials_;
	
	StringHashMap<int>	  				collisionFlags_;
	std::vector<std::string>			collisionFlagNames_;
	static StringHashMap<int>			s_materialKinds_;

	uint								primGroupCount_;
	bool								customBsp_;		// if the user specified their own bsp
	bool								outsideOnly_;
	bool								castsShadow_;

	class SuperModel*					pEditorModel_;

	/**
	 * Load the visual from the data section, for creating initial
	 * static lighting
	 */
	std::vector<Moo::VisualPtr> extractVisuals();

	/**
	 * As extractVisuals(), but returns the names of the visuals rather than
	 * a Ptr to them.
	 */
	std::vector<std::string> extractVisualNames() const;

	/**
	 * Calculate lighting infomation, and store it in values
	 *
	 * returns false if we were interupted while recalculating
	 */
	bool calculateLighting( StaticLighting::StaticLightContainer& lights,
							StaticLightValues& values,
							Moo::VisualPtr visual,
							bool calculateVisibility);

	/**
	 * Generate a new name to store lighting data in
	 */
	std::string generateLightingTagPrefix() const;

	/**
	 * Remove the static lighting fastion from the base model, and set it to NULL
	 */
	void clearLightingFashion();

	/** The fashion with the static lighting info */
	StaticLightFashionPtr pStaticLightFashion_;

	std::string lightingTagPrefix_;


	bool isModelNodeless()	{ return isModelNodeless_; }
	bool isModelNodeless_;
	void detectModelType();

	// check if the model file is a new date then the binary data file
	bool isVisualFileNewer() const;
	bool firstToss_;

	// for drawing the collision representation
	std::vector<Moo::VertexXYZL> verts_;

	// for edDescription
	std::string desc_;

	// is a model is not found, the standin is loaded
	bool standinModel_;
	DataSectionPtr originalSect_;

	// animations available to be played in this model
	std::vector<std::string> animationNames_;

	// dye and tint available to be played in this model
	// map dye name to tints names vector
	std::map<std::string, std::vector<std::string> > dyeTints_;

	void edit( Moo::EffectMaterialPtr material, ChunkItemEditor & editor );

	//change 2010-3-3 模型GUID
	UniqueID guid_;
	
	bool shouldDraw_;	  //change 2010-3-5 是否显示模型

	bool drawSpecialSurface_;  //change 2011-7-7 是否更改模型的表面颜色
	
	typedef std::map< std::string, EditorChunkModel* > GUIDModels;
};


#endif // EDITOR_CHUNK_MODEL_HPP
