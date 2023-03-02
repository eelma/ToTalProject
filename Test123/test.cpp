for (auto obj : game2D.m_npcList)
{
    KBaseObject* pObject = obj.second;
    pObject->m_rt.x1;
    KVector2D vPos(pObject->m_rt.x1, pObject->m_rt.y1);
    KVector2D vSize(pObject->m_rt.w, pObject->m_rt.h);

    //벡터의 직선의 방정식 &  시간의 동기화
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
            //패킷헤더만큼 영역을 예약해줘

            BYTE* buffer = sendBuffer->Buffer();
            //여기에 헤더값을 넣어줘야함
            vPos.x;
            //id(uint64), 체력 (uint32), 공격력(uint16)
            bw << (uint16)pObject->_vid << (KVector2D)vPos << (uint32)vPos.v[0] << (uint32)vPos.v[1] << (KVector2D)pObject->m_vVelocity2D << (KVector2D)pObject->m_vDirection2D << (KVector2D)vSize;

            bw.Write(sendData, sizeof(sendData));

            header->size = bw.WriteSize();
            header->id = 1;
            //정보 기입

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
            //패킷헤더만큼 영역을 예약해줘

            BYTE* buffer = sendBuffer->Buffer();
            //여기에 헤더값을 넣어줘야함
            vPos.x;
            //id(uint64), 체력 (uint32), 공격력(uint16)
            bw << (uint16)pObject->_vid << (KVector2D)vPos << (uint32)vPos.v[0] << (uint32)vPos.v[1] << (KVector2D)pObject->m_vVelocity2D << (KVector2D)pObject->m_vDirection2D << (KVector2D)vSize;

            bw.Write(sendData, sizeof(sendData));

            header->size = bw.WriteSize();
            header->id = 1;
            //정보 기입

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
            //패킷헤더만큼 영역을 예약해줘

            BYTE* buffer = sendBuffer->Buffer();
            //여기에 헤더값을 넣어줘야함
            vPos.x;
            //id(uint64), 체력 (uint32), 공격력(uint16)
            bw << (uint16)pObject->_vid << (KVector2D)vPos << (uint32)vPos.v[0] << (uint32)vPos.v[1] << (KVector2D)pObject->m_vVelocity2D << (KVector2D)pObject->m_vDirection2D << (KVector2D)vSize;

            bw.Write(sendData, sizeof(sendData));

            header->size = bw.WriteSize();
            header->id = 1;
            //정보 기입

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
            //패킷헤더만큼 영역을 예약해줘

            BYTE* buffer = sendBuffer->Buffer();
            //여기에 헤더값을 넣어줘야함


            bw << (uint16)pObject->_vid << (KVector2D)vPos << (uint32)vPos.v[0] << (uint32)vPos.v[1] << (KVector2D)pObject->m_vVelocity2D << (KVector2D)pObject->m_vDirection2D << (KVector2D)vSize;

            bw.Write(sendData, sizeof(sendData));

            header->size = bw.WriteSize();
            header->id = 1;
            //정보 기입

            sendBuffer->Close(bw.WriteSize());

            GSessionManager.BroadCast(sendBuffer);
        }
    }

    pObject->SetPosition(vPos, vSize);


}