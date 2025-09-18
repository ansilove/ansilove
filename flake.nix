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
        libansiloveDev = libansilove.dev or libansilove;
        gd = pkgs.gd;
        gdDev = gd.dev or gd;
        prefixInputs = [ libansiloveDev gdDev pkgs.zlib.dev pkgs.libpng.dev ];
        pkgConfigInputs = [ libansiloveDev gdDev pkgs.libpng.dev pkgs.zlib.dev ];
      in {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            cmake
            ninja
            pkg-config
            clang
            clang-tools
            libansilove
            gd
            zlib
            libpng
          ];

          shellHook = ''
            export CMAKE_PREFIX_PATH="${lib.makeSearchPath "" prefixInputs}${CMAKE_PREFIX_PATH:+:}$CMAKE_PREFIX_PATH"
            export PKG_CONFIG_PATH="${lib.makeSearchPath "lib/pkgconfig" pkgConfigInputs}${PKG_CONFIG_PATH:+:}$PKG_CONFIG_PATH"
          '';
        };
      });
}
