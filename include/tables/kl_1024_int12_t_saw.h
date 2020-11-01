#ifndef kl_1024_int12_t_saw_h
#define kl_1024_int12_t_saw_h

#define KL_1024_int12_t_saw_cells 1024

namespace lamb {
  namespace tables {
    namespace saw1024_int12_t {
      typedef int16_t value_type;
      const   size_t length = 1024;
      const   int16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
             0,        3,        7,       11,       15,       19,       23,       27, 
            31,       35,       39,       43,       47,       51,       55,       59, 
            63,       67,       71,       75,       79,       83,       87,       91, 
            95,       99,      103,      107,      111,      115,      119,      123, // 31
    
           127,      131,      135,      139,      143,      147,      151,      155, 
           159,      163,      167,      171,      175,      179,      183,      187, 
           191,      195,      199,      203,      207,      211,      215,      219, 
           223,      227,      231,      235,      239,      243,      247,      251, // 63
    
           255,      259,      263,      267,      271,      275,      279,      283, 
           287,      291,      295,      299,      303,      307,      311,      315, 
           319,      323,      327,      331,      335,      339,      343,      347, 
           351,      355,      359,      363,      367,      371,      375,      379, // 95
    
           383,      387,      391,      395,      399,      403,      407,      411, 
           415,      419,      423,      427,      431,      435,      439,      443, 
           447,      451,      455,      459,      463,      467,      471,      475, 
           479,      483,      487,      491,      495,      499,      503,      507, // 127
    
           511,      515,      519,      523,      527,      531,      535,      539, 
           543,      547,      551,      555,      559,      563,      567,      571, 
           575,      579,      583,      587,      591,      595,      599,      603, 
           607,      611,      615,      619,      623,      627,      631,      635, // 159
    
           639,      643,      647,      651,      655,      659,      663,      667, 
           671,      675,      679,      683,      687,      691,      695,      699, 
           703,      707,      711,      715,      719,      723,      727,      731, 
           735,      739,      743,      747,      751,      755,      759,      763, // 191
    
           767,      771,      775,      779,      783,      787,      791,      795, 
           799,      803,      807,      811,      815,      819,      823,      827, 
           831,      835,      839,      843,      847,      851,      855,      859, 
           863,      867,      871,      875,      879,      883,      887,      891, // 223
    
           895,      899,      903,      907,      911,      915,      919,      923, 
           927,      931,      935,      939,      943,      947,      951,      955, 
           959,      963,      967,      971,      975,      979,      983,      987, 
           991,      995,      999,     1003,     1007,     1011,     1015,     1019, // 255
    
          1023,     1027,     1031,     1035,     1039,     1043,     1047,     1051, 
          1055,     1059,     1063,     1067,     1071,     1075,     1079,     1083, 
          1087,     1091,     1095,     1099,     1103,     1107,     1111,     1115, 
          1119,     1123,     1127,     1131,     1135,     1139,     1143,     1147, // 287
    
          1151,     1155,     1159,     1163,     1167,     1171,     1175,     1179, 
          1183,     1187,     1191,     1195,     1199,     1203,     1207,     1211, 
          1215,     1219,     1223,     1227,     1231,     1235,     1239,     1243, 
          1247,     1251,     1255,     1259,     1263,     1267,     1271,     1275, // 319
    
          1279,     1283,     1287,     1291,     1295,     1299,     1303,     1307, 
          1311,     1315,     1319,     1323,     1327,     1331,     1335,     1339, 
          1343,     1347,     1351,     1355,     1359,     1363,     1367,     1371, 
          1375,     1379,     1383,     1387,     1391,     1395,     1399,     1403, // 351
    
          1407,     1411,     1415,     1419,     1423,     1427,     1431,     1435, 
          1439,     1443,     1447,     1451,     1455,     1459,     1463,     1467, 
          1471,     1475,     1479,     1483,     1487,     1491,     1495,     1499, 
          1503,     1507,     1511,     1515,     1519,     1523,     1527,     1531, // 383
    
