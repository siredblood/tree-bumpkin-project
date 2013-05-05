
#ifndef _COMMON_H_
#define _COMMON_H_
#include "worldeditor/world/world_manager.hpp"

//�ַ�תΪ��ɫ����ʽ"233;212;32"
Moo::Colour ConverStrToColorRGB(char *szColor);
Moo::Colour ConverStrToColorARGB(char *szColor);

//��ɫתΪ�ַ���
CString ConverColorRGBToStr( Moo::Colour ulColor );
CString ConverColorARGBToStr( Moo::Colour ulColor );

//�ַ�תΪ3ά���꣬��ʽ"12.33,45.34,454.5657"
Vector3 ConvertStrToVec3(char *szPos);
CString ConvertVec3ToStr(Vector3 pos);

//����ά����ת��Ϊ��Ļ����
Vector2 ConvertVec3ToScreenPt(Vector3 pos);

//ȡ��ѡ�ж���
void CancelSeleteItem(ChunkItemPtr item);

//�ж������Ƿ��ڿ��ӷ�Χ��
bool IsPositionInView(Vector3 pos);

//�жϵ��Ƿ�ɼ�
bool IsPositionCanSee(Vector3 pos);	

//�жϵ��Ƿ���ֱ����
bool IsPointInLine(Vector3 LinePt1, Vector3 LinePt2, Vector3 newPt);

//�ж��ַ����Ƿ����б���
bool IsStringInVector( std::string sText, std::vector<CString> &vTextVector );	

//�������ε�����������С��Χ����
void CalculatePolygonMinMaxBound(std::vector<Vector3> &vBound, Vector3 &MinPt, Vector3 &MaxPt);

//�������ε��������ĵ�
Vector3 CalculatePolygonCentre(std::vector<Vector3> &vPolygon);

//�������ε����������С��Χ��������ĵ�
void CalculatePolygonMinMaxCentre(std::vector<Vector3> &vBound, Vector3 &MinPt, Vector3 &MaxPt, Vector3 &Centre);

//bezier�������ɹ��̵�
float bezier(std::vector<float> p, float t);	

//��ȡ���ڵ�ʱ��
CString GetNowTime();	

//ʱ���������ת��
int timeToInt( const std::string & value );
std::string intToTime( int nValue );

//����ļ����Ƿ����,�������򴴽�
BOOL CheckFolder( CString strFolderPath );

//�Ѷ����ƶ���Ӧ��λ��
void MoveItemToPos(ChunkItemPtr &item, Vector3 pos, Vector3 dir);

//���Ҷ���
ChunkItemPtr findItem(CString strGuid);

#endif