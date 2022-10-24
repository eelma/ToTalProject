#pragma once
#include "KBaseObject.h"
class KObject3D : public KBaseObject
{
public:
	KObject3D() {};
	virtual ~KObject3D() {};
};

class KShape : public KObject3D
{

public:
	KShape() {};
	virtual ~KShape() {};

};
class KShapeBox :public KObject3D
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