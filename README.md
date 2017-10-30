this project based on POSIX pthread lib,only applyed in linux platform.
## Two work pattern(or both):
1. grab a thread from the pool,then assign the grabed thread your work.
2. create some identitied work,throw the works to the pool,the pool will
  all have those works done.
