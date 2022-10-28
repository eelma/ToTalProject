#pragma once
#include "KBaseObject.h"

class KShape : public KBaseObject
{

public:
	KShape() {};
	virtual ~KShape() {};

};
class KShapeBox :public KShape
{

public:
	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
	virtual bool Frame() override;
	virtual bool Render() override;
public:
	KShapeBox() {};
	virtual ~KShapeBox() {};
};
class KShapeLine : public KShape
{
public:
	virtual void CreateVertexData()override;
	virtual void CreateIndexData() override;
	virtual bool Frame() override;
	virtual bool Render() override;
public:
	KShapeLine() {};
	virtual ~KShapeLine() {};
};

class KShapeDirectionLine :public KShapeLine
{

public:
	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;

public:
	KShapeDirectionLine() {};
	virtual ~KShapeDirectionLine() {};


};