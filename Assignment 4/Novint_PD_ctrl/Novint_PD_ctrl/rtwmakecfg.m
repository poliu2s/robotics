function makeInfo = rtwmakecfg()
%RTWMAKECFG adds include and source directories to rtw make files.
%   makeInfo=RTWMAKECFG returns a structured array containing build info.
%   Please refer to the rtwmakecfg API section in the Real-Time workshop
%   Documentation for details on the format of this structure.
%
%   Simulink version    : 6.5 (R2006b) 03-Aug-2006
%   M file generated on : 13-Jan-2010 17:16:34

% Verify the Simulink version
verify_simulink_version();

% Get the current directory
currDir = pwd;

% Get the ML search paths and remove the toolbox subdirs except simfeatures
pSep = pathsep;
mlPaths = regexp([matlabpath pSep], ['.[^' pSep ']*' pSep], 'match');
if ~isempty(mlPaths)
    lctPath = fileparts(which('legacy_code'));
    lctPathIndex = strmatch([lctPath pSep], mlPaths);
    filteredPathIndices = strmatch(fullfile(matlabroot,'toolbox'), mlPaths);
    filteredPathIndices(find(filteredPathIndices == lctPathIndex)) = [];
    mlPaths(filteredPathIndices) = [];
    mlPaths = strrep(mlPaths, pSep, '');
end

% Declare cell arrays for storing the paths found
allIncPaths = {};
allSrcPaths = {};

% Detect if current build is for Model Reference Simulation Target
isMdlRefSimTarget = strcmpi(get_param(bdroot,'ModelReferenceTargetType'), 'SIM');
if (isMdlRefSimTarget==1)
    allCppSources = {};
end

% Get the build type
isSimTarget = is_simulation_target();
allLibs = {};


% Get the serialized paths information
info = get_serialized_info();

% Get all S-Function's name in the current model
sfunNames = {};
if ~isempty(bdroot)
    sfunBlks = find_system(bdroot,...
        'LookUnderMasks', 'all',...
        'FollowLinks', 'on',...
        'BlockType', 'S-Function'...
    );
    sfunNames = get_param(sfunBlks, 'FunctionName');
end

