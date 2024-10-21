TINAPE
======

This is not a Physics engine but a numerically stable Collision Engine.

Tinape utilizes CNL (Compositional Numeric Library) to create a numerically stable (if wanted continuous) collision
engine for circles (and lines - coming soon).

Numerical stability is guaranteed due to exact elastic fixed point operations.
This has advantages as it avoids handling unstable states as two object that already penetrate each other.
