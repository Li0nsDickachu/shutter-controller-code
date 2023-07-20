with import <nixpkgs> {};

stdenv.mkDerivation rec {
  name = "raylib";

  buildInputs = [
    raylib
  ];
}

