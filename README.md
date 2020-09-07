# uvxamples

This project is just for show some examples of [libuv](http://libuv.org/) API.
_Read [basics of libuv](http://docs.libuv.org/en/v1.x/guide/basics.html#basics-of-libuv) first_.

## Building:

We use CMake as building tool, so we can run multiplatform!

Run `./run.sh`, yes, that's it!

## Running examples:

There are two ways to do this, using python virtual env, or regular python env.

### Running with python virtual enviroment:

Run

```bash
# Activate the virtual envrionment.
source uvxamples-venv/bin/activate`

# With npm run.
npm start

# With python3 run.
python3 lib/example_runner.py
```

### Running without python virtual enviroment:

```bash
# Install the python dependencies.
pip install -r requirements.txt

# With npm run.
npm start

# With python3 run.
python3 lib/example_runner.py
```

## Example instructions (distributed in folders):

* check: [check examples](/src/check)
* fs: [file system operations examples](/src/fs)
* idle: [idle examples](/src/idle)
* signals: [signal examples](/src/signals)
* timer: [timer examples](/src/timer)

## Dependencies:

1. Cmake (at least 3.0).
2. Make.
3. Node.js.
4. Python3 with pip.

## PS: the content presented here are just for educational purposes.
