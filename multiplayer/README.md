## Multiplayer
This directory contains a client and server directory, these will host the multiplayer version
of pong.

- There will be a class to push and receive updates for the action
- This will update the other paddle and run on a seperate thread
- The instances will run on different ports as it will be running locally

- Info required in the payload
-- Player 1 / 2 - 0/1 = 0 player 1, 1 player 2
-- ballPosX = 2B
-- ballPosY = 2B
-- paddlePosX = 2B
-- paddlePosY = 2B
