#pragma once
// �⺻ : Ŭ���̾�Ʈ ���� ���� ü���.
// ���ϴ� ������ ���ϴ� ũ��� ������.
#include"KBaseObject.h"
class KObjectPlane :
    public KBaseObject
{

public:
	void    CreateVertexData() override;
	void    UpdateVertexBuffer() override;
};

