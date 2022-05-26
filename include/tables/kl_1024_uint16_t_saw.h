#ifndef kl_1024_uint16_t_saw_h
#define kl_1024_uint16_t_saw_h

#define KL_1024_uint16_t_saw_cells 1024

namespace lamb {
  namespace tables {
    namespace saw1024_uint16_t {
      typedef uint16_t value_type;
      const   size_t length = 1024;
      const   uint16_t data[]
#ifdef __AVR__
PROGMEM
#endif
      = {
         32768,    32831,    32895,    32959,    33023,    33087,    33151,    33215, 
         33279,    33343,    33407,    33471,    33535,    33599,    33663,    33727, 
         33791,    33855,    33919,    33983,    34047,    34111,    34175,    34239, 
         34303,    34367,    34431,    34495,    34559,    34623,    34687,    34751, // 31
    
         34815,    34879,    34943,    35007,    35071,    35135,    35199,    35263, 
         35327,    35391,    35455,    35519,    35583,    35647,    35711,    35775, 
         35839,    35903,    35967,    36031,    36095,    36159,    36223,    36287, 
         36351,    36415,    36479,    36543,    36607,    36671,    36735,    36799, // 63
    
         36863,    36927,    36991,    37055,    37119,    37183,    37247,    37311, 
         37375,    37439,    37503,    37567,    37631,    37695,    37759,    37823, 
         37887,    37951,    38015,    38079,    38143,    38207,    38271,    38335, 
         38399,    38463,    38527,    38591,    38655,    38719,    38783,    38847, // 95
    
         38911,    38975,    39039,    39103,    39167,    39231,    39295,    39359, 
         39423,    39487,    39551,    39615,    39679,    39743,    39807,    39871, 
         39935,    39999,    40063,    40127,    40191,    40255,    40319,    40383, 
         40447,    40511,    40575,    40639,    40703,    40767,    40831,    40895, // 127
    
         40959,    41023,    41087,    41151,    41215,    41279,    41343,    41407, 
         41471,    41535,    41599,    41663,    41727,    41791,    41855,    41919, 
         41983,    42047,    42111,    42175,    42239,    42303,    42367,    42431, 
         42495,    42559,    42623,    42687,    42751,    42815,    42879,    42943, // 159
    
         43007,    43071,    43135,    43199,    43263,    43327,    43391,    43455, 
         43519,    43583,    43647,    43711,    43775,    43839,    43903,    43967, 
         44031,    44095,    44159,    44223,    44287,    44351,    44415,    44479, 
         44543,    44607,    44671,    44735,    44799,    44863,    44927,    44991, // 191
    
         45055,    45119,    45183,    45247,    45311,    45375,    45439,    45503, 
         45567,    45631,    45695,    45759,    45823,    45887,    45951,    46015, 
         46079,    46143,    46207,    46271,    46335,    46399,    46463,    46527, 
         46591,    46655,    46719,    46783,    46847,    46911,    46975,    47039, // 223
    
         47103,    47167,    47231,    47295,    47359,    47423,    47487,    47551, 
         47615,    47679,    47743,    47807,    47871,    47935,    47999,    48063, 
         48127,    48191,    48255,    48319,    48383,    48447,    48511,    48575, 
         48639,    48703,    48767,    48831,    48895,    48959,    49023,    49087, // 255
    
         49151,    49215,    49279,    49343,    49407,    49471,    49535,    49599, 
         49663,    49727,    49791,    49855,    49919,    49983,    50047,    50111, 
         50175,    50239,    50303,    50367,    50431,    50495,    50559,    50623, 
         50687,    50751,    50815,    50879,    50943,    51007,    51071,    51135, // 287
    
         51199,    51263,    51327,    51391,    51455,    51519,    51583,    51647, 
         51711,    51775,    51839,    51903,    51967,    52031,    52095,    52159, 
         52223,    52287,    52351,    52415,    52479,    52543,    52607,    52671, 
         52735,    52799,    52863,    52927,    52991,    53055,    53119,    53183, // 319
    
         53247,    53311,    53375,    53439,    53503,    53567,    53631,    53695, 
         53759,    53823,    53887,    53951,    54015,    54079,    54143,    54207, 
         54271,    54335,    54399,    54463,    54527,    54591,    54655,    54719, 
         54783,    54847,    54911,    54975,    55039,    55103,    55167,    55231, // 351
    
         55295,    55359,    55423,    55487,    55551,    55615,    55679,    55743, 
         55807,    55871,    55935,    55999,    56063,    56127,    56191,    56255, 
         56319,    56383,    56447,    56511,    56575,    56639,    56703,    56767, 
         56831,    56895,    56959,    57023,    57087,    57151,    57215,    57279, // 383
    
         57343,    57407,    57471,    57535,    57599,    57663,    57727,    57791, 
         57855,    57919,    57983,    58047,    58111,    58175,    58239,    58303, 
         58367,    58431,    58495,    58559,    58623,    58687,    58751,    58815, 
         58879,    58943,    59007,    59071,    59135,    59199,    59263,    59327, // 415
    
         59391,    59455,    59519,    59583,    59647,    59711,    59775,    59839, 
         59903,    59967,    60031,    60095,    60159,    60223,    60287,    60351, 
         60415,    60479,    60543,    60607,    60671,    60735,    60799,    60863, 
         60927,    60991,    61055,    61119,    61183,    61247,    61311,    61375, // 447
    
         61439,    61503,    61567,    61631,    61695,    61759,    61823,    61887, 
         61951,    62015,    62079,    62143,    62207,    62271,    62335,    62399, 
         62463,    62527,    62591,    62655,    62719,    62783,    62847,    62911, 
         62975,    63039,    63103,    63167,    63231,    63295,    63359,    63423, // 479
    
         63487,    63551,    63615,    63679,    63743,    63807,    63871,    63935, 
         63999,    64063,    64127,    64191,    64255,    64319,    64383,    64447, 
         64511,    64575,    64639,    64703,    64767,    64831,    64895,    64959, 
         65023,    65087,    65151,    65215,    65279,    65343,    65407,    65471, // 511
    
         65535,       64,      128,      192,      256,      320,      384,      448, 
           512,      576,      640,      704,      768,      832,      896,      960, 
          1024,     1088,     1152,     1216,     1280,     1344,     1408,     1472, 
          1536,     1600,     1664,     1728,     1792,     1856,     1920,     1984, // 543
    
          2048,     2112,     2176,     2240,     2304,     2368,     2432,     2496, 
          2560,     2624,     2688,     2752,     2816,     2880,     2944,     3008, 
          3072,     3136,     3200,     3264,     3328,     3392,     3456,     3520, 
          3584,     3648,     3712,     3776,     3840,     3904,     3968,     4032, // 575
    
          4096,     4160,     4224,     4288,     4352,     4416,     4480,     4544, 
          4608,     4672,     4736,     4800,     4864,     4928,     4992,     5056, 
          5120,     5184,     5248,     5312,     5376,     5440,     5504,     5568, 
          5632,     5696,     5760,     5824,     5888,     5952,     6016,     6080, // 607
    
          6144,     6208,     6272,     6336,     6400,     6464,     6528,     6592, 
          6656,     6720,     6784,     6848,     6912,     6976,     7040,     7104, 
          7168,     7232,     7296,     7360,     7424,     7488,     7552,     7616, 
          7680,     7744,     7808,     7872,     7936,     8000,     8064,     8128, // 639
    
          8192,     8256,     8320,     8384,     8448,     8512,     8576,     8640, 
          8704,     8768,     8832,     8896,     8960,     9024,     9088,     9152, 
          9216,     9280,     9344,     9408,     9472,     9536,     9600,     9664, 
          9728,     9792,     9856,     9920,     9984,    10048,    10112,    10176, // 671
    
         10240,    10304,    10368,    10432,    10496,    10560,    10624,    10688, 
         10752,    10816,    10880,    10944,    11008,    11072,    11136,    11200, 
         11264,    11328,    11392,    11456,    11520,    11584,    11648,    11712, 
         11776,    11840,    11904,    11968,    12032,    12096,    12160,    12224, // 703
    
         12288,    12352,    12416,    12480,    12544,    12608,    12672,    12736, 
         12800,    12864,    12928,    12992,    13056,    13120,    13184,    13248, 
         13312,    13376,    13440,    13504,    13568,    13632,    13696,    13760, 
         13824,    13888,    13952,    14016,    14080,    14144,    14208,    14272, // 735
    
         14336,    14400,    14464,    14528,    14592,    14656,    14720,    14784, 
         14848,    14912,    14976,    15040,    15104,    15168,    15232,    15296, 
         15360,    15424,    15488,    15552,    15616,    15680,    15744,    15808, 
         15872,    15936,    16000,    16064,    16128,    16192,    16256,    16320, // 767
    
         16384,    16448,    16512,    16576,    16640,    16704,    16768,    16832, 
         16896,    16960,    17024,    17088,    17152,    17216,    17280,    17344, 
         17408,    17472,    17536,    17600,    17664,    17728,    17792,    17856, 
         17920,    17984,    18048,    18112,    18176,    18240,    18304,    18368, // 799
    
         18432,    18496,    18560,    18624,    18688,    18752,    18816,    18880, 
         18944,    19008,    19072,    19136,    19200,    19264,    19328,    19392, 
         19456,    19520,    19584,    19648,    19712,    19776,    19840,    19904, 
         19968,    20032,    20096,    20160,    20224,    20288,    20352,    20416, // 831
    
         20480,    20544,    20608,    20672,    20736,    20800,    20864,    20928, 
         20992,    21056,    21120,    21184,    21248,    21312,    21376,    21440, 
         21504,    21568,    21632,    21696,    21760,    21824,    21888,    21952, 
         22016,    22080,    22144,    22208,    22272,    22336,    22400,    22464, // 863
    
         22528,    22592,    22656,    22720,    22784,    22848,    22912,    22976, 
         23040,    23104,    23168,    23232,    23296,    23360,    23424,    23488, 
         23552,    23616,    23680,    23744,    23808,    23872,    23936,    24000, 
         24064,    24128,    24192,    24256,    24320,    24384,    24448,    24512, // 895
    
         24576,    24640,    24704,    24768,    24832,    24896,    24960,    25024, 
         25088,    25152,    25216,    25280,    25344,    25408,    25472,    25536, 
         25600,    25664,    25728,    25792,    25856,    25920,    25984,    26048, 
         26112,    26176,    26240,    26304,    26368,    26432,    26496,    26560, // 927
    
         26624,    26688,    26752,    26816,    26880,    26944,    27008,    27072, 
         27136,    27200,    27264,    27328,    27392,    27456,    27520,    27584, 
         27648,    27712,    27776,    27840,    27904,    27968,    28032,    28096, 
         28160,    28224,    28288,    28352,    28416,    28480,    28544,    28608, // 959
    
         28672,    28736,    28800,    28864,    28928,    28992,    29056,    29120, 
         29184,    29248,    29312,    29376,    29440,    29504,    29568,    29632, 
         29696,    29760,    29824,    29888,    29952,    30016,    30080,    30144, 
         30208,    30272,    30336,    30400,    30464,    30528,    30592,    30656, // 991
    
         30720,    30784,    30848,    30912,    30976,    31040,    31104,    31168, 
         31232,    31296,    31360,    31424,    31488,    31552,    31616,    31680, 
         31744,    31808,    31872,    31936,    32000,    32064,    32128,    32192, 
         32256,    32320,    32384,    32448,    32512,    32576,    32640,    32704, // 1023
    
      };
    }
  }
}
#endif
