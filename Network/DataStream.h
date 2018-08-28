/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: DataStream.h
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#ifndef DATASTREAM_H
#define DATASTREAM_H

class CDataStream
{
public:
	CDataStream(RakNet::BitStream bsStream);
	CDataStream(unsigned char *pucData, unsigned int uiLength);
	CDataStream();
	~CDataStream();

	virtual bool Read(void *pData, unsigned int uiLength);
	virtual bool ReadString(char *szData);
	virtual void Write(void *pData, unsigned int uiLength);
	virtual void WriteString(char *szData);
	virtual void IgnoreBytes(unsigned int uiBytes);
	virtual void SetReadPointer(unsigned int uiPointer);
	virtual unsigned int GetReadPointer();
	virtual void SetWritePointer(unsigned int uiPointer);
	virtual unsigned int GetWritePointer();

	template <typename T>
	void Write(T data)
	{
		Write(&data, sizeof(T));
	};

	template <typename T>
	bool Read(T data)
	{
		return Read(&data, sizeof(T));
	};

	RakNet::BitStream *GetBitStream() { return &m_bitStream; };

private:
	RakNet::BitStream	m_bitStream;
};

#endif