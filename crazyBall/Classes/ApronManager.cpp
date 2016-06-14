#include "ApronManager.h"


void ApronManager::generateApron(int pointNum)
{
	int apronNum = pointNum + 1;
	
	float* lines = new float[apronNum];
	
	struct timeval now;
	gettimeofday(&now, NULL);
	//初始化随机种子
	//timeval是个结构体，里边有俩个变量，一个是以秒为单位的，一个是以微妙为单位的 
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);    //都转化为毫秒 
	srand(rand_seed);

	//开口位置
	int open = CCRANDOM_0_1() * (apronNum + 1);
	float sum = 0.0f;
	//随机生成水平长度
	for (int i = 0; i < apronNum; i++) 
	{
		lines[i] = ((CCRANDOM_0_1() - 0.5) * 2 * maxDifferenceWidth) + width / apronNum;
		sum += lines[i];
	}
	
	float prop = (width - ballWidth) / sum;
	log("sum = %.2f,prop = %.2f", sum, prop);
	for (int i = 0; i < apronNum; i++)
	{
		lines[i] = lines[i] * prop;
	}
	Point* points = new Point[apronNum + 2];
	int flag = 1;
	for (int i = 0; i < apronNum + 2; i++)
	{
		points[i].x = pointx;
		points[i].y = pointy;
	}
	//生成点
	for (int i = 0; i < apronNum + 2; i++)
	{
		if (i == 0)
		{
			points[i].x += pointx;
			points[i].y += (CCRANDOM_0_1() * 2 - 1) * maxDifferenceHeight + height + pointy;
			continue;
		}
		points[i].y += (CCRANDOM_0_1() * 2 - 1) * maxDifferenceHeight + height + pointy;
		if(points[i].x == pointx)
			points[i].x += points[i - 1].x + lines[i - flag];
		if (open == i)
		{
			points[i + 1].x = points[i].x + ballWidth;
		}
		if (open == i - 1)
		{
			flag = 2;
			continue;
		}
		auto apron = Apron::createApron(points[i], points[i - 1]);
		aprons.pushBack(apron);
	}
	log("apron generate finish,count = %d,open = %d",aprons.size(),open);
}
Vector<Apron*>& ApronManager::getAprons()
{
	return aprons;
}


ApronManager* ApronManager::create(float height /*= HEIGHT*/, float width /*= WIDTH*/, float ballWidth /*= 30.0f*/, float maxDifferenceWidth /*= 50.0f*/, float maxDifferenceHeight /*= 100.0f*/, float pointx /*= 0.0f*/, float pointy /*= 0.0f*/)
{
	auto am = new ApronManager();
	log("create width = %.2f ballWidth = %.2f maxdifference = %.2f %.2f", width, ballWidth, maxDifferenceHeight, maxDifferenceWidth);
	if (am && am->init(height, width, ballWidth, maxDifferenceWidth, maxDifferenceHeight, pointx, pointy))
	{
		am->autorelease();
		return am;
	}
	else
	{
		delete am;
		am = nullptr;
		return nullptr;
	}
}

ApronManager::ApronManager()
{

}

ApronManager::~ApronManager()
{

}

bool ApronManager::init(float height /*= HEIGHT*/, float width /*= WIDTH*/, float ballWidth /*= 30.0f*/, float maxDifferenceWidth /*= 50.0f*/, float maxDifferenceHeight /*= 100.0f*/, float pointx /*= 0.0f*/, float pointy /*= 0.0f*/)
{
	this->height = height;
	this->width = width;
	this->ballWidth = ballWidth;
	this->pointx = pointx;
	this->pointy = pointy;
	this->maxDifferenceWidth = maxDifferenceWidth;
	this->maxDifferenceHeight = maxDifferenceHeight;
	log("init width = %.2f ballWidth = %.2f maxdifference = %.2f %.2f", width,ballWidth, maxDifferenceHeight, maxDifferenceWidth);
	return true;
}
