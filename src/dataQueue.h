#ifndef _DATA_QUEUE_H_
#define _DATA_QUEUE_H_

#include <vector>
#define CHUNK_SIZE (1024*16)
#define CHUNK_COUNT (20)
class DataQueue {

public:
	DataQueue();
	~DataQueue();

	void insertData(char* buf, int bufLen);
	void extractData(char* buf, int*bufLen);

private:
	void readBufLen(int* len);
	void writeBufLen(int len);
	void gotoLastBuf(int len);

private:
	unsigned int m_insertPos;
	unsigned int m_insertChunk;

	unsigned int m_extractPos;
	unsigned int m_extractChunk;

	std::vector<char*> m_bufs;
};

#endif //_DATA_QUEUE_H_
