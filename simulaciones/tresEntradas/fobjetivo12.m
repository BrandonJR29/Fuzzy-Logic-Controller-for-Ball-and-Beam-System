function [ fx ] = fobjetivo12(u, ess, salida, valido, Px, time)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
if valido

    Up=max(u);
    Ud=min(u);
%SE CALCULA LA FUNCIÓN OBJETIVO (ERROR CUADRÁTICO, ERROR EN ESTADO ESTACIONARIO Y SOBREPICO)

%--------------------------------------------------------------------------
%Error cuadrático:            
    f1=sumsqr(ess)/length(ess);  

%--------------------------------------------------------------------------
%Error en estado estacionario;

    f2=abs(Up-salida.signals.values(round((length(salida.signals.values)/2*3/4))))+abs(Ud-salida.signals.values(round((length(salida.signals.values)*3/4))));

%--------------------------------------------------------------------------
%Sobrepico:

    %if max(salida.signals.values)>Up %Se comprueba si existe un sobrepico.
    %    sobrepico_up=max(salida.signals.values); %Se determina el sobre pico.
    %else
    %    sobrepico_up=Up; %Si no hay sobrepico, se iguala a la referencia para anular el cálculo en la función objetivo.
    %end
    if min(salida.signals.values(find(salida.signals.values<Ud)))<Ud %Sobrepico en el vaciado.
        sobrepico_ud=min(salida.signals.values(find(salida.signals.values<Ud)));
    else
        sobrepico_ud=Ud;
    end
    %f3=abs(sobrepico_up-Up)+abs(sobrepico_ud-Ud);
    f3=abs(sobrepico_ud-Ud);
%--------------------------------------------------------------------------
%Tiempo de establecimiento:
    w=2; %variable axuliar para el cálculo del ts.
    if max(salida.signals.values)<Ud %sistema de 2do orden o con sobrepico
         z=find((salida.signals.values<Ud+0.05)&(salida.signals.values>Ud-0.05)); %Se busca en "salida" los valores que esten entorno al 5% de la referencia.
         for i=length(z):-1:2 %Se busca el la estabilidad entorno al +/-5% de la referencia (Se ignoran los cruces por la referencia que generen sobrepico por encima del +/-5%
        if z(i)~=z(i-1)+1
            w=i;
        end
         end
         ts=salida.time(z(w)); %Se detemrina el tiempo de establecimiento.
    else
         z=find(salida.signals.values<0.05);
         if isempty(z)
            ts=time; %Si no alcanza el criterio del 5%, se penaliza la funcion asignando el máximo valor el tiempo de simulación.
            else
            ts=salida.time(min(z)); 
         end   
    end
    f4=ts/time;%normalizado
%--------------------------------------------------------------------------
%Tiempo de alza:
    if max(salida.signals.values)<Ud
        ta=salida.time(find(salida.signals.values<Ud, 1 ));
        f5=ta/time; %normalizado
    else
        f5=0; 
    end

    fx=0.5*f1+0.25*f2+0.15*f3+0.05*f4+0.05*f5+Px; 
else
    fx=Px;
end
end

