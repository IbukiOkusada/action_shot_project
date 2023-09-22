xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 52;
 2.92784;-1.92306;-1.82340;,
 2.92784;-2.91966;-1.82340;,
 2.92784;-3.31601;-5.10500;,
 2.92784;-2.22979;-3.51888;,
 -2.04396;-1.65299;-3.51888;,
 -2.04396;-1.30642;-1.82340;,
 2.37655;-1.30642;-1.82340;,
 2.37654;-1.65299;-3.51888;,
 -2.63303;-3.20069;-5.10500;,
 -2.63303;-2.80433;-1.82340;,
 -2.63303;-1.87282;-1.82340;,
 -2.63303;-2.11447;-3.51888;,
 2.37655;-4.31276;-6.13723;,
 2.37654;-4.31276;-1.82340;,
 -2.04396;-4.31276;-1.82340;,
 -2.04396;-4.31276;-6.13723;,
 2.37654;-2.49836;-5.10500;,
 -2.04396;-2.49836;-5.10500;,
 -2.04396;-1.30642;2.64208;,
 -2.04396;-2.61028;2.98194;,
 2.37655;-2.61028;2.98194;,
 2.37654;-1.30642;2.64208;,
 -2.04396;-4.31276;2.98194;,
 2.37655;-4.31276;2.98194;,
 -2.63303;-1.87282;2.64208;,
 -2.63303;-2.80433;2.64208;,
 2.92784;-2.91966;2.64208;,
 2.92784;-1.92306;2.64208;,
 2.92784;-4.31276;2.64208;,
 2.92784;-4.31276;-1.82340;,
 2.92784;-4.31276;-5.87125;,
 -2.63303;-4.31276;-1.82340;,
 -2.63303;-4.31276;-5.87125;,
 -2.63303;-4.31276;2.64208;,
 -1.60472;-1.97591;-1.44516;,
 -2.26685;-1.97591;0.15337;,
 -2.26685;0.09876;0.15337;,
 -1.60472;0.09876;-1.44516;,
 -1.60472;-1.97591;1.75189;,
 -1.60472;0.09876;1.75189;,
 -0.00619;-1.97591;2.41403;,
 -0.00619;0.09876;2.41403;,
 1.59233;-1.97591;1.75189;,
 1.59233;0.09876;1.75189;,
 2.25446;-1.97591;0.15337;,
 2.25446;0.09876;0.15337;,
 1.59233;-1.97591;-1.44516;,
 1.59233;0.09876;-1.44516;,
 -0.00619;-1.97591;-2.10728;,
 -0.00619;0.09876;-2.10728;,
 -0.00619;-1.97591;0.15337;,
 -0.00619;0.09876;0.15337;;
 
 56;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;7,16,17,4;,
 4;18,19,20,21;,
 4;22,14,13,23;,
 4;24,10,9,25;,
 4;21,6,5,18;,
 4;26,1,0,27;,
 4;28,29,1,26;,
 4;2,1,29,30;,
 4;16,12,15,17;,
 4;31,9,8,32;,
 4;25,9,31,33;,
 4;19,22,23,20;,
 4;27,0,6,21;,
 4;7,6,0,3;,
 4;2,16,7,3;,
 4;30,12,16,2;,
 4;29,13,12,30;,
 4;23,13,29,28;,
 4;20,23,28,26;,
 4;21,20,26,27;,
 4;33,31,14,22;,
 4;15,14,31,32;,
 4;17,15,32,8;,
 4;4,17,8,11;,
 4;10,5,4,11;,
 4;18,5,10,24;,
 4;25,19,18,24;,
 4;33,22,19,25;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,34,37,49;,
 3;35,34,50;,
 3;38,35,50;,
 3;40,38,50;,
 3;42,40,50;,
 3;44,42,50;,
 3;46,44,50;,
 3;48,46,50;,
 3;34,48,50;,
 3;37,36,51;,
 3;36,39,51;,
 3;39,41,51;,
 3;41,43,51;,
 3;43,45,51;,
 3;45,47,51;,
 3;47,49,51;,
 3;49,37,51;;
 
 MeshMaterialList {
  1;
  56;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\kids_girl_UV.png";
   }
  }
 }
 MeshNormals {
  44;
  0.873149;0.000000;0.487454;,
  1.000000;0.000000;0.000000;,
  0.934212;0.356719;0.000001;,
  0.876504;0.449604;-0.172039;,
  -0.920082;0.391726;0.000000;,
  -0.835697;0.514562;-0.191928;,
  -1.000000;0.000000;0.000000;,
  -0.914891;0.402158;-0.035251;,
  0.932457;0.359604;-0.034772;,
  0.856988;0.036096;0.514070;,
  0.903086;0.302991;-0.304355;,
  -0.959930;0.240203;-0.144349;,
  0.207207;0.192292;0.959213;,
  0.404096;0.910235;-0.090439;,
  0.400951;0.859396;-0.317296;,
  0.330799;0.671745;-0.662821;,
  0.000000;-1.000000;-0.000000;,
  0.240967;0.097374;0.965636;,
  -0.288231;0.679540;-0.674647;,
  -0.346875;0.880869;-0.322100;,
  -0.361462;0.928172;-0.088552;,
  -0.190872;0.192312;0.962592;,
  -0.225706;0.097356;0.969319;,
  -0.707107;0.000000;-0.707107;,
  -1.000000;0.000000;0.000001;,
  -0.707108;0.000000;0.707106;,
  0.000001;0.000000;1.000000;,
  0.707107;0.000000;0.707107;,
  1.000000;0.000000;0.000001;,
  0.707106;0.000000;-0.707108;,
  0.000001;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.408349;0.912826;0.000001;,
  -0.373604;0.927588;0.000000;,
  0.247590;0.507981;-0.825018;,
  -0.220574;0.500239;-0.837322;,
  -0.258675;0.000000;0.965964;,
  0.272727;0.000000;0.962091;,
  0.479475;0.489252;-0.728517;,
  0.404758;0.123392;0.906060;,
  -0.430186;0.481128;-0.763843;,
  -0.438796;0.062613;0.896403;,
  -0.374099;0.124690;0.918968;,
  -0.499741;0.000000;0.866175;;
  56;
  4;8,1,10,3;,
  4;19,20,13,14;,
  4;11,6,7,5;,
  4;16,16,16,16;,
  4;14,15,18,19;,
  4;21,22,17,12;,
  4;16,16,16,16;,
  4;4,7,6,6;,
  4;32,13,20,33;,
  4;9,1,8,2;,
  4;0,1,1,9;,
  4;10,1,1,1;,
  4;15,34,35,18;,
  4;6,6,11,6;,
  4;6,6,6,6;,
  4;22,36,37,17;,
  4;2,8,13,32;,
  4;14,13,8,3;,
  4;10,15,14,3;,
  4;38,34,15,10;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;17,37,0,9;,
  4;12,17,9,39;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;18,35,40,40;,
  4;19,18,11,5;,
  4;7,20,19,5;,
  4;33,20,7,4;,
  4;41,22,21,42;,
  4;43,36,22,41;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,23,23,30;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;;
 }
 MeshTextureCoords {
  52;
  0.397376;0.742188;,
  0.397376;0.772807;,
  0.397376;0.784984;,
  0.397376;0.751612;,
  0.479958;0.733890;,
  0.479958;0.723242;,
  0.406533;0.723242;,
  0.406533;0.733890;,
  0.489742;0.781441;,
  0.489742;0.769264;,
  0.489742;0.740644;,
  0.489742;0.748069;,
  0.406533;0.815608;,
  0.406533;0.815608;,
  0.479958;0.815608;,
  0.479958;0.815608;,
  0.406533;0.759863;,
  0.479958;0.759863;,
  0.479958;0.723242;,
  0.479958;0.763302;,
  0.406533;0.763302;,
  0.406533;0.723242;,
  0.479958;0.815608;,
  0.406533;0.815608;,
  0.489742;0.740644;,
  0.489742;0.769264;,
  0.397376;0.772807;,
  0.397376;0.742188;,
  0.397376;0.815608;,
  0.397376;0.815608;,
  0.397376;0.815608;,
  0.489742;0.815608;,
  0.489742;0.815608;,
  0.489742;0.815608;,
  0.583709;0.691310;,
  0.591244;0.691310;,
  0.591244;0.639860;,
  0.583709;0.639860;,
  0.583709;0.691310;,
  0.583709;0.639860;,
  0.565519;0.691310;,
  0.565519;0.639860;,
  0.547329;0.691310;,
  0.547329;0.639860;,
  0.539794;0.691310;,
  0.539794;0.639860;,
  0.547329;0.691310;,
  0.547329;0.639860;,
  0.565519;0.691310;,
  0.565519;0.639860;,
  0.565519;0.691310;,
  0.565519;0.639860;;
 }
}
