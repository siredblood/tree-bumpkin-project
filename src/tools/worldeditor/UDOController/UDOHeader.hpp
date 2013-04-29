#ifndef UDOHeader_h__
#define UDOHeader_h__   

const float	  MIN_SPEED	    = 0.1f;

struct UDOCameraNode
{
	UDOCameraNode()
		: id( -1 ), pid( -1 ){}

	int			id;
	int			pid;
	Matrix		transform;
	std::string guid;
	std::string chunkID;
	std::string nextGUID;
	std::string nextChunkID;
	std::string backGUID;
	std::string backChunkID;
	float		speed;
	std::string description;
};
 
struct UDOCamera
{
	UDOCamera() 
		: id( -1 )
		, strName( "" )
		, fSpeed( 0.0f )
		, iNodeid( -1 ){}
	UDOCamera( const UDOCamera &rhs )
		: id( rhs.id )
		, strName( rhs.strName )
		, fSpeed( rhs.fSpeed )
		, iNodeid( rhs.iNodeid ){}
	UDOCamera &operator=( const UDOCamera &rhs )
	{
		id = rhs.id;
		strName = rhs.strName;
		fSpeed = rhs.fSpeed;
		iNodeid = rhs.iNodeid;

		return *this;
	}

	int					id;
	std::string			strName;
	float				fSpeed;
	int					iNodeid;
};

struct FlyData
{
	Vector3		pos;
	Vector3		rot;
	float		speed;
	std::string description;
};

// 临时数据结构，用来保存ID和速度
struct TempStruct
{
	int		    id;			 // 节点ID
	float	    fSpeed;		 // 速度
	std::string description; // 描述
};


#endif // UDOHeader_h__

