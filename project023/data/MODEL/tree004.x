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
 148;
 0.71836;60.58375;0.04215;,
 4.11520;60.58375;-3.35470;,
 0.71836;60.58375;-4.76172;,
 0.71836;60.58375;0.04215;,
 5.52220;60.58375;0.04215;,
 0.71836;60.58375;0.04215;,
 4.11520;60.58375;3.43897;,
 0.71836;60.58375;0.04215;,
 0.71836;60.58375;4.84599;,
 0.71836;60.58375;0.04215;,
 -2.67846;60.58375;3.43897;,
 0.71836;60.58375;0.04215;,
 -4.08549;60.58375;0.04215;,
 0.71836;60.58375;0.04215;,
 -2.67846;60.58375;-3.35470;,
 0.71836;60.58375;0.04215;,
 0.71836;60.58375;-4.76172;,
 0.58176;-0.54095;-0.06996;,
 0.58176;-0.54095;-6.81340;,
 5.71051;-0.61266;-5.52026;,
 0.58176;-0.54095;-0.06996;,
 7.32520;-0.54095;-0.06996;,
 0.58176;-0.54095;-0.06996;,
 4.98027;-1.20276;4.74845;,
 0.58176;-0.54095;-0.06996;,
 0.58176;-0.54095;6.67350;,
 0.58176;-0.54095;-0.06996;,
 -4.31669;-1.02062;5.26318;,
 0.58176;-0.54095;-0.06996;,
 -7.29141;-1.18843;0.49400;,
 0.58176;-0.54095;-0.06996;,
 -4.29818;-1.07649;-4.95185;,
 0.58176;-0.54095;-0.06996;,
 0.58176;-0.54095;-6.81340;,
 -5.27400;26.06432;0.45467;,
 -3.14380;25.07626;-4.69740;,
 -3.62308;25.50385;3.85744;,
 0.69519;25.64036;-6.04865;,
 -0.22293;25.08686;5.29578;,
 0.69519;25.64036;-6.04865;,
 4.05213;25.62647;-4.47609;,
 4.70654;22.93873;3.84827;,
 5.80138;23.08963;0.11319;,
 3.92267;39.91282;-3.86669;,
 5.37058;39.79996;0.39012;,
 1.08489;39.57403;-5.25721;,
 3.88289;39.61584;3.51038;,
 1.08489;39.57403;-5.25721;,
 -2.94883;39.58591;-3.91437;,
 0.18026;39.68313;4.72402;,
 -4.46765;40.01369;0.24161;,
 -2.61189;39.90459;3.43939;,
 -2.74791;93.65835;0.69212;,
 9.49158;92.89659;-8.60789;,
 0.84155;92.89659;-12.19084;,
 20.30580;78.94474;-20.92146;,
 0.84155;87.30485;-22.56145;,
 13.07453;92.89659;0.04215;,
 18.13042;87.54456;15.91297;,
 -7.80847;92.89659;-8.60789;,
 0.84155;92.89659;-12.19084;,
 0.84155;87.30485;-22.56145;,
 0.84155;78.93617;-29.49088;,
 0.84155;92.89659;12.27511;,
 -11.39143;92.89659;0.04212;,
 -20.04146;78.93617;20.92514;,
 0.84155;78.93617;29.57518;,
 -7.80847;92.89659;-8.60789;,
 -28.69150;78.93617;0.04212;,
 -20.59076;68.45584;-20.26992;,
 22.44227;68.64686;-21.76593;,
 27.98408;73.33150;-8.58082;,
 16.67526;50.90742;-15.49887;,
 21.72453;59.19257;-20.84087;,
 24.27612;68.09244;15.91893;,
 22.35640;52.01226;-0.53335;,
 0.84155;59.19257;29.57518;,
 -21.76205;69.06456;22.64574;,
 -15.14159;50.82381;16.02532;,
 0.84155;50.82381;22.64574;,
 16.67526;50.90742;-15.49887;,
 22.35640;52.01226;-0.53335;,
 15.13999;50.28503;14.82252;,
 9.21434;46.23605;-8.01987;,
 -7.80847;45.23197;8.69218;,
 0.84155;45.23197;12.27511;,
 -15.14159;50.82381;-15.94104;,
 0.84155;50.82381;-22.56145;,
 9.21434;46.23605;-8.01987;,
 -7.80847;45.23197;-8.60789;,
 0.84155;43.26858;0.04215;,
 0.84155;43.26858;0.04215;,
 -21.76205;69.06456;22.64574;,
 0.84155;78.93617;29.57518;,
 0.84155;78.93617;29.57518;,
 18.13042;87.54456;15.91297;,
 -21.76205;69.06456;22.64574;,
 27.98408;73.33150;-8.58082;,
 20.30580;78.94474;-20.92146;,
 20.30580;78.94474;-20.92146;,
 0.84155;78.93617;-29.49088;,
 27.98408;73.33150;-8.58082;,
 0.84155;92.89659;12.27511;,
 -2.74791;93.65835;0.69212;,
 -21.76205;69.06456;22.64574;,
 9.21434;46.23605;-8.01987;,
 0.84155;50.82381;-22.56145;,
 0.84155;45.23197;12.27511;,
 15.13999;50.28503;14.82252;,
 18.13042;87.54456;15.91297;,
 -26.82887;58.09717;-1.73681;,
 -20.59076;68.45584;-20.26992;,
 -15.14159;50.82381;-15.94104;,
 -26.82887;58.09717;-1.73681;,
 -15.14159;50.82381;-15.94104;,
 -21.76205;50.82381;0.04212;,
 6.18640;58.64385;-29.21161;,
 6.18640;58.64385;-29.21161;,
 -15.14159;50.82381;-15.94104;,
 3.80455;92.15230;7.58215;,
 18.13042;87.54456;15.91297;,
 3.80455;92.15230;7.58215;,
 0.84155;92.89659;12.27511;,
 -2.74791;93.65835;0.69212;,
 16.83857;56.71614;20.79904;,
 -26.45457;66.14417;-5.95183;,
 -26.45457;66.14417;-5.95183;,
 -20.59076;68.45584;-20.26992;,
 -7.44020;63.56023;-27.26151;,
 0.84155;78.93617;-29.49088;,
 -15.14159;50.82381;-15.94104;,
 -7.44020;63.56023;-27.26151;,
 -15.14159;50.82381;-15.94104;,
 12.22034;56.12335;-26.60165;,
 12.22034;56.12335;-26.60165;,
 0.84155;45.23197;12.27511;,
 0.84155;43.26858;0.04215;,
 -2.74791;93.65835;0.69212;,
 -11.39143;92.89659;0.04212;,
 -2.74791;93.65835;0.69212;,
 22.44227;68.64686;-21.76593;,
 -21.76205;69.06456;22.64574;,
 -13.23318;46.20750;0.51646;,
 0.84155;43.26858;0.04215;,
 -21.76205;50.82381;0.04212;,
 -13.23318;46.20750;0.51646;,
 -21.76205;50.82381;0.04212;,
 0.84155;43.26858;0.04215;;
 
 100;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,19;,
 3;20,19,21;,
 3;22,21,23;,
 3;24,23,25;,
 3;26,25,27;,
 3;28,27,29;,
 3;30,29,31;,
 3;32,31,33;,
 4;34,35,31,29;,
 4;34,29,27,36;,
 4;35,37,33,31;,
 4;36,27,25,38;,
 4;39,40,19,18;,
 4;38,25,23,41;,
 4;40,42,21,19;,
 4;41,23,21,42;,
 4;43,1,4,44;,
 4;43,44,42,40;,
 4;43,40,39,45;,
 4;43,45,2,1;,
 4;44,4,6,46;,
 4;44,46,41,42;,
 4;47,37,35,48;,
 4;47,48,14,16;,
 4;46,6,8,49;,
 4;46,49,38,41;,
 4;48,35,34,50;,
 4;48,50,12,14;,
 4;49,8,10,51;,
 4;49,51,36,38;,
 4;50,34,36,51;,
 4;50,51,10,12;,
 3;52,53,54;,
 4;54,53,55,56;,
 4;53,57,58,55;,
 4;59,60,61,62;,
 4;63,64,65,66;,
 4;64,67,68,65;,
 4;67,62,69,68;,
 4;70,71,72,73;,
 4;71,74,75,72;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;79,78,84,85;,
 4;86,87,88,89;,
 3;85,84,90;,
 3;89,88,91;,
 3;92,76,93;,
 3;94,74,95;,
 3;94,65,96;,
 3;97,70,98;,
 3;97,95,74;,
 3;99,100,56;,
 3;99,58,101;,
 3;102,103,64;,
 3;104,65,68;,
 3;105,106,80;,
 3;107,108,79;,
 3;109,63,66;,
 3;110,111,112;,
 3;113,78,77;,
 3;113,114,115;,
 3;113,115,78;,
 3;116,98,70;,
 3;116,100,98;,
 3;117,87,118;,
 3;119,120,57;,
 3;121,122,120;,
 3;121,123,122;,
 3;124,75,74;,
 3;124,108,75;,
 3;125,111,110;,
 3;126,68,127;,
 3;128,127,129;,
 3;128,130,127;,
 3;131,116,132;,
 3;131,100,116;,
 3;133,87,117;,
 4;106,134,73,80;,
 4;83,82,135,136;,
 4;74,93,76,124;,
 4;53,137,119,57;,
 4;138,139,60,59;,
 4;73,134,117,140;,
 4;76,79,108,124;,
 4;110,141,68,126;,
 3;142,89,143;,
 3;142,144,86;,
 3;142,86,89;,
 3;145,78,146;,
 3;145,147,84;,
 3;145,84,78;;
 
 MeshMaterialList {
  2;
  100;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.316800;0.216800;0.062400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "af18.jpg";
   }
  }
  Material {
   0.200800;0.605600;0.257600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\leaf000.jpg";
   }
  }
 }
 MeshNormals {
  85;
  0.000000;1.000000;0.000000;,
  0.047644;-0.998864;-0.000000;,
  -0.006990;-0.999954;0.006577;,
  0.000000;-0.998099;-0.061631;,
  -0.074774;-0.994853;-0.068384;,
  -0.025862;-0.999665;0.000000;,
  0.089163;-0.995988;-0.007684;,
  0.082323;-0.996593;0.005096;,
  0.096436;-0.995257;0.012780;,
  0.026163;-0.999558;-0.014153;,
  -0.997138;0.061778;0.043573;,
  -0.680768;0.049631;-0.730816;,
  -0.659559;0.060376;0.749224;,
  0.024601;0.044593;-0.998702;,
  -0.019094;0.048819;0.998625;,
  0.730998;0.048004;-0.680689;,
  0.694861;0.043759;0.717812;,
  0.998682;0.045759;0.023257;,
  0.736168;0.023116;-0.676404;,
  0.999675;0.013582;0.021585;,
  0.044191;0.039766;-0.998231;,
  0.685123;0.014862;0.728275;,
  -0.696276;0.038587;-0.716736;,
  -0.039874;0.020703;0.998990;,
  -0.998015;0.036822;0.051099;,
  -0.682976;0.034200;0.729640;,
  -0.670709;0.044363;-0.740393;,
  -0.997546;0.064224;0.027893;,
  -0.643355;0.058469;0.763332;,
  -0.005928;0.035337;-0.999358;,
  0.012773;0.053585;0.998482;,
  0.717905;0.060061;-0.693546;,
  0.703622;0.050833;0.708754;,
  0.997732;0.059073;0.032264;,
  0.728747;0.009945;-0.684711;,
  0.999562;-0.005488;0.029066;,
  0.032782;0.025566;-0.999135;,
  0.684122;-0.006385;0.729339;,
  -0.701428;0.022231;-0.712393;,
  -0.028578;-0.002810;0.999588;,
  -0.998956;0.014451;0.043338;,
  -0.690108;0.005955;0.723682;,
  0.031036;0.999456;0.011107;,
  -0.050182;0.948495;-0.312793;,
  0.298323;0.937672;-0.178252;,
  0.340381;0.938209;0.062491;,
  0.060709;0.764677;-0.641547;,
  0.553712;0.817446;0.158695;,
  0.044951;0.962614;0.267122;,
  -0.292644;0.945110;0.145351;,
  -0.459474;0.828614;-0.319816;,
  -0.172469;0.394555;-0.902541;,
  0.591497;0.520387;-0.615897;,
  -0.637325;0.578538;0.509029;,
  -0.930441;0.353773;-0.095520;,
  -0.768154;-0.034264;-0.639348;,
  -0.507020;-0.673785;-0.537536;,
  0.981393;0.137513;-0.134008;,
  0.923848;-0.115072;0.365052;,
  0.033373;0.391488;0.919578;,
  -0.723436;-0.112214;0.681211;,
  0.740406;0.003110;-0.672153;,
  0.690022;-0.428015;-0.583671;,
  0.646587;-0.716417;-0.262055;,
  0.808626;-0.572408;0.135918;,
  0.043730;-0.333470;0.941746;,
  0.043271;-0.790348;-0.611128;,
  -0.006489;-0.772385;0.635122;,
  -0.558371;-0.718257;0.415126;,
  0.194858;-0.959143;-0.205123;,
  0.450025;-0.827766;0.335082;,
  0.080453;-0.947106;0.310672;,
  -0.236228;-0.947311;0.216328;,
  -0.664024;-0.747656;0.009055;,
  -0.173597;-0.957472;-0.230459;,
  -0.012698;-0.999913;-0.003516;,
  -0.922176;-0.382657;-0.056255;,
  0.072717;-0.242523;-0.967416;,
  0.181555;0.978941;0.093336;,
  0.675880;-0.427993;0.600007;,
  -0.974862;-0.074940;-0.209830;,
  -0.376655;-0.217066;-0.900562;,
  0.328584;-0.538206;-0.776123;,
  -0.387156;-0.922007;0.003684;,
  0.555063;0.175616;0.813058;;
  100;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,1,2;,
  3;9,2,3;,
  3;9,3,4;,
  3;9,4,5;,
  3;9,5,6;,
  3;9,6,7;,
  3;9,7,8;,
  3;9,8,1;,
  4;10,11,26,27;,
  4;10,27,28,12;,
  4;11,13,29,26;,
  4;12,28,30,14;,
  4;13,15,31,29;,
  4;14,30,32,16;,
  4;15,17,33,31;,
  4;16,32,33,17;,
  4;18,34,35,19;,
  4;18,19,17,15;,
  4;18,15,13,20;,
  4;18,20,36,34;,
  4;19,35,37,21;,
  4;19,21,16,17;,
  4;20,13,11,22;,
  4;20,22,38,36;,
  4;21,37,39,23;,
  4;21,23,14,16;,
  4;22,11,10,24;,
  4;22,24,40,38;,
  4;23,39,41,25;,
  4;23,25,12,14;,
  4;24,10,12,25;,
  4;24,25,41,40;,
  3;42,44,43;,
  4;43,44,52,46;,
  4;44,45,47,52;,
  4;50,43,46,51;,
  4;48,49,53,59;,
  4;49,50,54,53;,
  4;50,51,55,54;,
  4;61,57,63,62;,
  4;57,58,64,63;,
  4;65,60,68,67;,
  4;63,64,70,69;,
  4;67,68,72,71;,
  4;56,66,69,74;,
  3;71,72,75;,
  3;74,69,75;,
  3;60,65,59;,
  3;59,84,84;,
  3;59,53,60;,
  3;57,61,52;,
  3;57,47,58;,
  3;52,51,46;,
  3;52,47,57;,
  3;48,42,49;,
  3;60,53,54;,
  3;69,66,63;,
  3;71,70,67;,
  3;47,48,59;,
  3;76,55,56;,
  3;76,68,60;,
  3;76,56,73;,
  3;76,73,68;,
  3;77,52,61;,
  3;77,51,52;,
  3;77,66,56;,
  3;78,47,45;,
  3;78,48,47;,
  3;78,42,48;,
  3;79,64,58;,
  3;79,70,64;,
  3;80,55,76;,
  3;80,54,55;,
  3;81,55,51;,
  3;81,56,55;,
  3;81,77,56;,
  3;81,51,77;,
  3;82,66,77;,
  4;66,82,62,63;,
  4;69,70,71,75;,
  4;58,59,65,79;,
  4;44,42,78,45;,
  4;49,42,43,50;,
  4;62,82,77,61;,
  4;65,67,70,79;,
  4;76,60,54,80;,
  3;83,74,75;,
  3;83,73,56;,
  3;83,56,74;,
  3;83,68,73;,
  3;83,75,72;,
  3;83,72,68;;
 }
 MeshTextureCoords {
  148;
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.750000;0.589950;,
  0.875000;0.589950;,
  0.625000;0.589950;,
  1.000000;0.589950;,
  0.500000;0.589950;,
  0.000000;0.589950;,
  0.125000;0.589950;,
  0.375000;0.589950;,
  0.250000;0.589950;,
  0.125000;0.327620;,
  0.250000;0.327620;,
  0.000000;0.327620;,
  0.375000;0.327620;,
  1.000000;0.327620;,
  0.875000;0.327620;,
  0.500000;0.327620;,
  0.750000;0.327620;,
  0.625000;0.327620;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.125000;,
  0.250000;0.250000;,
  0.875000;0.125000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.875000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.500000;0.375000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.125000;0.625000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.500000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.125000;0.875000;,
  0.625000;0.875000;,
  0.500000;0.875000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  0.875000;0.875000;,
  0.562500;1.000000;,
  0.937500;1.000000;,
  0.625000;0.562500;,
  0.500000;0.500000;,
  0.500000;0.437500;,
  0.375000;0.375000;,
  0.625000;0.500000;,
  0.250000;0.437500;,
  0.125000;0.375000;,
  0.125000;0.312500;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.500000;0.187500;,
  0.625000;0.125000;,
  0.687500;0.500000;,
  0.062500;0.875000;,
  0.000000;0.750000;,
  0.437500;0.875000;,
  0.375000;0.750000;,
  0.375000;0.312500;,
  0.789180;0.578360;,
  0.875000;0.500000;,
  0.812500;0.625000;,
  0.703360;0.625000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.062630;0.500000;,
  0.937630;0.656180;,
  0.875000;0.687500;,
  0.353080;0.081170;,
  0.375000;0.125000;,
  0.396920;0.081170;,
  0.500000;0.125000;,
  0.437500;0.000000;,
  0.450790;0.625000;,
  0.819480;0.500000;,
  0.819480;0.465260;,
  0.875000;0.437500;,
  1.000000;0.441690;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.441690;,
  0.000000;0.500000;,
  1.000000;0.698100;,
  0.000000;0.698100;,
  0.375000;0.875000;,
  0.312500;1.000000;,
  0.187500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  1.000000;0.625000;,
  0.750000;0.500000;,
  0.785140;0.945290;,
  0.812500;1.000000;,
  0.750000;0.875000;,
  0.714860;0.917930;,
  0.750000;0.812500;,
  0.687500;1.000000;;
 }
}
