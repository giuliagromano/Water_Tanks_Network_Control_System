% Parametri iniziali
a21 = 1; % Coefficiente di controllo
epsilon = 0.4; % Passo del consenso
timesteps = 100; % Numero di iterazioni

% Definisce i colori per i grafici
colorx1 = [0, 0.4470, 0.7410]; % Blu
colorx2 = [0.8500, 0.3250, 0.0980]; % Arancione
colormedia = [0.9290, 0.6940, 0.1250]; % Giallo
colorz1 = [0.4940, 0.1840, 0.5560]; % Viola
colorz2 = [0.4660, 0.6740, 0.1880]; % Verde
colordelta21 = [0.6350, 0.0780, 0.1840]; % Rosso
colordelta12 = [0.3010, 0.7450, 0.9330]; % Ciano

% Array per memorizzare i risultati
x1_values = zeros(1, timesteps);
x2_values = zeros(1, timesteps);
delta21_values = zeros(1, timesteps);
delta21_values_pre = zeros(1,timesteps);
z1_values = zeros(1, timesteps);
z2_values = zeros(1, timesteps);

for i=1:24
    z1_values(1,i)=1;
end
for i=25:50
    z1_values(1,i)=2;
end
for i=51:100
    z1_values(1,i)=1;
end

for i=1:15
    z2_values(1,i)=2
end
for i=16:65
    z2_values(1,i)=1;
end
for i=66:100
    z2_values(1,i)=2;
end

media = (z1_values + z2_values)/2;

delta21_values(1,1) = 0; % Variabile di controllo iniziale tra nodo 2 e nodo 1
x1_values(1,1) = z1_values(1,1); % Livello iniziale d'acqua nel nodo 1
x2_values(1,1) = z2_values(1,1); % Livello iniziale d'acqua nel nodo 2

% Loop temporale
for k = 1:timesteps-1
    % Aggiorna la variabile di controllo
    if k < 40 || k > 70
        delta21_values(k+1) = delta21_values(k) - (x2_values(k) - x1_values(k));
    else
        delta21_values(k+1) = 0;
    end
    
    % Algoritmo del consenso
    x1_values(k+1) = epsilon * (-delta21_values(k+1)) + z1_values(k+1);
    x2_values(k+1) = epsilon * delta21_values(k+1) + z2_values(k+1);
end

% Visualizza le stime
figure;
plot(1:timesteps, x1_values, 'Color', colorx1, 'LineWidth', 1.5); % Nodo 1
hold on;
plot(1:timesteps, x2_values, 'Color', colorx2, 'LineWidth', 1.5); % Nodo 2
plot(1:timesteps, media, 'Color', colormedia, 'LineWidth', 1.5); % Media
hold off;
xlabel('Time');
ylabel('Estimated Values and Average');
legend('Node 1', 'Node 2', 'Average');
title('Estimated Values in Robust Control Algorithm');
grid on;

% Visualizza le variabili di controllo delta
figure;
plot(1:timesteps, delta21_values, 'Color', colordelta21, 'LineWidth', 1.5); % Delta21
hold on;
plot(1:timesteps, -delta21_values, 'Color', colordelta12, 'LineWidth', 1.5); % Delta12
hold off;
xlabel('Time');
ylabel('\delta_{21} and \delta_{12}');
legend('\delta_{21}', '\delta_{12}');
title('Control Variable \delta in Robust Control Algorithm');
grid on;

% Visualizza i valori di z
figure;
plot(1:timesteps, z1_values, 'Color', colorz1, 'LineWidth', 1.5); % z1
hold on;
plot(1:timesteps, z2_values, 'Color', colorz2, 'LineWidth', 1.5); % z2
hold off;
xlabel('Time');
ylabel('Water Sensor Level');
yticks([0 1 2 3]); % Mostra solo 0, 1, 2, 3 sull'asse y
ylim([0 3]); % Imposta l'intervallo dell'asse y da 0 a 3
legend('z1', 'z2');
title('Water Sensor Level in Robust Control Algorithm');
grid on;
