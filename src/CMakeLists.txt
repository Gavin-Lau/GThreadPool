INCLUDE_DIRECTORIES (
	../include
  .
)

SET(SRC_LIST 
  pthread_core.cpp
  pthread_lock.cpp
  pthreadpool.cpp
)

ADD_LIBRARY(GThreadPool ${SRC_LIST} )  

TARGET_LINK_LIBRARIES( MyMidWare
	pthread
)

INSTALL(TARGETS MyMidWare
	RUNTIME DESTINATION bin
)

