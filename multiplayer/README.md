## Multiplayer

This directory contains a client and server directory, these will host the multiplayer version
of pong.

- There will be a class to push and receive updates for the action
- This will update the other paddle and run on a seperate thread
- The instances will run on different ports as it will be running locally

- Info required in the payload
  -- ballPosX = 2B
  -- ballPosY = 2B
  -- paddlePosX = 2B
  -- paddlePosY = 2B

-- i.e
0000 0000 0000 0000 ballPosX
0000 0000 0000 0000 ballPosY
0000 0000 0000 0000 paddlePosX
0000 0000 0000 0000 paddlePosY
