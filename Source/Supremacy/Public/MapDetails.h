// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapDetails.generated.h"

USTRUCT(BlueprintType)
struct FMapDetails {
  GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString Name;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString ImageURL;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int Width;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int Height;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int CellsX;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int CellsY;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int PixelLeft;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int PixelTop;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TArray<int> DisabledCells;

  FMapDetails()
  {
      Width = 0;
      Height = 0;
      CellsX = 0;
      CellsY = 0;
      PixelLeft = 0;
      PixelTop = 0;
      DisabledCells = TArray<int>();
  }

  FMapDetails(FString Name, FString ImageURL, int Width, int Height, int CellsX, int CellsY, int PixelLeft, int PixelTop, TArray<int> DisabledCells)
      : Name(Name), ImageURL(ImageURL), Width(Width), Height(Height), CellsX(CellsX), CellsY(CellsY), PixelLeft(PixelLeft), PixelTop(PixelTop), DisabledCells(DisabledCells)
  {}
};

static const TMap<FString, FMapDetails> SupremacyMapDetails = {
  {
    "DesertCity",
    {
      "DesertCity",
      "https://ninjasoftware-static-media.s3.ap-southeast-2.amazonaws.com/supremacy/maps/desert_city.jpg",
      1080, 1080,
      30, 30,
      -36000, -38000,
      {}
    },
  },
  {
    "ArcticBay",
    {
      "ArcticBay",
      "https://ninjasoftware-static-media.s3.ap-southeast-2.amazonaws.com/supremacy/maps/arctic_bay.jpg",
      1080, 1080,
      55, 55,
      -40000, -39000,
      {0,162,217,272,327,382,437,492,547,602,657,712,767,822,877,932,987,1042,1097,1152,1207,1262,1317,1372,1427,1482,1537,1592,1647,1702,1757,1812,1867,1922,1977,2032,2087,2142,2197,2252,2307,2362,2417,2472,2527,2582,2637,2692,2747,2802,2857,163,218,273,328,383,438,493,548,603,658,713,768,823,878,933,988,1043,1098,1153,1208,1263,1318,1373,1428,1483,1538,1593,1648,1703,1758,1813,1868,1923,1978,2033,2088,2143,2198,2253,2308,2363,2418,2473,2528,2583,2638,2693,2748,2803,2858,164,219,274,329,384,439,494,549,604,659,714,769,824,879,934,989,1044,1099,1154,1209,1264,1319,1374,1429,1484,1539,1594,1649,1704,1759,1814,1869,1924,1979,2034,2089,2144,2199,2254,2309,2364,2419,2474,2529,2584,2639,2694,2749,2804,2859,165,220,275,330,385,440,495,550,605,660,715,770,825,880,935,990,1045,1100,1155,1210,1265,1320,1375,1430,1485,1540,1595,1650,1705,1760,1815,1870,1925,1980,2035,2090,2145,2200,2255,2310,2365,2420,2475,2530,2585,2640,2695,2750,2805,2860,166,221,276,331,386,441,496,551,606,661,716,771,826,881,936,991,1046,1101,1156,1211,1266,1321,1376,1431,1486,1541,1596,1651,1706,1761,1816,1871,1926,1981,2036,2091,2146,2201,2256,2311,2366,2421,2476,2531,2586,2641,2696,2751,2806,2861,167,222,277,332,387,442,497,552,607,662,717,772,827,882,937,992,1047,1102,1157,1212,1267,1322,1377,1432,1487,1542,1597,1652,1707,1762,1817,1872,1927,1982,2037,2092,2147,2202,2257,2312,2367,2422,2477,2532,2587,2642,2697,2752,2807,2862,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,2863,2864,2865,2866,2867,2868,2869,2870,2871,2872,2873,2874,2875,2876,2877,2878,2879,2880,2881,2882,2883,2884,2885,2886,2887,2888,2889,2890,2891,2892,2893,2894,2895,2896,2897,2898,2899,2900,2901,2902,2903,2904,2905,2906,2907,2908,2909,2910,2911,2912,2913,2914,2915,2916,2917,2918,2919,2920,2921,2922,2923,2924,2925,2926,2927,2928,2929,2930,2931,2932,2933,2934,2935,2936,2937,2938,2939,2940,2941,2942,2943,2944,2945,2946,2947,2948,2949,2950,2951,2952,2953,2954,2955,2956,2957,2958,2959,2960,2961,2962,2963,2964,2965,2966,2967,2968,2969,2970,2971,2972,2973,2974,2975,2976,2977,2978,2979,2980,2981,2982,2983,2984,2985,2986,2987,2988,2989,2990,2991,2992,2993,2994,2995,2996,2997,2998,2999,3000,3001,3002,3003,3004,3005,3006,3007,3008,3009,3010,3011,3012,3013,3014,3015,3016,3017,3018,3019,3020,3021,3022,3023,3024}
    },
  },
  {
    "UrbanBuildings",
    {
      "UrbanBuildings",
      "https://ninjasoftware-static-media.s3.ap-southeast-2.amazonaws.com/supremacy/maps/UrbanBuildings-v2.jpg",
      1080, 1080,
      62, 62,
      -110500, -152500,
      {0,183,245,307,369,431,493,555,617,679,741,803,865,927,989,1051,1113,1175,1237,1299,1361,1423,1485,1547,1609,1671,1733,1795,1857,1919,1981,2043,2105,2167,2229,2291,2353,2415,2477,2539,2601,2663,2725,2787,2849,2911,2973,3035,3097,3159,3221,3283,3345,3407,3469,3531,3593,3655,184,246,308,370,432,494,556,618,680,742,804,866,928,990,1052,1114,1176,1238,1300,1362,1424,1486,1548,1610,1672,1734,1796,1858,1920,1982,2044,2106,2168,2230,2292,2354,2416,2478,2540,2602,2664,2726,2788,2850,2912,2974,3036,3098,3160,3222,3284,3346,3408,3470,3532,3594,3656,185,247,309,371,433,495,557,619,681,743,805,867,929,991,1053,1115,1177,1239,1301,1363,1425,1487,1549,1611,1673,1735,1797,1859,1921,1983,2045,2107,2169,2231,2293,2355,2417,2479,2541,2603,2665,2727,2789,2851,2913,2975,3037,3099,3161,3223,3285,3347,3409,3471,3533,3595,3657,186,248,310,372,434,496,558,620,682,744,806,868,930,992,1054,1116,1178,1240,1302,1364,1426,1488,1550,1612,1674,1736,1798,1860,1922,1984,2046,2108,2170,2232,2294,2356,2418,2480,2542,2604,2666,2728,2790,2852,2914,2976,3038,3100,3162,3224,3286,3348,3410,3472,3534,3596,3658,187,249,311,373,435,497,559,621,683,745,807,869,931,993,1055,1117,1179,1241,1303,1365,1427,1489,1551,1613,1675,1737,1799,1861,1923,1985,2047,2109,2171,2233,2295,2357,2419,2481,2543,2605,2667,2729,2791,2853,2915,2977,3039,3101,3163,3225,3287,3349,3411,3473,3535,3597,3659,188,250,312,374,436,498,560,622,684,746,808,870,932,994,1056,1118,1180,1242,1304,1366,1428,1490,1552,1614,1676,1738,1800,1862,1924,1986,2048,2110,2172,2234,2296,2358,2420,2482,2544,2606,2668,2730,2792,2854,2916,2978,3040,3102,3164,3226,3288,3350,3412,3474,3536,3598,3660,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,3661,3662,3663,3664,3665,3666,3667,3668,3669,3670,3671,3672,3673,3674,3675,3676,3677,3678,3679,3680,3681,3682,3683,3684,3685,3686,3687,3688,3689,3690,3691,3692,3693,3694,3695,3696,3697,3698,3699,3700,3701,3702,3703,3704,3705,3706,3707,3708,3709,3710,3711,3712,3713,3714,3715,3716,3717,3718,3719,3720,3721,3722,3723,3724,3725,3726,3727,3728,3729,3730,3731,3732,3733,3734,3735,3736,3737,3738,3739,3740,3741,3742,3743,3744,3745,3746,3747,3748,3749,3750,3751,3752,3753,3754,3755,3756,3757,3758,3759,3760,3761,3762,3763,3764,3765,3766,3767,3768,3769,3770,3771,3772,3773,3774,3775,3776,3777,3778,3779,3780,3781,3782,3783,3784,3785,3786,3787,3788,3789,3790,3791,3792,3793,3794,3795,3796,3797,3798,3799,3800,3801,3802,3803,3804,3805,3806,3807,3808,3809,3810,3811,3812,3813,3814,3815,3816,3817,3818,3819,3820,3821,3822,3823,3824,3825,3826,3827,3828,3829,3830,3831,3832,3833,3834,3835,3836,3837,3838,3839,3840,3841,3842,3843}
    },
  },
  {
    "NeoTokyo",
    {
      "NeoTokyo",
      "https://ninjasoftware-static-media.s3.ap-southeast-2.amazonaws.com/supremacy/maps/NeoTokyo.jpg",
      1080, 1080,
      34, 34,
      -33550, -34450,
      {0,66,100,134,168,202,236,270,304,338,372,406,440,474,508,542,576,610,644,678,712,746,780,814,848,882,916,950,984,1018,1052,1086,67,101,135,169,203,237,271,305,339,373,407,441,475,509,543,577,611,645,679,713,747,781,815,849,883,917,951,985,1019,1053,1087,68,102,136,170,204,238,272,306,340,374,408,442,476,510,544,578,612,646,680,714,748,782,816,850,884,918,952,986,1020,1054,1088,69,103,137,171,205,239,273,307,341,375,409,443,477,511,545,579,613,647,681,715,749,783,817,851,885,919,953,987,1021,1055,1089,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,1090,1091,1092,1093,1094,1095,1096,1097,1098,1099,1100,1101,1102,1103,1104,1105,1106,1107,1108,1109,1110,1111,1112,1113,1114,1115,1116,1117,1118,1119,1120,1121,1122,1123,1124,1125,1126,1127,1128,1129,1130,1131,1132,1133,1134,1135,1136,1137,1138,1139,1140,1141,1142,1143,1144,1145,1146,1147,1148,1149,1150,1151,1152,1153,1154,1155,368,402,436,470,504,538,572,606,640,674,708,742,776,810,844,878,912,946,980,1014,1048,1082,1083,1084,1085,1051,1050,1049,1015,1016,1017,983,982,981,947,948,949,915,914,913,879,845,811,777,743,709,675,641,607,573,539,505,471,437,403,369,370,439,473,540,574,608,642,676,710,744,778,812,846,880,881,847,813,779,745,711,677,643,609,575,541,507,506,472,438,404,405,371,1060,1059,1058,1057,1056,1022,988,954,920,955,989,1023,1024,1025,990,785,786,787,788,750,784,752,753,754,755,756,789,790,791,757,723,722,721,720,719,718,717,751,682,716,648,580,614,684,685,686,687,688,689,655,621,587,553,519,485,451,417,383,349,315,281,247,213,179,145,111,77,76,75,74,73,72,71,70,104,138,172,206,240,274,308,342,376,410,444,478,512,546,547,581,615,649,683,616,582,548,514,480,446,412,378,275,513,309,343,377,411,445,479,650,651,652,653,654,620,586,552,518,484,450,416,382,348,314,280,246,212,178,144,110,109,108,107,106,139,105,173,207,241,242,208,174,140,141,142,143,177,176,175,209,243,210,211,245,276,278,279,277,244,311,312,313,347,381,415,449,483,517,551,585,619,618,617,583,549,515,481,447,413,379,345,346,380,414,448,482,516,550,584,344,310,220,221,222,256,186,187,188,189,190,191,118,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,133,167,166,165,128,131,132,164,163,129,130,127,126,123,121,120,119,156,157,158,124,125,159,155,122,152,153,154,195,162,196,197,198,199,200,201,161,193,194,160,224,225,192,226,259,258,257,223,261,262,263,264,265,266,267,268,269,235,234,233,232,231,230,229,228,227,260,83,82,116,151,117,150,301,303,337,336,302,335,80,81,115,149,287,288,322,321,356,358,324,290,291,360,326,292,496,530,564,563,562,561,560,362,363,364,396,397,398,430,464,498,499,500,770,771,772,738,737,736,702,703,804,805,806,907,873,941,942,976,975,974,1008,1009,1010,1044,1043,1042,930,929,928,963,964,998,997,996,962,965,931,999,798,799,800,802,794,795,796,762,761,760,726,727,728,658,660,659,625,626,592,558,524,490,456,455,454,488,522,556,590,624,557,523,489,591,1005,971}
    },
  },
  {
    "CloudKu",
    {
      "CloudKu",
      "https://ninjasoftware-static-media.s3.ap-southeast-2.amazonaws.com/supremacy/maps/cloud_ku.png",
      1080, 1080,
      45,  45,
      -45000, -45000,
      {}
    },
  },
  {
    "TheHive",
    {
      "TheHive",
      "https://ninjasoftware-static-media.s3.ap-southeast-2.amazonaws.com/supremacy/maps/the_hive.png",
      1080, 1080,
      40,  40,
      -20000, -59700,
      {}
    },
  },
  {
    "AokigaharaForest",
    {
      "AokigaharaForest",
      "https://ninjasoftware-static-media.s3.ap-southeast-2.amazonaws.com/supremacy/maps/AokigaharaForest.jpg",
      1080, 1080,
      46, 46,
      -51000, -51000,
      {0,90,136,182,228,274,320,366,412,458,504,550,596,642,688,734,780,826,872,918,964,1010,1056,1102,1148,1194,1240,1286,1332,1378,1424,1470,1516,1562,1608,1654,1700,1746,1792,1838,1884,1930,1976,2022,91,137,183,229,275,321,367,413,459,505,551,597,643,689,735,781,827,873,919,965,1011,1057,1103,1149,1195,1241,1287,1333,1379,1425,1471,1517,1563,1609,1655,1701,1747,1793,1839,1885,1931,1977,2023,92,138,184,230,276,322,368,414,460,506,552,598,644,690,736,782,828,874,920,966,1012,1058,1104,1150,1196,1242,1288,1334,1380,1426,1472,1518,1564,1610,1656,1702,1748,1794,1840,1886,1932,1978,2024,93,139,185,231,277,323,369,415,461,507,553,599,645,691,737,783,829,875,921,967,1013,1059,1105,1151,1197,1243,1289,1335,1381,1427,1473,1519,1565,1611,1657,1703,1749,1795,1841,1887,1933,1979,2025,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,2026,2027,2028,2029,2030,2031,2032,2033,2034,2035,2036,2037,2038,2039,2040,2041,2042,2043,2044,2045,2046,2047,2048,2049,2050,2051,2052,2053,2054,2055,2056,2057,2058,2059,2060,2061,2062,2063,2064,2065,2066,2067,2068,2069,2070,2071,2072,2073,2074,2075,2076,2077,2078,2079,2080,2081,2082,2083,2084,2085,2086,2087,2088,2089,2090,2091,2092,2093,2094,2095,2096,2097,2098,2099,2100,2101,2102,2103,2104,2105,2106,2107,2108,2109,2110,2111,2112,2113,2114,2115}
    },
  },
  {
    "CityBlockArena",
    {
      "CityBlockArena",
      "https://ninjasoftware-static-media.s3.ap-southeast-2.amazonaws.com/supremacy/maps/CityBlockArena.jpg",
      1080, 1080,
      34, 34,
      -34500, -28200,
      {}
      },
    },
  {
    "RedMountainMine",
    {
      "RedMountainMine",
      "https://ninjasoftware-static-media.s3.ap-southeast-2.amazonaws.com/supremacy/maps/RedMountainMine.jpg",
      1080, 1080,
      72, 72,
      -54000, 0,
      {}
    },
  },
};