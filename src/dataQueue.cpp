#include "dataQueue.h"

#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Max(a, b) ((a) > (b) ? (a) : (b))

DataQueue::DataQueue()
{	
	for (int i = 0; i < CHUNK_COUNT; ++i)
	{
		char* buf = (char*)malloc(CHUNK_SIZE * sizeof(char));
		m_bufs.push_back(buf);
	}

	m_insertPos = 0;
	m_insertChunk = 0;
	m_extractPos = 0;
	m_extractChunk = 0;
}

DataQueue::~DataQueue()
{
	int chunkCount = m_bufs.size();
	for (int i = 0; i < chunkCount; ++i)
	{
		free(m_bufs.back());
		m_bufs.pop_back();
	}
}

void DataQueue::insertData(char* buf, int bufLen)
{
	while ((m_bufs.size() - m_insertChunk)*CHUNK_SIZE - m_insertPos <= bufLen)
	{
		m_bufs.push_back((char*)malloc(CHUNK_SIZE * sizeof(char)));
	}

	writeBufLen(bufLen);

	int curChunkavai = CHUNK_SIZE - m_insertChunk;
	int curBufleft = bufLen;
	while (curBufleft > 0)
	{
		if (curBufleft >= curChunkavai)
		{
			memcpy(m_bufs[m_insertChunk] + m_insertPos, buf + bufLen - curChunkavai, curBufleft);
			curBufleft = curBufleft - curChunkavai;
			curChunkavai = CHUNK_SIZE;
			m_insertPos = 0;
			m_insertChunk++;
		} else {
			memcpy(m_bufs[m_insertChunk] + m_insertPos, buf + bufLen - curChunkavai, curChunkavai);
			m_insertPos += curBufleft;
			break;
		}
	}
	writeBufLen(bufLen);
}

void DataQueue::extractData(char* buf, int*bufLen)
{
	readBufLen(bufLen);
	gotoLastBuf(*bufLen);
	int curChunkavai = CHUNK_SIZE - m_insertChunk;
	int bufcopyed = 0;

	while (bufcopyed < *buf)
	{
		memcpy(buf + bufcopyed, )
	}
	int queryLen = 0;
	readBufLen(&queryLen);
}



void DataQueue::readBufLen(int* len)
{
	*len = 0;
	if (m_insertPos > 4)
	{
		char* curChunk = m_bufs[m_insertChunk];
		*len += curChunk[m_insertPos - 3];
		*len += (curChunk[m_insertPos - 2]) << 8;
		*len += (curChunk[m_insertPos - 1]) << 16;
		*len += (curChunk[m_insertPos]) << 24;
		m_insertPos += 4;
	} else {

		char* curChunk = m_bufs[m_insertChunk];
		int readedBytes = 0;
		while (m_insertPos >= 0)
		{
			*len += (curChunk[m_insertPos]) << (8 * (4 - readedBytes));
			m_insertPos--;
			readedBytes++;
		}

		m_insertPos = CHUNK_SIZE;
		m_insertChunk--;
		curChunk = m_bufs[m_insertChunk];

		while (4 - readedBytes > 0)
		{
			*len += (curChunk[m_insertPos]) << (8 * (4 - readedBytes));
			m_insertPos--;
			readedBytes++;
		}
	}
	
}

void DataQueue::writeBufLen(int len)
{
	if (CHUNK_SIZE - m_insertPos > 4)
	{
		char* curChunk = m_bufs[m_insertChunk];
		curChunk[m_insertPos] = (unsigned char)len;
		curChunk[m_insertPos + 1] = (unsigned char)(len >> 8);
		curChunk[m_insertPos + 2] = (unsigned char)(len >> 16);
		curChunk[m_insertPos + 3] = (unsigned char)(len >> 24);
		m_insertPos += 4;
	} else {
		char* curChunk = m_bufs[m_insertChunk];
		
		int writedBytes = 0;
		int highByte = len;
		while (CHUNK_SIZE - m_insertPos > 0)
		{
			curChunk[m_insertPos] = (unsigned char)highByte;
			highByte = highByte >> 8;
			writedBytes++;
			m_insertPos++;
		}
		m_insertPos = 0;
		m_insertChunk++;
		curChunk = m_bufs[m_insertChunk];
		while (4 - writedBytes > 0)
		{
			curChunk[m_insertPos] = (unsigned char)highByte;
			highByte = highByte >> 8;
			writedBytes++;
			m_insertPos++;
		}
	}

}

void DataQueue::gotoLastBuf(int len)
{
	m_extractPos = 0;
	m_extractChunk = m_insertChunk;
	if (len < m_insertPos)
	{
		m_extractPos = m_insertPos - len;
		m_extractChunk = m_insertChunk;
	} else {
		m_extractChunk = m_insertChunk - (len - m_insertPos) / CHUNK_SIZE 
			- ((len - m_insertPos) % CHUNK_SIZE == 0 ? 0 : 1);
		m_extractPos = CHUNK_SIZE - (len - m_insertPos) % CHUNK_SIZE;
	}
}