for ii = 1:length(info)
    % If the S-Function isn't part of the current build then skip its path info
    if isempty(strmatch(info(ii).SFunctionName, sfunNames, 'exact'))
        continue
    end

    % Path to the S-function source file
    if strcmp(info(ii).Language, 'C')
        fext = '.c';
    else
        fext = '.cpp';
    end
    pathToSFun = fileparts(which([info(ii).SFunctionName,fext]));
    if isempty(pathToSFun)
        pathToSFun = currDir;
    end

    % Default search paths for this S-function
    defaultPaths = [{pathToSFun} {currDir}];
    allPaths = [defaultPaths mlPaths];

    % Verify if IncPaths are absolute or relative and then complete
    % relative paths with the full S-function dir or current dir or ML path
    incPaths = info(ii).IncPaths;
    for jj = 1:length(incPaths)
        [fullPath, isFound] = resolve_path_info(correct_path_sep(incPaths{jj}), allPaths);
        if (isFound==0)
            error('LegacyCode:badIncludePath',...
                'Cannot find the include path ''%s''.', incPaths{jj});
        else
            incPaths{jj} = fullPath;
        end
    end
    incPaths = [incPaths defaultPaths];

    % Verify if SrcPaths are Absolute or Relative and then complete
    % relative paths with the full S-function dir or current dir or ML path
    srcPaths = info(ii).SrcPaths;
    for jj = 1:length(srcPaths)
        [fullPath, isFound] = resolve_path_info(correct_path_sep(srcPaths{jj}), allPaths);
        if (isFound==0)
            error('LegacyCode:badSourcePath',...
                'Cannot find the source path ''%s''.', srcPaths{jj});
        else
            srcPaths{jj} = fullPath;
        end
    end
    srcPaths = [srcPaths defaultPaths];

    % Common search paths for Source files specified with path
    srcSearchPaths = [srcPaths mlPaths];

    % Add path to source files if not specified and complete relative
    % paths with the full S-function dir or current dir or search
    % paths and then extract only the path part to add it to the srcPaths
    sourceFiles = info(ii).SourceFiles;
    saveCppSourceInfo = isMdlRefSimTarget && strcmp(info(ii).Language, 'C++');
    if (saveCppSourceInfo==1)
        cppSourceFiles = {[info(ii).SFunctionName,'_wrapper.cpp']};
    end
    pathFromSourceFiles = cell(1, length(sourceFiles));
    for jj = 1:length(sourceFiles)
        [fullName, isFound] = resolve_file_info(correct_path_sep(sourceFiles{jj}), srcSearchPaths);
        if isFound==0
            error('LegacyCode:badSourceFile',...
                'Cannot find the file ''%s''.', sourceFiles{jj});
        else
            % Extract the path part only
            [fpath, fname, fext] = fileparts(fullName);
            pathFromSourceFiles{jj} = fpath;
            if (saveCppSourceInfo==1)
                cppSourceFiles(end+1) = {[fname,fext]};
            end
        end
    end
    srcPaths = [srcPaths pathFromSourceFiles];

    % Verify if LibPaths are Absolute or Relative and then complete
    % relative paths with the full S-function dir or current dir or ML path
    libPaths = info(ii).LibPaths;
    for jj = 1:length(libPaths)
        [fullPath, isFound] = resolve_path_info(correct_path_sep(libPaths{jj}), allPaths);
        if (isFound==0)
            error('LegacyCode:badLibraryPath',...
                'Cannot find the library path ''%s''.', libPaths{jj});
        else
            libPaths{jj} = fullPath;
        end
    end
    libPaths = [libPaths defaultPaths];

    % Common search paths for Host and Target Lib with relative paths
    libSearchPaths = [libPaths mlPaths];

    if (isSimTarget==1)
        % Add path to host lib files if not specified and complete relative
        % paths with the full S-function dir or current dir or ML path
        libFiles = info(ii).HostLibFiles;
        for jj = 1:length(libFiles)
            [fullName, isFound] = resolve_file_info(correct_path_sep(libFiles{jj}), libSearchPaths);
            if isFound==0
                error('LegacyCode:badHostLibraryFile',...
                    'Cannot find the library ''%s''.', libFiles{jj});
            else
                libFiles{jj} = fullName;
            end
        end

    else
        % Add path to target lib files if not specified and complete relative 
        % paths with the full S-function dir or current dir or ML path
        libFiles = info(ii).TargetLibFiles;
        for jj = 1:length(libFiles)
            [fullName, isFound] = resolve_file_info(correct_path_sep(libFiles{jj}), libSearchPaths);
            if isFound==0
                error('LegacyCode:badTargetLibraryFile',...
                    'Cannot find the library ''%s''.', libFiles{jj});
            else
                libFiles{jj} = fullName;
            end
        end
    end

    % Concatenate known include and source directories
    allIncPaths = RTW.uniquePath([allIncPaths incPaths]);
    allSrcPaths = RTW.uniquePath([allSrcPaths srcPaths]);

    % Concatenate known C++ sources
    if (isMdlRefSimTarget==1)
        allCppSources = RTW.unique([allCppSources cppSourceFiles]);
    end

    % Concatenate Host or Target libraries
    allLibs   = RTW.uniquePath([allLibs libFiles]);

end

% Additionnal include directories
makeInfo.includePath = correct_path_name(allIncPaths);

% Additionnal source directories
makeInfo.sourcePath = correct_path_name(allSrcPaths);

% Additionnal C++ sources for Model Reference Simulation Target
if (isMdlRefSimTarget==1)
    makeInfo.sources = allCppSources;
end

% Additionnal libraries according to the build type
makeInfo.linkLibsObjs = correct_path_name(allLibs);

%--------------------------------------------------------------------------
function verify_simulink_version()

% Retrieve Simulink version
slVer = ver('simulink');
factor = 1.0;
thisVer = 0.0;
for ii = 1:length(slVer.Version)
    if slVer.Version(ii)=='.'
        factor = factor/10.0;
    else
        thisVer = thisVer + sscanf(slVer.Version(ii), '%d')*factor;
    end
end

% Verify that the actual plateform supports the function used
if thisVer < 6.4
    error('LegacyCode:badSimulinkVersion','This Simulink version ''%g'' is not supported.', thisVer)
end


%--------------------------------------------------------------------------
function [fullPath, isFound] = resolve_path_info(fullPath, searchPaths)

% Initialize output value
isFound = 0;

if is_absolute_path(fullPath)==1
    % Verify that the dir exists
    if exist(fullPath, 'dir')
        isFound = 1;
    end
else
    % Walk through the search path
    for ii = 1:length(searchPaths)
        thisFullPath = fullfile(searchPaths{ii}, fullPath);
        % If this candidate path exists then exit
        if exist(thisFullPath, 'dir')
            isFound = 1;
            fullPath = thisFullPath;
            break
        end
    end
end


