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
    ;% Auto data (sldrtex_profiling_P)
    ;%
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% sldrtex_profiling_P.UniformRandomNumber200x200_Minimum
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% sldrtex_profiling_P.UniformRandomNumber200x200_Maximum
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% sldrtex_profiling_P.UniformRandomNumber200x200_Seed
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 40001;
	
	  ;% sldrtex_profiling_P.UniformRandomNumber100x100_Minimum
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 40002;
	
	  ;% sldrtex_profiling_P.UniformRandomNumber100x100_Maximum
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 40003;
	
	  ;% sldrtex_profiling_P.UniformRandomNumber100x100_Seed
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 50003;
	
	  ;% sldrtex_profiling_P.ExecutionTime_P1
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 50004;
	
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
    ;% Auto data (sldrtex_profiling_B)
    ;%
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% sldrtex_profiling_B.UniformRandomNumber200x200
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% sldrtex_profiling_B.Timestamp3
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 40000;
	
	  ;% sldrtex_profiling_B.MatrixMulltiply200x200
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 40001;
	
	  ;% sldrtex_profiling_B.Timestamp1
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 80001;
	
	  ;% sldrtex_profiling_B.MinMax40000elements
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 80002;
	
	  ;% sldrtex_profiling_B.Timestamp2
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 80003;
	
	  ;% sldrtex_profiling_B.MatrixMultiplyblock
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 80004;
	
	  ;% sldrtex_profiling_B.MinMaxblock
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 80005;
	
	  ;% sldrtex_profiling_B.MinMax10000elements
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 80006;
	
	  ;% sldrtex_profiling_B.Modelexecutiontime
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 80007;
	
	  ;% sldrtex_profiling_B.Taskexecutiontimes
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 80008;
	
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
    nTotSects     = 4;
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
    ;% Auto data (sldrtex_profiling_DW)
    ;%
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% sldrtex_profiling_DW.UniformRandomNumber200x200_NextOutput
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% sldrtex_profiling_DW.UniformRandomNumber100x100_NextOutput
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 40000;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% sldrtex_profiling_DW.Blockprofiling_PWORK.LoggedData
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
	  ;% sldrtex_profiling_DW.Modelandtaskexecutiontimes_PWORK.LoggedData
	  section.data(2).logicalSrcIdx = 3;
	  section.data(2).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% sldrtex_profiling_DW.ExecutionTime_DIMS2
	  section.data(1).logicalSrcIdx = 4;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% sldrtex_profiling_DW.RandSeed
	  section.data(1).logicalSrcIdx = 5;
	  section.data(1).dtTransOffset = 0;
	
	  ;% sldrtex_profiling_DW.RandSeed_p
	  section.data(2).logicalSrcIdx = 6;
	  section.data(2).dtTransOffset = 40000;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
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


  targMap.checksum0 = 1301872827;
  targMap.checksum1 = 3462230155;
  targMap.checksum2 = 1371858433;
  targMap.checksum3 = 2408090048;

