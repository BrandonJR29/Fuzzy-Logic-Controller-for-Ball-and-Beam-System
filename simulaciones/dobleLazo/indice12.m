function [ v0 ] = indice12(pendulo,simetria)
%ESTA FUNCIÓN FORMA EL VECTOR V0 PARA EL ALGORITMO DE OPTIMIZACIÓN, A
%PARTIR DE LOS INDICES ACTUALES DE LAS FUNCIONES DE PERTENENCIA
%   Detailed explanation goes here
N_IN=length(pendulo.input);
v0=[];
for i=1:N_IN
    if (simetria)
        if rem(length(pendulo.input(i).mf),2)==0 % Si el número de las FP son pares:
            N_FP=length(pendulo.input(i).mf)/2;
        else %Si el número de F.P es impar:
            N_FP=floor(length(pendulo.input(i).mf)/2)+rem(length(pendulo.input(i).mf),2); 
        end
    else
        N_FP=length(pendulo.input(i).mf);
    end
    for j=1:N_FP
            v0=horzcat(v0,pendulo.input(i).mf(j).params(5:7)); %Se toman los índices (nT, n1 y n2) de las F.P
    end
    
    
end

end

