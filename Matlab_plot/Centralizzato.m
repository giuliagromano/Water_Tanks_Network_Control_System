% Legge i dati dal file di testo
data = readmatrix('Dati_Centralizzato_Hacker.txt');
%data = readmatrix('Dati_Centralizzato.txt');
%data = readmatrix('Dati_Centralizzato_Riferimento_Costante.txt');

% Separa i dati nei vettori appropriati
livelloM = data(1, :);
livello1 = data(2, :);
livello2 = data(3, :);
Pump1 = data(4, :);
Pump2 = data(5, :);

% Crea un vettore per l'asse x (tempo o indice)
x = 1:length(livelloM);

% Definisce i colori per i grafici
colorM = [0, 0.4470, 0.7410]; % Blu
color1 = [0.8500, 0.3250, 0.0980]; % Arancione
color2 = [0.9290, 0.6940, 0.1250]; % Giallo
colorP1 = [0.4940, 0.1840, 0.5560]; % Viola
colorP2 = [0.4660, 0.6740, 0.1880]; % Verde

% Prima figura: Livelli
figure;

% Crea il primo grafico
subplot(3, 1, 1); % Subplot 1
plot(x, livelloM, 'LineWidth', 1.5, 'Color', colorM);
title('Master');
xlabel('Time');
ylabel('Water Level');
yticks([0 1 2 3]); % Mostra solo 0, 1, 2, 3 sull'asse y
ylim([0 3]); % Imposta l'intervallo dell'asse y da 0 a 3
grid on; % Aggiunge la griglia

% Crea il secondo grafico
subplot(3, 1, 2); % Subplot 2
plot(x, livello1, 'LineWidth', 1.5, 'Color', color1);
title('Slave 1');
xlabel('Time');
ylabel('Water Level');
yticks([0 1 2 3]); % Mostra solo 0, 1, 2, 3 sull'asse y
ylim([0 3]); % Imposta l'intervallo dell'asse y da 0 a 3
grid on; % Aggiunge la griglia

% Crea il terzo grafico
subplot(3, 1, 3); % Subplot 3
plot(x, livello2, 'LineWidth', 1.5, 'Color', color2);
title('Slave 2');
xlabel('Time');
ylabel('Water Level');
yticks([0 1 2 3]); % Mostra solo 0, 1, 2, 3 sull'asse y
ylim([0 3]); % Imposta l'intervallo dell'asse y da 0 a 3
grid on; % Aggiunge la griglia

% Aggiusta le posizioni dei subplots
subplot(3, 1, 1);
pos1 = get(gca, 'Position');
subplot(3, 1, 2);
pos2 = get(gca, 'Position');
subplot(3, 1, 3);
pos3 = get(gca, 'Position');

pos1(2) = pos1(2) - 0.03;
pos2(2) = pos2(2) - 0.03;
pos3(2) = pos3(2) - 0.03;

set(gca, 'Position', pos3);
subplot(3, 1, 2);
set(gca, 'Position', pos2);
subplot(3, 1, 1);
set(gca, 'Position', pos1);

% Seconda figura: Pompe
figure;

% Crea il primo grafico
subplot(2, 1, 1); % Subplot 1
plot(x, Pump1, 'LineWidth', 1.5, 'Color', colorP1);
title('Pump 1');
xlabel('Time');
ylabel('Operating');
yticks([0 1]); % Mostra solo 0 e 1 sull'asse y
grid on; % Aggiunge la griglia

% Crea il secondo grafico
subplot(2, 1, 2); % Subplot 2
plot(x, Pump2, 'LineWidth', 1.5, 'Color', colorP2);
title('Pump 2');
xlabel('Time');
ylabel('Operating');
yticks([0 1]); % Mostra solo 0 e 1 sull'asse y
grid on; % Aggiunge la griglia