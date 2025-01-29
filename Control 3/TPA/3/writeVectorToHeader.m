function writeVectorToHeader(vector, filename, array_name)
    % Function to write a MATLAB matrix to a .h file as a C array.
    % Inputs:
    %   matrix      - The matrix to export
    %   filename    - Name of the output .h file (e.g., 'matrix_data.h')
    %   array_name  - Name of the C array (e.g., 'my_matrix')
    
    fid = fopen(strcat('codigo/include/', filename), 'w');
    
    if fid == -1
        error('Error opening the file: %s', filename);
    end
    
    guard = upper(strrep(filename, '.', '_'));
    fprintf(fid, '#ifndef %s\n#define %s\n\n', guard, guard);
    
    vector_length = length(vector);
    fprintf(fid, 'const float %s[%d] = {', array_name, vector_length);
    
    for i = 1:vector_length
        if i < vector_length
            fprintf(fid, '%g, ', vector(i));
        else
            fprintf(fid, '%g', vector(i));
        end
    end
    
    fprintf(fid, '};\n\n');
    
    fprintf(fid, '#endif // %s\n', guard);
    
    fclose(fid);
    fprintf('Matriz exportada desde %s hasta %s.\n', filename, array_name);
end
