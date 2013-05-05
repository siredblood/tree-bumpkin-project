
#ifndef _COMMON_H_
#define _COMMON_H_
#include "worldeditor/world/world_manager.hpp"

//字符转为颜色，格式"233;212;32"
Moo::Colour ConverStrToColorRGB(char *szColor);
Moo::Colour ConverStrToColorARGB(char *szColor);

//颜色转为字符串
CString ConverColorRGBToStr( Moo::Colour ulColor );
CString ConverColorARGBToStr( Moo::Colour ulColor );

//字符转为3维坐标，格式"12.33,45.34,454.5657"
Vector3 ConvertStrToVec3(char *szPos);
CString ConvertVec3ToStr(Vector3 pos);

//把三维坐标转换为屏幕坐标
Vector2 ConvertVec3ToScreenPt(Vector3 pos);

//取消选中对象
void CancelSeleteItem(ChunkItemPtr item);

//判断坐标是否在可视范围内
bool IsPositionInView(Vector3 pos);

//判断点是否可见
bool IsPositionCanSee(Vector3 pos);	

//判断点是否在直线上
bool IsPointInLine(Vector3 LinePt1, Vector3 LinePt2, Vector3 newPt);

//判断字符串是否在列表中
bool IsStringInVector( std::string sText, std::vector<CString> &vTextVector );	

//计算多边形的外框的最大和最小范围坐标
void CalculatePolygonMinMaxBound(std::vector<Vector3> &vBound, Vector3 &MinPt, Vector3 &MaxPt);

//计算多边形的外框的中心点
Vector3 CalculatePolygonCentre(std::vector<Vector3> &vPolygon);

//计算多边形的外框的最大最小范围坐标和中心点
void CalculatePolygonMinMaxCentre(std::vector<Vector3> &vBound, Vector3 &MinPt, Vector3 &MaxPt, Vector3 &Centre);

//bezier曲线生成过程点
float bezier(std::vector<float> p, float t);	

//获取现在的时间
CString GetNowTime();	

//时间跟整数的转换
int timeToInt( const std::string & value );
std::string intToTime( int nValue );

//检测文件夹是否存在,不存在则创建
BOOL CheckFolder( CString strFolderPath );

//把对象移动相应的位置
void MoveItemToPos(ChunkItemPtr &item, Vector3 pos, Vector3 dir);

//查找对象
ChunkItemPtr findItem(CString strGuid);

#endif