% Legge i dati dal file di testo
data = readmatrix('Dati_Weighted_Dynamic_Consensus.txt');

% Definisce i colori per i grafici
colorx1 = [0, 0.4470, 0.7410]; % Blu
colorx2 = [0.8500, 0.3250, 0.0980]; % Arancione
colorx3 = [0.4940, 0.1840, 0.5560];   % Viola
colormedia1 = [0.9290, 0.6940, 0.1250]; % Giallo
colormedia2 = [0.4660, 0.6740, 0.1880]; % Verde
colorz1 = [0.4940, 0.1840, 0.5560]; % Viola
colorz2 = [0.4660, 0.6740, 0.1880]; % Verde
colorz3 = [0.8500, 0.3250, 0.0980];   % Arancione

% Separa i dati nei tre vettori
x1 = data(1, :);
x2 = data(2, :);
x3 = data(3, :);
z1=  data(4, :);
z2=  data(5, :);
z3=  data(6, :);

% Crea un vettore per l'asse x (tempo o indice)
x = 1:length(x1);

mediap=(4*z1+3*z2+2*z3)/9;
media=(z1+z2+z3)/3;

% Visualizza le stime
figure;
plot(x, x1, 'Color', colorx1, 'LineWidth', 1.5); % Nodo 1
hold on;
plot(x, x2, 'Color', colorx2, 'LineWidth', 1.5); % Nodo 2
plot(x, x3, 'Color', colorx3, 'LineWidth', 1.5); % Nodo 3
plot(x, media, 'Color', colormedia1, 'LineWidth', 1.5); % Media 1
plot(x, mediap, 'Color', colormedia2, 'LineWidth', 1.5); % Media 2
hold off;
xlabel('Time');
ylabel('Estimated Values and Averages');
legend('Node 1', 'Node 2', 'Node 3', 'Average', 'Weighted Average');
title('Estimated Values in Weighted Dynamic Consensus Algorithm');
grid on;

% Visualizza i valori di z
figure;
plot(x, z1, 'Color', colorz1, 'LineWidth', 1.5); % z1
hold on;
plot(x, z2, 'Color', colorz2, 'LineWidth', 1.5); % z2
plot(x, z3, 'Color', colorz3, 'LineWidth', 1.5); % z3
hold off;
xlabel('Time');
ylabel('Water Sensor Level');
yticks([0 1 2 3]); % Mostra solo 0, 1, 2, 3 sull'asse y
ylim([0 3]); % Imposta l'intervallo dell'asse y da 0 a 3
legend('z1', 'z2', 'z3');
title('Water Sensor Level in Weighted Dynamic Consensus Algorithm');
grid on;