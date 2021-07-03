function y = unicamf(x, params)

%Representación Única de Funciones de Pertenencia (Trapezoidales, Triangulares y tipo Curvas polinómicas)
%   unicamf(x, params) devuelve un vector el cual es la función de pertenencia evaluada en x  
%   params = [a b c d nT n1 n2] es un vector de 7 elementos que determina
%                           los puntos de la función de pertenencia unicamf
%   Siempre se requiere a <= b <= c <=d.
%   nT: Índice Trapecio. nT pertenece a R. 0<=nT<1.
%   n1: Índice Movimiento Recta. n1 pertenece a R. 0<n1<=K1. K1 es la
%       cantidad máxima de variaciones que se desea de la recta en la
%       función de pertenencia
%   n2: Índice Expansión-Contracción. n2 pertenence a R. 0<n2<=1 Expansión, 
%                                                     1<=n2<=K2 Contracción.
%                                 K2 pertenece a R y depende de la máxima
%                                 contracción que se desea en la función de
%                                 pertenencia.
%
%Ejemplo:
%       x = (0:0.001:10);
%       y=unicamf(x, [3 4 4 5 0 1 1]);
%       plot(x,y)
%       y=unicamf(x, [3 4 4 5 0.2 1 1]);
%       plot(x,y)

if nargin ~= 2
     error('Two arguments are required by the MF.');
elseif length(params) ~= 7
     error('The MF needs eight parameters.');
end
 
a = params(1); b = params(2); c = params(3); d = params(4);
nT= params(5); n1= params(6); n2= params(7);

if a > b,
     error('Illegal parameter condition: a > b');
elseif b > c,
     error('Illegal parameter condition: b > c');
elseif c > d,
     error('Illegal parameter condition: c > d');
end

y = zeros(size(x));

%Left:
%x1=(b-(b-a)/n1):incre:(b-nT*(b-a));
index = find((b-(b-a)/n1) <= x & x <= (b-nT*(b-a)));
y(index)=(1+n1*((x(index)-b+nT*(b-a))/(b-a-n1*nT*(b-a)))).^n2;

%Center
%x2=(b-nT*(b-a)):incre:(c+nT*(d-c));
index = find((b-nT*(b-a)) <= x & x < (c+nT*(d-c)));
y(index) = ones(size(index));
%f2=1;

%Rigth
%x3=(c+nT*(d-c)):incre:(c+(d-c)/n1);
index = find((c+nT*(d-c)) <= x & x <= (c+(d-c)/n1));
y(index)=(1+n1*((c+nT*(d-c))-x(index))/((d-c-n1*nT*(d-c)))).^n2;
