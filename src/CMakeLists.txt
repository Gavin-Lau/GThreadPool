INCLUDE_DIRECTORIES (
	../include
  .
)

SET(SRC_LIST 
  pthread_core.cpp
  pthread_lock.cpp
  pthreadpool.cpp
)

ADD_LIBRARY(GThreadPool SHARED ${SRC_LIST} )  

TARGET_LINK_LIBRARIES(GThreadPool 
	pthread
)

INSTALL(TARGETS GThreadPool 
	LIBRARY DESTINATION bin
)

