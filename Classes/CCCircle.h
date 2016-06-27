#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CCCircle
{
public:
	CCCircle(void);
	CCCircle(cocos2d::CCPoint& center, float radius); //�ṩԲ����뾶 ��ʼ��Բ
	~CCCircle(void);

	bool intersectsRect(cocos2d::CCRect& rect) const;//�Ƿ��볤���������ཻ
	bool intersectsCircle(CCCircle& circle) const;//�Ƿ���Բ�������ཻ

private:
	CC_SYNTHESIZE(cocos2d::CCPoint, m_center, MCenter);//Բ��
	CC_SYNTHESIZE(float, m_radius, MRadius);//�뾶
};

#define CCCircMake(ccPoint, radius) CCCircle::CCCircle(ccPoint, (float)(radius))