function [ x0 ] = vertices12(pendulo,simetria)
%ESTA FUNCIÓN FORMA EL VECTOR X0 PARA EL ALGORITMO DE OPTIMIZACIÓN, A
%PARTIR DE LOS VÉRTICES ACTUALES DE LAS FUNCIONES DE PERTENENCIA
%   Detailed explanation goes here
N_IN=length(pendulo.input);
x0=[];
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
        if (j==1)
            x0=horzcat(x0,pendulo.input(i).mf(j).params(3:4)); %Se considera la primera F.P trapezoidal abierta y se toman los vértices "c" y "d" únicamente.
        else
            if (j==N_FP)
                x0=horzcat(x0,pendulo.input(i).mf(j).params(1:2));  %Se considera la última F.P trapezoidal abierta y se toman los vértices "a" y "b" únicamente.
            else
                x0=horzcat(x0,pendulo.input(i).mf(j).params(1:4)); %Se incluyen todos los vértices pra cualquier otra F.P 
            end
        end
    end
    
    
end

end

