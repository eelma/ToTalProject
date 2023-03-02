for (auto obj : game2D.m_npcList)
{
    KBaseObject* pObject = obj.second;
    pObject->m_rt.x1;
    KVector2D vPos(pObject->m_rt.x1, pObject->m_rt.y1);
    KVector2D vSize(pObject->m_rt.w, pObject->m_rt.h);

    //������ ������ ������ &  �ð��� ����ȭ
    pObject->m_vVelocity2D = pObject->m_vDirection2D;
    vPos = vPos + pObject->m_vVelocity2D;
    //m_fFriction = (fDeltaTime * m_fSpeed * 0.1f);
    pObject->m_fSpeed = 100;

    if (100 >= pObject->m_fSpeed)
    {
        pObject->m_fSpeed = 100;
    }
    if (vPos.x >= 100.0f)
    {
        vPos.x = 100.0f;
        pObject->m_vDirection2D.x *= -1.0f;
        {
            char sendData[] = "";
            SendBufferRef sendBuffer = GSendBufferManager->Open(100);
            BufferWriter bw(sendBuffer->Buffer(), 100);

            PacketHeader* header = bw.Reserve<PacketHeader>();
            //��Ŷ�����ŭ ������ ��������

            BYTE* buffer = sendBuffer->Buffer();
            //���⿡ ������� �־������
            vPos.x;
            //id(uint64), ü�� (uint32), ���ݷ�(uint16)
            bw << (uint16)pObject->_vid << (KVector2D)vPos << (uint32)vPos.v[0] << (uint32)vPos.v[1] << (KVector2D)pObject->m_vVelocity2D << (KVector2D)pObject->m_vDirection2D << (KVector2D)vSize;

            bw.Write(sendData, sizeof(sendData));

            header->size = bw.WriteSize();
            header->id = 1;
            //���� ����

            sendBuffer->Close(bw.WriteSize());

            GSessionManager.BroadCast(sendBuffer);
        }
    }
    if (vPos.x <= 0.0f)
    {
        vPos.x = 0.0f;
        pObject->m_vDirection2D.x *= -1.0f;
        {
            char sendData[] = "";
            SendBufferRef sendBuffer = GSendBufferManager->Open(100);
            BufferWriter bw(sendBuffer->Buffer(), 100);

            PacketHeader* header = bw.Reserve<PacketHeader>();
            //��Ŷ�����ŭ ������ ��������

            BYTE* buffer = sendBuffer->Buffer();
            //���⿡ ������� �־������
            vPos.x;
            //id(uint64), ü�� (uint32), ���ݷ�(uint16)
            bw << (uint16)pObject->_vid << (KVector2D)vPos << (uint32)vPos.v[0] << (uint32)vPos.v[1] << (KVector2D)pObject->m_vVelocity2D << (KVector2D)pObject->m_vDirection2D << (KVector2D)vSize;

            bw.Write(sendData, sizeof(sendData));

            header->size = bw.WriteSize();
            header->id = 1;
            //���� ����

            sendBuffer->Close(bw.WriteSize());

            GSessionManager.BroadCast(sendBuffer);
        }
    }
    if (vPos.y >= 100.0f)
    {
        vPos.y = 100.0f;
        pObject->m_vDirection2D.y *= -1.0f;
        {
            char sendData[] = "";
            SendBufferRef sendBuffer = GSendBufferManager->Open(100);
            BufferWriter bw(sendBuffer->Buffer(), 100);

            PacketHeader* header = bw.Reserve<PacketHeader>();
            //��Ŷ�����ŭ ������ ��������

            BYTE* buffer = sendBuffer->Buffer();
            //���⿡ ������� �־������
            vPos.x;
            //id(uint64), ü�� (uint32), ���ݷ�(uint16)
            bw << (uint16)pObject->_vid << (KVector2D)vPos << (uint32)vPos.v[0] << (uint32)vPos.v[1] << (KVector2D)pObject->m_vVelocity2D << (KVector2D)pObject->m_vDirection2D << (KVector2D)vSize;

            bw.Write(sendData, sizeof(sendData));

            header->size = bw.WriteSize();
            header->id = 1;
            //���� ����

            sendBuffer->Close(bw.WriteSize());

            GSessionManager.BroadCast(sendBuffer);
        }
    }
    if (vPos.y <= 0.0f)
    {
        vPos.y = 0.0f;
        pObject->m_vDirection2D.y *= -1.0f;
        {
            char sendData[] = "";
            SendBufferRef sendBuffer = GSendBufferManager->Open(100);
            BufferWriter bw(sendBuffer->Buffer(), 100);

            PacketHeader* header = bw.Reserve<PacketHeader>();
            //��Ŷ�����ŭ ������ ��������

            BYTE* buffer = sendBuffer->Buffer();
            //���⿡ ������� �־������


            bw << (uint16)pObject->_vid << (KVector2D)vPos << (uint32)vPos.v[0] << (uint32)vPos.v[1] << (KVector2D)pObject->m_vVelocity2D << (KVector2D)pObject->m_vDirection2D << (KVector2D)vSize;

            bw.Write(sendData, sizeof(sendData));

            header->size = bw.WriteSize();
            header->id = 1;
            //���� ����

            sendBuffer->Close(bw.WriteSize());

            GSessionManager.BroadCast(sendBuffer);
        }
    }

    pObject->SetPosition(vPos, vSize);


}