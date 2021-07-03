function [valido,Px] = penalizar12(pendulo,x,v,simetria)
%Se aplican las restricciones inherentes a las F.P y solapamientos.
valido=true;

%Se calcula el número de entradas:
N_IN=length(pendulo.input);

%Se calcula la dimensión de la matriz de restricciones
dim=0;
for i=1:N_IN
dim=max(dim,length(pendulo.input(i).mf));
end
if (simetria)
    if rem(dim,2)==0 %Si es par:
        dim=dim/2*4-2;
    else %Si es impar:
        dim=(floor(dim/2)+rem(dim,2))*4-4;
    end
else %Si no se aplica simetria:
    dim=dim*4-4;
end

%Se inicializa la matriz "m":
m=ones(N_IN,dim);

% Se arma la matriz de restricciones:
k=1;
for i=1:N_IN
    N_FP=length(pendulo.input(i).mf); %Número totales de FP de la entrada"i".
    if (simetria)
        if rem(N_FP,2)==0 %Si es par:
            N_V_FP=N_FP/2*4-2;
        else %Si es impar:
            N_V_FP=(floor(N_FP/2)+rem(N_FP,2))*4-4;
        end
    else %Si no se aplica simetria:
         N_V_FP=N_FP*4-4; %Número totales de vértices de las FP de la entrada"i".
    end
    
    for j=1:N_V_FP
        m(i,j)=x(k);
        k=k+1;
    end
end


%-------------------------------------------------------------------------%
%REGLA # 1 RESTRICCIONES PROPIAS DE LA FP TRAPEZOIDAL: 

%Caso 1: b>a  
for i=1:N_IN
    N_FP=length(pendulo.input(i).mf);
    if (simetria)
        if rem(N_FP,2)==0 %Si es par:
            N_FP=N_FP/2;
        else %Si es impar:
            N_FP=(floor(N_FP/2)+rem(N_FP,2));
        end
    end    
  
    for j=0:(N_FP-2)
        if m(i,3+4*j)>=m(i,4+4*j) %Si a>=b, entonces:
            valido=false;
        end 
    end
end

%Caso 2: c>=b  

for i=1:(N_IN)
    N_FP=length(pendulo.input(i).mf);
    if (simetria)
        if rem(N_FP,2)==0 %Si es par:
            N_FP=N_FP/2+1;
        else %Si es impar:
            N_FP=(floor(N_FP/2)+rem(N_FP,2));
        end
    end    
    
    for j=0:(N_FP-3) 
        if m(i,4+4*j)>m(i,5+4*j) %Si b>c, entonces:
            valido=false;
        end
    end
end

%Caso 3: d>c
for i=1:(N_IN)
    N_FP=length(pendulo.input(i).mf);
    if (simetria)
        if rem(N_FP,2)==0 %Si es par:
            N_FP=N_FP/2+1;
        else %Si es impar:
            N_FP=(floor(N_FP/2)+rem(N_FP,2));
        end
    end    
    
    for j=0:(N_FP-2)
        if m(i,1+4*j)>=m(i,2+4*j) %Si c>=d, entonces:
            valido=false;
        end    
    end    
end

P1=0;
if valido==false
    P1=P1+100;
end

%-------------------------------------------------------------------------%
%REGLA # 2 GARANTIZAR SOLAPAMIENTO ENTRE FP CONTIGUAS DE LA ENTRADA "i":
%Vértice "d" de la F.P "j" > "a" de la F.P (j+1) son iguales,

P2=0;
for i=1:N_IN
    N_FP=length(pendulo.input(i).mf);
    if (simetria)
        if rem(N_FP,2)==0 %Si es par:
            N_FP=N_FP/2;
        else %Si es impar:
            N_FP=(floor(N_FP/2)+rem(N_FP,2));
        end
    end        
    
    for j=0:(N_FP-2)
        a=m(i,3+4*j);
        d=m(i,2+4*j);
        P2=P2+100*max(a-d,0);%Función de penalización 1
    end        
            
