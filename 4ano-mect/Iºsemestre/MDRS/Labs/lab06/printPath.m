function printPath(path, sep)
    aux = '';
    for i = 1:length(path)
        fprintf('%s', aux);
           fprintf('%d', path(i))
        aux = sep;
    end
end