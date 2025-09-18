{
  description = "AnsiLove/C development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        inherit (pkgs) lib;
        libansilove = pkgs.libansilove;
        gd = pkgs.gd;
        libs = map lib.getLib [ libansilove gd pkgs.libpng pkgs.zlib ];
        devs = map lib.getDev [ libansilove gd pkgs.libpng pkgs.zlib ];
      in {
        devShells.default = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            cmake
            ninja
            pkg-config
            clang
            clang-tools
          ];
          buildInputs = devs ++ libs;
          CMAKE_PREFIX_PATH = lib.makeSearchPath "" devs;
          CMAKE_LIBRARY_PATH = lib.makeSearchPath "lib" libs;
          PKG_CONFIG_PATH = lib.makeSearchPath "lib/pkgconfig" devs;
        };
      });
}