end
    

%-------------------------------------------------------------------------%
%REGLA # 3 EVITAR PERTENENCIA TOTAL:
%Vértice "c" de la F.P "j" < vértice "b" de la F.P (j+1)

P3=0;
for i=1:N_IN
    N_FP=length(pendulo.input(i).mf);
    if (simetria)
        if rem(N_FP,2)==0 %Si es par:
            N_FP=N_FP/2;
        else %Si es impar:
            N_FP=(floor(N_FP/2)+rem(N_FP,2));
        end
    end      
    
    for j=0:(N_FP-2)
        c=m(i,1+4*j);
        b=m(i,4+4*j);
        P3=P3+100*max(c-b,0);%Función de penalización 2       
    end

end

%-------------------------------------------------------------------------%
%REGLA # 4 EVITAR MÚLTIPLE SOLAPAMIENTO.
%Vértice "d" de la F.P "j" < vértice "a" de la F.P (j+2)

P4=0;
for i=1:N_IN
    N_FP=length(pendulo.input(i).mf);
    if (simetria)
        if rem(N_FP,2)==0 %Si es par:
            N_FP=N_FP/2;
        else %Si es impar:
            N_FP=(floor(N_FP/2)+rem(N_FP,2));
        end
    end      
    
    for j=0:(N_FP-3)
        a=m(i,7+4*j);
        d=m(i,2+4*j);
        P4=P4+100*max(d-a,0);%Función de penalización 2 
    end
end

%-------------------------------------------------------------------------%
%REGLA # 5 RESTRICCIÓN DE LOS EXTREMOS
%El vertice "c" de la 1ra F.P >=-1 y el vértice "b" de la última F.P >=1
P5=0;
for i=1:N_IN
    c=m(i,1);
    P5=P5+100*max(-(1+c),0);

    N_FP=length(pendulo.input(i).mf);
    if (simetria)
        if rem(N_FP,2)==0 %Si es par:
            N_V_FP=N_FP/2*4-2;
             c=m(i,N_V_FP-1);
             P5=P5+100*max(c,0);
             d=m(i,N_V_FP);
             P5=P5+100*max(d-1,0);                 
        else %Si es impar:
            N_V_FP=(floor(N_FP/2)+rem(N_FP,2))*4-4;
            d=m(i,N_V_FP-2);
            P5=P5+10*max(d,0);
            a=m(i,N_V_FP-1);
            P5=P5+100*max(-(1+a),0);
            b=m(i,N_V_FP);
            P5=P5+100*max(b,0);

        end
    else %Si no se aplica simetria:
         N_V_FP=N_FP*4-4; %Número totales de vértices de las FP de la entrada"i".
         b=m(i,N_V_FP);
         P5=P5+100*max(b-1,0);

    end     


end
if P5~=0
    valido=false;
end
%-------------------------------------------------------------------------%
%REGLA # 6 RESTRICIONES DE LOS ÍNDICES
offset=0;
for i=1:(N_IN)
    N_FP=length(pendulo.input(i).mf);
    if (simetria)
        if rem(N_FP,2)==0 %Si es par:
            N_FP=N_FP/2;
        else %Si es impar:
            N_FP=(floor(N_FP/2)+rem(N_FP,2));
        end
    end
    
    for j=0:N_FP-1
        
        if v(offset+1+3*j)>=1/v(offset+2+3*j) %nT<1/n1
            valido=false;
        end
        if (v(offset+1+3*j)<0 || v(offset+1+3*j)>=1) %0<=nT<1
            valido=false;
        end
        if v(offset+2+3*j)<=0 %n1>0
            valido=false;
        end        
        if v(offset+3+3*j)<=0 %n2>0
            valido=false;
        end      
        
    end
    offset=offset+N_FP*3;
    
end

%-------------------------------------------------------------------------%
if valido==false
    P6=100;
else
    P6=0;
end
%-------------------------------------------------------------------------%
Px=P1+P2+P3+P4+P5+P6; %Función de penalización   
end

