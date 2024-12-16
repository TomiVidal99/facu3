function writeMatrixToHeader(matrix, filename, array_name)
    % Function to write a MATLAB matrix to a .h file as a C array.
    % Inputs:
    %   matrix      - The matrix to export
    %   filename    - Name of the output .h file (e.g., 'matrix_data.h')
    %   array_name  - Name of the C array (e.g., 'my_matrix')
    
    fid = fopen(filename, 'w');
    
    if fid == -1
        error('Error opening the file: %s', filename);
    end
    
    guard = upper(strrep(filename, '.', '_'));
    fprintf(fid, '#ifndef %s\n#define %s\n\n', guard, guard);
    
    [rows, cols] = size(matrix);
    fprintf(fid, 'const int %s[%d][%d] = {\n', array_name, rows, cols);
    
    for i = 1:rows
        fprintf(fid, '    {');
        for j = 1:cols
            if j < cols
                fprintf(fid, '%g, ', matrix(i, j));
            else
                fprintf(fid, '%g', matrix(i, j));
            end
        end
        if i < rows
            fprintf(fid, '},\n');
        else
            fprintf(fid, '}\n');
        end
    end
    
    fprintf(fid, '};\n\n');
    
    fprintf(fid, '#endif // %s\n', guard);
    
    fclose(fid);
    fprintf('Matrix exported successfully to %s as %s.\n', filename, array_name);
end
