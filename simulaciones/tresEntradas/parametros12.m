function [pendulo_out] = parametros12(pendulo,x,v,simetria)
%Asigna al archivo.fis los valores de los vértices del contenidos en el
%vector "x"

pendulo_out=pendulo;

x=x';
v=v';
N_IN=length(pendulo_out.input);
offset=1;
k=1;
  if simetria
      for i=1:N_IN
          N_FP=length(pendulo.input(i).mf);
          if rem(N_FP,2)==0 % Si el número de las FP son pares:
              N_FP_S=N_FP/2;
          else %Si el número de F.P es impar:
              N_FP_S=floor(N_FP/2)+rem(N_FP,2); 
          end
          for j=1:N_FP_S
              if (j==1)
                    pendulo_out.input(i).mf(j).params(3:4)=x(offset:offset+1); %Si es la primera F.P se considera trapezoidal abierta.
                    pendulo_out.input(i).mf(N_FP+1-j).params(1:2)=(-1)*fliplr(x(offset:offset+1)); %Si es la primera F.P se considera trapezoidal abierta. 
                    pendulo_out.input(i).mf(j).params(5:7)=v(k:k+2); %Se cargan los indices (nT, n1 y n2) de cada F.P
                    pendulo_out.input(i).mf(N_FP+1-j).params(5:7)=v(k:k+2);
                    k=k+3;
                    offset=offset+2;
              else
                  if (j==N_FP_S)
                        pendulo_out.input(i).mf(j).params(1:2)=x(offset:offset+1); %Si es la útima F.P se considera trapezoidal abierta. 
                        pendulo_out.input(i).mf(N_FP+1-j).params(3:4)=(-1)*fliplr(x(offset:offset+1)); %Si es la primera F.P se considera trapezoidal abierta.                        
                        pendulo_out.input(i).mf(j).params(5:7)=v(k:k+2); %Se cargan los indices (nT, n1 y n2) de cada F.P
                        pendulo_out.input(i).mf(N_FP+1-j).params(5:7)=v(k:k+2);
                        k=k+3;
                        offset=offset+2;
                     else
                        pendulo_out.input(i).mf(j).params=x(offset:offset+3);%Se consideran todos los vérties en cualquier otra F.P
                        pendulo_out.input(i).mf(N_FP+1-j).params=(-1)*fliplr(x(offset:offset+3));%Se consideran todos los vérties en cualquier otra F.P
                        pendulo_out.input(i).mf(j).params(5:7)=v(k:k+2);
                        pendulo_out.input(i).mf(N_FP+1-j).params(5:7)=v(k:k+2);
                        k=k+3;
                        offset=offset+4;
                  end
              end
          end          
      end 
              
          
            
  else % Si no hay simetria:
       for i=1:N_IN
          N_FP=length(tanque.input(i).mf);
          for j=1:N_FP
              if (j==1)
                    tanque_out.input(i).mf(j).params(3:4)=x(offset:offset+1); %Si es la primera F.P se considera trapezoidal abierta.
                    tanque_out.input(1).mf(j).params(5:7)=v(k:k+2);
                    offset=offset+2;
                    k=k+3;
              else
                  if (j==N_FP)
                        tanque_out.input(i).mf(j).params(1:2)=x(offset:offset+1); %Si es la útima F.P se considera trapezoidal abierta. 
                        offset=offset+2;
                        tanque_out.input(1).mf(j).params(5:7)=v(k:k+2); %Se cargan los indices (nT, n1 y n2) de cada F.P
                        k=k+3;
                     else
                        tanque_out.input(i).mf(j).params(1:4)=x(offset:offset+3);%Se consideran todos los vérties en cualquier otra F.P
                        tanque_out.input(1).mf(j).params(5:7)=v(k:k+2); %Se cargan los indices (nT, n1 y n2) de cada F.P
                        offset=offset+4;
                        k=k+3;
                  end
              end
          end

      end
  end
end

