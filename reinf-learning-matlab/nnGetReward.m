function [reward, terminal] = nnGetReward(action, sensor, crash)
    
    % Reward function of the Neural Network

    a = action;
    reward = 0;
    terminal = false;    
    obstacleCrash = ~isempty(find(crash(1),1));
    obstacleDetected = ~isempty(find(crash(2),1));
    totalSensorDistance = sum(sensor) % distance of all 5 sensors combined.
    % [89.841   74.554   69.567   72.610   63.438] - when sensor sees obstacle at distances 89cm, 74cm, ...
    % distance cut from ideal 5*100cm = 500cm (when no obstacles are seen by any of 5 sensors), normalized between 0 and 1
    totalSensorDistanceCut = (length(sensor)*100 - totalSensorDistance) / (length(sensor)*100);
    
    r = [0.01, -0.01, -0.01, -1];
    
    if( a == 1)
        
        reward = r(1);
    elseif (a == 2)
        
        reward = r(2);        
    elseif ( a == 3 )
        
        reward = r(3);
    end
    
    if(obstacleDetected)
        %reward = - round(totalSensorDistanceCut .* 10) ./ 10;
        stateReward = -totalSensorDistanceCut;
        % if reward (punishment) for sensorsState is worse than reward 
        % for action (straight, left, right), use the sensorState reward.
        if(stateReward < reward) reward = stateReward; end
        disp("Obstacle detected");
    end
    
    if(obstacleCrash)
        reward = r(4);
        disp("Obstacle crash");
        terminal = true;
    end
    
end