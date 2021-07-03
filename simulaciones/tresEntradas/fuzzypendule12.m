%La funcion devuelve los parametros del optitank.fis, x y p. A la funcion se le debe indicar:
%dtol:(tolerancia de convergencia)
%d0:(longitud del paso inicial).
%simetria: variable booleana en la cual se indica si se desea aplicar
%simetría o no.


function [optitank x p tiempo] = fuzzypendule12(dtol,d0,simetria,time)

if nargin ~= 4
     error('Se requieren tres argumentos: dtol, d0 y simetría');
end
 
if dtol > d0,
     error('Condicion no permitida: dtol > d0');
end

if (d0 >= 1)||(d0<=-1),
     error('Condicion no permitida: d0 e (-1,1)');
end
if (simetria ~= 1)&&(simetria ~=0)&&(simetria ~=true)&&(simetria ~=false),
     error('"simetría" debe ser "true" o "false"');
end
if (time >= 100)||(time<=0),
     error('Condicion no permitida: time>0)');
end

global pendulo; %declarar % global tanque en command window


%Lectura inicial del .fis y Simulación Inicial 
pendulo=readfis('C:\Users\brand\OneDrive\Escritorio\tesis\simulacion\simu3\posAngv2unicamf');

[optitank x p tiempo]=optimizarrapida(dtol,d0,simetria,time);
end


