{
  lib
, stdenv
, fetchzip
, releaseMode
}:

stdenv.mkDerivation (finalAttrs: 
let
  cmakeBuildProfiles = import ./cmake-profiles.nix;
in 
{
  name = "${finalAttrs.pname}-${finalAttrs.version}-${stdenv.hostPlatform.system}";
  pname = "glad";
  version = "3.3";
  src = fetchzip {
    url = "https://glad.dav1d.de/generated/tmpp2m75o02glad/glad.zip";
    hash = "sha256-6yRlTrfcieoHrnrny9yJT29P24SOnNGT7pE4IfC9IUY=";
    stripRoot = false;
  };

  dontStrip = cmakeBuildProfiles.${releaseMode}.symbols;

  nativeBuildInputs = [ ];
  buildInputs = [ ];

  buildPhase = ''
    runHook preBuild
    $CC -c src/glad.c -Iinclude -o glad.o
    $AR rcs libglad.a glad.o
    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall
    mkdir -p $out/include $out/lib $out/lib/pkgconfig
    cp -r include/* $out/include/
    cp libglad.a $out/lib/
    runHook postInstall


    cat >"$out/lib/pkgconfig/glad.pc" <<EOF
    prefix=$out
    libdir=$out/lib
    includedir=$out/include
    INSTALL_BIN=$out/bin
    INSTALL_INC=$out/include
    INSTALL_LIB=$out/lib

    Name: Glad
    Description: OpenGL Wrapper
    Version: ${finalAttrs.version}
    Requires:
    Libs: -L$out/lib -lglad
    Cflags: -I$out/include
    EOF
  '';
})
