function msd = MSD_routine(data)
% USAGE:    msd = MSD_routine(data)
% PURPOSE:  Calcuate the MSD from a data series
%           
% 
% INPUT:
% data 
%           Trajectory data of the 3-column format:
%           frame    x-position     y-position    
%           
%   
% OUTPUT:  
% msd: will have three columns:
%       Column 1: lag time (in frames)
%       Column 2: MSD (in pixels)
%       Column 3: number of observations in average
%
% CREATED: Alessio Caciagli, University of Cambridge, January 2017

msd = [];
    
    % Find the number of frames for the particle
    totalframe = length(data);
    
    % The maximum frame separation is totalframe - 1
    max_step = totalframe - 1;
    
    % Only analyze if there is more than one frame to calculate
    % displacement
    if max_step >= 1
        disp(['Total frames: ',...
            num2str(totalframe)]);
            msd=zeros(max_step,1);
        % Step through all frame separations starting from 1 up to max_step
        for step=1:max_step
            deltacoords=data(1+step:1+max_step,2:3)-data(1:1+max_step-step,2:3);
            squaredisp=sum(deltacoords.^2,2);
            msd(step,1) = step; 
            msd(step,2) = mean(squaredisp); %# mean average
            msd(step,3) = length(squaredisp); %# number of observations
        end
    end
end