%--------------------------------------------------------------------------
function [fullName, isFound] = resolve_file_info(fullName, searchPaths)

% Initialize output value
isFound = 0;

% Extract file parts
[fPath, fName, fExt] = fileparts(fullName);

if is_absolute_path(fPath)==1
    % If the file has no extension then try to add it
    if isempty(fExt)
        fExt = find_file_extension(fullfile(fPath, fName));
        fullName = fullfile(fPath, [fullName,fExt]);
    end
    % Verify that the file exists
    if exist(fullName, 'file')
        isFound = 1;
    end
else
    % Walk through the search path
    for ii = 1:length(searchPaths)
        thisFullName = fullfile(searchPaths{ii}, fullName);
        % If the file has no extension then try to add it
        if isempty(fExt)
            fExt = find_file_extension(thisFullName);
            thisFullName = [thisFullName,fExt];
        end
        % If this candidate path exists then exit
        if exist(thisFullName, 'file')
            fullName = thisFullName;
            isFound = 1;
            break
        end
    end
end


%--------------------------------------------------------------------------
function fext = find_file_extension(fullName)

% Initialize output value
fext = [];

% Use 'dir' because this command has the same behavior both
% on PC and Unix
theDir = dir([fullName,'.*']);
if ~isempty(theDir)
    for ii = 1:length(theDir)
        if theDir(ii).isdir
            continue
        end
        [fpath, fname, fext] = fileparts(theDir(ii).name);
        if ~isempty(fext)
            break % stop on first occurence
        end
    end
end


%--------------------------------------------------------------------------
function isSimTarget = is_simulation_target()

% Default output value
isSimTarget = 0;

% Get the current model and the code generation type to decide
% if we must link with the host libraries or with the target libraries
modelName = get_param(0, 'CurrentSystem');
if ~isempty(modelName)
    sysTarget = get_param(modelName, 'RTWSystemTargetFile');
    isSimTarget = ~isempty([findstr(sysTarget, 'rtwsfcn') findstr(sysTarget, 'accel')]);

    mdlRefSimTarget = get_param(modelName,'ModelReferenceTargetType');
    isSimTarget = strcmpi(mdlRefSimTarget, 'SIM') || isSimTarget;

    % Verify again it's not Accelerator
    if ~isSimTarget
        simMode = get_param(modelName, 'SimulationMode');
        simStat = get_param(modelName, 'SimulationStatus');
        isSimTarget = strcmp(simStat, 'initializing') & strcmp(simMode, 'accelerator');
    end
end


%--------------------------------------------------------------------------
function bool = is_absolute_path(thisPath)

if isempty(thisPath)
    bool = 0;
    return
end

if(thisPath(1)=='.')
    % Relative path
    bool = 0;
else
    if(ispc && length(thisPath)>=2)
        % Absolute path on PC start with drive letter or \(for UNC paths)
        bool = (thisPath(2)==':') | (thisPath(1)=='\');
    else
        % Absolute paths on unix start with '/'
        bool = thisPath(1)=='/';
    end
end


%--------------------------------------------------------------------------
function thePath = correct_path_sep(thePath)

if isunix
    wrongFilesepChar = '\';
    filesepChar = '/';
else
    wrongFilesepChar = '/';
    filesepChar = '\';
end

seps = find(thePath==wrongFilesepChar);
if(~isempty(seps))
    thePath(seps) = filesepChar;
end


%--------------------------------------------------------------------------
function thePaths = correct_path_name(thePaths)

for ii = 1:length(thePaths)
    thePaths{ii} = rtw_alt_pathname(thePaths{ii});
end
thePaths = RTW.uniquePath(thePaths);


%--------------------------------------------------------------------------
function info = get_serialized_info()

% Allocate the output structure array
info(1:1) = struct(...
    'SFunctionName', '',...
    'IncPaths', {{}},...
    'SrcPaths', {{}},...
    'LibPaths', {{}},...
    'SourceFiles', {{}},...
    'HostLibFiles', {{}},...
    'TargetLibFiles', {{}},...
    'Language', ''...
    );

% Fill file and path dependencies for 'sfunc_haptics'
info(1).SFunctionName = 'sfunc_haptics';
info(1).IncPaths = {'C:\Program Files\novint\HDAL_SDK_1.1.0_Beta\include'};
info(1).LibPaths = {'C:\Program Files\novint\HDAL_SDK_1.1.0_Beta\lib'};
info(1).SourceFiles = {'haptics.cpp'};
info(1).HostLibFiles = {'hdl.lib'};
info(1).TargetLibFiles = {'hdl.lib'};
info(1).Language = 'C++';



