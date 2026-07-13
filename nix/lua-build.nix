{ lib
, stdenv
, callPackage
, fetchurl
, gnumake
, releaseMode
}:

stdenv.mkDerivation (finalAttrs:
let
  cmakeBuildProfiles = import ./cmake-profiles.nix;
in
{
  name = "${finalAttrs.pname}-${finalAttrs.version}-${stdenv.hostPlatform.system}";
  pname = "lua";
  version = "5.5.0";
  src = fetchurl {
    url = "https://www.lua.org/ftp/lua-${finalAttrs.version}.tar.gz";
    hash = "sha256-V8zDK7vQBcq3W8xSREBSU1r2kXiduiuQFtXFBkDWiz0=";
  };

  dontStrip = cmakeBuildProfiles.${releaseMode}.symbols;

  nativeBuildInputs = [
    gnumake
  ];
  makeFlags = [
    "INSTALL_TOP=$(out)"
  ];

  postInstall = ''
    mkdir -p "$out/lib/pkgconfig"

    cat >"$out/lib/pkgconfig/lua.pc" <<EOF
    prefix=$out
    libdir=$out/lib
    includedir=$out/include
    INSTALL_BIN=$out/bin
    INSTALL_INC=$out/include
    INSTALL_LIB=$out/lib

    Name: Lua
    Description: An Extensible Extension Language
    Version: ${finalAttrs.version}
    Requires:
    Libs: -L$out/lib -llua
    Cflags: -I$out/include
    EOF
  '';
})