          1535,     1539,     1543,     1547,     1551,     1555,     1559,     1563, 
          1567,     1571,     1575,     1579,     1583,     1587,     1591,     1595, 
          1599,     1603,     1607,     1611,     1615,     1619,     1623,     1627, 
          1631,     1635,     1639,     1643,     1647,     1651,     1655,     1659, // 415
    
          1663,     1667,     1671,     1675,     1679,     1683,     1687,     1691, 
          1695,     1699,     1703,     1707,     1711,     1715,     1719,     1723, 
          1727,     1731,     1735,     1739,     1743,     1747,     1751,     1755, 
          1759,     1763,     1767,     1771,     1775,     1779,     1783,     1787, // 447
    
          1791,     1795,     1799,     1803,     1807,     1811,     1815,     1819, 
          1823,     1827,     1831,     1835,     1839,     1843,     1847,     1851, 
          1855,     1859,     1863,     1867,     1871,     1875,     1879,     1883, 
          1887,     1891,     1895,     1899,     1903,     1907,     1911,     1915, // 479
    
          1919,     1923,     1927,     1931,     1935,     1939,     1943,     1947, 
          1951,     1955,     1959,     1963,     1967,     1971,     1975,     1979, 
          1983,     1987,     1991,     1995,     1999,     2003,     2007,     2011, 
          2015,     2019,     2023,     2027,     2031,     2035,     2039,     2043, // 511
    
          2047,    -2043,    -2039,    -2035,    -2031,    -2027,    -2023,    -2019, 
         -2015,    -2011,    -2007,    -2003,    -1999,    -1995,    -1991,    -1987, 
         -1983,    -1979,    -1975,    -1971,    -1967,    -1963,    -1959,    -1955, 
         -1951,    -1947,    -1943,    -1939,    -1935,    -1931,    -1927,    -1923, // 543
    
         -1919,    -1915,    -1911,    -1907,    -1903,    -1899,    -1895,    -1891, 
         -1887,    -1883,    -1879,    -1875,    -1871,    -1867,    -1863,    -1859, 
         -1855,    -1851,    -1847,    -1843,    -1839,    -1835,    -1831,    -1827, 
         -1823,    -1819,    -1815,    -1811,    -1807,    -1803,    -1799,    -1795, // 575
    
         -1791,    -1787,    -1783,    -1779,    -1775,    -1771,    -1767,    -1763, 
         -1759,    -1755,    -1751,    -1747,    -1743,    -1739,    -1735,    -1731, 
         -1727,    -1723,    -1719,    -1715,    -1711,    -1707,    -1703,    -1699, 
         -1695,    -1691,    -1687,    -1683,    -1679,    -1675,    -1671,    -1667, // 607
    
         -1663,    -1659,    -1655,    -1651,    -1647,    -1643,    -1639,    -1635, 
         -1631,    -1627,    -1623,    -1619,    -1615,    -1611,    -1607,    -1603, 
         -1599,    -1595,    -1591,    -1587,    -1583,    -1579,    -1575,    -1571, 
         -1567,    -1563,    -1559,    -1555,    -1551,    -1547,    -1543,    -1539, // 639
    
         -1535,    -1531,    -1527,    -1523,    -1519,    -1515,    -1511,    -1507, 
         -1503,    -1499,    -1495,    -1491,    -1487,    -1483,    -1479,    -1475, 
         -1471,    -1467,    -1463,    -1459,    -1455,    -1451,    -1447,    -1443, 
         -1439,    -1435,    -1431,    -1427,    -1423,    -1419,    -1415,    -1411, // 671
    
         -1407,    -1403,    -1399,    -1395,    -1391,    -1387,    -1383,    -1379, 
         -1375,    -1371,    -1367,    -1363,    -1359,    -1355,    -1351,    -1347, 
         -1343,    -1339,    -1335,    -1331,    -1327,    -1323,    -1319,    -1315, 
         -1311,    -1307,    -1303,    -1299,    -1295,    -1291,    -1287,    -1283, // 703
    
