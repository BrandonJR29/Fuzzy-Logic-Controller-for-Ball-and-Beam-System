function [optitank xm p tiempo] = optimizar12(dtol,d0,simetria,time)
%UNTITLED2 Summary of this function goes here
%ESTA FUNCIÓN SE ENCARGA DE REALIZAR LA OPTIMIZACIÓN DEL SISTEMA DIFUSO
%TANQUE, POR EL MÉTODO DE BÚSQUEDA DIRECTA.
%VARIABLES DE ENTRADS:
%dtol1: criterio de parada del método de búsqueda directo.
%d01: es el paso inicial de búsqueda.
tic;
global pendulo;

%SE PREPARA EL VECTOR X0 PARA EL ALGORITMO DE OPTIMIZACIÓN, A PARTIR DE LOS VÉRTICES ACTUALES:
x0=vertices12(pendulo,simetria);

v0=indice12(pendulo,simetria);

%SE NORMALIZA Y ESCALA EL VECTOR PARA QUE TODA FP TRABAJE EN EL RANGO[-1,1]
[x0]=normalizar12(pendulo,x0,simetria);

%SE CALCULA EL ORDEN DEL SISTEMA:
dim=length(v0);

%SE INICIALIZAN LOS PARÁMETROS PARA EL MÉTODO DE BÚSQUE DIRECTA.
xk=x0'; %Vector que contiene los vértices de las F.P.
vk=v0'; %Es el vector inciial que contiene los índices (nT, n1 y n2) de las F.P involucradas en la optimización.
dk=d0;
D=[eye(dim) -1*eye(dim)]; %Matriz base para el dominio de búsqueda.
p=0;
vk1=zeros(dim,2*dim); %Se inicializa el vector vk1 según las dimensiones que corresponden.
fk1=zeros(2*dim,1); %Se inicializa el vector fk1 según las dimensiones que corresponden.

%Primera simulación:
 xk=actualizar12(pendulo,xk,vk,simetria); %Se actualizan los vértices en función de los índices nT, n1 y n2 iniciales.
 [valido,Px]=penalizar12(pendulo,xk',vk',simetria); %Se aplica la función de penalización
 
if valido
             xd=desnormalizar12(pendulo,xk(:,1),simetria); % Se desnormaliza
             pendulo=parametros12(pendulo,xd,vk,simetria); %Se asignan los vértices al archivo .fis
             %sim('C:\Users\Luis\Dropbox\Postgrado\Control Difuso\Tarea 12\Pendulo12AnguloFuzzy',time);
             sim('C:\Users\brand\OneDrive\Escritorio\tesis\simulacion\simu2\fuzzyImpleAjust',time);
             
end
fk=fobjetivo12(u,ess,salida,valido,Px,time); %Se evalua la simulación en la Función objetivo
       
while (dk>dtol) % MIENTRAS QUE EL PASO SEA MAYOR A LA TOLERANCIA, ENTONCES:
        aux=0;
        p=p+1; %Puntero que indica el número de iteraciones.

        %% Se calculan todos los vk+1:        
        for i=1:2*dim
            for j=1:dim
                vk1(j,i)=vk(j,1)+dk*D(j,i);
            end
        end

         %% SE APLICAN LAS RESTRICCIONES Y SE EVALUAN LOS xk+1 PARA OBTENER f(xk+1):
        for i=1:2*dim
            
            xk1=actualizar12(pendulo,xk,vk1(:,i),simetria); %Para cada posible solución en el cambio de índices (nT,n1 y n2), se actualizan los vértices.
            [valido,Px]=penalizar12(pendulo,xk1',vk1(:,i)',simetria); %Se aplica la penalización.
            %Se simula para obtener la salida del sistema para cada fk1:
            if valido
                 xd=desnormalizar12(pendulo,xk1,simetria); %Llamado a la función par desnormalizar las componentes de xk1
                 %Se asigna el valor desnormalizado al archivo .fis, aplicando simetría, a los efectos de obtener la simulación:
                 pendulo=parametros12(pendulo,xd,vk1(:,i),simetria);
                 %sim('C:\Users\Luis\Dropbox\Postgrado\Control Difuso\Tarea 11\Pendulo11AnguloFuzzy',30);
                 sim('C:\Users\brand\OneDrive\Escritorio\tesis\simulacion\simu2\fuzzyImpleAjust',time);   
            end
            % Se plica la función objetivo para cada fk+1:
            fk1(i,1)=fobjetivo12(u,ess,salida,valido,Px,time);
            %disp(fk1(i,1));  
        
            if fk1(i,1)<fk
                fk=fk1(i,1);
                vk=vk1(:,i); %Se asigna a vk el nuevo valor que minimiza a la función objetivo.        
                xk=actualizar12(pendulo,xk,vk,simetria); %Se actualiza en definitivo los vértices en función del Vk que minimiza la F.O
                aux=1;
                break
            end;
   
        end
        
