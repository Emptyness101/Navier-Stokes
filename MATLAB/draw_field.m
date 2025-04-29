filename = 'Fields/Velocity.txt';
fid = fopen(filename, 'r');
rawText = fscanf(fid, '%c');
fclose(fid);

tokens = regexp(rawText, '\{([-\d\.eE]+),([-\d\.eE]+)\}', 'tokens');
coords = cellfun(@(c) [str2double(c{1}), str2double(c{2})], tokens, 'UniformOutput', false);
coords = vertcat(coords{:});

rows = 100;
cols = 100; 

[X, Y] = meshgrid(1:cols, 1:rows);

U = zeros(rows, cols);
V = zeros(rows, cols);

for r = 1:rows
    for c = 1:cols
        index = (r-1)*cols + c; 
        if index <= length(coords)
            U(r,c) = coords(index, 1); 
            V(r,c) = coords(index, 2); 
        end
    end
end

figure;
hold on; 

quiver(X, Y, U, V, 0.7, 'AutoScale', 'off', 'LineWidth', 2); 

zeroIndices = (U == 0 & V == 0);
plot(X(zeroIndices), Y(zeroIndices), 'ko', 'MarkerFaceColor', 'k', 'MarkerSize', 0.5);

xlabel('X');
ylabel('Y');
grid on;
axis equal;

set(gca, 'YDir', 'reverse');

hold off;