         -1279,    -1275,    -1271,    -1267,    -1263,    -1259,    -1255,    -1251, 
         -1247,    -1243,    -1239,    -1235,    -1231,    -1227,    -1223,    -1219, 
         -1215,    -1211,    -1207,    -1203,    -1199,    -1195,    -1191,    -1187, 
         -1183,    -1179,    -1175,    -1171,    -1167,    -1163,    -1159,    -1155, // 735
    
         -1151,    -1147,    -1143,    -1139,    -1135,    -1131,    -1127,    -1123, 
         -1119,    -1115,    -1111,    -1107,    -1103,    -1099,    -1095,    -1091, 
         -1087,    -1083,    -1079,    -1075,    -1071,    -1067,    -1063,    -1059, 
         -1055,    -1051,    -1047,    -1043,    -1039,    -1035,    -1031,    -1027, // 767
    
         -1023,    -1019,    -1015,    -1011,    -1007,    -1003,     -999,     -995, 
          -991,     -987,     -983,     -979,     -975,     -971,     -967,     -963, 
          -959,     -955,     -951,     -947,     -943,     -939,     -935,     -931, 
          -927,     -923,     -919,     -915,     -911,     -907,     -903,     -899, // 799
    
          -895,     -891,     -887,     -883,     -879,     -875,     -871,     -867, 
          -863,     -859,     -855,     -851,     -847,     -843,     -839,     -835, 
          -831,     -827,     -823,     -819,     -815,     -811,     -807,     -803, 
          -799,     -795,     -791,     -787,     -783,     -779,     -775,     -771, // 831
    
          -767,     -763,     -759,     -755,     -751,     -747,     -743,     -739, 
          -735,     -731,     -727,     -723,     -719,     -715,     -711,     -707, 
          -703,     -699,     -695,     -691,     -687,     -683,     -679,     -675, 
          -671,     -667,     -663,     -659,     -655,     -651,     -647,     -643, // 863
    
          -639,     -635,     -631,     -627,     -623,     -619,     -615,     -611, 
          -607,     -603,     -599,     -595,     -591,     -587,     -583,     -579, 
          -575,     -571,     -567,     -563,     -559,     -555,     -551,     -547, 
          -543,     -539,     -535,     -531,     -527,     -523,     -519,     -515, // 895
    
          -511,     -507,     -503,     -499,     -495,     -491,     -487,     -483, 
          -479,     -475,     -471,     -467,     -463,     -459,     -455,     -451, 
          -447,     -443,     -439,     -435,     -431,     -427,     -423,     -419, 
          -415,     -411,     -407,     -403,     -399,     -395,     -391,     -387, // 927
    
          -383,     -379,     -375,     -371,     -367,     -363,     -359,     -355, 
          -351,     -347,     -343,     -339,     -335,     -331,     -327,     -323, 
          -319,     -315,     -311,     -307,     -303,     -299,     -295,     -291, 
          -287,     -283,     -279,     -275,     -271,     -267,     -263,     -259, // 959
    
          -255,     -251,     -247,     -243,     -239,     -235,     -231,     -227, 
          -223,     -219,     -215,     -211,     -207,     -203,     -199,     -195, 
          -191,     -187,     -183,     -179,     -175,     -171,     -167,     -163, 
          -159,     -155,     -151,     -147,     -143,     -139,     -135,     -131, // 991
    
          -127,     -123,     -119,     -115,     -111,     -107,     -103,      -99, 
           -95,      -91,      -87,      -83,      -79,      -75,      -71,      -67, 
           -63,      -59,      -55,      -51,      -47,      -43,      -39,      -35, 
           -31,      -27,      -23,      -19,      -15,      -11,       -7,       -3, // 1023
    
      };
    }
  }
}
#endif
