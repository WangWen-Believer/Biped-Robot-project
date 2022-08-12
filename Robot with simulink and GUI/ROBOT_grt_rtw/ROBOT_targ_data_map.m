  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (ROBOT_P)
    ;%
      section.nData     = 69;
      section.data(69)  = dumData; %prealloc
      
	  ;% ROBOT_P.a
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ROBOT_P.Constant_Value
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ROBOT_P.Constant1_Value
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ROBOT_P.Gain_Gain
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ROBOT_P.Constant_Value_d
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% ROBOT_P.Constant10_Value
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% ROBOT_P.Gain_Gain_c
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% ROBOT_P.Constant_Value_g
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% ROBOT_P.Constant11_Value
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% ROBOT_P.Gain_Gain_h
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% ROBOT_P.Constant_Value_gd
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% ROBOT_P.Constant12_Value
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% ROBOT_P.Gain_Gain_m
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% ROBOT_P.Constant_Value_c
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% ROBOT_P.Constant13_Value
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% ROBOT_P.Gain_Gain_o
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% ROBOT_P.Constant_Value_j
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% ROBOT_P.Constant14_Value
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% ROBOT_P.Gain_Gain_k
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% ROBOT_P.Constant_Value_l
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% ROBOT_P.Constant15_Value
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% ROBOT_P.Gain_Gain_g
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% ROBOT_P.Constant_Value_a
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 22;
	
	  ;% ROBOT_P.Constant16_Value
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 23;
	
	  ;% ROBOT_P.Gain_Gain_g5
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 24;
	
	  ;% ROBOT_P.Constant_Value_h
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 25;
	
	  ;% ROBOT_P.Constant17_Value
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 26;
	
	  ;% ROBOT_P.Gain_Gain_gm
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 27;
	
	  ;% ROBOT_P.Constant_Value_gz
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 28;
	
	  ;% ROBOT_P.Constant18_Value
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 29;
	
	  ;% ROBOT_P.Gain_Gain_kc
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 30;
	
	  ;% ROBOT_P.Constant_Value_p
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 31;
	
	  ;% ROBOT_P.Constant19_Value
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 32;
	
	  ;% ROBOT_P.Gain_Gain_j
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 33;
	
	  ;% ROBOT_P.Constant_Value_m
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 34;
	
	  ;% ROBOT_P.Constant2_Value
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 35;
	
	  ;% ROBOT_P.Gain_Gain_n
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 36;
	
	  ;% ROBOT_P.Constant_Value_b
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 37;
	
	  ;% ROBOT_P.Constant20_Value
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 38;
	
	  ;% ROBOT_P.Gain_Gain_ma
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 39;
	
	  ;% ROBOT_P.Constant_Value_cb
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 40;
	
	  ;% ROBOT_P.Constant21_Value
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 41;
	
	  ;% ROBOT_P.Gain_Gain_l
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 42;
	
	  ;% ROBOT_P.Constant_Value_bj
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 43;
	
	  ;% ROBOT_P.Gain_Gain_ov
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 44;
	
	  ;% ROBOT_P.Constant_Value_f
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 45;
	
	  ;% ROBOT_P.Constant23_Value
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 46;
	
	  ;% ROBOT_P.Gain_Gain_gd
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 47;
	
	  ;% ROBOT_P.Constant_Value_ar
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 48;
	
	  ;% ROBOT_P.Constant3_Value
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 49;
	
	  ;% ROBOT_P.Gain_Gain_kl
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 50;
	
	  ;% ROBOT_P.Constant_Value_fd
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 51;
	
	  ;% ROBOT_P.Constant4_Value
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 52;
	
	  ;% ROBOT_P.Gain_Gain_d
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 53;
	
	  ;% ROBOT_P.Constant_Value_n
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 54;
	
	  ;% ROBOT_P.Constant5_Value
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 55;
	
	  ;% ROBOT_P.Gain_Gain_dq
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 56;
	
	  ;% ROBOT_P.Constant_Value_ng
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 57;
	
	  ;% ROBOT_P.Constant6_Value
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 58;
	
	  ;% ROBOT_P.Gain_Gain_e
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 59;
	
	  ;% ROBOT_P.Constant_Value_ad
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 60;
	
	  ;% ROBOT_P.Constant7_Value
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 61;
	
	  ;% ROBOT_P.Gain_Gain_a
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 62;
	
	  ;% ROBOT_P.Constant_Value_no
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 63;
	
	  ;% ROBOT_P.Constant8_Value
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 64;
	
	  ;% ROBOT_P.Gain_Gain_f
	  section.data(66).logicalSrcIdx = 65;
	  section.data(66).dtTransOffset = 65;
	
	  ;% ROBOT_P.Constant_Value_pw
	  section.data(67).logicalSrcIdx = 66;
	  section.data(67).dtTransOffset = 66;
	
	  ;% ROBOT_P.Constant9_Value
	  section.data(68).logicalSrcIdx = 67;
	  section.data(68).dtTransOffset = 67;
	
	  ;% ROBOT_P.Gain_Gain_p
	  section.data(69).logicalSrcIdx = 68;
	  section.data(69).dtTransOffset = 68;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (ROBOT_B)
    ;%
      section.nData     = 46;
      section.data(46)  = dumData; %prealloc
      
	  ;% ROBOT_B.Gain
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ROBOT_B.Gain_f
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ROBOT_B.Gain_c
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ROBOT_B.Gain_l
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ROBOT_B.Gain_h
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% ROBOT_B.Gain_o
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% ROBOT_B.Gain_ce
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% ROBOT_B.Gain_d
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% ROBOT_B.Gain_ho
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% ROBOT_B.Gain_f1
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% ROBOT_B.Gain_i
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% ROBOT_B.Gain_j
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% ROBOT_B.Gain_lg
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% ROBOT_B.Gain_dz
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% ROBOT_B.Gain_n
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% ROBOT_B.Gain_ox
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% ROBOT_B.Gain_cl
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% ROBOT_B.Gain_fa
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% ROBOT_B.Gain_k
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% ROBOT_B.Gain_m
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% ROBOT_B.Gain_im
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% ROBOT_B.Gain_a
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% ROBOT_B.Gain_dw
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 22;
	
	  ;% ROBOT_B.INPUT_21_1_1
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 23;
	
	  ;% ROBOT_B.INPUT_15_1_1
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 27;
	
	  ;% ROBOT_B.INPUT_17_1_1
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 31;
	
	  ;% ROBOT_B.INPUT_8_1_1
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 35;
	
	  ;% ROBOT_B.INPUT_14_1_1
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 39;
	
	  ;% ROBOT_B.INPUT_22_1_1
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 43;
	
	  ;% ROBOT_B.INPUT_1_1_1
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 47;
	
	  ;% ROBOT_B.INPUT_20_1_1
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 51;
	
	  ;% ROBOT_B.INPUT_11_1_1
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 55;
	
	  ;% ROBOT_B.INPUT_18_1_1
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 59;
	
	  ;% ROBOT_B.INPUT_23_1_1
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 63;
	
	  ;% ROBOT_B.INPUT_13_1_1
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 67;
	
	  ;% ROBOT_B.INPUT_12_1_1
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 71;
	
	  ;% ROBOT_B.INPUT_7_1_1
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 75;
	
	  ;% ROBOT_B.INPUT_2_1_1
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 79;
	
	  ;% ROBOT_B.INPUT_16_1_1
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 83;
	
	  ;% ROBOT_B.INPUT_3_1_1
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 87;
	
	  ;% ROBOT_B.INPUT_4_1_1
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 91;
	
	  ;% ROBOT_B.INPUT_5_1_1
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 95;
	
	  ;% ROBOT_B.INPUT_6_1_1
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 99;
	
	  ;% ROBOT_B.INPUT_9_1_1
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 103;
	
	  ;% ROBOT_B.INPUT_10_1_1
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 107;
	
	  ;% ROBOT_B.INPUT_19_1_1
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 111;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 3;
    sectIdxOffset = 1;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (ROBOT_DW)
    ;%
      section.nData     = 23;
      section.data(23)  = dumData; %prealloc
      
	  ;% ROBOT_DW.INPUT_21_1_1_discrete
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ROBOT_DW.INPUT_15_1_1_discrete
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 2;
	
	  ;% ROBOT_DW.INPUT_17_1_1_discrete
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 4;
	
	  ;% ROBOT_DW.INPUT_8_1_1_discrete
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 6;
	
	  ;% ROBOT_DW.INPUT_14_1_1_discrete
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 8;
	
	  ;% ROBOT_DW.INPUT_22_1_1_discrete
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 10;
	
	  ;% ROBOT_DW.INPUT_1_1_1_discrete
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 12;
	
	  ;% ROBOT_DW.INPUT_20_1_1_discrete
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 14;
	
	  ;% ROBOT_DW.INPUT_11_1_1_discrete
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 16;
	
	  ;% ROBOT_DW.INPUT_18_1_1_discrete
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 18;
	
	  ;% ROBOT_DW.INPUT_23_1_1_discrete
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 20;
	
	  ;% ROBOT_DW.INPUT_13_1_1_discrete
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 22;
	
	  ;% ROBOT_DW.INPUT_12_1_1_discrete
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 24;
	
	  ;% ROBOT_DW.INPUT_7_1_1_discrete
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 26;
	
	  ;% ROBOT_DW.INPUT_2_1_1_discrete
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 28;
	
	  ;% ROBOT_DW.INPUT_16_1_1_discrete
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 30;
	
	  ;% ROBOT_DW.INPUT_3_1_1_discrete
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 32;
	
	  ;% ROBOT_DW.INPUT_4_1_1_discrete
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 34;
	
	  ;% ROBOT_DW.INPUT_5_1_1_discrete
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 36;
	
	  ;% ROBOT_DW.INPUT_6_1_1_discrete
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 38;
	
	  ;% ROBOT_DW.INPUT_9_1_1_discrete
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 40;
	
	  ;% ROBOT_DW.INPUT_10_1_1_discrete
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 42;
	
	  ;% ROBOT_DW.INPUT_19_1_1_discrete
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 44;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% ROBOT_DW.SINK_1_Simulator
	  section.data(1).logicalSrcIdx = 23;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ROBOT_DW.SINK_1_SimulationData
	  section.data(2).logicalSrcIdx = 24;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ROBOT_DW.SINK_1_DiagnosticManager
	  section.data(3).logicalSrcIdx = 25;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ROBOT_DW.SINK_1_Logger
	  section.data(4).logicalSrcIdx = 26;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ROBOT_DW.SINK_1_SampleTimeIdx
	  section.data(5).logicalSrcIdx = 27;
	  section.data(5).dtTransOffset = 4;
	
	  ;% ROBOT_DW.STATE_1_Simulator
	  section.data(6).logicalSrcIdx = 28;
	  section.data(6).dtTransOffset = 5;
	
	  ;% ROBOT_DW.STATE_1_SimulationData
	  section.data(7).logicalSrcIdx = 29;
	  section.data(7).dtTransOffset = 6;
	
	  ;% ROBOT_DW.STATE_1_DiagnosticManager
	  section.data(8).logicalSrcIdx = 30;
	  section.data(8).dtTransOffset = 7;
	
	  ;% ROBOT_DW.STATE_1_Logger
	  section.data(9).logicalSrcIdx = 31;
	  section.data(9).dtTransOffset = 8;
	
	  ;% ROBOT_DW.STATE_1_SampleTimeIdx
	  section.data(10).logicalSrcIdx = 32;
	  section.data(10).dtTransOffset = 9;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% ROBOT_DW.SINK_1_CallSimulatorOutput
	  section.data(1).logicalSrcIdx = 33;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ROBOT_DW.STATE_1_CallSimulatorOutput
	  section.data(2).logicalSrcIdx = 34;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 1339606787;
  targMap.checksum1 = 820518362;
  targMap.checksum2 = 3341637844;
  targMap.checksum3 = 2944994238;

