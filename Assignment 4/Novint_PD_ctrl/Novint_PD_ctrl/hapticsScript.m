clc
close all
clear all
hapticsSim = legacy_code('initialize');
%definition
hapticsSim.SFunctionName = 'sfunc_haptics';
hapticsSim.OutputFcnSpec = 'void falconPlant(double u1[3], double y1[3])';
hapticsSim.StartFcnSpec = 'createHaptics()';
hapticsSim.TerminateFcnSpec = 'deleteHaptics()';
hapticsSim.HeaderFiles = {'haptics.h'};
hapticsSim.SourceFiles = {'haptics.cpp'};
hapticsSim.HostLibFiles = {'hdl.lib'};
hapticsSim.IncPaths = {'C:\Program Files\novint\HDAL_SDK_1.1.0_Beta\include'};
hapticsSim.SrcPaths = {''};
hapticsSim.LibPaths = {'C:\Program Files\novint\HDAL_SDK_1.1.0_Beta\lib'};
hapticsSim.Options.language = 'C++';
hapticsSim.Options.useTlcWithAccel = false;
hapticsSim.TargetLibFiles = {'hdl.lib'};
%compile
legacy_code('sfcn_cmex_generate', hapticsSim);
legacy_code('sfcn_tlc_generate', hapticsSim);
legacy_code('rtwmakecfg_generate', hapticsSim);
%'-g' to enable debug from VC++
% legacy_code('compile', hapticsSim, {'-g','-DWIN32', '-D_DEBUG', '-D_CONSOLE'});
legacy_code('compile', hapticsSim, '-DWIN32');

%Generate Block
legacy_code('slblock_generate', hapticsSim, 'hapticsSimBlk');
