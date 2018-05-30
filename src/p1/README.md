# snake

![Preview](preview.png)

Four snakes in separate threads crawling in random directions.

Game aims to use Ncurses library within many threads. Originally, the library not thread-safe.


## Build

```bash
make
./Snake
```

_Note:_ Doesn't work for provided Docker image. MacOS can handle it though.


## Remove garbage executable

```bash
make clean
```