%         %% SE APLICAN LAS RESTRICCIONES Y SE EVALUAN LOS xk+1 PARA OBTENER f(xk+1):
%         for i=1:2*dim
%             
%             xk1=actualizar12(pendulo,xk,vk1(:,i),simetria); %Para cada posible solución en el cambio de índices (nT,n1 y n2), se actualizan los vértices.
%             [valido,Px]=penalizar12(pendulo,xk1',vk1(:,i)',simetria); %Se aplica la penalización.
%             %             %             
%             %Se simula para obtener la salida del sistema para cada fk1:
%             if valido
%                  xd=desnormalizar12(pendulo,xk1,simetria); %Llamado a la función par desnormalizar las componentes de xk1
%             
%             %Se asigna el valor desnormalizado al archivo .fis, aplicando simetría, a los efectos de obtener la simulación:
%            
%                  pendulo=parametros12(pendulo,xd,vk1(:,i),simetria);
%                 
%                  %sim('C:\Users\Luis\Dropbox\Postgrado\Control Difuso\Tarea 12\Pendulo12AnguloFuzzy',time);
%                  sim('C:\Pana\Archivos Matlab\Matlab2016a\ClasesPostgrado\Sem03_2016\SarcoLuis\12ArchivosPendulo\Pendulo12AnguloFuzzy',time);
%                 
%             end
%             
%             % Se plica la función objetivo para cada fk+1:
%             fk1(i,1)=fobjetivo12(u,ess,salida,valido,Px,time);
%             %disp(fk1(i,1));
%               
%         end
%         
% 
%         
%         %% SE BUSCA EL fk+1 MÍNIMO DE ENTRE TODOS LOS VALORES CALCULADOS:
%         minimo=min(fk1);
%         if (minimo<fk)
%              i=find(minimo==fk1);
%              i=i(1,1); % Se toma la componente (1,1) de i en caso de que este resulte un vector (caso en que dos o más componente de fk1 sean iguales);
%              fk=fk1(i,1);
%              vk=vk1(:,i); %Se asigna a vk el nuevo valor que minimiza a la función objetivo.        
%              xk=actualizar12(pendulo,xk,vk,simetria); %Se actualiza en definitivo los vértices en función del Vk que minimiza la F.O
%              aux=1;
%         end;
        
        if (aux==0)            
            dk=1/2*dk;                             
        end
        
if p>100 %criterio de parada en caso de que la función no presente mínimo (evitar loop)
    break
end
          
end
xm=desnormalizar12(pendulo,xk,simetria); %El vector de salida es xk desnormalizado.
pendulo=parametros12(pendulo,xm,vk,simetria);
%Se simula para obtener la salida del sistema con el valor óptimo
%alcanzado:
%sim('C:\Users\Luis\Dropbox\Postgrado\Control Difuso\Tarea 12\Pendulo12AnguloFuzzy',time);
sim('C:\Users\brand\OneDrive\Escritorio\tesis\simulacion\simu2\fuzzyImpleAjust',time);

optitank=pendulo; %Se asigna a la salida el archivo .fis optimizado por esta función.
tiempo=toc;

end

