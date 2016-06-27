#include "CCCircle.h"
#include "cocos2d.h"

USING_NS_CC;

CCCircle::CCCircle(void) :
	m_center(CCPoint(0, 0)), m_radius(0)
{
}

CCCircle::CCCircle(cocos2d::CCPoint& center, float radius) :
	m_center(center), m_radius(radius) {
}

CCCircle::~CCCircle(void)
{
}

//�ж�Բ�뷽�������Ƿ��ཻ
bool CCCircle::intersectsRect(cocos2d::CCRect& rect) const
{
	int arcR = (int)m_radius;//Բ�ΰ뾶
	int arcOx = (int)m_center.x;//Բ��X����
	int arcOy = (int)m_center.y;//Բ��Y����
	int rectX = (int)rect.getMinX();//���������Ͻ�X����
	int rectY = (int)rect.getMaxY();//���������Ͻ�Y����
	int rectW = rect.getMaxX() - rectX;//�����ο�
	int rectH = rect.getMaxY() - rectY;//�����θ�
	if (((rectX - arcOx) * (rectX - arcOx) + (rectY - arcOy) * (rectY - arcOy)) <= arcR * arcR)
		return true;
	if (((rectX + rectW - arcOx) * (rectX + rectW - arcOx) + (rectY - arcOy) * (rectY - arcOy)) <= arcR * arcR)
		return true;
	if (((rectX - arcOx) * (rectX - arcOx) + (rectY + rectH - arcOy) * (rectY + rectH - arcOy)) <= arcR * arcR)
		return true;
	if (((rectX + rectW - arcOx) * (rectX + rectW - arcOx) + (rectY + rectH - arcOy) * (rectY + rectH - arcOy)) <= arcR * arcR)
		return true;
	//�ֱ��жϾ���4��������Բ�ĵľ����Ƿ�<=Բ�뾶�����<=��˵����ײ�ɹ�
	int minDisX = 0;
	if (arcOy >= rectY && arcOy <= rectY + rectH) {
		if (arcOx < rectX)
			minDisX = rectX - arcOx;
		else if (arcOx > rectX + rectW)
			minDisX = arcOx - rectX - rectW;
		else
			return true;
		if (minDisX <= arcR)
			return true;

	}//�жϵ�Բ�ĵ�Y������������ʱX��λ�ã����X��(rectX-arcR)��(rectX+rectW+arcR)�����Χ�ڣ�����ײ�ɹ�

	int minDisY = 0;
	if (arcOx >= rectX && arcOx <= rectX + rectW) {
		if (arcOy < rectY)
			minDisY = rectY - arcOy;
		else if (arcOy > rectY + rectH)
			minDisY = arcOy - rectY - rectH;
		else
			return true;
		if (minDisY <= arcR)
			return true;

	}//�жϵ�Բ�ĵ�X������������ʱY��λ�ã����X��(rectY-arcR)��(rectY+rectH+arcR)�����Χ�ڣ�����ײ�ɹ�
	return false;
}
//�ж���Բ�Ƿ��ཻ
bool CCCircle::intersectsCircle(CCCircle& circle) const
{
	//Բ��֮��ľ���С����Բ�뾶֮�ͼ��ཻ
	if (sqrt(pow(m_center.x - circle.m_center.x, 2) + pow(m_center.y - circle.m_center.y, 2)) > m_radius + circle.m_radius) {
		return false;

	}
	return true;
}
