#ifndef KL_1024_s0q15_cosh_h 
#define KL_1024_s0q15_cosh_h 

#define KL_1024_s0q15_cosh_h_cells 

namespace lamb {
 namespace tables {
  namespace cosh1024_s0q15 {
   typedef s0q15 q_t; 
   const size_t length = 1024; 
   const q_t  data[] 
#ifdef __AVR__ 
   PROGMEM 
#endif 
   = { 
    q_t(-22695), q_t(-29654), q_t( 28977), q_t( 22127),  // 0 
    q_t( 15329), q_t(  8585), q_t(  1893), q_t( -4747),  // 4 
    q_t(-11335), q_t(-17872), q_t(-24358), q_t(-30794),  // 8 
    q_t( 28357), q_t( 22022), q_t( 15735), q_t(  9498),  // 12 
    q_t(  3309), q_t( -2831), q_t( -8924), q_t(-14969),  // 16 
    q_t(-20967), q_t(-26919), q_t( 32712), q_t( 26853),  // 20 
    q_t( 21040), q_t( 15272), q_t(  9548), q_t(  3870),  // 24 
    q_t( -1765), q_t( -7355), q_t(-12902), q_t(-18406),  // 28 
    q_t(-23867), q_t(-29285), q_t( 30875), q_t( 25541),  // 32 
    q_t( 20248), q_t( 14997), q_t(  9786), q_t(  4616),  // 36 
    q_t(  -513), q_t( -5603), q_t(-10653), q_t(-15664),  // 40 
    q_t(-20635), q_t(-25568), q_t(-30462), q_t( 30217),  // 44 
    q_t( 25399), q_t( 20618), q_t( 15874), q_t( 11168),  // 48 
    q_t(  6498), q_t(  1864), q_t( -2733), q_t( -7295),  // 52 
    q_t(-11821), q_t(-16312), q_t(-20768), q_t(-25189),  // 56 
    q_t(-29575), q_t( 31608), q_t( 27290), q_t( 23005),  // 60 
    q_t( 18754), q_t( 14535), q_t( 10350), q_t(  6197),  // 64 
    q_t(  2077), q_t( -2011), q_t( -6068), q_t(-10092),  // 68 
    q_t(-14086), q_t(-18048), q_t(-21979), q_t(-25880),  // 72 
    q_t(-29750), q_t( 31946), q_t( 28136), q_t( 24356),  // 76 
    q_t( 20605), q_t( 16883), q_t( 13190), q_t(  9527),  // 80 
    q_t(  5891), q_t(  2285), q_t( -1294), q_t( -4845),  // 84 
    q_t( -8368), q_t(-11864), q_t(-15332), q_t(-18773),  // 88 
    q_t(-22188), q_t(-25575), q_t(-28937), q_t(-32272),  // 92 
    q_t( 29955), q_t( 26672), q_t( 23414), q_t( 20182),  // 96 
    q_t( 16975), q_t( 13793), q_t( 10636), q_t(  7504),  // 100 
    q_t(  4396), q_t(  1312), q_t( -1747), q_t( -4783),  // 104 
    q_t( -7795), q_t(-10783), q_t(-13748), q_t(-16690),  // 108 
    q_t(-19609), q_t(-22506), q_t(-25379), q_t(-28230),  // 112 
    q_t(-31059), q_t( 31670), q_t( 28885), q_t( 26122),  // 116 
    q_t( 23381), q_t( 20661), q_t( 17962), q_t( 15285),  // 120 
    q_t( 12628), q_t(  9992), q_t(  7377), q_t(  4782),  // 124 
    q_t(  2207), q_t(  -347), q_t( -2882), q_t( -5396),  // 128 
    q_t( -7891), q_t(-10367), q_t(-12823), q_t(-15260),  // 132 
    q_t(-17678), q_t(-20077), q_t(-22457), q_t(-24818),  // 136 
    q_t(-27161), q_t(-29486), q_t(-31792), q_t( 31455),  // 140 
    q_t( 29185), q_t( 26932), q_t( 24697), q_t( 22480),  // 144 
    q_t( 20279), q_t( 18096), q_t( 15931), q_t( 13782),  // 148 
    q_t( 11650), q_t(  9534), q_t(  7436), q_t(  5353),  // 152 
    q_t(  3287), q_t(  1238), q_t(  -796), q_t( -2814),  // 156 
    q_t( -4816), q_t( -6802), q_t( -8772), q_t(-10727),  // 160 
    q_t(-12667), q_t(-14592), q_t(-16501), q_t(-18396),  // 164 
    q_t(-20275), q_t(-22140), q_t(-23990), q_t(-25826),  // 168 
    q_t(-27647), q_t(-29454), q_t(-31247), q_t( 32511),  // 172 
    q_t( 30746), q_t( 28995), q_t( 27258), q_t( 25535),  // 176 
    q_t( 23825), q_t( 22129), q_t( 20446), q_t( 18776),  // 180 
    q_t( 17120), q_t( 15476), q_t( 13846), q_t( 12228),  // 184 
    q_t( 10623), q_t(  9031), q_t(  7451), q_t(  5884),  // 188 
    q_t(  4329), q_t(  2786), q_t(  1256), q_t(  -263),  // 192 
    q_t( -1769), q_t( -3264), q_t( -4747), q_t( -6218),  // 196 
    q_t( -7677), q_t( -9125), q_t(-10562), q_t(-11987),  // 200 
    q_t(-13400), q_t(-14803), q_t(-16195), q_t(-17575),  // 204 
    q_t(-18945), q_t(-20304), q_t(-21652), q_t(-22989),  // 208 
    q_t(-24316), q_t(-25632), q_t(-26938), q_t(-28233),  // 212 
    q_t(-29518), q_t(-30793), q_t(-32058), q_t( 32223),  // 216 
    q_t( 30978), q_t( 29743), q_t( 28518), q_t( 27303),  // 220 
    q_t( 26097), q_t( 24901), q_t( 23714), q_t( 22537),  // 224 
    q_t( 21369), q_t( 20211), q_t( 19062), q_t( 17922),  // 228 
    q_t( 16791), q_t( 15669), q_t( 14556), q_t( 13452),  // 232 
    q_t( 12356), q_t( 11270), q_t( 10192), q_t(  9123),  // 236 
    q_t(  8062), q_t(  7010), q_t(  5966), q_t(  4931),  // 240 
    q_t(  3904), q_t(  2885), q_t(  1874), q_t(   872),  // 244 
    q_t(  -123), q_t( -1109), q_t( -2088), q_t( -3059),  // 248 
    q_t( -4022), q_t( -4977), q_t( -5924), q_t( -6864),  // 252 
    q_t( -7796), q_t( -8721), q_t( -9638), q_t(-10548),  // 256 
    q_t(-11450), q_t(-12345), q_t(-13233), q_t(-14114),  // 260 
    q_t(-14988), q_t(-15854), q_t(-16714), q_t(-17566),  // 264 
    q_t(-18412), q_t(-19250), q_t(-20082), q_t(-20907),  // 268 
    q_t(-21726), q_t(-22537), q_t(-23342), q_t(-24141),  // 272 
    q_t(-24933), q_t(-25718), q_t(-26497), q_t(-27270),  // 276 
    q_t(-28036), q_t(-28796), q_t(-29550), q_t(-30298),  // 280 
    q_t(-31039), q_t(-31775), q_t(-32504), q_t( 32309),  // 284 
    q_t( 31592), q_t( 30880), q_t( 30175), q_t( 29475),  // 288 
    q_t( 28781), q_t( 28093), q_t( 27411), q_t( 26734),  // 292 
    q_t( 26063), q_t( 25398), q_t( 24738), q_t( 24083),  // 296 
    q_t( 23434), q_t( 22791), q_t( 22153), q_t( 21520),  // 300 
    q_t( 20892), q_t( 20270), q_t( 19653), q_t( 19042),  // 304 
    q_t( 18435), q_t( 17833), q_t( 17237), q_t( 16646),  // 308 
    q_t( 16059), q_t( 15478), q_t( 14902), q_t( 14330),  // 312 
    q_t( 13764), q_t( 13202), q_t( 12645), q_t( 12093),  // 316 
    q_t( 11545), q_t( 11003), q_t( 10465), q_t(  9931),  // 320 
    q_t(  9402), q_t(  8878), q_t(  8358), q_t(  7843),  // 324 
    q_t(  7333), q_t(  6826), q_t(  6324), q_t(  5827),  // 328 
    q_t(  5334), q_t(  4845), q_t(  4361), q_t(  3880),  // 332 
    q_t(  3404), q_t(  2933), q_t(  2465), q_t(  2002),  // 336 
    q_t(  1542), q_t(  1087), q_t(   636), q_t(   189),  // 340 
    q_t(  -254), q_t(  -693), q_t( -1129), q_t( -1560),  // 344 
    q_t( -1987), q_t( -2411), q_t( -2830), q_t( -3246),  // 348 
    q_t( -3658), q_t( -4066), q_t( -4471), q_t( -4871),  // 352 
    q_t( -5268), q_t( -5662), q_t( -6051), q_t( -6437),  // 356 
    q_t( -6820), q_t( -7199), q_t( -7574), q_t( -7946),  // 360 
    q_t( -8314), q_t( -8679), q_t( -9040), q_t( -9398),  // 364 
    q_t( -9752), q_t(-10103), q_t(-10451), q_t(-10795),  // 368 
    q_t(-11136), q_t(-11474), q_t(-11808), q_t(-12139),  // 372 
    q_t(-12467), q_t(-12791), q_t(-13113), q_t(-13431),  // 376 
    q_t(-13746), q_t(-14057), q_t(-14366), q_t(-14671),  // 380 
    q_t(-14974), q_t(-15273), q_t(-15569), q_t(-15863),  // 384 
    q_t(-16153), q_t(-16440), q_t(-16724), q_t(-17005),  // 388 
    q_t(-17283), q_t(-17559), q_t(-17831), q_t(-18100),  // 392 
    q_t(-18367), q_t(-18631), q_t(-18891), q_t(-19149),  // 396 
    q_t(-19404), q_t(-19657), q_t(-19906), q_t(-20153),  // 400 
    q_t(-20397), q_t(-20638), q_t(-20876), q_t(-21112),  // 404 
    q_t(-21345), q_t(-21575), q_t(-21803), q_t(-22028),  // 408 
    q_t(-22250), q_t(-22470), q_t(-22687), q_t(-22901),  // 412 
    q_t(-23113), q_t(-23322), q_t(-23529), q_t(-23733),  // 416 
    q_t(-23935), q_t(-24134), q_t(-24330), q_t(-24524),  // 420 
    q_t(-24715), q_t(-24904), q_t(-25091), q_t(-25275),  // 424 
    q_t(-25456), q_t(-25635), q_t(-25812), q_t(-25986),  // 428 
    q_t(-26158), q_t(-26328), q_t(-26495), q_t(-26659),  // 432 
    q_t(-26821), q_t(-26981), q_t(-27139), q_t(-27294),  // 436 
    q_t(-27447), q_t(-27598), q_t(-27746), q_t(-27892),  // 440 
    q_t(-28035), q_t(-28177), q_t(-28316), q_t(-28453),  // 444 
    q_t(-28587), q_t(-28719), q_t(-28849), q_t(-28977),  // 448 
    q_t(-29103), q_t(-29226), q_t(-29347), q_t(-29466),  // 452 
    q_t(-29583), q_t(-29697), q_t(-29810), q_t(-29920),  // 456 
    q_t(-30028), q_t(-30133), q_t(-30237), q_t(-30339),  // 460 
    q_t(-30438), q_t(-30535), q_t(-30630), q_t(-30723),  // 464 
    q_t(-30814), q_t(-30903), q_t(-30989), q_t(-31074),  // 468 
    q_t(-31156), q_t(-31236), q_t(-31314), q_t(-31390),  // 472 
    q_t(-31464), q_t(-31536), q_t(-31606), q_t(-31674),  // 476 
    q_t(-31740), q_t(-31803), q_t(-31865), q_t(-31924),  // 480 
    q_t(-31982), q_t(-32037), q_t(-32091), q_t(-32142),  // 484 
    q_t(-32191), q_t(-32239), q_t(-32284), q_t(-32327),  // 488 
    q_t(-32368), q_t(-32407), q_t(-32444), q_t(-32480),  // 492 
    q_t(-32513), q_t(-32544), q_t(-32573), q_t(-32600),  // 496 
    q_t(-32625), q_t(-32648), q_t(-32669), q_t(-32688),  // 500 
    q_t(-32705), q_t(-32720), q_t(-32733), q_t(-32744),  // 504 
    q_t(-32753), q_t(-32760), q_t(-32765), q_t(-32768),  // 508 
    q_t( 32767), q_t(-32768), q_t(-32765), q_t(-32760),  // 512 
    q_t(-32753), q_t(-32744), q_t(-32733), q_t(-32720),  // 516 
    q_t(-32705), q_t(-32688), q_t(-32669), q_t(-32648),  // 520 
    q_t(-32625), q_t(-32600), q_t(-32573), q_t(-32544),  // 524 
    q_t(-32513), q_t(-32480), q_t(-32444), q_t(-32407),  // 528 
    q_t(-32368), q_t(-32327), q_t(-32284), q_t(-32239),  // 532 
    q_t(-32191), q_t(-32142), q_t(-32091), q_t(-32037),  // 536 
    q_t(-31982), q_t(-31924), q_t(-31865), q_t(-31803),  // 540 
    q_t(-31740), q_t(-31674), q_t(-31606), q_t(-31536),  // 544 
    q_t(-31464), q_t(-31390), q_t(-31314), q_t(-31236),  // 548 
    q_t(-31156), q_t(-31074), q_t(-30989), q_t(-30903),  // 552 
    q_t(-30814), q_t(-30723), q_t(-30630), q_t(-30535),  // 556 
    q_t(-30438), q_t(-30339), q_t(-30237), q_t(-30133),  // 560 
    q_t(-30028), q_t(-29920), q_t(-29810), q_t(-29697),  // 564 
    q_t(-29583), q_t(-29466), q_t(-29347), q_t(-29226),  // 568 
    q_t(-29103), q_t(-28977), q_t(-28849), q_t(-28719),  // 572 
    q_t(-28587), q_t(-28453), q_t(-28316), q_t(-28177),  // 576 
    q_t(-28035), q_t(-27892), q_t(-27746), q_t(-27598),  // 580 
    q_t(-27447), q_t(-27294), q_t(-27139), q_t(-26981),  // 584 
    q_t(-26821), q_t(-26659), q_t(-26495), q_t(-26328),  // 588 
    q_t(-26158), q_t(-25986), q_t(-25812), q_t(-25635),  // 592 
    q_t(-25456), q_t(-25275), q_t(-25091), q_t(-24904),  // 596 
    q_t(-24715), q_t(-24524), q_t(-24330), q_t(-24134),  // 600 
    q_t(-23935), q_t(-23733), q_t(-23529), q_t(-23322),  // 604 
    q_t(-23113), q_t(-22901), q_t(-22687), q_t(-22470),  // 608 
    q_t(-22250), q_t(-22028), q_t(-21803), q_t(-21575),  // 612 
    q_t(-21345), q_t(-21112), q_t(-20876), q_t(-20638),  // 616 
    q_t(-20397), q_t(-20153), q_t(-19906), q_t(-19657),  // 620 
    q_t(-19404), q_t(-19149), q_t(-18891), q_t(-18631),  // 624 
    q_t(-18367), q_t(-18100), q_t(-17831), q_t(-17559),  // 628 
    q_t(-17283), q_t(-17005), q_t(-16724), q_t(-16440),  // 632 
    q_t(-16153), q_t(-15863), q_t(-15569), q_t(-15273),  // 636 
    q_t(-14974), q_t(-14671), q_t(-14366), q_t(-14057),  // 640 
    q_t(-13746), q_t(-13431), q_t(-13113), q_t(-12791),  // 644 
    q_t(-12467), q_t(-12139), q_t(-11808), q_t(-11474),  // 648 
    q_t(-11136), q_t(-10795), q_t(-10451), q_t(-10103),  // 652 
    q_t( -9752), q_t( -9398), q_t( -9040), q_t( -8679),  // 656 
    q_t( -8314), q_t( -7946), q_t( -7574), q_t( -7199),  // 660 
    q_t( -6820), q_t( -6437), q_t( -6051), q_t( -5662),  // 664 
    q_t( -5268), q_t( -4871), q_t( -4471), q_t( -4066),  // 668 
    q_t( -3658), q_t( -3246), q_t( -2830), q_t( -2411),  // 672 
    q_t( -1987), q_t( -1560), q_t( -1129), q_t(  -693),  // 676 
    q_t(  -254), q_t(   189), q_t(   636), q_t(  1087),  // 680 
    q_t(  1542), q_t(  2002), q_t(  2465), q_t(  2933),  // 684 
    q_t(  3404), q_t(  3880), q_t(  4361), q_t(  4845),  // 688 
    q_t(  5334), q_t(  5827), q_t(  6324), q_t(  6826),  // 692 
    q_t(  7333), q_t(  7843), q_t(  8358), q_t(  8878),  // 696 
    q_t(  9402), q_t(  9931), q_t( 10465), q_t( 11003),  // 700 
    q_t( 11545), q_t( 12093), q_t( 12645), q_t( 13202),  // 704 
    q_t( 13764), q_t( 14330), q_t( 14902), q_t( 15478),  // 708 
    q_t( 16059), q_t( 16646), q_t( 17237), q_t( 17833),  // 712 
    q_t( 18435), q_t( 19042), q_t( 19653), q_t( 20270),  // 716 
    q_t( 20892), q_t( 21520), q_t( 22153), q_t( 22791),  // 720 
    q_t( 23434), q_t( 24083), q_t( 24738), q_t( 25398),  // 724 
    q_t( 26063), q_t( 26734), q_t( 27411), q_t( 28093),  // 728 
    q_t( 28781), q_t( 29475), q_t( 30175), q_t( 30880),  // 732 
    q_t( 31592), q_t( 32309), q_t(-32504), q_t(-31775),  // 736 
    q_t(-31039), q_t(-30298), q_t(-29550), q_t(-28796),  // 740 
    q_t(-28036), q_t(-27270), q_t(-26497), q_t(-25718),  // 744 
    q_t(-24933), q_t(-24141), q_t(-23342), q_t(-22537),  // 748 
    q_t(-21726), q_t(-20907), q_t(-20082), q_t(-19250),  // 752 
    q_t(-18412), q_t(-17566), q_t(-16714), q_t(-15854),  // 756 
    q_t(-14988), q_t(-14114), q_t(-13233), q_t(-12345),  // 760 
    q_t(-11450), q_t(-10548), q_t( -9638), q_t( -8721),  // 764 
    q_t( -7796), q_t( -6864), q_t( -5924), q_t( -4977),  // 768 
    q_t( -4022), q_t( -3059), q_t( -2088), q_t( -1109),  // 772 
    q_t(  -123), q_t(   872), q_t(  1874), q_t(  2885),  // 776 
    q_t(  3904), q_t(  4931), q_t(  5966), q_t(  7010),  // 780 
    q_t(  8062), q_t(  9123), q_t( 10192), q_t( 11270),  // 784 
    q_t( 12356), q_t( 13452), q_t( 14556), q_t( 15669),  // 788 
    q_t( 16791), q_t( 17922), q_t( 19062), q_t( 20211),  // 792 
    q_t( 21369), q_t( 22537), q_t( 23714), q_t( 24901),  // 796 
    q_t( 26097), q_t( 27303), q_t( 28518), q_t( 29743),  // 800 
    q_t( 30978), q_t( 32223), q_t(-32058), q_t(-30793),  // 804 
    q_t(-29518), q_t(-28233), q_t(-26938), q_t(-25632),  // 808 
    q_t(-24316), q_t(-22989), q_t(-21652), q_t(-20304),  // 812 
    q_t(-18945), q_t(-17575), q_t(-16195), q_t(-14803),  // 816 
    q_t(-13400), q_t(-11987), q_t(-10562), q_t( -9125),  // 820 
    q_t( -7677), q_t( -6218), q_t( -4747), q_t( -3264),  // 824 
    q_t( -1769), q_t(  -263), q_t(  1256), q_t(  2786),  // 828 
    q_t(  4329), q_t(  5884), q_t(  7451), q_t(  9031),  // 832 
    q_t( 10623), q_t( 12228), q_t( 13846), q_t( 15476),  // 836 
    q_t( 17120), q_t( 18776), q_t( 20446), q_t( 22129),  // 840 
    q_t( 23825), q_t( 25535), q_t( 27258), q_t( 28995),  // 844 
    q_t( 30746), q_t( 32511), q_t(-31247), q_t(-29454),  // 848 
    q_t(-27647), q_t(-25826), q_t(-23990), q_t(-22140),  // 852 
    q_t(-20275), q_t(-18396), q_t(-16501), q_t(-14592),  // 856 
    q_t(-12667), q_t(-10727), q_t( -8772), q_t( -6802),  // 860 
    q_t( -4816), q_t( -2814), q_t(  -796), q_t(  1238),  // 864 
    q_t(  3287), q_t(  5353), q_t(  7436), q_t(  9534),  // 868 
    q_t( 11650), q_t( 13782), q_t( 15931), q_t( 18096),  // 872 
    q_t( 20279), q_t( 22480), q_t( 24697), q_t( 26932),  // 876 
    q_t( 29185), q_t( 31455), q_t(-31792), q_t(-29486),  // 880 
    q_t(-27161), q_t(-24818), q_t(-22457), q_t(-20077),  // 884 
    q_t(-17678), q_t(-15260), q_t(-12823), q_t(-10367),  // 888 
    q_t( -7891), q_t( -5396), q_t( -2882), q_t(  -347),  // 892 
    q_t(  2207), q_t(  4782), q_t(  7377), q_t(  9992),  // 896 
    q_t( 12628), q_t( 15285), q_t( 17962), q_t( 20661),  // 900 
    q_t( 23381), q_t( 26122), q_t( 28885), q_t( 31670),  // 904 
    q_t(-31059), q_t(-28230), q_t(-25379), q_t(-22506),  // 908 
    q_t(-19609), q_t(-16690), q_t(-13748), q_t(-10783),  // 912 
    q_t( -7795), q_t( -4783), q_t( -1747), q_t(  1312),  // 916 
    q_t(  4396), q_t(  7504), q_t( 10636), q_t( 13793),  // 920 
    q_t( 16975), q_t( 20182), q_t( 23414), q_t( 26672),  // 924 
    q_t( 29955), q_t(-32272), q_t(-28937), q_t(-25575),  // 928 
    q_t(-22188), q_t(-18773), q_t(-15332), q_t(-11864),  // 932 
    q_t( -8368), q_t( -4845), q_t( -1294), q_t(  2285),  // 936 
    q_t(  5891), q_t(  9527), q_t( 13190), q_t( 16883),  // 940 
    q_t( 20605), q_t( 24356), q_t( 28136), q_t( 31946),  // 944 
    q_t(-29750), q_t(-25880), q_t(-21979), q_t(-18048),  // 948 
    q_t(-14086), q_t(-10092), q_t( -6068), q_t( -2011),  // 952 
    q_t(  2077), q_t(  6197), q_t( 10350), q_t( 14535),  // 956 
    q_t( 18754), q_t( 23005), q_t( 27290), q_t( 31608),  // 960 
    q_t(-29575), q_t(-25189), q_t(-20768), q_t(-16312),  // 964 
    q_t(-11821), q_t( -7295), q_t( -2733), q_t(  1864),  // 968 
    q_t(  6498), q_t( 11168), q_t( 15874), q_t( 20618),  // 972 
    q_t( 25399), q_t( 30217), q_t(-30462), q_t(-25568),  // 976 
    q_t(-20635), q_t(-15664), q_t(-10653), q_t( -5603),  // 980 
    q_t(  -513), q_t(  4616), q_t(  9786), q_t( 14997),  // 984 
    q_t( 20248), q_t( 25541), q_t( 30875), q_t(-29285),  // 988 
    q_t(-23867), q_t(-18406), q_t(-12902), q_t( -7355),  // 992 
    q_t( -1765), q_t(  3870), q_t(  9548), q_t( 15272),  // 996 
    q_t( 21040), q_t( 26853), q_t( 32712), q_t(-26919),  // 1000 
    q_t(-20967), q_t(-14969), q_t( -8924), q_t( -2831),  // 1004 
    q_t(  3309), q_t(  9498), q_t( 15735), q_t( 22022),  // 1008 
    q_t( 28357), q_t(-30794), q_t(-24358), q_t(-17872),  // 1012 
    q_t(-11335), q_t( -4747), q_t(  1893), q_t(  8585),  // 1016 
    q_t( 15329), q_t( 22127), q_t( 28977), q_t(-29654),  // 1020 
    }; 
  } 
 } 
} 

#endif