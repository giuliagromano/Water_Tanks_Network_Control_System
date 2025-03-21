% Legge i dati dal file di testo
data = readmatrix('Dati_Dynamic_Consensus_3_Nodi_FaultyNet.txt');

% Separa i dati nei tre vettori
x1 = data(1, :);
x2 = data(2, :);
x3 = data(3, :);
% z1 = data(4, :);
% z2 = data(5, :);
% z3 = data(6, :);
% 
% % Calcola la media
% media = (z1 + z2 + z3) / 3;

% Crea un vettore per l'asse x (tempo o indice)
x = 1:length(x1);

% Definisce i colori per i grafici
colorx1 = [0, 0.4470, 0.7410]; % Blu
colormedia = [0.8500, 0.3250, 0.0980]; % Arancione
colorx3 = [0.6350, 0.0780, 0.1840]; % Rosso
colorx2 = [0.9290, 0.6940, 0.1250]; % Giallo
colorz1 = [0.4940, 0.1840, 0.5560]; % Viola
colorz2 = [0.4660, 0.6740, 0.1880]; % Verde
colorz3 = [0.3010, 0.7450, 0.9330]; % Ciano

% Crea il primo grafico
figure('Name', 'Estimated Values in Dynamic Consensus with faulty node', 'NumberTitle', 'off');
plot(x, x1, 'Color', colorx1, 'LineWidth', 1.5, 'MarkerSize', 6, 'DisplayName', 'x1');
hold on;
plot(x, x2, 'Color', colorx2, 'LineWidth', 1.5, 'MarkerSize', 6, 'DisplayName', 'x2');
plot(x, x3, 'Color', colorx3, 'LineWidth', 1.5, 'MarkerSize', 6, 'DisplayName', 'x3');
title('Estimated Values in Dynamic Consensus for 3 Nodes', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Time', 'FontSize', 12);
ylabel('Estimated Values and Average', 'FontSize', 12);
legend('Node 1', 'Node 2', 'Node 3');
grid on;
set(gca, 'FontSize', 12);

% % Crea il secondo grafico
% figure('Name', 'Water Sensor Level in Dynamic Consensus for 3 Nodes', 'NumberTitle', 'off');
% plot(x, z1, 'Color', colorz1, 'LineWidth', 1.5, 'MarkerSize', 6, 'DisplayName', 'z1');
% hold on;
% plot(x, z2, 'Color', colorz2, 'LineWidth', 1.5, 'MarkerSize', 6, 'DisplayName', 'z2');
% plot(x, z3, 'Color', colorz3, 'LineWidth', 1.5, 'MarkerSize', 6, 'DisplayName', 'z3');
% title('Water Sensor Level in Dynamic Consensus for 3 Nodes', 'FontSize', 14, 'FontWeight', 'bold');
% xlabel('Time', 'FontSize', 12);
% ylabel('Water Sensor Level', 'FontSize', 12);
% yticks([0 1 2 3]); % Mostra solo 0, 1, 2, 3 sull'asse y
% ylim([0 3]); % Imposta l'intervallo dell'asse y da 0 a 3
% legend('Location', 'best', 'FontSize', 10);
% grid on;
% set(gca, 'FontSize', 12);

% Imposta le figure per avere aspetto coerente
set(gcf, 'Color', 'w'); % Sfondo bianco per la figura