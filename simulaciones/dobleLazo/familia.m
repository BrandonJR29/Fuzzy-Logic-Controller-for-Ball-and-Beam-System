function y = familia(x, params)

%Familia de Funciones de pertenencia (Trapecio, Triangulo y Curva polinomica)
%   familia(x, params) devuelve un vector el cual es la funcion de pertenencia evaluada en X  
%   params = [a b c d nT n1 n2] es un vector de 7 elementos que determina
%                           los puntos de la funcion de pertenencia familia
%   Siempre se requiere a <= b <= c <=d.
%   nT: Indice Trapecio. nT pertenece a R. 0<=nT<1.
%   n1: Indice Movimiento Recta. n1 pertenece a R. 0<n1<=K1. K1 es la
%       cantidad maxima de variaciones que se desea de la recta en la
%       funcion de pertenencia
%   n2: Indice Expansion-Contraccion. n2 pertenence a R. 0<n2<=1 Expansion, 
%                                                     1<=n2<=K2 Contraccion.
%                                 K2 pertenece a R y depende de la maxima
%                                 contraccion que se desea en la funcion de
%                                 pertenencia.
%
%Ejemplo:
%       x = (0:0.001:10);
%       y=familia(x, [3 4 4 5 0 1 1]);
%       plot(x,y)
%       y=familia(x, [3 4 4 5 0.2 1 1]);
%       plot(x,y)

%a=4;  %b=6;  c=6;  d=8;  nT=0; n1=1; n2=1;

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
