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

// ��ʱ���ݽṹ����������ID���ٶ�
struct TempStruct
{
	int		    id;			 // �ڵ�ID
	float	    fSpeed;		 // �ٶ�
	std::string description; // ����
};


#endif // UDOHeader_h__

