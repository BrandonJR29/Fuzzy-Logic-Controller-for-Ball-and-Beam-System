function [ xout ] = desnormalizar12(pendulo,xin,simetria)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
xout=xin';
min=-1;
max=1;
N_IN=length(pendulo.input);
offset=0;

for i=1:N_IN
    N_FP=length(pendulo.input(i).mf); %Se obtiene el número de F.P de la entrada (i).
    if (simetria==true)
        if rem(N_FP,2)==0 % Si el número de FP es par:
            N_V_FP=N_FP/2*4-2;
        else %Si el número de FP es impar:
            N_V_FP=(floor(N_FP/2)+rem(N_FP,2))*4-4;
        end
    else
        N_V_FP=N_FP*4-4;
    end
    if (pendulo.input(i).range(1)~=min)||(pendulo.input(i).range(2)~=max)
        for j=offset+1:offset+N_V_FP
            xout(j)=(xout(j)-min)/(max-min); %Se normaliza
            xout(j)=xout(j)*(pendulo.input(i).range(2)-pendulo.input(i).range(1))+pendulo.input(i).range(1); %Se escala al rango real indicado en la matriz de normalización.
        end
    end
    offset=offset+N_V_FP;
end

xout=xout';

end

