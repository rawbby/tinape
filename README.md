TINAPE
======

This is not a Physics engine but a numerically stable Collision Engine.

Tinape utilizes CNL (Compositional Numeric Library) to create a numerically stable (if wanted continuous) collision
engine for circles (and lines - coming soon).

Numerical stability is guaranteed due to exact elastic fixed point operations.
This has advantages as it avoids handling unstable states as two object that already penetrate each other.

Build
-----

```shell
python bootstrap.py
mkdir cmake-build-release
cmake -S . -B ./cmake-build-release -DCMAKE_BUILD_TYPE=Release
cmake --build ./cmake-build-release --config Release
cmake-build-release/bin/sandbox
```
