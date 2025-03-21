% Parametri iniziali
a21 = 1; % Coefficiente di controllo
a23 = 1;
epsilon = 0.4; % Passo del consenso
timesteps = 100; % Numero di iterazioni

% Array per memorizzare i risultatix1_values = zeros(1, timesteps);
x1_values = zeros(1, timesteps);
x2_values = zeros(1, timesteps);
x3_values = zeros(1,timesteps);
z1_values = zeros(1, timesteps);
z2_values = zeros(1, timesteps);
z3_values = zeros(1, timesteps);


% for i=1:24
%     z1_values(1,i)=1;% end
% for i=25:50%     z1_values(1,i)=2;
% end% for i=51:100
%     z1_values(1,i)=1;% end
% % for i=1:15
%     z2_values(1,i)=2% end
% for i=16:65%     z2_values(1,i)=1;
% end% for i=66:100
%     z2_values(1,i)=2;% end
% % for i=1:34
%     z3_values(1,i)=3;% end
% for i=35:53%     z3_values(1,i)=2;
% end% for i=54:80
%     z3_values(1,i)=1;% end
% for i=81:100%     z3_values(1,i)=2;
% end

for i=1:24    
    z1_values(1,i)=1;
end
for i=25:50
    z1_values(1,i)=2;
end
for i=51:100
    z1_values(1,i)=1;
end
for i=1:24
    z2_values(1,i)=2;
end
for i=25:50    
    z2_values(1,i)=1;
end
for i=51:100
    z2_values(1,i)=2;
end
for i=1:24
    z3_values(1,i)=3;
end
for i=25:50    
    z3_values(1,i)=2;
end
for i=51:100
    z3_values(1,i)=1;
end

media = (z1_values + z2_values + z3_values)/3;

x1_values(1,1) = z1_values(1,1); % Livello iniziale d'acqua nel nodo 1
x2_values(1,1) = z2_values(1,1); % Livello iniziale d'acqua nel nodo 2
x3_values(1,1) = z3_values(1,1); % Livello iniziale d'acqua nel nodo 2

% Loop temporale
for k = 1:timesteps-1

    % Algoritmo del consenso    
    x1_values(k+1) = x1_values(k) - epsilon * (x1_values(k) - x2_values(k)) + z1_values(k+1) - z1_values(k);
    x2_values(k+1) = x2_values(k) - epsilon * ((x2_values(k) - x1_values(k)) + (x2_values(k) - x3_values(k))) + z2_values(k+1) - z2_values(k);   
    x3_values(k+1) = x3_values(k) - epsilon * (x3_values(k) - x2_values(k)) + z3_values(k+1) - z3_values(k);   
end

% Visualizza i livelli d'acqua
figure;
plot(1:timesteps, x1_values, 'r', 1:timesteps, x2_values, 'b', 1:timesteps, x3_values, 'y', 1:timesteps, media, 'g');
xlabel('Time step');
ylabel('Water Level');
legend('Node 1', 'Node 2', 'Node 3', 'Average');
title('Water Levels with Robust Control Algorithm');

% Visualizza i valori di z
figure;
plot(1:timesteps, z1_values, 'r');
hold on
plot(1:timesteps, z2_values, 'b');
hold on
plot(1:timesteps, z3_values, 'y');
xlabel('Time step');
ylabel('z values');
yticks([0 1 2 3 4]); % Mostra solo 0, 1, 2, 3 sull'asse y
ylim([0 4]); % Imposta l'intervallo dell'asse y da 0 a 3
legend('Node 1', 'Node 2', 'Node 3');
title('z values over time');