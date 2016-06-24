## Synopsis

This is a game bot for HearthStone.

Your account shall be locked if you use this game bot to play it automatically.

Your account shall *not* be locked if you just refer to the move suggested by this game bot, move your mouse on your own, drag the mouse on your own, and click the mouse on your own.

But, to be on the safe side, I will take no responsbility if your account got locked.

## Motivation

1. AlphaGo is so strong. AlphaGo rocks!!!
2. AlphaGo uses Monte Carlo tree search.
3. I don't know Monte Carlo tree search.
4. I want to learn Monte Carlo tree search.
5. I want to try it out for a game. A card game is chosen: HearthStone.
6. This project is what I got.

## Components

### AI Engine
* Monte Carlo tree search
* Shared tree nodes to reduce memory prints

### Simulation Engine
* There's no HearthStone simulation engine written in C++, so I need to write one.
* Written in C++11
* One of the design goals is **speed**.

### Recognize Game Board
* Use the logging feature in HearthStone
* Written in C# since no critical performance issue occurs here.
* Parse the logs to get a picture of the game board.
* Use the C# **yield** to parse the logs in a cleaner way.

### Play back on game client
* The automatic play-back feature is not implemented yet
** So, hey, you will not get your account locked!
* Just refer to the move the AI suggested, and do it manually on the game client.

## Installation

1. Install HearthStone on Windows.
2. Enable logging to HearthStone, so we can know what's the board looks like.
3. Open the C# project under 'ui' folder.
4. Run it.

## Contributors

Just me.

## License

The newest GPL license is applied to this project.