function [reward, terminal] = nnGetReward(action, crash)
    
    % Reward function of the Neural Network

    a = action;
    reward = 0;
    terminal = false;    
    obstacleCrash = ~isempty(find(crash(1),1));
    obstacleDetected = ~isempty(find(crash(2),1));
    
    r = [0.01, -0.01, -0.01, -0.05, -1];
    
    if( a == 1)
        
        reward = r(1);
    elseif (a == 2)
        
        reward = r(2);        
    elseif ( a == 3 )
        
        reward = r(3);
    end
    
    if(obstacleDetected)
        reward = r(4);
        disp("Obstacle detected");
    end
    
    if(obstacleCrash)
        reward = r(5);
        disp("Obstacle crash");
        terminal = true;
    end
    
end