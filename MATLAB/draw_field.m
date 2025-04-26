% Откроем файл
filename = 'Fields/Velocity.txt';
fid = fopen(filename, 'r');
rawText = fscanf(fid, '%c');
fclose(fid);

% Извлекаем все пары чисел
tokens = regexp(rawText, '\{([-\d\.eE]+),([-\d\.eE]+)\}', 'tokens');
coords = cellfun(@(c) [str2double(c{1}), str2double(c{2})], tokens, 'UniformOutput', false);
coords = vertcat(coords{:});

% Размеры сетки (устанавливаем нужные размеры)
rows = 100; % Установите нужное количество строк
cols = 100; % Установите нужное количество столбцов

% Преобразуем координаты в сетку
[X, Y] = meshgrid(1:cols, 1:rows);

% Для каждого узла сетки извлекаем значения векторов скорости
U = zeros(rows, cols);
V = zeros(rows, cols);

% Заполняем матрицы скорости
for r = 1:rows
    for c = 1:cols
        index = (r-1)*cols + c; % индекс для каждой ячейки
        if index <= length(coords)
            U(r,c) = coords(index, 1); % компонент скорости по оси X
            V(r,c) = coords(index, 2); % компонент скорости по оси Y
        end
    end
end

% Рисуем векторное поле
figure;
hold on; % чтобы рисовать на одном графике

% Отрисовываем стрелки для ненулевых векторов
quiver(X, Y, U, V, 0.7, 'AutoScale', 'off', 'LineWidth', 2); % Убираем автоматическое масштабирование и увеличиваем толщину стрелок

% Отображаем нулевые векторы как маленькие точки
zeroIndices = (U == 0 & V == 0); % Нахождение нулевых векторов
plot(X(zeroIndices), Y(zeroIndices), 'ko', 'MarkerFaceColor', 'k', 'MarkerSize', 0.5); % 'ko' — это чёрные точки, уменьшаем размер

% Настройки графика
xlabel('X');
ylabel('Y');
title('Векторное поле скорости (нулевые как маленькие точки)');
grid on;
axis equal;

% Инвертируем ось Y
set(gca, 'YDir', 'reverse');

hold off;


