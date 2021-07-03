function [ xout ] = actualizar12(pendulo,x,v,simetria)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
v=v';
x=x';
dim=length(x);
xout=zeros(1,dim);

N_IN=length(pendulo.input);
offset=1;
k=1;
for i=1:N_IN
    N_FP=length(pendulo.input(i).mf);
    if (simetria)
        if rem(N_FP,2)==0 %Si es par:
            N_FP=N_FP/2;
        else %Si es impar:
            N_FP=(floor(N_FP/2)+rem(N_FP,2));
        end
    end 
    
    for j=0:N_FP-1
        if j==0
            xout(offset)=x(offset)+v(k)*(x(offset+1)-x(offset)); %c=c+nT*(d-c)
            xout(offset+1)=x(offset)+(x(offset+1)-x(offset))/v(k+1); %d=c+(d-c)/n1
            offset=offset+2;
            k=k+3;
        else
            if j==N_FP-1
                xout(offset)=x(offset+1)-(x(offset+1)-x(offset))/v(k+1); %a=b-(b-a)/n1
                xout(offset+1)=x(offset+1)-v(k)*(x(offset+1)-x(offset)); %b=b-nT(b-a)
                 offset=offset+2;
                 k=k+3;
            else
                xout(offset)=x(offset+1)-(x(offset+1)-x(offset))/v(k+1); %a=b-(b-a)/n1
                xout(offset+1)=x(offset+1)-v(k)*(x(offset+1)-x(offset)); %b=b-nT(b-a) 
                xout(offset+2)=x(offset+2)+v(k)*(x(offset+3)-x(offset+2)); %c=c+nT*(d-c)
                xout(offset+3)=x(offset+2)+(x(offset+3)-x(offset+2))/v(k+1); %d=c+(d-c)/n1
                offset=offset+4;
                k=k+3;
            end
        end
    end


   
   
end
xout=xout';
end

