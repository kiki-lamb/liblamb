#ifndef KL_1024_s0q15_tan_h 
#define KL_1024_s0q15_tan_h 

#define KL_1024_s0q15_tan_h_cells 

namespace lamb {
 namespace tables {
  namespace tan1024_s0q15 {
   typedef s0q15 q_t; 
   const size_t length = 1024; 
   const q_t  data[] 
#ifdef __AVR__ 
   PROGMEM 
#endif 
   = { 
    q_t( 27599), q_t( 28192), q_t( 28776), q_t( 29349),  // 0 
    q_t( 29912), q_t( 30466), q_t( 31011), q_t( 31547),  // 4 
    q_t( 32074), q_t( 32593), q_t(-32432), q_t(-31930),  // 8 
    q_t(-31434), q_t(-30946), q_t(-30465), q_t(-29992),  // 12 
    q_t(-29524), q_t(-29064), q_t(-28610), q_t(-28161),  // 16 
    q_t(-27719), q_t(-27283), q_t(-26852), q_t(-26427),  // 20 
    q_t(-26007), q_t(-25593), q_t(-25183), q_t(-24778),  // 24 
    q_t(-24378), q_t(-23983), q_t(-23592), q_t(-23205),  // 28 
    q_t(-22823), q_t(-22445), q_t(-22071), q_t(-21700),  // 32 
    q_t(-21334), q_t(-20971), q_t(-20612), q_t(-20257),  // 36 
    q_t(-19905), q_t(-19556), q_t(-19210), q_t(-18868),  // 40 
    q_t(-18528), q_t(-18192), q_t(-17859), q_t(-17528),  // 44 
    q_t(-17200), q_t(-16875), q_t(-16552), q_t(-16232),  // 48 
    q_t(-15915), q_t(-15599), q_t(-15286), q_t(-14976),  // 52 
    q_t(-14668), q_t(-14361), q_t(-14057), q_t(-13755),  // 56 
    q_t(-13455), q_t(-13157), q_t(-12860), q_t(-12566),  // 60 
    q_t(-12273), q_t(-11982), q_t(-11693), q_t(-11405),  // 64 
    q_t(-11119), q_t(-10834), q_t(-10551), q_t(-10269),  // 68 
    q_t( -9988), q_t( -9709), q_t( -9431), q_t( -9155),  // 72 
    q_t( -8879), q_t( -8605), q_t( -8332), q_t( -8060),  // 76 
    q_t( -7789), q_t( -7519), q_t( -7250), q_t( -6982),  // 80 
    q_t( -6715), q_t( -6449), q_t( -6183), q_t( -5918),  // 84 
    q_t( -5654), q_t( -5391), q_t( -5128), q_t( -4866),  // 88 
    q_t( -4605), q_t( -4344), q_t( -4084), q_t( -3824),  // 92 
    q_t( -3565), q_t( -3306), q_t( -3048), q_t( -2790),  // 96 
    q_t( -2532), q_t( -2275), q_t( -2018), q_t( -1761),  // 100 
    q_t( -1504), q_t( -1248), q_t(  -992), q_t(  -735),  // 104 
    q_t(  -479), q_t(  -223), q_t(    32), q_t(   288),  // 108 
    q_t(   544), q_t(   800), q_t(  1056), q_t(  1312),  // 112 
    q_t(  1569), q_t(  1826), q_t(  2082), q_t(  2340),  // 116 
    q_t(  2597), q_t(  2855), q_t(  3113), q_t(  3371),  // 120 
    q_t(  3630), q_t(  3890), q_t(  4150), q_t(  4410),  // 124 
    q_t(  4671), q_t(  4932), q_t(  5194), q_t(  5457),  // 128 
    q_t(  5721), q_t(  5985), q_t(  6250), q_t(  6515),  // 132 
    q_t(  6782), q_t(  7049), q_t(  7318), q_t(  7587),  // 136 
    q_t(  7857), q_t(  8128), q_t(  8401), q_t(  8674),  // 140 
    q_t(  8948), q_t(  9224), q_t(  9501), q_t(  9779),  // 144 
    q_t( 10059), q_t( 10339), q_t( 10622), q_t( 10905),  // 148 
    q_t( 11190), q_t( 11477), q_t( 11765), q_t( 12055),  // 152 
    q_t( 12346), q_t( 12640), q_t( 12935), q_t( 13231),  // 156 
    q_t( 13530), q_t( 13831), q_t( 14133), q_t( 14438),  // 160 
    q_t( 14745), q_t( 15054), q_t( 15365), q_t( 15678),  // 164 
    q_t( 15994), q_t( 16312), q_t( 16633), q_t( 16956),  // 168 
    q_t( 17282), q_t( 17611), q_t( 17942), q_t( 18276),  // 172 
    q_t( 18613), q_t( 18953), q_t( 19296), q_t( 19643),  // 176 
    q_t( 19992), q_t( 20345), q_t( 20702), q_t( 21062),  // 180 
    q_t( 21425), q_t( 21793), q_t( 22164), q_t( 22539),  // 184 
    q_t( 22918), q_t( 23302), q_t( 23689), q_t( 24081),  // 188 
    q_t( 24478), q_t( 24879), q_t( 25285), q_t( 25696),  // 192 
    q_t( 26112), q_t( 26533), q_t( 26959), q_t( 27392),  // 196 
    q_t( 27829), q_t( 28273), q_t( 28723), q_t( 29178),  // 200 
    q_t( 29641), q_t( 30109), q_t( 30585), q_t( 31067),  // 204 
    q_t( 31557), q_t( 32054), q_t( 32559), q_t(-32464),  // 208 
    q_t(-31943), q_t(-31414), q_t(-30876), q_t(-30329),  // 212 
    q_t(-29773), q_t(-29207), q_t(-28631), q_t(-28045),  // 216 
    q_t(-27449), q_t(-26842), q_t(-26223), q_t(-25592),  // 220 
    q_t(-24950), q_t(-24295), q_t(-23627), q_t(-22945),  // 224 
    q_t(-22250), q_t(-21539), q_t(-20814), q_t(-20074),  // 228 
    q_t(-19317), q_t(-18543), q_t(-17751), q_t(-16942),  // 232 
    q_t(-16113), q_t(-15265), q_t(-14396), q_t(-13505),  // 236 
    q_t(-12592), q_t(-11656), q_t(-10696), q_t( -9710),  // 240 
    q_t( -8697), q_t( -7657), q_t( -6587), q_t( -5487),  // 244 
    q_t( -4355), q_t( -3190), q_t( -1989), q_t(  -752),  // 248 
    q_t(   525), q_t(  1842), q_t(  3202), q_t(  4608),  // 252 
    q_t(  6061), q_t(  7565), q_t(  9122), q_t( 10736),  // 256 
    q_t( 12410), q_t( 14146), q_t( 15951), q_t( 17826),  // 260 
    q_t( 19778), q_t( 21811), q_t( 23930), q_t( 26141),  // 264 
    q_t( 28452), q_t( 30868), q_t(-32138), q_t(-29485),  // 268 
    q_t(-26701), q_t(-23775), q_t(-20695), q_t(-17449),  // 272 
    q_t(-14022), q_t(-10398), q_t( -6560), q_t( -2487),  // 276 
    q_t(  1845), q_t(  6459), q_t( 11387), q_t( 16660),  // 280 
    q_t( 22320), q_t( 28408), q_t(-30558), q_t(-23446),  // 284 
    q_t(-15722), q_t( -7301), q_t(  1916), q_t( 12048),  // 288 
    q_t( 23242), q_t(-29862), q_t(-15973), q_t(  -351),  // 292 
    q_t( 17351), q_t(-27955), q_t( -4612), q_t( 22629),  // 296 
    q_t(-10702), q_t( 27967), q_t(  9734), q_t(  3397),  // 300 
    q_t( 14100), q_t(-15083), q_t( -3034), q_t( 16121),  // 304 
    q_t(-14515), q_t(  1246), q_t( 14541), q_t(-25956),  // 308 
    q_t(-17328), q_t( -2309), q_t(  6736), q_t( 16366),  // 312 
    q_t( 23828), q_t( 29526), q_t( -3486), q_t(  4732),  // 316 
    q_t( -3308), q_t(-22760), q_t( 15007), q_t(-19009),  // 320 
    q_t(  7697), q_t( 30617), q_t(-15031), q_t(  2392),  // 324 
    q_t( 17782), q_t( 31477), q_t(-21791), q_t(-10738),  // 328 
    q_t(  -726), q_t(  8386), q_t( 16715), q_t( 24360),  // 332 
    q_t( 31401), q_t(-27628), q_t(-21595), q_t(-15986),  // 336 
    q_t(-10757), q_t( -5870), q_t( -1292), q_t(  3006),  // 340 
    q_t(  7049), q_t( 10860), q_t( 14458), q_t( 17862),  // 344 
    q_t( 21087), q_t( 24147), q_t( 27055), q_t( 29822),  // 348 
    q_t( 32458), q_t(-30562), q_t(-28159), q_t(-25861),  // 352 
    q_t(-23662), q_t(-21553), q_t(-19531), q_t(-17589),  // 356 
    q_t(-15722), q_t(-13927), q_t(-12198), q_t(-10532),  // 360 
    q_t( -8925), q_t( -7375), q_t( -5878), q_t( -4430),  // 364 
    q_t( -3030), q_t( -1675), q_t(  -363), q_t(   908),  // 368 
    q_t(  2141), q_t(  3337), q_t(  4498), q_t(  5626),  // 372 
    q_t(  6722), q_t(  7788), q_t(  8825), q_t(  9834),  // 376 
    q_t( 10817), q_t( 11775), q_t( 12708), q_t( 13618),  // 380 
    q_t( 14505), q_t( 15372), q_t( 16218), q_t( 17044),  // 384 
    q_t( 17851), q_t( 18640), q_t( 19412), q_t( 20167),  // 388 
    q_t( 20906), q_t( 21629), q_t( 22337), q_t( 23031),  // 392 
    q_t( 23711), q_t( 24378), q_t( 25031), q_t( 25672),  // 396 
    q_t( 26301), q_t( 26918), q_t( 27524), q_t( 28120),  // 400 
    q_t( 28704), q_t( 29279), q_t( 29843), q_t( 30398),  // 404 
    q_t( 30944), q_t( 31481), q_t( 32009), q_t( 32529),  // 408 
    q_t(-32495), q_t(-31991), q_t(-31495), q_t(-31006),  // 412 
    q_t(-30525), q_t(-30050), q_t(-29582), q_t(-29121),  // 416 
    q_t(-28665), q_t(-28217), q_t(-27774), q_t(-27337),  // 420 
    q_t(-26905), q_t(-26479), q_t(-26059), q_t(-25644),  // 424 
    q_t(-25233), q_t(-24828), q_t(-24427), q_t(-24031),  // 428 
    q_t(-23640), q_t(-23253), q_t(-22870), q_t(-22491),  // 432 
    q_t(-22117), q_t(-21746), q_t(-21379), q_t(-21016),  // 436 
    q_t(-20657), q_t(-20301), q_t(-19948), q_t(-19599),  // 440 
    q_t(-19253), q_t(-18910), q_t(-18570), q_t(-18234),  // 444 
    q_t(-17900), q_t(-17569), q_t(-17240), q_t(-16915),  // 448 
    q_t(-16592), q_t(-16272), q_t(-15954), q_t(-15638),  // 452 
    q_t(-15325), q_t(-15014), q_t(-14706), q_t(-14399),  // 456 
    q_t(-14095), q_t(-13792), q_t(-13492), q_t(-13194),  // 460 
    q_t(-12897), q_t(-12602), q_t(-12309), q_t(-12018),  // 464 
    q_t(-11728), q_t(-11440), q_t(-11154), q_t(-10869),  // 468 
    q_t(-10586), q_t(-10304), q_t(-10023), q_t( -9744),  // 472 
    q_t( -9466), q_t( -9189), q_t( -8913), q_t( -8639),  // 476 
    q_t( -8366), q_t( -8094), q_t( -7823), q_t( -7552),  // 480 
    q_t( -7283), q_t( -7015), q_t( -6748), q_t( -6481),  // 484 
    q_t( -6216), q_t( -5951), q_t( -5687), q_t( -5424),  // 488 
    q_t( -5161), q_t( -4899), q_t( -4637), q_t( -4377),  // 492 
    q_t( -4116), q_t( -3857), q_t( -3597), q_t( -3338),  // 496 
    q_t( -3080), q_t( -2822), q_t( -2564), q_t( -2307),  // 500 
    q_t( -2050), q_t( -1793), q_t( -1536), q_t( -1280),  // 504 
    q_t( -1023), q_t(  -767), q_t(  -511), q_t(  -255),  // 508 
    q_t(     0), q_t(   256), q_t(   512), q_t(   768),  // 512 
    q_t(  1024), q_t(  1281), q_t(  1537), q_t(  1794),  // 516 
    q_t(  2051), q_t(  2308), q_t(  2565), q_t(  2823),  // 520 
    q_t(  3081), q_t(  3339), q_t(  3598), q_t(  3858),  // 524 
    q_t(  4117), q_t(  4378), q_t(  4638), q_t(  4900),  // 528 
    q_t(  5162), q_t(  5425), q_t(  5688), q_t(  5952),  // 532 
    q_t(  6217), q_t(  6482), q_t(  6749), q_t(  7016),  // 536 
    q_t(  7284), q_t(  7553), q_t(  7824), q_t(  8095),  // 540 
    q_t(  8367), q_t(  8640), q_t(  8914), q_t(  9190),  // 544 
    q_t(  9467), q_t(  9745), q_t( 10024), q_t( 10305),  // 548 
    q_t( 10587), q_t( 10870), q_t( 11155), q_t( 11441),  // 552 
    q_t( 11729), q_t( 12019), q_t( 12310), q_t( 12603),  // 556 
    q_t( 12898), q_t( 13195), q_t( 13493), q_t( 13793),  // 560 
    q_t( 14096), q_t( 14400), q_t( 14707), q_t( 15015),  // 564 
    q_t( 15326), q_t( 15639), q_t( 15955), q_t( 16273),  // 568 
    q_t( 16593), q_t( 16916), q_t( 17241), q_t( 17570),  // 572 
    q_t( 17901), q_t( 18235), q_t( 18571), q_t( 18911),  // 576 
    q_t( 19254), q_t( 19600), q_t( 19949), q_t( 20302),  // 580 
    q_t( 20658), q_t( 21017), q_t( 21380), q_t( 21747),  // 584 
    q_t( 22118), q_t( 22492), q_t( 22871), q_t( 23254),  // 588 
    q_t( 23641), q_t( 24032), q_t( 24428), q_t( 24829),  // 592 
    q_t( 25234), q_t( 25645), q_t( 26060), q_t( 26480),  // 596 
    q_t( 26906), q_t( 27338), q_t( 27775), q_t( 28218),  // 600 
    q_t( 28666), q_t( 29122), q_t( 29583), q_t( 30051),  // 604 
    q_t( 30526), q_t( 31007), q_t( 31496), q_t( 31992),  // 608 
    q_t( 32496), q_t(-32528), q_t(-32008), q_t(-31480),  // 612 
    q_t(-30943), q_t(-30397), q_t(-29842), q_t(-29278),  // 616 
    q_t(-28703), q_t(-28119), q_t(-27523), q_t(-26917),  // 620 
    q_t(-26300), q_t(-25671), q_t(-25030), q_t(-24377),  // 624 
    q_t(-23710), q_t(-23030), q_t(-22336), q_t(-21628),  // 628 
    q_t(-20905), q_t(-20166), q_t(-19411), q_t(-18639),  // 632 
    q_t(-17850), q_t(-17043), q_t(-16217), q_t(-15371),  // 636 
    q_t(-14504), q_t(-13617), q_t(-12707), q_t(-11774),  // 640 
    q_t(-10816), q_t( -9833), q_t( -8824), q_t( -7787),  // 644 
    q_t( -6721), q_t( -5625), q_t( -4497), q_t( -3336),  // 648 
    q_t( -2140), q_t(  -907), q_t(   364), q_t(  1676),  // 652 
    q_t(  3031), q_t(  4431), q_t(  5879), q_t(  7376),  // 656 
    q_t(  8926), q_t( 10533), q_t( 12199), q_t( 13928),  // 660 
    q_t( 15723), q_t( 17590), q_t( 19532), q_t( 21554),  // 664 
    q_t( 23663), q_t( 25862), q_t( 28160), q_t( 30563),  // 668 
    q_t(-32457), q_t(-29821), q_t(-27054), q_t(-24146),  // 672 
    q_t(-21086), q_t(-17861), q_t(-14457), q_t(-10859),  // 676 
    q_t( -7048), q_t( -3005), q_t(  1293), q_t(  5871),  // 680 
    q_t( 10758), q_t( 15987), q_t( 21596), q_t( 27629),  // 684 
    q_t(-31400), q_t(-24359), q_t(-16714), q_t( -8385),  // 688 
    q_t(   727), q_t( 10739), q_t( 21792), q_t(-31476),  // 692 
    q_t(-17781), q_t( -2391), q_t( 15032), q_t(-30616),  // 696 
    q_t( -7696), q_t( 19010), q_t(-15006), q_t( 22761),  // 700 
    q_t(  3309), q_t( -4731), q_t(  3487), q_t(-29525),  // 704 
    q_t(-23827), q_t(-16365), q_t( -6735), q_t(  2310),  // 708 
    q_t( 17329), q_t( 25957), q_t(-14540), q_t( -1245),  // 712 
    q_t( 14516), q_t(-16120), q_t(  3035), q_t( 15084),  // 716 
    q_t(-14099), q_t( -3396), q_t( -9733), q_t(-27966),  // 720 
    q_t( 10703), q_t(-22628), q_t(  4613), q_t( 27956),  // 724 
    q_t(-17350), q_t(   352), q_t( 15974), q_t( 29863),  // 728 
    q_t(-23241), q_t(-12047), q_t( -1915), q_t(  7302),  // 732 
    q_t( 15723), q_t( 23447), q_t( 30559), q_t(-28407),  // 736 
    q_t(-22319), q_t(-16659), q_t(-11386), q_t( -6458),  // 740 
    q_t( -1844), q_t(  2488), q_t(  6561), q_t( 10399),  // 744 
    q_t( 14023), q_t( 17450), q_t( 20696), q_t( 23776),  // 748 
    q_t( 26702), q_t( 29486), q_t( 32139), q_t(-30867),  // 752 
    q_t(-28451), q_t(-26140), q_t(-23929), q_t(-21810),  // 756 
    q_t(-19777), q_t(-17825), q_t(-15950), q_t(-14145),  // 760 
    q_t(-12409), q_t(-10735), q_t( -9121), q_t( -7564),  // 764 
    q_t( -6060), q_t( -4607), q_t( -3201), q_t( -1841),  // 768 
    q_t(  -524), q_t(   753), q_t(  1990), q_t(  3191),  // 772 
    q_t(  4356), q_t(  5488), q_t(  6588), q_t(  7658),  // 776 
    q_t(  8698), q_t(  9711), q_t( 10697), q_t( 11657),  // 780 
    q_t( 12593), q_t( 13506), q_t( 14397), q_t( 15266),  // 784 
    q_t( 16114), q_t( 16943), q_t( 17752), q_t( 18544),  // 788 
    q_t( 19318), q_t( 20075), q_t( 20815), q_t( 21540),  // 792 
    q_t( 22251), q_t( 22946), q_t( 23628), q_t( 24296),  // 796 
    q_t( 24951), q_t( 25593), q_t( 26224), q_t( 26843),  // 800 
    q_t( 27450), q_t( 28046), q_t( 28632), q_t( 29208),  // 804 
    q_t( 29774), q_t( 30330), q_t( 30877), q_t( 31415),  // 808 
    q_t( 31944), q_t( 32465), q_t(-32558), q_t(-32053),  // 812 
    q_t(-31556), q_t(-31066), q_t(-30584), q_t(-30108),  // 816 
    q_t(-29640), q_t(-29177), q_t(-28722), q_t(-28272),  // 820 
    q_t(-27828), q_t(-27391), q_t(-26958), q_t(-26532),  // 824 
    q_t(-26111), q_t(-25695), q_t(-25284), q_t(-24878),  // 828 
    q_t(-24477), q_t(-24080), q_t(-23688), q_t(-23301),  // 832 
    q_t(-22917), q_t(-22538), q_t(-22163), q_t(-21792),  // 836 
    q_t(-21424), q_t(-21061), q_t(-20701), q_t(-20344),  // 840 
    q_t(-19991), q_t(-19642), q_t(-19295), q_t(-18952),  // 844 
    q_t(-18612), q_t(-18275), q_t(-17941), q_t(-17610),  // 848 
    q_t(-17281), q_t(-16955), q_t(-16632), q_t(-16311),  // 852 
    q_t(-15993), q_t(-15677), q_t(-15364), q_t(-15053),  // 856 
    q_t(-14744), q_t(-14437), q_t(-14132), q_t(-13830),  // 860 
    q_t(-13529), q_t(-13230), q_t(-12934), q_t(-12639),  // 864 
    q_t(-12345), q_t(-12054), q_t(-11764), q_t(-11476),  // 868 
    q_t(-11189), q_t(-10904), q_t(-10621), q_t(-10338),  // 872 
    q_t(-10058), q_t( -9778), q_t( -9500), q_t( -9223),  // 876 
    q_t( -8947), q_t( -8673), q_t( -8400), q_t( -8127),  // 880 
    q_t( -7856), q_t( -7586), q_t( -7317), q_t( -7048),  // 884 
    q_t( -6781), q_t( -6514), q_t( -6249), q_t( -5984),  // 888 
    q_t( -5720), q_t( -5456), q_t( -5193), q_t( -4931),  // 892 
    q_t( -4670), q_t( -4409), q_t( -4149), q_t( -3889),  // 896 
    q_t( -3629), q_t( -3370), q_t( -3112), q_t( -2854),  // 900 
    q_t( -2596), q_t( -2339), q_t( -2081), q_t( -1825),  // 904 
    q_t( -1568), q_t( -1311), q_t( -1055), q_t(  -799),  // 908 
    q_t(  -543), q_t(  -287), q_t(   -31), q_t(   224),  // 912 
    q_t(   480), q_t(   736), q_t(   993), q_t(  1249),  // 916 
    q_t(  1505), q_t(  1762), q_t(  2019), q_t(  2276),  // 920 
    q_t(  2533), q_t(  2791), q_t(  3049), q_t(  3307),  // 924 
    q_t(  3566), q_t(  3825), q_t(  4085), q_t(  4345),  // 928 
    q_t(  4606), q_t(  4867), q_t(  5129), q_t(  5392),  // 932 
    q_t(  5655), q_t(  5919), q_t(  6184), q_t(  6450),  // 936 
    q_t(  6716), q_t(  6983), q_t(  7251), q_t(  7520),  // 940 
    q_t(  7790), q_t(  8061), q_t(  8333), q_t(  8606),  // 944 
    q_t(  8880), q_t(  9156), q_t(  9432), q_t(  9710),  // 948 
    q_t(  9989), q_t( 10270), q_t( 10552), q_t( 10835),  // 952 
    q_t( 11120), q_t( 11406), q_t( 11694), q_t( 11983),  // 956 
    q_t( 12274), q_t( 12567), q_t( 12861), q_t( 13158),  // 960 
    q_t( 13456), q_t( 13756), q_t( 14058), q_t( 14362),  // 964 
    q_t( 14669), q_t( 14977), q_t( 15287), q_t( 15600),  // 968 
    q_t( 15916), q_t( 16233), q_t( 16553), q_t( 16876),  // 972 
    q_t( 17201), q_t( 17529), q_t( 17860), q_t( 18193),  // 976 
    q_t( 18529), q_t( 18869), q_t( 19211), q_t( 19557),  // 980 
    q_t( 19906), q_t( 20258), q_t( 20613), q_t( 20972),  // 984 
    q_t( 21335), q_t( 21701), q_t( 22072), q_t( 22446),  // 988 
    q_t( 22824), q_t( 23206), q_t( 23593), q_t( 23984),  // 992 
    q_t( 24379), q_t( 24779), q_t( 25184), q_t( 25594),  // 996 
    q_t( 26008), q_t( 26428), q_t( 26853), q_t( 27284),  // 1000 
    q_t( 27720), q_t( 28162), q_t( 28611), q_t( 29065),  // 1004 
    q_t( 29525), q_t( 29993), q_t( 30466), q_t( 30947),  // 1008 
    q_t( 31435), q_t( 31931), q_t( 32433), q_t(-32592),  // 1012 
    q_t(-32073), q_t(-31546), q_t(-31010), q_t(-30465),  // 1016 
    q_t(-29911), q_t(-29348), q_t(-28775), q_t(-28191),  // 1020 
    }; 
  } 
 } 
} 

#endif