#!/usr/bin/env bash
# Compile le projet (macOS / Linux) dans le dossier build/ et, en option, lance une simulation.
#   ./build.sh          -> compile tout
#   ./build.sh 3d       -> compile puis lance la simulation 3D (Qt/OpenGL)
#   ./build.sh text     -> compile puis lance la simulation textuelle
# qmake est cherché dans : $QMAKE, le PATH, puis ~/Qt/5.15.2/{clang_64,gcc_64}/bin.
set -e
ROOT="$(cd "$(dirname "$0")" && pwd)"
SRC="$ROOT/Projet_Final"
BUILD="$ROOT/build"

if [ -z "$QMAKE" ]; then
  for q in qmake qmake-qt5 "$HOME/Qt/5.15.2/clang_64/bin/qmake" "$HOME/Qt/5.15.2/gcc_64/bin/qmake"; do
    if command -v "$q" >/dev/null 2>&1; then QMAKE="$q"; break; fi
  done
fi
[ -n "$QMAKE" ] || { echo "qmake (Qt 5) introuvable : voir README.md, section Installation." >&2; exit 1; }
echo "qmake utilisé : $QMAKE"

mkdir -p "$BUILD"
cd "$BUILD"
"$QMAKE" CONFIG+=sdk_no_version_check "$SRC/Projet_Final.pro"
make   # séquentiel : general/ doit être compilé avant text/ et Qt_GL/

# Les exécutables lisent des chemins relatifs (../height_data, gnuplot/) :
# on les lance donc depuis leur dossier source.
if [ "$(uname)" = "Darwin" ]; then
  BIN3D="$BUILD/Qt_GL/Simulations.app/Contents/MacOS/Simulations"
  BINTXT="$BUILD/text/Simulations_text.app/Contents/MacOS/Simulations_text"
else
  BIN3D="$BUILD/Qt_GL/Simulations"
  BINTXT="$BUILD/text/Simulations_text"
fi
case "$1" in
  3d)   cd "$SRC/Qt_GL" && exec "$BIN3D" ;;
  text) cd "$SRC/text"  && exec "$BINTXT" ;;
esac
