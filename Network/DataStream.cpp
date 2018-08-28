/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: DataStream.cpp
-- Project: Network
-- Author(s): OrMisicL

=============================================================*/

#include "Main.h"

using namespace RakNet;

CDataStream::CDataStream()
{
	// Create the bitstream
	m_bitStream.Create();
}

CDataStream::CDataStream(RakNet::BitStream bsStream)
{
	// Create the bitsream
	m_bitStream.SetData(bsStream.GetData());
	m_bitStream.SetNumberOfBitsAllocated(bsStream.GetNumberOfBitsAllocated());
	m_bitStream.SetReadOffset(bsStream.GetReadOffset());
}

CDataStream::CDataStream(unsigned char *pucData, unsigned int uiLength)
{
	// Create the bitsream
	m_bitStream.SetData(pucData);
	m_bitStream.SetNumberOfBitsAllocated(BYTES_TO_BITS(uiLength));
	m_bitStream.ResetReadPointer();
}

CDataStream::~CDataStream()
{

}

bool CDataStream::Read(void *pData, unsigned int uiLength)
{
	// Read from the bitStream
	return m_bitStream.Read((char *)pData, (const unsigned int)uiLength);
}

bool CDataStream::ReadString(char *szData)
{
	// Read from the bitStream
	return m_bitStream.Read(szData);
}

void CDataStream::Write(void *pData, unsigned int uiLength)
{
	// Write to the bitStream
	m_bitStream.Write((char *)pData, (const unsigned int)uiLength);
}

void CDataStream::WriteString(char *szData)
{
	// Write to the bitStream
	m_bitStream.Write(szData);
}

void CDataStream::IgnoreBytes(unsigned int uiBytes)
{
	// Ignore specific set of bytes
	m_bitStream.IgnoreBytes(uiBytes);
}

void CDataStream::SetReadPointer(unsigned int uiPointer)
{
	m_bitStream.SetReadOffset(BYTES_TO_BITS(uiPointer));
}

unsigned int CDataStream::GetReadPointer()
{
	return m_bitStream.GetReadOffset();
}

void CDataStream::SetWritePointer(unsigned int uiPointer)
{
	m_bitStream.SetWriteOffset(BYTES_TO_BITS(uiPointer));
}

unsigned int CDataStream::GetWritePointer()
{
	return m_bitStream.GetWriteOffset();
}




