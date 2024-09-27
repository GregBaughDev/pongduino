# Multiplayer

This directory contains the classes for multiplayer communication.

- `GameServer` - This class is the source of truth for the current game state. It contains the game logic and receives updates on the paddle position from both game instances. The gameserver class publishes the current game state (ball location, lPaddle and rPaddle positions) to both game instances.
- `Client` - This class is instantiated by both game instances and simply publishes the current state of the main paddle to the server. By return, it receives the current game state to update the gui for the player.

## Payload

There are two structs used for game state, `PaddleComm` is used by the paddles to provide the server with their main paddle location. It also contains the number of the paddle providing it's data. `PongComm` is the whole game state, both paddles and the ball. It could be extended to include additional data if required.
