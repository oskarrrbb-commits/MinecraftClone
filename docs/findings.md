## 1. Top and bottom faces vanished with back-face culling

**Symptom:** With GL_CULL_FACE on, top and bottom faces disappeared; sides were fine.

**Cause:** Rows 2 and 3 of faceVertexOffsets were wound clockwise (seen from outside), so the GPU culled them as back faces.

**Fix:** Swapped the 2nd and 4th corners in those two rows. Changing the shared indices instead broke all six faces.

**Prevention:** Unit test: each face's cross product must match its neighborOffsets direction.